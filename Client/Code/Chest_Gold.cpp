#include "stdafx.h"
#include "Chest_Gold.h"

#include "Export_Function.h"

CChest_Gold::CChest_Gold(LPDIRECT3DDEVICE9 pGraphicDev)
	: CChest(pGraphicDev, OBJ_ID::ENVIRONMENT_CHEST_GOLD)
{
}

CChest_Gold::CChest_Gold(const CChest& rhs)
	: CChest(rhs)
{
}

CChest_Gold::~CChest_Gold()
{
}

HRESULT CChest_Gold::Ready_Object()
{
	CChest::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_eEnter = ENTER_TYPE::ENTER_NO;
	m_eInterType = INTERACTION_TYPE::INTERACTION_INSPECT;

	m_pTransformCom->Set_Scale(_vec3{ 1.5f, 1.5f, 1.5f });
	m_pTransformCom->Set_Pos(_vec3{ 95.f, m_pTransformCom->Get_Scale().y, 80.f });

	m_szName = L"Gold_Chest";

	return S_OK;
}

_int CChest_Gold::Update_Object(const _float& fTimeDelta)
{
	_int iExit = CChest::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CChest_Gold::LateUpdate_Object()
{
	CChest::LateUpdate_Object();
}

void CChest_Gold::Render_Object()
{
	CChest::Render_Object();
}

void CChest_Gold::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CChest_Gold::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CChest_Gold::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CChest_Gold::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Gold_Chest", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CChest_Gold* CChest_Gold::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CChest_Gold* pInstance = new CChest_Gold(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Chest_Gold Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CChest_Gold::Free()
{
	CChest::Free();
}
