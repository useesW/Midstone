#ifndef TRANSFROMCOMPONENT_H
#define TRANSFROMCOMPONENT_H
#include "Matrix.h"
using namespace MATH;

struct TransformComponent {
	Vec3 position, scale;
	float rotation;

	Matrix4 modelMatrix;

	TransformComponent(Vec3 position_, Vec3 scale_, float rotation_, Matrix4 modelMatrix_) {
		position = position_;
		scale = scale_;
		rotation = rotation_;
		modelMatrix = modelMatrix_;
	}

	TransformComponent() {
		position = Vec3(0.0f, 0.0f, 0.0f);
		scale = Vec3(1.0f, 1.0f, 1.0f);
		rotation = 0.0f;
		modelMatrix = Matrix4();
	}
};
#endif
