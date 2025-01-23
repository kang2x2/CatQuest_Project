#include "stdafx.h"
#include "BingoChest.h"

#include "Export_Function.h"

CBingoChest::CBingoChest(LPDIRECT3DDEVICE9 pGraphicDev)
	: CChest(pGraphicDev, OBJ_ID::ENVIRONMENT_BINGO_CHEST)
	, m_bOpen(false)
{
}

CBingoChest::CBingoChest(const CChest& rhs)
	: CChest(rhs)
{
}

CBingoChest::~CBingoChest()
{
}

HRESULT CBingoChest::Ready_Object()
{
	CChest::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_eEnter = ENTER_TYPE::ENTER_NO;
	m_eInterType = INTERACTION_TYPE::INTERACTION_INSPECT;

	m_pTransformCom->Set_Scale(_vec3{ 1.5f, 1.5f, 1.5f });
	m_pTransformCom->Set_Pos(_vec3{ 155.f, m_pTransformCom->Get_Scale().y, 75.f });

	m_szName = L"BingoChest";

	return S_OK;
}

_int CBingoChest::Update_Object(const _float& fTimeDelta)
{
	_int iExit = CChest::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CBingoChest::LateUpdate_Object()
{
	CChest::LateUpdate_Object();
}

void CBingoChest::Render_Object()
{
	CChest::Render_Object();
}

void CBingoChest::OnCollision_Enter(CGameObject* _pColObj)
{

}

void CBingoChest::OnCollision_Stay(CGameObject* _pColObj)
{
	switch (_pColObj->Get_Type())
	{
	case Engine::OBJ_TYPE::PLAYER:
	{
		m_bCol = true;
	}
	break;
	default:
		break;
	}
}

void CBingoChest::OnCollision_Exit(CGameObject* _pColObj)
{
	m_bCol = false;
}

HRESULT CBingoChest::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Gold_Chest", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CBingoChest* CBingoChest::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBingoChest* pInstance = new CBingoChest(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("BingoChest Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CBingoChest::Free()
{
	CChest::Free();
}
