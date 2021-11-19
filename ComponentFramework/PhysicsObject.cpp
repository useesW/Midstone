#include "PhysicsObject.h"

PhysicsObject::PhysicsObject(float mass_, Vec3 pos_, Vec3 vel_, Vec3 accel_, float rot_, Vec3 gravity_, bool useGravity_, bool isStatic_, Mesh* collisionMesh_):
	mass(mass_), pos(pos_), vel(vel_), accel(accel_), rot(rot_), gravity(gravity_), useGravity(useGravity_), isStatic(isStatic_), collisionMesh(collisionMesh_){}

PhysicsObject::PhysicsObject(bool isStatic_) :
	mass(1.0f), pos(Vec3()), vel(Vec3()), accel(Vec3()), rot(0.0f), gravity(Vec3(0.0f, -9.8f, 0.0f)), isStatic(isStatic_), collisionMesh(nullptr) {
	useGravity = (isStatic_) ? false : true;
}

PhysicsObject::PhysicsObject():
	mass(1.0f), pos(Vec3()), vel(Vec3()), accel(Vec3()), rot(0.0f), gravity(Vec3(0.0f, -9.8f, 0.0f)), useGravity(true), isStatic(false), collisionMesh(nullptr) {}

PhysicsObject::~PhysicsObject(){}

void PhysicsObject::FixedUpdate(const float deltaTime) {
	if (isStatic) { return; }
	if (useGravity) { ApplyForce(gravity); }

	vel = vel + (accel * deltaTime);
	pos += vel * deltaTime + 0.5f * accel * deltaTime * deltaTime;
}

/// Requres Testing
bool PhysicsObject::RespondCollision(Mesh* otherMesh, Matrix4 myModelMatrix, Matrix4 otherModelMatrix) {
	if (isStatic) { return false; }
	Vec3 displacementVector = Vec3();
	//Loop through my verticies
	for (int v1 = 0; v1 < collisionMesh->vertices.size(); v1++) {
		// create a vector from the center of the ball to the object extent (a vertex)
		Vec2 line1S = Vec2(); 
			line1S.x = pos.x; 
			line1S.y = pos.y;
		Vec2 line1E = Vec2(); 
			line1E.y += (myModelMatrix * collisionMesh->vertices.at(v1)).y;

		// Loop through collision check ball verticies
		for (int v2 = 0; v2 < otherMesh->vertices.size(); v2++) {
			// Create a line representing an edge of the ball object
			//std::cout << "Current Vetex: (" << (otherModelMatrix * otherMesh->vertices.at(v2)).y << "," << (otherModelMatrix * otherMesh->vertices.at(v2)).y << ")\n";
			Vec2 line2S = Vec2(); 
				line2S.x += (otherModelMatrix * otherMesh->vertices.at(v2)).x; 
				line2S.y += (otherModelMatrix * otherMesh->vertices.at(v2)).y;
			Vec2 line2E = Vec2(); 
				//line2E.x = (balls[i]->modelMatrix * balls[i]->mesh->vertices.at((v2 + 1) % sizeof(balls[i]->mesh->vertices))).x; 
				//line2E.y = (balls[i]->modelMatrix * balls[i]->mesh->vertices.at((v2 + 1) % sizeof(balls[i]->mesh->vertices))).y;
				line2E.x += (v2 == otherMesh->vertices.size())? (otherModelMatrix * otherMesh->vertices.at(0)).x:(otherModelMatrix * otherMesh->vertices.at(v2)).x;
				line2E.y += (v2 == otherMesh->vertices.size())? (otherModelMatrix * otherMesh->vertices.at(0)).y:(otherModelMatrix * otherMesh->vertices.at(v2)).y;


			float h = (line2E.x - line2S.x) * (line1S.y - line1E.y) - (line1S.x - line1E.x) * (line2E.y - line2S.y);
			float t1 = ((line2S.y - line2E.y) * (line1S.x - line2S.x) + (line2E.x - line2S.x) * (line1S.y - line2S.y)) / h;
			float t2 = ((line1S.y - line1E.y) * (line1S.x - line2S.x) + (line1E.x - line1S.x) * (line1S.y - line2S.y)) / h;
			//Vec2 temp = LineIntersection(line1S, line1E, line2S, line2E);
			//displacementVector.x += temp.x;
			//displacementVector.y += temp.y;

			if (t1 >= 0.0f && t1 < 1.0f && t2 >= 0.0f && t2 < 1.0f) {
				displacementVector.x += (1.0f - t1) * (line1E.x - line1S.x);
				displacementVector.y += (1.0f - t1) * (line1E.y - line1S.y);
			}
		}
	}

	std::cout << "Displacement vec2( " << displacementVector.x << ", " << displacementVector.y << ", " << displacementVector.z << ") \n";

	pos += displacementVector;

	float velMag = sqrt(pow(vel.x, 2) + pow(vel.y, 2) + pow(vel.z, 2));
	float disMag = sqrt(pow(displacementVector.x, 2) + pow(displacementVector.y, 2));

	if (disMag > 0.001) { // Since the displacement vector will be normalized, check to see if you're dividing by zero
		displacementVector.x /= disMag; // Normalize
		displacementVector.y /= disMag; // Normalize

		vel = Vec3(displacementVector.x * velMag, displacementVector.y * velMag, 0.0f);
		return true;
	} else { return false; } // If the magnitude of the displacement vector is near-at zero, then no collision took place.
}

/// Requires Testing
//                                 mk_pair A, mk_pair B, mk_pair C, mk_pair D
Vec2 PhysicsObject::LineIntersection(Vec2 s1, Vec2 e1, Vec2 s2, Vec2 e2) {
	// ax + by = c conversion
	double a1 = e1.y - s1.y;
	double b1 = s1.x - e1.x;
	double c1 = a1 * (s1.x) + b1 * (s1.y);

	double a2 = e2.y - s2.y;
	double b2 = s2.x - e2.x;
	double c2 = a2 * (s2.x) + b2 * (s2.y);

	double det = a1 * b2 - a2 * b1;
	if (det == 0) { return Vec2(); } // No Intersection


	Vec2 iPoint = Vec2(); iPoint.x = ((b2 * c1 - b1 * c2) / det); iPoint.y = ((a1 * c2 - a2 * c1) / det);

	// Check if intersection point is within the segment reach
	float magRef = sqrt(pow(e1.x - s1.x, 2) + pow(e1.y - s1.y, 2));
	float magCheck = sqrt(pow(iPoint.x - s1.x, 2) + pow(iPoint.y - s1.y, 2));

	if (magCheck > magRef) { return Vec2(); } // No Collision

	// Return displacement vector (collisionP - boundsP) = -differenceV   <-- Opposite direction of collision
	iPoint.x -= e1.x;
	iPoint.y -= e1.y;
	return iPoint;
}


