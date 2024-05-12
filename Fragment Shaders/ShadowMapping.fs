#version 330 core
out vec4 FragColor;

#define MAX_LIGHTS 20

struct Light {
    vec3 position;
    vec3 color;
    float intensity;
};

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} fs_in;

uniform sampler2D diffuseTexture;
uniform sampler2D shadowMap;

uniform vec3 viewPos;
uniform int numLights;
uniform Light lights[MAX_LIGHTS];

float ShadowCalculation(vec4 fragPosLightSpace)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // calculate bias (based on depth map resolution and slope)
    vec3 normal = normalize(fs_in.Normal);
    vec3 lightDir = normalize(lights[0].position - fs_in.FragPos);

    float bias = max(0.001 * (1.0 - dot(normal, lightDir)), 0.001);
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for (int x = -1; x <= 1; ++x)
    {
        for (int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0; 
        }
    }
      shadow /= 9.0;

     if (projCoords.z > 0.99f)
        shadow = 0.0f;

    return shadow;
}

void main()
{           
    vec3 color = texture(diffuseTexture, fs_in.TexCoords).rgb;
    vec3 normal = normalize(fs_in.Normal);
    vec3 lighting = vec3(0.0);

    if(length(vec3(0.0) - fs_in.FragPos) > 150)
    {
        FragColor = vec4(color, 1.0);
        return;
    }

    for (int i = 0; i < numLights; ++i)
    {
        // intensity
        float distance = length(lights[i].position - fs_in.FragPos);
        float intensity = lights[i].intensity / log(distance * distance + 1.0);
        // ambient
        vec3 ambient = 0.3 * lights[i].color * intensity;
        // diffuse
        vec3 lightDir = normalize(lights[i].position - fs_in.FragPos);
        float diff = max(dot(lightDir, normal), 0.0);
        vec3 diffuse = diff * lights[i].color * intensity;
        // specular
        vec3 viewDir = normalize(viewPos - fs_in.FragPos);
        float spec = 0.0;
        vec3 halfwayDir = normalize(lightDir + viewDir);
        spec = pow(max(dot(normal, halfwayDir), 0.0), 4096.0);
        vec3 specular = spec * lights[i].color * intensity;
        
        // calculate shadow
        float shadow = ShadowCalculation(fs_in.FragPosLightSpace);
        lighting += (ambient + (1.0 - shadow) * (diffuse + specular)) * color;
    }

    FragColor = vec4(lighting, 1.0);
}