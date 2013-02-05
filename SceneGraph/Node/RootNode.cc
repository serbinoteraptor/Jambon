#include "RootNode.hh"

RootNode::RootNode() : SceneNode("Root", SceneNodeProperties::RenderPass::RenderPass_0, glm::mat4(1.0f))
{
  m_children.reserve(SceneNodeProperties::RenderPass::RenderPass_Last);

  SceneNode * staticGroup = new SceneNode("Static", SceneNodeProperties::RenderPass::RenderPass_Static, glm::mat4(1.0f));
  m_children.push_back(staticGroup);

  SceneNode * actorGroup = new SceneNode("Actors", SceneNodeProperties::RenderPass::RenderPass_Actor, glm::mat4(1.0f));
  m_children.push_back(actorGroup);

  SceneNode * skyGroup = new SceneNode("Sky", SceneNodeProperties::RenderPass::RenderPass_Sky, glm::mat4(1.0f));
  m_children.push_back(skyGroup);
}

bool RootNode::VAddChild(ISceneNode * kid)
{
  ISceneNode* group = m_children[kid->VGetPorps()->GetRenderPass()];
  if(group)
  {
    return group->VAddChild(kid);
    //static_cast<SceneNode*>(kid)->m_pParent = group;
  }

  return false;
}
bool RootNode::VRenderChildren(Scene * pScene)
{
  for (int pass = SceneNodeProperties::RenderPass::RenderPass_0;
       pass < SceneNodeProperties::RenderPass::RenderPass_Last;
       ++pass)
  {
    m_children[pass]->VRenderChildren(pScene);
  }

  return true;
}
