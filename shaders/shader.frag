#version 450

layout(binding = 1) uniform FragmentUniformBufferObject {
    vec3 lightDir;
} ubo;
layout(binding = 2) uniform sampler2D texSampler;

layout(location = 0) in vec3 fragNorm;
layout(location = 1) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

void main() {
    //vec3 C = texture(texSampler, fragTexCoord).xyz * max(dot(ubo.lightDir, fragNorm), 0);
    //outColor = vec4(C, 1.0f) + vec4(0.1f);

    vec3 Norm = normalize(fragNorm);

	//vec3 EyeDir = normalize(gubo.eyePos - fragPos);
	vec3 NormP = dot(Norm, ubo.lightDir) > 0 ? Norm : -Norm;

	vec3 Diffuse = texture(texSampler, fragTexCoord).rgb * (dot(NormP, ubo.lightDir) * 0.99f + 0.01f);
	//vec3 Specular = vec3(pow(max(dot(EyeDir, -reflect(gubo.lightDir, NormP)),0.0f), 64.0f));
	
	outColor = vec4(Diffuse, 1.0f);

}