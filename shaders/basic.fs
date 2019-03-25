#version 330 core
out vec4 FragColor;

in vec3 fragPos;  
in vec3 normal;  
in vec2 texCoord;
in vec3 viewPos;

uniform sampler2D diffuse;
uniform sampler2D specularMap;

uniform int lightNum;
uniform vec3 lightPos[16];
uniform vec3 lightColor[16];
uniform float lightIntensity[16];

uniform vec3 tint;
uniform float shininess;

vec3 lightCalculation(vec3 lightPos, vec3 lightDir, vec3 lightColor, float lightIntensity,vec3 normalThing){
	//Diffuse shade
	float diff = max(dot(normalThing, lightDir), 0.0);
	vec3 diffuse = diff * lightColor * lightIntensity;
	
	//Specular shade
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 halfwayDir = normalize(lightDir + viewDir); 
	float spec = pow(max(dot(normalThing, halfwayDir), 0.0), shininess);
	vec3 specular = lightColor * spec * vec3(texture(specularMap, texCoord));
	
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

void main(){           
	
	vec3 color = texture(diffuse, texCoord).rgb;
	vec3 normalFrag = normalize(normal);
	
	vec3 result;
	for(int i = 0; i < lightNum; i++){
		vec3 lightDir = normalize(lightPos[i] - fragPos);
		result += lightCalculation(lightPos[i], lightDir, lightColor[i], lightIntensity[i],normalFrag);
	}
	
	// ambient
	vec3 ambient = 0.4 * color;
	FragColor = vec4(tint, 1.0) * vec4(result + ambient, 1.0);
    
}