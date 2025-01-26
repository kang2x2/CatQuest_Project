#include "stdafx.h"
#include "DragonSkull3.h"

#include "Export_Function.h"

CDragonSkull3::CDragonSkull3(LPDIRECT3DDEVICE9 pGraphicDev)
	: CSkull(pGraphicDev, OBJ_ID::ENVIRONMENT_SKULL_DRAGON3)
{
}

CDragonSkull3::CDragonSkull3(const CSkull& rhs)
	: CSkull(rhs)
{
}

CDragonSkull3::~CDragonSkull3()
{
}

HRESULT CDragonSkull3::Ready_Object()
{
	CSkull::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 1.f, 1.f, 1.f });
	m_pTransformCom->Set_Pos(_vec3{ 375.f, m_pTransformCom->Get_Scale().y, 98.f });

	m_szName = L"DragonSkull3";

	return S_OK;
}

_int CDragonSkull3::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CDragonSkull3::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CDragonSkull3::Render_Object()
{
	__super::Render_Object();
}

void CDragonSkull3::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CDragonSkull3::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CDragonSkull3::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CDragonSkull3::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Skull_Dragon3", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CDragonSkull3* CDragonSkull3::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CDragonSkull3* pInstance = new CDragonSkull3(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("DragonSkull3 Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CDragonSkull3::Free()
{
	__super::Free();
}
