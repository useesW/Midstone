#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H
#include <vector>
#include "Vector.h"
#include "Sphere.h"
#include "Mesh.h"
#include "Matrix.h"

using namespace MATH;

class PhysicsObject {
	friend class Physics;
protected:
	float mass;

	Vec3 pos, vel, accel;
	float rot;
	
	Vec3 gravity;
	bool useGravity;
	bool isStatic;
	Mesh* collisionMesh;

public:
	PhysicsObject(float mass_, Vec3 pos_, Vec3 vel_, Vec3 accel_, float rot_, Vec3 gravity_, bool useGravity_, bool isStatic_, Mesh* collisionMesh_);
	PhysicsObject(bool IsStatic_);
	PhysicsObject();
	virtual ~PhysicsObject();
	
	void FixedUpdate(const float deltaTime);

	inline void ApplyForce(const Vec3 force) { accel = force / mass; }
	bool RespondCollision(Mesh* otherMesh, Matrix4 myModelMatrix, Matrix4 otherModelMatrix);
	Vec2 LineIntersection(Vec2 s1, Vec2 e1, Vec2 s2, Vec2 e2);


#pragma region Getters & Setters
	// Getters
	inline float getMass() { return mass; }
	inline Vec3 getPos() { return pos; }
	inline Vec3 getVel() { return vel; }
	inline Vec3 getAccel() { return accel; }
	inline float getRot() { return rot; }
	inline Vec3 getGravity() { return gravity;}
	inline bool getUseGravity() { return useGravity;}
	inline bool getIsStatic() { return isStatic;}
	inline Mesh* getCollisionMesh() { return collisionMesh; }

	// Setters
	inline void setMass(const float &mass_) { mass = mass_; }
	inline void setPos(const Vec3 &pos_) { pos = pos_; }
	inline void setVel(const Vec3 &vel_) { vel = vel_; }
	inline void setAccel(const Vec3 &accel_) { accel = accel_; }
	inline void setRot(const float &rot_) { rot = rot_; }
	inline void setGravity(const Vec3& gravity_) { gravity = gravity_; }
	inline void setUseGravity(const bool& useGravity_) { useGravity = useGravity_; }
	inline void setIsStatic(const bool& isStatic_) { isStatic = isStatic_; }
#pragma endregion
	
	//inline void TransformVerticies(Matrix4 transformmatrix) { for (int i = 0; i < 100; i++) { vertices[i] = transformmatrix * vertices[i]; } }
};
#endif

