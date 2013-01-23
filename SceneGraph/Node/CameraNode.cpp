#include "CameraNode.h"



CameraNode::CameraNode(const glm::vec3 & pos,
                       GLfloat persp,
                       GLfloat ratio,
                       GLfloat near,
                       GLfloat far) : SceneNode("Camera", SceneNodeProperties::RenderPass::RenderPass_0, glm::mat4(1.0f))
{
  m_bIsActive = true;

  m_horizontalAngle = 45.0f;
  m_verticalAngle = 0.0f;

  m_position = pos;
  m_FoV = persp;
  m_speed = 3.0f;
  m_mouseSpeed = 0.005f;

  m_Projection =  glm::perspective(m_FoV, ratio, near, far);

  // Direction : Spherical coordinates to Cartesian coordinates conversion
  glm::vec3 direction(
    cos(m_verticalAngle) * sin(m_horizontalAngle),
    sin(m_verticalAngle),
    cos(m_verticalAngle) * cos(m_horizontalAngle)
    );

  // Right vector
  glm::vec3 right = glm::vec3(
    sin(m_horizontalAngle - 3.14f/2.0f),
    0,
    cos(m_horizontalAngle - 3.14f/2.0f)
    );

  // Up vector
  glm::vec3 up = glm::cross( right, direction );

  m_View = glm::lookAt(pos, pos + direction, up);
}

void CameraNode::VOnUpdate(Scene * pScene, const double elapsedTime)
{
  float fElapsedTime = (GLfloat) elapsedTime;

  //	Get mouse position.
  int xpos, ypos;
  glfwGetMousePos(&xpos, &ypos);

  // Reset mouse position for next frame.
  //	TODO : Fix that cheaty hard coded dimensions.
  glfwSetMousePos(1024/2, 768/2);

  // Compute new orientation
  m_horizontalAngle += m_mouseSpeed * float(1024/2 - xpos );
  m_verticalAngle   += m_mouseSpeed * float( 768/2 - ypos );

  // Direction : Spherical coordinates to Cartesian coordinates conversion
  glm::vec3 direction(
    cos(m_verticalAngle) * sin(m_horizontalAngle),
    sin(m_verticalAngle),
    cos(m_verticalAngle) * cos(m_horizontalAngle)
    );

  // Right vector
  glm::vec3 right = glm::vec3(
    sin(m_horizontalAngle - 3.14f/2.0f),
    0,
    cos(m_horizontalAngle - 3.14f/2.0f)
    );

  // Up vector
  glm::vec3 up = glm::cross( right, direction );

  // Move forward
  if (glfwGetKey( GLFW_KEY_UP ) == GLFW_PRESS){
    m_position += direction * fElapsedTime * m_speed;
  }
  // Move backward
  if (glfwGetKey( GLFW_KEY_DOWN ) == GLFW_PRESS){
    m_position -= direction * fElapsedTime * m_speed;
  }
  // Strafe right
  if (glfwGetKey( GLFW_KEY_RIGHT ) == GLFW_PRESS){
    m_position += right * fElapsedTime * m_speed;
  }
  // Strafe left
  if (glfwGetKey( GLFW_KEY_LEFT ) == GLFW_PRESS){
    m_position -= right * fElapsedTime * m_speed;
  }

  float FoV = m_FoV - 5 * glfwGetMouseWheel();

  // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
  m_Projection = glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 100.0f);
  // Camera matrix
  m_View       = glm::lookAt(
    m_position,           // Camera is here
    m_position+direction, // and looks here : at the same position, plus "direction"
    up                  // Head is up (set to 0,-1,0 to look upside-down)
    );
}
