#include "stdafx.h"
#include "Tower3.h"

#include "Export_Function.h"

CTower3::CTower3(LPDIRECT3DDEVICE9 pGraphicDev)
	: CTower(pGraphicDev, OBJ_ID::ENVIRONMENT_BUILDING_TOWER_3)
{
}

CTower3::CTower3(const CTower& rhs)
	: CTower(rhs)
{
}

CTower3::~CTower3()
{
}

HRESULT CTower3::Ready_Object()
{
	CTower::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 3.f, 5.f, 3.f });
	m_pTransformCom->Set_Pos(_vec3{ 140.f, m_pTransformCom->Get_Scale().y, 125.f });

	m_szName = L"Tower3";

	return S_OK;
}

_int CTower3::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CTower3::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CTower3::Render_Object()
{
	__super::Render_Object();
}

void CTower3::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CTower3::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CTower3::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CTower3::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Tower3", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CTower3* CTower3::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CTower3* pInstance = new CTower3(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Tower3 Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CTower3::Free()
{
	__super::Free();
}
