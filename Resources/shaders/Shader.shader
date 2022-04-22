#vertex shader
#version 330 core

layout(location = 0) in vec2 bufferPositions;
layout(location = 1) in vec2 bufferTexCoords;
layout(location = 2) in float bufferTexIndex;

uniform mat4 viewProjection;
uniform mat4 MVP;

out vec2 texCoords;
out float texIndex;

void main()
{
	gl_Position = viewProjection * vec4(bufferPositions, 0.0f, 1.0f);
	texCoords = bufferTexCoords;
	texIndex = bufferTexIndex;
}

#fragment shader
#version 330 core

out vec4 newColor;
in vec2 texCoords;
in float texIndex;

uniform sampler2D newTexture[5];

void main()
{
	newColor = texture(newTexture[int(texIndex)], texCoords);
} 