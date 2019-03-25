#ifndef MESHHANDLER_H
#define MESHHANDLER_H

#include <glad/glad.h>
#include <vector>
#include <string>
#include <stdexcept>
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#include "vertex.h"

class Mesh {
public:
	glm::mat4 mat;
	Mesh(const char* path) {
		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;
		std::string err;

		if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path)) {
			throw std::runtime_error(err);
		}
		for (const auto& shape : shapes) {
			for (size_t index = 0; index < shape.mesh.indices.size(); index+= 3) {
				vertex vert = {};
				vertex vert1 = {};
				vertex vert2 = {};

				vert.pos = {
					glm::vec3(attrib.vertices[3 * shape.mesh.indices[index].vertex_index + 0],
					attrib.vertices[3 * shape.mesh.indices[index].vertex_index + 1],
					attrib.vertices[3 * shape.mesh.indices[index].vertex_index + 2])
				};

				vert.normal = {
					glm::vec3(attrib.normals[3 * shape.mesh.indices[index].normal_index + 0],
					attrib.normals[3 * shape.mesh.indices[index].normal_index + 1],
					attrib.normals[3 * shape.mesh.indices[index].normal_index + 2])
				};

				vert.tex = {
					glm::vec2(attrib.texcoords[2 * shape.mesh.indices[index].texcoord_index + 0],
					attrib.texcoords[2 * shape.mesh.indices[index].texcoord_index + 1])
				};


				vert1.pos = {
					glm::vec3(attrib.vertices[3 * shape.mesh.indices[index + 1].vertex_index + 0],
					attrib.vertices[3 * shape.mesh.indices[index + 1].vertex_index + 1],
					attrib.vertices[3 * shape.mesh.indices[index + 1].vertex_index + 2])
				};

				vert1.normal = {
					glm::vec3(attrib.normals[3 * shape.mesh.indices[index + 1].normal_index + 0],
					attrib.normals[3 * shape.mesh.indices[index + 1].normal_index + 1],
					attrib.normals[3 * shape.mesh.indices[index + 1].normal_index + 2])
				};

				vert1.tex = {
					glm::vec2(attrib.texcoords[2 * shape.mesh.indices[index + 1].texcoord_index + 0],
					attrib.texcoords[2 * shape.mesh.indices[index + 1].texcoord_index + 1])
				};


				vert2.pos = {
					glm::vec3(attrib.vertices[3 * shape.mesh.indices[index + 2].vertex_index + 0],
					attrib.vertices[3 * shape.mesh.indices[index + 2].vertex_index + 1],
					attrib.vertices[3 * shape.mesh.indices[index + 2].vertex_index + 2])
				};

				vert2.normal = {
					glm::vec3(attrib.normals[3 * shape.mesh.indices[index + 2].normal_index + 0],
					attrib.normals[3 * shape.mesh.indices[index + 2].normal_index + 1],
					attrib.normals[3 * shape.mesh.indices[index + 2].normal_index + 2])
				};

				vert2.tex = {
					glm::vec2(attrib.texcoords[2 * shape.mesh.indices[index + 2].texcoord_index + 0],
					attrib.texcoords[2 * shape.mesh.indices[index + 2].texcoord_index + 1])
				};

				glm::vec3 firstEdge = vert1.pos - vert.pos;
				glm::vec3 secondEdge = vert2.pos - vert.pos;

				float deltaU = vert1.tex.x - vert.tex.x;
				float deltaV = vert1.tex.y - vert.tex.y;
				float deltaU1 = vert2.tex.x - vert.tex.x;
				float deltaV1 = vert2.tex.y - vert.tex.y;

				float f = 1.0f / (deltaU * deltaV1 - deltaU1 * deltaV);

				glm::vec3 tangent, biTangent;

				tangent.x = f * (deltaV1 * firstEdge.x - deltaV * secondEdge.x);
				tangent.y = f * (deltaV1 * firstEdge.y - deltaV * secondEdge.y);
				tangent.z = f * (deltaV1 * firstEdge.z - deltaV * secondEdge.z);
				tangent = glm::normalize(tangent);

				vert.tangent = tangent, vert1.tangent = tangent, vert2.tangent = tangent;

				vertices.push_back(vert);
				vertices.push_back(vert1);
				vertices.push_back(vert2);
			}
		}

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));
		glEnableVertexAttribArray(3);

		glBindVertexArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	Mesh() = default;
	//Render mesh.
	void render() {
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	}
	//Dispose of VAO and VBO.
	void terminator() {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}
private:
	unsigned int VBO, VAO;
	std::vector<vertex> vertices;
};
#endif
