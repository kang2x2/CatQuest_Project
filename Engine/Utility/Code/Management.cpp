#include "Export_Utility.h"


IMPLEMENT_SINGLETON(CManagement)

CManagement::CManagement() 
			: m_pCurScene(nullptr)
			, m_ePlayMode(PLAY_MODE::GAME)
			, m_eGameStatus(GAME_STATUS::PLAYING)
			, m_bDebug(FALSE)
			, m_bEnterInGame(FALSE)
			, m_ePrevSceneType(SCENE_TYPE::WORLD)
			, m_bStartEndingVideo(FALSE)
{
}

CManagement::~CManagement()
{
	Free();
}


_int CManagement::Update_Scene(const _float& fTimeDelta)
{
	if (nullptr == m_pCurScene)
		return -1;

	return m_pCurScene->Update_Scene(fTimeDelta);
}

void CManagement::LateUpdate_Scene()
{
	if (nullptr == m_pCurScene)
		return;

	m_pCurScene->LateUpdate_Scene();
}

void CManagement::Render_Scene(LPDIRECT3DDEVICE9 pGraphicDev)
{
	Engine::Render_GameObject(pGraphicDev);

	if (m_pCurScene)
		m_pCurScene->Render_Scene();
}

CGameObject * CManagement::Get_GameObject(const OBJ_TYPE & _eObjType, const _tchar * pObjTag)
{
	return m_pCurScene->Get_GameObject(_eObjType, pObjTag);
}

CComponent * CManagement::Get_Component(const OBJ_TYPE& _eObjType, const _tchar * pObjTag, const COMPONENT_TYPE& _eComponentType, COMPONENTID eID)
{
	if (nullptr == m_pCurScene)
		return nullptr;

	return m_pCurScene->Get_Component(_eObjType, pObjTag, _eComponentType, eID);
}

CGameObject* CManagement::Get_Player()
{
	return Get_GameObject(OBJ_TYPE::PLAYER, L"Player");
}

CLayer * CManagement::Get_Layer(const OBJ_TYPE& _eType)
{
	return 	m_pCurScene->Get_Layer(_eType);
}

HRESULT CManagement::Set_Scene(CScene * pScene)
{
	Safe_Release(m_pCurScene);
	
	m_pCurScene = pScene;

	return S_OK;
}

HRESULT	CManagement::Change_Scene(CScene* _pScene)
{
	// ���� �����ӿ� Ŭ�󿡼� ���� �����Ǿ�, ���� �������� �� ������ �κп��� ������ ���� �Ű������� �Ͽ� �ش� �Լ��� ȣ�� �Ǿ���.

	// 0. �츱 ������Ʈ���� ó���Ѵ�.
	vector<CGameObject*>& vecMaintain = m_pCurScene->Get_MaintainObj();

	for (int i = 0; i < vecMaintain.size(); ++i)
		CEventMgr::GetInstance()->Add_Obj(vecMaintain[i]->Get_Name(), vecMaintain[i]);

	m_ePrevSceneType = m_pCurScene->Get_SceneType();
	// 1. ���� ���� �����Ѵ�
	Safe_Release(m_pCurScene);

	// 2. ���� ���� �����Ѵ�
	m_pCurScene = _pScene;
	return S_OK;
}

HRESULT CManagement::Add_Object(const OBJ_TYPE & _eObjType, const _tchar * _pObjTag, CGameObject* _pObj)
{
	FAILED_CHECK_RETURN(m_pCurScene->Add_Object(_eObjType, _pObjTag, _pObj), E_FAIL);

	return S_OK;
}

void CManagement::Free()
{
	Safe_Release(m_pCurScene);
}
