#pragma once
#include <GLHeaders.hh>
#include "ShaderManager/shader.hh"
#include "log.hh"
class SceneNode;

#include <string>


class SceneNodeProperties
{
  //	Allow SceneNode to access every SceneNodeProperties's member, even the private ones.
  friend class SceneNode;

public :

  //	Allow SceneGraph optimisation for rendering.
  enum RenderPass
  {
    RenderPass_0,
    RenderPass_Static = RenderPass_0,
    RenderPass_Actor,
    RenderPass_Sky,
    RenderPass_Last
  };

protected :
  std::string m_Name;
  glm::mat4	m_Model;
  RenderPass	m_RenderPass;
  GLuint	m_Shader;

public :
  //	Getters.
  glm::mat4 const & GetModel() const { return m_Model; }
  RenderPass GetRenderPass() const { return m_RenderPass; }
  const char * Name() const { return m_Name.c_str(); }
  GLuint const GetShader() const { return m_Shader; }

  //	Transformations.
  void Transform(const glm::mat4 & m) { m_Model *= m; };
  void Rotate(GLfloat angle, const glm::detail::tvec3<GLfloat> v) { m_Model = glm::rotate(m_Model, angle, v); }
  void Translate(const glm::detail::tvec3<GLfloat> &v) { m_Model = glm::translate(m_Model, v); }
  void Scale(const glm::detail::tvec3<GLfloat> &v) { m_Model = glm::scale(m_Model, v); }
};
