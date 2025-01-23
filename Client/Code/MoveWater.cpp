#include "stdafx.h"

#include "Export_Function.h"

#include "MoveWater.h"

CMoveWater::CMoveWater(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
	: CEffect(pGraphicDev, _pOwnerObject, OBJ_ID::EFFECT_MOVEWATER)
{
	m_pOwnerobject = _pOwnerObject;
}

CMoveWater::CMoveWater(const CMoveWater& rhs)
	: CEffect(rhs), m_pTextureCom(rhs.m_pTextureCom)
{
}

CMoveWater::~CMoveWater()
{
}

HRESULT CMoveWater::Ready_Object()
{
	__super::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom, STATE_TYPE::FRONT_IDLE, 0.1f, true);

	m_pTransformCom->Set_Pos(_vec3{ m_pOwnerobject->Get_Transform()->Get_Info(INFO_POS).x,
		m_pOwnerobject->Get_Transform()->Get_Info(INFO_POS).y - m_pOwnerobject->Get_Transform()->Get_Scale().y * 0.5f,
		m_pOwnerobject->Get_Transform()->Get_Info(INFO_POS).z });
	m_pTransformCom->Set_Scale(_vec3{ 1.2f, 1.2f, 1.2f });

	m_bActive = true;
	m_iTranslucent = 200;

	return S_OK;
}

_int CMoveWater::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);
	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	m_pTransformCom->Set_Pos({
		m_pTransformCom->Get_Info(INFO_POS).x,
		m_pTransformCom->Get_Info(INFO_POS).y + 0.05f,
		m_pTransformCom->Get_Info(INFO_POS).z
		});

	m_pAnimation->Update_Animation(fTimeDelta);

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

void CMoveWater::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CMoveWater::Render_Object()
{
	m_pAnimation->Render_Animation();

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));
}

HRESULT CMoveWater::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Move_Water", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	return S_OK;
}

void CMoveWater::Play_Effect(const _vec3& _vPos, const _vec3& _vSize)
{
	m_vOffSet = _vPos;
	m_vSize = _vSize;
	m_bActive = true;
}

CMoveWater* CMoveWater::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
{
	CMoveWater* pInstance = new CMoveWater(pGraphicDev, _pOwnerObject);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("MOVE_DUST Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CMoveWater::Free()
{
	m_pAnimation->Release();
	__super::Free();
}
