#pragma once
#include "meshHandler.h"
#include "textureHandler.h"
#include "shaderLoader.h"
#include "camera.h"

struct Object {
	Mesh mesh;
	std::vector<Texture> textures;
	Shader *usedShader;
	glm::vec3 tint = glm::vec3(1.0f);
	float shininess = 4.0;
	Object(const char* meshFile, Texture initialTex, Shader* shade) : usedShader(shade){
		mesh = Mesh(meshFile);
		textures.push_back(initialTex);
	}
	void addTexture(Texture latestTex) {
		textures.push_back(latestTex);
	}
};

struct Light {
	glm::vec3 position;
	glm::vec3 color;
	float intensity;
	Mesh worldRepresent;
	Shader* lightShader;
	Light(glm::vec3 pos, glm::vec3 col, float intense, Mesh rep, Shader* shader) : position(pos), color(col), intensity(intense), worldRepresent(rep), lightShader(shader) {}
};

struct Scene {
	std::vector<Object> objects;
	std::vector<Light> lights;

	void addObject(Object obj) {
		objects.push_back(obj);
	}
	void addLight(Light light) {
		lights.push_back(light);
	}
	void render(Camera cam) {
		for (auto obj : objects) {
			obj.usedShader->use();
			obj.usedShader->setMat4("view", cam.view);
			obj.usedShader->setMat4("proj", cam.proj);
			obj.usedShader->setVec3("camPos", cam.position);

			obj.usedShader->setMat4("model", obj.mesh.mat);
			obj.usedShader->setVec3("tint", obj.tint);
			obj.usedShader->setFloat("shininess", obj.shininess);

			int textureIteration = 0;
			for (auto tex : obj.textures) {
				textureBind(tex.textureId, textureIteration);
				textureIteration++;
			}

			obj.usedShader->setInt("lightNum", lights.size());
			for (int i = 0; i < lights.size(); i++) {
				obj.usedShader->setVec3("lightPos[" + std::to_string(i) + "]", lights[i].position);
				obj.usedShader->setVec3("lightColor[" + std::to_string(i) + "]", lights[i].color);
				obj.usedShader->setFloat("lightIntensity[" + std::to_string(i) + "]", lights[i].intensity);
			}

			obj.mesh.render();
		}
		for (auto light : lights) {
			light.lightShader->use();
			light.lightShader->setMat4("proj", cam.proj);
			light.lightShader->setMat4("view", cam.view);
			light.lightShader->setMat4("model", light.worldRepresent.mat * glm::translate(light.position));

			light.lightShader->setVec3("tint", light.color);
			light.lightShader->setFloat("tintIntensiveness", light.intensity);

			light.worldRepresent.render();
		}
	}
	void terminate() {
		for (auto obj : objects) {
			for (auto tex : obj.textures) {
				tex.terminator();
			}
			obj.mesh.terminator();
		}
		for (auto light : lights) {
			light.worldRepresent.terminator();
		}
	}
};
