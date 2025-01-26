#include "stdafx.h"
#include "House6.h"

#include "Export_Function.h"

CHouse6::CHouse6(LPDIRECT3DDEVICE9 pGraphicDev)
	: CHouse(pGraphicDev, OBJ_ID::ENVIRONMENT_BUILDING_HOUSE_6)
{
}

CHouse6::CHouse6(const CHouse& rhs)
	: CHouse(rhs)
{
}

CHouse6::~CHouse6()
{
}

HRESULT CHouse6::Ready_Object()
{
	CHouse::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 4.f, 4.f, 4.f });
	m_pTransformCom->Set_Pos(_vec3{ 130.f , m_pTransformCom->Get_Scale().y, 130.f });

	m_szName = L"House6";

	return S_OK;
}

_int CHouse6::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CHouse6::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CHouse6::Render_Object()
{
	__super::Render_Object();
}

void CHouse6::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CHouse6::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CHouse6::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CHouse6::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_House6", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CHouse6* CHouse6::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CHouse6* pInstance = new CHouse6(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("House6 Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CHouse6::Free()
{
	__super::Free();
}
