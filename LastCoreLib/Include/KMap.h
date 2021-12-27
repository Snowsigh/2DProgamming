#pragma once
#include "KModel.h"
#include "KShape.h"
struct KMapinfo
{
    int m_iNumRow; 
    int m_iNumCol;
    int m_iNumRowCell;
    int m_iNumColCell;
    int m_iNumVertex;
    float m_fCellDistance;
};
class KMap : public KModel
{
public:
    KMapinfo m_mapInfo;
public:
    bool Load(KMapinfo& pinfo, ID3D11DeviceContext* pContext, LPCWSTR vsFile, LPCWSTR psFile);
    bool CreateVertexData() override;
    bool CreateIndexData() override;
    

};
class KMiniMap : public KPlane
{
public:
    bool		LoadTexture()
    {
       m_kTex.LoadTexture(L"../../Data/kgcabk.bmp");
    }
    bool CreateVertexData()
    {
        m_VertexList.resize(4);

        m_VertexList[0].pos = TVector3(-1.0f, 1.0f, 0.0f);
        m_VertexList[0].normal = TVector3(0.0f, 0.0f, -1.0f);
        m_VertexList[0].color = TVector4(1.0f, 1.0f, 1.0f, 1.0f);
        m_VertexList[0].tex = TVector2(0.0f, 0.0f);

        m_VertexList[1].pos = TVector3(-0.5f, 1.0f, 0.0f);
        m_VertexList[1].normal = TVector3(0.0f, 0.0f, -1.0f);
        m_VertexList[1].color = TVector4(1.0f, 1.0f, 1.0f, 1.0f);
        m_VertexList[1].tex = TVector2(1.0f, 0.0f);


        m_VertexList[2].pos = TVector3(-1.0f, 0.5f, 0.0f);
        m_VertexList[2].normal = TVector3(0.0f, 0.0f, -1.0f);
        m_VertexList[2].color = TVector4(1.0f, 1.0f, 1.0f, 1.0f);
        m_VertexList[2].tex = TVector2(0.0f, 1.0f);


        m_VertexList[3].pos = TVector3(-0.5f, 0.5f, 0.0f);
        m_VertexList[3].normal = TVector3(0.0f, 0.0f, -1.0f);
        m_VertexList[3].color = TVector4(1.0f, 1.0f, 1.0f, 1.0f);
        m_VertexList[3].tex = TVector2(1.0f, 1.0f);
        return true;
    }


};

