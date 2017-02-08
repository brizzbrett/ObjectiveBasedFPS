#version 400 core
layout(location = 0) in vec4 verts_ms;
layout(location = 1) in vec4 color;
smooth out vec4 theColor;

uniform mat4 mvp;

void main()
{
	gl_Position = mvp * verts_ms;
	theColor = color;
}
