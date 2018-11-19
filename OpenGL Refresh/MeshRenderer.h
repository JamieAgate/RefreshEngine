#ifndef _MESH_RENDERER_
#define _MESH_RENDERER_

#include <memory>

#include "Mesh.h"
#include "Material.h"
#include "Component.h"
#include "Camera.h"

class GameObject;

class MeshRenderer :
	virtual public Component
{
public:
	MeshRenderer();
	~MeshRenderer();

	void OnInit(std::shared_ptr<GameObject> _parent, std::shared_ptr<Shader> _shader, std::shared_ptr<Material> _mat, std::shared_ptr<Mesh> _mesh, std::weak_ptr<Camera> _cam);
	void OnInit() override;
	void OnBegin() override;
	void OnUpdate() override;
	void OnDisplay() override;
	void OnDisplay(std::shared_ptr<Shader> _shader);

private:
	std::weak_ptr<Material> m_material;
	std::weak_ptr<Mesh> m_mesh;
	std::weak_ptr<Shader> m_shader;

	std::weak_ptr<Camera> m_camera;
};

#endif // !_MESH_RENDERER_


