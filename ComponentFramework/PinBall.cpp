#include <iostream>
#include "PinBall.h"
#include "MMath.h"

PinBall::PinBall(Mesh* mesh_, Shader* shader_, Texture* texture_, float textureScale_, float collisionRadius_, Vec2 gameBounds_) :
	mesh(mesh_), shader(shader_), texture(texture_) {

	//vertices = mesh->vertices;
	mass = 1.0f;
	textureScale = textureScale_;
	collisionRadius = collisionRadius_;
	gameBounds = gameBounds_;
}

PinBall::~PinBall() {}

bool PinBall::OnCreate() { return true; } /// Just a stub
void PinBall::OnDestroy() {}				  /// Just a stub
void PinBall::Update(float deltaTime_) {

	//deltaTime_ = deltaTime_ * 0.1;
	FixedUpdate(deltaTime_);

	setModelMatrix(
		// ***CHANGE Y & Z COMPONENTS * **
		MMath::translate(pos) *
		MMath::scale(Vec3(textureScale, textureScale, 1.0)) * // Identical scales for each
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

#pragma region Outer Bounds Collision Detection
	if ((pos.x + collisionRadius) > gameBounds.x) {
		pos.x += (gameBounds.x - (pos.x + collisionRadius));
		vel.x *= -1;
	} else if ((pos.x - collisionRadius) < -gameBounds.x) {
		pos.x += (-gameBounds.x - (pos.x - collisionRadius));
		vel.x *= -1;
	}

	if ((pos.y + collisionRadius) > gameBounds.y) {
		pos.y += (gameBounds.y - (pos.y + collisionRadius));
		vel.y *= -1;
	} else if ((pos.y - collisionRadius) < -gameBounds.y) {
		pos.y += (-gameBounds.y - (pos.y - collisionRadius));
		vel.y *= -1;
	}
#pragma endregion

#pragma region Ball-Ball Collision
	Vec2 displacementVector = Vec2();
	for (int i = 0; i <= sizeof(balls); i++) {
		//std::cout << "Ball At Position: (" << pos.x << "," << pos.y << ") Collision With Ball: (" << balls[i]->pos.x << "," << balls[i]->pos.y << ") Not Skipped \n";

		// Skip Self Collision
		if (pos != balls[i]->pos &&
			(sqrt(pow(this->pos.x - balls[i]->getPos().x, 2) + pow(this->pos.y - balls[i]->getPos().y, 2)) < collisionRadius)) { // 
			displacementVector.x += pos.x - balls[i]->getPos().x;
			displacementVector.y += pos.y - balls[i]->getPos().y;
		}
	}

	//pos += Vec3(displacementVector.x, displacementVector.y, 0.0f); // Displace ball 
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

void PinBall::HandleDisplacement(Vec2 displacementVector) {


	// Flip respective velocity

}

void PinBall::HandleFlipVelocy(Vec2 signVector) {
}
