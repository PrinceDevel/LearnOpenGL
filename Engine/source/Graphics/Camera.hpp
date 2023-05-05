#pragma once

#include "Maths.hpp"

const float DEFAULT_YAW             = -90.0f;
const float DEFAULT_PITCH           =  0.0f;
const float DEFAULT_SPEED           =  2.5f;
const float DEFAULT_SENSITIVITY     =  0.1f;
const float DEFAULT_ZOOM            =  45.0f;

class Camera 
{
public:
    Camera(Vec3F aPos = vec3_zero, Vec3F aUp = vec3_up, float aYaw = DEFAULT_YAW, float aPitch = DEFAULT_PITCH);
    ~Camera();

    Mat4F GetViewMatrix() const;
    void Update(Vec2F offset);
    void Update(float xOffset = 0.0f, float yOffset = 0.0f);
    void UpdateCameraVectors();

public:
    Vec3F Position;
    float MoveSpeed;
    float MouseSensitivity;
    float Zoom;

    Vec3F Front;
    Vec3F Right;
    Vec3F Up;
    Vec3F WorldUp;

    float Yaw;
    float Pitch;
};