#include "Core.h"

Core::Core()
{
	m_lightingDataUploaded = false;
	//LOAD RESOURCES
	m_resources = std::make_shared<Resources>();

	m_resources->Load<Mesh>("Sphere Mesh","sphere.obj");
	m_resources->Load<Mesh>("Box Mesh","Box.obj");

	m_resources->Load<Shader>("Default Shader","Shaders/DefaultVertShader.txt", "Shaders/DefaultFragShader.txt");
	m_resources->Load<Shader>("Depth Shader","Shaders/DepthVertShader.txt", "Shaders/DepthFragShader.txt");
	m_resources->Load<Shader>("Lamp Shader","Shaders/LampVertShader.txt", "Shaders/LampFragShader.txt");
	m_resources->Load<Shader>("Debug Depth Shader","Shaders/DebugDepthVert.txt", "Shaders/DebugDepthFrag.txt");

	m_resources->Load<Material>("Default Material","Textures/Default.png");

	////MESH UPLOAD
	//m_meshes.insert(std::pair<std::string, std::shared_ptr<Mesh>>("Sphere", std::make_shared<Mesh>("sphere.obj")));

	//m_meshes.insert(std::pair<std::string, std::shared_ptr<Mesh>>("Box", std::make_shared<Mesh>("Box.obj")));

	////SHADER UPLOAD
	//m_shaders.insert(std::pair<std::string, std::shared_ptr<Shader>>("Default", std::make_shared<Shader>("Shaders/DefaultVertShader.txt", "Shaders/DefaultFragShader.txt")));

	//m_shaders.insert(std::pair<std::string, std::shared_ptr<Shader>>("Depth", std::make_shared<Shader>("Shaders/DepthVertShader.txt", "Shaders/DepthFragShader.txt")));

	//m_shaders.insert(std::pair<std::string, std::shared_ptr<Shader>> ("Lamp", std::make_shared<Shader>("Shaders/LampVertShader.txt", "Shaders/LampFragShader.txt")));

	//m_shaders.insert(std::pair<std::string, std::shared_ptr<Shader>>("DebugDepth", std::make_shared<Shader>("Shaders/DebugDepthVert.txt", "Shaders/DebugDepthFrag.txt")));
	////MATERIAL UPLOAD
	//m_materials.insert(std::pair<std::string, std::shared_ptr<Material>>("Default", std::make_shared<Material>(m_shaders.find("Default")->second, "Textures/Default.png")));

	//m_materials.insert(std::pair<std::string, std::shared_ptr<Material>>("Lamp", std::make_shared<Material>(m_shaders.find("Lamp")->second, "Textures/Default.png")));

	m_input = std::make_shared<InputManager>();

	m_mainCamera = std::make_shared<Camera>(m_input);

	m_lastTime = SDL_GetTicks();

	m_shadowFBO = std::make_shared<FrameBuffer>();
	m_shadowFBO->GenerateShadowMap(1024, 1024);

	std::weak_ptr<Shader> depthShad = m_resources->Get<Shader>("Debug Depth Shader");
	depthShad.lock()->Use();
	depthShad.lock()->SetFloat("near_plane", -10.0f);
	depthShad.lock()->SetFloat("far_plane", 20.0f);
	depthShad.lock()->SetInt("depthMap", 2);
}

Core::~Core()
{

}

