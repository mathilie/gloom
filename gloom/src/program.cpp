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
#include "sceneGraph.hpp"

GLuint array[7];
GLuint buffer[7];
GLuint colorBuffer[7];

Gloom::Camera cam(glm::vec3(1.0f, 1.0f, 10.0f), 5.0f, 0.005f);
Mesh chessboard = generateChessboard(10, 10, 8, {0.0f,0.0f,0.0f,1.0f}, {1.0f,1.0f,1.0f,1.0f});

SceneNode* SteveNode = createSceneNode();
SceneNode* chessNode = createSceneNode();
MinecraftCharacter Steve = loadMinecraftCharacterModel("../gloom/res/steve.obj");

/* her er en ide til hvordan det kan løses
void addChildren(Mesh data) { //omtrent noe sånn som dette vi må implementere, meget mulig det kan gjøres i hovedloopen med noen if/else løsninger. vi må instantiere hver node med koordinater. Deretter kan vi legge dem som barn 
	for (size_t i = 0; i < length; i++)
	{

		SceneNode* child = createSceneNode(float3 position, float3 rotation, float3 referencePoint, int VAOID, int VAOIC); // dette er ikke lov tror jeg
		addChild(SteveNode, child);
	}
	
}
*/

/* lagt til fra handoutsnippet i oppgavetekst
void visitSceneNode(SceneNode* node, glm::mat4 transformationThusFar) {
	// Do transformations here
	// Do rendering here
	for (SceneNode* child : node->children) {
		visitSceneNode(child, combinedTransformation);
	}
}
*/

void task(Mesh data[7]) {
	glGenVertexArrays(7, &array[0]);
	glGenBuffers(7, &colorBuffer[0]);
	glGenBuffers(7, &buffer[0]);
	for (short i = 0; i < 7; i++) {
		//legge til scenenodes til foreldrene her
		
		glBindVertexArray(array[i]);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, buffer[i]);
		glBufferData(GL_ARRAY_BUFFER, (12 + sizeof(GLfloat))*data[i].vertices.size(), &data[i].vertices[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, colorBuffer[i]);
		glBufferData(GL_ARRAY_BUFFER, (12 + sizeof(GLfloat))*data[i].colours.size(), &data[i].colours[0], GL_STATIC_DRAW);
	}
}

void drawTask() {
	glm::mat4x4 persMatrix = glm::perspective(3.14f * 2 / 3, 1.0f, 0.1f, 0.0f);
	glm::mat4x4 transformation = persMatrix*cam.getViewMatrix();
	for (short i = 0; i < 7; i++) {
		glBindVertexArray(array[i]);
		glBindBuffer(GL_ARRAY_BUFFER, buffer[i]);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
		glBindBuffer(GL_ARRAY_BUFFER, colorBuffer[i]);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);
		glUniformMatrix4fv(2, 1, GL_FALSE, glm::value_ptr(transformation));
		glDrawArrays(GL_TRIANGLE_FAN, 0, 400);
	}

}
void initTask() {
	Mesh data[7] = {
		Steve.torso,
		Steve.leftArm,
		Steve.rightArm,
		Steve.head,
		Steve.rightLeg,
		Steve.leftLeg,
		chessboard
	};
	task(data);
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
    //glEnable(GL_CULL_FACE);
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
