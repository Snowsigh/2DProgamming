#include "KOctree.h"
 
int main()
{	
	KOctree m_octree;
	m_octree.Init(KVector3(300, 300, 300));
	m_octree.AddObject(KVector3(35, 35, 35), KVector3(50, 50, 50));
	m_octree.AddObject(KVector3(0, 0, 0), KVector3(20, 20, 20));
	m_octree.AddObject(KVector3(100, 100, 50), KVector3(150, 125, 70));
	m_octree.AddObject(KVector3(50, 50, 70), KVector3(100, 100, 100));
	m_octree.AddObject(KVector3(35, 35, 35), KVector3(100, 100, 100));
	
	m_octree.Show(m_octree.m_pRootNode);

	return 0;
}