#version 330

uniform sampler2D ShadowMap, RotationTexture;

uniform vec3 LightDirection;
uniform float Scale, Radius;

vec3 color;

out vec4 outputColor;

in vec4 texCoord0;

void main()
{	

	vec3 ShadowTexCoord = texCoord0.xyz / texCoord0.w;

	ShadowTexCoord.z -= 0.005;

	vec4 ScaleRotationVector = (texture2D(RotationTexture, gl_FragCoord.st * Scale) * 2.0 - 1.0) * Radius;

	mat2x2 ScaleRotationMatrix = mat2x2(ScaleRotationVector.xy, ScaleRotationVector.zw);

	float Shadow = 0.0;

	for(int i = 0; i < 16; i++)
	{
		float Depth = texture2D(ShadowMap, ShadowTexCoord.st + ScaleRotationMatrix * vec2(0.0, 0.0)).r;

		if(ShadowTexCoord.z < Depth)
		{
			Shadow += 1.0;
		}
	}

	Shadow /= 16.0;

	vec3 Normal = normalize(vec3(1.0f));

	float NdotLD = max(0.0, dot(Normal, LightDirection));

	color = vec3(0.004f, 0.65f,0.067f);

	outputColor = vec4(color * (0.25 + 0.75 * NdotLD * Shadow), 1.0);

	//outputColor = vec4(0.004f, 0.65f,0.067f, 1.0f);
	
}

