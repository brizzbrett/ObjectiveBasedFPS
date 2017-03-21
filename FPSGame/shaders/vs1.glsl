#version 330

layout(location = 0) in vec3 verts_ms;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

uniform mat4 ShadowMatrix;

uniform mat4 LightProjection;
uniform mat4 LightView;

out vec4 texCoord0;

void main()
{
	texCoord0 = ShadowMatrix * vec4(verts_ms, 1.0f);
	gl_Position = Projection * View * Model * vec4(verts_ms, 1.0f);
}
