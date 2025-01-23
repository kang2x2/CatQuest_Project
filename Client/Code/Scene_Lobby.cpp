#include "stdafx.h"
#include "..\Header\Scene_Lobby.h"

#include "Export_Function.h"

CScene_Lobby::CScene_Lobby(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CScene(pGraphicDev, SCENE_TYPE::LOBBY)
{
}

CScene_Lobby::~CScene_Lobby()
{
}

HRESULT CScene_Lobby::Ready_Scene()
{
	FAILED_CHECK_RETURN(Ready_Prototype(), E_FAIL);

	FAILED_CHECK_RETURN(Ready_Layer_Environment(), E_FAIL);

	return S_OK;
}

Engine::_int CScene_Lobby::Update_Scene(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Scene(fTimeDelta);

	return iExit;
}

void CScene_Lobby::LateUpdate_Scene()
{
	__super::LateUpdate_Scene();
}

void CScene_Lobby::Render_Scene()
{

}

void CScene_Lobby::Free()
{
	__super::Free();
}

CScene_Lobby* CScene_Lobby::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CScene_Lobby* pInstance = new CScene_Lobby(pGraphicDev);

	if (FAILED(pInstance->Ready_Scene()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Scene Lobby Create Failed");
		return nullptr;
	}

	return pInstance;
}

HRESULT CScene_Lobby::Ready_Prototype()
{
	FAILED_CHECK_RETURN(Engine::Ready_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, CRcTex::Create(m_pGraphicDev)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Logo", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Logo/gentlebros_logo.png")), E_FAIL);

	return S_OK;
}

HRESULT CScene_Lobby::Ready_Layer_Environment()
{
	return E_NOTIMPL;
}

