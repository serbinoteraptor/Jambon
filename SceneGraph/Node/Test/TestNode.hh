#pragma once
#include <SceneGraph/Node/SceneNode.hh>
#include <list>

class TestNode : public SceneNode
{
public:
  static const std::vector<GLfloat> bdv;
  std::vector<GLfloat> color;
  GLuint m_vertexBuffer;
  GLuint m_colorBuffer;
  GLuint m_programID;
  GLuint m_MatrixID;

public:
  TestNode(unsigned char rgb = 0x02);
  ~TestNode();

  bool VRender(Scene * pScene) override;
  void VOnUpdate(Scene * pScene, const double elapsedTime) override;
};
