#include "stdafx.h"

#include "Export_Function.h"

#include "HealEffect.h"
#include "Player.h"
#include "SoundMgr.h"

CHealEffect::CHealEffect(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
	: CEffect(pGraphicDev, _pOwnerObject, OBJ_ID::EFFECT_SKILL_HEAL)
	, m_iEffectLevel(0), m_iSparkleCount(0), m_iSparkle2Level(0)
	, m_bActiveDrop(true)
{
	m_pOwnerobject = _pOwnerObject;
}

CHealEffect::CHealEffect(const CHealEffect& rhs)
	: CEffect(rhs)
{
}

CHealEffect::~CHealEffect()
{
}

HRESULT CHealEffect::Ready_Object()
{
	__super::Ready_Object();

	// CGameObject::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	//_pDropTransCom->Set_Pos(_vec3{ m_pOwnerobject->Get_Transform()->Get_Info(INFO_POS).x,
	//	m_pOwnerobject->Get_Transform()->Get_Info(INFO_POS).y - m_pOwnerobject->Get_Transform()->Get_Scale().y * 0.5f,
	//	m_pOwnerobject->Get_Transform()->Get_Info(INFO_POS).z });
	//_pTransformCom->Set_Scale(_vec3{ 5.12f, 5.12f, 5.12f });

	m_pDropTransCom->Set_Scale({ 5.12f, 5.12f, 5.12f });

	Ready_Lerp();

	m_bActive = true;
	m_iPawTranslucent = 255;

	m_szName = L"HealEffect";

	m_bHeal = false;

	return S_OK;
}

void CHealEffect::Ready_Lerp()
{
	// Drop
	m_tDropLerp.Init_Lerp(LERP_MODE::EASE_IN);
	m_tDropLerp.Set_Lerp(0.2f, m_pOwnerobject->Get_Transform()->Get_Info(INFO_POS).y + 15.f, m_pOwnerobject->Get_Transform()->Get_Info(INFO_POS).y);

	// Paw
	m_tPawSizeLerp.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_tPawSizeLerp.Set_Lerp(0.2f, 0.f, 3.f);
	m_tPawTlLerp.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_tPawTlLerp.Set_Lerp(0.4f, 255.f, 0.f);

	// Sparkle1
	// 1
	m_vecSparkle1[0].m_tPosLerpX.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_vecSparkle1[0].m_tPosLerpX.Set_Lerp(0.2f, 0.f, -5.5f);

	m_vecSparkle1[0].m_tPosLerpY.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_vecSparkle1[0].m_tPosLerpY.Set_Lerp(0.2f, 0.f, - 1.f);

	// 2
	m_vecSparkle1[1].m_tPosLerpX.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_vecSparkle1[1].m_tPosLerpX.Set_Lerp(0.2f, 0.f, -4.f);

	m_vecSparkle1[1].m_tPosLerpY.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_vecSparkle1[1].m_tPosLerpY.Set_Lerp(0.2f, 0.f, 3.5f);
	// 3
	m_vecSparkle1[2].m_tPosLerpX.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_vecSparkle1[2].m_tPosLerpX.Set_Lerp(0.2f, 0.f, 1.f);

	m_vecSparkle1[2].m_tPosLerpY.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_vecSparkle1[2].m_tPosLerpY.Set_Lerp(0.2f, 0.f, 6.5f);

	// 4
	m_vecSparkle1[3].m_tPosLerpX.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_vecSparkle1[3].m_tPosLerpX.Set_Lerp(0.2f, 0.f, 5.f);

	m_vecSparkle1[3].m_tPosLerpY.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_vecSparkle1[3].m_tPosLerpY.Set_Lerp(0.2f, 0.f, 1.f);

	for (_int i = 0; i < SPARKLE_COUNT; ++i)
	{
		m_vecSparkle1[i].m_tSizeUpLerp.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
		m_vecSparkle1[i].m_tSizeUpLerp.Set_Lerp(0.2f, 0.f, 1.f + (i * 0.2f));
		m_vecSparkle1[i].m_tSizeDownLerp.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
		m_vecSparkle1[i].m_tSizeDownLerp.Set_Lerp(0.2f, 1.f + (i * 0.2f), 0.f);
	}

	// sparkle2
	// 1
	m_vecSparkle2[0].m_tSizeUpLerp.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_vecSparkle2[0].m_tSizeUpLerp.Set_Lerp(0.15f, 0.f, 1.2f);
	m_vecSparkle2[0].m_tSizeDownLerp.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_vecSparkle2[0].m_tSizeDownLerp.Set_Lerp(0.15f, 1.2f, 0.f);

	// 2
	m_vecSparkle2[1].m_tSizeUpLerp.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_vecSparkle2[1].m_tSizeUpLerp.Set_Lerp(0.15f, 0.f, 1.4f);
	m_vecSparkle2[1].m_tSizeDownLerp.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_vecSparkle2[1].m_tSizeDownLerp.Set_Lerp(0.15f, 1.4f, 0.f);

	// 3
	m_vecSparkle2[2].m_tSizeUpLerp.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_vecSparkle2[2].m_tSizeUpLerp.Set_Lerp(0.15f, 0.f, 1.6f);
	m_vecSparkle2[2].m_tSizeDownLerp.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_vecSparkle2[2].m_tSizeDownLerp.Set_Lerp(0.15f, 1.6f, 0.f);

	// 4
	m_vecSparkle2[3].m_tSizeUpLerp.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_vecSparkle2[3].m_tSizeUpLerp.Set_Lerp(0.15f, 0.f, 1.8f);
	m_vecSparkle2[3].m_tSizeDownLerp.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_vecSparkle2[3].m_tSizeDownLerp.Set_Lerp(0.15f, 1.8f, 0.f);


}

_int CHealEffect::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);
	Engine::Add_RenderGroup(RENDER_WDUI, this);

	switch (m_iEffectLevel)
	{
	case 0:
		m_tDropLerp.Update_Lerp(fTimeDelta);

		m_pDropTransCom->Set_Pos({
			m_pOwnerobject->Get_Transform()->Get_Info(INFO_POS).x,
			m_tDropLerp.fCurValue,
			m_pOwnerobject->Get_Transform()->Get_Info(INFO_POS).z });

		if (!m_tDropLerp.bActive)
		{
			CSoundMgr::GetInstance()->PlaySound(L"skill_healingpaw.wav", CHANNEL_ID::EFFECT_0, VOLUME_PLAYER_SKILL);
			m_iEffectLevel += 1;
			m_bActiveDrop = false;
			m_bHeal = true;

		}
		break;
	case 1:
		for (_int i = 0; i < SPARKLE_COUNT; ++i)
		{
			m_vecSparkle1[i].m_tPosLerpX.Update_Lerp(fTimeDelta);
			m_vecSparkle1[i].m_tPosLerpY.Update_Lerp(fTimeDelta);
			m_vecSparkle1[i].m_tSizeUpLerp.Update_Lerp(fTimeDelta);

			m_vecSparkle1[i].m_pSparkle1_TransCom->Set_Pos({
				m_pOwnerobject->Get_Transform()->Get_Info(INFO_POS).x 
				+ m_vecSparkle1[i].m_tPosLerpX.fCurValue,
				m_vecSparkle1[i].m_tPosLerpY.fCurValue,
				m_pOwnerobject->Get_Transform()->Get_Info(INFO_POS).z
				});

			if (!m_vecSparkle1[i].m_tSizeUpLerp.bActive)
			{
				m_vecSparkle1[i].m_tSizeDownLerp.Update_Lerp(fTimeDelta);
				m_vecSparkle1[i].m_pSparkle1_TransCom->Set_Scale({
					m_vecSparkle1[i].m_tSizeDownLerp.fCurValue,
					m_vecSparkle1[i].m_tSizeDownLerp.fCurValue,
					m_vecSparkle1[i].m_tSizeDownLerp.fCurValue});
			}
			else
			{
				m_vecSparkle1[i].m_pSparkle1_TransCom->Set_Scale({
					m_vecSparkle1[i].m_tSizeDownLerp.fCurValue,
					m_vecSparkle1[i].m_tSizeDownLerp.fCurValue,
					m_vecSparkle1[i].m_tSizeDownLerp.fCurValue });
			}

			if (!m_vecSparkle1[i].m_tSizeDownLerp.bActive)
			{
				m_iSparkleCount += 1;
			}
		}

		m_tPawSizeLerp.Update_Lerp(fTimeDelta);
		m_pPawTransCom->Set_Pos(m_pOwnerobject->Get_Transform()->Get_Info(INFO_POS));
		m_pPawTransCom->Set_Scale({
			m_tPawSizeLerp.fCurValue,
			m_tPawSizeLerp.fCurValue,
			m_tPawSizeLerp.fCurValue });

		if (m_iSparkleCount >= 3)
		{
			m_iEffectLevel += 1;
		}
		break;
	case 2:
		m_tPawTlLerp.Update_Lerp(fTimeDelta);
		m_pPawTransCom->Set_Pos(m_pOwnerobject->Get_Transform()->Get_Info(INFO_POS));
		m_iPawTranslucent = (_int)m_tPawTlLerp.fCurValue;
		if (!m_tPawTlLerp.bActive)
		{
			Sparkle2_Update(fTimeDelta);
		}
		break;

	case 3:
		CEventMgr::GetInstance()->Delete_Obj(this);
		break;
	}




	if (!m_pOwnerobject->Is_Active())
	{
		CEventMgr::GetInstance()->Delete_Obj(this);
		return iExit;
	}

	return iExit;
}


