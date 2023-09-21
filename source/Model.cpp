#include "Model.h"

std::vector<glm::vec3> calc_tangents(std::vector<vertex_t> const& vertices, std::vector<uint8_t> const& indices)
{
	std::vector<glm::vec3> res;
	res.reserve(indices.size());
	for (auto q = 0; q < 6; ++q)
	{
		auto
			v = q * 4,
			i = q * 6;
		glm::vec3
			edge0 = vertices[indices[i + 1]].position - vertices[indices[i + 0]].position, edge1 = vertices[indices[i + 2]].position - vertices[indices[0]].position,
			edge2 = vertices[indices[i + 4]].position - vertices[indices[i + 3]].position, edge3 = vertices[indices[i + 5]].position - vertices[indices[3]].position;

		glm::vec2
			delta_uv0 = vertices[indices[i + 1]].texcoord - vertices[indices[i + 0]].texcoord, delta_uv1 = vertices[indices[i + 2]].texcoord - vertices[indices[i + 0]].texcoord,
			delta_uv2 = vertices[indices[i + 4]].texcoord - vertices[indices[i + 3]].texcoord, delta_uv3 = vertices[indices[i + 5]].texcoord - vertices[indices[i + 3]].texcoord;

		float const
			f0 = 1.0f / (delta_uv0.x * delta_uv1.y - delta_uv1.x * delta_uv0.y),
			f1 = 1.0f / (delta_uv2.x * delta_uv3.y - delta_uv3.x * delta_uv2.y);

		auto const
			t0 = glm::normalize(glm::vec3(
				f0 * (delta_uv1.y * edge0.x - delta_uv0.y * edge1.x),
				f0 * (delta_uv1.y * edge0.y - delta_uv0.y * edge1.y),
				f0 * (delta_uv1.y * edge0.z - delta_uv0.y * edge1.z)
			)),
			t1 = glm::normalize(glm::vec3(
				f1 * (delta_uv3.y * edge2.x - delta_uv2.y * edge3.x),
				f1 * (delta_uv3.y * edge2.y - delta_uv2.y * edge3.y),
				f1 * (delta_uv3.y * edge2.z - delta_uv2.y * edge3.z)
			));

		res.push_back(t0); res.push_back(t0); res.push_back(t0);
		res.push_back(t1); res.push_back(t1); res.push_back(t1);
	}
	return res;
}