#include "stdafx.h"
#include "House5.h"

#include "Export_Function.h"

CHouse5::CHouse5(LPDIRECT3DDEVICE9 pGraphicDev)
	: CHouse(pGraphicDev, OBJ_ID::ENVIRONMENT_BUILDING_HOUSE_5)
{
}

CHouse5::CHouse5(const CHouse& rhs)
	: CHouse(rhs)
{
}

CHouse5::~CHouse5()
{
}

HRESULT CHouse5::Ready_Object()
{
	CHouse::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 4.f, 4.f, 4.f });
	m_pTransformCom->Set_Pos(_vec3{ 120.f , m_pTransformCom->Get_Scale().y, 130.f });
	
	m_szName = L"House5";
	
	return S_OK;
}

_int CHouse5::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CHouse5::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CHouse5::Render_Object()
{
	__super::Render_Object();
}

void CHouse5::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CHouse5::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CHouse5::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CHouse5::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_House5", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CHouse5* CHouse5::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CHouse5* pInstance = new CHouse5(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("House5 Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CHouse5::Free()
{
	__super::Free();
}
