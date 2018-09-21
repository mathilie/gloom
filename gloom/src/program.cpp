// Local headers
#include "program.hpp"
#include "gloom/gloom.hpp"
GLuint array;
GLuint buffer;
GLuint colorBuffer;
GLfloat identity[4];

void makeAndLoadVertexes(GLfloat coords[], size_t lengthCoords, GLfloat colors[], size_t colorsLength);


//TASK 1

void task1() {
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
		-0.1f , 0.9f , 0.0f };
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

	glGenBuffers(1, &colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
}

void drawTask1() {
	glBindVertexArray(array);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glDrawArrays(GL_TRIANGLES, 0, 15);
}


//TASK 2

void task2() {
	static const GLfloat coords[] = {
		-1.0f, -1.0f, -0.5f,
		1.0f, -1.0f, -0.5f,
		0.0f , -0.2f , -0.5f,
		-0.7f, -1.0f, 0.0f,
		0.7f, -1.0f, 0.0f,
		0.0f , 0.4f , 0.0f,
		-0.4f, -1.0f, 0.5f,
		0.4f, -1.0f, 0.5f,
		0.0f , 0.9f , 0.5f };
	static const GLfloat colors[]{
		1.0f, 0.0f, 0.0f, 0.3f,
		1.0f, 0.0f, 0.0f, 0.3f,
		1.0f, 0.0f, 0.0f, 0.3f,
		0.0f, 1.0f, 0.0f, 0.5f,
		0.0f, 1.0f, 0.0f, 0.5f,
		0.0f, 1.0f, 0.0f, 0.5f,
		0.0f, 0.0f, 1.0f, 0.8f,
		0.0f, 0.0f, 1.0f, 0.8f,
		0.0f, 0.0f, 1.0f, 0.8f
		};
	glGenVertexArrays(1, &array);
	glBindVertexArray(array);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(coords), coords, GL_STATIC_DRAW);

	glGenBuffers(1, &colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
}

void drawTask2() {
	glBindVertexArray(array);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glDrawArrays(GL_TRIANGLES, 6, 3);
	glDrawArrays(GL_TRIANGLES, 3, 3);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}


//Task 3
void task3() {
	static const GLfloat coords[] = {
		-1.0f, -1.0f, -0.5f,
		1.0f, -1.0f, -0.5f,
		0.0f , -0.2f , -0.5f,
		-0.7f, -1.0f, 0.0f,
		0.7f, -1.0f, 0.0f,
		0.0f , 0.4f , 0.0f,
		-0.4f, -1.0f, 0.5f,
		0.4f, -1.0f, 0.5f,
		0.0f , 0.9f , 0.5f };
	static const GLfloat colors[]{
		1.0f, 0.0f, 0.0f, 0.3f,
		1.0f, 0.0f, 0.0f, 0.3f,
		1.0f, 0.0f, 0.0f, 0.3f,
		0.0f, 1.0f, 0.0f, 0.5f,
		0.0f, 1.0f, 0.0f, 0.5f,
		0.0f, 1.0f, 0.0f, 0.5f,
		0.0f, 0.0f, 1.0f, 0.8f,
		0.0f, 0.0f, 1.0f, 0.8f,
		0.0f, 0.0f, 1.0f, 0.8f
	};

	identity[0] = { 1.0f, 0.0f, 0.0f, 0.0f };
	identity[1] = { 0.0f, 1.0f, 0.0f, 0.0f };
	identity[2] = { 0.0f, 0.0f, 1.0f, 0.0f };
	identity[3] = { 0.0f, 0.0f, 0.0f, 1.0f };

	glGenVertexArrays(1, &array);
	glBindVertexArray(array);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(coords), coords, GL_STATIC_DRAW);

	glGenBuffers(1, &colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
}

void drawTask3() {
	glBindVertexArray(array);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glUniform4fv(3, 1, indentity);
	glDrawArrays(GL_TRIANGLES, 6, 3);
	glDrawArrays(GL_TRIANGLES, 3, 3);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}


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
	task2();


	//makeAndLoadVertexes(coords, 75, colors, 75);
    // Rendering Loop
    while (!glfwWindowShouldClose(window))
    {
        // Clear colour and depth buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw your scene here
		drawTask2();
        // Handle other events
        glfwPollEvents();
        handleKeyboardInput(window);

        // Flip buffers
        glfwSwapBuffers(window);
		printGLError();
    }
}

void makeAndLoadVertexes(GLfloat* coords, size_t lengthCoords, GLfloat colors[], size_t colorsLength) {

}


void handleKeyboardInput(GLFWwindow* window)
{
    // Use escape key for terminating the GLFW window
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}
