#version 330 core

in vec3 ourColor;
in vec2 texCoord; 

out vec4 fragColor;

uniform sampler2D texture1; 
uniform sampler2D texture2; 
uniform float alpha;

void main()
{
    fragColor = mix(texture(texture1, texCoord),
                    texture(texture2, texCoord), alpha);
}
