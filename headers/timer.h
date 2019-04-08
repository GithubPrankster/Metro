struct deltaTimer {
	double deltaTime = 0.0f, lastFrame = 0.0f;
	void calculateDelta(double currentFrame) {
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
	}
};
