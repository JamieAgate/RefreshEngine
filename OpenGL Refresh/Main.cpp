#include "glew.h"
#include "Core.h"

#include <SDL.h>

#include <iostream>

#undef main

void GameLoop(SDL_Renderer* _renderer, SDL_Window* _window);
bool InitGL();

int main(int argc, char *argv[])
{
	const int SCREEN_WIDTH = 1600;
	const int SCREEN_HEIGHT = 900;
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_GLContext glcontext = NULL;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL could not Initialize. SDL_Error: %s\n", SDL_GetError());
	}
	else
	{

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		window = SDL_CreateWindow("OpenGL Refresh", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
		if (window == NULL)
		{
			printf("Window couldn't be created. SDL_Error %s\n", SDL_GetError());
		}
		else
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (renderer == NULL)//initialise renderer
			{
				printf("Renderer could not be created! SDL_ERROR %s\n", SDL_GetError());
			}
			else
			{
				glcontext = SDL_GL_CreateContext(window);

				if (InitGL())
				{
					GameLoop(renderer, window);
				}
			}
		}
	}
	SDL_DestroyRenderer(renderer);
	SDL_GL_DeleteContext(glcontext);
	SDL_DestroyWindow(window);
	SDL_Quit();
	system("PAUSE");
	return 0;
}

bool InitGL()
{
	glewExperimental = GL_TRUE;

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cerr << "Error: GLEW failed to initialise with message: " << glewGetErrorString(err) << std::endl;
		return false;
	}
	std::cout << "INFO: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;

	std::cout << "INFO: OpenGL Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "INFO: OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "INFO: OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "INFO: OpenGL Shading Language Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	return true;
}

void GameLoop(SDL_Renderer* _renderer, SDL_Window* _window)
{
	glEnable(GL_DEPTH_TEST);
	glCullFace(GL_BACK);

	std::shared_ptr<Core> core = std::make_shared<Core>();
	core->Init();

	bool quit = false;
	SDL_Event e;

	SDL_SetRelativeMouseMode(SDL_TRUE);

	while (!quit)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				quit = true;
		}

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		core->Update();
		core->Draw();

		SDL_GL_SwapWindow(_window);
	}
}