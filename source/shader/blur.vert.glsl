R"===(
#version 460

out gl_PerVertex{ vec4 gl_Position; };

layout(location = 3) uniform vec2 u_uv_diff;

out out_block
{
	vec2 texcoord;
} o;

void main()
{
	vec2 v[] = {
		vec2(-1.0f, 1.0f),
		vec2(1.0f, 1.0f),
		vec2(1.0f,-1.0f),
		vec2(-1.0f,-1.0f)
	};
	vec2 t[] = {
		vec2(0.0f, 1.0f),
		vec2(1.0f, 1.0f),
		vec2(1.0f, 0.0f),
		vec2(0.0f, 0.0f)

	};
	uint i[] = { 0, 3, 2, 2, 1, 0 };

	const vec2 position = v[i[gl_VertexID]];
	const vec2 texcoord = t[i[gl_VertexID]];

	o.texcoord = texcoord * u_uv_diff;
	gl_Position = vec4(position, 0.0, 1.0);
}

)==="