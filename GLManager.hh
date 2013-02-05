#pragma once

#include "GLHeaders.hh"
#include "SceneGraph/Scene/Scene.hh"
#include <system_error>
#include "log.hh"

#define FPS_TIME_RATIO	0.0166666667	//	1/60

class GLManager
{
private :
  static GLManager * m_pManager;
  GLManager() { m_pScene = 0;}
  ~GLManager();

  size_t  width, height;
  Scene  *m_pScene;

  // I don't know why, but it's necessary. If not present, no display.
  GLuint  m_VertexArrayID;

  // Blur.
  GLuint  fbo, fbo_texture, rbo_depth;

  // Square : screen.
  GLuint  vbo_fbo_vertices;
  GLfloat fbo_vertices[8];
  GLuint  m_BlurShader;


  bool InitBlur();
  void ApplyBlur();
  void DeleteBlur();

public :
  static GLManager * GetInstance(void);
  Scene * GetCurrentScene(void) { return m_pScene; }
  static void Kill();
  int InitOpenGL(size_t _width = WIDTH, size_t _height = HEIGHT, const char * title = "OpenGLWindow");
  void Loop();
  bool AddNode(std::string const& name)
  {
    if(m_pScene)
      return (m_pScene->AddNode(name));

    return false;
  }

  bool AddNode(ISceneNode* kid)
  {
    if(m_pScene)
      return (m_pScene->AddNode(kid));

    return false;
  }

private :

  void CreateScene();
  void DeleteScene();
};
