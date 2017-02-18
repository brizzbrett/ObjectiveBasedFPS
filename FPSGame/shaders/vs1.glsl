#version 400

layout(location = 0) in vec3 verts_ms;
layout(location = 1) in vec3 color;

smooth out vec3 theColor;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main()
{
	gl_Position = Projection * View * Model * vec4(verts_ms, 1);
	theColor = color;
}
