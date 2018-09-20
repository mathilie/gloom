// Local headers
#include "program.hpp"
#include "gloom/gloom.hpp"
GLuint array;
GLuint buffer;

void makeAndLoadVertexes(GLfloat coords[], size_t lengthCoords, GLfloat colors[], size_t colorsLength);

void runProgram(GLFWwindow* window)
{
    // Enable depth (Z) buffer (accept "closest" fragment)
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Configure miscellaneous OpenGL settings
    glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Set default colour after clearing the colour buffer
    glClearColor(0.3f, 0.5f, 0.8f, 1.0f);


    // Set up your scene here (create Vertex Array Objects, etc.)
	
	static const GLfloat coords[] = { 
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
		-0.1f , 0.9f , 0.0f};
	static const GLfloat colors[]{
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f,
		0.6f, 0.4f, 0.2f,
		0.4f, 0.8f, 0.1f,
		0.0f, 0.0f, 0.0f,
		0.2f, 0.2f, 0.2f,
		0.8f, 0.8f, 0.8f,
		0.1f, 0.5f, 0.7f,
		1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f
	};
	glGenVertexArrays(1, &array);
	glBindVertexArray(array);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(coords), coords, GL_STATIC_DRAW);
	
	GLuint colorBuffer;
	glGenBuffers(1, &colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

	//makeAndLoadVertexes(coords, 75, colors, 75);
    // Rendering Loop
    while (!glfwWindowShouldClose(window))
    {
        // Clear colour and depth buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw your scene here
		glBindVertexArray(array);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glDrawArrays(GL_TRIANGLES, 0, 15);
        // Handle other events
        glfwPollEvents();
        handleKeyboardInput(window);

        // Flip buffers
        glfwSwapBuffers(window);
		printGLError();
    }
}

void makeAndLoadVertexes(GLfloat* coords, size_t lengthCoords, GLfloat colors[], size_t colorsLength) {
	/*GLfloat *dataarray = new GLfloat[lengthCoords + colorsLength];
	for (unsigned int i = 0; i <lengthCoords / 3; i++) {
		dataarray[i * 7] = coords[i * 3];
		dataarray[i * 7 + 1] = coords[i * 3 + 1];
		dataarray[i * 7 + 2] = coords[i * 3 + 2];
		dataarray[i * 7 + 3] = colors[i * 4];
		dataarray[i * 7 + 4] = colors[i * 4 + 1];
		dataarray[i * 7 + 5] = colors[i * 4 + 2];
		dataarray[i * 7 + 6] = colors[i * 4 + 3];
	}*/

	//delete[] dataarray;
	//return dataarray;
}


void handleKeyboardInput(GLFWwindow* window)
{
    // Use escape key for terminating the GLFW window
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}
