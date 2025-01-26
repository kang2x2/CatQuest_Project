#include "stdafx.h"

#include "Export_Function.h"

#include "TrapFistDust.h"
#include "Player.h"

CTrapFistDust::CTrapFistDust(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos)
	: CEffect(pGraphicDev, OBJ_ID::EFFECT_TRAP_FISTDUST)
{
	m_vPos = _vPos;
}

CTrapFistDust::CTrapFistDust(const CTrapFistDust& rhs)
	: CEffect(rhs), m_pTextureCom(rhs.m_pTextureCom)
{
}

CTrapFistDust::~CTrapFistDust()
{
}

HRESULT CTrapFistDust::Ready_Object()
{
	__super::Ready_Object();

	// CGameObject::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom, STATE_TYPE::FRONT_IDLE, 0.1f, true);

	m_pTransformCom->Set_Pos(_vec3{ m_vPos.x, m_vPos.y, m_vPos.z });
	m_pTransformCom->Set_Scale(_vec3{ 2.6f, 2.6f, 2.6f });

	m_bActive = true;
	m_iTranslucent = 240;
	m_iDeAlpha = 20;

	return S_OK;
}

_int CTrapFistDust::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);
	Engine::Add_RenderGroup(RENDER_WDUI, this);

	m_pAnimation->Update_Animation(fTimeDelta);

	m_iTranslucent -= m_iDeAlpha;

	if (m_pAnimation->Is_End())
	{
		CEventMgr::GetInstance()->Delete_Obj(this);
	}

	return iExit;
}

void CTrapFistDust::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CTrapFistDust::Render_Object()
{
	NULL_CHECK(m_pOwnerobject);

	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(m_iTranslucent, 255, 255, 255));

	m_pAnimation->Render_Animation();
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());
	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));
	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));
}

HRESULT CTrapFistDust::Add_Component()
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

void CTrapFistDust::Play_Effect(const _vec3& _vPos, const _vec3& _vSize)
{
}

CTrapFistDust* CTrapFistDust::Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos)
{
	CTrapFistDust* pInstance = new CTrapFistDust(pGraphicDev, _vPos);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("TrapFistDust Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CTrapFistDust::Free()
{
	m_pAnimation->Release();
	__super::Free();
}
