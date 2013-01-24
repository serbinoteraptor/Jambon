#pragma once

#include <SceneGraph/Node/SceneNode.h>

class TestNode : public SceneNode
{
protected:
  GLfloat bdv[9];
  GLfloat color[9];
  GLuint m_vertexBuffer;
  GLuint m_colorBuffer;
  GLuint m_programID;
  GLuint m_MatrixID;

public:
  TestNode(GLfloat xx, GLfloat xy, GLfloat xz, GLfloat yx, GLfloat yy, GLfloat yz, GLfloat zx, GLfloat zy, GLfloat zz);
  ~TestNode();

  bool VRender(Scene * pScene) override;
  void VOnUpdate(Scene * pScene, const double elapsedTime) override;
};
