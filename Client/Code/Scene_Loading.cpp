#include "stdafx.h"
#include "..\Header\Scene_Loading.h"

#include "Export_Function.h"

CScene_Loading::CScene_Loading(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CScene(pGraphicDev, SCENE_TYPE::LOADING)
{
}

CScene_Loading::~CScene_Loading()
{
}

HRESULT CScene_Loading::Ready_Scene()
{
	FAILED_CHECK_RETURN(Ready_Prototype(), E_FAIL);

	return S_OK;
}

Engine::_int CScene_Loading::Update_Scene(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Scene(fTimeDelta);

	return iExit;
}

void CScene_Loading::LateUpdate_Scene()
{
	__super::LateUpdate_Scene();
}

void CScene_Loading::Render_Scene()
{

}

void CScene_Loading::Free()
{
	__super::Free();
}

CScene_Loading* CScene_Loading::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CScene_Loading* pInstance = new CScene_Loading(pGraphicDev);

	if (FAILED(pInstance->Ready_Scene()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Scene Loading Create Failed");
		return nullptr;
	}

	return pInstance;
}

HRESULT CScene_Loading::Ready_Prototype()
{

	return S_OK;
}

