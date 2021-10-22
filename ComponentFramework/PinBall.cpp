#include <iostream>
#include "PinBall.h"
#include "MMath.h"

PinBall::PinBall(Mesh* mesh_, Shader* shader_, Texture* texture_) :
	mesh(mesh_), shader(shader_), texture(texture_) {

	//vertices = mesh->vertices;
	mass = 1.0f;
	radius = 0.3f;
}

PinBall::~PinBall() {}

bool PinBall::OnCreate() { return true; } /// Just a stub
void PinBall::OnDestroy() {}				  /// Just a stub
void PinBall::Update(float deltaTime_) {

	//applyForce(Vec3(0.0,-9.8f,0.0f));

	//vel += accel * deltaTime_;
	pos += vel * deltaTime_;

	setModelMatrix(
		// ***CHANGE Y & Z COMPONENTS * **
		MMath::translate(pos) *
		MMath::scale(Vec3(radius, radius, 1.0)) * // Identical scales for each
		MMath::rotate(180, Vec3(0.0f, 0.0f, 1.0f))); // face the camera
}

void PinBall::Render() const {
	Matrix3 normalMatrix = MMath::transpose(MMath::inverse(modelMatrix));

	glUniformMatrix4fv(shader->getUniformID("modelMatrix"), 1, GL_FALSE, modelMatrix);
	glUniformMatrix3fv(shader->getUniformID("normalMatrix"), 1, GL_FALSE, normalMatrix);
	if (texture) {
		glBindTexture(GL_TEXTURE_2D, texture->getTextureID());
	}

	mesh->Render();

	/// Unbind the texture
	if (texture) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void PinBall::HandleEvents(const SDL_Event& event) {} /// Just a stub




// if the diplacement angle is more than 180, then change the velecoty vector to the displacement vector
// If the agnle is less than 180, then simply displace the position
void PinBall::CalculateCollisions(PinBall* balls[]) {
	Vec2 displacementVector = Vec2();

	// Collide W/ Goals
	// COllide W/ Bounds 
	// COllide W/ Paddles
	

	#pragma region Temp Bounds Constraint Temp
	if (sqrt(pow(pos.x, 2) + pow(pos.y, 2)) > 4.0f) {
		//pos = Vec3();
		if (pos.x > 0.0f) { displacementVector.x += (pos.x - 4); }
		else { displacementVector.x += (4 - pos.x); }

		if (pos.y > 0.0f) { displacementVector.y += (pos.y - 4); }
		else { displacementVector.y += (4 - pos.y); }
	}
	#pragma endregion

	
	// COllide W/ Balls 
	// Loop Through Active Balls
	std::cout << "Compared Against " << sizeof(balls) << "Balls \n";

	for (int i = 0; i <= sizeof(balls); i++) {
		//if (this->pos = balls[i]->pos) { 
		//	std::cout << "Ball At Position: (" << pos.x << "," << pos.y << ") Collision With Ball: (" << balls[i]->pos.x << "," << balls[i]->pos.y << ") Skipped \n";
		//	continue; 
		//} // skips collision calculation with itself
		//std::cout << "Ball At Position: (" << pos.x << "," << pos.y << ") Collision With Ball: (" << balls[i]->pos.x << "," << balls[i]->pos.y << ") Not Skipped \n";
		
		
		
		
		std::cout << "This Ball Has " << sizeof(mesh->vertices) << "Verticies \n";

		// Loop through my verticies
		for (int v1 = 0; v1 < mesh->vertices.size(); v1++) {
			// create a vector from the center of the ball to the object extent (a vertex)
			Vec2 line1S = Vec2(); line1S.x = pos.x; line1S.y = pos.y;
			Vec2 line1E = Vec2(); line1E.x = (modelMatrix * mesh->vertices.at(v1)).x; line1E.y = (modelMatrix * mesh->vertices.at(v1)).y;

			std::cout << "Ball " << i << " Has " << sizeof(mesh->vertices) << "Verticies \n";
			
			// Loop through collision check ball verticies
			for (int v2 = 0; v2 < balls[i]->mesh->vertices.size(); v2++) {
				// Create a line representing an edge of the ball object
				std::cout << "Current Vetex: (" << (balls[i]->modelMatrix * balls[i]->mesh->vertices.at(v2)).y << "," << (balls[i]->modelMatrix * balls[i]->mesh->vertices.at(v2)).y << ")\n";
				Vec2 line2S = Vec2(); 
					line2S.x = (balls[i]->modelMatrix * balls[i]->mesh->vertices.at(v2)).x; 
					line2S.y = (balls[i]->modelMatrix * balls[i]->mesh->vertices.at(v2)).y;
				Vec2 line2E = Vec2(); 
					//line2E.x = (balls[i]->modelMatrix * balls[i]->mesh->vertices.at((v2 + 1) % sizeof(balls[i]->mesh->vertices))).x; 
					//line2E.y = (balls[i]->modelMatrix * balls[i]->mesh->vertices.at((v2 + 1) % sizeof(balls[i]->mesh->vertices))).y;
					line2E.x = (v2 == balls[i]->mesh->vertices.size())? (balls[i]->modelMatrix * balls[i]->mesh->vertices.at(0)).x:(balls[i]->modelMatrix * balls[i]->mesh->vertices.at(v2 + 1)).x;
					line2E.y = (v2 == balls[i]->mesh->vertices.size())? (balls[i]->modelMatrix * balls[i]->mesh->vertices.at(0)).y:(balls[i]->modelMatrix * balls[i]->mesh->vertices.at(v2 + 1)).y;

				Vec2 temp = LineIntersection(line1S, line1E, line2S, line2E);
				displacementVector.x += temp.x;
				displacementVector.y += temp.y;
			}
		}
		
		std::cout << "Ball: " << this << "Collision With Ball: " << balls[i] << " Results In A Displacement Of: (" << displacementVector.x << "," << displacementVector.y << ")\n";
	}



	#pragma region Collision Displacement Response
	//pos += Vec3(displacementVector.x,displacementVector.y,0.0f); // Displace ball 


	float velMag = sqrt(pow(vel.x, 2) + pow(vel.y, 2) + pow(vel.z, 2));
	float disMag = sqrt(pow(displacementVector.x, 2) + pow(displacementVector.y, 2));

	if (disMag > 0.001) { // Since the displacement vector will be normalized, check to see if you're dividing by zero
		displacementVector.x /= disMag; // Normalize
		displacementVector.y /= disMag; // Normalize

		vel = Vec3(displacementVector.x * velMag, displacementVector.y * velMag, 0.0f);
	}
	#pragma endregion





	

	return;

	#pragma region Debug
	std::cout << "Distance From Origin: " << sqrt(pow(pos.x, 2) + pow(pos.y, 2)) << "\n";
	std::cout << "Velocity Magnitude: " << velMag << "\n";
	std::cout << "Displacement Magnitude: " << disMag << "\n";
	std::cout << "Displacement: (" << displacementVector.x << "," << displacementVector.y << ") \n";
	std::cout << "Velocity    : (" << vel.x << "," << vel.y << ") \n";
	std::cout << "-----------------------------------------------------------------" << "\n";
	#pragma endregion
}

//                                 mk_pair A, mk_pair B, mk_pair C, mk_pair D
inline Vec2 PinBall::LineIntersection(Vec2 s1, Vec2 e1, Vec2 s2, Vec2 e2) {
	// ax + by = c conversion
	double a1 = e1.y- s1.y;
	double b1 = s1.x- e1.x;
	double c1 = a1 * (s1.x) + b1 * (s1.y);

	double a2 = e2.y- s2.y;
	double b2 = s2.x- e2.x;
	double c2 = a2 * (s2.x) + b2 * (s2.y);

	double det = a1 * b2 - a2 * b1;
	if (det == 0) { return Vec2(); } // No Intersection


	Vec2 iPoint = Vec2(); iPoint.x = ((b2 * c1 - b1 * c2) / det); iPoint.y = ((a1 * c2 - a2 * c1) / det);

	// Check if intersection point is within the segment reach
	float magRef   = sqrt(pow(e1.x-s1.x,2) + pow(e1.y-s1.y,2));
	float magCheck = sqrt(pow(iPoint .x - s1.x, 2) + pow(iPoint.y - s1.y, 2));

	if (magCheck > magRef) { return Vec2(); } // No Collision

	// Return displacement vector (collisionP - boundsP) = -differenceV   <-- Opposite direction of collision
	iPoint.x -= e1.x;
	iPoint.y -= e1.y;
	return iPoint;
}


