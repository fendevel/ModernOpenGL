#version 450

in in_block
{
	vec3 pos;
	vec3 nrm;
	vec2 uvs;
} i;

layout (location = 0) out vec3 out_pos;
layout (location = 1) out vec3 out_nrm;
layout (location = 2) out vec4 out_alb;

layout (binding = 0) uniform sampler2D dif;
layout (binding = 1) uniform sampler2D spc;
layout (binding = 2) uniform sampler2D nrm;

void main()
{
	vec3 dif_tex = texture(dif, i.uvs).rgb;
	vec3 spc_tex = texture(spc, i.uvs).rgb;
	vec3 nrm_tex = texture(nrm, i.uvs).rgb;

	out_pos = i.pos;
	out_nrm = normalize(cross(i.nrm, nrm_tex));
	out_alb.rgb = texture(dif, i.uvs).rgb;
	out_alb.a = texture(spc, i.uvs).r;
}