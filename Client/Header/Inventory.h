#pragma once
#include "UI.h"
#include "Skill.h"

#define		MAX_SKILL_SLOT 4

BEGIN(Engine)

class CRcTex;
class CTexture;
class CTransform;
class CGameObject;
class CAnimation;

END
// 아이템, 스킬 인벤토리 구분
enum class INVENTYPE { INVEN_ITEM, INVEN_SKILL, INVEN_END };
// OK, NO 버튼
enum EQUIPCHECK{ EQUIP_NONE, EQUIP_OK, EQUIP_NO };
// Player UI
enum PLAYERUI  { PLAYER_GOLD, PLAYER_ARMOR, PLAYER_HEART, PLAYER_DAMAGE, PLAYER_MAGIC, PLAYER_UI_END };
// Item UI
enum ITEMui    { ITEM_HEART, ITEM_DAMAGE, ITEM_MAGIC, ITEMUI_END};
// Skill Font
enum SkillFont { SKILL_NAME, SKILL_DAMAGE_NUM, SKILL_DAMAGE_STR, SKILL_CONTENT, SKILL_FONT_END};

#pragma region 스킬 구조체
// 스킬 정보
struct tagInvenSkill
{
	CSkill*		m_pSkill; 
	_int		m_iSkillID;
	CTexture*	m_pSkillTexCom; 
	_matrix		m_matSkill;

	_bool		m_bEquip = false;
};
// 스킬 칸(오른쪽)
struct tagSkillSpace
{
	_matrix     m_matSpace;
	CTexture*	m_pSpaceNoneTex; // 빈 칸
	CTexture*	m_pSpaceIsTex;   // 존재하는 칸
	CTexture*	m_pSpaceSelectTex; // 피킹된 칸
	_bool		m_bIsSpace = false; // 스킬이 있는지
	_bool		m_bOnSpace = false; // 피킹이 됬는지

	tagInvenSkill m_pSpaceSkill; // 스킬
};

// Skill Ring(왼쪽)
struct tagSkillRingUI
{
	_matrix     m_matEmptySkillUI; // 빈 상태
	_matrix     m_matSkillRingUI;  // 주변 링
	_matrix		m_matSkillNumUI;   // 아래 넘버

	CTexture*	m_pSkillEmptyUITex; // 빈 상태
	CTexture*	m_pSkillRingUITex;  // 주변 링
	CTexture*	m_pSkillNumUITex;   // 아래 넘버

	tagInvenSkill* m_pEquipSkill = nullptr; // 스킬

	_bool		m_bIsSkill = false; // 스킬이 있나?
};
// 스킬 북
struct tagSkillBookUI
{
	_matrix     m_matSkillBookUI;	// 스킬북 행렬
	CTexture*	m_pSkillBookTexCom; // 스킬북 텍스처
	_bool		m_bShowUI = false;
};
// 스킬 폰트
struct tagSkillStatFont
{
	RECT		m_pSkillStatRc;
};
#pragma endregion

#pragma region 아이템 구조체
// 아이템 칸
struct tagItemSpace
{
	_matrix     m_matSpace;
	_matrix		m_matEquip;
	CTexture* m_pSpaceNoneTex;
	CTexture* m_pSpaceIsTex;
	CTexture* m_pSpaceSelectTex;
	CTexture* m_pSpaceEquipTex;
	_bool		m_bIsSpace = false;
	_bool		m_bOnSpace = false;
	_bool		m_bEquip = false;
};
// 장착여부
struct tagEquipCheck
{
	_matrix     m_mateCheck;
	CTexture*   m_pOkTex;
	CTexture*   m_pNoTex;
	EQUIPCHECK  m_eEquipCheck;
	_bool		m_bShowUI;
};
// 플레이어 UI
struct tagPlayerUI
{
	_matrix     m_matPlUI;
	CTexture*	m_pPlUITex;
};
// 플레이어 스텟 폰트 박스
struct tagPlayerStatFont
{
	RECT		m_plStatRc;
};
// 아이템 스텟 UI
struct tagItemStatUI
{
	_matrix     m_matItemStatUI;
	CTexture*   m_pItemStatUITex;
};
// 아이템 스텟 폰트 박스
struct tagItemStatFont
{
	RECT		m_pItemStatRc;
};
#pragma endregion

