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
glm::vec3 Managers::CameraManager::GetPosition() const {
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