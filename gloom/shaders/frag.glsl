#version 430 core
layout(location = 1)in vec4 outVertexColour;
out vec4 color;
void main()
{
	color = outVertexColour;
}