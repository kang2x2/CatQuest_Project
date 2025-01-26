#include "stdafx.h"
#include "SkillGetEffect.h"
#include "Export_Function.h"

#include "Player.h"

#include "SkillGetUI.h"

#include "SoundMgr.h"

CSkillGetEffect::CSkillGetEffect(LPDIRECT3DDEVICE9 pGraphicDev, CSkill* _pSkill)
	:	CUI(pGraphicDev, OBJ_ID::UI_SKILL_GET_EFFECT_UI)
		, m_bSizeUp(false) , m_bTimeSet(false), m_bResultStay(false), m_bReadySound(true)
		, m_ReadyEffect(false)
		, m_iStayCount(0), m_iAllTranslucent(0)
{
	m_pSkill = _pSkill;
}

CSkillGetEffect::CSkillGetEffect(const CSkillGetEffect& rhs)
	: CUI(rhs)
{
}

CSkillGetEffect::~CSkillGetEffect()
{
}

HRESULT CSkillGetEffect::Ready_Object()
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

	Ready_SkillGlow();
	Ready_SkillShine();
	Ready_Sparkle();

	m_tReadyEffectLerp.Init_Lerp(LERP_MODE::EASE_IN);
	m_tReadyEffectLerp.Set_Lerp(0.5f, 0.f, 255.f);

	return S_OK;
}

void CSkillGetEffect::Ready_SkillGlow()
{
	m_iSkillAlpha = 255;

	m_fPosX = WINCX / 2.f;
	m_fPosY = WINCY / 2.f;
	m_fSizeX = 165.f * 0.3f;
	m_fSizeY = 165.f * 0.3f;
	m_matGlow._41 = m_fPosX;
	m_matGlow._42 = m_fPosY;
	m_matGlow._11 = m_fSizeX;
	m_matGlow._22 = m_fSizeY;

	m_fCurShineSize = m_fSizeX;

	// �ʱ� ����
	// ��ų ��ġ
	m_tRandomMoveLerpX.Init_Lerp(LERP_MODE::EASE_IN);
	m_tRandomMoveLerpX.Set_Lerp(0.1f, m_fPosX, m_fPosX + 5.f);
	m_tRandomMoveLerpX.fCurValue = m_tRandomMoveLerpX.fStartValue;

	m_tRandomMoveLerpY.Init_Lerp(LERP_MODE::EASE_IN);
	m_tRandomMoveLerpY.Set_Lerp(0.1f, m_fPosY, m_fPosY + 5.f);
	m_tRandomMoveLerpY.fCurValue = m_tRandomMoveLerpY.fStartValue;

	// ��ų ������ �ٿ�
	m_tSmallerLerp.Init_Lerp(LERP_MODE::EASE_IN);
	m_tSmallerLerp.Set_Lerp(0.8f, m_fSizeX, m_fSizeX * 0.7f);
	// ��ų ������ ����
	m_tSuddenSkillLerp.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_tSuddenSkillLerp.Set_Lerp(0.25f, m_fSizeX * 0.7f, m_fSizeX * 2.f);
	// ��ų ������ ����
	m_tReturnSkillSizeLerp.Init_Lerp(LERP_MODE::EASE_IN);
	m_tReturnSkillSizeLerp.Set_Lerp(0.25f, m_fSizeX * 2.f, m_fSizeX);
}

void CSkillGetEffect::Ready_SkillShine()
{
	m_fPosX = WINCX / 2.f;
	m_fPosY = WINCY / 2.f;
	m_fSizeX = 250.f * 0.5f;
	m_fSizeY = 250.f * 0.5f;
	m_matShine._41 = m_fPosX;
	m_matShine._42 = m_fPosY;
	m_matShine._11 = m_fSizeX;
	m_matShine._22 = m_fSizeY;

	// ���̴� ������ ����
	m_tSuddenShineLerp.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_tSuddenShineLerp.Set_Lerp(0.25f, m_fSizeX * 0.7f, m_fSizeX * 10.f);
	// ���̴� ������ ����
	m_tReturnShineSizeLerp.Init_Lerp(LERP_MODE::EASE_IN);
	m_tReturnShineSizeLerp.Set_Lerp(0.25f, m_fSizeX * 10.f, m_fSizeX);

}

