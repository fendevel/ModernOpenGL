R"===(
#version 460

in in_block
{
	vec3 pos;
    vec3 nrm;
    vec2 uvs;
    smooth vec4 curr_pos;
    smooth vec4 prev_pos;
} i;

layout(location = 0) out vec3 out_pos;
layout(location = 1) out vec3 out_nrm;
layout(location = 2) out vec4 out_alb;
layout(location = 3) out vec2 out_vel;
layout(location = 4) out vec3 out_emi;

layout(binding = 0) uniform sampler2D dif;
layout(binding = 1) uniform sampler2D spc;
layout(binding = 2) uniform sampler2D nrm;
layout(binding = 3) uniform sampler2D emi;

layout(location = 0) uniform float emissive_strength;

void main()
{
    vec3 dif_tex = texture(dif, i.uvs).rgb;
    vec3 spc_tex = texture(spc, i.uvs).rgb;
    vec3 nrm_tex = texture(nrm, i.uvs).rgb;

    out_pos = i.pos;
    out_nrm = normalize(cross(i.nrm, nrm_tex));
    out_alb.rgb = texture(dif, i.uvs).rgb;
    out_alb.a = texture(spc, i.uvs).r;
    out_vel = ((i.curr_pos.xy / i.curr_pos.w) * 0.5 + 0.5) - ((i.prev_pos.xy / i.prev_pos.w) * 0.5 + 0.5);
    out_emi = texture(emi, i.uvs).rgb * emissive_strength;
}

)==="