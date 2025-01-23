#include "stdafx.h"

#include "Export_Function.h"

#include "GetWorldEffect.h"

CGetWorldEffect::CGetWorldEffect(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _pPos)
	: CEffect(pGraphicDev, OBJ_ID::EFFECT_WORLDGETEFFECT)
	, m_vPos(_pPos), m_fTranslucent(255.f)
{
}

CGetWorldEffect::CGetWorldEffect(const CGetWorldEffect& rhs)
	: CEffect(rhs)
	, m_vPos(rhs.m_vPos)
{
}

CGetWorldEffect::~CGetWorldEffect()
{
}

HRESULT CGetWorldEffect::Ready_Object()
{
	__super::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_bActive = true;

	m_pOraTransCom->Set_Pos(m_vPos);
	
	m_tSizeUpLerp.Init_Lerp(LERP_MODE::EASE_IN);
	m_tSizeUpLerp.Set_Lerp(1.f, 3.06f, 12.24f);

	m_tAlphaDownLerp.Init_Lerp(LERP_MODE::EASE_IN);
	m_tAlphaDownLerp.Set_Lerp(1.f, 255.f, 0.f);

	return S_OK;
}

_int CGetWorldEffect::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);
	Engine::Add_RenderGroup(RENDER_WDUI, this); // 무조건 늦게 그려지게

	m_tSizeUpLerp.Update_Lerp(fTimeDelta);
	m_tAlphaDownLerp.Update_Lerp(fTimeDelta);

	m_pOraTransCom->Set_Scale({
		m_tSizeUpLerp.fCurValue,
		m_tSizeUpLerp.fCurValue,
		m_tSizeUpLerp.fCurValue
		});

	m_fTranslucent = m_tAlphaDownLerp.fCurValue;

	if (m_fTranslucent < 10.f)
	{
		CEventMgr::GetInstance()->Delete_Obj(this);
	}

	return iExit;
}

void CGetWorldEffect::LateUpdate_Object()
{

	__super::LateUpdate_Object();
}

void CGetWorldEffect::Render_Object()
{
	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB((_int)m_fTranslucent, 255, 255, 255));
	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

	// Ora
	m_pOraTexCom->Render_Texture();
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pOraTransCom->Get_WorldMat());
	m_pBufferCom->Render_Buffer();


}

HRESULT CGetWorldEffect::Add_Component()
{
	CComponent* pComponent = nullptr;

	// Ora
	pComponent = m_pOraTransCom = dynamic_cast<CTransform*>(CProtoMgr::GetInstance()->Clone_Proto(COMPONENT_TYPE::TRANSFORM, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].emplace(COMPONENT_TYPE::TRANSFORM, pComponent);

	pComponent = m_pOraTexCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Item_WorldFlight_Ora", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);


	// 버퍼
	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	return S_OK;
}

void CGetWorldEffect::Play_Effect(const _vec3& _vPos, const _vec3& _vSize)
{
	m_vOffSet = _vPos;
	m_vSize = _vSize;
	m_bActive = true;
}

CGetWorldEffect* CGetWorldEffect::Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _pPos)
{
	CGetWorldEffect* pInstance = new CGetWorldEffect(pGraphicDev, _pPos);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("GetWorldEffect Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CGetWorldEffect::Free()
{
	__super::Free();
}
