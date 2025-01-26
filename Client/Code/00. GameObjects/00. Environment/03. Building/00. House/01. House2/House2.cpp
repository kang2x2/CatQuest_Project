#include "stdafx.h"
#include "House2.h"

#include "Export_Function.h"

CHouse2::CHouse2(LPDIRECT3DDEVICE9 pGraphicDev)
	: CHouse(pGraphicDev, OBJ_ID::ENVIRONMENT_BUILDING_HOUSE_2)
{
}

CHouse2::CHouse2(const CHouse& rhs)
	: CHouse(rhs)
{
}

CHouse2::~CHouse2()
{
}

HRESULT CHouse2::Ready_Object()
{
	CHouse::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 4.f, 4.f, 4.f });
	m_pTransformCom->Set_Pos(_vec3{ 90.f, m_pTransformCom->Get_Scale().y, 130.f });

	m_szName = L"House2";

	return S_OK;
}

_int CHouse2::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CHouse2::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CHouse2::Render_Object()
{
	__super::Render_Object();
}

void CHouse2::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CHouse2::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CHouse2::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CHouse2::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_House2", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CHouse2* CHouse2::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CHouse2* pInstance = new CHouse2(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("House2 Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CHouse2::Free()
{
	__super::Free();
}
