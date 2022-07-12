#version 450

layout(binding = 0) uniform VertexUniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
} ubo;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNorm;
layout(location = 2) in vec2 inTexCoord;
layout(location = 3) in vec3 inMaterial;

layout(location = 0) out vec3 fragNorm;
layout(location = 1) out vec2 fragTexCoord;
layout(location = 2) out vec3 fragPos;
layout(location = 3) out vec3 fragMaterial;

void main() {
    gl_Position = ubo.proj * ubo.view * ubo.model * vec4(inPosition, 1.0);
    fragNorm = inNorm;
    fragTexCoord = inTexCoord;
    fragPos = inPosition;
    fragMaterial = inMaterial;
}