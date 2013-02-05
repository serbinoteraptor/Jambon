#ifndef CUBENODE_HPP
# define CUBENODE_HPP

#include <SceneGraph/Node/SceneNode.hh>
#include <SceneGraph/Scene/Scene.hh>

class CubeNode:
  public SceneNode
{
protected:
  GLuint m_vertexBuffer;
  GLuint m_colorBuffer;
  GLuint m_programID;
  GLuint m_MatrixID;
  GLfloat color[9];

public:
  CubeNode();
  virtual ~CubeNode();

  void VOnUpdate(Scene * pScene, const double elapsedTime) override;
  bool VRender(Scene * pScene) override;

public:
  static const std::vector<GLfloat> bdv;
};


#endif
