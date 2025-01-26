#include "stdafx.h"
#include "WeaponGetEffect.h"
#include "Export_Function.h"

#include "Player.h"

#include "WeaponGetUI.h"
#include "Item_Weapon.h"

#include "SoundMgr.h"

CWeaponGetEffect::CWeaponGetEffect(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pWeapon)
	: CUI(pGraphicDev, OBJ_ID::UI_WEAPON_GET_EFFECT_UI)
	, m_bSizeUp(false), m_bTimeSet(false), m_bResultStay(false), m_bReadySound(true)
	, m_ReadyEffect(false)
	, m_iStayCount(0), m_iAllTranslucent(0)
{
	m_pWeapon = _pWeapon;
}

CWeaponGetEffect::CWeaponGetEffect(const CWeaponGetEffect& rhs)
	: CUI(rhs)
{
}

CWeaponGetEffect::~CWeaponGetEffect()
{
}

HRESULT CWeaponGetEffect::Ready_Object()
{
	__super::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	D3DXMatrixIdentity(&m_matGlow);
	D3DXMatrixIdentity(&m_matShine);
	for (_int i = 0; i < MAX_SPARKLE_SIZE; ++i)
	{
		D3DXMatrixIdentity(&m_SparkleAry[i].m_matSparkle);
	}

	m_eUIType = UI_TYPE::VIEW;
	m_eUILayer = UI_LAYER::LV2;

	Ready_WeaponGlow();
	Ready_WeaponShine();
	Ready_Sparkle();

	m_tReadyEffectLerp.Init_Lerp(LERP_MODE::EASE_IN);
	m_tReadyEffectLerp.Set_Lerp(0.5f, 0.f, 255.f);

	return S_OK;
}

void CWeaponGetEffect::Ready_WeaponGlow()
{
	m_iWeaponAlpha = 255;

	m_fPosX = WINCX / 2.f;
	m_fPosY = WINCY / 2.f;
	m_fSizeX = 60.f * 0.4f;
	m_fSizeY = 120.f * 0.4f;
	m_matGlow._41 = m_fPosX;
	m_matGlow._42 = m_fPosY;
	m_matGlow._11 = m_fSizeX;
	m_matGlow._22 = m_fSizeY;

	m_fCurShineSize = m_fSizeX;

	// 초기 세팅
	// 무기 위치
	m_tRandomMoveLerpX.Init_Lerp(LERP_MODE::EASE_IN);
	m_tRandomMoveLerpX.Set_Lerp(0.1f, m_fPosX, m_fPosX + 5.f);
	m_tRandomMoveLerpX.fCurValue = m_tRandomMoveLerpX.fStartValue;

	m_tRandomMoveLerpY.Init_Lerp(LERP_MODE::EASE_IN);
	m_tRandomMoveLerpY.Set_Lerp(0.1f, m_fPosY, m_fPosY + 5.f);
	m_tRandomMoveLerpY.fCurValue = m_tRandomMoveLerpY.fStartValue;

	// 무기 사이즈 다운
	m_tSmallerLerpX.Init_Lerp(LERP_MODE::EASE_IN);
	m_tSmallerLerpX.Set_Lerp(0.8f, m_fSizeX, m_fSizeX * 0.7f);
	m_tSmallerLerpY.Init_Lerp(LERP_MODE::EASE_IN);
	m_tSmallerLerpY.Set_Lerp(0.8f, m_fSizeY, m_fSizeY * 0.7f);
	// 무기 사이즈 서든
	m_tSuddenWeaponLerpX.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_tSuddenWeaponLerpX.Set_Lerp(0.4f, m_fSizeX * 0.7f, m_fSizeX * 2.f);
	m_tSuddenWeaponLerpY.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_tSuddenWeaponLerpY.Set_Lerp(0.4f, m_fSizeY * 0.7f, m_fSizeY * 2.f);

	// 무기 사이즈 복구
	m_tReturnWeaponSizeLerpX.Init_Lerp(LERP_MODE::EASE_IN);
	m_tReturnWeaponSizeLerpX.Set_Lerp(0.25f, m_fSizeX * 2.f, m_fSizeX);
	m_tReturnWeaponSizeLerpY.Init_Lerp(LERP_MODE::EASE_IN);
	m_tReturnWeaponSizeLerpY.Set_Lerp(0.25f, m_fSizeY * 2.f, m_fSizeY);

}

