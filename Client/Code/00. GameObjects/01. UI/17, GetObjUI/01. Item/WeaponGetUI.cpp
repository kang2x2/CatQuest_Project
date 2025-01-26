#include "stdafx.h"
#include "WeaponGetUI.h"
#include "Export_Function.h"

#include "Player.h"
#include "Item_Weapon.h"
#include "QuestMgr.h"
#include "SoundMgr.h"


CWeaponGetUI::CWeaponGetUI(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pWeapon)
	: CUI(pGraphicDev, OBJ_ID::UI_WEAPON_GET_UI)
	, m_bDelete(false)
	, m_iStatTranslucent(0)
{
	m_pWeapon = _pWeapon;
}

CWeaponGetUI::CWeaponGetUI(const CWeaponGetUI& rhs)
	: CUI(rhs)
{
}

CWeaponGetUI::~CWeaponGetUI()
{
}

HRESULT CWeaponGetUI::Ready_Object()
{
	__super::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	D3DXMatrixIdentity(&m_matBack);
	D3DXMatrixIdentity(&m_matBase);
	D3DXMatrixIdentity(&m_matWeapon);
	D3DXMatrixIdentity(&m_matInventory);
	D3DXMatrixIdentity(&m_matArrow);
	D3DXMatrixIdentity(&m_matHeart);
	D3DXMatrixIdentity(&m_matDamage);
	D3DXMatrixIdentity(&m_matArmor);

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

	// 무기
	m_fPosX = WINCX / 2;
	m_fPosY = WINCY / 2;
	m_fSizeX = 60.f;
	m_fSizeY = 120.f;
	m_fMultipleSizeX = 0.3f;
	m_fMultipleSizeY = 0.3f;
	m_matWeapon._41 = m_fPosX;
	m_matWeapon._42 = m_fPosY;
	m_matWeapon._11 = m_fSizeX * m_fMultipleSizeX;
	m_matWeapon._22 = m_fSizeY * m_fMultipleSizeY;

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

	// Heart
	m_fPosX = WINCX / 2 - 120.f;
	m_fPosY = WINCY / 2 - 85.f;
	m_fSizeX = 43.f;
	m_fSizeY = 43.f;
	m_fMultipleSizeX = 0.4f;
	m_fMultipleSizeY = 0.4f;
	m_matHeart._41 = m_fPosX;
	m_matHeart._42 = m_fPosY;
	m_matHeart._11 = m_fSizeX * m_fMultipleSizeX;
	m_matHeart._22 = m_fSizeY * m_fMultipleSizeY;

	// Damage
	m_fPosX = WINCX / 2 - 30.f;
	m_fPosY = WINCY / 2 - 85.f;
	m_fSizeX = 43.f;
	m_fSizeY = 43.f;
	m_fMultipleSizeX = 0.4f;
	m_fMultipleSizeY = 0.4f;
	m_matDamage._41 = m_fPosX;
	m_matDamage._42 = m_fPosY;
	m_matDamage._11 = m_fSizeX * m_fMultipleSizeX;
	m_matDamage._22 = m_fSizeY * m_fMultipleSizeY;

	// Armor
	m_fPosX = WINCX / 2 + 65.f;
	m_fPosY = WINCY / 2 - 85.f;
	m_fSizeX = 43.f;
	m_fSizeY = 43.f;
	m_fMultipleSizeX = 0.4f;
	m_fMultipleSizeY = 0.4f;
	m_matArmor._41 = m_fPosX;
	m_matArmor._42 = m_fPosY;
	m_matArmor._11 = m_fSizeX * m_fMultipleSizeX;
	m_matArmor._22 = m_fSizeY * m_fMultipleSizeY;

	// 무기 정보 폰트
	m_rcName = { WINCX / 2, WINCY / 2 - 100,  WINCX / 2,  WINCY / 2 - 100 };
	m_rcnNavigation = { WINCX / 2 - 25, WINCY / 2 + 120, WINCX / 2 - 25, WINCY / 2 + 120 };
	
	m_rcHeart = { WINCX / 2 - 95, WINCY / 2 + 65,  WINCX / 2 - 95,  WINCY / 2 + 65 };
	m_rcDamage = { WINCX / 2 + 35, WINCY / 2 + 65,  WINCX / 2 + 35,  WINCY / 2 + 65 };
	m_rcArmor = { WINCX / 2 + 120, WINCY / 2 + 65,  WINCX / 2 + 120,  WINCY / 2 + 65 };

	// 스탯 러프
	m_tStatLerp.Init_Lerp(LERP_MODE::EASE_OUT);
	m_tStatLerp.Set_Lerp(0.5f, WINCY / 2 + 55, WINCY / 2 + 65);

	m_eUIType = UI_TYPE::VIEW;
	m_eUILayer = UI_LAYER::LV2;

	m_iTranslucent = 0;

	return S_OK;
}

