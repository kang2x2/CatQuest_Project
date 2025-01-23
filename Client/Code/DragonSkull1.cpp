#include "stdafx.h"
#include "DragonSkull1.h"

#include "Export_Function.h"

CDragonSkull1::CDragonSkull1(LPDIRECT3DDEVICE9 pGraphicDev)
	: CSkull(pGraphicDev, OBJ_ID::ENVIRONMENT_SKULL_DRAGON1)
{
}

CDragonSkull1::CDragonSkull1(const CSkull& rhs)
	: CSkull(rhs)
{
}

CDragonSkull1::~CDragonSkull1()
{
}

HRESULT CDragonSkull1::Ready_Object()
{
	CSkull::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 2.f, 2.f, 2.f });
	m_pTransformCom->Set_Pos(_vec3{ 360.f, m_pTransformCom->Get_Scale().y, 98.f });

	m_szName = L"DragonSkull1";

	return S_OK;
}

_int CDragonSkull1::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CDragonSkull1::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CDragonSkull1::Render_Object()
{
	__super::Render_Object();
}

void CDragonSkull1::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CDragonSkull1::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CDragonSkull1::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CDragonSkull1::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Skull_Dragon1", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CDragonSkull1* CDragonSkull1::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CDragonSkull1* pInstance = new CDragonSkull1(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("DragonSkull1 Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CDragonSkull1::Free()
{
	__super::Free();
}
