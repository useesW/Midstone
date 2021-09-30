#ifndef SKYBOX_H
#define SKYBOX_H
#include <glew.h>
#include "GameObject.h"


class Mesh;
class Shader;

class SkyBox : public GameObject {
private:
	GLuint skyboxTextureID;
	Mesh *boxMesh;
	Shader *shader;
	
public:
	SkyBox();
	~SkyBox();
	bool LoadSkyBox(const char* posX, const char* negX, const char* posY, const char* negY, const char* posZ, const char* negZ);
	bool OnCreate() override;
	void OnDestroy() override;
	void Update(const float deltaTime) override;
	void HandleEvents(const SDL_Event& event) override;
	void Render() const;
	Shader* getShader() { return shader; }
	GLuint getSkyBoxTextureID() { return skyboxTextureID; }
};

#endif