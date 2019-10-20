#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 lightColor; 
uniform vec3 objectColor;
uniform vec3 lightPos;

out vec3 color;

void main()
{
    vec4 vertexViewPos = view * model * vec4(aPos, 1.0f);
    vec3 vertexPos = vec3(vertexViewPos);
	gl_Position = projection * vertexViewPos;
    vec3 normal = mat3(transpose(inverse(view * model))) * aNormal;

    float ambientStength = 0.2f;
    vec3 ambient = ambientStength * lightColor;

    float diffuseStrength = 0.3f;
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - vertexPos);
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = diffuseStrength * diff * lightColor;

    float specularStrength = 0.7f;
    vec3 viewDir = normalize(-vertexPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 16.0f);
    vec3 specular = specularStrength * spec * lightColor;

    color = (ambient + diffuse + specular) * objectColor;
}
