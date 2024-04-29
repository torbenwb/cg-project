#version 330 core
uniform mat4 model;
uniform mat4 view;
uniform mat4 perspective;

layout (location=0) in vec3 point;
layout (location=1) in vec3 normal;
layout (location=2) in vec2 uv;

out vec3 fragPos;
out vec3 fragNormal;
out vec2 fragUV;

void main() {
    vec4 worldPosition = model * vec4(point, 1);
    vec4 viewPosition = view * worldPosition;

    gl_Position = perspective * viewPosition;

    fragPos = vec3(model * vec4(point, 1.0));
    fragNormal = (model * vec4(normal, 0.0)).xyz;
    fragUV = uv;
}