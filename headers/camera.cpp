#include "camera.h"

double lastX, lastY;
bool firstMouse = true;
float yaw = -90.0f;
float pitch = 0.0f;

glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

void setStartCursorPos(int scrWidth, int scrHeight) {
	lastX = scrWidth / 2.0, lastY = scrHeight / 2.0;
}

Camera::Camera() {
}

Camera::Camera(float fov, int scrWidth, int scrHeight) {
	proj = glm::perspective(fov, (float)scrWidth / (float)scrHeight, 0.1f, 1000.0f);

}

void Camera::calculateView() {
	view = glm::lookAt(position, position + cameraFront, cameraUp);
}
