#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;
layout (location = 3) in mat4 instanceMatrix;

out vec2 TexCoord;
out vec4 PosLightSpace;
out vec3 Normal;
out vec3 Pos;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 lightSpace;

void main() {
    gl_Position = projection * view * instanceMatrix * vec4(position, 1.0);
    TexCoord = texCoord;
    Pos = vec3(instanceMatrix * vec4(position, 1.0));
    PosLightSpace = lightSpace * instanceMatrix * vec4(position, 1.0);
    Normal = normal;
}