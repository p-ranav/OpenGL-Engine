// User-defined Headers
#include "camera_manager.h"

// Initialize CameraManager
Managers::CameraManager::CameraManager() :
	view_port_(0), position_(0), rotation_(),
	projection_matrix_(1), view_matrix_(1), is_view_dirty_(false)
{}

// Initialize Camera Manager with provided screen width and height
Managers::CameraManager::CameraManager(int screen_width, int screen_height)
	: view_port_(0, 0, screen_width, screen_height), position_(0), rotation_()
	, projection_matrix_(1), view_matrix_(1), is_view_dirty_(false)
{}

// Sets the camera view port
void Managers::CameraManager::SetViewport(int x, int y, int width, int height) {
	view_port_ = glm::vec4(x, y, width, height);
	glViewport(x, y, width, height);
}

// Returns the camera view port
glm::vec4 Managers::CameraManager::GetViewport() const {
	return view_port_;
}

// Sets the internal projection matrix
void Managers::CameraManager::SetProjectionMatrix(float field_of_view, float aspect_ratio, float z_near_value, float z_far_value) {
	projection_matrix_ = glm::perspective(glm::radians(field_of_view), aspect_ratio, z_near_value, z_far_value);
}

// Update the view matrix
void Managers::CameraManager::ApplyViewMatrix() {
	UpdateViewMatrix();
}

// Set the camera position
void Managers::CameraManager::SetPosition(const glm::vec3& position) {
	position_ = position;
	is_view_dirty_ = true;
}

// Returns the camera position
glm::vec3 Managers::CameraManager::GetPosition() {
	return position_;
}

// Translate the camera by delta
void Managers::CameraManager::Translate(const glm::vec3& delta, bool local /* = true */) {
	if (local)
		position_ += rotation_ * delta;
	else
		position_ += delta;
	is_view_dirty_ = true;
}

// Sets the camera rotation
void Managers::CameraManager::SetRotation(const glm::quat& rotation) {
	rotation_ = rotation;
	is_view_dirty_ = true;
}

// Returns the camera rotation
glm::quat Managers::CameraManager::GetRotation() const {
	return rotation_;
}

// Set the Euler Angles
void Managers::CameraManager::SetEulerAngles(const glm::vec3& euler_angles) {
	rotation_ = glm::quat(glm::radians(euler_angles));
}

// Returns the Euler Angles
glm::vec3 Managers::CameraManager::GetEulerAngles() const {
	return glm::degrees(glm::eulerAngles(rotation_));
}

// Rotates the camera by provided quaternion
void Managers::CameraManager::Rotate(const glm::quat& rotate_by) {
	rotation_ = rotation_ * rotate_by;
	is_view_dirty_ = true;
}

// Returns the projection matrix
glm::mat4 Managers::CameraManager::GetProjectionMatrix() {
	return projection_matrix_;
}

// Returns the view matrix
glm::mat4 Managers::CameraManager::GetViewMatrix() {
	UpdateViewMatrix();
	return view_matrix_;
}

// Updates the view matrix
void Managers::CameraManager::UpdateViewMatrix() {
	if (is_view_dirty_) {
		glm::mat4 translate = glm::translate(-position_);
		// Since we know the rotation matrix is ortho-normalized, we can simply 
		// transpose the rotation matrix instead of inversing.
		glm::mat4 rotate = glm::transpose(glm::toMat4(rotation_));
		view_matrix_ = rotate * translate;
		is_view_dirty_ = false;
	}
}

// Define Static Variables
int Managers::CameraManager::KEY_W = 0;
int Managers::CameraManager::KEY_A = 0;
int Managers::CameraManager::KEY_S = 0;
int Managers::CameraManager::KEY_D = 0;
int Managers::CameraManager::KEY_Q = 0;
int Managers::CameraManager::KEY_E = 0;
glm::ivec2 Managers::CameraManager::MOUSE_POSITION = glm::ivec2();
glm::quat Managers::CameraManager::MOUSE_ROTATION_X = glm::quat();
glm::quat Managers::CameraManager::MOUSE_ROTATION_Y = glm::quat();
int Managers::CameraManager::MOUSE_STATE = 0;
const glm::vec3 Managers::CameraManager::LOCAL_FORWARD(0.0f, 0.0f, -1.0f);
const glm::vec3 Managers::CameraManager::LOCAL_UP(0.0f, 1.0f, 0.0f);
const glm::vec3 Managers::CameraManager::LOCAL_RIGHT(1.0f, 0.0f, 0.0f);
glm::vec3 Managers::CameraManager::CAMERA_TRANSLATION = glm::vec3();

// Key press callback - Simply save the key that was pressed
void Managers::CameraManager::KeyPressCallback(unsigned char c, int x, int y) {
	std::cout << "Key Press Detected: " << c << std::endl;
	switch (c) {
	case 'w':
	case 'W':
		KEY_W = 1;
		break;
	case 'a':
	case 'A':
		KEY_A = 1;
		break;
	case 's':
	case 'S':
		KEY_S = 1;
		break;
	case 'd':
	case 'D':
		KEY_D = 1;
		break;
	case 'q':
	case 'Q':
		KEY_Q = 1;
		break;
	case 'e':
	case 'E':
		KEY_E = 1;
		break;
	case 27:
		glutLeaveMainLoop();
		break;
	}
	float translation_speed = 0.1f;
	CAMERA_TRANSLATION = glm::vec3(KEY_D - KEY_A, KEY_Q - KEY_E, KEY_S - KEY_W) * translation_speed;
}

// Key release callback - Simply reset the key that was pressed
void Managers::CameraManager::KeyReleaseCallback(unsigned char c, int x, int y) {
	switch (c)
	{
	case 'w':
	case 'W':
		KEY_W = 0;
		break;
	case 'a':
	case 'A':
		KEY_A = 0;
		break;
	case 's':
	case 'S':
		KEY_S = 0;
		break;
	case 'd':
	case 'D':
		KEY_D = 0;
		break;
	case 'q':
	case 'Q':
		KEY_Q = 0;
		break;
	case 'e':
	case 'E':
		KEY_E = 0;
		break;
	default:
		break;
	}
	float translation_speed = 0.1f;
	CAMERA_TRANSLATION = glm::vec3(KEY_D - KEY_A, KEY_Q - KEY_E, KEY_S - KEY_W) * translation_speed;
}

// Handle mouse press
void Managers::CameraManager::MousePressCallback(int button, int state, int x, int y) {
	MOUSE_STATE = state;
	MOUSE_POSITION = glm::ivec2(x, y);
}

// HANDLE mouse movement
void Managers::CameraManager::MouseMoveCallback(int x, int y) {
	glm::ivec2 current_mouse_position = glm::ivec2(x, y);
	// Calculate mouse movement delta
	glm::vec2 delta = glm::vec2(current_mouse_position - MOUSE_POSITION);

	// Update mouse position
	MOUSE_POSITION = current_mouse_position;

	// Check if delta is large enough to set rotation
	float rotation_speed = 0.1f;
	if (delta.x > 1 || delta.x < -1 || delta.y > 1 || delta.y < -1) {
		MOUSE_ROTATION_X = glm::angleAxis<float>(-rotation_speed * glm::radians(delta.x), LOCAL_UP);
		MOUSE_ROTATION_Y = glm::angleAxis<float>(-rotation_speed * glm::radians(delta.y), LOCAL_RIGHT);
	}
	// Zero out the rotation if the delta is not large enough
	else {
		MOUSE_ROTATION_X = glm::vec3();
		MOUSE_ROTATION_Y = glm::vec3();
	}
}