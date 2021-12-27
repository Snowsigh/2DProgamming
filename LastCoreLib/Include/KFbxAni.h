#pragma once
#include "KStd.h"
#include "KMesh.h"
struct KWeight
{
	std::vector<int>     m_IndexList;
	std::vector<float>   m_WegihtList;
};
struct KSkinData
{
	std::vector<FbxNode*>  m_MatrixList;
	std::vector<KWeight>   m_VertexList;

};
class KFbxAni
{
private:
	FbxScene* m_pFbxS;
public:
	
	bool	m_bAnimPlay = false;
	float   m_fElpaseTime = 0.0f;
	int		m_iAnimIndex = 0;
	float m_fStartTime;
	float m_fEndTime;
	float m_fSampleTime;
public:
	bool	SetAni(FbxScene* obj);
	KMesh*		GetFindInedx(FbxNode* pNode, std::vector<KMesh*> pMeshList);
public:
	void	ParseAnimationNode(std::vector<KMesh*> pMeshList);
	void	ParseAnimation();
	void	ParseAnimStack(FbxString* szData);
	bool	ParseMeshSkinning(FbxMesh* pFbxMesh, KMesh* pMesh, KSkinData* pSkindata);
};

