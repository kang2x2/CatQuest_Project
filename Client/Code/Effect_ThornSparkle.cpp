#include "stdafx.h"

#include "Export_Function.h"

#include "Effect_ThornSparkle.h"

CEffect_ThornSparkle::CEffect_ThornSparkle(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _pPos)
	: CEffect(pGraphicDev, OBJ_ID::EFFECT_THORNSPARKLE)
	, m_iLevel(0), m_vPos(_pPos)
{
}

CEffect_ThornSparkle::CEffect_ThornSparkle(const CEffect_ThornSparkle& rhs)
	: CEffect(rhs)
	, m_iLevel(rhs.m_iLevel)
	, m_vPos(rhs.m_vPos)
{
}

CEffect_ThornSparkle::~CEffect_ThornSparkle()
{
}

HRESULT CEffect_ThornSparkle::Ready_Object()
{
	__super::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_bActive = true;

	m_sSparkle[0].m_pSparkleTransCom->Set_Pos({ m_vPos.x - 1.f, m_vPos.y - 1.f, m_vPos.z });
	m_sSparkle[1].m_pSparkleTransCom->Set_Pos({ m_vPos.x + 1.f, m_vPos.y + 0.5f, m_vPos.z });
	m_sSparkle[2].m_pSparkleTransCom->Set_Pos({ m_vPos.x - 1.f, m_vPos.y + 2.f, m_vPos.z });
	
	m_sSparkle[0].m_pSparkleTransCom->Set_Scale({ 0.f, 0.f, 0.f });
	m_sSparkle[1].m_pSparkleTransCom->Set_Scale({ 0.f, 0.f, 0.f });
	m_sSparkle[2].m_pSparkleTransCom->Set_Scale({ 0.f, 0.f, 0.f });
	
	m_sSparkle[0].m_tSizeUpLerp.Init_Lerp(LERP_MODE::EASE_IN);
	m_sSparkle[0].m_tSizeUpLerp.Set_Lerp(0.1f, 0.f, 0.5f);
	m_sSparkle[1].m_tSizeUpLerp.Init_Lerp(LERP_MODE::EASE_IN);
	m_sSparkle[1].m_tSizeUpLerp.Set_Lerp(0.1f, 0.f, 0.5f);
	m_sSparkle[2].m_tSizeUpLerp.Init_Lerp(LERP_MODE::EASE_IN);
	m_sSparkle[2].m_tSizeUpLerp.Set_Lerp(0.1f, 0.f, 0.5f);

	m_sSparkle[0].m_tSizeDownLerp.Init_Lerp(LERP_MODE::EASE_IN);
	m_sSparkle[0].m_tSizeDownLerp.Set_Lerp(0.1f, 0.5f, 0.f);
	m_sSparkle[1].m_tSizeDownLerp.Init_Lerp(LERP_MODE::EASE_IN);
	m_sSparkle[1].m_tSizeDownLerp.Set_Lerp(0.1f, 0.5f, 0.f);
	m_sSparkle[2].m_tSizeDownLerp.Init_Lerp(LERP_MODE::EASE_IN);
	m_sSparkle[2].m_tSizeDownLerp.Set_Lerp(0.1f, 0.5f, 0.f);

	return S_OK;
}

