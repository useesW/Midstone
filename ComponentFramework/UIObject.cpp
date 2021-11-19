#include "UIObject.h"
#include "MMath.h"

UIObject::UIObject(std::string name_, UIObject* parent_, Scene* currentScene_, bool startRendered_,
					TransformComponent* transform_, RenderComponent* renderer_) :
					name(name_), parent(parent_), 
					currentScene(currentScene_), render(startRendered_), enabled(true),
					transform(transform_), renderer(renderer_) {
	UpdateModelMatrix();
}

UIObject::UIObject(std::string name_, Scene* currentScene_, bool startRendered_,
					TransformComponent* transform_, RenderComponent* renderer_) :
					name(name_), parent(nullptr),
					currentScene(currentScene_), render(startRendered_), enabled(true),
					transform(transform_), renderer(renderer_) {
	UpdateModelMatrix();
}

UIObject::UIObject() {}
UIObject::~UIObject() {}

bool UIObject::OnCreate() { return true; }
void UIObject::OnDestroy() {}
void UIObject::Update(float deltaTime_) {}
void UIObject::HandleEvents(const SDL_Event& sdlEvent) {}

void UIObject::Render() const {
	if (render && enabled) {

		Matrix4 parentModelMatrix;
		if (parent != nullptr) { parentModelMatrix = parent->getModelMatrix(); }

		Matrix3 normalMatrix = MMath::transpose(MMath::inverse(parentModelMatrix * transform->modelMatrix));

		glUniformMatrix4fv(renderer->shader->getUniformID("modelMatrix"), 1, GL_FALSE, parentModelMatrix * transform->modelMatrix);
		glUniformMatrix3fv(renderer->shader->getUniformID("normalMatrix"), 1, GL_FALSE, normalMatrix);
		if (renderer->texture) { glBindTexture(GL_TEXTURE_2D, renderer->texture->getTextureID()); }

		renderer->mesh->Render();

		if (renderer->texture) { glBindTexture(GL_TEXTURE_2D, 0); }
	}
}

void UIObject::UpdateModelMatrix() {
 	setModelMatrix(
		MMath::translate(transform->position) *
		MMath::scale(transform->scale) *
		MMath::rotate(transform->rotation, Vec3(0.0f, 0.0f, 1.0f))
	);
}