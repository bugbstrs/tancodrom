#version 330 core
out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} fs_in;

uniform sampler2D diffuseTexture;
//uniform sampler2D shadowMap;
uniform sampler2DArray shadowMap;

uniform int numLights;
uniform vec3 lightPos[10];
uniform vec3 lightColorArray[10];
uniform float lightIntensity[10];

uniform vec3 viewPos;
uniform float hue;

float CalculateShadow(vec4 fragPosLightSpace, int lightIndex) {
    vec3 lightDir = normalize(lightPos[lightIndex] - fs_in.FragPos);
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    projCoords = projCoords * 0.5 + 0.5;
    float closestDepth = texture(shadowMap, vec3(projCoords.xy, lightIndex)).r; 
    float currentDepth = projCoords.z;
    float bias = max(0.05 * (1.0 - dot(fs_in.Normal, lightDir)), 0.001);
    float shadow = 0.0;
    if (currentDepth - bias > closestDepth) {
        shadow = 1.0;
    }
    return shadow;
}

void main()
{
    vec3 color = hue * texture(diffuseTexture, fs_in.TexCoords).rgb;
    vec3 ambient = vec3(0.0);
    vec3 lighting = vec3(0.0);

    for (int i = 0; i < numLights; ++i)
    {
        vec3 lightDir = normalize(lightPos[i] - fs_in.FragPos);
        vec3 lightColor = lightIntensity[i] * lightColorArray[i];
        vec3 viewDir = normalize(viewPos - fs_in.FragPos);
        vec3 reflectDir = reflect(-lightDir, fs_in.Normal);

        // Ambient (added outside the light loop)
        ambient += 0.3 * color;

        // Diffuse
        float diff = max(dot(fs_in.Normal, lightDir), 0.0);
        vec3 diffuse = diff * lightColor;

        // Specular
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
        vec3 specular = spec * lightColor;

        // Shadow
        //float shadow = ShadowCalculation(fs_in.FragPosLightSpace, lightDir);
        
        float shadow = CalculateShadow(fs_in.FragPosLightSpace, i);

        // Lighting calculation
        lighting += (1.0 - shadow) * (diffuse + specular);
    }

    // Final color with ambient added
    lighting += ambient;
    
    FragColor = vec4(lighting * color, 1.0);
}
