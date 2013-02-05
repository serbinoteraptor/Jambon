#include "CubeNode.hh"

const std::vector<GLfloat> CubeNode::bdv =
{
  -1.0f, -1.0f, -1.0f,
  -1.0f, -1.0f,  1.0f,
  -1.0f,  1.0f,  1.0f,
   1.0f,  1.0f, -1.0f,
  -1.0f, -1.0f, -1.0f,
  -1.0f,  1.0f, -1.0f,
   1.0f, -1.0f,  1.0f,
  -1.0f, -1.0f, -1.0f,
   1.0f, -1.0f, -1.0f,
   1.0f,  1.0f, -1.0f,
   1.0f, -1.0f, -1.0f,
  -1.0f, -1.0f, -1.0f,
  -1.0f, -1.0f, -1.0f,
  -1.0f,  1.0f,  1.0f,
  -1.0f,  1.0f, -1.0f,
   1.0f, -1.0f,  1.0f,
  -1.0f, -1.0f,  1.0f,
  -1.0f, -1.0f, -1.0f,
  -1.0f,  1.0f,  1.0f,
  -1.0f, -1.0f,  1.0f,
   1.0f, -1.0f,  1.0f,
   1.0f,  1.0f,  1.0f,
   1.0f, -1.0f, -1.0f,
   1.0f,  1.0f, -1.0f,
   1.0f, -1.0f, -1.0f,
   1.0f,  1.0f,  1.0f,
   1.0f, -1.0f,  1.0f,
   1.0f,  1.0f,  1.0f,
   1.0f,  1.0f, -1.0f,
  -1.0f,  1.0f, -1.0f,
   1.0f,  1.0f,  1.0f,
  -1.0f,  1.0f, -1.0f,
  -1.0f,  1.0f,  1.0f,
   1.0f,  1.0f,  1.0f,
  -1.0f,  1.0f,  1.0f,
   1.0f, -1.0f,  1.0f,
};

CubeNode::CubeNode()
  : SceneNode{"cube", SceneNodeProperties::RenderPass_Actor, glm::mat4(1.0f)}
{
  //XXX: Hardcoded vertex file path.
  // m_programID = LoadShaders("SimpleTransform.vertexshader", "SingleColor.fragmentshader");
  m_programID = LoadShaders("TransformVertexShader.vertexshader", "ColorFragment.fragmentshader");
  m_MatrixID = glGetUniformLocation(m_programID, "MVP");

  // Red for each vertex.
  // color[0] = color[3] = color[6] = (float) ((rgb & 0x02) / 0x02);
  // color[1] = color[4] = color[7] = (float) ((rgb & 0x04) / 0x04);
  // color[2] = color[5] = color[8] = (float) ((rgb & 0x08) / 0x08);

  color[0] = color[3] = color[6] = 0.0f;
  color[1] = color[4] = color[7] = 1.0f;
  color[2] = color[5] = color[8] = 0.0f;


  glGenBuffers(1, &m_vertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, CubeNode::bdv.size() * sizeof (GLfloat), CubeNode::bdv.data(), GL_STATIC_DRAW);

  glGenBuffers(1, &m_colorBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
}

CubeNode::~CubeNode()
{
}

void
CubeNode::VOnUpdate(Scene * pScene, const double elapsedTime)
{
}

bool
CubeNode::VRender(Scene * pScene)
{
  glUseProgram(m_programID);

  glm::mat4 MVP = pScene->GetCamera().GetProjection() *
    pScene->GetCamera().GetView() *
    m_Props.GetModel();

  glUniformMatrix4fv(m_MatrixID, 1, GL_FALSE, &MVP[0][0]);

  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
  glVertexAttribPointer(
    0,                  // attribute. No particular reason for 0, but Umust match the layout in the shader.
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
  glDrawArrays(GL_TRIANGLES, 0, CubeNode::bdv.size() / 3); // From index 0 to 3 -> 1 triangle

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
}
