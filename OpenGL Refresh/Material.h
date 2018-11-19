#ifndef _MATERIAL_
#define _MATERIAL_

#include "Component.h"
#include "Shader.h"
#include "lodepng.h"
#include "Resource.h"

#include <vector>

class Material : public Resource
{
public:
	Material();
	~Material();

	void Load(std::string _path);

	void UploadMaterialData(std::shared_ptr<Shader> _shader);

	void Draw(std::shared_ptr<Shader> _shader, glm::mat4 _modelMat, glm::mat4 _viewMat, glm::mat4 _projMat, glm::vec3 _camPos);
	void Draw(glm::mat4 _modelMat, std::shared_ptr<Shader> _shader);
private:
	unsigned int m_diffuseTexture;
	std::weak_ptr<Shader> m_materialShader;
};

#endif // !_MATERIAL_


