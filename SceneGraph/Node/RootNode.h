#pragma once

#include "SceneGraph/Node/SceneNode.h"

class RootNode : public SceneNode
{
public :
  RootNode();
  virtual bool VAddChild(ISceneNode * kid);
  virtual bool VRenderChildren(Scene * pScene);
  virtual bool VIsVisible(Scene * pScene) const { return true; }
};
