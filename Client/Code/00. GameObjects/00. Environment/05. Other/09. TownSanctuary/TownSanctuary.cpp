#include "stdafx.h"
#include "TownSanctuary.h"

#include "Export_Function.h"

CTownSanctuary::CTownSanctuary(LPDIRECT3DDEVICE9 pGraphicDev)
	: CEnvironment(pGraphicDev, OBJ_ID::ENVIRONMENT_OTHER_TOWN_SANCTUARY)
{
}

CTownSanctuary::CTownSanctuary(const CTownSanctuary& rhs)
	: CEnvironment(rhs)
{
}

CTownSanctuary::~CTownSanctuary()
{
}

HRESULT CTownSanctuary::Ready_Object()
{
	CEnvironment::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_eEnter = ENTER_TYPE::ENTER_NO;

	m_pTransformCom->Set_Scale(_vec3{ 1.f, 1.5f, 1.f });
	m_pTransformCom->Set_Pos(_vec3{ 305.f, m_pTransformCom->Get_Scale().y, 116.f });

	m_szName = L"TownSanctuary";

	return S_OK;
}

_int CTownSanctuary::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CTownSanctuary::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CTownSanctuary::Render_Object()
{
	m_pTextureCom->Render_Texture(); // 텍스처 세팅 -> 버퍼 세팅 순서 꼭!

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetTexture(0, NULL);

	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

	CEnvironment::Render_Object();
}

void CTownSanctuary::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CTownSanctuary::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CTownSanctuary::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CTownSanctuary::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	pComponent = m_pColliderCom = dynamic_cast<CRectCollider*>(Engine::Clone_Proto(COMPONENT_TYPE::COL_RECT, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::COL_RECT, pComponent);

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Otehr_TownSanctuary", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CTownSanctuary* CTownSanctuary::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CTownSanctuary* pInstance = new CTownSanctuary(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("TownSanctuary Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CTownSanctuary::Free()
{
	__super::Free();
}