void CHealEffect::Sparkle2_Update(const _float& fTimeDelta)
{
	switch(m_iSparkle2Level)
	{
	case 0:
		m_vecSparkle2[0].m_tSizeUpLerp.Update_Lerp(fTimeDelta);

		if (!m_vecSparkle2[0].m_tSizeUpLerp.bActive)
		{
			m_vecSparkle2[0].m_tSizeDownLerp.Update_Lerp(fTimeDelta);
			m_vecSparkle2[0].m_pSparkle2_TransCom->Set_Scale({
				m_vecSparkle2[0].m_tSizeDownLerp.fCurValue,
				m_vecSparkle2[0].m_tSizeDownLerp.fCurValue,
				m_vecSparkle2[0].m_tSizeDownLerp.fCurValue });
		}
		else
		{
			m_vecSparkle2[0].m_pSparkle2_TransCom->Set_Scale({
				m_vecSparkle2[0].m_tSizeUpLerp.fCurValue,
				m_vecSparkle2[0].m_tSizeUpLerp.fCurValue,
				m_vecSparkle2[0].m_tSizeUpLerp.fCurValue });
		}

		m_vecSparkle2[0].m_pSparkle2_TransCom->Set_Pos({
			m_pOwnerobject->Get_Transform()->Get_Info(INFO_POS).x
			+ 3 * 0.5f,
			m_pOwnerobject->Get_Transform()->Get_Info(INFO_POS).y,
			m_pOwnerobject->Get_Transform()->Get_Info(INFO_POS).z
			});

		if (!m_vecSparkle2[0].m_tSizeDownLerp.bActive)
		{
			m_iSparkle2Level += 1;
		}
		break;
	case 1:
		m_vecSparkle2[1].m_tSizeUpLerp.Update_Lerp(fTimeDelta);

		if (!m_vecSparkle2[1].m_tSizeUpLerp.bActive)
		{
			m_vecSparkle2[1].m_tSizeDownLerp.Update_Lerp(fTimeDelta);
			m_vecSparkle2[1].m_pSparkle2_TransCom->Set_Scale({
				m_vecSparkle2[1].m_tSizeDownLerp.fCurValue,
				m_vecSparkle2[1].m_tSizeDownLerp.fCurValue,
				m_vecSparkle2[1].m_tSizeDownLerp.fCurValue });
		}
		else
		{
			m_vecSparkle2[1].m_pSparkle2_TransCom->Set_Scale({
				m_vecSparkle2[1].m_tSizeUpLerp.fCurValue,
				m_vecSparkle2[1].m_tSizeUpLerp.fCurValue,
				m_vecSparkle2[1].m_tSizeUpLerp.fCurValue });
		}

		m_vecSparkle2[1].m_pSparkle2_TransCom->Set_Pos({
			m_pOwnerobject->Get_Transform()->Get_Info(INFO_POS).x
			- 3 * 0.6f,
			m_pOwnerobject->Get_Transform()->Get_Info(INFO_POS).y
			- 3 * 0.5f,
			m_pOwnerobject->Get_Transform()->Get_Info(INFO_POS).z
			});

		if (!m_vecSparkle2[1].m_tSizeDownLerp.bActive)
		{
			m_iSparkle2Level += 1;
		}
		break;
	case 2:
		m_vecSparkle2[2].m_tSizeUpLerp.Update_Lerp(fTimeDelta);

		if (!m_vecSparkle2[2].m_tSizeUpLerp.bActive)
		{
			m_vecSparkle2[2].m_tSizeDownLerp.Update_Lerp(fTimeDelta);
			m_vecSparkle2[2].m_pSparkle2_TransCom->Set_Scale({
				m_vecSparkle2[2].m_tSizeDownLerp.fCurValue,
				m_vecSparkle2[2].m_tSizeDownLerp.fCurValue,
				m_vecSparkle2[2].m_tSizeDownLerp.fCurValue });
		}
		else
		{
			m_vecSparkle2[2].m_pSparkle2_TransCom->Set_Scale({
				m_vecSparkle2[2].m_tSizeUpLerp.fCurValue,
				m_vecSparkle2[2].m_tSizeUpLerp.fCurValue,
				m_vecSparkle2[2].m_tSizeUpLerp.fCurValue });
		}

		m_vecSparkle2[2].m_pSparkle2_TransCom->Set_Pos({
			m_pOwnerobject->Get_Transform()->Get_Info(INFO_POS).x
			- 3 * 0.7f,
			m_pOwnerobject->Get_Transform()->Get_Info(INFO_POS).y
			+ 3 * 0.5f,
			m_pOwnerobject->Get_Transform()->Get_Info(INFO_POS).z
			});

		if (!m_vecSparkle2[2].m_tSizeDownLerp.bActive)
		{
			m_iSparkle2Level += 1;
		}
		break;
	case 3:
		m_vecSparkle2[3].m_tSizeUpLerp.Update_Lerp(fTimeDelta);

		if (!m_vecSparkle2[3].m_tSizeUpLerp.bActive)
		{
			m_vecSparkle2[3].m_tSizeDownLerp.Update_Lerp(fTimeDelta);
			m_vecSparkle2[3].m_pSparkle2_TransCom->Set_Scale({
				m_vecSparkle2[3].m_tSizeDownLerp.fCurValue,
				m_vecSparkle2[3].m_tSizeDownLerp.fCurValue,
				m_vecSparkle2[3].m_tSizeDownLerp.fCurValue });
		}
		else
		{
			m_vecSparkle2[3].m_pSparkle2_TransCom->Set_Scale({
				m_vecSparkle2[3].m_tSizeUpLerp.fCurValue,
				m_vecSparkle2[3].m_tSizeUpLerp.fCurValue,
				m_vecSparkle2[3].m_tSizeUpLerp.fCurValue });
		}

		m_vecSparkle2[3].m_pSparkle2_TransCom->Set_Pos({
			m_pOwnerobject->Get_Transform()->Get_Info(INFO_POS).x
			+ 3 * 0.7f,
			m_pOwnerobject->Get_Transform()->Get_Info(INFO_POS).y
			+ 3 * 0.5f,
			m_pOwnerobject->Get_Transform()->Get_Info(INFO_POS).z
			});

		if (!m_vecSparkle2[3].m_tSizeDownLerp.bActive)
		{
			m_iSparkle2Level += 1;
		}
		break;
	case 4:
		m_iEffectLevel += 1;
		break;
	}
}

