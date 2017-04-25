#version 330

out vec4 color;

in vec2 texCoords;

void main()
{	
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * vec3(1.0f, 1.0f, 1.0f);

	vec3 objectColor = vec3(0.004f, 0.65f,0.067f);
    vec3 result = objectColor;
    

	color = vec4(result, 1.0f);
}

