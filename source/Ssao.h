#pragma once

#include <vector>
#include <glm/glm.hpp>

std::vector<glm::vec3> generate_ssao_kernel();

std::vector<glm::vec3> generate_ssao_noise();