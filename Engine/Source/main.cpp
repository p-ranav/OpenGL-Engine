/**
 * Author: Pranav Srinivas Kumar 
 */

// User-defined Headers
#include "Core\Init\init_glut.h"
#include "Managers\scene_manager.h"

int main(int argc, char **argv)
{
	Core::WindowInfo window(std::string("Engine"), 400, 200, 800, 600, true);
	Core::ContextInfo context(4, 5, true);
	Core::FrameBufferInfo framebuffer_info(true, true, true, true);
	Core::Init::InitGLUT::Init(window, context, framebuffer_info);

	Core::ListenerInterface* scene = new Managers::SceneManager();
	Core::Init::InitGLUT::SetListener(scene);

	Core::Init::InitGLUT::Run();
	
	delete scene;
	return 0;
}