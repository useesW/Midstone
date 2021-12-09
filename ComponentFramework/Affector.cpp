#include "Affector.h"
#include <iostream>
#include "MMath.h"
#include "PinBall.h"

Affector::Affector(Mesh* mesh_, Shader* shader_, Texture* default_Texture_, Texture* hit_Texture_, Vec3 pos_, float textureScale_, float collisionRadius_, int scoreIteration_) :
	mesh(mesh_), shader(shader_), default_Texture(default_Texture_), hit_Texture(hit_Texture_), pos(pos_),textureScale(textureScale_),collisionRadius(collisionRadius_),scoreIteration(scoreIteration_) {
	modelMatrix = (
		// ***CHANGE Y & Z COMPONENTS * **
		MMath::translate(pos) *
		MMath::scale(Vec3(textureScale, textureScale, 1.0)) * // Identical scales for each
		MMath::rotate(180, Vec3(0.0f, 0.0f, 1.0f))); // face the camera
}

Affector::~Affector() {}

bool Affector::OnCreate() { return true; }
void Affector::OnDestroy() {}

void Affector::Update(float deltaTime_) {
	hitDurration_Current += deltaTime_;
	if (hitDurration_Current > hitDurration_Set) {
		hit = false;
	}
}

void Affector::HandleEvents(const SDL_Event& sdlEvent) {}

void Affector::Render() const {
	Matrix3 normalMatrix = MMath::transpose(MMath::inverse(modelMatrix));

	glUniformMatrix4fv(shader->getUniformID("modelMatrix"), 1, GL_FALSE, modelMatrix);
	glUniformMatrix3fv(shader->getUniformID("normalMatrix"), 1, GL_FALSE, normalMatrix);
	if (hit && hit_Texture) {
		glBindTexture(GL_TEXTURE_2D, hit_Texture->getTextureID());
	} else if (default_Texture) {
		glBindTexture(GL_TEXTURE_2D, default_Texture->getTextureID());
	}

	mesh->Render();

	if (hit && hit_Texture) {
		glBindTexture(GL_TEXTURE_2D, 0);
	} else if (default_Texture) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

int Affector::CalculateCollision(PinBall* ball) {
	Vec2 displacementVector = Vec2();

	if (ball != nullptr &&
		(sqrt(pow(pos.x - ball->getPos().x, 2) + pow(pos.y - ball->getPos().y, 2)) < (collisionRadius + ball->getCollisionRadius()))) { // Check radius overlap
		displacementVector.x = ball->getPos().x - pos.x;
		displacementVector.y = ball->getPos().y - pos.y;

		ball->setPos( ball->getPos() + Vec3(displacementVector.x, displacementVector.y, 0.0f)); // Displace ball 
		float velMag = sqrt(pow(ball->getVel().x, 2) + pow(ball->getVel().y, 2) + pow(ball->getVel().z, 2));
		float disMag = sqrt(pow(displacementVector.x, 2) + pow(displacementVector.y, 2));

		if (disMag > 0.001) { // Since the displacement vector will be normalized, check to see if you're dividing by zero
			displacementVector.x /= disMag; // Normalize
			displacementVector.y /= disMag; // Normalize

			ball->setVel(Vec3(displacementVector.x * velMag, displacementVector.y * velMag, 0.0f));
		}

		hit = true;
		hitDurration_Current = 0.0f;
		return scoreIteration;
	}

	return 0;
}