#pragma region 공용 구조체
// 라인
struct tagLine
{
	_matrix     m_matLine;
	CTexture* m_pLineTex;
};
#pragma endregion

class CPlayer;

class CInventory : public CUI   // 뷰포트 사용 | 피킹이 가능한 형태의 UI 입니다
{
protected:

	explicit CInventory(LPDIRECT3DDEVICE9 pGraphicDevr);
	explicit CInventory(const CInventory& rhs);
	virtual ~CInventory();


public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

public:
#pragma region Ready
	// Ready
	void					Ready_WorldMatrix();
	void					Ready_PublicUI();
	// Item
	void					Ready_ItemPlayerUI();
	void					Ready_ItemUI();
	void					Ready_ItemPlayerFont();
	void					Ready_ItemFont();
	// Skill
	void					Ready_SkillUI();
	void					Ready_SkillFont();
#pragma endregion

#pragma region Render
	// Render Public
	void					Render_PublicUI();
	// Render Item
	void					Render_ItemInventory();
	void					Render_PlayerStatUI();
	void					Render_ItemUI();
	void					Render_PlayerItemFont();
	// Render Skill
	void					Render_SkillInventory();
	void					Render_PlayerSkillUI();
	void					Render_SkillUI();
	void					Render_SkillFont();
#pragma endregion

#pragma region Update
	void					Key_Input();
	void					Mouse_Update();

	void					ItemPicking_UI();
	void				    Item_StatView(_int _Index);

	void					SkillPicking_UI();
	void					Skill_StatView(_int _Index);

	void					TabPicking_UI();

	void					Skill_Slot();
#pragma endregion

public:
	// Item
	HRESULT					Add_Item(CGameObject* _pItem);
	// Skill
	HRESULT					Add_Skill(CSkill* _pSKill);
	// Key
	void					Set_HaveQuestItem(_bool _isAdd)
	{
		if (_isAdd) m_iQuestItem += 1;
		else if (!_isAdd && m_iQuestItem > 0) m_iQuestItem -= 1;
	}
	_int					Get_HaveKey() { return m_iQuestItem; }

protected:
	virtual HRESULT			Add_Component();

private:
#pragma region System
	_bool					m_bIsOn; // 활성 여부
	_bool					m_bAlphaSet; // 알파 변수
	_int					m_iTranslucent; // 온오프 알파값

	CPlayer*				m_pPlayer;	// 계속 참조할 플레이어

	_int					m_iQuestItem; // 열쇠 

	INVENTYPE				m_eInvenType; // 아이템인지 스킬인지
	
#pragma endregion

	CTexture*				m_pInventoryTexCom[INVENTORYID_END]; // 기존에 있던 배열
	_matrix                 m_matInventoryWolrd[INVENTORYID_END]; // 기존에 있던 배열

#pragma region UI
#pragma region Item
	// 아이템 인벤토리 관련
	vector<CGameObject*>	m_vecItem; // 아이템 배열

	tagItemSpace			m_sItemSpaceAry[INVEN_BUTTON12 - 2]; // 아이템 칸 배열
	tagEquipCheck			m_sItemEquipCheck; // 장비 장착 여부 구조체
	tagPlayerUI				m_sPlayerUIAry[PLAYER_UI_END]; // 플레이어 UI 배열
	tagPlayerStatFont		m_sPlayerStatFont[PLAYER_UI_END]; // 플레이어 Stat 폰트 배열
	tagItemStatUI			m_sItemStatUIAry[ITEMUI_END]; // 아이템 스텟 UI 배열
	tagItemStatFont			m_sItemStatFont[ITEMUI_END]; // 아이템 스텟 Font

