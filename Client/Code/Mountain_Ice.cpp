#include "stdafx.h"
#include "Mountain_Ice.h"

#include "Export_Function.h"

CMountain_Ice::CMountain_Ice(LPDIRECT3DDEVICE9 pGraphicDev)
	: CMountain(pGraphicDev, OBJ_ID::ENVIRONMENT_NATURAL_MOUNTAIN_ICE)
{
}

CMountain_Ice::CMountain_Ice(const CMountain& rhs)
	: CMountain(rhs)
{
}

CMountain_Ice::~CMountain_Ice()
{
}

HRESULT CMountain_Ice::Ready_Object()
{
	CMountain::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 11.f, 5.f, 7.f });
	m_pTransformCom->Set_Pos(_vec3{ 130.f , m_pTransformCom->Get_Scale().y - 1.f, 90.f });
	
	m_szName = L"Mountain_Ice";
	
	return S_OK;
}

_int CMountain_Ice::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CMountain_Ice::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CMountain_Ice::Render_Object()
{
	__super::Render_Object();
}

void CMountain_Ice::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CMountain_Ice::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CMountain_Ice::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CMountain_Ice::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Mountain_Ice", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CMountain_Ice* CMountain_Ice::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CMountain_Ice* pInstance = new CMountain_Ice(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Mountain_Ice Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CMountain_Ice::Free()
{
	__super::Free();
}
