#include "TestNode.hh"
#include "SceneGraph/Scene/Scene.hh"

#include <log.hh>

const std::vector<GLfloat> TestNode::bdv =
{
  -1.0f, -1.0f, 0.0f,
  1.0f, -1.0f, 0.0f,
  0.0f,  1.0f, 0.0f,
};

TestNode::TestNode(unsigned char rgb)
  : SceneNode("Triangle", SceneNodeProperties::RenderPass_Actor, glm::mat4(1.0f))
  , color{{1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f}}
{
  //XXX: Hardcoded vertex file path.
  m_programID = LoadShaders("SimpleTransform.vertexshader", "SingleColor.fragmentshader");
  //m_programID = LoadShaders("SimpleTransform.vertexshader", "ColorFragment.fragmentshader");
  m_MatrixID = glGetUniformLocation(m_programID, "MVP");

  glGenBuffers(1, &m_vertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, bdv.size(), bdv.data(), GL_STATIC_DRAW);

  glGenBuffers(1, &m_colorBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer);
  glBufferData(GL_ARRAY_BUFFER, color.size(), color.data(), GL_STATIC_DRAW);
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


  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer);
  glVertexAttribPointer(
  	1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
  	3,                                // size
  	GL_FLOAT,                         // type
  	GL_FALSE,                         // normalized?
  	0,                                // stride
  	(void*)0                          // array buffer offset
  );

  // Draw the triangle.
  glDrawArrays(GL_TRIANGLES, 0, 3); // From index 0 to 3 -> 1 triangle

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);

  return true;
}

void
TestNode::VOnUpdate(Scene * pScene, const double elapsedTime)
{
  (void) pScene;

  // Rotate at 60 rpm.
  // this->VRotate(2 * PI * elapsedTime, vec3(0.0f, 1.0f, 0.0f));
}

TestNode::~TestNode()
{
  // Cleanup VBO and shader
  glDeleteBuffers(1, &m_vertexBuffer);
  glDeleteBuffers(1, &m_colorBuffer);
}
