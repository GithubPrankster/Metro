double lastX, lastY;
bool firstMouse = true;
float yaw = -90.0f;	
float pitch = 0.0f;

glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

void setStartCursorPos(int scrWidth, int scrHeight) {
	lastX = scrWidth / 2.0, lastY = scrHeight / 2.0;
}

struct Camera {
	glm::vec3 position;
	glm::mat4 proj, view;
	//float constY;
	Camera(float fov, int scrWidth, int scrHeight) {
		proj = glm::perspective(fov, (float)scrWidth / (float)scrHeight, 0.1f, 1000.0f);
		
	}

	void calculateView() {
		view = glm::lookAt(position, position + cameraFront, cameraUp);
	}
};