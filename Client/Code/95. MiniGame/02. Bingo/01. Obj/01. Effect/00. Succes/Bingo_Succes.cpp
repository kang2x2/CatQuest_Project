#include "stdafx.h"

#include "Export_Function.h"

#include "Bingo_Succes.h"

CBingoSucces::CBingoSucces(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pPlayer)
	: CEffect(pGraphicDev, OBJ_ID::EFFECT_BINGO_SUCCES)
	, m_iLerpLevel(0)
{
	m_pPlayer = _pPlayer;
}

CBingoSucces::CBingoSucces(const CBingoSucces& rhs)
	: CEffect(rhs)
{
}

CBingoSucces::~CBingoSucces()
{
}

HRESULT CBingoSucces::Ready_Object()
{
	__super::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	Ready_Lerp();

	m_bActive = true;

	return S_OK;
}

void CBingoSucces::Ready_Lerp()
{
	// y값
	m_tPosUpLerp.Init_Lerp(LERP_MODE::SMOOTHSTEP);
	m_tPosUpLerp.Set_Lerp(0.5f,
		m_pPlayer->Get_Transform()->Get_Info(INFO_POS).y,
		m_pPlayer->Get_Transform()->Get_Info(INFO_POS).y + 11.f);

	// 사이즈
	m_tSizeUpLerp.Init_Lerp(LERP_MODE::EASE_IN);
	m_tSizeUpLerp.Set_Lerp(0.5f, 0.f, 3.5f);

	// 삭제
	m_tDeleteLerp.Init_Lerp(LERP_MODE::EASE_IN);
	m_tDeleteLerp.Set_Lerp(0.5f, 3.5f, 0.f);

	// 투명도
	m_tTranslucentLerp.Init_Lerp(LERP_MODE::EASE_IN);
	m_tTranslucentLerp.Set_Lerp(0.5f, 255.f, 0.f);
}

_int CBingoSucces::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);
	Engine::Add_RenderGroup(RENDER_WDUI, this); // 무조건 늦게 그려지게

	switch (m_iLerpLevel)
	{
	case 0:
		m_tPosUpLerp.Update_Lerp(fTimeDelta);
		m_tSizeUpLerp.Update_Lerp(fTimeDelta);

		if (!m_tSizeUpLerp.bActive)
			m_iLerpLevel += 1;
		break;
	case 1:
		m_tDeleteLerp.Update_Lerp(fTimeDelta);

		if (!m_tDeleteLerp.bActive)
			m_iLerpLevel += 1;
		break;
	case 2:
		m_tTranslucentLerp.Update_Lerp(fTimeDelta);

		if (!m_tTranslucentLerp.bActive)
			m_iLerpLevel += 1;
		break;
	case 3:
		break;	
	}


	// 위치
	m_pTransformCom->Set_Pos({
		m_pPlayer->Get_Transform()->Get_Info(INFO_POS).x,
		m_tPosUpLerp.fCurValue,
		m_pPlayer->Get_Transform()->Get_Info(INFO_POS).z});

	// 사이즈
	m_pTransformCom->Set_Scale({m_tSizeUpLerp.fCurValue, m_tSizeUpLerp.fCurValue , m_tSizeUpLerp.fCurValue });

	// 알파
	m_iTranslucent = m_tTranslucentLerp.fCurValue;

	// 삭제
	if (m_iTranslucent <= 0)
		CEventMgr::GetInstance()->Delete_Obj(this);


	return iExit;
}

void CBingoSucces::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CBingoSucces::Render_Object()
{
	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB((_int)m_iTranslucent, 255, 255, 255));
	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

	// 랜더
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());
	m_pTextureCom->Render_Texture();
	m_pBufferCom->Render_Buffer();
}

HRESULT CBingoSucces::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Bingo_Bingo", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);
	
	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	return S_OK;
}

CBingoSucces* CBingoSucces::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pPlayer)
{
	CBingoSucces* pInstance = new CBingoSucces(pGraphicDev, _pPlayer);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("BingoSucces Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CBingoSucces::Free()
{
	__super::Free();
}
