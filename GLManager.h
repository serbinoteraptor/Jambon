#pragma once

#include "GLHeaders.h"
#include "SceneGraph/Scene/Scene.h"

#define FPS_TIME_RATIO	0.0166666667	//	1/60

class GLManager
{
private :
  static GLManager * m_pManager;
  GLManager() { m_pScene = 0;}
  ~GLManager();

  size_t		 width, height;
  Scene		*m_pScene;

  //	I don't know why, but it's necessary. If not present, no display.
  GLuint		m_VertexArrayID;

  //	Blur.
  GLuint	fbo, fbo_texture, rbo_depth;

  //	Square : screen.
  GLuint	vbo_fbo_vertices;
  GLfloat	fbo_vertices[8];
  GLuint	m_BlurShader;


  bool InitBlur();
  void ApplyBlur();
  void DeleteBlur();

public :
  static GLManager * GetInstance(void);
  Scene * GetCurrentScene(void) { return m_pScene; }
  static void Kill();
  int InitOpenGL(size_t _width = 1024, size_t _height = 768, const char * title = "OpenGLWindow");
  void Loop();
  bool AddNode(std::string const& name)
  {
    if(m_pScene)
      return (m_pScene->AddNode(name));
    else
      return false;
  }

  bool AddNode(ISceneNode * kid)
  {
    if(m_pScene)
      return (m_pScene->AddNode(kid));
    else
      return false;
  }

  ISceneNode * GetLastAddedNode()
  {
    return m_pScene->GetLastAddedNode();
  }
private :

  void CreateScene();
  void DeleteScene();
};
