#ifndef RENDERCOMPONENT_H
#define RENDERCOMPONENT_H
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"

struct RenderComponent {
	Mesh* mesh;
	Texture* texture;
	Shader* shader;

	RenderComponent(Mesh* mesh_, Texture* texture_, Shader* shader_){
		mesh = mesh_;
		texture = texture_;
		shader = shader_;
	}
	
	RenderComponent() {
		mesh = nullptr;
		texture = nullptr;
		shader = nullptr;
	}
};
#endif
