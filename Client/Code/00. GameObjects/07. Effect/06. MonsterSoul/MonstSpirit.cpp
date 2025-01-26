#include "stdafx.h"

#include "Export_Function.h"
#include "EventMgr.h"

#include "MonstSpirit.h"

CMonstSpirit::CMonstSpirit(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& _pPos)
	: CEffect(pGraphicDev, OBJ_ID::EFFECT_MONSTERSPIRIT)
{
	m_vSpritPos		= _pPos;
	m_vWavePos		= _pPos;
	m_vBlueOrbPos = _pPos;
}

CMonstSpirit::CMonstSpirit(const CMonstSpirit& rhs)
	: CEffect(rhs),
	m_pTexSpritCom(rhs.m_pTexSpritCom),
	m_pTexWaveCom(rhs.m_pTexWaveCom),
	m_pTexBlueOrbCom(rhs.m_pTexBlueOrbCom),
	m_pTexYellowOrbCom(rhs.m_pTexYellowOrbCom),

	m_pSpritTransCom(rhs.m_pSpritTransCom),
	m_pWaveTransCom(rhs.m_pWaveTransCom)
{
	// 위 적어둔 것들 클론 해서 사용하지 않기 때문에 의미가 없다 사실상.
}

CMonstSpirit::~CMonstSpirit()
{
}

HRESULT CMonstSpirit::Ready_Object()
{
	__super::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_bActive = true;
	m_iSpiritTranslucent = 0;

	// 영혼
	m_iSpiritMaxAlpha = 170;
	m_fSpritSizeY = 1.5f;
	m_bExtinction = false;
	// 웨이브
	m_fWaveSize = 0.f;
	// 파랑구
	m_fRotZ = 15.f;
	m_fBlueOrbSize = 0.f;
	
	// 노랑구

	// 영혼 제외 알파값
	m_iOtherMaxAlpha = 170;
	m_iOtherTranslucent = 0;
	return S_OK;
}

_int CMonstSpirit::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);
	Engine::Add_RenderGroup(RENDER_WDUI, this); 

	// 영혼
	m_pSpritTransCom->Set_Scale(_vec3{ 2.f, m_fSpritSizeY, 2.f });
	m_pSpritTransCom->Set_Pos(m_vSpritPos);
	// 웨이브
	m_pWaveTransCom->Set_Scale(_vec3{ m_fWaveSize, m_fWaveSize, m_fWaveSize });
	m_pWaveTransCom->Set_Pos(m_vWavePos);

	// 파란구
	for (_int i = 0; i < 3; ++i)
	{
		m_sBlueOrb[i].m_pBlueOrbTransCom->Set_Scale(_vec3{ 
			m_fBlueOrbSize + i * 0.1f,
			m_fBlueOrbSize + i * 0.1f,
			m_fBlueOrbSize + i * 0.1f });
		m_sBlueOrb[i].m_pBlueOrbTransCom->Set_Pos(m_vBlueOrbPos);
		m_sBlueOrb[i].m_pBlueOrbTransCom->Set_Rot(_vec3{ 0.f, 0.f, m_fRotZ * i });
	}

	Alpha_Update();

	return iExit;
}

void CMonstSpirit::LateUpdate_Object()
{
	// 영혼
	m_fSpritSizeY += 0.1f;
	m_vSpritPos.y += 0.2f;
	// 웨이브
	m_fWaveSize += 0.15f;
	// 파란구
	m_fBlueOrbSize += 0.2f;

	__super::LateUpdate_Object();
}

void CMonstSpirit::Render_Object()
{
	// 영혼
	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(m_iSpiritTranslucent, 255, 255, 255));

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pSpritTransCom->Get_WorldMat());
	m_pTexSpritCom->Render_Texture();
	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));

	// 그 외
	// Wave
	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(m_iOtherTranslucent, 255, 255, 255));

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pWaveTransCom->Get_WorldMat());
	m_pTexWaveCom->Render_Texture();
	m_pBufferCom->Render_Buffer();

	// Orb
	for (_int i = 0; i < 3; ++i)
	{
		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_sBlueOrb[i].m_pBlueOrbTransCom->Get_WorldMat());
		m_sBlueOrb[i].m_pBlueOrbTextureCom->Render_Texture();
		m_pBufferCom->Render_Buffer();
	}


	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));


}

HRESULT CMonstSpirit::Add_Component()
{
	CComponent* pComponent = nullptr;

	// 스피릿 
	pComponent = m_pSpritTransCom = dynamic_cast<CTransform*>(CProtoMgr::GetInstance()->Clone_Proto(COMPONENT_TYPE::TRANSFORM, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].emplace(COMPONENT_TYPE::TRANSFORM, pComponent);

	pComponent = m_pTexSpritCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_MonsterSpirit", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);
	
	// 웨이브
	pComponent = m_pWaveTransCom = dynamic_cast<CTransform*>(CProtoMgr::GetInstance()->Clone_Proto(COMPONENT_TYPE::TRANSFORM, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].emplace(COMPONENT_TYPE::TRANSFORM, pComponent);

	pComponent = m_pTexWaveCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Spiritwave", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	// 파란구
	for (_int i = 0; i < 3; ++i)
	{
		pComponent = m_sBlueOrb[i].m_pBlueOrbTransCom = dynamic_cast<CTransform*>(CProtoMgr::GetInstance()->Clone_Proto(COMPONENT_TYPE::TRANSFORM, this));
		NULL_CHECK_RETURN(pComponent, E_FAIL);
		m_mapComponent[ID_DYNAMIC].emplace(COMPONENT_TYPE::TRANSFORM, pComponent);

		pComponent = m_sBlueOrb[i].m_pBlueOrbTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Spiritorb", this));
		NULL_CHECK_RETURN(pComponent, E_FAIL);
		m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);
	}

	// 버퍼
	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);
}

void CMonstSpirit::Play_Effect(const _vec3& _vPos, const _vec3& _vSize)
{
	m_vOffSet = _vPos;
	m_vSize = _vSize;
	m_bActive = true;
}

void CMonstSpirit::Alpha_Update()
{
	if (!m_bExtinction) 
	{
		m_iSpiritTranslucent += 10;		

		// 영혼
		if (m_iSpiritTranslucent > m_iSpiritMaxAlpha)
		{
			m_bExtinction = true;
			m_iOtherTranslucent -= 10;
		}
		// 그 외
		if (m_iOtherTranslucent < m_iOtherMaxAlpha)
		{
			m_iOtherTranslucent += 10;
		}
	}
	else
	{
		m_iSpiritTranslucent -= 10;
		// 영혼
		if (m_iSpiritTranslucent < 10)
		{
			CEventMgr::GetInstance()->Delete_Obj(this);
		}

		// 그 외
		if (m_iOtherTranslucent > 10)
		{
			m_iOtherTranslucent -= 10;
		}
	}
}

CMonstSpirit* CMonstSpirit::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& _pPos)
{
	CMonstSpirit* pInstance = new CMonstSpirit(pGraphicDev, _pPos);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("MonsterSpirit Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CMonstSpirit::Free()
{
	__super::Free();
}
