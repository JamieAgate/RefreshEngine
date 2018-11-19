#include "MeshRenderer.h"
#include "GameObject.h"

MeshRenderer::MeshRenderer()
	: Component()
{

}

MeshRenderer::~MeshRenderer()
{

}


void MeshRenderer::OnInit(std::shared_ptr<GameObject> _parent, std::shared_ptr<Shader> _shader, std::shared_ptr<Material> _mat, std::shared_ptr<Mesh> _mesh, std::weak_ptr<Camera> _cam)
{
	SetParent(_parent);
	m_material = _mat;
	m_mesh = _mesh;
	m_shader = _shader;
	m_camera = _cam;
	m_material.lock()->UploadMaterialData(_shader);
}

void MeshRenderer::OnInit()
{

}

void MeshRenderer::OnBegin()
{

}

void MeshRenderer::OnUpdate()
{

}

void MeshRenderer::OnDisplay()
{
	m_material.lock()->Draw(m_shader.lock() ,GetParent()->GetModelMatrix(),m_camera.lock()->GetViewMatrix(),m_camera.lock()->GetPerspecMat(),m_camera.lock()->GetCamPos());
	m_mesh.lock()->Draw();
}

void MeshRenderer::OnDisplay(std::shared_ptr<Shader> _shader)
{
	m_material.lock()->Draw(GetParent()->GetModelMatrix(),_shader);
	m_mesh.lock()->Draw();
}
