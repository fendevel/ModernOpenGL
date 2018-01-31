#version 450

out gl_PerVertex { vec4 gl_Position; };

layout (location = 0) uniform mat3 cam_dir;
layout (location = 1) uniform float fov;
layout (location = 2) uniform float ratio;
layout (location = 3) uniform vec2 uv_diff;

out out_block
{
	vec2 uvs;
	vec3 ray;
} o;

vec3 skyray(vec2 tex, float fovy, float aspect)
{
    float d = 0.5 / tan(fovy/2.0);
    return normalize(vec3((tex.x - 0.5) * aspect, tex.y - 0.5, -d));
}

void main()
{
	vec2 v[] = {
		vec2(-1.0f, 1.0f),
 		vec2( 1.0f, 1.0f),
 		vec2( 1.0f,-1.0f),
		vec2(-1.0f,-1.0f)
	};
	vec2 t[] = {
		vec2(0.0f, 1.0f),
		vec2(1.0f, 1.0f),
		vec2(1.0f, 0.0f),
		vec2(0.0f, 0.0f)

	};
	uint i[] = { 0, 3, 2, 2, 1, 0 };

	const vec2 pos = v[i[gl_VertexID]];
	const vec2 uvs = t[i[gl_VertexID]];

	o.ray = cam_dir*skyray(uvs, fov, ratio);
	o.uvs = uvs * uv_diff;
	gl_Position = vec4(pos, 0.0, 1.0);
}