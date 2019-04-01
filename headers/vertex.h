#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>
struct vertex {
	glm::vec3 pos;
	glm::vec3 normal;
	glm::vec2 tex;

	bool operator==(const vertex& other) const {
		return pos == other.pos && normal == other.normal && tex == other.tex;
	}
};

namespace std {
	template<> struct hash<vertex> {
		size_t operator()(vertex const& vertex) const {
			return ((hash<glm::vec3>()(vertex.pos) ^
				(hash<glm::vec3>()(vertex.normal) << 1)) >> 1) ^
				(hash<glm::vec2>()(vertex.tex) << 1);
		}
	};
}