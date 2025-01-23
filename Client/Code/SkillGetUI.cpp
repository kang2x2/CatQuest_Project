#include "stdafx.h"
#include "SkillGetUI.h"
#include "Export_Function.h"

#include "Player.h"

#include "QuestMgr.h"
#include "SoundMgr.h"

CSkillGetUI::CSkillGetUI(LPDIRECT3DDEVICE9 pGraphicDev, CSkill* _pSkill)
	: CUI(pGraphicDev, OBJ_ID::UI_SKILL_GET_UI)
	, m_bDelete(false)
	, m_iLvPrevTranslucent(255)
	, m_iLvCurTranslucent(0)
	, m_iTempLv(_pSkill->Get_SkillLv() + 1)
{
	m_pSkill = _pSkill;
}

CSkillGetUI::CSkillGetUI(const CSkillGetUI& rhs)
	: CUI(rhs)
{
}

CSkillGetUI::~CSkillGetUI()
{
}

HRESULT CSkillGetUI::Ready_Object()
{
	__super::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	D3DXMatrixIdentity(&m_matBack);
	D3DXMatrixIdentity(&m_matBase);
	D3DXMatrixIdentity(&m_matSkill);
	D3DXMatrixIdentity(&m_matInventory);
	D3DXMatrixIdentity(&m_matArrow);

	m_eUIType = UI_TYPE::VIEW;
	m_eUILayer = UI_LAYER::LV2;

	// 배경
	m_fPosX = WINCX >> 1;
	m_fPosY = WINCY >> 1;
	m_fSizeX = WINCX;
	m_fSizeY = WINCY;
	m_matBack._41 = m_fPosX;
	m_matBack._42 = m_fPosY;
	m_matBack._11 = m_fSizeX;
	m_matBack._22 = m_fSizeY;

	// 베이스
	m_fPosX = WINCX / 2;
	m_fPosY = WINCY / 2 + 50.f; 
	m_fSizeX = 200.f;
	m_fSizeY = 200.f;
	m_fMultipleSizeX = 1.5f;
	m_fMultipleSizeY = 1.5f;
	m_matBase._41 = m_fPosX;
	m_matBase._42 = m_fPosY;
	m_matBase._11 = m_fSizeX * m_fMultipleSizeX;
	m_matBase._22 = m_fSizeY * m_fMultipleSizeY;

	// 스킬
	m_fPosX = WINCX / 2;
	m_fPosY = WINCY / 2;
	m_fSizeX = 165.f;
	m_fSizeY = 165.f;
	m_fMultipleSizeX = 0.3f;
	m_fMultipleSizeY = 0.3f;
	m_matSkill._41 = m_fPosX;
	m_matSkill._42 = m_fPosY;
	m_matSkill._11 = m_fSizeX * m_fMultipleSizeX;
	m_matSkill._22 = m_fSizeY * m_fMultipleSizeY;

	// 인벤토리
	m_fPosX = WINCX / 2 + 110;
	m_fPosY = WINCY / 2 - 140;
	m_fSizeX = 125.f;
	m_fSizeY = 100.f;
	m_fMultipleSizeX = 0.2f;
	m_fMultipleSizeY = 0.2f;
	m_matInventory._41 = m_fPosX;
	m_matInventory._42 = m_fPosY;
	m_matInventory._11 = m_fSizeX * m_fMultipleSizeX;
	m_matInventory._22 = m_fSizeY * m_fMultipleSizeY;

	// 스킬 폰트
	m_rcName = { WINCX / 2, WINCY / 2 - 100,  WINCX / 2,  WINCY / 2 - 100 };
	m_rcnNavigation = { WINCX / 2 - 25, WINCY / 2 + 120, WINCX / 2 - 25, WINCY / 2 + 120 };
	m_rcLv1 = { WINCX / 2 - 15, WINCY / 2 + 55,  WINCX / 2 - 15,  WINCY / 2 + 55 };
	m_rcLv2 = { WINCX / 2 + 20, WINCY / 2 + 55,  WINCX / 2 + 20,  WINCY / 2 + 55 };

	m_rcFlyGet = { WINCX / 2, WINCY / 2 + 55,  WINCX / 2,  WINCY / 2 + 55 };
	m_rcFlyNavigation = { WINCX / 2, WINCY / 2 + 120, WINCX / 2, WINCY / 2 + 120 };

	// 폰트 러프
	m_tLvPrevLerp.Init_Lerp(LERP_MODE::EASE_OUT);
	m_tLvPrevLerp.Set_Lerp(0.5f, WINCY / 2 + 55, WINCY / 2 + 45);

	m_tLvCurLerp.Init_Lerp(LERP_MODE::EASE_OUT);
	m_tLvCurLerp.Set_Lerp(0.5f, WINCY / 2 + 65, WINCY / 2 + 55);


	m_eUIType = UI_TYPE::VIEW;
	m_eUILayer = UI_LAYER::LV2;

	m_iTranslucent = 0;

	return S_OK;
}

