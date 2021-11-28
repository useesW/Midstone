#include "PhysicsObject.h"

PhysicsObject::PhysicsObject() :pos(0.0f), vel(0.0f), accel(0.0f), mass(0.0f), boundingSphere(0.0f) {
	/// Another way to initialize within the constructor
	angle = angularVel = angularAccel = 0.0f;
	rotationalI = 1.0f;

}


PhysicsObject::~PhysicsObject() {

}

void PhysicsObject::FixedUpdate(float deltaTime_) {
	vel = vel + (Vec3(0, -9.8, 0) * deltaTime_);
	pos += vel * deltaTime_;
}

