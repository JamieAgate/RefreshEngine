#ifndef _FRAMEBUFFER_H_
#define _FRAMEBUFFER_H_

#include "glew.h"
#include <exception>

class FrameBuffer
{
public:
	FrameBuffer();
	~FrameBuffer();

	void GenerateShadowMap(const unsigned int _screenW, const unsigned int _screenH);

	GLuint GetDepthMapFBO() { return m_depthMapFBO; }
	GLuint GetDepthMapTex() { return m_depthMap; }

private:
	GLuint m_depthMapFBO;
	GLuint m_depthMap;
};

#endif // !_FRAMEBUFFER_H_


