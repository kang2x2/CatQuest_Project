#include "stdafx.h"
#include "Chest_Cosmetic.h"

#include "Export_Function.h"

CChest_Cosmetic::CChest_Cosmetic(LPDIRECT3DDEVICE9 pGraphicDev)
	: CChest(pGraphicDev, OBJ_ID::ENVIRONMENT_CHEST_COSMETIC)
{
}

CChest_Cosmetic::CChest_Cosmetic(const CChest& rhs)
	: CChest(rhs)
{
}

CChest_Cosmetic::~CChest_Cosmetic()
{
}

HRESULT CChest_Cosmetic::Ready_Object()
{
	CChest::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_eEnter = ENTER_TYPE::ENTER_NO;
	m_eInterType = INTERACTION_TYPE::INTERACTION_INSPECT;

	m_pTransformCom->Set_Scale(_vec3{ 1.f, 1.f, 1.f });
	m_pTransformCom->Set_Pos(_vec3{ 90.f, m_pTransformCom->Get_Scale().y, 80.f });

	m_szName = L"Cosmetic_Chest";

	return S_OK;
}

_int CChest_Cosmetic::Update_Object(const _float& fTimeDelta)
{
	_int iExit = CChest::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CChest_Cosmetic::LateUpdate_Object()
{
	CChest::LateUpdate_Object();
}

void CChest_Cosmetic::Render_Object()
{
	CChest::Render_Object();
}

void CChest_Cosmetic::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CChest_Cosmetic::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CChest_Cosmetic::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CChest_Cosmetic::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Cosmetic_Chest", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CChest_Cosmetic* CChest_Cosmetic::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CChest_Cosmetic* pInstance = new CChest_Cosmetic(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Chest_Cosmetic Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CChest_Cosmetic::Free()
{
	CChest::Free();
}