void CWeaponGetEffect::Ready_WeaponShine()
{
	m_fPosX = WINCX / 2.f;
	m_fPosY = WINCY / 2.f;
	m_fSizeX = 250.f * 0.5f;
	m_fSizeY = 250.f * 0.5f;
	m_matShine._41 = m_fPosX;
	m_matShine._42 = m_fPosY;
	m_matShine._11 = m_fSizeX;
	m_matShine._22 = m_fSizeY;

	// 샤이닝 사이즈 서든
	m_tSuddenShineLerp.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_tSuddenShineLerp.Set_Lerp(0.25f, m_fSizeX * 0.7f, m_fSizeX * 10.f);
	// 샤이닝 사이즈 복구
	m_tReturnShineSizeLerp.Init_Lerp(LERP_MODE::EASE_IN);
	m_tReturnShineSizeLerp.Set_Lerp(0.25f, m_fSizeX * 10.f, m_fSizeX);

}

void CWeaponGetEffect::Ready_Sparkle()
{
	m_fPosX = WINCX / 2.f;
	m_fPosY = WINCY / 2.f;
	m_fSizeX = 80.f;
	m_fSizeY = 80.f;

	// 1번 별
	m_SparkleAry[0].m_fTempSize = m_fSizeX * 0.5f;
	m_SparkleAry[0].m_matSparkle._41 = m_fPosX;
	m_SparkleAry[0].m_matSparkle._42 = m_fPosY;

	m_SparkleAry[0].m_tMoveLerpX.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_SparkleAry[0].m_tMoveLerpX.Set_Lerp(0.5f, m_fPosX, m_fPosX - 200.f);
	m_SparkleAry[0].m_tMoveLerpX.fCurValue = m_SparkleAry[0].m_tMoveLerpX.fStartValue;

	m_SparkleAry[0].m_tMoveLerpY.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_SparkleAry[0].m_tMoveLerpY.Set_Lerp(0.5f, m_fPosY, m_fPosY + 100.f);
	m_SparkleAry[0].m_tMoveLerpY.fCurValue = m_SparkleAry[0].m_tMoveLerpY.fStartValue;

	// 2번 별
	m_SparkleAry[1].m_fTempSize = m_fSizeX * 0.2f;
	m_SparkleAry[1].m_matSparkle._41 = m_fPosX;
	m_SparkleAry[1].m_matSparkle._42 = m_fPosY;

	m_SparkleAry[1].m_tMoveLerpX.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_SparkleAry[1].m_tMoveLerpX.Set_Lerp(0.5f, m_fPosX, m_fPosX - 100.f);
	m_SparkleAry[1].m_tMoveLerpX.fCurValue = m_SparkleAry[1].m_tMoveLerpX.fStartValue;

	m_SparkleAry[1].m_tMoveLerpY.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_SparkleAry[1].m_tMoveLerpY.Set_Lerp(0.5f, m_fPosY, m_fPosY + 70.f);
	m_SparkleAry[1].m_tMoveLerpY.fCurValue = m_SparkleAry[1].m_tMoveLerpY.fStartValue;

	// 3번 별
	m_SparkleAry[2].m_fTempSize = m_fSizeX * 0.25f;
	m_SparkleAry[2].m_matSparkle._41 = m_fPosX;
	m_SparkleAry[2].m_matSparkle._42 = m_fPosY;

	m_SparkleAry[2].m_tMoveLerpX.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_SparkleAry[2].m_tMoveLerpX.Set_Lerp(0.6f, m_fPosX, m_fPosX - 110.f);
	m_SparkleAry[2].m_tMoveLerpX.fCurValue = m_SparkleAry[2].m_tMoveLerpX.fStartValue;

	m_SparkleAry[2].m_tMoveLerpY.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_SparkleAry[2].m_tMoveLerpY.Set_Lerp(0.6f, m_fPosY, m_fPosY - 70.f);
	m_SparkleAry[2].m_tMoveLerpY.fCurValue = m_SparkleAry[2].m_tMoveLerpY.fStartValue;

	// 4번 별
	m_SparkleAry[3].m_fTempSize = m_fSizeX * 0.2f;
	m_SparkleAry[3].m_matSparkle._41 = m_fPosX;
	m_SparkleAry[3].m_matSparkle._42 = m_fPosY;

	m_SparkleAry[3].m_tMoveLerpX.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_SparkleAry[3].m_tMoveLerpX.Set_Lerp(0.3f, m_fPosX, m_fPosX - 40.f);
	m_SparkleAry[3].m_tMoveLerpX.fCurValue = m_SparkleAry[3].m_tMoveLerpX.fStartValue;

	m_SparkleAry[3].m_tMoveLerpY.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_SparkleAry[3].m_tMoveLerpY.Set_Lerp(0.3f, m_fPosY, m_fPosY - 110.f);
	m_SparkleAry[3].m_tMoveLerpY.fCurValue = m_SparkleAry[3].m_tMoveLerpY.fStartValue;

	// 5번 별
	m_SparkleAry[4].m_fTempSize = m_fSizeX * 0.45f;
	m_SparkleAry[4].m_matSparkle._41 = m_fPosX;
	m_SparkleAry[4].m_matSparkle._42 = m_fPosY;

	m_SparkleAry[4].m_tMoveLerpX.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_SparkleAry[4].m_tMoveLerpX.Set_Lerp(0.7f, m_fPosX, m_fPosX + 150.f);
	m_SparkleAry[4].m_tMoveLerpX.fCurValue = m_SparkleAry[4].m_tMoveLerpX.fStartValue;

	m_SparkleAry[4].m_tMoveLerpY.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_SparkleAry[4].m_tMoveLerpY.Set_Lerp(0.7f, m_fPosY, m_fPosY - 120.f);
	m_SparkleAry[4].m_tMoveLerpY.fCurValue = m_SparkleAry[4].m_tMoveLerpY.fStartValue;

	// 6번별
	m_SparkleAry[5].m_fTempSize = m_fSizeX * 0.15f;
	m_SparkleAry[5].m_matSparkle._41 = m_fPosX;
	m_SparkleAry[5].m_matSparkle._42 = m_fPosY;

	m_SparkleAry[5].m_tMoveLerpX.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_SparkleAry[5].m_tMoveLerpX.Set_Lerp(0.5f, m_fPosX, m_fPosX + 200.f);
	m_SparkleAry[5].m_tMoveLerpX.fCurValue = m_SparkleAry[5].m_tMoveLerpX.fStartValue;

	m_SparkleAry[5].m_tMoveLerpY.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_SparkleAry[5].m_tMoveLerpY.Set_Lerp(0.5f, m_fPosY, m_fPosY - 5.f);
	m_SparkleAry[5].m_tMoveLerpY.fCurValue = m_SparkleAry[5].m_tMoveLerpY.fStartValue;

	// 7번별
	m_SparkleAry[6].m_fTempSize = m_fSizeX * 0.55f;
	m_SparkleAry[6].m_matSparkle._41 = m_fPosX;
	m_SparkleAry[6].m_matSparkle._42 = m_fPosY;

	m_SparkleAry[6].m_tMoveLerpX.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_SparkleAry[6].m_tMoveLerpX.Set_Lerp(0.5f, m_fPosX, m_fPosX + 240.f);
	m_SparkleAry[6].m_tMoveLerpX.fCurValue = m_SparkleAry[6].m_tMoveLerpX.fStartValue;

	m_SparkleAry[6].m_tMoveLerpY.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_SparkleAry[6].m_tMoveLerpY.Set_Lerp(0.5f, m_fPosY, m_fPosY + 15.f);
	m_SparkleAry[6].m_tMoveLerpY.fCurValue = m_SparkleAry[6].m_tMoveLerpY.fStartValue;

	// 마지막 별
	m_SparkleAry[7].m_fTempSize = m_fSizeX * 0.55f;
	m_SparkleAry[7].m_matSparkle._41 = m_fPosX;
	m_SparkleAry[7].m_matSparkle._42 = m_fPosY;

	m_SparkleAry[7].m_tMoveLerpX.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_SparkleAry[7].m_tMoveLerpX.Set_Lerp(0.5f, m_fPosX, m_fPosX + 80.f);
	m_SparkleAry[7].m_tMoveLerpX.fCurValue = m_SparkleAry[7].m_tMoveLerpX.fStartValue;

	m_SparkleAry[7].m_tMoveLerpY.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_SparkleAry[7].m_tMoveLerpY.Set_Lerp(0.5f, m_fPosY, m_fPosY + 30.f);
	m_SparkleAry[7].m_tMoveLerpY.fCurValue = m_SparkleAry[7].m_tMoveLerpY.fStartValue;

	for (_int i = 0; i < MAX_SPARKLE_SIZE; ++i)
	{
		m_SparkleAry[i].m_tSizeUpLerp.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
		m_SparkleAry[i].m_tSizeUpLerp.Set_Lerp(0.8f, 0.f, m_SparkleAry[i].m_fTempSize);
		m_SparkleAry[i].m_tSizeDownLerp.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
		m_SparkleAry[i].m_tSizeDownLerp.Set_Lerp(1.f, m_SparkleAry[i].m_fTempSize, 0.f);
	}
}

