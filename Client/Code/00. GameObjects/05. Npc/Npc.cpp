#include "stdafx.h"
#include "..\Header\Npc.h"

#include "Export_Function.h"

CNpc::CNpc(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID)
	: Engine::CGameObject(pGraphicDev, OBJ_TYPE::NPC, _eID)
{

}

CNpc::CNpc(const CNpc& rhs)
	: Engine::CGameObject(rhs)
{
}

CNpc::~CNpc()
{
}

HRESULT CNpc::Ready_Object()
{
	CGameObject::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_eEnter = ENTER_TYPE::ENTER_NO;
	m_eInterType = INTERACTION_TYPE::INTERACTION_CHAT;
	m_bCol = false;
	m_bReadyTalk = false;

	return S_OK;
}

Engine::_int CNpc::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	m_pAnimation->Update_Animation(fTimeDelta);

	return iExit;
}

void CNpc::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CNpc::Render_Object()  // 텍스처 세팅 -> 버퍼 세팅 순서 꼭!
{
	m_pTextureCom->Render_Texture();
	m_pAnimation->Render_Animation();

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetTexture(0, NULL);

	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));


	__super::Render_Object(); // 콜라이더 출력
}

void CNpc::OnCollision_Stay(CGameObject* _pColObj)
{

}

void CNpc::Play_ColLogic(const _float& fTimeDelta)
{

}

HRESULT CNpc::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	pComponent = m_pColliderCom = dynamic_cast<CRectCollider*>(Engine::Clone_Proto(COMPONENT_TYPE::COL_RECT, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::COL_RECT, pComponent);

	return S_OK;
}

void CNpc::Free()
{
	m_pAnimation->Release(); 
	__super::Free();
}

