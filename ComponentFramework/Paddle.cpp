#include "Paddle.h"
#include <iostream>
#include "MMath.h"
#include "PinBall.h"

Paddle::Paddle(Mesh* mesh_, Shader* shader_, Texture* texture_, Vec2 textureScale_, Vec3 pos_, float rotation_, Vec2 collisionBounds_) : 
	mesh(mesh_), shader(shader_), texture(texture_), textureScale(textureScale_), pos(pos_), rotation(rotation_), collisionBounds(collisionBounds_) {

	extended = false;
	
	double angle = (-rotation * (3.1415)) / 180;
	extentionNormal = Vec3((cos(angle) * (0)) - (sin(angle) * (1)), (sin(angle) * (0)) + (cos(angle) * (1)), 0.0f);
	
	startPos = pos;
	extendedPos = pos + (extentionNormal * 1);
	percentComplete = 0.0f;
	extentionTime = 0.1f;
	elapsedTime = 0.0f;

	modelMatrix = (
		// ***CHANGE Y & Z COMPONENTS * **
		MMath::translate(pos) *
		MMath::rotate(rotation, Vec3(0.0f, 0.0f, -1.0f)) * // angle Paddle
		MMath::scale(Vec3(textureScale.x, textureScale.y, 1.0)));
}

Paddle::~Paddle() {}

bool Paddle::OnCreate() { return true; }
void Paddle::OnDestroy() {}

void Paddle::Update(float deltaTime_) {
	if (extended) {
		elapsedTime += deltaTime_;
		if (elapsedTime > extentionTime) { elapsedTime = extentionTime; extended = false; }
		percentComplete = elapsedTime / extentionTime;
		pos = (startPos + percentComplete * (extendedPos - startPos));


	} else {
		elapsedTime -= deltaTime_;
		if (elapsedTime < 0.0f) { elapsedTime = 0.0f;}
		percentComplete = elapsedTime / extentionTime;
		pos = (startPos + percentComplete * (extendedPos - startPos));
	}

	modelMatrix = (
		// ***CHANGE Y & Z COMPONENTS * **
		MMath::translate(pos) *
		MMath::rotate(rotation, Vec3(0.0f, 0.0f, -1.0f)) * // angle Paddle
		MMath::scale(Vec3(textureScale.x, textureScale.y, 1.0)));
}

void Paddle::HandleEvents(const SDL_Event& sdlEvent) {}

void Paddle::Render() const {
	Matrix3 normalMatrix = MMath::transpose(MMath::inverse(modelMatrix));

	glUniformMatrix4fv(shader->getUniformID("modelMatrix"), 1, GL_FALSE, modelMatrix);
	glUniformMatrix3fv(shader->getUniformID("normalMatrix"), 1, GL_FALSE, normalMatrix);
	if (texture) {
		glBindTexture(GL_TEXTURE_2D, texture->getTextureID());
	}

	mesh->Render();

	if (texture) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void Paddle::CalculateCollision(PinBall* ball) {
	double angle = (rotation * (3.1415)) / 180;

	Vec3 setPos = ball->getPos();
	Vec3 displacement = Vec3();

	Vec3 setVel = Vec3();
	float velMag = sqrt(pow(ball->getVel().x, 2) + pow(ball->getVel().y, 2) + pow(ball->getVel().z, 2));

	float localX = (cos(angle) * (ball->getPos().x - pos.x)) - (sin(angle) * (ball->getPos().y - pos.y));
	float localY = (sin(angle) * (ball->getPos().x - pos.x)) + (cos(angle) * (ball->getPos().y - pos.y));

#pragma region Debug
	/*std::cout << "----------------------------------------------------------------------------------" <<std::endl;
	std::cout << "Ball Pos Global : ( " << ball->getPos().x << " , " << ball->getPos().y << " )" <<std::endl;
	std::cout << "Paddle Pos Global : ( " << pos.x << " , " << pos.y << " )" <<std::endl;
	std::cout << "Global Diference : ( " << sqrt(pow((ball->getPos().x - pos.x),2)) << " , " << sqrt(pow((ball->getPos().y - pos.y),2)) << " )" <<std::endl;
	std::cout << "Ball Pos Local : ( " << localX << " , " << localY << " )" <<std::endl;
	std::cout << "local Y: " << localY - ball->getCollisionRadius() << " | At Collision Distance of " << collisionBounds.y << std::endl;*/
#pragma endregion


	if ((localY - ball->getCollisionRadius()) < collisionBounds.y && 
		(localY + ball->getCollisionRadius()) > -collisionBounds.y && 
		(localX - ball->getCollisionRadius()) < collisionBounds.x &&
		(localX + ball->getCollisionRadius()) > -collisionBounds.x) {

		if ((localY - ball->getCollisionRadius()) < collisionBounds.y) {
			//setPos.y += sqrt(pow((localY - ball->getCollisionRadius()) - collisionBounds.y, 2));
			displacement = Vec3(0.0f, sqrt(pow((localY - ball->getCollisionRadius()) - collisionBounds.y, 2)), 0.0f);
			setPos += displacement;
		} 

	}


	ball->setPos(setPos);
	float displacementMag = sqrt(pow(displacement.x, 2) + pow(displacement.y, 2));
	if (displacementMag > 0.0f) { // Yes Collision
		if (extended) {
			ball->setVel(ball->getVel() + (extentionNormal * 3.0f));
		} else {
			ball->setVel(ball->getVel() * -1);
		}
	}
}