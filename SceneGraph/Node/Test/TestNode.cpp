#include "TestNode.h"
#include "SceneGraph/Scene/Scene.h"

TestNode::TestNode(GLfloat xx, GLfloat xy, GLfloat xz, GLfloat yx, GLfloat yy, GLfloat yz, GLfloat zx, GLfloat zy, GLfloat zz) :
  SceneNode("Triangle", SceneNodeProperties::RenderPass_Actor, glm::mat4(1.0f))
{
  //XXX: Hardcoded vertex file path.
  m_programID = LoadShaders("SimpleTransform.vertexshader", "SingleColor.fragmentshader");
  m_MatrixID = glGetUniformLocation(m_programID, "MVP");

  // Store vertex coordonates.
  bdv[0] = xx;
  bdv[1] = xy;
  bdv[2] = xz;
  bdv[3] = yx;
  bdv[4] = yy;
  bdv[5] = yz;
  bdv[6] = zx;
  bdv[7] = zy;
  bdv[8] = zz;

  // Red for each vertex.
  color[0] = color[3] = color[6] = 1.0f;
  color[1] = color[4] = color[7] = 0.0f;
  color[2] = color[5] = color[8] = 0.0f;

  glGenBuffers(1, &m_vertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(bdv), bdv, GL_STATIC_DRAW);

  glGenBuffers(1, &m_colorBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
}

bool
TestNode::VRender(Scene * pScene)
{
  glUseProgram(m_programID);

  glm::mat4 MVP = pScene->GetCamera().GetProjection() *
                  pScene->GetCamera().GetView() *
                  m_Props.GetModel();

  glUniformMatrix4fv(m_MatrixID, 1, GL_FALSE, &MVP[0][0]);

  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
  glVertexAttribPointer(
    0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
    3,                  // size
    GL_FLOAT,           // type
    GL_FALSE,           // normalized?
    0,                  // stride
    (void*)0            // array buffer offset
    );


  //// 2nd attribute buffer : colors
  //glEnableVertexAttribArray(1);
  //glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
  //glVertexAttribPointer(
  //	1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
  //	3,                                // size
  //	GL_FLOAT,                         // type
  //	GL_FALSE,                         // normalized?
  //	0,                                // stride
  //	(void*)0                          // array buffer offset
  //);

  // Draw the triangle.
  glDrawArrays(GL_TRIANGLES, 0, 3); // From index 0 to 3 -> 1 triangle

  glDisableVertexAttribArray(0);
  //glDisableVertexAttribArray(1);

  return true;
}

void
TestNode::VOnUpdate(Scene * pScene, const double elapsedTime)
{
  (void) pScene;

  // Rotate at 60 rpm.
  VRotate(360 * elapsedTime / 1000, vec3(0.0f, 1.0f, 0.0f));
}

TestNode::~TestNode()
{
  // Cleanup VBO and shader
  glDeleteBuffers(1, &m_vertexBuffer);
  glDeleteBuffers(1, &m_colorBuffer);
}
