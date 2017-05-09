#version 330

layout(location = 0) in vec3 verts_ms;
layout(location = 1) in vec3 norm_ms;
layout(location = 2) in vec2 uv_ms;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

out vec2 texCoords;
out vec3 Normal;  
out vec3 FragPos; 

void main()
{
	gl_Position = Projection * View * Model * vec4(verts_ms, 1.0f);
	texCoords = uv_ms;	

	Normal = norm_ms;

	FragPos = vec3(Model * vec4(verts_ms, 1.0f));
}
