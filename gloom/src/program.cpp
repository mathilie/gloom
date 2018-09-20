// Local headers
#include "program.hpp"
#include "gloom/gloom.hpp"
GLuint array;
GLuint buffer;

GLfloat* makeAndLoadVertexes(GLfloat coords[], size_t lengthCoords, GLfloat colors[], size_t colorsLength);

void runProgram(GLFWwindow* window)
{
    // Enable depth (Z) buffer (accept "closest" fragment)
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Configure miscellaneous OpenGL settings
    glEnable(GL_CULL_FACE);

    // Set default colour after clearing the colour buffer
    glClearColor(0.3f, 0.5f, 0.8f, 1.0f);


    // Set up your scene here (create Vertex Array Objects, etc.)
	
	static GLfloat coords[] = { 
		-1.0f, -0.9f, 0.0f,
		-0.8f, -0.9f, 0.0f,
		-0.9f , 0.9f , 0.0f,
		-0.8f, -0.9f, 0.0f,
		-0.6f, -0.9f, 0.0f,
		-0.7f , 0.9f , 0.0f,
		-0.6f, -0.9f, 0.0f,
		-0.4f, -0.9f, 0.0f,
		-0.5f , 0.9f , 0.0f,
		-0.4f, -0.9f, 0.0f,
		-0.2f, -0.9f, 0.0f,
		-0.3f , 0.9f , 0.0f,
		-0.2f, -0.9f, 0.0f,
		0.0f, -0.9f, 0.0f,
		-0.1f , 0.9f , 0.0f };
	static GLfloat colors[75]{
		1.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f,
		0.6f, 0.4f, 0.2f, 1.0f,
		0.4f, 0.8f, 0.1f, 1.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
		0.2f, 0.2f, 0.2f, 1.0f,
		0.8f, 0.8f, 0.8f, 1.0f,
		0.1f, 0.5f, 0.7f, 1.0f,
		1.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f
	};
	

	GLfloat* dataarray = makeAndLoadVertexes(coords, 75, colors, 75);
    // Rendering Loop
    while (!glfwWindowShouldClose(window))
    {
        // Clear colour and depth buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw your scene here
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glVertexAttribPointer(0, 7, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glDrawArrays(GL_TRIANGLES,0,15);
		glDisableVertexAttribArray(0);
		

        // Handle other events
        glfwPollEvents();
        handleKeyboardInput(window);

        // Flip buffers
        glfwSwapBuffers(window);
		printGLError();
    }
}

GLfloat* makeAndLoadVertexes(GLfloat coords[], size_t lengthCoords, GLfloat colors[], size_t colorsLength) {
	GLfloat *dataarray = new GLfloat[lengthCoords + colorsLength];
	for (unsigned int i = 0; i <lengthCoords / 3; i++) {
		dataarray[i * 7] = coords[i * 3];
		dataarray[i * 7 + 1] = coords[i * 3 + 1];
		dataarray[i * 7 + 2] = coords[i * 3 + 2];
		dataarray[i * 7 + 3] = colors[i * 4];
		dataarray[i * 7 + 4] = colors[i * 4 + 1];
		dataarray[i * 7 + 5] = colors[i * 4 + 2];
		dataarray[i * 7 + 6] = colors[i * 4 + 3];
	}
	glGenVertexArrays(5, &array);
	glBindVertexArray(array);
	glGenBuffers(5, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(dataarray), dataarray, GL_STATIC_DRAW);
	delete[] dataarray;
	return dataarray;
}


void handleKeyboardInput(GLFWwindow* window)
{
    // Use escape key for terminating the GLFW window
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}
