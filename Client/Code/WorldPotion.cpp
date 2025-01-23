#include "stdafx.h"
#include "WorldPotion.h"

#include "Export_Function.h"

CWorldPotion::CWorldPotion(LPDIRECT3DDEVICE9 pGraphicDev)
	: CEnvironment(pGraphicDev, OBJ_ID::ENVIRONMENT_OTHER_POTION)
{
}

CWorldPotion::CWorldPotion(const CWorldPotion& rhs)
	: CEnvironment(rhs)
{
}

CWorldPotion::~CWorldPotion()
{
}

HRESULT CWorldPotion::Ready_Object()
{
	CEnvironment::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_eEnter = ENTER_TYPE::ENTER;

	m_pTransformCom->Set_Scale(_vec3{ 0.5f, 0.5f, 0.5f });
	m_pTransformCom->Set_Pos(_vec3{ 292.f, m_pTransformCom->Get_Scale().y, 98.f });

	m_szName = L"WorldPotion";

	return S_OK;
}

_int CWorldPotion::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CWorldPotion::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CWorldPotion::Render_Object()
{
	m_pTextureCom->Render_Texture(); // 텍스처 세팅 -> 버퍼 세팅 순서 꼭!

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetTexture(0, NULL);

	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

	CEnvironment::Render_Object();
}

void CWorldPotion::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CWorldPotion::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CWorldPotion::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CWorldPotion::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	pComponent = m_pColliderCom = dynamic_cast<CRectCollider*>(Engine::Clone_Proto(COMPONENT_TYPE::COL_RECT, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::COL_RECT, pComponent);

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Other_WorldPotion", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CWorldPotion* CWorldPotion::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CWorldPotion* pInstance = new CWorldPotion(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("WorldPotion Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CWorldPotion::Free()
{
	__super::Free();
}