_int CSkillGetUI::Update_Object(const _float& fTimeDelta)
{
	CManagement::GetInstance()->Get_Layer(OBJ_TYPE::PLAYER)->Layer_SetActive(false);
	CManagement::GetInstance()->Get_Layer(OBJ_TYPE::MONSTER)->Layer_SetActive(false);

	if (!m_bDelete && m_iTranslucent < 255)
		m_iTranslucent += 5;

	if (CInputDev::GetInstance()->Key_Down('E'))
	{
		CSoundMgr::GetInstance()->PlaySound(L"button_press.wav", CHANNEL_ID::UI_1, 1.f);
		CSoundMgr::GetInstance()->Lerp_Volume_CurBGM(LERP_MODE::SMOOTHERSTEP, 1.f, 0.1f, SOUND_VOLUME_BGM);

		m_bDelete = true;
	}
	if (m_bDelete)
	{
		m_iTranslucent -= 5;
		m_iLvCurTranslucent -= 5;
		if (m_iTranslucent < 5)
		{
			// 스킬 레벨 업
			if (m_pSkill->Get_Name() != L"냥다람쥐")
			{
				m_pSkill->Skill_LvUp(1);
			}
			// bgm 다시 재생
			// CSoundMgr::GetInstance()->SetChannelVolume(CHANNEL_ID::BGM_CUR, 0.7f);

			// 퀘스트가 다음 단계로 나아갈 수 있게
			CQuestMgr::GetInstance()->Set_ReadyNext();
			CManagement::GetInstance()->Get_Layer(OBJ_TYPE::PLAYER)->Layer_SetActive(true);
			CManagement::GetInstance()->Get_Layer(OBJ_TYPE::MONSTER)->Layer_SetActive(true);

			// 지금 있는 세이드도 같이 지운다.
			CEventMgr::GetInstance()->Delete_Obj(
				CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"ShadeUI"));
			CEventMgr::GetInstance()->Delete_Obj(this);
		}
	}

	// 폰트
	if (m_iTranslucent > 250)
	{
		if (m_iLvPrevTranslucent > 0)
			m_iLvPrevTranslucent -= 5;
		if(m_iLvCurTranslucent < 255)
			m_iLvCurTranslucent += 5;

		m_tLvPrevLerp.Update_Lerp(fTimeDelta);
		m_tLvCurLerp.Update_Lerp(fTimeDelta);

		m_rcLv2 = { WINCX / 2 + 20, (_int)m_tLvPrevLerp.fCurValue,  WINCX / 2 + 20,  (_int)m_tLvPrevLerp.fCurValue };
		m_rcLv3 = { WINCX / 2 + 20, (_int)m_tLvCurLerp.fCurValue,  WINCX / 2 + 20,  (_int)m_tLvCurLerp.fCurValue };
	}
		

	_int iExit = __super::Update_Object(fTimeDelta);

	return iExit;
}