_int CWeaponGetEffect::Update_Object(const _float& fTimeDelta)
{
	CManagement::GetInstance()->Get_Layer(OBJ_TYPE::PLAYER)->Layer_SetActive(false);
	CManagement::GetInstance()->Get_Layer(OBJ_TYPE::MONSTER)->Layer_SetActive(false);

	_int iExit = __super::Update_Object(fTimeDelta);

	// 시작 알파 보간 처리
	m_tReadyEffectLerp.Update_Lerp(fTimeDelta);
	if (m_tReadyEffectLerp.bActive && !m_ReadyEffect)
	{
		m_iAllTranslucent = (_int)m_tReadyEffectLerp.fCurValue;
	}
	else
	{
		m_ReadyEffect = true;
	}

	if (m_ReadyEffect)
	{
		// 지우기
		if (m_iStayCount2 < GetTickCount64())
		{
			m_iAllTranslucent -= 5;
			if (m_iAllTranslucent < 10)
			{
				CWeaponGetUI* pGetUI = CWeaponGetUI::Create(m_pGraphicDev, m_pWeapon);
				NULL_CHECK_RETURN(pGetUI, E_FAIL);
				CEventMgr::GetInstance()->Add_Obj(L"GetObjUI", pGetUI);

				CEventMgr::GetInstance()->Delete_Obj(this);
				return true;
			}
		}

		if (!m_bSizeUp)
		{
			if (m_bReadySound)
			{
				// CSoundMgr::GetInstance()->SetChannelVolume(CHANNEL_ID::BGM_CUR, 0.f);
				CSoundMgr::GetInstance()->PlaySound(L"Open Chest.wav", CHANNEL_ID::EFFECT_0, ITEM_SKILL_GET_EFFECT);
				CSoundMgr::GetInstance()->Lerp_Volume_CurBGM(LERP_MODE::SMOOTHERSTEP, 1.f, SOUND_VOLUME_BGM, 0.1f);
				m_bReadySound = false;
			}

			Random_Move();
			Smaller_Weapon();
		}
		else if (GetTickCount64() > m_iStayCount && m_bSizeUp)
		{
			m_iWeaponAlpha = 255;
			Sudden_Weapon();
		}

		m_matGlow._41 = m_tRandomMoveLerpX.fCurValue;
		m_matGlow._42 = m_tRandomMoveLerpY.fCurValue;
		m_matGlow._11 = m_fCurWeaponSizeX;
		m_matGlow._22 = m_fCurWeaponSizeY;
	}

	return iExit;
}

