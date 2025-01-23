#include "stdafx.h"
#include "Tombstone.h"

#include "Export_Function.h"

CTombstone::CTombstone(LPDIRECT3DDEVICE9 pGraphicDev)
	: COtherEnvironment(pGraphicDev, OBJ_ID::ENVIRONMENT_NATURE_TOMBSTONE)
{
}

CTombstone::CTombstone(const COtherEnvironment& rhs)
	: COtherEnvironment(rhs)
{
}

CTombstone::~CTombstone()
{
}

HRESULT CTombstone::Ready_Object()
{
	COtherEnvironment::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 1.5f, 1.5f, 1.5f });
	m_pTransformCom->Set_Pos(_vec3{ 219.f, m_pTransformCom->Get_Scale().y, 185.f });

	m_szName = L"Tombstone";

	return S_OK;
}

_int CTombstone::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CTombstone::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CTombstone::Render_Object()
{
	__super::Render_Object();
}

void CTombstone::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CTombstone::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CTombstone::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CTombstone::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Tombstone", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CTombstone* CTombstone::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CTombstone* pInstance = new CTombstone(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Tombstone Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CTombstone::Free()
{
	__super::Free();
}
