#include "init_glut.h"

// Define Static Variables in InitGLUT class
Core::ListenerInterface* Core::Init::InitGLUT::listener_ = NULL;
Core::WindowInfo Core::Init::InitGLUT::window_info_;

// Initialize OpenGL Context, Display Mode, Window Position and Setup Callbacks
void Core::Init::InitGLUT::Init(const Core::WindowInfo& window_info, 
	const Core::ContextInfo& context_info, const Core::FrameBufferInfo& framebuffer_info) {
	// Initialize GLUT with fake arguments
	int fakeargc = 1; char *fakeargv[] = { "fake", NULL };
	glutInit(&fakeargc, fakeargv);

	// Setup the Context Version and Profile
	if (context_info.core) {
		glutInitContextVersion(context_info.major_version, context_info.minor_version);
		glutInitContextProfile(GLUT_CORE_PROFILE);
	}
	else
		glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	// Setup Display Mode
	glutInitDisplayMode(framebuffer_info.flags);

	// Window Initial Position
	glutInitWindowPosition(window_info.position_x, window_info.position_y);

	// Window Size
	glutInitWindowSize(window_info.width, window_info.height);
	
	// Create the Window with the above parameters
	glutCreateWindow(window_info.name.c_str());
	window_info_ = window_info;

	spdlog::get("console")->info("GLUT::Initialized!");
	
	// Setup Rendering Callbacks
	glutIdleFunc(IdleCallback);
	glutCloseFunc(CloseCallback);
	glutDisplayFunc(DisplayCallback);
	glutReshapeFunc(ReshapeCallback);
	
	// Initialize GLEW
	Init::InitGLEW::Init();
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	// Print Debug Information
	PrintOpenGLInfo();
}

// Start the Rendering Loop
void Core::Init::InitGLUT::Run() {
	spdlog::get("console")->info("GLUT::Running Rendering Loop!");
	glutMainLoop();
}

// Leave the Rendering Loop
void Core::Init::InitGLUT::Close() {
	spdlog::get("console")->info("GLUT::Finished!");
	glutLeaveMainLoop();
}

// Do nothing in the idle callback - Just redisplay
void Core::Init::InitGLUT::IdleCallback(void) {
	glutPostRedisplay();
}

// Clear the necessary bits, color and swap buffer
void Core::Init::InitGLUT::DisplayCallback() {
	if (listener_) {
		listener_->NotifyBeginFrame();
		listener_->NotifyDisplayFrame();
		glutSwapBuffers();
		listener_->NotifyEndFrame();
	}
}

// Update the Window width and Height on change
void Core::Init::InitGLUT::ReshapeCallback(int width, int height) {
	if (window_info_.is_reshapable) {
		if (listener_)
			listener_->NotifyReshape(width, height, window_info_.width, window_info_.height);
		window_info_.width = width;
		window_info_.height = height;
	}
}

// Call this->Close() to teardown the rendering loop
void Core::Init::InitGLUT::CloseCallback() {
	Close();
}

// Enter Full Screen mode
void Core::Init::InitGLUT::EnterFullscreen() {
	glutFullScreen();
}

// Exit Full Screen mode
void Core::Init::InitGLUT::ExitFullscreen() {
	glutLeaveFullScreen();
}

// Print simple debug information to console
void Core::Init::InitGLUT::PrintOpenGLInfo() {
	spdlog::get("console")->info("GLUT::Vendor: {0}", glGetString(GL_VENDOR));
	spdlog::get("console")->info("GLUT::Renderer: {0}", glGetString(GL_RENDERER));
	spdlog::get("console")->info("GLUT::OpenGL Version: {0}", glGetString(GL_VERSION));
}

// Set the Listener Object
void Core::Init::InitGLUT::SetListener(Core::ListenerInterface* listener) {
	listener_ = listener;
}