void CWeaponGetEffect::Random_Move()
{
	m_tRandomMoveLerpX.Update_Lerp(Engine::Get_TimeDelta(L"Timer_FPS65"));
	m_tRandomMoveLerpY.Update_Lerp(Engine::Get_TimeDelta(L"Timer_FPS65"));
	if (!m_tRandomMoveLerpX.bActive && !m_tRandomMoveLerpY.bActive)
	{
		m_iRandValue = (rand() % 20) - 10;
		m_tRandomMoveLerpX.Init_Lerp(LERP_MODE::EASE_OUT);
		m_tRandomMoveLerpX.Set_Lerp(0.1f, m_fPosX, m_fPosX + m_iRandValue);
		m_tRandomMoveLerpX.fCurValue = m_tRandomMoveLerpX.fStartValue;

		m_iRandValue = (rand() % 20) - 10;
		m_tRandomMoveLerpY.Init_Lerp(LERP_MODE::EASE_OUT);
		m_tRandomMoveLerpY.Set_Lerp(0.1f, m_fPosY, m_fPosY + m_iRandValue);
		m_tRandomMoveLerpY.fCurValue = m_tRandomMoveLerpY.fStartValue;
	}
}

void CWeaponGetEffect::Smaller_Weapon()
{
	m_tSmallerLerpX.Update_Lerp(Engine::Get_TimeDelta(L"Timer_FPS65"));
	m_tSmallerLerpY.Update_Lerp(Engine::Get_TimeDelta(L"Timer_FPS65"));
	m_fCurWeaponSizeX = m_tSmallerLerpX.fCurValue;
	m_fCurWeaponSizeY = m_tSmallerLerpY.fCurValue;

	if (m_iWeaponAlpha > 5)
	{
		m_iWeaponAlpha -= 10;
	}

	if (!m_tSmallerLerpX.bActive && !m_bTimeSet)
	{
		m_iStayCount = GetTickCount64() + 50;
		m_bTimeSet = true;
	}

	if (m_bTimeSet && GetTickCount64() > m_iStayCount)
		m_bSizeUp = true;

}

