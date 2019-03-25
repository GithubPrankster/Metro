struct deltaTimer {
	float deltaTime = 0.0f, lastFrame = 0.0f;
	void calculateDelta(float currentFrame) {
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
	}
};
