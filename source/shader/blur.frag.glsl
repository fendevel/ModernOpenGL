R"===(
#version 460

layout (location = 0) out vec4 col;
layout (binding = 0) uniform sampler2D tex_col;
layout (binding = 1) uniform sampler2D tex_vel;

layout (location = 0) uniform float vel_scale;

in in_block
{
	vec2 texcoord;
} inp;

void main()
{
    vec2 texel_size = 1.0 / vec2(textureSize(tex_col, 0));
    vec2 tex_coords = gl_FragCoord.xy * texel_size;
    vec2 vel = texture(tex_vel, tex_coords).rg;
    vel *= vel_scale;

    float speed = length(vel / texel_size);
    int samples = clamp(int(speed), 1, 40);

    col = texture(tex_col, inp.texcoord);

    for (int i = 1; i < samples; ++i)
    {
        vec2 offset = vel * (float(i) / float(samples - 1) - 0.5);
        col += texture(tex_col, tex_coords + offset);
    }
    col /= float(samples);
}

)==="