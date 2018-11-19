#ifndef _CORE_
#define _CORE_

#include <vector>
#include <memory>
#include <map>

#include "GameObject.h"
#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"
#include "InputManager.h"
#include "Material.h"
#include "MeshRenderer.h"
#include "Light.h"
#include "PointLight.h"
#include "FrameBuffer.h"
#include "Resources.h"

class Core : public std::enable_shared_from_this<Core>
{
public:
	Core();
	~Core();

	void Init();

	std::shared_ptr<InputManager> GetInput() { return m_input; }

	void SetIfLightingDataUploaded(bool _b) { m_lightingDataUploaded = _b; }

	void UploadLightingData();

	void CreateGameObject(glm::vec3 _pos);

	void Update();

	void DrawShadows(std::vector<std::weak_ptr<Shader>> _shaders);
	void Draw();
	void renderQuad();
private:
	std::vector<std::shared_ptr<GameObject>> m_gameObjects;

	std::shared_ptr<FrameBuffer> m_shadowFBO;

	std::shared_ptr<Resources> m_resources;

	//std::map<std::string,std::shared_ptr<Shader>> m_shaders;
	//std::map<std::string, std::shared_ptr<Mesh>> m_meshes;
	//std::map<std::string, std::shared_ptr<Material>> m_materials;

	bool m_lightingDataUploaded;
	std::vector<std::weak_ptr<Light>> m_lights;

	std::shared_ptr<InputManager> m_input;

	std::shared_ptr<Camera> m_mainCamera;

	unsigned int m_lastTime;
};

#endif // !_CORE_