_int CWeaponGetUI::Update_Object(const _float& fTimeDelta)
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
		m_iStatTranslucent -= 5;
		if (m_iTranslucent < 5)
		{
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
	

	// 스탯 폰트
	if (m_iTranslucent > 250)
	{
		if (m_iStatTranslucent < 255)
			m_iStatTranslucent += 5;

		m_tStatLerp.Update_Lerp(fTimeDelta);

		m_rcHeart = { WINCX / 2 - 85, (_int)m_tStatLerp.fCurValue,  WINCX / 2 - 85,  (_int)m_tStatLerp.fCurValue };
		m_rcDamage = { WINCX / 2 + 5, (_int)m_tStatLerp.fCurValue,  WINCX / 2 + 5,  (_int)m_tStatLerp.fCurValue };
		m_rcArmor = { WINCX / 2 + 100, (_int)m_tStatLerp.fCurValue,  WINCX / 2 + 100,  (_int)m_tStatLerp.fCurValue };
	}


	_int iExit = __super::Update_Object(fTimeDelta);

	return iExit;
}

void CWeaponGetUI::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CWeaponGetUI::Render_Object()
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

	// 무기
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matWeapon);
	m_pWeaponTexCom->Render_Texture();
	m_pBufferCom->Render_Buffer();

	// 인벤토리 아이콘
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matInventory);
	m_pInventoryTexCom->Render_Texture();
	m_pBufferCom->Render_Buffer();

	// Heart
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matHeart);
	m_pHeartTexCom->Render_Texture();
	m_pBufferCom->Render_Buffer();

	// Damage
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matDamage);
	m_pDamageTexCom->Render_Texture();
	m_pBufferCom->Render_Buffer();

	// Armor
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matArmor);
	m_pArmorTexCom->Render_Texture();
	m_pBufferCom->Render_Buffer();

	// Font
	// 아이템명
	if (m_pWeapon->Get_Name() == L"닌자냥이 세트")
	{
		CGraphicDev::GetInstance()->Get_InGameFont()->DrawTextW(NULL, m_pWeapon->Get_Name(), -1,
			&m_rcName, DT_CENTER | DT_NOCLIP, D3DCOLOR_ARGB(m_iTranslucent, 051, 102, 051));
	}
	if (m_pWeapon->Get_Name() == L"매직냥 스태프")
	{
		CGraphicDev::GetInstance()->Get_InGameFont()->DrawTextW(NULL, m_pWeapon->Get_Name(), -1,
			&m_rcName, DT_CENTER | DT_NOCLIP, D3DCOLOR_ARGB(m_iTranslucent, 051, 102, 051));
	}
	if (m_pWeapon->Get_Name() == L"냥서커의 보물")
	{
		CGraphicDev::GetInstance()->Get_InGameFont()->DrawTextW(NULL, m_pWeapon->Get_Name(), -1,
			&m_rcName, DT_CENTER | DT_NOCLIP, D3DCOLOR_ARGB(m_iTranslucent, 051, 102, 051));
	}


	// 능력치
	wstring strStat;
	D3DCOLOR statColor;
	// 체력
	strStat = to_wstring((_int)dynamic_cast<CItem_Weapon*>(m_pWeapon)->Get_StatInfo().fMaxHP);
	statColor = (stoi(strStat) > 0) ?
		statColor = D3DCOLOR_ARGB(m_iStatTranslucent, 051, 102, 255)
		: statColor = D3DCOLOR_ARGB(m_iStatTranslucent, 153, 102, 0);
	
	CGraphicDev::GetInstance()->Get_InGameFont()->DrawTextW(NULL, strStat.c_str(), -1,
		&m_rcHeart, DT_CENTER | DT_NOCLIP, statColor);
	// 데미지
	strStat = to_wstring((_int)dynamic_cast<CItem_Weapon*>(m_pWeapon)->Get_StatInfo().fAD);
	statColor = (stoi(strStat) > 0) ?
		statColor = D3DCOLOR_ARGB(m_iStatTranslucent, 0, 153, 0)
		: statColor = D3DCOLOR_ARGB(m_iStatTranslucent, 153, 102, 0);

	CGraphicDev::GetInstance()->Get_InGameFont()->DrawTextW(NULL, strStat.c_str(), -1,
		&m_rcDamage, DT_CENTER | DT_NOCLIP, statColor);
	// 아머
	strStat = to_wstring((_int)dynamic_cast<CItem_Weapon*>(m_pWeapon)->Get_StatInfo().fMaxDef);
	statColor = (stoi(strStat) > 0) ?
		statColor = D3DCOLOR_ARGB(m_iStatTranslucent, 0, 153, 0)
		: statColor = D3DCOLOR_ARGB(m_iStatTranslucent, 153, 102, 0);

	CGraphicDev::GetInstance()->Get_InGameFont()->DrawTextW(NULL, strStat.c_str(), -1,
		&m_rcArmor, DT_CENTER | DT_NOCLIP, statColor);

	CGraphicDev::GetInstance()->Get_InGameFont()->DrawTextW(NULL, L"Equip new items in", -1,
			&m_rcnNavigation, DT_CENTER | DT_NOCLIP, D3DCOLOR_ARGB(m_iTranslucent, 153, 102, 0));

	__super::Render_Object();
}


