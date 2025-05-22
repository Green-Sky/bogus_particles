#include "./bogus_particles.hpp"

#include <imgui.h>

BogusParticles::BogusParticles(void) {
	for (auto& particle : _particles) {
		particle.pos.x = -100000;
		particle.pos.y = -100000;
	}
}

float BogusParticles::render(float delta) {
	// first get mouse pos
	const auto mouse_pos = ImGui::GetMousePos();

#if 0
	// spawn a particle at mouse pos
	_particles.at(_next_pos) = {
		mouse_pos
	};
	_next_pos = (_next_pos+1) % _particles.size();
#else
	// spawn explosion on click

	// we sidestep any shorcut/focus routing
	if (ImGui::GetIO().MouseReleased[ImGuiMouseButton_Left]) {
		// exeplosion
		for (size_t i = 0; i < 32; i++) {
			_particles.at(_next_pos) = {
				mouse_pos,
				{-300.f + 600.f * _dist(_rng), -300.f + 600.f * _dist(_rng)}
			};
			_next_pos = (_next_pos+1) % _particles.size();
		}
	}
#endif
	// simulate every particle
	for (auto& particle : _particles) {
		particle.pos.x += particle.vel.x * delta;
		particle.pos.y += particle.vel.y * delta;

		// fake gravity
		particle.vel.y += 150.f * delta;

		// fake air dampening
		particle.vel.x -= particle.vel.x * 0.5f * delta;
		particle.vel.y -= particle.vel.y * 0.5f * delta;
	}

	auto* dl = ImGui::GetForegroundDrawList();

	for (const auto& particle : _particles) {
		const float radius = 3.f;
		ImVec2 ul(particle.pos.x - radius, particle.pos.y - radius);
		ImVec2 lr(particle.pos.x + radius, particle.pos.y + radius);
		dl->AddRectFilled(ul, lr, ImGui::GetColorU32({1.f, 1.f, 0.4f, 0.7f}));
	}

	return 1/30.f;
}

