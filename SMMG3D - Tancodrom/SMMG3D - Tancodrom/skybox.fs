#version 330 core
out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube skybox;
uniform float hue;
uniform float time;

void main()
{   
    vec3 adjustedTexCoords = TexCoords;
    
    float faceShift = 0.01 * sin(time);
    if (TexCoords.y >= 0.999) {
        adjustedTexCoords.xz += mod(time * 0.008, 1.0);
    }
    vec3 customColor = vec3(0.004,0.008,0.071);
    vec4 skyboxColor = texture(skybox, adjustedTexCoords);
    vec3 blendedColor = mix(skyboxColor.rgb, customColor, 1-hue);
    FragColor = vec4(blendedColor, skyboxColor.a);
}