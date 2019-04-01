#pragma once

#include "timer.h"
#include "scene.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void inputHandle(GLFWwindow* window, Camera* cam, float delta);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

class windowManager {
public:
	GLFWwindow* window;
	deltaTimer delta;
	Scene mainScene;
	int scrWidth, scrHeight, scrSamples;
	windowManager(int width, int height, int samples, const char* name) {
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		glfwWindowHint(GLFW_SAMPLES, samples);

		window = glfwCreateWindow(width, height, "Metro Renderer", NULL, NULL);
		if (window == NULL)
		{
			std::cout << "GLFW has decided to game end itself." << std::endl;
			glfwTerminate();
		}
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		glfwMakeContextCurrent(window);
		glfwSetCursorPosCallback(window, mouse_callback);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "GLAD could not be initialized!" << std::endl;
		}

		setStartCursorPos(width, height);
		glfwSetCursorPos(window, lastX, lastY);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glEnable(GL_MULTISAMPLE);
		glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

		scrWidth = width, scrHeight = height, scrSamples = samples;
	}
	void mainLoop(Camera cam) {
		while (!glfwWindowShouldClose(window)) {
			delta.calculateDelta(glfwGetTime());
			std::cout << delta.deltaTime << std::endl;
			inputHandle(window, &cam, delta.deltaTime);

			glClearColor(0.2f, 0.2f, 0.4f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			
			cam.calculateView();
			mainScene.render(cam);

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		mainScene.terminate();
	}
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void inputHandle(GLFWwindow* window, Camera* cam, float delta) {
	float velocity;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		velocity = 10.5f * delta;
	else
		velocity = 6.5f * delta;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	//cam->position.y = cam->constY;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		cam->position += velocity * cameraFront;
	}
		
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		cam->position -= velocity * cameraFront;
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		cam->position -= velocity * glm::normalize(glm::cross(cameraFront, cameraUp));
	}
		
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		cam->position += velocity * glm::normalize(glm::cross(cameraFront, cameraUp));
	}

	//cam->position.y = cam->constY;
		
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos){
	if (firstMouse)
	{
		lastX = xpos, lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX, yoffset = lastY - ypos;
	lastX = xpos, lastY = ypos;

	float sensitivity = 0.06;
	xoffset *= sensitivity, yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
}


