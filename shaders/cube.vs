#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec2 texCoord;
out vec3 normal;
out vec3 fragPos;
out vec3 viewPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform vec3 camPos;

void main()
{
	fragPos = vec3(model * vec4(aPos, 1.0));
    normal = mat3(transpose(inverse(mat3(model)))) * aNormal;  
    texCoord = aTexCoord;

	vec4 finalPos = proj * view * vec4(fragPos, 1.0);
	
	viewPos = camPos;
	
    gl_Position = finalPos;
}