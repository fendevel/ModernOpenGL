R"===(
#version 460

out gl_PerVertex { vec4 gl_Position; };

out out_block
{
	vec3 pos;
	vec3 nrm;
	vec2 uvs;
	smooth vec4 curr_pos;
	smooth vec4 prev_pos;
} o;

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 col;
layout (location = 2) in vec3 nrm;
layout (location = 3) in vec2 uvs;

layout (location = 0) uniform mat4 proj;
layout (location = 1) uniform mat4 view;
layout (location = 2) uniform mat4 modl;
layout (location = 3) uniform mat4 mvp_curr;
layout (location = 4) uniform mat4 mvp_prev;
layout (location = 5) uniform bool except;

void main()
{
	if (!except)
	{
		o.curr_pos = mvp_curr * vec4(pos, 1.0);
		o.prev_pos = mvp_prev * vec4(pos, 1.0);
	}
	else
	{
		o.curr_pos = mvp_curr * vec4(pos, 1.0);
		o.prev_pos = o.curr_pos;
	}
	const vec4 mpos = (view * modl * vec4(pos, 1.0));
	o.pos = (modl * vec4(pos, 1.0)).xyz;
	o.nrm = mat3(transpose(inverse(modl))) * nrm;
	o.uvs = uvs;
	gl_Position = proj * mpos;
}

)==="