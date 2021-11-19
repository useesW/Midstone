#ifndef UIOBJECT_H
#define UIOBJECT_H
#include <glew.h>
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "Scene.h"

using namespace MATH;
union SDL_Event;

class UIObject {

protected:
	std::string name;
	UIObject* parent;
	Scene* currentScene;
	bool render;
	bool enabled;

	TransformComponent* transform;
	RenderComponent* renderer;

public:
	UIObject(std::string name_, UIObject* parent_, Scene* currentScene_, bool startRendered_,
				TransformComponent* transform_, RenderComponent* renderer_);
	UIObject(std::string name_, Scene* currentScene_, bool startRendered_,
				TransformComponent* transform_, RenderComponent* renderer_);
	UIObject();
	~UIObject();

	virtual bool OnCreate();
	virtual void OnDestroy();
	virtual void Update(const float deltaTime_);
	virtual void HandleEvents(const SDL_Event& sdlEvent);
	virtual void Render() const;
	void UpdateModelMatrix();

#pragma region Getters & Setters
	// Getters
	inline std::string getName() { return name; }
	inline UIObject* getParent() { return parent; }
	inline bool getIsRendered() { return render; }
	inline bool getEnabled() { return enabled; }

	inline Vec3 getPosition() { return transform->position; }
	inline float getRotation() { return transform->rotation; }
	inline Vec3 getScale() { return transform->scale; }

	inline Matrix4& getModelMatrix() { return transform->modelMatrix; }
	inline Mesh* getRenderMesh() { return renderer->mesh; }
	inline Texture* getTexture() { return renderer->texture; }
	inline Shader* getShader() const { return renderer->shader; }

	// Setters
	inline void setParent(UIObject* parent_) { parent = parent_; }
	inline void setModelMatrix(const Matrix4& modelMatrix_) { transform->modelMatrix = modelMatrix_; }
	inline void setTexture(Texture* texture_) { renderer->texture = texture_; }
#pragma endregion

};

#endif