void CSkillGetEffect::Ready_Sparkle()
{
	m_fPosX = WINCX / 2.f;
	m_fPosY = WINCY / 2.f;
	m_fSizeX = 80.f;
	m_fSizeY = 80.f;

	// 1�� ��
	m_SparkleAry[0].m_fTempSize = m_fSizeX * 0.5f;
	m_SparkleAry[0].m_matSparkle._41 = m_fPosX;
	m_SparkleAry[0].m_matSparkle._42 = m_fPosY;

	m_SparkleAry[0].m_tMoveLerpX.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_SparkleAry[0].m_tMoveLerpX.Set_Lerp(0.5f, m_fPosX, m_fPosX - 200.f);
	m_SparkleAry[0].m_tMoveLerpX.fCurValue = m_SparkleAry[0].m_tMoveLerpX.fStartValue;

	m_SparkleAry[0].m_tMoveLerpY.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_SparkleAry[0].m_tMoveLerpY.Set_Lerp(0.5f, m_fPosY, m_fPosY + 100.f);
	m_SparkleAry[0].m_tMoveLerpY.fCurValue = m_SparkleAry[0].m_tMoveLerpY.fStartValue;

	// 2�� ��
	m_SparkleAry[1].m_fTempSize = m_fSizeX * 0.2f;
	m_SparkleAry[1].m_matSparkle._41 = m_fPosX;
	m_SparkleAry[1].m_matSparkle._42 = m_fPosY;

	m_SparkleAry[1].m_tMoveLerpX.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_SparkleAry[1].m_tMoveLerpX.Set_Lerp(0.5f, m_fPosX, m_fPosX - 100.f);
	m_SparkleAry[1].m_tMoveLerpX.fCurValue = m_SparkleAry[1].m_tMoveLerpX.fStartValue;

	m_SparkleAry[1].m_tMoveLerpY.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_SparkleAry[1].m_tMoveLerpY.Set_Lerp(0.5f, m_fPosY, m_fPosY + 70.f);
	m_SparkleAry[1].m_tMoveLerpY.fCurValue = m_SparkleAry[1].m_tMoveLerpY.fStartValue;

	// 3�� ��
	m_SparkleAry[2].m_fTempSize = m_fSizeX * 0.25f;
	m_SparkleAry[2].m_matSparkle._41 = m_fPosX;
	m_SparkleAry[2].m_matSparkle._42 = m_fPosY;

	m_SparkleAry[2].m_tMoveLerpX.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_SparkleAry[2].m_tMoveLerpX.Set_Lerp(0.6f, m_fPosX, m_fPosX - 110.f);
	m_SparkleAry[2].m_tMoveLerpX.fCurValue = m_SparkleAry[2].m_tMoveLerpX.fStartValue;

	m_SparkleAry[2].m_tMoveLerpY.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_SparkleAry[2].m_tMoveLerpY.Set_Lerp(0.6f, m_fPosY, m_fPosY - 70.f);
	m_SparkleAry[2].m_tMoveLerpY.fCurValue = m_SparkleAry[2].m_tMoveLerpY.fStartValue;

	// 4�� ��
	m_SparkleAry[3].m_fTempSize = m_fSizeX * 0.2f;
	m_SparkleAry[3].m_matSparkle._41 = m_fPosX;
	m_SparkleAry[3].m_matSparkle._42 = m_fPosY;

	m_SparkleAry[3].m_tMoveLerpX.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_SparkleAry[3].m_tMoveLerpX.Set_Lerp(0.3f, m_fPosX, m_fPosX - 40.f);
	m_SparkleAry[3].m_tMoveLerpX.fCurValue = m_SparkleAry[3].m_tMoveLerpX.fStartValue;

	m_SparkleAry[3].m_tMoveLerpY.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_SparkleAry[3].m_tMoveLerpY.Set_Lerp(0.3f, m_fPosY, m_fPosY - 110.f);
	m_SparkleAry[3].m_tMoveLerpY.fCurValue = m_SparkleAry[3].m_tMoveLerpY.fStartValue;

	// 5�� ��
	m_SparkleAry[4].m_fTempSize = m_fSizeX * 0.45f;
	m_SparkleAry[4].m_matSparkle._41 = m_fPosX;
	m_SparkleAry[4].m_matSparkle._42 = m_fPosY;

	m_SparkleAry[4].m_tMoveLerpX.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_SparkleAry[4].m_tMoveLerpX.Set_Lerp(0.7f, m_fPosX, m_fPosX + 150.f);
	m_SparkleAry[4].m_tMoveLerpX.fCurValue = m_SparkleAry[4].m_tMoveLerpX.fStartValue;

	m_SparkleAry[4].m_tMoveLerpY.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_SparkleAry[4].m_tMoveLerpY.Set_Lerp(0.7f, m_fPosY, m_fPosY - 120.f);
	m_SparkleAry[4].m_tMoveLerpY.fCurValue = m_SparkleAry[4].m_tMoveLerpY.fStartValue;

	// 6����
	m_SparkleAry[5].m_fTempSize = m_fSizeX * 0.15f;
	m_SparkleAry[5].m_matSparkle._41 = m_fPosX;
	m_SparkleAry[5].m_matSparkle._42 = m_fPosY;

	m_SparkleAry[5].m_tMoveLerpX.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_SparkleAry[5].m_tMoveLerpX.Set_Lerp(0.5f, m_fPosX, m_fPosX + 200.f);
	m_SparkleAry[5].m_tMoveLerpX.fCurValue = m_SparkleAry[5].m_tMoveLerpX.fStartValue;

	m_SparkleAry[5].m_tMoveLerpY.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_SparkleAry[5].m_tMoveLerpY.Set_Lerp(0.5f, m_fPosY, m_fPosY - 5.f);
	m_SparkleAry[5].m_tMoveLerpY.fCurValue = m_SparkleAry[5].m_tMoveLerpY.fStartValue;

	// 7����
	m_SparkleAry[6].m_fTempSize = m_fSizeX * 0.55f;
	m_SparkleAry[6].m_matSparkle._41 = m_fPosX;
	m_SparkleAry[6].m_matSparkle._42 = m_fPosY;

	m_SparkleAry[6].m_tMoveLerpX.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_SparkleAry[6].m_tMoveLerpX.Set_Lerp(0.5f, m_fPosX, m_fPosX + 240.f);
	m_SparkleAry[6].m_tMoveLerpX.fCurValue = m_SparkleAry[6].m_tMoveLerpX.fStartValue;

	m_SparkleAry[6].m_tMoveLerpY.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_SparkleAry[6].m_tMoveLerpY.Set_Lerp(0.5f, m_fPosY, m_fPosY + 15.f);
	m_SparkleAry[6].m_tMoveLerpY.fCurValue = m_SparkleAry[6].m_tMoveLerpY.fStartValue;

	// ������ ��
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

_int CSkillGetEffect::Update_Object(const _float& fTimeDelta)
{
	CManagement::GetInstance()->Get_Layer(OBJ_TYPE::PLAYER)->Layer_SetActive(false);
	CManagement::GetInstance()->Get_Layer(OBJ_TYPE::MONSTER)->Layer_SetActive(false);

	_int iExit = __super::Update_Object(fTimeDelta);
	
	// ���� ���� ���� ó��
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
		if (m_iStayCount2 < GetTickCount64())
		{
			m_iAllTranslucent -= 5;
			if (m_iAllTranslucent < 10)
			{
				CSkillGetUI* pGetUI = CSkillGetUI::Create(m_pGraphicDev, m_pSkill);
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
			Smaller_Skill();
		}
		else if (GetTickCount64() > m_iStayCount && m_bSizeUp)
		{
			m_iSkillAlpha = 255;
			Sudden_Skill();
		}

		m_matGlow._41 = m_tRandomMoveLerpX.fCurValue;
		m_matGlow._42 = m_tRandomMoveLerpY.fCurValue;
		m_matGlow._11 = m_fCurSkillSize;
		m_matGlow._22 = m_fCurSkillSize;
	}

	return iExit;
}

void CSkillGetEffect::Random_Move()
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

void CSkillGetEffect::Smaller_Skill()
{
	m_tSmallerLerp.Update_Lerp(Engine::Get_TimeDelta(L"Timer_FPS65"));
	m_fCurSkillSize = m_tSmallerLerp.fCurValue;

	if (m_iSkillAlpha > 5)
	{
		m_iSkillAlpha -= 10;
	}

	if (!m_tSmallerLerp.bActive && !m_bTimeSet)
	{
		m_iStayCount = GetTickCount64() + 50;
		m_bTimeSet = true;
	}

	if (m_bTimeSet && GetTickCount64() > m_iStayCount)
		m_bSizeUp = true;

}

void CSkillGetEffect::Sudden_Skill()
{
	m_tSuddenSkillLerp.Update_Lerp(Engine::Get_TimeDelta(L"Timer_FPS65"));
	m_tSuddenShineLerp.Update_Lerp(Engine::Get_TimeDelta(L"Timer_FPS65"));

	if (!m_tSuddenSkillLerp.bActive)
	{
		if (!m_bResultStay)
		{
			m_iStayCount2 = GetTickCount64() + 900;
			m_bResultStay = true;
		}
		// ����Ŭ
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

		m_tReturnSkillSizeLerp.Update_Lerp(Engine::Get_TimeDelta(L"Timer_FPS65"));
		m_tReturnShineSizeLerp.Update_Lerp(Engine::Get_TimeDelta(L"Timer_FPS65"));
		m_fCurSkillSize = m_tReturnSkillSizeLerp.fCurValue;
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

		m_fCurSkillSize = m_tSuddenSkillLerp.fCurValue;
		m_fCurShineSize = m_tSuddenShineLerp.fCurValue;
	}



	
}

void CSkillGetEffect::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CSkillGetEffect::Render_Object()
{
	// �ʱ� ����
	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(m_iAllTranslucent, 255, 255, 255));
	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

	// ���̴�
	if(m_bSizeUp)
	{
		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matShine);
		m_pShineTexCom->Render_Texture();
		m_pBufferCom->Render_Buffer();

		// ����Ŭ
		for (_int i = 0; i < MAX_SPARKLE_SIZE; ++i)
		{
			m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_SparkleAry[i].m_matSparkle);
			m_SparkleAry[i].m_pSparkleTexCom->Render_Texture();
			m_pBufferCom->Render_Buffer();
		}
	}



	// �۷ο�
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matGlow);
	m_pGlowTexCom->Render_Texture();
	m_pBufferCom->Render_Buffer();

	// ��ų (������ �� ���� ���� ����. ���� ���� �� ���� �پ��� ����)
	if (m_ReadyEffect && !m_bSizeUp)
	{
		m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB((_int)m_iSkillAlpha, 255, 255, 255));
	}
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matGlow);
	if(m_pSkill->Get_Name() != L"�ɴٶ���")
	{
		m_pSkillTexCom->Render_Texture((_int)(m_pSkill->Get_ID()) - 126);
	}
	else
	{
		m_pSkillTexCom->Render_Texture();
	}
	m_pBufferCom->Render_Buffer();
	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(m_iAllTranslucent, 255, 255, 255));



	__super::Render_Object();
}


