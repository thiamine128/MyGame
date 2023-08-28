#version 330 core

in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D gNormal;
uniform sampler2D gColor;
uniform int screenWidth;
uniform int screenHeight;

vec4 getSize(sampler2D tex, vec2 vUv) {
    float dx = 0.52 / screenWidth;
    float dy = 0.52 / screenHeight;
    vec4 curNormalY = -1. * texture2D(tex, vUv + vec2(-dx, -dy))
        + -2. * texture2D(tex, vUv + vec2(-dx, 0.))
        + -1. * texture2D(tex, vUv + vec2(-dx, dy))
        + 1. * texture2D(tex, vUv + vec2(dx, -dy))
        + 2. * texture2D(tex, vUv + vec2(dx, 0.))
        + 1. * texture2D(tex, vUv + vec2(dx, dy));

    vec4 curNormalX = -1. * texture2D(tex, vUv + vec2(-dx, -dy))
        + 1. * texture2D(tex, vUv + vec2(-dx, dy))
        + -2. * texture2D(tex, vUv + vec2(0., -dy))
        + 2. * texture2D(tex, vUv + vec2(0., dy))
        + -1. * texture2D(tex, vUv + vec2(dx, -dy))
        + 1. * texture2D(tex, vUv + vec2(dx, dy));
        
        return sqrt(curNormalX * curNormalX + curNormalY * curNormalY);
}

bool check(vec4 size, float threshold) {
    return size.x > threshold || size.y > threshold || size.z > threshold;
}

void main()
{
    FragColor.a = 1.0;
    FragColor.rgb = texture(gColor, TexCoord).rgb;

    if (check(getSize(gColor, TexCoord), 0.3) || check(getSize(gNormal, TexCoord), 5.0)) {
        FragColor.rgb = vec3(0.0);
    }
}