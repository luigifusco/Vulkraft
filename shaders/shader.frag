#version 450

layout(binding = 1) uniform FragmentUniformBufferObject {
    vec3 lightDir;
	vec3 eyePos;
} ubo;
layout(binding = 2) uniform sampler2D texSampler;

layout(location = 0) in vec3 fragNorm;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in vec3 fragPos;

layout(location = 0) out vec4 outColor;

void main() {
    vec3 Norm = normalize(fragNorm);

	vec3 EyeDir = normalize(ubo.eyePos - fragPos);
	float NormP = clamp(dot(Norm, ubo.lightDir),0,1) * 0.8f;

	vec3 Diffuse = texture(texSampler, fragTexCoord).rgb * (NormP  + 0.2f);
	vec3 Reflection = -reflect(ubo.lightDir, Norm);
	vec3 Specular = vec3(1.0f, 1.0f, 1.0f) * pow(clamp(dot(EyeDir, Reflection), 0, 1), 64.0f);
	
	outColor = vec4((Diffuse * 0.8f + Specular * 0.2f), 1.0f);

}