HRESULT CSkillGetEffect::Add_Component()
{

	CComponent* pComponent = nullptr;

	// ��ų, ��ų�۷ο�
	if (m_pSkill->Get_Name() == L"�ɴٶ���")
	{
		m_pSkillTexCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Get_Fly_UI", this));
		NULL_CHECK_RETURN(m_pSkillTexCom, E_FAIL);
		m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, m_pSkillTexCom);
	}
	else
	{
		m_pSkillTexCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_UI_Skill", this));
		NULL_CHECK_RETURN(m_pSkillTexCom, E_FAIL);
		m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, m_pSkillTexCom);
	}

	pComponent = m_pGlowTexCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Skill_Glow", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	// ���̴�
	pComponent = m_pShineTexCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Skill_Shine", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	// ����Ŭ
	for (_int i = 0; i < MAX_SPARKLE_SIZE; ++i)
	{
		pComponent = m_SparkleAry[i].m_pSparkleTexCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Skill_Sparkle", this));
		NULL_CHECK_RETURN(pComponent, E_FAIL);
		m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);
	}


	// ����
	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	return S_OK;
}

CSkillGetEffect* CSkillGetEffect::Create(LPDIRECT3DDEVICE9 pGraphicDev, CSkill* _pSkill)
{
	CSkillGetEffect* pInstance = new CSkillGetEffect(pGraphicDev, _pSkill);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("SkillGetEffect Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CSkillGetEffect::Free()
{
	__super::Free();

}
