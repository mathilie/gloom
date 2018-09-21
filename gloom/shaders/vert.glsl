#version 430 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec4 vertexColour;
layout(location = 2) uniform mat4 imat;
layout(location = 1) out vec4 outVertexColour;
void main()
{
	outVertexColour = vertexColour;
	vec4 position4 = vec4(position, 1.0f);
    gl_Position = transpose(imat)*position4;
}