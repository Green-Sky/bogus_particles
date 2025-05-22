#pragma once

#include <imgui.h>

#include <array>
#include <random>

struct BogusParticles {
	struct Particle {
		ImVec2 pos;
		ImVec2 vel;
	};

	std::array<Particle, 256> _particles;

	size_t _next_pos {0};

	std::default_random_engine _rng{1337};
	std::uniform_real_distribution<float> _dist;

	BogusParticles(void);

	float render(float delta);
};

