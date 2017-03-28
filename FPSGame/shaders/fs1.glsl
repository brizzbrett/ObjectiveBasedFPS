#version 330

out vec4 outputColor;
out vec4 outputTexture;

in vec2 texCoords;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;
uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;

void main()
{	
	outputColor = vec4(0.004f, 0.65f,0.067f, 1.0f);
	outputTexture = vec4(texture(texture_diffuse1,texCoords));
}

