#include "stdafx.h"
#include "House4.h"

#include "Export_Function.h"

CHouse4::CHouse4(LPDIRECT3DDEVICE9 pGraphicDev)
	: CHouse(pGraphicDev, OBJ_ID::ENVIRONMENT_BUILDING_HOUSE_4)
{
}

CHouse4::CHouse4(const CHouse& rhs)
	: CHouse(rhs)
{
}

CHouse4::~CHouse4()
{
}

HRESULT CHouse4::Ready_Object()
{
	CHouse::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 4.f, 4.f, 4.f });
	m_pTransformCom->Set_Pos(_vec3{ 110.f, m_pTransformCom->Get_Scale().y, 130.f });

	m_szName = L"House4";

	return S_OK;
}

_int CHouse4::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CHouse4::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CHouse4::Render_Object()
{
	__super::Render_Object();
}

void CHouse4::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CHouse4::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CHouse4::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CHouse4::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_House4", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CHouse4* CHouse4::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CHouse4* pInstance = new CHouse4(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("House4 Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CHouse4::Free()
{
	__super::Free();
}