void CWeaponGetEffect::Sudden_Weapon()
{
	m_tSuddenWeaponLerpX.Update_Lerp(Engine::Get_TimeDelta(L"Timer_FPS65"));
	m_tSuddenWeaponLerpY.Update_Lerp(Engine::Get_TimeDelta(L"Timer_FPS65"));
	m_tSuddenShineLerp.Update_Lerp(Engine::Get_TimeDelta(L"Timer_FPS65"));

	if (!m_tSuddenWeaponLerpX.bActive)
	{
		if (!m_bResultStay)
		{
			m_iStayCount2 = GetTickCount64() + 900;
			m_bResultStay = true;
		}
		// 스파클
		for (_int i = 0; i < MAX_SPARKLE_SIZE; ++i)
		{
			if (!m_SparkleAry[i].m_tSizeUpLerp.bActive)
			{
				m_SparkleAry[i].m_tSizeDownLerp.Update_Lerp(Engine::Get_TimeDelta(L"Timer_FPS65"));

				m_SparkleAry[i].m_matSparkle._11 = m_SparkleAry[i].m_tSizeDownLerp.fCurValue;
				m_SparkleAry[i].m_matSparkle._22 = m_SparkleAry[i].m_tSizeDownLerp.fCurValue;
			}
			else
			{
				m_SparkleAry[i].m_tMoveLerpX.Update_Lerp(Engine::Get_TimeDelta(L"Timer_FPS65"));
				m_SparkleAry[i].m_tMoveLerpY.Update_Lerp(Engine::Get_TimeDelta(L"Timer_FPS65"));
				m_SparkleAry[i].m_tSizeUpLerp.Update_Lerp(Engine::Get_TimeDelta(L"Timer_FPS65"));

				m_SparkleAry[i].m_matSparkle._11 = m_SparkleAry[i].m_tSizeUpLerp.fCurValue;
				m_SparkleAry[i].m_matSparkle._22 = m_SparkleAry[i].m_tSizeUpLerp.fCurValue;
			}
			m_SparkleAry[i].m_matSparkle._41 = m_SparkleAry[i].m_tMoveLerpX.fCurValue;
			m_SparkleAry[i].m_matSparkle._42 = m_SparkleAry[i].m_tMoveLerpY.fCurValue;
		}

		m_tReturnWeaponSizeLerpX.Update_Lerp(Engine::Get_TimeDelta(L"Timer_FPS65"));
		m_tReturnWeaponSizeLerpY.Update_Lerp(Engine::Get_TimeDelta(L"Timer_FPS65"));
		m_tReturnShineSizeLerp.Update_Lerp(Engine::Get_TimeDelta(L"Timer_FPS65"));
		m_fCurWeaponSizeX = m_tReturnWeaponSizeLerpX.fCurValue;
		m_fCurWeaponSizeY = m_tReturnWeaponSizeLerpY.fCurValue;
		m_fCurShineSize = m_tReturnShineSizeLerp.fCurValue;

		_float fAngle = 1.f;

		D3DXMATRIX rotationMatrix;
		D3DXMatrixIdentity(&rotationMatrix);
		D3DXMatrixRotationZ(&rotationMatrix, D3DXToRadian(fAngle));

		m_matShine._11 = m_fCurShineSize;
		m_matShine._22 = m_fCurShineSize;

		m_matShine *= rotationMatrix;

		m_matShine._41 = m_fPosX;
		m_matShine._42 = m_fPosY;
	}
	else
	{
		m_matShine._11 = m_fCurShineSize;
		m_matShine._22 = m_fCurShineSize;

		m_fCurWeaponSizeX = m_tSuddenWeaponLerpX.fCurValue;
		m_fCurWeaponSizeY = m_tSuddenWeaponLerpY.fCurValue;
		m_fCurShineSize = m_tSuddenShineLerp.fCurValue;
	}




}

