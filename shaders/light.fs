#version 330 core
out vec4 FragColor;

uniform vec3 tint;
uniform float tintIntensiveness = 0.0f;

void main(){           

	FragColor = vec4(tint + tintIntensiveness, 1.0);
	
}