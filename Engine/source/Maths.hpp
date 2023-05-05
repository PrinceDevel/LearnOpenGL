#pragma once

#include <Deps/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define glmValue(x) glm::value_ptr(x)

using Mat4F = glm::mat4x4;
using Vec4F = glm::vec4;
using Vec3F = glm::vec3;
using Vec2F = glm::vec2;

#define vec2_zero       Vec2F(0.0f, 0.0f)
#define vec3_zero       Vec3F(0.0f, 0.0f, 0.0f)
#define vec4_zero       Vec4F(0.0f, 0.0f, 0.0f, 0.0f)

#define vec3_up         Vec3F(0.0f, 1.0f, 0.0f)
#define vec3_front      Vec3F(0.0f, 0.0f, 1.0f)
#define vec3_right      Vec3F(1.0f, 0.0f, 0.0f)