	// 현재 이넘값 추가로 하기가 어려워 따로 선언함.
	RECT					m_curHPrc;
	RECT					m_curMPrc;
#pragma endregion

#pragma region Skill
	// 스킬 인벤토리 관련
	vector<tagInvenSkill>	m_vecSkill; // 스킬 배열

	tagSkillSpace			m_sSkillSpaceAry[INVEN_BUTTON12 - 2]; // 스킬 칸 배열
	tagSkillBookUI			m_sSkillBookUI; // 스킬 장착 여부 구조체
	tagSkillRingUI			m_sSkillRingAry[MAX_SKILL_SLOT]; // 왼쪽 스킬 4칸 관련
	tagSkillStatFont		m_sPlayerSkillFont[SKILL_FONT_END]; // 스킬 폰트 배열
	tagInvenSkill*			m_saveSkill; // 선택한 스킬 저장

	_matrix					m_sBigSkillRing; // 큰 링
	CTexture*				m_pBigSkillRingTex; // 큰 링

	_int					m_iPickSpace; // 선택한 스페이스 인덱스
	RECT					m_SkillSelectRc; // 슬롯 선택

	_bool					m_bPickMode; // 픽 모드
	_bool					m_bSizeUp;   // 러프 사용을 위한 bool 변수
	LERP_FLOAT_INFO			m_tSizeLerp; // 스킬 픽 모드 시 사용할 러프
#pragma endregion

	// 공용
	tagLine					m_sLineAry[INVEN_LINE - 16]; // 라인 배열
	_bool					m_bTabItemPick; // 아이템 탭 알파
	_bool					m_bTabSkillPick; // 스킬 탭 알파

#pragma endregion

#pragma region 렉트
	// 아이템 스텟 폰트
	RECT		m_ItemNameRc;
	RECT		m_ItemLvRc;
	// 능력 증가치 폰트
	RECT		m_ResultHpRc;
	RECT		m_ResultDmgRc;
	RECT		m_ResultMagicRc;
#pragma endregion

#pragma region 마네킹
	// 마네킹
	CGameObject*	m_pMannequin;
	CTexture*		m_pMannequinTexCom[_uint(CLASS_TYPE::TYPEEND)]; // 사진 배열
	CAnimation*		m_pMannequinAniCom[_uint(CLASS_TYPE::TYPEEND)]; // 애니 배열
	_matrix			m_matMannequinWorld; //

	CTexture*		m_pShadowTexCom;   // 마네킹 그림자
	_matrix			m_matShadowWorld;  // 마네킹 그림자

	CLASS_TYPE		m_eMannequinClass; // 마네킹의 클래스(직업) 
#pragma endregion
	
#pragma region  fancy

	// 왼쪽
	CTexture*	 m_pFancyLTexCom;
	_matrix		 m_matFancyLWorld;
	// 오른쪽
	CTexture*	 m_pFancyRTexCom;
	_matrix		 m_matFancyRWorld;
	// 폰트
	RECT		 m_FancyRc;

#pragma endregion
	
#pragma region CursorPt
	CTexture*	 m_pCursorTexCom;
	_matrix		 m_matCursorWorld;
#pragma endregion

#pragma region BAR
	CTexture*	 m_pBarTexCom;
	_matrix		 m_matBar[8];

	_float		m_fHpRatio;

	_float		m_fHpBarPosX;
	_float		m_fHpBarPosY;

	_float		m_fHpBarSizeX;
	_float		m_fHpBarSizeY;
	
	_float		m_fMpRatio;

	_float		m_fMpBarPosX;
	_float		m_fMpBarPosY;

	_float		m_fMpBarSizeX;
	_float		m_fMpBarSizeY;

	_float		m_fCapSizeX;
	_float		m_fCapSizeY;

#pragma endregion



public: 

	static CInventory* Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void			Free() override;


};