void Core::Init()
{
	CreateGameObject(glm::vec3(0.0f,0.5f,0.0f));
	m_gameObjects.back()->AddComponenet<MeshRenderer>("MeshRenderer",m_gameObjects.back(),m_resources->Get<Shader>("Default Shader"), m_resources->Get<Material>("Default Material"), m_resources->Get<Mesh>("Sphere Mesh"), m_mainCamera);

	CreateGameObject(glm::vec3(0.0f, -1.5f, 0.0f));
	m_gameObjects.back()->AddComponenet<MeshRenderer>("MeshRenderer", m_gameObjects.back(), m_resources->Get<Shader>("Default Shader") ,m_resources->Get<Material>("Default Material"), m_resources->Get<Mesh>("Box Mesh"), m_mainCamera);

	CreateGameObject(glm::vec3(0.0f, 4.0f, 3.0f));
	m_gameObjects.back()->AddComponenet<PointLight>("PointLight", m_gameObjects.back());
	m_lights.push_back(m_gameObjects.back()->GetComponent<PointLight>());
	m_gameObjects.back()->AddComponenet<MeshRenderer>("MeshRenderer",m_gameObjects.back(), m_resources->Get<Shader>("Lamp Shader"), m_resources->Get<Material>("Default Material"), m_resources->Get<Mesh>("Sphere Mesh"), m_mainCamera);
	m_gameObjects.back()->SetScale(0.5f, 0.5f, 0.5f);

	CreateGameObject(glm::vec3(6.0f, -1.0f, -2.0f));
	m_gameObjects.back()->AddComponenet<PointLight>("PointLight", m_gameObjects.back());
	m_lights.push_back(m_gameObjects.back()->GetComponent<PointLight>());
	m_gameObjects.back()->AddComponenet<MeshRenderer>("MeshRenderer", m_gameObjects.back(), m_resources->Get<Shader>("Lamp Shader"), m_resources->Get<Material>("Default Material"), m_resources->Get<Mesh>("Sphere Mesh"), m_mainCamera);
	m_gameObjects.back()->SetScale(0.5f, 0.5f, 0.5f);

	CreateGameObject(glm::vec3(0.0f, 0.0f, 0.0f));
	m_gameObjects.back()->SetRotation(glm::vec3(0.0f, 90.0f, 0.0f));
	m_gameObjects.back()->AddComponenet<Light>("DirLight",m_gameObjects.back(), 0);
	m_lights.push_back(m_gameObjects.back()->GetComponent<Light>());
}


void Core::Update()
{
	unsigned int current = SDL_GetTicks();//gets current ticks
	float deltaTs = (float)(current - m_lastTime) / 1000.0f;//measures the change it ticks

	m_input->UpdateKeyboard();
	m_mainCamera->Update(deltaTs);
	for (std::shared_ptr<GameObject> g : m_gameObjects)
	{
		g->Update();
	}

	UploadLightingData();

	//caps framerate
	if (deltaTs < (1.0f / 50.0f))
	{
		SDL_Delay((unsigned int)(((1.0f / 50.0f) - deltaTs)*1000.0f));
	}
	m_lastTime = current;
}

void Core::UploadLightingData()
{
	if (!m_lightingDataUploaded)
	{
		std::vector<std::weak_ptr<Shader>> shaders = m_resources->GetResources<Shader>();
		for (std::weak_ptr<Light> l : m_lights)
		{
			if (!l.lock()->GetIfUploaded())
			{
				for (std::weak_ptr<Shader> s : shaders)
				{
					s.lock()->Use();
					l.lock()->UploadLightData(s.lock());
					l.lock()->SwitchIfUplaoded();
				}
			}
		}
		DrawShadows(shaders);
		m_lightingDataUploaded = true;
	}
}

void Core::CreateGameObject(glm::vec3 _pos)
{
	m_gameObjects.push_back(std::make_shared<GameObject>(shared_from_this(),_pos));
}


void Core::DrawShadows(std::vector<std::weak_ptr<Shader>> _shaders)
{
	glCullFace(GL_FRONT);

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0, 0, 1024, 1024);
	glBindFramebuffer(GL_FRAMEBUFFER, m_shadowFBO->GetDepthMapFBO());
	glClear(GL_DEPTH_BUFFER_BIT);
	
	for (std::shared_ptr<GameObject> g : m_gameObjects)
	{
		g->Draw(m_resources->Get<Shader>("Depth Shader"));
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glViewport(0, 0, 1600, 900);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	typedef std::map<std::string, std::shared_ptr<Shader>>::iterator iterator;

	for (std::weak_ptr<Shader> s : _shaders)
	{
		s.lock()->Use();
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, m_shadowFBO->GetDepthMapTex());
	}

	glCullFace(GL_BACK);
}

void Core::Draw()
{
	for (std::shared_ptr<GameObject> g : m_gameObjects)
	{
		g->Draw();
	}

	//m_resources->Get<Shader>("Debug Depth Shader")->Use();
	//renderQuad();
}

void Core::renderQuad()
{
	unsigned int quadVAO = 0;
	unsigned int quadVBO;
	if (quadVAO == 0)
	{
		float quadVertices[] = {
			// positions        // texture Coords
			-1.0f,  -0.3f, 0.0f, 0.0f, 1.0f,
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			-0.3f,  -0.3f, 0.0f, 1.0f, 1.0f,
			-0.3f, -1.0f, 0.0f, 1.0f, 0.0f,
		};
		// setup plane VAO
		glGenVertexArrays(1, &quadVAO);
		glGenBuffers(1, &quadVBO);
		glBindVertexArray(quadVAO);
		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	}
	glBindVertexArray(quadVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}
