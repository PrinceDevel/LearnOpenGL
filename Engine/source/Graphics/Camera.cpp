#include "precompiled.hpp"
#include "Camera.hpp"

Camera::Camera(Vec3F aPos, Vec3F aUp, float aYaw, float aPitch) : Front(-vec3_front), MoveSpeed(DEFAULT_SPEED), MouseSensitivity(DEFAULT_SENSITIVITY), Zoom(DEFAULT_ZOOM), Position(aPos), WorldUp(aUp), Yaw(aYaw), Pitch(aPitch) 
{
    UpdateCameraVectors();
}
Camera::~Camera() {}

Mat4F Camera::GetViewMatrix() const {
    return glm::lookAt(Position, Position + Front, Up);
}

void Camera::UpdateCameraVectors() {
    Vec3F front;
    front.x     = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y     = sin(glm::radians(Pitch));
    front.z     = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    
    Front       = glm::normalize(front);
    Right       = glm::normalize(glm::cross(Front, WorldUp));
    Up          = glm::normalize(glm::cross(Right, Front));
}
void Camera::Update(float xOffset, float yOffset) {
    xOffset *= MouseSensitivity;
    yOffset *= MouseSensitivity;

    Yaw += xOffset;
	Pitch += yOffset;

	if (Pitch > 89.0f)
		Pitch = 89.0f;
	if (Pitch < -89.0f)
		Pitch = -89.0f;
	
	UpdateCameraVectors();	
}
void Camera::Update(Vec2F offset) {
    offset *= MouseSensitivity;
    
    Yaw += offset.x;
	Pitch += offset.y;

	if (Pitch > 89.0f)
		Pitch = 89.0f;
	if (Pitch < -89.0f)
		Pitch = -89.0f;
	
	UpdateCameraVectors();	
}