#include "stdafx.h"
#include "MagicShop.h"

#include "Export_Function.h"

CMagicShop::CMagicShop(LPDIRECT3DDEVICE9 pGraphicDev)
	: CEnvironment(pGraphicDev, OBJ_ID::ENVIRONMENT_ENTERANCE_MAGICSHOP)
{
}

CMagicShop::CMagicShop(const CMagicShop& rhs)
	: CEnvironment(rhs)
{
}

CMagicShop::~CMagicShop()
{
}

HRESULT CMagicShop::Ready_Object()
{
	CEnvironment::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_eEnter = ENTER_TYPE::ENTER_NO;
	m_eInterType = INTERACTION_TYPE::INTERACTION_ENTER;

	m_pTransformCom->Set_Scale(_vec3{ 4.f, 5.f, 4.f });
	m_pTransformCom->Set_Pos(_vec3{ 70.f, m_pTransformCom->Get_Scale().y, 115.f });

	m_szName = L"MagicShop";

	return S_OK;
}

_int CMagicShop::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CMagicShop::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CMagicShop::Render_Object()
{
	m_pTextureCom->Render_Texture(); // 텍스처 세팅 -> 버퍼 세팅 순서 꼭!

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetTexture(0, NULL);

	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

	CEnvironment::Render_Object();
}

void CMagicShop::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CMagicShop::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CMagicShop::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CMagicShop::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	pComponent = m_pColliderCom = dynamic_cast<CRectCollider*>(Engine::Clone_Proto(COMPONENT_TYPE::COL_RECT, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::COL_RECT, pComponent);

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_MagicShop", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CMagicShop* CMagicShop::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CMagicShop* pInstance = new CMagicShop(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("MagicShop Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CMagicShop::Free()
{
	__super::Free();
}
