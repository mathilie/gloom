#version 430 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec4 vertexColour;
layout(location = 1) out vec4 outVertexColour;
layout(location = 3) mat4 transformationMatrix
void main()
{
	outVertexColour = vertexColour;
    gl_Position = vec4(position, 1.0f);
}