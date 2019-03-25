#include <iostream>
#include <vector>

#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/constants.hpp>

#include "headers/windowManager.h"

const int WIDTH = 1280, HEIGHT = 720;
const int glfwSamples = 4;

int main() {
	glfwInit();
	windowManager mainWindow(WIDTH, HEIGHT, glfwSamples, "Metro Renderer");

	Camera mainCam(glm::radians(45.0f), WIDTH, HEIGHT);
	mainCam.position = glm::vec3(0.0f, 1.0f, 6.0f);
	//mainCam.constY = mainCam.position.y;

	Shader basicShader("shaders/basic.vs", "shaders/basic.fs");
	Shader basicLight("shaders/light.vs", "shaders/light.fs");

	//Basic textures
	Texture planks("textures/woodplank.png", GL_RGBA, GL_NEAREST);
	Texture floorTex("textures/woodfloor.png", GL_RGBA, GL_NEAREST);
	Texture bricks("textures/brickwaller.png", GL_RGBA, GL_NEAREST);
	Texture wall("textures/wallwood.png", GL_RGBA, GL_NEAREST);
	//Texture bricks("textures/brickwaller.png", GL_RGBA, GL_NEAREST);

	//Light meshes (can be changed for interesting results!)
	Mesh lightObj("models/areaLight.obj");
	Mesh light("models/light.obj");

	//Box
	mainWindow.mainScene.addObject(Object("models/box.obj", planks, &basicShader));
	mainWindow.mainScene.objects[0].addTexture(Texture("textures/woodspec.png", GL_RGBA, GL_NEAREST));

	//Floor
	mainWindow.mainScene.addObject(Object("models/floor.obj", floorTex, &basicShader));
	mainWindow.mainScene.objects[1].addTexture(Texture("textures/woodfloorheight.png", GL_RGBA, GL_NEAREST));

	//Ceiling
	mainWindow.mainScene.addObject(Object("models/ceiling.obj", floorTex, &basicShader));
	mainWindow.mainScene.objects[1].addTexture(Texture("textures/woodfloorheight.png", GL_RGBA, GL_NEAREST));

	//Pillars
	mainWindow.mainScene.addObject(Object("models/pillars.obj", bricks, &basicShader));
	mainWindow.mainScene.objects[2].addTexture(Texture("textures/brickspec.png", GL_RGBA, GL_NEAREST));

	//Room
	mainWindow.mainScene.addObject(Object("models/room.obj", wall, &basicShader));
	//Lights
	mainWindow.mainScene.addLight(Light(glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(0.4f, 0.5f, 0.2f), 0.4f, lightObj, &basicLight));

	mainWindow.mainScene.addLight(Light(glm::vec3(-3.0f, 3.0f, -3.0f), glm::vec3(0.2f, 0.2f, 0.5f), 0.6f, light, &basicLight));
	mainWindow.mainScene.addLight(Light(glm::vec3(2.0f, 0.5f, -4.0f), glm::vec3(0.2f, 0.2f, 0.5f), 0.6f, light, &basicLight));
	mainWindow.mainScene.addLight(Light(glm::vec3(3.0f), glm::vec3(0.2f, 0.2f, 0.5f), 0.6f, light, &basicLight));
	mainWindow.mainScene.addLight(Light(glm::vec3(-2.0f, 0.5f, 4.0f), glm::vec3(0.2f, 0.2f, 0.5f), 0.6f, light, &basicLight));

	mainWindow.mainLoop(mainCam);
	glfwTerminate();

	return EXIT_SUCCESS;
}

