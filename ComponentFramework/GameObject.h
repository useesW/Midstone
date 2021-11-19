#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <glew.h>
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "PhysicsObject.h"

using namespace MATH;
union SDL_Event; /// A forward declaration 

/// Add Constuctor
class GameObject : public PhysicsObject {
public:
#pragma region Variables
	std::string name;
	GameObject* parent;

	TransformComponent* transform;
	RenderComponent* renderer;
#pragma endregion

public:
	GameObject(std::string name_, GameObject* parent_, TransformComponent* transform_, RenderComponent* renderer_, float mass_, Vec3 gravity_, bool useGravity_, bool isStatic_, Mesh* collisionMesh_);
	GameObject(std::string name_, TransformComponent* transform_, RenderComponent* renderer_, float mass_, Vec3 gravity_, bool useGravity_, bool isStatic_, Mesh* collisionMesh_);
	GameObject();
	~GameObject();

	virtual bool OnCreate();
	virtual void OnDestroy();

	virtual void Update(const float deltaTime);

	virtual void HandleEvents(const SDL_Event& sdlEvent);
	virtual void Render() const;
	void UpdateModelMatrix();


private:
	void ConvertPhysicsValues() { transform->position = pos; transform->rotation = rot; };


public:

#pragma region Getters & Setters
	// Getters
	inline std::string getName() { return name; }
	inline GameObject* getParent() { return parent; }

	inline Vec3 getPosition() { return transform->position; }
	inline float getRotation() { return transform->rotation; }
	inline Vec3 getScale() { return transform->scale; }
	inline Matrix4& getModelMatrix() { return transform->modelMatrix; }
	
	inline Mesh* getRenderMesh() { return renderer->mesh; }
	inline Texture* getTexture() { return renderer->texture; }
	inline Shader* getShader() const { return renderer->shader; }

	// Setters
	inline void setParent(GameObject* parent_) { parent = parent_; }
	inline void setPosition(Vec3 pos_) { transform->position = pos_; pos = pos_; }
	inline void setModelMatrix(const Matrix4& modelMatrix_) { transform->modelMatrix = modelMatrix_; }
#pragma endregion

	
};
#endif