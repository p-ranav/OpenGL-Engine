// User-defined Headers
#include "init_glew.h"

// Initialize GLEW and check if GLEW GL_VERSION 4.5 is supported
void Core::Init::InitGLEW::Init() {
	glewExperimental = true;
	if (glewInit() == GLEW_OK)
		spdlog::get("console")->info("GLEW::Initialized!");
	if (glewIsSupported("GL_VERSION_4_5"))
		spdlog::get("console")->info("GLEW::GL_VERSION_4_5 is supported!");
	else
		spdlog::get("console")->info("GLEW::GL_VERSION_4_5 is not supported!");
}