#include "stdafx.h"
#include "..\Header\Scene_Ending.h"

#include "Export_Function.h"

CScene_Ending::CScene_Ending(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CScene(pGraphicDev, SCENE_TYPE::ENDING)
{
}

CScene_Ending::~CScene_Ending()
{
}

HRESULT CScene_Ending::Ready_Scene()
{
	FAILED_CHECK_RETURN(Ready_Prototype(), E_FAIL);

	return S_OK;
}

Engine::_int CScene_Ending::Update_Scene(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Scene(fTimeDelta);

	return iExit;
}

void CScene_Ending::LateUpdate_Scene()
{
	__super::LateUpdate_Scene();
}

void CScene_Ending::Render_Scene()
{

}

void CScene_Ending::Free()
{
	__super::Free();
}

CScene_Ending* CScene_Ending::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CScene_Ending* pInstance = new CScene_Ending(pGraphicDev);

	if (FAILED(pInstance->Ready_Scene()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Scene Ending Create Failed");
		return nullptr;
	}

	return pInstance;
}

HRESULT CScene_Ending::Ready_Prototype()
{

	return S_OK;
}

