cmake_minimum_required(VERSION 3.24 FATAL_ERROR)

########################################

add_library(plugin_bogus_particles MODULE
	./plugin_bogus_particles.cpp
)
target_compile_features(plugin_bogus_particles PUBLIC cxx_std_17)
set_target_properties(plugin_bogus_particles PROPERTIES
	C_VISIBILITY_PRESET hidden
)
target_compile_definitions(plugin_bogus_particles PUBLIC ENTT_API_IMPORT)
target_link_libraries(plugin_bogus_particles PUBLIC
	solanaceae_plugin
	bogus_particles
)

