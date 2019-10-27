#version 330 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shineness;
};

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 normal;
in vec3 fragPos;
in vec2 texCoords;

out vec4 fragColor;

uniform vec3 lightColor; 

uniform Material material;
uniform Light light; 

uniform float time; 

void main()
{
    vec3 diffuseColor = vec3(texture(material.specular, texCoords));
    vec3 ambient = light.ambient * diffuseColor;

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = light.diffuse * diff * diffuseColor; 

    vec3 viewDir = normalize(-fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shineness);
    vec3 specularColor = vec3(texture(material.specular, texCoords));
    vec3 specular = light.specular * spec * specularColor;

    vec3 emission = vec3(0.0f);
    if (specularColor.r == 0.0f) {
        vec3 emissionFadeOut = vec3(sin(time) * 0.5 + 0.5);
        vec2 emissionTextOffset = vec2(0.0f, time);
        vec3 emissionColor = vec3(texture(material.emission, texCoords + emissionTextOffset));
        emission = emissionFadeOut * emissionColor;
    }

    vec3 result = ambient + diffuse + specular + emission;
    fragColor = vec4(result, 1.0f);
}
