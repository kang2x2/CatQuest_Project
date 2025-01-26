#include "stdafx.h"
#include "..\Header\House.h"

#include "Export_Function.h"

CHouse::CHouse(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID)
	: CEnvironment(pGraphicDev, _eID)
{
}

CHouse::CHouse(const CHouse& rhs)
	: CEnvironment(rhs)
{
}

CHouse::~CHouse()
{
}

HRESULT CHouse::Ready_Object()
{
	CEnvironment::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_eEnter = ENTER_TYPE::ENTER_NO;

	return S_OK;
}

_int CHouse::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	return iExit;
}

void CHouse::LateUpdate_Object()
{
	__super::LateUpdate_Object();

}

void CHouse::Render_Object()
{
	m_pTextureCom->Render_Texture(); // �ؽ�ó ���� -> ���� ���� ���� ��!

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetTexture(0, NULL);

	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

	CEnvironment::Render_Object();
}

void CHouse::Play_ColLogic(const _float& fTimeDelta)
{
}

HRESULT CHouse::Add_Component()
{
	CComponent* pComponent = nullptr;

	// Rc Texture
	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	// Rect Collider
	pComponent = m_pColliderCom = dynamic_cast<CRectCollider*>(Engine::Clone_Proto(COMPONENT_TYPE::COL_RECT, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::COL_RECT, pComponent);

	return S_OK;

}

void CHouse::Free()
{
	__super::Free();
}
