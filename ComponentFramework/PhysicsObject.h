#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H
#include <vector>
#include "Vector.h"
#include "Sphere.h"
#include "Matrix.h"

using namespace MATH;

class PhysicsObject {
	friend class Physics;
protected:
	Vec3 pos, vel, accel;
	float mass;
	Sphere boundingSphere;
	//Vec3 vertices[100];
	//static std::vector<Vec3> vertices;
	float angle, angularVel, angularAccel, rotationalI;
public:
	PhysicsObject();
	virtual ~PhysicsObject();
	

public:
	/// Untility functions so small they cane be inlined
	inline void setPos(const Vec3 &pos_) { pos = pos_; }
	inline Vec3 getPos() { return pos; }
	inline void setVel(const Vec3 &vel_) { vel = vel_; }
	inline Vec3 getVel() { return vel; }
	inline void setAccel(const Vec3 &accel_) { accel = accel_; }
	inline Vec3 getAccel() { return accel; }
	inline void setAngularVel(const float angularVel_) { angularVel = angularVel_; }
	inline float getAngle() { return angle; }
	inline void applyForce(const Vec3 force) { accel = force / mass;  }
	//inline void TransformVerticies(Matrix4 transformmatrix) { for (int i = 0; i < 100; i++) { vertices[i] = transformmatrix * vertices[i]; } }

};
#endif

