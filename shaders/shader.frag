#version 450

layout(binding = 1) uniform FragmentUniformBufferObject {
    vec3 lightDir0;
	vec3 lightCol0;
	vec3 lightDir1;
	vec3 lightCol1;
	vec3 eyePos;
	vec2 ambFactor;
	vec3 eyeDir;
} ubo;
layout(binding = 2) uniform sampler2D texSampler;

layout(location = 0) in vec3 fragNorm;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in vec3 fragPos;
layout(location = 3) in vec3 fragMaterial;

layout(location = 0) out vec4 outColor;

vec3 Oren_Nayar_Diffuse_BRDF(vec3 lightDir, vec3 normVect, vec3 viewDir, vec3 mainColor, float sigma) {	
	float theta_i = acos(dot(lightDir, normVect));
	float theta_r = acos(dot(viewDir, normVect));
	float alpha = max(theta_i, theta_r);
	float beta = min(theta_i, theta_r);

	float sigma_2 = pow(sigma, 2);
	float A = 1 - 0.5 * sigma_2 / (sigma_2 + 0.33);
	float B = 0.45 * sigma_2 / (sigma_2 + 0.09);

	vec3 v_i = normalize(lightDir - dot(lightDir, normVect) * normVect);
	vec3 v_r = normalize(viewDir - dot(viewDir, normVect) * normVect);
	float G = max(0, dot(v_i, v_r));
	vec3 L = mainColor * clamp(dot(lightDir, normVect), 0, 1);

	return L * (A + B * G * sin(alpha) * tan(beta));
}

vec3 Phong_Specular_BRDF(vec3 lightDir, vec3 normVect, vec3 viewDir, vec3 mainColor, float gamma)  {
	vec3 R = 2 * normVect * dot(lightDir, normVect) - lightDir;
	return mainColor * pow(clamp(dot(viewDir, R), 0, 1), gamma);
}

vec3 spot_light_color(vec3 pos) {
	// Spot light color
	float cos_alpha = dot(normalize(ubo.eyePos - pos), ubo.eyeDir);
	float c_in = cos(0.261799f);
	float c_out = cos(0.523599f);
	float dimming = clamp((cos_alpha - c_out) / (c_in - c_out), 0, 1);
	return vec3(.3 * (244./255.),.3 * (252./255.),.3 * (3./255.)) * dimming * pow((1 / length(ubo.eyePos - pos)),1.f);
}

void main() {
	vec3 Norm = normalize(fragNorm);
	vec3 EyeDir = normalize(ubo.eyePos - fragPos);

	vec3 lightDir0 = normalize(ubo.lightDir0);
	vec3 lightDir1 = normalize(ubo.lightDir1);
	
	vec4 Texture = texture(texSampler, fragTexCoord);
	if(Texture.a == 0) discard;

	vec3 DiffColor = Texture.rgb;
	
	vec3 Diffuse = vec3(0);
	Diffuse += Oren_Nayar_Diffuse_BRDF(lightDir0, Norm, EyeDir, DiffColor, fragMaterial.y) * ubo.lightCol0;
	Diffuse += Oren_Nayar_Diffuse_BRDF(lightDir1, Norm, EyeDir, DiffColor, fragMaterial.y) * ubo.lightCol1;
	
	vec3 Specular = vec3(0);
	Specular += Phong_Specular_BRDF(lightDir0, Norm, EyeDir, vec3(0.05), fragMaterial.z) * ubo.lightCol0;
	Specular += Phong_Specular_BRDF(lightDir1, Norm, EyeDir, vec3(0.05), fragMaterial.z) * ubo.lightCol1;

	vec3 Ambient = ubo.ambFactor.x * DiffColor;

	vec3 SpotLight = vec3(0);
	if (lightDir1.y > 0) {
		SpotLight = spot_light_color(fragPos) * DiffColor;
	}
	
	if(fragMaterial.x == 1.0f) {
		outColor = vec4(Diffuse + Specular + Ambient, Texture.a);
	} else {
		outColor = vec4(Diffuse + Specular + Ambient + SpotLight, 1.0f);
	}
}