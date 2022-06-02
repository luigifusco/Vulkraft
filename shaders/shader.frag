#version 450

layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
    vec3 lightDir;
} ubo;
layout(binding = 1) uniform sampler2D texSampler;

layout(location = 0) in vec3 fragNorm;
layout(location = 1) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

void main() {
    vec3 C = texture(texSampler, fragTexCoord).xyz * max(dot(ubo.lightDir, fragNorm), 0);
    outColor = vec4(C, 1.0f) + vec4(0.1f);

}