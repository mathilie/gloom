// Local headers
#include "program.hpp"
#include "gloom/gloom.hpp"
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <math.h>
#include <gloom/camera.hpp>
#include <OBJLoader.hpp>
#include <toolbox.hpp>
#include <mesh.hpp>

GLuint array;
GLuint buffer;
GLuint colorBuffer;
GLfloat transmatrix[] = {
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f
};
glm::vec3 cameraPosition = { 0.0f, 0.0f, -1.0f };
glm::vec2 cameraAngle = {0.0f,0.0f};

Gloom::Camera cam;
Mesh chessboard = generateChessboard(100, 100, 5, {0.0f,0.0f,0.0f,1.0f}, {1.0f,1.0f,1.0f,1.0f});


void task4() {
	static const GLfloat coords[] = {
		-1.0f, -1.0f, 0.5f,
		1.0f, -1.0f, 0.5f,
		0.0f , -0.2f , 0.5f,
		-0.7f, -1.0f, 0.0f,
		0.7f, -1.0f, 0.0f,
		0.0f , 0.4f , 0.0f,
		-0.4f, -1.0f, -0.5f,
		0.4f, -1.0f, -0.5f,
		-0.0f , 0.9f , -0.5f };
	static const GLfloat colors[]{
		1.0f, 0.0f, 0.0f, 0.5f,
		1.0f, 0.0f, 0.0f, 0.5f,
		1.0f, 0.0f, 0.0f, 0.5f,
		0.0f, 1.0f, 0.0f, 0.5f,
		0.0f, 1.0f, 0.0f, 0.5f,
		0.0f, 1.0f, 0.0f, 0.5f,
		0.0f, 0.0f, 1.0f, 0.5f,
		0.0f, 0.0f, 1.0f, 0.5f,
		0.0f, 0.0f, 1.0f, 0.5f
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

void drawTask4() {
	glm::mat4x4 persMatrix = glm::perspective(3.14f * 2 / 3, 1.0f, 0.1f, 0.0f);
	GLfloat translationMatrix[] = {
		1.0f,0.0f,0.0f,cameraPosition[0],
		0.0f,1.0f,0.0f,cameraPosition[1],
		0.0f,0.0f,1.0f,cameraPosition[2],
		0.0f,0.0f,0.0f,1.0f
	};
	GLfloat rotationMatrix[] = {
		cos(cameraAngle[0]),0.0f, sin(cameraAngle[0]),0.0f,
		0.0f,1.0f,0.0f,0.0f,
		-sin(cameraAngle[0]),0.0f,cos(cameraAngle[0]),0.0f,
		0.0f,0.0f,0.0f,1.0f
	};
	GLfloat rotationMatrix2[] = {
		1.0f,0.0f, 0.0f,0.0f,
		0.0f,cos(cameraAngle[1]),sin(cameraAngle[1]),0.0f,
		0.0f,-sin(cameraAngle[1]),cos(cameraAngle[1]),0.0f,
		0.0f,0.0f,0.0f,1.0f
	};
	glm::mat4x4 transMat = glm::make_mat4x4(translationMatrix);
	glm::mat4x4 rotMat = glm::make_mat4x4(rotationMatrix);
	glm::mat4x4 rotMat2 = glm::make_mat4x4(rotationMatrix2);
	glm::mat4x4 transformation = transMat*rotMat*rotMat2*transpose(persMatrix);
	glBindVertexArray(array);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glUniformMatrix4fv(2, 1, GL_FALSE, glm::value_ptr(transformation));
	glDrawArrays(GL_TRIANGLES, 0, 9);
}
void initTask() {
	task4();
}

void drawTask() {
	drawTask4();
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
	initTask();

	getTimeDeltaSeconds();
	//makeAndLoadVertexes(coords, 75, colors, 75);
    // Rendering Loop
    while (!glfwWindowShouldClose(window))
    {
		
        // Clear colour and depth buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw your scene here
		drawTask();
        // Handle other events
        glfwPollEvents();
        handleKeyboardInput(window);
		cam.updateCamera(getTimeDeltaSeconds());
        // Flip buffers
        glfwSwapBuffers(window);
		printGLError();
    }
}



void handleKeyboardInput(GLFWwindow* window)
{
    // Use escape key for terminating the GLFW window
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		cameraPosition[1] = cameraPosition[1]-0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		cameraPosition[1] = cameraPosition[1]+0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		cameraPosition[0] = cameraPosition[0]+cos(cameraAngle[0])*0.01f;
		cameraPosition[2] = cameraPosition[2]+sin(cameraAngle[0])*0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		cameraPosition[0] = cameraPosition[0]-cos(cameraAngle[0])*0.01f;
		cameraPosition[2] = cameraPosition[2]-sin(cameraAngle[0])*0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		cameraPosition[0] = cameraPosition[0]-sin(cameraAngle[0])*0.01f;
		cameraPosition[2] = cameraPosition[2]+cos(cameraAngle[0])*0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		cameraPosition[0] = cameraPosition[0]+sin(cameraAngle[0])*0.01f;
		cameraPosition[2] = cameraPosition[2]-cos(cameraAngle[0])*0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		cameraAngle[1] = cameraAngle[1]-0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		cameraAngle[1] = cameraAngle[1]+0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		cameraAngle[0] = cameraAngle[0]-0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		cameraAngle[0] = cameraAngle[0]+0.01f;
	}
}
