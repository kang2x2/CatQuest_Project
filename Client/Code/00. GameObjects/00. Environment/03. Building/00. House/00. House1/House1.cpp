#include "stdafx.h"
#include "House1.h"

#include "Export_Function.h"

CHouse1::CHouse1(LPDIRECT3DDEVICE9 pGraphicDev)
	: CHouse(pGraphicDev, OBJ_ID::ENVIRONMENT_BUILDING_HOUSE_1)
{
}

CHouse1::CHouse1(const CHouse& rhs)
	: CHouse(rhs)
{
}

CHouse1::~CHouse1()
{
}

HRESULT CHouse1::Ready_Object()
{
	CHouse::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 4.f, 4.f, 4.f });
	m_pTransformCom->Set_Pos(_vec3{ 80.f, m_pTransformCom->Get_Scale().y, 130.f });

	m_szName = L"House1";

	return S_OK;
}

_int CHouse1::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CHouse1::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CHouse1::Render_Object()
{
	__super::Render_Object();
}

void CHouse1::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CHouse1::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CHouse1::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CHouse1::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_House1", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CHouse1* CHouse1::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CHouse1* pInstance = new CHouse1(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("House1 Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CHouse1::Free()
{
	__super::Free();
}
