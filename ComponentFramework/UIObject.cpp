#include "UIObject.h"

#include "MMath.h"

UIObject::UIObject(Mesh* mesh_, Shader* shader_, Texture* texture_) :
	mesh(mesh_), shader(shader_), texture(texture_) {
}



UIObject::~UIObject() {}

bool UIObject::OnCreate() { return true; } /// Just a stub
void UIObject::OnDestroy() {}				  /// Just a stub
void UIObject::Update(float deltaTime_) {} /// Just a stub

void UIObject::Render() const {
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

void UIObject::HandleEvents(const SDL_Event& event) {} /// Just a stub