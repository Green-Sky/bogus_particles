#include <solanaceae/plugin/solana_plugin_v1.h>

#include <imgui.h>

#include <bogus_particles.hpp>

#include <memory>
#include <limits>
#include <iostream>

static std::unique_ptr<BogusParticles> g_bogus_particles = nullptr;

constexpr const char* plugin_name = "BogusParticles";

extern "C" {

SOLANA_PLUGIN_EXPORT const char* solana_plugin_get_name(void) {
	return plugin_name;
}

SOLANA_PLUGIN_EXPORT uint32_t solana_plugin_get_version(void) {
	return SOLANA_PLUGIN_VERSION;
}

SOLANA_PLUGIN_EXPORT uint32_t solana_plugin_start(struct SolanaAPI* solana_api) {
	std::cout << "PLUGIN " << plugin_name << " START()\n";

	if (solana_api == nullptr) {
		return 1;
	}

	try {
		auto* imguic = PLUG_RESOLVE_INSTANCE_VERSIONED(ImGuiContext, ImGui::GetVersion());
		auto* imguimemaf = PLUG_RESOLVE_INSTANCE_VERSIONED(ImGuiMemAllocFunc, ImGui::GetVersion());
		auto* imguimemff = PLUG_RESOLVE_INSTANCE_VERSIONED(ImGuiMemFreeFunc, ImGui::GetVersion());
		auto* imguimemud = plug_resolveInstanceOptional<void*>(solana_api, "ImGuiMemUserData", ImGui::GetVersion());

		ImGui::SetCurrentContext(imguic);
		ImGui::SetAllocatorFunctions(imguimemaf, imguimemff, imguimemud);

		// static store, could be anywhere tho
		// construct with fetched dependencies
		g_bogus_particles = std::make_unique<BogusParticles>();

		// register your api, if you have it
		PLUG_PROVIDE_INSTANCE(BogusParticles, plugin_name, g_bogus_particles.get());
	} catch (const ResolveException& e) {
		std::cerr << "PLUGIN " << plugin_name << " " << e.what << "\n";
		return 2;
	}

	return 0;
}

SOLANA_PLUGIN_EXPORT void solana_plugin_stop(void) {
	std::cout << "PLUGIN " << plugin_name << " STOP()\n";

	g_bogus_particles.reset();
}

SOLANA_PLUGIN_EXPORT float solana_plugin_tick(float delta) {
	return std::numeric_limits<float>::max();
}

SOLANA_PLUGIN_EXPORT float solana_plugin_render(float delta) {
	return g_bogus_particles->render(delta);
}

} // extern C

