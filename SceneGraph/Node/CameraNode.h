#pragma once

#include <GLHeaders.h>
#include "SceneGraph/Node/SceneNode.h"

class CameraNode : public SceneNode
{
private :
  bool		m_bIsActive;
  glm::mat4	m_Projection;
  glm::mat4	m_View;

  glm::vec3	m_position;

  float		m_horizontalAngle;
  float		m_verticalAngle;
  float		m_FoV;

  //	Mouse values.
  float m_speed; // 3 units / second
  float m_mouseSpeed;

public :
  glm::mat4 const& GetProjection(void) const { return m_Projection; }
  glm::mat4 const& GetView(void) const { return m_View; }

  CameraNode(const glm::vec3 & pos = glm::vec3(1.0f),
             GLfloat persp = 45.0f,
             GLfloat ratio = (4.0f / 3.0f),
             GLfloat near = 0.001f,
             GLfloat far = 100000.0f);

  //XXX: Add setters to persp, ratio, near, far.
  virtual void VOnUpdate(Scene * pScene, const double elapsedTime);

  //	Rendering methods.
  virtual bool VIsVisible(Scene * pScene) { return m_bIsActive; }
  virtual bool VPreRender(Scene * pScene) { return true; }
  virtual bool VRender(Scene * pScene) { return true; }
  virtual bool VRenderChildren(Scene * pScene) { return true; }
  virtual bool VPostRender(Scene * pScene) { return true; }

  virtual bool VAddChild(ISceneNode * kik) { return false; }
  virtual void VScale(const glm::detail::tvec3<GLfloat> &v) { return; }

  virtual ~CameraNode() {};
};
