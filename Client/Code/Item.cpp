#include "stdafx.h"
#include "..\Header\Item.h"
#include "EventMgr.h"
#include "Export_Function.h"

#include "ItemGetEffect.h"
#include "Effect_Font.h"
#include "SoundMgr.h"

CItem::CItem(LPDIRECT3DDEVICE9 pGraphicDev , const OBJ_ID& _eID)
	: Engine::CGameObject(pGraphicDev, OBJ_TYPE::ITEM, _eID)
	, m_pTextureCom(nullptr)
	, m_fJumpingSpeed(0.f)
	, m_eItemType(ITEM_TYPE::TYPEEND)
	, m_vImageSize({ 0.f,0.f,0.f })
	, m_bCol(false)
{
	ZeroMemory(&m_tStatInfo, sizeof(STATINFO));
	
}

CItem::CItem(const CItem & rhs)
	: Engine::CGameObject(rhs)
	, m_tStatInfo(rhs.m_tStatInfo)
	, m_fJumpingSpeed(rhs.m_fJumpingSpeed)
	, m_eItemType(rhs.m_eItemType)
	, m_vImageSize(rhs.m_vImageSize)
	, m_bCol(rhs.m_bCol)
{
}

CItem::~CItem()
{
}

HRESULT CItem::Ready_Object()
{
	CGameObject::Ready_Object();
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);



	return S_OK;
}

_int CItem::Update_Object(const _float & fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);
	

	// 각각의 아이템에서 실행 함
	//Engine::Add_RenderGroup(RENDER_ALPHA, this);


	return iExit;
}

void CItem::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CItem::Render_Object()
{
	//m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	//m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

	//m_pBufferCom->Render_Buffer();

	//m_pGraphicDev->SetTexture(0, NULL);

	//m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

	__super::Render_Object(); // 콜라이더 출력

}

void CItem::OnCollision_Enter(CGameObject* _pColObj)
{
	// Target - Pos
	_vec3 vColPos =  _pColObj->Get_Transform()->Get_Info(INFO_POS);
	
	// Item - Pos
	_vec3	vOwnerPos =  m_pTransformCom->Get_Info(INFO_POS);




	// Overlap - 콜라이더끼리 충돌
	_vec3 vOverlap = static_cast<CRectCollider*>(m_pColliderCom)->Get_Overlap_Rect();

	if (_pColObj->Get_Type() == OBJ_TYPE::PLAYER)
	{
		if (m_eID == OBJ_ID::ITEM_EXP)
		{
			CGameObject* pEffect = CEffect_Font::Create(m_pGraphicDev, this, m_iItemValue, FONT_TYPE::EXP);
			NULL_CHECK(pEffect);
			CEventMgr::GetInstance()->Add_Obj(L"Effect_Font", pEffect);
			CSoundMgr::GetInstance()->PlaySoundW(L"exp_pickup.wav", CHANNEL_ID::EFFECT_6, VOLUME_PLAYER_EXPPICK);
		}
		if (m_eID == OBJ_ID::ITEM_GOLD)
		{
			CGameObject* pEffect = CEffect_Font::Create(m_pGraphicDev, this, m_iItemValue, FONT_TYPE::GOLD);
			NULL_CHECK(pEffect);
			CEventMgr::GetInstance()->Add_Obj(L"Effect_Font", pEffect);
			CSoundMgr::GetInstance()->PlaySoundW(L"coin_pickup.wav", CHANNEL_ID::EFFECT_7, VOLUME_PLAYER_GOLDPICK);
		}

		CEventMgr::GetInstance()->Add_Obj(L"ItemGetEffect", CItemGetEffect::Create(
			m_pGraphicDev, _pColObj->Get_Transform()->Get_Info(INFO_POS)
		));
		CEventMgr::GetInstance()->Delete_Obj(this);  // 삭제
	}

	

	
	

}

void CItem::OnCollision_Stay(CGameObject* _pColObj)
{

}

void CItem::OnCollision_Exit(CGameObject* _pColObj)
{

}

HRESULT CItem::Add_Component()
{
	CComponent* pComponent = nullptr;

	// Rc Collider
	pComponent = m_pColliderCom = dynamic_cast<CRectCollider*>(Engine::Clone_Proto(COMPONENT_TYPE::COL_RECT, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::COL_RECT, pComponent);

	// Rc Texture
	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);


	return S_OK;
}


void CItem::Free()
{
	__super::Free();
}