HRESULT CWeaponGetUI::Add_Component()
{

	CComponent* pComponent = nullptr;
	// 배경
	m_pBackTexCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_UI_Shade", this));
	NULL_CHECK_RETURN(m_pBackTexCom, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, m_pBackTexCom);

	// 무기
	if (m_pWeapon->Get_Name() == L"닌자냥이 세트")
	{
		m_pWeaponTexCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Item_NinjaWeapon", this));
		NULL_CHECK_RETURN(m_pWeaponTexCom, E_FAIL);
		m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, m_pWeaponTexCom);
	}
	if (m_pWeapon->Get_Name() == L"매직냥 스태프")
	{
		m_pWeaponTexCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Item_MageWeapon", this));
		NULL_CHECK_RETURN(m_pWeaponTexCom, E_FAIL);
		m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, m_pWeaponTexCom);
	}
	if (m_pWeapon->Get_Name() == L"냥서커의 보물")
	{
		m_pWeaponTexCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Item_WarriorWeapon", this));
		NULL_CHECK_RETURN(m_pWeaponTexCom, E_FAIL);
		m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, m_pWeaponTexCom);
	}

	// 베이스 
	m_pBaseTexCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Get_Weapon_UI", this));
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

	// Heart
	m_pHeartTexCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Player_Heart", this));
	NULL_CHECK_RETURN(m_pHeartTexCom, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, m_pHeartTexCom);

	// Damage
	m_pDamageTexCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Player_Damage", this));
	NULL_CHECK_RETURN(m_pDamageTexCom, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, m_pDamageTexCom);

	// Armor
	m_pArmorTexCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Player_Armor", this));
	NULL_CHECK_RETURN(m_pArmorTexCom, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, m_pArmorTexCom);


	// 버퍼
	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	return S_OK;
}

CWeaponGetUI* CWeaponGetUI::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pWeapon)
{
	CWeaponGetUI* pInstance = new CWeaponGetUI(pGraphicDev, _pWeapon);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("WeaponGetUI Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CWeaponGetUI::Free()
{
	__super::Free();

}