void CSkillGetUI::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CSkillGetUI::Render_Object()
{
	// 초기 세팅
	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(m_iTranslucent, 255, 255, 255));
	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

	// 배경
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matBack);
	m_pBackTexCom->Render_Texture();
	m_pBufferCom->Render_Buffer();

	// 베이스
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matBase);
	m_pBaseTexCom->Render_Texture();
	m_pBufferCom->Render_Buffer();

	// 스킬
	if (m_pSkill->Get_Name() != L"냥다람쥐")
	{
		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matSkill);
		m_pSkillTexCom->Render_Texture((_int)(m_pSkill->Get_ID()) - 126);
		m_pBufferCom->Render_Buffer();
	}
	else
	{
		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matSkill);
		m_pSkillTexCom->Render_Texture();
		m_pBufferCom->Render_Buffer();
	}


	// 스킬명
	BYTE newAlpha = m_iTranslucent;
	CGraphicDev::GetInstance()->Get_InGameFont()->DrawTextW(NULL, m_pSkill->Get_Name(), -1,
		&m_rcName, DT_CENTER | DT_NOCLIP, (m_pSkill->Get_SkillFontColor() & 0x00FFFFFF) | (newAlpha << 24));

	// 레벨
	wstring strSkillLv;
	if (m_pSkill->Get_Name() != L"냥다람쥐")
	{
		CGraphicDev::GetInstance()->Get_InGameFont()->DrawTextW(NULL, L"Lv ", -1,
			&m_rcLv1, DT_CENTER | DT_NOCLIP, D3DCOLOR_ARGB(m_iTranslucent, 153, 102, 0));

		strSkillLv = to_wstring(m_pSkill->Get_SkillLv());
		CGraphicDev::GetInstance()->Get_InGameFont()->DrawTextW(NULL, strSkillLv.c_str(), -1,
			&m_rcLv2, DT_CENTER | DT_NOCLIP, D3DCOLOR_ARGB(m_iLvPrevTranslucent, 153, 102, 0));
	
		strSkillLv = to_wstring(m_iTempLv);
		CGraphicDev::GetInstance()->Get_InGameFont()->DrawTextW(NULL, strSkillLv.c_str(), -1,
			&m_rcLv3, DT_CENTER | DT_NOCLIP, D3DCOLOR_ARGB(m_iLvCurTranslucent, 0, 153, 0));
		
		strSkillLv = L"Equip new skills in";
		CGraphicDev::GetInstance()->Get_InGameFont()->DrawTextW(NULL, strSkillLv.c_str(), -1,
			&m_rcnNavigation, DT_CENTER | DT_NOCLIP, D3DCOLOR_ARGB(m_iTranslucent, 153, 102, 0));


		// 인벤토리 아이콘
		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matInventory);
		m_pInventoryTexCom->Render_Texture();
		m_pBufferCom->Render_Buffer();
	}
	else // 냥다람쥐 일 때 그릴 거
	{
		strSkillLv = L"Oh! I Can Fly!!!";
		CGraphicDev::GetInstance()->Get_InGameFont()->DrawTextW(NULL, strSkillLv.c_str(), -1,
			&m_rcFlyNavigation, DT_CENTER | DT_NOCLIP, D3DCOLOR_ARGB(m_iTranslucent, 153, 102, 0));
	
		CGraphicDev::GetInstance()->Get_InGameFont()->DrawTextW(NULL,L"Fly Get!", -1,
			&m_rcFlyGet, DT_CENTER | DT_NOCLIP, D3DCOLOR_ARGB(m_iTranslucent, 0, 153, 0));

	}



	//m_iLvPrevTranslucent
	__super::Render_Object();
}


HRESULT CSkillGetUI::Add_Component()
{

	CComponent* pComponent = nullptr;
	// 배경
	m_pBackTexCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_UI_Shade", this));
	NULL_CHECK_RETURN(m_pBackTexCom, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, m_pBackTexCom);

	// 스킬, 스킬글로우
	if (m_pSkill->Get_Name() == L"냥다람쥐")
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



	// 베이스 
	m_pBaseTexCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Get_Skill_UI", this));
	NULL_CHECK_RETURN(m_pBaseTexCom, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, m_pBackTexCom);

	// 인벤토리 UI
	m_pInventoryTexCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Get_Inven_UI", this));
	NULL_CHECK_RETURN(m_pInventoryTexCom, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, m_pBackTexCom);

	// 에로우 문양
	// m_pBackTexCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_UI_Shade", this));
	// NULL_CHECK_RETURN(m_pBackTexCom, E_FAIL);
	// m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, m_pBackTexCom);


	// 버퍼
	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	return S_OK;
}

CSkillGetUI* CSkillGetUI::Create(LPDIRECT3DDEVICE9 pGraphicDev, CSkill* _pSkill)
{
	CSkillGetUI* pInstance = new CSkillGetUI(pGraphicDev, _pSkill);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("SkillGetUI Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CSkillGetUI::Free()
{
	__super::Free();

}
