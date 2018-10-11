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

Gloom::Camera cam(glm::vec3(0.0f, 0.0f, 2.0f), 5.0f, 0.005f);
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
	glm::mat4x4 transformation = persMatrix*cam.getViewMatrix();
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

void handleInputs(GLFWwindow* window) {
	handleKeyboardInput(window);
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	cam.handleCursorPosInput(xpos, ypos);
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


	//makeAndLoadVertexes(coords, 75, colors, 75);
    // Rendering Loop
	double delta=getTimeDeltaSeconds();
    while (!glfwWindowShouldClose(window))
    {
        // Clear colour and depth buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		delta = getTimeDeltaSeconds();
        // Draw your scene here
		drawTask();
        // Handle other events
        glfwPollEvents();
		handleInputs(window);
		cam.updateCamera(delta);
		// Flip buffers
        glfwSwapBuffers(window);
		printGLError();
    }
}



void handleKeyboardInput(GLFWwindow* window)
{
    // Use escape key for terminating the GLFW window
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) cam.handleKeyboardInputs(GLFW_KEY_A, GLFW_PRESS);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) cam.handleKeyboardInputs(GLFW_KEY_D, GLFW_PRESS);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) cam.handleKeyboardInputs(GLFW_KEY_S, GLFW_PRESS);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) cam.handleKeyboardInputs(GLFW_KEY_W, GLFW_PRESS);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) cam.handleKeyboardInputs(GLFW_KEY_E, GLFW_PRESS);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) cam.handleKeyboardInputs(GLFW_KEY_Q, GLFW_PRESS);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE) cam.handleKeyboardInputs(GLFW_KEY_A, GLFW_RELEASE);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE) cam.handleKeyboardInputs(GLFW_KEY_D, GLFW_RELEASE);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE) cam.handleKeyboardInputs(GLFW_KEY_S, GLFW_RELEASE);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE) cam.handleKeyboardInputs(GLFW_KEY_W, GLFW_RELEASE);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_RELEASE) cam.handleKeyboardInputs(GLFW_KEY_E, GLFW_RELEASE);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_RELEASE) cam.handleKeyboardInputs(GLFW_KEY_Q, GLFW_RELEASE);
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) cam.handleMouseButtonInputs(GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS);
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) cam.handleMouseButtonInputs(GLFW_MOUSE_BUTTON_LEFT, GLFW_RELEASE);

}
