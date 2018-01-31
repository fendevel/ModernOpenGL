#version 450

layout (location = 0) out vec4 col;
layout (binding = 0) uniform sampler2D pos_tex;
layout (binding = 1) uniform sampler2D nrm_tex;
layout (binding = 2) uniform sampler2D alb_tex;
layout (binding = 3) uniform sampler2D dep_tex;
layout (binding = 4) uniform samplerCube skybox;

layout (location = 0) uniform vec3 cam_pos;

in in_block
{
	vec2 uvs;
	vec3 ray;
} i;

vec3 calc_spec(float strength, vec3 col, vec3 view_pos, vec3 vert_pos, vec3 light_dir, vec3 normal)
{
	vec3 
		view_dir = normalize(view_pos - vert_pos),
		ref_dir = reflect(-light_dir, normal);
	
	float spec = pow(max(dot(view_dir, ref_dir), 0.0), 32.0);
	return strength * spec * col;
}

void main()
{
	const vec3 pos = texture(pos_tex, i.uvs).rgb;
	const vec3 nrm = texture(nrm_tex, i.uvs).rgb;
	const vec4 alb_spec = texture(alb_tex, i.uvs);
	const vec3 alb = alb_spec.rgb;
	const float spc = alb_spec.a;
	const float dep = texture(dep_tex, i.uvs).r;
	
	vec4 final = vec4(1.0);
	vec3 ambient_col = vec3(0.2);

	vec3 light_col = vec3(1.0);
	vec3 light_pos = vec3(0.0, 8.0, 0.0);
	vec3 light_dir = normalize(light_pos - pos);
	float light_dif = max(dot(nrm, light_dir), 0.0);
		
	vec3 light_spec = calc_spec(spc, light_col, cam_pos, pos, light_dir, nrm);

	final.xyz = (ambient_col + (light_dif * light_col) + light_spec) * alb;
	if (dep == 1.0)
		col = texture(skybox, i.ray);
	else
		col = final;
}