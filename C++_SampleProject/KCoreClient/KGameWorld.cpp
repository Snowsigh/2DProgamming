#include "KGameWorld.h"
#include <string>
#include <KObjectMgr.h>
#include <KInput.h>
bool KGameWorld::CreateModelType()
{
	KShader* pVShader = I_Shader.CreateVertexShader(m_pd3dDevice, L"Shader.txt", "VS");
	KShader* pPShader = I_Shader.CreatePixelShader(m_pd3dDevice, L"Shader.txt", "PSAlphaBlend");
	
	

/// <summary>
/// 배경이미지
/// </summary>
/// <param name="file"></param>
/// <returns></returns>
	{
		KImageObject* obj = new KImageObject;

		obj->Init();
		obj->SetRectDraw({ 0, 0, g_rtClient.right,g_rtClient.bottom });
		obj->SetPosition(KVector2((g_rtClient.right / 2), (g_rtClient.bottom / 2)));
		obj->m_pColorTex = m_pBG;
		obj->m_pMaskTex = nullptr;
		obj->m_pVShader = pVShader;
		obj->m_pPShader = pPShader;
		if (!obj->Create(m_pd3dDevice, m_pContext))
		{
			return false;

		}
		obj->SetCollisionType(KCollisionType::Ignore, KSelectType::Select_Ignore);
		m_UIobj.insert(std::make_pair(L"bk", obj));
	}
	
	
/// <summary>
///  오브젝트
/// </summary>
/// <param name="file"></param>
/// <returns></returns>
	{
		KEtcObject* bks = new KEtcObject;
		bks->Init();
		bks->SetRectDraw({ 0,0, 500 , 150 });
		bks->SetPosition(KVector2((400), (g_rtClient.bottom - 100)));
		bks->m_pColorTex = nullptr;
		bks->m_pMaskTex = nullptr;
		bks->m_pVShader = pVShader;
		bks->m_pPShader = pPShader;
		if (!bks->Create(m_pd3dDevice, m_pContext
						,nullptr, L"../../Data/Stage/Stage1_Dust.png"))
		{
			return false;
		}
		bks->SetCollisionType(KCollisionType::Ignore, KSelectType::Select_Overlap);
		m_EtcObj.insert(std::make_pair(L"Dust", bks));
	}
/// <summary>
/// 플레이어 캐릭터
/// </summary>
/// <param name="file"></param>
/// <returns></returns>

	PlayerObj.SetRectDraw({ 0,0, 150 , 155 });
	PlayerObj.SetPosition(KVector2((200), (500)));
	PlayerObj.m_pColorTex = PlayerObj.PlayerAnimation->GetTex();
	PlayerObj.m_pMaskTex = nullptr;
	PlayerObj.m_pVShader = nullptr;
	PlayerObj.m_pPShader = nullptr;
	if (!PlayerObj.Create(m_pd3dDevice, m_pContext,L"PlayerShader.txt"))
	{
		return false;
	}

	PlayerObj.SetCollisionType(KCollisionType::Ignore, KSelectType::Select_Overlap);

	/// <summary>
	///  캐릭터
	/// </summary>
	/// <param name="file"></param>
	/// <returns></returns>	
	
	MonsterObj.SetRectDraw({ 0,0, 250 , 300 });
	MonsterObj.SetPosition(KVector2((800), (500)));
	MonsterObj.m_pColorTex = MonsterObj.m_kAnimation->GetTex();
	MonsterObj.m_pMaskTex = nullptr;
	MonsterObj.m_pVShader = nullptr;
	MonsterObj.m_pPShader = nullptr;
	if (!MonsterObj.Create(m_pd3dDevice, m_pContext, L"PlayerShader.txt"))
	{
		return false;
	}

	MonsterObj.SetCollisionType(KCollisionType::Ignore, KSelectType::Select_Overlap);

	/// <summary>
	/// 버튼
	/// </summary>
	/// <param name="file"></param>
	/// <returns></returns>
	//KButtonObject* btnObj = new KButtonObject;
	//btnObj->Init();
	//btnObj->m_rtOffset = { 0, 0, 0, 0 };
	//btnObj->SetRectDraw({ 0,0, 334,82 });
	//btnObj->SetPosition(KVector2(g_rtClient.right / 2.0f, g_rtClient.bottom / 2.0f));
	//KTexture* pTex = I_Texture.Load(L"../../data/ui/main_start_nor.png");
	//KSound* pSound = I_Sound.Load("../../data/Sound/00_Menu.MP3");
	//// 가변인자를 통해서 생성자 직접 호출
	//btnObj->m_pStatePlayList.emplace_back(pTex, pSound);
	//pTex = I_Texture.Load(L"../../data/ui/main_start_pus.png");
	//pSound = I_Sound.Load("../../data/Sound/FootStepSound.wav");
	//// 가변인자를 통해서 생성자 직접 호출
	//btnObj->m_pStatePlayList.emplace_back(pTex, pSound);
	//pTex = I_Texture.Load(L"../../data/ui/main_start_sel.png");
	//pSound = I_Sound.Load("../../data/Sound/FootStepSound_2.wav");
	//// 가변인자를 통해서 생성자 직접 호출
	//btnObj->m_pStatePlayList.emplace_back(pTex, pSound);
	//pTex = I_Texture.Load(L"../../data/ui/main_start_dis.png");
	//pSound = I_Sound.Load("../../data/Sound/PianoSound_00.mp3");
	//// 가변인자를 통해서 생성자 직접 호출
	//btnObj->m_pStatePlayList.emplace_back(pTex, pSound);

	//if (!btnObj->Create(m_pd3dDevice, m_pContext,
	//	L"../../data/shader/DefaultUI.txt",
	//	L"../../data/main_start_nor.png"))
	//{
	//	return false;
	//}
	//btnObj->SetCollisionType(TCollisionType::Ignore, TSelectType::Select_Overlap);
	//I_UI.m_list.insert(std::make_pair(L"btnStart", btnObj));

	//// 새로운 모델을 생성해서 등록한다.
	//TUIModelComposed* pComposedObj = new TUIModelComposed;
	//pComposedObj->m_csName = L"TUIModelComposed";
	//TButtonObject* pDlgWindow = (TButtonObject*)I_UI.GetPtr(L"btnDlg")->Clone();
	//pDlgWindow->m_pParent = pComposedObj;
	//pDlgWindow->m_rtOffset = { 50, 50, 50, 50 };
	//pDlgWindow->SetRectDraw({ 0,0, g_rtClient.right / 3,g_rtClient.bottom / 3 });
	//pDlgWindow->SetPosition(TVector2(400, 300));
	//pComposedObj->Add(pDlgWindow);
	//TUIModel* pNewDlgBtn = I_UI.GetPtr(L"btnStart")->Clone();// new TButtonObject(*I_UI.GetPtr(L"btnStart"));
	//pNewDlgBtn->m_csName = L"btnStartClone_ComposedList";
	//pNewDlgBtn->m_pParent = pComposedObj;
	//pNewDlgBtn->SetRectDraw({ 0,0, 100,50 });
	//pNewDlgBtn->AddPosition(TVector2(0, 0));
	//pComposedObj->Add(pNewDlgBtn);
	//I_UI.m_list.insert(std::make_pair(L"dlgWindow", pComposedObj));
	return true;
}

