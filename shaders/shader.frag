#version 450

layout(binding = 1) uniform FragmentUniformBufferObject {
    vec3 lightDir0;
	vec3 lightCol0;
	vec3 lightDir1;
	vec3 lightCol1;
	vec3 eyePos;
	vec2 ambFactor;
} ubo;
layout(binding = 2) uniform sampler2D texSampler;

layout(location = 0) in vec3 fragNorm;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in vec3 fragPos;

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

void main() {
	vec3 Norm = normalize(fragNorm);
	vec3 EyeDir = normalize(ubo.eyePos - fragPos);

	vec3 lightDir0 = normalize(ubo.lightDir0);
	vec3 lightDir1 = normalize(ubo.lightDir1);
	
	float sigma = 2.0f;		// Oren Nayar BRDF parameter
	float gamma = 200.0f;	// Phong BRDF parameter
	
	vec4 Texture = texture(texSampler, fragTexCoord);
	if(Texture.a == 0) discard;

	vec3 DiffColor = Texture.rgb;
	
	vec3 Diffuse = vec3(0);
	Diffuse += Oren_Nayar_Diffuse_BRDF(lightDir0, Norm, EyeDir, DiffColor, sigma) * ubo.lightCol0;
	Diffuse += Oren_Nayar_Diffuse_BRDF(lightDir1, Norm, EyeDir, DiffColor, sigma) * ubo.lightCol1;
	
	vec3 Specular = vec3(0);
	Specular += Phong_Specular_BRDF(lightDir0, Norm, EyeDir, vec3(0.05), gamma) * ubo.lightCol0;
	Specular += Phong_Specular_BRDF(lightDir1, Norm, EyeDir, vec3(0.05), gamma) * ubo.lightCol1;

	vec3 Ambient = ubo.ambFactor.x * DiffColor;
	
	outColor = vec4(Diffuse + Specular + Ambient, 1.0f);	
}