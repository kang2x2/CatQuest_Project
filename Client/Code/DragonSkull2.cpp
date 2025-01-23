#include "stdafx.h"
#include "DragonSkull2.h"

#include "Export_Function.h"

CDragonSkull2::CDragonSkull2(LPDIRECT3DDEVICE9 pGraphicDev)
	: CSkull(pGraphicDev, OBJ_ID::ENVIRONMENT_SKULL_DRAGON2)
{
}

CDragonSkull2::CDragonSkull2(const CSkull& rhs)
	: CSkull(rhs)
{
}

CDragonSkull2::~CDragonSkull2()
{
}

HRESULT CDragonSkull2::Ready_Object()
{
	CSkull::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 2.f, 2.f, 2.f });
	m_pTransformCom->Set_Pos(_vec3{ 370.f, m_pTransformCom->Get_Scale().y, 98.f });

	m_szName = L"DragonSkull2";

	return S_OK;
}

_int CDragonSkull2::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CDragonSkull2::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CDragonSkull2::Render_Object()
{
	__super::Render_Object();
}

void CDragonSkull2::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CDragonSkull2::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CDragonSkull2::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CDragonSkull2::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Skull_Dragon2", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CDragonSkull2* CDragonSkull2::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CDragonSkull2* pInstance = new CDragonSkull2(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("DragonSkull2 Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CDragonSkull2::Free()
{
	__super::Free();
}
