#version 330 core
out vec4 FragColor;

in vec2 texCoord;
in vec3 normal;
in vec3 fragPos;
in vec3 viewPos;

uniform samplerCube skybox;
uniform sampler2D reflectionMap;
uniform vec3 tint;

uniform int lightNum;
uniform vec3 lightPos[16];
uniform vec3 lightColor[16];
uniform float lightIntensity[16];

vec3 lightCalculation(vec3 lightPos, vec3 lightDir, vec3 lightColor, float lightIntensity,vec3 normalThing){
	//Diffuse shade
	float diff = max(dot(normalThing, lightDir), 0.0);
	vec3 diffuse = diff * lightColor * lightIntensity;
	
	//Specular shade
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 halfwayDir = normalize(lightDir + viewDir); 
	float spec = pow(max(dot(normalThing, halfwayDir), 0.0), 32.0);
	vec3 specular = lightColor * spec;
	
	//Attenuation calculations...
	float distance    = length(lightPos - fragPos);
	float attenuation = 1.0 / (1.0f + 0.09f * distance + 0.032f * (distance * distance));   
	
	//Multiply everything by it. So light actually behaves like uh, light.
	diffuse  *= attenuation;
	specular *= attenuation; 
	
	//Oh right, return result.
	vec3 result = diffuse + specular;
	return result;
}

void main() {             
    vec3 I = normalize(fragPos - viewPos);
    vec3 R = normalize(reflect(I, normalize(normal)));
	vec3 cubeTotal = texture(skybox, R).rgb * tint;
	vec3 result;
	for(int i = 0; i < lightNum; i++){
		vec3 lightDir = normalize(lightPos[i] - fragPos);
		result += lightCalculation(lightPos[i], lightDir, lightColor[i], lightIntensity[i],normalize(normal));
	}
    FragColor = vec4(cubeTotal + result, 1.0);
}