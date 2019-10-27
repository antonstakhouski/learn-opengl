#version 330 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shineness;
};

struct Light {
    vec3 direction; 

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

void main()
{
    vec3 diffuseColor = vec3(texture(material.diffuse, texCoords));
    vec3 ambient = light.ambient * diffuseColor;

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = light.diffuse * diff * diffuseColor; 

    vec3 viewDir = normalize(-fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shineness);
    vec3 specularColor = vec3(texture(material.specular, texCoords));
    vec3 specular = light.specular * spec * specularColor;

    vec3 result = ambient + diffuse + specular;
    fragColor = vec4(result, 1.0f);
}
