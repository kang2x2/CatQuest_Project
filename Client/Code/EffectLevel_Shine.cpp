#include "stdafx.h"
#include "EffectLevel_Shine.h"
#include "Export_Function.h"
#include "Player.h"

CEffectLevel_Shine::CEffectLevel_Shine(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
	: CEffect(pGraphicDev, _pOwnerObject, OBJ_ID::EFFECT_LEVELUP_SHINE)
{
	m_pOwnerobject = _pOwnerObject;
}

CEffectLevel_Shine::CEffectLevel_Shine(const CEffectLevel_Shine& rhs)
	: CEffect(rhs)
{
}

CEffectLevel_Shine::~CEffectLevel_Shine()
{
}

HRESULT CEffectLevel_Shine::Ready_Object()
{
	__super::Ready_Object();

	m_bActive = false;

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	NULL_CHECK_RETURN(m_pOwnerobject, E_FAIL);

	for (_uint i = 0; i < 3; ++i)
	{
		D3DXMatrixIdentity(&m_matEffect[i]);
	}

	m_matEffect[2]._11 = 125.f * 2.5;
	m_matEffect[2]._22 = 125.f * 2.5;
	

	return S_OK;
}

_int CEffectLevel_Shine::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);
	Engine::Add_RenderGroup(RENDER_VIEWUI, this);

	if (m_fShineAlpha2 <= 0)
	{
		m_bActive = false;
	}
		
	// ±Û·Î¿ì
	m_tPos_Y_Glow.Update_Lerp(fTimeDelta);
	m_tSize_Y_Glow.Update_Lerp(fTimeDelta);

	// »þÀÎ
	m_tSize_Shine.Update_Lerp(fTimeDelta);
	m_tAlpha_Shine.Update_Lerp(fTimeDelta);

	m_tAlpha_Shine2.Update_Lerp(fTimeDelta);

	
	
	return iExit;
}

void CEffectLevel_Shine::LateUpdate_Object()
{
	if (m_tSize_Y_Glow.bActive)
	{
		m_matEffect[0]._22 = m_tSize_Y_Glow.fCurValue;
	}
	else if(m_tPos_Y_Glow.fCurValue <= 80.f && !m_bStartShine)
	{
		CCameraMgr::GetInstance()->Shake_Camera();

		m_matEffect[0]._11 = 0.f;
		m_matEffect[0]._22 = 0.f;

		//»þÀÎ1
		m_tSize_Shine.Init_Lerp(LERP_MODE::EASE_IN);
		m_tAlpha_Shine.Init_Lerp(LERP_MODE::SMOOTHSTEP);

		m_tSize_Shine.Set_Lerp(0.5f, _vec3{ 100.f * 2.5, 100.f * 2.5, 0.f }, _vec3{ 100.f * 7, 100.f * 7, 0.f });
		m_tAlpha_Shine.Set_Lerp(0.5f, m_fShineAlpha, 0.f);
		m_tAlpha_Shine.fCurValue = m_tAlpha_Shine.fStartValue;

		// »þÀÎ2
		m_tAlpha_Shine2.Init_Lerp(LERP_MODE::EXPONENTIAL);
		m_tAlpha_Shine2.Set_Lerp(3.f, m_fShineAlpha2, 0.f);
		m_tAlpha_Shine2.fCurValue = m_tAlpha_Shine2.fStartValue;

		m_bStartShine = true;
	}

	if (m_tAlpha_Shine.bActive)
	{
		_vec3 vShineSize = m_tSize_Shine.vCurVec;
		m_matEffect[1]._11 = vShineSize.x;
		m_matEffect[1]._22 = vShineSize.y;

		m_fShineAlpha = m_tAlpha_Shine.fCurValue;
	}
	
	if (m_tAlpha_Shine2.bActive)
	{
		m_fShineAlpha2 = m_tAlpha_Shine2.fCurValue;
	}

	Follow_Owner();

	__super::LateUpdate_Object();
}

