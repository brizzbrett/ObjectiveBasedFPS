#version 330

out vec4 outputTexture;

in vec2 texCoords;

uniform sampler2D texture_diffuse1;

void main()
{	
	outputTexture = vec4(texture(texture_diffuse1,texCoords));
}

