#pragma once

#include <SceneGraph/Node/CameraNode.h>
#include <SceneGraph/Node/RootNode.h>
#include <SceneGraph/Node/Test/TestNode.h>


class Scene
{
private:
	CameraNode	 m_Camera;
	RootNode	 m_RootNode;
	ISceneNode	*m_lastAddedNode;

public :
	CameraNode & GetCamera (void) { return m_Camera; }
	bool Render();
	bool Update(const double elapsedTime);
	bool AddNode(ISceneNode * node);
	bool AddNode(const char * name);

	ISceneNode * GetLastAddedNode () { return m_lastAddedNode; }
};
