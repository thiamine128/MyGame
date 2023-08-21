#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texcoord;

uniform mat4 model;
uniform vec2 viewport;

out vec2 TexCoord;

void main() {
    vec3 pos = (model * vec4(position, 1.0)).xyz;
    pos.xy /= viewport;
    pos.xy -= vec2(1.0);
    gl_Position = vec4(pos, 1.0);
    TexCoord = texcoord;
}