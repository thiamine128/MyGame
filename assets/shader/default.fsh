#version 330 core

in vec2 TexCoord;
in vec4 PosLightSpace;
in vec3 Normal;
in vec3 Pos;

out vec4 FragColor;

uniform sampler2D texture0;
uniform sampler2D shadowMap;
uniform vec3 lightPos;
uniform float time;

vec2 poissonDisk[4] = vec2[](
  vec2(-0.94201624, -0.39906216),
  vec2(0.94558609, -0.76890725),
  vec2(-0.094184101, -0.92938870),
  vec2(0.34495938, 0.29387760)
);

float calcShadow(vec4 pos) {
    vec3 coord = pos.xyz / pos.w;
    coord = coord * 0.5 + 0.5;

    if (coord.x > 1.0 || coord.y > 1.0 || coord.x < 0.0 || coord.y < 0.0)
        return 1.0;
    float shadow = 1.0;
    vec3 lightDir = normalize(lightPos);
    vec3 normal = normalize(Normal);
    float bias = max(0.01 * (0.5 - dot(normal, lightDir)), 0.006);
    float dense = 0.05f;
    if (time >= 0.6f || time <= 0.1f)
        dense = 0.0f;
    else if (time >= 0.1f && time <= 0.15f)
        dense = mix(0.0f, 0.05f, (time - 0.1f) / 0.05f);
    else if (time >= 0.55f && time <= 0.6f)
        dense = mix(0.05f, 0.0f, (time - 0.55f) / 0.05f);
    else
        dense = 0.05f;
    for (int i = 0; i < 4; ++i) {
        if (texture(shadowMap, coord.xy + poissonDisk[i] / 700.0).r < coord.z - bias) {
            shadow -= dense;
        }
    }
    return shadow;
}

vec3 night = vec3(0.4, 0.4, 1.0);
vec3 day = vec3(1.0);

void main()
{
    FragColor = vec4(1.0);
    vec3 col = vec3(1.0);
    if (time > 0.5f && time < 0.7f)
    {
        col = mix(day, night, (time - 0.5f) / 0.2f);
    }
    else if (time >= 0.7f)
    {
        col = night;
    }
    else if (time <= 0.2f)
    {
        col = mix(night, day, time / 0.2f);
    }
    else
    {
        col = day;
    }
    FragColor.rgb = texture(texture0, TexCoord).rgb * col * calcShadow(PosLightSpace);
}