void CWeaponGetEffect::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CWeaponGetEffect::Render_Object()
{
	// 초기 세팅
	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(m_iAllTranslucent, 255, 255, 255));
	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

	// 샤이닝
	if (m_bSizeUp)
	{
		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matShine);
		m_pShineTexCom->Render_Texture();
		m_pBufferCom->Render_Buffer();

		// 스파클
		for (_int i = 0; i < MAX_SPARKLE_SIZE; ++i)
		{
			m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_SparkleAry[i].m_matSparkle);
			m_SparkleAry[i].m_pSparkleTexCom->Render_Texture();
			m_pBufferCom->Render_Buffer();
		}
	}

	// 글로우
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matGlow);
	m_pGlowTexCom->Render_Texture();
	m_pBufferCom->Render_Buffer();

	// 무기(시작할 때 알파 보간 등장. 이후 연출 땐 알파 줄어드는 연출)
	if (m_ReadyEffect && !m_bSizeUp) 
	{
		m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB((_int)m_iWeaponAlpha, 255, 255, 255));
	}
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matGlow);
	m_pWeaponTexCom->Render_Texture();
	m_pBufferCom->Render_Buffer();
	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(m_iAllTranslucent, 255, 255, 255));



	__super::Render_Object();
}


HRESULT CWeaponGetEffect::Add_Component()
{

	CComponent* pComponent = nullptr;

	if(m_pWeapon->Get_Name() == L"닌자냥이 세트")
	{
		m_pWeaponTexCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Item_NinjaWeapon", this));
		NULL_CHECK_RETURN(m_pWeaponTexCom, E_FAIL);
		m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, m_pWeaponTexCom);

		pComponent = m_pGlowTexCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Get_Ninja_Weapon_UI", this));
		NULL_CHECK_RETURN(pComponent, E_FAIL);
		m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);
	}
	else if(m_pWeapon->Get_Name() == L"매직냥 스태프")
	{
		m_pWeaponTexCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Item_MageWeapon", this));
		NULL_CHECK_RETURN(m_pWeaponTexCom, E_FAIL);
		m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, m_pWeaponTexCom);

		pComponent = m_pGlowTexCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Get_Mage_Weapon_UI", this));
		NULL_CHECK_RETURN(pComponent, E_FAIL);
		m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	}
	else if (m_pWeapon->Get_Name() == L"냥서커의 보물")
	{
		m_pWeaponTexCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Item_WarriorWeapon", this));
		NULL_CHECK_RETURN(m_pWeaponTexCom, E_FAIL);
		m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, m_pWeaponTexCom);

		pComponent = m_pGlowTexCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Get_Warrior_Weapon_UI", this));
		NULL_CHECK_RETURN(pComponent, E_FAIL);
		m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);
	}

	// 샤이닝
	pComponent = m_pShineTexCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Skill_Shine", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	// 스파클
	for (_int i = 0; i < MAX_SPARKLE_SIZE; ++i)
	{
		pComponent = m_SparkleAry[i].m_pSparkleTexCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Skill_Sparkle", this));
		NULL_CHECK_RETURN(pComponent, E_FAIL);
		m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);
	}


	// 버퍼
	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	return S_OK;
}

CWeaponGetEffect* CWeaponGetEffect::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pWeapon)
{
	CWeaponGetEffect* pInstance = new CWeaponGetEffect(pGraphicDev, _pWeapon);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("WeaponGetEffect Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CWeaponGetEffect::Free()
{
	__super::Free();

}
