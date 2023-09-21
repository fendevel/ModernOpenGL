#include "Ssao.h"

#include <random>

#include "Util.h"

std::vector<glm::vec3> generate_ssao_kernel()
{
	std::vector<glm::vec3>  res;
	res.reserve(64);

	std::uniform_real_distribution<float> random(0.0f, 1.0f);
	std::default_random_engine generator;

	for (int i = 0; i < 64; ++i)
	{
		auto sample = glm::normalize(glm::vec3(
			random(generator) * 2.0f - 1.0f,
			random(generator) * 2.0f - 1.0f,
			random(generator)
		)) * random(generator)
			* lerp(0.1f, 1.0f, glm::pow(float(i) / 64.0f, 2));
		res.push_back(sample);
	}
	return res;
}

std::vector<glm::vec3> generate_ssao_noise()
{
	std::vector<glm::vec3>  res;
	res.reserve(16);

	std::uniform_real_distribution<float> random(0.0f, 1.0f);
	std::default_random_engine generator;

	for (int i = 0; i < 16; ++i)
		res.push_back(glm::vec3(
			random(generator) * 2.0f - 1.0f,
			random(generator) * 2.0f - 1.0f,
			0.0f
		));

	return res;
}