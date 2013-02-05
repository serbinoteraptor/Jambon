#pragma once

#include <GLHeaders.hh>

// Forwards.
class Scene;
class SceneNodeProperties;

class ISceneNode
{
protected:

public:
  //	Update loop.
  virtual void VOnUpdate(Scene *pScene, const double elapsedTime) = 0;

  //	Rendering methods.
  virtual bool VIsVisible(Scene *pScene) const = 0;
  virtual bool VPreRender(Scene *pScene) = 0;
  virtual bool VRender(Scene *pScene) = 0;
  virtual bool VRenderChildren(Scene *pScene) = 0;
  virtual bool VPostRender(Scene *pScene) = 0;

  virtual const SceneNodeProperties *const VGetPorps() const = 0;
  virtual bool VAddChild(ISceneNode *kid) = 0;
  //	Transformations.
  virtual void VSetTransform(const glm::mat4 & to) = 0;
  virtual void VRotate(GLfloat angle, const glm::detail::tvec3<GLfloat> &v) = 0;
  virtual void VTranslate(const glm::detail::tvec3<GLfloat> &v) = 0;
  virtual void VTranslate(GLfloat x, GLfloat y, GLfloat z) = 0;
  virtual void VScale(const glm::detail::tvec3<GLfloat> &v) = 0;
  virtual void VScale(GLfloat x, GLfloat y, GLfloat z) = 0;

  virtual ~ISceneNode() {};
};