_int CEffect_ThornSparkle::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);
	Engine::Add_RenderGroup(RENDER_WDUI, this); // 무조건 늦게 그려지게

	switch (m_iLevel)
	{
	case 0:
		m_sSparkle[0].m_tSizeUpLerp.Update_Lerp(fTimeDelta);
		m_sSparkle[0].m_pSparkleTransCom->Set_Scale({
		m_sSparkle[0].m_tSizeUpLerp.fCurValue,
		m_sSparkle[0].m_tSizeUpLerp.fCurValue,
		m_sSparkle[0].m_tSizeUpLerp.fCurValue });
		
		if (!m_sSparkle[0].m_tSizeUpLerp.bActive) m_iLevel += 1;

		break;
	case 1:
		m_sSparkle[1].m_tSizeUpLerp.Update_Lerp(fTimeDelta);
		m_sSparkle[1].m_pSparkleTransCom->Set_Scale({
		m_sSparkle[1].m_tSizeUpLerp.fCurValue,
		m_sSparkle[1].m_tSizeUpLerp.fCurValue,
		m_sSparkle[1].m_tSizeUpLerp.fCurValue });

		if (!m_sSparkle[1].m_tSizeUpLerp.bActive) m_iLevel += 1;

		break;
	case 2:
		m_sSparkle[2].m_tSizeUpLerp.Update_Lerp(fTimeDelta);
		m_sSparkle[2].m_pSparkleTransCom->Set_Scale({
		m_sSparkle[2].m_tSizeUpLerp.fCurValue,
		m_sSparkle[2].m_tSizeUpLerp.fCurValue,
		m_sSparkle[2].m_tSizeUpLerp.fCurValue });

		if (!m_sSparkle[2].m_tSizeUpLerp.bActive) m_iLevel += 1;

		break;
	case 3:
		m_sSparkle[2].m_tSizeDownLerp.Update_Lerp(fTimeDelta);
		m_sSparkle[2].m_pSparkleTransCom->Set_Scale({
		m_sSparkle[2].m_tSizeDownLerp.fCurValue,
		m_sSparkle[2].m_tSizeDownLerp.fCurValue,
		m_sSparkle[2].m_tSizeDownLerp.fCurValue });

		if (!m_sSparkle[2].m_tSizeDownLerp.bActive) m_iLevel += 1;

		break;
	case 4:
		m_sSparkle[1].m_tSizeDownLerp.Update_Lerp(fTimeDelta);
		m_sSparkle[1].m_pSparkleTransCom->Set_Scale({
		m_sSparkle[1].m_tSizeDownLerp.fCurValue,
		m_sSparkle[1].m_tSizeDownLerp.fCurValue,
		m_sSparkle[1].m_tSizeDownLerp.fCurValue });

		if (!m_sSparkle[1].m_tSizeDownLerp.bActive) m_iLevel += 1;

		break;
	case 5:
		m_sSparkle[0].m_tSizeDownLerp.Update_Lerp(fTimeDelta);
		m_sSparkle[0].m_pSparkleTransCom->Set_Scale({
		m_sSparkle[0].m_tSizeDownLerp.fCurValue,
		m_sSparkle[0].m_tSizeDownLerp.fCurValue,
		m_sSparkle[0].m_tSizeDownLerp.fCurValue });

		if (!m_sSparkle[0].m_tSizeDownLerp.bActive) m_iLevel += 1;

		break;

	case 6:
		CEventMgr::GetInstance()->Delete_Obj(this);
		break;	
	}

	return iExit;
}

void CEffect_ThornSparkle::LateUpdate_Object()
{

	__super::LateUpdate_Object();
}

void CEffect_ThornSparkle::Render_Object()
{
	for (_int i = 0; i < 3; ++i)
	{
		m_sSparkle[i].m_pSparkleTextureCom->Render_Texture();
		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_sSparkle[i].m_pSparkleTransCom->Get_WorldMat());
		m_pBufferCom->Render_Buffer();
	}

	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

}

HRESULT CEffect_ThornSparkle::Add_Component()
{
	CComponent* pComponent = nullptr;

	for (_int i = 0; i < 3; ++i)
	{
		pComponent = m_sSparkle[i].m_pSparkleTransCom = dynamic_cast<CTransform*>(CProtoMgr::GetInstance()->Clone_Proto(COMPONENT_TYPE::TRANSFORM, this));
		NULL_CHECK_RETURN(pComponent, E_FAIL);
		m_mapComponent[ID_DYNAMIC].emplace(COMPONENT_TYPE::TRANSFORM, pComponent);

		pComponent = m_sSparkle[i].m_pSparkleTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_YellowSparkle", this));
		NULL_CHECK_RETURN(pComponent, E_FAIL);
		m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);
	}

	// 버퍼
	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	return S_OK;
}

void CEffect_ThornSparkle::Play_Effect(const _vec3& _vPos, const _vec3& _vSize)
{
	m_vOffSet = _vPos;
	m_vSize = _vSize;
	m_bActive = true;
}

CEffect_ThornSparkle* CEffect_ThornSparkle::Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _pPos)
{
	CEffect_ThornSparkle* pInstance = new CEffect_ThornSparkle(pGraphicDev, _pPos);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Effect_ThornSparkle Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CEffect_ThornSparkle::Free()
{
	__super::Free();
}
