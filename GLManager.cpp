#include "GLManager.h"

#include <stdio.h>
#include <stdlib.h>


GLManager * GLManager::m_pManager = NULL;

GLManager * GLManager::GetInstance(void)
{
	if (m_pManager == NULL)
		m_pManager = new GLManager();

	return m_pManager;
}

void GLManager::Kill()
{
	if (m_pManager != NULL)
	{
		delete m_pManager;
		m_pManager = NULL;
	}
}

GLManager::~GLManager()
{
	glDeleteVertexArrays(1, &m_VertexArrayID);

	DeleteScene();
}

int GLManager::InitOpenGL(size_t _width, size_t _height, const char * title)
{
	//	Initialise GLFW.
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        return -1;
    }

    glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);			//	x4 antialising.
    glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE,GL_TRUE);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);	//	3.3
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);	//	3.3
	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //	Open a window and create its OpenGL context, according to the dimensions.
    if( !glfwOpenWindow( _width, _height, 0,0,0,0, 32,0, GLFW_WINDOW ) )
    {
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        glfwTerminate();
        return -1;
    }

	//	Initialize GLEW.
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	width = _width;
	height = _height;

	//	Set the title of the window.S
	glfwSetWindowTitle(title);
	
	//	I don't know why, but it's necessary. If not present, no display.
	GLuint m_VertexArrayID;
	glGenVertexArrays(1, &m_VertexArrayID);
	glBindVertexArray(m_VertexArrayID);

	//	Ensure we can capture keys like arrows and escape.
	glfwEnable( GLFW_STICKY_KEYS );

	//	Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS); 

	// InitBlur();

	CreateScene();

	return 0;
}

bool GLManager::InitBlur()
{
	//	Init_resources.
	//	Create back-buffer, used for post-processing.

	//	Texture.
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &fbo_texture);
	glBindTexture(GL_TEXTURE_2D, fbo_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glBindTexture(GL_TEXTURE_2D, 0);

	//	Depth buffer.
	glGenRenderbuffers(1, &rbo_depth);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo_depth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	//	Framebuffer.
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fbo_texture, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo_depth);
	GLenum status;
	if ((status = glCheckFramebufferStatus(GL_FRAMEBUFFER)) != GL_FRAMEBUFFER_COMPLETE) {
		fprintf(stderr, "glCheckFramebufferStatus: error %p", status);
		return false;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//	v_coord
	//	fbo_texture
	m_BlurShader = LoadShaders("postproc.v.glsl", "postproc.f.glsl");
	
	if (m_BlurShader < 0)
		return false;

	//	Square : screen.
	fbo_vertices[0] = -1.0f;
	fbo_vertices[1] = -1.0f;
	fbo_vertices[2] =  1.0f;
	fbo_vertices[3] = -1.0f;
	fbo_vertices[4] = -1.0f;
	fbo_vertices[5] =  1.0f;
	fbo_vertices[6] =  1.0f;
	fbo_vertices[7] =  1.0f;

	glGenBuffers(1, &vbo_fbo_vertices);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_fbo_vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fbo_vertices), fbo_vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return true;
}

void GLManager::ApplyBlur()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glUseProgram(m_BlurShader);
	glBindTexture(GL_TEXTURE_2D, fbo_texture);

	GLuint uniform_fbo_texture = glGetUniformLocation(m_BlurShader, "fbo_texture");
	GLuint attribute_v_coord_postproc = glGetAttribLocation(m_BlurShader, "v_coord");

	glUniform1i(uniform_fbo_texture, /*GL_TEXTURE*/0);
	glEnableVertexAttribArray(attribute_v_coord_postproc);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_fbo_vertices);
	glVertexAttribPointer(
		attribute_v_coord_postproc,  // attribute
		2,                  // number of elements per vertex, here (x,y)
		GL_FLOAT,           // the type of each element
		GL_FALSE,           // take our values as-is
		0,                  // no extra data between each position
		0                   // offset of first element
		);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glDisableVertexAttribArray(attribute_v_coord_postproc);

	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void GLManager::DeleteBlur()
{
	glDeleteProgram(m_BlurShader);

	glDeleteRenderbuffers(1, &rbo_depth);
	glDeleteTextures(1, &fbo_texture);
	glDeleteFramebuffers(1, &fbo);
}

void GLManager::CreateScene()
{
	m_pScene = new Scene();
}

void GLManager::DeleteScene()
{
	if (m_pScene)
		delete m_pScene;

	m_pScene = 0;
}

void GLManager::Loop()
{
	//	Initialize lastTime.
	static double lastTime = glfwGetTime();
	static double fpsLocker = FPS_TIME_RATIO;

	//	Compute time difference between current and last frame.
	double currentTime = glfwGetTime();
	float deltaTime = 1000.0f * float(currentTime - lastTime);
	
	//	Update components.
	m_pScene->Update(deltaTime);

	//	Substract delta and check if we need to redraw scene.
	fpsLocker -= deltaTime;
	if (fpsLocker < 0)
	{
		//	Clear the screen.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//	Set default color.
		glClearColor(0.0f, 0.0f, 0.2f, 0.0f);

		m_pScene->Render();

		fpsLocker = FPS_TIME_RATIO;

		// ApplyBlur();

		//	Swap buffers.
		glfwSwapBuffers();
	}

	lastTime = glfwGetTime();
}