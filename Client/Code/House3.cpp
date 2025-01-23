#include "stdafx.h"
#include "House3.h"

#include "Export_Function.h"

CHouse3::CHouse3(LPDIRECT3DDEVICE9 pGraphicDev)
	: CHouse(pGraphicDev, OBJ_ID::ENVIRONMENT_BUILDING_HOUSE_3)
{
}

CHouse3::CHouse3(const CHouse& rhs)
	: CHouse(rhs)
{
}

CHouse3::~CHouse3()
{
}

HRESULT CHouse3::Ready_Object()
{
	CHouse::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 4.f, 4.f, 4.f });
	m_pTransformCom->Set_Pos(_vec3{ 100.f, m_pTransformCom->Get_Scale().y, 130.f });

	m_szName = L"House3";

	return S_OK;
}

_int CHouse3::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CHouse3::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CHouse3::Render_Object()
{
	__super::Render_Object();
}

void CHouse3::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CHouse3::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CHouse3::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CHouse3::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_House3", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CHouse3* CHouse3::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CHouse3* pInstance = new CHouse3(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("House3 Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CHouse3::Free()
{
	__super::Free();
}
