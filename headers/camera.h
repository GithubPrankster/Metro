#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/constants.hpp>

extern double lastX, lastY;
extern bool firstMouse;
extern float yaw;
extern float pitch;

extern glm::vec3 cameraFront;
extern glm::vec3 cameraUp;

void setStartCursorPos(int scrWidth, int scrHeight);

struct Camera {
	glm::vec3 position;
	glm::mat4 proj, view;
	//float constY;
	Camera();
	Camera(float fov, int scrWidth, int scrHeight);
	void calculateView();
};

#endif