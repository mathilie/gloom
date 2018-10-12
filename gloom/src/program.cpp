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

SceneNode* root = createSceneNode();
MinecraftCharacter Steve = loadMinecraftCharacterModel("../gloom/res/steve.obj");


 //lagt til fra handoutsnippet i oppgavetekst
void visitSceneNode(SceneNode* node, glm::mat4 transformationThusFar) {
	glm::mat4 combinedTransformation = (*node).currentTransformationMatrix*transformationThusFar;

	// Do transformations here

	//legges her fordi det ikke gjøres noe rekursivt i  scenenodebesøket, her blir scenenoden lagt til i array
	int index = (*node).vertexArrayObjectID;
	// Do rendering here
	if (index > 0 ) {
		glm::mat4x4 persMatrix = glm::perspective(3.14f * 2 / 3, 1.0f, 0.1f, 0.0f);
		glm::mat4x4 viewMatrix = cam.getViewMatrix();
		glBindVertexArray(index);
		glBindBuffer(GL_ARRAY_BUFFER, buffer[index-1]);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
		glBindBuffer(GL_ARRAY_BUFFER, colorBuffer[index-1]);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);
		glUniformMatrix4fv(2, 1, GL_FALSE, glm::value_ptr(persMatrix*viewMatrix));
		glDrawArrays(GL_TRIANGLE_FAN, 0, 400);
	}
	for (SceneNode* child : node->children) {
		visitSceneNode(child, combinedTransformation);
	}

}

void updatePositions() {

}

void buildSceneGraph() {
	
	SceneNode* bodyRoot = createSceneNode();
	(*bodyRoot).referencePoint = float3(0.0f, 0.0f, 0.0f);
	
	SceneNode* torso = createSceneNode();
	(*torso).referencePoint = float3(0.0f, 12.0f, 0.0f);
	(*torso).vertexArrayObjectID = array[0];
	glBindVertexArray(array[0]);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, (12 + sizeof(GLfloat))*Steve.torso.vertices.size(), &Steve.torso.vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer[0]);
	glBufferData(GL_ARRAY_BUFFER, (12 + sizeof(GLfloat))*Steve.torso.colours.size(), &Steve.torso.colours[0], GL_STATIC_DRAW);
	
	SceneNode* leftLeg = createSceneNode();
	(*leftLeg).referencePoint = float3(-2.0f, 0.0f, 0.0f);
	(*leftLeg).vertexArrayObjectID = array[1];
	glBindVertexArray(array[1]);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
	glBufferData(GL_ARRAY_BUFFER, (12 + sizeof(GLfloat))*Steve.leftLeg.vertices.size(), &Steve.leftLeg.vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer[1]);
	glBufferData(GL_ARRAY_BUFFER, (12 + sizeof(GLfloat))*Steve.leftLeg.colours.size(), &Steve.leftLeg.colours[0], GL_STATIC_DRAW);

	SceneNode* rightLeg = createSceneNode();
	(*rightLeg).referencePoint = float3(2.0f, 0.0f, 0.0f);
	(*rightLeg).vertexArrayObjectID = array[2];
	glBindVertexArray(array[2]);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[2]);
	glBufferData(GL_ARRAY_BUFFER, (12 + sizeof(GLfloat))*Steve.rightLeg.vertices.size(), &Steve.rightLeg.vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer[2]);
	glBufferData(GL_ARRAY_BUFFER, (12 + sizeof(GLfloat))*Steve.rightLeg.colours.size(), &Steve.rightLeg.colours[0], GL_STATIC_DRAW);

	SceneNode* leftArm = createSceneNode();
	(*leftArm).referencePoint = float3(-4.0f, 12.0f, 0.0f);
	(*leftArm).vertexArrayObjectID = array[3];
	glBindVertexArray(array[3]);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[3]);
	glBufferData(GL_ARRAY_BUFFER, (12 + sizeof(GLfloat))*Steve.leftArm.vertices.size(), &Steve.leftArm.vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer[3]);
	glBufferData(GL_ARRAY_BUFFER, (12 + sizeof(GLfloat))*Steve.leftArm.colours.size(), &Steve.leftArm.colours[0], GL_STATIC_DRAW);

	SceneNode* rightArm = createSceneNode();
	(*rightArm).referencePoint = float3(4.0f, 12.0f, 0.0f);
	(*rightArm).vertexArrayObjectID = array[4];
	glBindVertexArray(array[4]);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[4]);
	glBufferData(GL_ARRAY_BUFFER, (12 + sizeof(GLfloat))*Steve.rightArm.vertices.size(), &Steve.rightArm.vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer[4]);
	glBufferData(GL_ARRAY_BUFFER, (12 + sizeof(GLfloat))*Steve.rightArm.colours.size(), &Steve.rightArm.colours[0], GL_STATIC_DRAW);

	SceneNode* head = createSceneNode();
	(*head).referencePoint = float3(0.0f, 12.0f, 0.0f);
	(*head).vertexArrayObjectID = array[5];
	glBindVertexArray(array[5]);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[5]);
	glBufferData(GL_ARRAY_BUFFER, (12 + sizeof(GLfloat))*Steve.head.vertices.size(), &Steve.head.vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer[5]);
	glBufferData(GL_ARRAY_BUFFER, (12 + sizeof(GLfloat))*Steve.head.colours.size(), &Steve.head.colours[0], GL_STATIC_DRAW);

	SceneNode* board = createSceneNode();
	(*board).vertexArrayObjectID = array[6];
	glBindVertexArray(array[6]);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[6]);
	glBufferData(GL_ARRAY_BUFFER, (12 + sizeof(GLfloat))*chessboard.vertices.size(), &chessboard.vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer[6]);
	glBufferData(GL_ARRAY_BUFFER, (12 + sizeof(GLfloat))*chessboard.vertices.size(), &chessboard.colours[0], GL_STATIC_DRAW);

	addChild(torso, head);
	addChild(torso, leftLeg);
	addChild(torso, leftArm);
	addChild(torso, rightArm);
	addChild(torso, rightLeg);
	addChild(bodyRoot, torso);
	addChild(root, bodyRoot);
	addChild(root, board);
	
}

void drawTask() {
	visitSceneNode(root, cam.getViewMatrix());
}
void initTask() {
	glGenVertexArrays(7, &array[0]);
	glGenBuffers(7, &colorBuffer[0]);
	glGenBuffers(7, &buffer[0]);
	buildSceneGraph();
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
