#pragma once
#include "KModel.h"
const enum OBJECTCLASSTYPE {
	CLASS_GEOM = 0,
	CLASS_BONE,
	CLASS_DUMMY,
	CLASS_BIPED,
};
struct KLayer
{
	FbxLayerElementUV* pUV;
	FbxLayerElementVertexColor* pColor;
	FbxLayerElementNormal* pNormal;
	FbxLayerElementMaterial* pMaterial;
};

struct PNCTIW_VERTEX
{
	float   index[4];
	float   weight[4];
};
struct KAnimMatrix
{
	TMatrix   matAnimation[255];
};

class KMesh : public KModel
{
	int m_iMtrlRef;
public:
	std::vector<int>  m_iBoneList;
	KAnimMatrix   m_matAnimMatrix;
	ID3D11Buffer* m_pAnimCB;
	ID3D11Buffer* m_pIWVertrexBuffer;
public:
	std::vector<FbxNode*>	m_pFNodeList;
	std::vector<KMesh*> m_pMeshLinkList;
	std::vector<TMatrix>	m_matBindPoseList;
public:
	OBJECTCLASSTYPE     m_ClassType;
	std::wstring		m_szName;
	std::wstring		m_szParentName;
	int					m_iNumLayer;
	std::vector<KLayer> m_LayerList;
	TMatrix				m_matWorld;
	KMesh*				m_pParent;
	std::vector<KMesh*> m_pSubMesh;
	std::vector<TMatrix> m_AnimationTrack;
	FbxNode* m_pFbxNode;
	std::vector<PNCTIW_VERTEX>  m_WeightList;
public:
	FbxColor ReadColor(const FbxMesh* mesh,
		DWORD dwVertexColorCount, FbxLayerElementVertexColor* VertexColorSets,
		DWORD dwDCCIndex, DWORD dwVertexIndex);
	FbxVector4 ReadNormal(const FbxMesh* mesh,
		DWORD dwVertexNormalCount, FbxLayerElementNormal* VertexNormalSets,
		int controlPointIndex, int iVertexIndex);
	FbxVector2 ReadTextureCoord(FbxMesh* pFbxMesh, DWORD dwVertexTextureCount,
		FbxLayerElementUV* pUVSet, int vertexIndex, int uvIndex);
public:
public:
	virtual HRESULT		CreateConstantBuffer()override;
	virtual HRESULT		LoadShaderAndInputLayout(LPCWSTR vsFile, LPCWSTR psFile) override;
	virtual HRESULT		CreateVertexBuffer()override;
	virtual bool		PreRender()override;
public:
	INT GetRef()
	{
		return m_iMtrlRef;
	}
	bool SetRef(INT vValue)
	{
		m_iMtrlRef = vValue;
		return true;
	}
	bool Release() override
	{
		KModel::Release();
		for (auto data : m_pSubMesh)
		{
			data->Release();
			if (data)delete data;
		}
		if (m_pAnimCB)m_pAnimCB->Release();
		if (m_pIWVertrexBuffer)m_pIWVertrexBuffer->Release();
		return true;
	}


	
};