void CHealEffect::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CHealEffect::Render_Object()
{
	NULL_CHECK(m_pOwnerobject);

	// Drop
	if (m_bActiveDrop)
	{
		m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));
		m_pDropTexCom->Render_Texture();
		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pDropTransCom->Get_WorldMat());
		m_pBufferCom->Render_Buffer();
	}

	// sparkle1
	for (_int i = 0; i < SPARKLE_COUNT; ++i)
	{
		m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));
		m_vecSparkle1[i].m_pSparkle1_TexCom->Render_Texture();
		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_vecSparkle1[i].m_pSparkle1_TransCom->Get_WorldMat());
		m_pBufferCom->Render_Buffer();
	}

	// sparkle2
	for (_int i = 0; i < SPARKLE_COUNT; ++i)
	{
		m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));
		m_vecSparkle2[i].m_pSparkle2_TexCom->Render_Texture();
		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_vecSparkle2[i].m_pSparkle2_TransCom->Get_WorldMat());
		m_pBufferCom->Render_Buffer();
	}


	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(m_iPawTranslucent, 255, 255, 255));
	m_pPawTexCom->Render_Texture();
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pPawTransCom->Get_WorldMat());
	m_pBufferCom->Render_Buffer();
	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));


	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));
	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));
}

HRESULT CHealEffect::Add_Component()
{
	CComponent* pComponent = nullptr;

	// Texture
	pComponent = m_pDropTexCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Skill_HealDrop", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pPawTexCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Skill_HealPaw", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	// Texture - Sparkle1
	for (_int i = 0; i < SPARKLE_COUNT; ++i)
	{
		pComponent = m_vecSparkle1[i].m_pSparkle1_TexCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Skill_HealSpark", this));
		NULL_CHECK_RETURN(pComponent, E_FAIL);
		m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

		pComponent = m_vecSparkle1[i].m_pSparkle1_TransCom = dynamic_cast<CTransform*>(CProtoMgr::GetInstance()->Clone_Proto(COMPONENT_TYPE::TRANSFORM, this));
		NULL_CHECK_RETURN(pComponent, E_FAIL);
		m_mapComponent[ID_DYNAMIC].emplace(COMPONENT_TYPE::TRANSFORM, pComponent);
	}
	// Texture - Sparkle2
	for (_int i = 0; i < SPARKLE_COUNT; ++i)
	{
		pComponent = m_vecSparkle2[i].m_pSparkle2_TexCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Skill_HealSpark", this));
		NULL_CHECK_RETURN(pComponent, E_FAIL);
		m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

		pComponent = m_vecSparkle2[i].m_pSparkle2_TransCom = dynamic_cast<CTransform*>(CProtoMgr::GetInstance()->Clone_Proto(COMPONENT_TYPE::TRANSFORM, this));
		NULL_CHECK_RETURN(pComponent, E_FAIL);
		m_mapComponent[ID_DYNAMIC].emplace(COMPONENT_TYPE::TRANSFORM, pComponent);
	}


	// Transform
	pComponent = m_pDropTransCom = dynamic_cast<CTransform*>(CProtoMgr::GetInstance()->Clone_Proto(COMPONENT_TYPE::TRANSFORM, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].emplace(COMPONENT_TYPE::TRANSFORM, pComponent);
	
	pComponent = m_pPawTransCom = dynamic_cast<CTransform*>(CProtoMgr::GetInstance()->Clone_Proto(COMPONENT_TYPE::TRANSFORM, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].emplace(COMPONENT_TYPE::TRANSFORM, pComponent);

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	return S_OK;
}

void CHealEffect::Play_Effect(const _vec3& _vPos, const _vec3& _vSize)
{
	m_vOffSet = _vPos;
	m_vSize = _vSize;
	m_bActive = true;
}

CHealEffect* CHealEffect::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
{
	CHealEffect* pInstance = new CHealEffect(pGraphicDev, _pOwnerObject);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("HealEffect Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CHealEffect::Free()
{
	__super::Free();
}
