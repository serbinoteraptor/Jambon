#include "SceneNode.hh"
#include "log.hh"


SceneNode:: ~SceneNode()
{
}

void SceneNode::VOnUpdate(Scene * pScene, const double elapsedTime)
{
  SceneNodeList::const_iterator it = m_children.begin();
  SceneNodeList::const_iterator itEnd = m_children.end();

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
  //glUseProgram(m_Props.m_shader);

  return true;
}

bool SceneNode::VRender(Scene * pScene)
{
  return true;
}

bool SceneNode::VRenderChildren(Scene * pScene)
{
  SceneNodeList::const_iterator it = m_children.begin();
  SceneNodeList::const_iterator itEnd = m_children.end();

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

bool
SceneNode::VAddChild(ISceneNode* kid)
{
  this->m_children.push_back(kid);

  return true;
}


bool SceneNode::VPostRender(Scene * pScene)
{
  return true;
}