bool KGameWorld::Load(std::wstring file)
{
	m_pBG = I_Texture.Load(L"../../Data/Stage/Stage1_Stage.png");
	PlayerObj.ActionTexInit();
	MonsterObj.ActionTexInit();
	CreateModelType();
	MonsterObj.Init();
	return true;
}

bool KGameWorld::Init()
{
	KWorld::Init();
	PlayerObj.Init();
	
	return false;
}

bool KGameWorld::Frame()
{
	if (m_bLoadzone && m_pNextWorld != nullptr)
	{
		I_ObjectMgr.Releae();
		m_pNextWorld->Load(L"zone.txt");
		KWorld::m_pWorld = m_pNextWorld;
	}
	//m_pBGSound->Frame();
	static int iIndex = 0;
	//if ( TInput::Get().GetKey(VK_F2) == KEY_PUSH)
	//{
	//	iIndex++;
	//	if (iIndex >= 10)
	//	{
	//		iIndex = 0;
	//	}
	//	auto data = m_UIObj.find(L"bk");
	//	if (data != m_UIObj.end())
	//	{
	//		data->second->m_pColorTex = m_pChangeColorTex[iIndex];			
	//	}		
	//}
	if (I_INPUT.GetKey(VK_F3) == KEY_PUSH)
	{

	}
	if (I_INPUT.GetKey(VK_F4) == KEY_PUSH)
	{

	}
	if (I_INPUT.GetKey(VK_F6) == KEY_PUSH)
	{

	}
	if (I_INPUT.GetKey(VK_F7) == KEY_PUSH)
	{

	}
	KWorld::Frame();
	PlayerObj.Frame();
	MonsterObj.Frame();

	return true;
	
}

bool KGameWorld::Render()
{
	KWorld::Render();
	PlayerObj.Render();
	MonsterObj.Render();
	return false;
}

bool KGameWorld::Release()
{
	KWorld::Release();
	PlayerObj.Release();
	MonsterObj.Release();
	return false;
}
