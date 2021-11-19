#include "GameObject.h"
#include "MMath.h"

GameObject::GameObject(std::string name_, GameObject* parent_, 
						TransformComponent* transform_, RenderComponent* renderer_, 
						float mass_, Vec3 gravity_, bool useGravity_, bool isStatic_, Mesh* collisionMesh_) :
	name(name_), parent(parent_), transform(transform_),renderer(renderer_)  {

	mass = mass_;
	gravity = (isStatic_) ? Vec3() : gravity_;
	useGravity = (isStatic_) ? false : useGravity_;
	isStatic = isStatic_;
	collisionMesh = collisionMesh_;
	UpdateModelMatrix();
}

GameObject::GameObject(std::string name_, 
						TransformComponent* transform_, RenderComponent* renderer_, 
						float mass_, Vec3 gravity_, bool useGravity_, bool isStatic_, Mesh* collisionMesh_) :
	name(name_), parent(nullptr), transform(transform_), renderer(renderer_) {

	mass = mass_;
	gravity = (isStatic_) ? Vec3() : gravity_;
	useGravity = (isStatic_) ? false : useGravity_;
	isStatic = isStatic_;
	collisionMesh = collisionMesh_;
	UpdateModelMatrix();
}

GameObject::GameObject() {}
GameObject::~GameObject() {}

bool GameObject::OnCreate(){return false;}

void GameObject::OnDestroy(){}

void GameObject::Update(const float deltaTime) {
	FixedUpdate(deltaTime);
	ConvertPhysicsValues();
	UpdateModelMatrix();
}

void GameObject::HandleEvents(const SDL_Event& sdlEvent) {}

void GameObject::Render() const {
	Matrix4 parentModelMatrix;
	if (parent != nullptr) { parentModelMatrix = parent->getModelMatrix(); }
	
	Matrix3 normalMatrix = MMath::transpose(MMath::inverse(parentModelMatrix * transform->modelMatrix));

	glUniformMatrix4fv(renderer->shader->getUniformID("modelMatrix"), 1, GL_FALSE, parentModelMatrix * transform->modelMatrix);
	glUniformMatrix3fv(renderer->shader->getUniformID("normalMatrix"), 1, GL_FALSE, normalMatrix);
	if (renderer->texture) { glBindTexture(GL_TEXTURE_2D, renderer->texture->getTextureID()); }

	renderer->mesh->Render();

	if (renderer->texture) { glBindTexture(GL_TEXTURE_2D, 0); }
}

void GameObject::UpdateModelMatrix() {
	setModelMatrix( 
		MMath::translate(transform->position) *
		MMath::scale(transform->scale) *
		MMath::rotate(transform->rotation, Vec3(0.0f, 0.0f, 1.0f))
	);
}