void CEffectLevel_Shine::Render_Object()
{
	
	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matEffect[0]);

	m_pTex_Glow->Render_Texture();
	m_pBufferCom->Render_Buffer();

	if (!m_tSize_Y_Glow.bActive)
	{
		if (m_tAlpha_Shine.bActive)
		{
			m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(_uint(m_fShineAlpha), 255, 255, 255));
			m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matEffect[1]);

			m_pTex_Shine->Render_Texture();
			m_pBufferCom->Render_Buffer();
		}
		
		if (m_tAlpha_Shine2.bActive)
		{
			m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(_uint(m_fShineAlpha2), 255, 255, 255));
			m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matEffect[2]);

			m_pTex_Shine_02->Render_Texture();
			m_pBufferCom->Render_Buffer();
		}
	
	

		m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	
}

void CEffectLevel_Shine::Play_Effect(const _vec3& _vPos, const _vec3& _vSize)
{
	NULL_CHECK(m_pOwnerobject);

	m_bStartShine = false;

	ZeroMemory(&m_tSize_Y_Glow, sizeof(LERP_FLOAT_INFO));
	ZeroMemory(&m_tPos_Y_Glow, sizeof(LERP_FLOAT_INFO));
	ZeroMemory(&m_tAlpha_Shine, sizeof(LERP_FLOAT_INFO));
	ZeroMemory(&m_tAlpha_Shine2, sizeof(LERP_FLOAT_INFO));
	ZeroMemory(&m_tSize_Shine, sizeof(LERP_VEC3_INFO));

	m_fGlow_PosY = (WINCY >> 1) + 20;
	m_fGlow_SizeY = 199.f * 0.3 * 5;

	m_fShineAlpha = 255.f;
	m_fShineAlpha2 = 235.f;

	m_matEffect[0]._11 = 199.f * 0.3;
	m_matEffect[0]._22 = m_fGlow_SizeY;

	m_tPos_Y_Glow.Init_Lerp(LERP_MODE::EASE_IN);
	m_tSize_Y_Glow.Init_Lerp(LERP_MODE::SMOOTHSTEP);

	m_tPos_Y_Glow.Set_Lerp(0.2f, m_fGlow_PosY, 0);
	m_tSize_Y_Glow.Set_Lerp(0.2f, m_fGlow_SizeY, 100.f);

	m_bActive = true;
}

void CEffectLevel_Shine::Follow_Owner()
{
	NULL_CHECK(m_pOwnerobject);

	_vec3 vPlayerPos = m_pOwnerobject->Get_Transform()->Get_Info(INFO::INFO_POS);

	_matrix matView = CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Get_MatView();
	_matrix matProj = CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Get_MatProj();
	D3DVIEWPORT9 pViewport = CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Get_ViewPort();

	D3DXVec3TransformCoord(&vPlayerPos, &vPlayerPos, &matView);
	D3DXVec3TransformCoord(&vPlayerPos, &vPlayerPos, &matProj);

	_float ScreenX = vPlayerPos.x * (pViewport.Width / 2) + pViewport.X + (pViewport.Width / 2);
	_float ScreenY = WINCY - (-vPlayerPos.y * (pViewport.Height / 2) + pViewport.Y + (pViewport.Height / 2));

	vPlayerPos = { ScreenX , ScreenY, 0.f };

	_vec3 vOwnerPosShine;
	_vec3 vOwnerPosShine2;
	_vec3 vOwnerPosGlow = vOwnerPosShine2 = vOwnerPosShine = vPlayerPos;

	vOwnerPosGlow.y += m_tPos_Y_Glow.fCurValue;
	vOwnerPosShine.x += 5.f;

	_matrix matRot;
	D3DXMatrixRotationZ(&matRot, D3DXToRadian(1.5f));
	m_matEffect[2] *= matRot;


	memcpy(&m_matEffect[0].m[3], &vOwnerPosGlow, sizeof(_vec3));
	memcpy(&m_matEffect[1].m[3], &vOwnerPosShine, sizeof(_vec3));
	memcpy(&m_matEffect[2].m[3], &vOwnerPosShine2, sizeof(_vec3));
	
}

HRESULT CEffectLevel_Shine::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTex_Glow = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Glow", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTex_Shine_02 = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Shine02", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTex_Shine = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Shine", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	return S_OK;
}

CEffectLevel_Shine* CEffectLevel_Shine::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
{
	CEffectLevel_Shine* pInstance = new CEffectLevel_Shine(pGraphicDev, _pOwnerObject);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Level Effect_Shine Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CEffectLevel_Shine::Free()
{
	__super::Free();
}
