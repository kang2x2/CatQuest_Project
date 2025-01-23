#include "stdafx.h"
#include "Mountain_Grass.h"

#include "Export_Function.h"

CMountain_Grass::CMountain_Grass(LPDIRECT3DDEVICE9 pGraphicDev)
	: CMountain(pGraphicDev, OBJ_ID::ENVIRONMENT_NATURAL_MOUNTAIN_GRASS)
{
}

CMountain_Grass::CMountain_Grass(const CMountain& rhs)
	: CMountain(rhs)
{
}

CMountain_Grass::~CMountain_Grass()
{
}

HRESULT CMountain_Grass::Ready_Object()
{
	CMountain::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 11.f, 5.f, 7.f });
	m_pTransformCom->Set_Pos(_vec3{ 140.f, m_pTransformCom->Get_Scale().y - 1.f, 80.f });
	
	m_szName = L"Mountain_Grass";

	return S_OK;
}

_int CMountain_Grass::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CMountain_Grass::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CMountain_Grass::Render_Object()
{
	__super::Render_Object();
}

void CMountain_Grass::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CMountain_Grass::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CMountain_Grass::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CMountain_Grass::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Mountain_Grass", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CMountain_Grass* CMountain_Grass::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CMountain_Grass* pInstance = new CMountain_Grass(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Mountain_Grass Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CMountain_Grass::Free()
{
	__super::Free();
}
