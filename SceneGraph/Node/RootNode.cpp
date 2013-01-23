#include "RootNode.h"

RootNode::RootNode() : SceneNode("Root", SceneNodeProperties::RenderPass::RenderPass_0, glm::mat4(1.0f))
{
  m_Children.reserve(SceneNodeProperties::RenderPass::RenderPass_Last);

  SceneNode * staticGroup = new SceneNode("Static", SceneNodeProperties::RenderPass::RenderPass_Static, glm::mat4(1.0f));
  m_Children.push_back(staticGroup);

  SceneNode * actorGroup = new SceneNode("Actors", SceneNodeProperties::RenderPass::RenderPass_Actor, glm::mat4(1.0f));
  m_Children.push_back(actorGroup);

  SceneNode * skyGroup = new SceneNode("Sky", SceneNodeProperties::RenderPass::RenderPass_Sky, glm::mat4(1.0f));
  m_Children.push_back(skyGroup);
}

bool RootNode::VAddChild(ISceneNode * kid)
{
  ISceneNode * group = m_Children[kid->VGetPorps()->GetRenderPass()];
  if(group)
  {
    group->VAddChild(kid);
    //static_cast<SceneNode*>(kid)->m_pParent = group;
    return true;
  }

  return false;
}
bool RootNode::VRenderChildren(Scene * pScene)
{
  for (int pass = SceneNodeProperties::RenderPass::RenderPass_0; pass < SceneNodeProperties::RenderPass::RenderPass_Last; ++pass)
  {
    m_Children[pass]->VRenderChildren(pScene);
  }

  return true;
}
