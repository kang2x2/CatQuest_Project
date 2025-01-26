#include "stdafx.h"

#include "Export_Function.h"

#include "MoveDust.h"
#include "Player.h"

CMoveDust::CMoveDust(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
	: CEffect(pGraphicDev, _pOwnerObject, OBJ_ID::EFFECT_MOVEDUST)
{
	m_pOwnerobject = _pOwnerObject;
}

CMoveDust::CMoveDust(const CMoveDust& rhs)
	: CEffect(rhs), m_pTextureCom(rhs.m_pTextureCom)
{
}

CMoveDust::~CMoveDust()
{
}

HRESULT CMoveDust::Ready_Object()
{
	__super::Ready_Object();

	// CGameObject::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom, STATE_TYPE::FRONT_IDLE, 0.1f, true);

	m_pTransformCom->Set_Pos(_vec3{ m_pOwnerobject->Get_Transform()->Get_Info(INFO_POS).x,
		m_pOwnerobject->Get_Transform()->Get_Info(INFO_POS).y - m_pOwnerobject->Get_Transform()->Get_Scale().y * 0.5f,
		m_pOwnerobject->Get_Transform()->Get_Info(INFO_POS).z });
	m_pTransformCom->Set_Scale(_vec3{ 1.2f, 1.2f, 1.2f });

	m_bActive = true;
	m_iTranslucent = 200;
	m_iDeAlpha = 2;

	return S_OK;
}

_int CMoveDust::Update_Object(const _float& fTimeDelta)
{ 
	_int iExit = __super::Update_Object(fTimeDelta);
	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	m_pTransformCom->Set_Pos({ 
		m_pTransformCom->Get_Info(INFO_POS).x,
		m_pTransformCom->Get_Info(INFO_POS).y + 0.05f,
		m_pTransformCom->Get_Info(INFO_POS).z
		});

	m_pAnimation->Update_Animation(fTimeDelta);

	m_iTranslucent -= m_iDeAlpha;

	if (m_pAnimation->Is_End()) 
	{
		CEventMgr::GetInstance()->Delete_Obj(this);
	}
		
	if (!m_pOwnerobject->Is_Active())
	{
		CEventMgr::GetInstance()->Delete_Obj(this);
		return iExit;
	}

	return iExit;
}

void CMoveDust::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CMoveDust::Render_Object()
{
	NULL_CHECK(m_pOwnerobject);

	if (static_cast<CPlayer*>(m_pOwnerobject)->Get_CurGroundType() != GROUND_TYPE::NORMAL)
		return;

	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(m_iTranslucent, 255, 255, 255));

	m_pAnimation->Render_Animation();

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));
	
	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));
}

HRESULT CMoveDust::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Move_Dust", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	return S_OK;
}

void CMoveDust::Play_Effect(const _vec3& _vPos, const _vec3& _vSize)
{
	m_vOffSet = _vPos;
	m_vSize = _vSize;
	m_bActive = true;
}

CMoveDust* CMoveDust::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
{
	CMoveDust* pInstance = new CMoveDust(pGraphicDev, _pOwnerObject);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("MOVE_DUST Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CMoveDust::Free()
{
	m_pAnimation->Release();
	__super::Free();
}
