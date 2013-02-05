#pragma once

#include "SceneGraph/Interface/ISceneNode.hh"
#include "SceneGraph/Interface/SceneNodeProperties.hh"

#include <vector>
#include <iostream>

class Scene;

typedef std::vector<ISceneNode*> SceneNodeList;

class SceneNode : public ISceneNode
{
  //	Allow Scene to access every SceneNode's member, even .hhe private ones.
  friend class Scene;

protected :
  SceneNodeList	       m_children;	//	List of the node .hhildren.
  SceneNode	      *m_pParent;		//	Parent in .hhe SceneGra.hh.
  SceneNodeProperties  m_Props;		//	Node properties.

public :
  SceneNode(std::string name,
              SceneNodeProperties::RenderPass renderPass,
              const glm::mat4 & to)
  {
    m_pParent = NULL;
    m_Props.m_Model = to;
    m_Props.m_Name = name;
    m_Props.m_RenderPass = renderPass;
    VSetTransform(to);
  }

  virtual ~SceneNode();

  //	Getters.
  virtual const SceneNodeProperties * const VGetPorps() const { return &m_Props; }

  //	Update loop.
  virtual void VOnUpdate(Scene * pScene, const double elapsedTime);

  //	Render me.hhods.
  virtual bool VIsVisible(Scene * pScene) const;
  virtual bool VPreRender(Scene * pScene);
  virtual bool VRender(Scene * pScene);
  virtual bool VRenderChildren(Scene * pScene);
  virtual bool VPostRender(Scene * pScene);

  //	Scene gra.hh management.
  virtual bool VAddChild(ISceneNode* kid);

  //	Transformations.
  virtual void VSetTransform(const glm::mat4 & to) { m_Props.Transform(to); };
  virtual void VRotate(GLfloat angle, const glm::detail::tvec3<GLfloat> &v) { m_Props.Rotate(angle, v); }
  virtual void VTranslate(const glm::detail::tvec3<GLfloat> &v) { m_Props.Translate(v); }
  virtual void VTranslate(GLfloat x, GLfloat y, GLfloat z) { m_Props.Translate(glm::detail::tvec3<GLfloat>(x, y, z)); }
  virtual void VScale(const glm::detail::tvec3<GLfloat> &v) { m_Props.Scale(v); }
  virtual void VScale(GLfloat x, GLfloat y, GLfloat z) { m_Props.Scale(glm::detail::tvec3<GLfloat>(x, y, z)); }
};
