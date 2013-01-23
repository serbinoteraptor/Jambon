#include "SceneNode.h"

void SceneNode::VOnUpdate(Scene * pScene, const double elapsedTime)
{
  SceneNodeList::const_iterator it = m_Children.begin();
  SceneNodeList::const_iterator itEnd = m_Children.end();

  while(it != itEnd)
  {
    (*it)->VOnUpdate(pScene, elapsedTime);
    ++it;
  }
}

bool SceneNode::VIsVisible(Scene * pScene) const
{

  return true;
}

bool SceneNode::VPreRender(Scene * pScene)
{
  //glUseProgram(m_Props.m_Shader);

  return true;
}

bool SceneNode::VRender(Scene * pScene)
{
  return true;
}

bool SceneNode::VRenderChildren(Scene * pScene)
{
  SceneNodeList::const_iterator it = m_Children.begin();
  SceneNodeList::const_iterator itEnd = m_Children.end();

  while (it != itEnd)
  {
    if ((*it)->VPreRender(pScene))
    {
      (*it)->VRender(pScene);

      (*it)->VRenderChildren(pScene);
    }
    (*it)->VPostRender(pScene);

    ++it;
  }

  return true;
}

bool SceneNode::VPostRender(Scene * pScene)
{
  return true;
}

bool SceneNode::VAddChild(ISceneNode * kid)
{
  m_Children.push_back(kid);
  return true;
}
