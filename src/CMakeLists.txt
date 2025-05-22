cmake_minimum_required(VERSION 3.24 FATAL_ERROR)

add_library(bogus_particles
	./bogus_particles.hpp
	./bogus_particles.cpp
)
target_include_directories(bogus_particles PUBLIC .)
target_compile_features(bogus_particles PUBLIC cxx_std_17)
target_link_libraries(bogus_particles PUBLIC
	imgui
)

