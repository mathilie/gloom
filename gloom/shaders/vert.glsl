#version 430 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vertexColour;
layout(location = 1) out vec4 outVertexColour;
void main()
{
	outVertexColour = vec4(vertexColour, 1.0f);
    gl_Position = vec4(position, 1.0f);
}