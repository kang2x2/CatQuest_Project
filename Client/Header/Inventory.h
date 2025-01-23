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
// ������, ��ų �κ��丮 ����
enum class INVENTYPE { INVEN_ITEM, INVEN_SKILL, INVEN_END };
// OK, NO ��ư
enum EQUIPCHECK{ EQUIP_NONE, EQUIP_OK, EQUIP_NO };
// Player UI
enum PLAYERUI  { PLAYER_GOLD, PLAYER_ARMOR, PLAYER_HEART, PLAYER_DAMAGE, PLAYER_MAGIC, PLAYER_UI_END };
// Item UI
enum ITEMui    { ITEM_HEART, ITEM_DAMAGE, ITEM_MAGIC, ITEMUI_END};
// Skill Font
enum SkillFont { SKILL_NAME, SKILL_DAMAGE_NUM, SKILL_DAMAGE_STR, SKILL_CONTENT, SKILL_FONT_END};

#pragma region ��ų ����ü
// ��ų ����
struct tagInvenSkill
{
	CSkill*		m_pSkill; 
	_int		m_iSkillID;
	CTexture*	m_pSkillTexCom; 
	_matrix		m_matSkill;

	_bool		m_bEquip = false;
};
// ��ų ĭ(������)
struct tagSkillSpace
{
	_matrix     m_matSpace;
	CTexture*	m_pSpaceNoneTex; // �� ĭ
	CTexture*	m_pSpaceIsTex;   // �����ϴ� ĭ
	CTexture*	m_pSpaceSelectTex; // ��ŷ�� ĭ
	_bool		m_bIsSpace = false; // ��ų�� �ִ���
	_bool		m_bOnSpace = false; // ��ŷ�� �����

	tagInvenSkill m_pSpaceSkill; // ��ų
};

// Skill Ring(����)
struct tagSkillRingUI
{
	_matrix     m_matEmptySkillUI; // �� ����
	_matrix     m_matSkillRingUI;  // �ֺ� ��
	_matrix		m_matSkillNumUI;   // �Ʒ� �ѹ�

	CTexture*	m_pSkillEmptyUITex; // �� ����
	CTexture*	m_pSkillRingUITex;  // �ֺ� ��
	CTexture*	m_pSkillNumUITex;   // �Ʒ� �ѹ�

	tagInvenSkill* m_pEquipSkill = nullptr; // ��ų

	_bool		m_bIsSkill = false; // ��ų�� �ֳ�?
};
// ��ų ��
struct tagSkillBookUI
{
	_matrix     m_matSkillBookUI;	// ��ų�� ���
	CTexture*	m_pSkillBookTexCom; // ��ų�� �ؽ�ó
	_bool		m_bShowUI = false;
};
// ��ų ��Ʈ
struct tagSkillStatFont
{
	RECT		m_pSkillStatRc;
};
#pragma endregion

#pragma region ������ ����ü
// ������ ĭ
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
// ��������
struct tagEquipCheck
{
	_matrix     m_mateCheck;
	CTexture*   m_pOkTex;
	CTexture*   m_pNoTex;
	EQUIPCHECK  m_eEquipCheck;
	_bool		m_bShowUI;
};
// �÷��̾� UI
struct tagPlayerUI
{
	_matrix     m_matPlUI;
	CTexture*	m_pPlUITex;
};
// �÷��̾� ���� ��Ʈ �ڽ�
struct tagPlayerStatFont
{
	RECT		m_plStatRc;
};
// ������ ���� UI
struct tagItemStatUI
{
	_matrix     m_matItemStatUI;
	CTexture*   m_pItemStatUITex;
};
// ������ ���� ��Ʈ �ڽ�
struct tagItemStatFont
{
	RECT		m_pItemStatRc;
};
#pragma endregion

#pragma region ���� ����ü
// ����
struct tagLine
{
	_matrix     m_matLine;
	CTexture* m_pLineTex;
};
#pragma endregion

class CPlayer;

class CInventory : public CUI   // ����Ʈ ��� | ��ŷ�� ������ ������ UI �Դϴ�
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
	_bool					m_bIsOn; // Ȱ�� ����
	_bool					m_bAlphaSet; // ���� ����
	_int					m_iTranslucent; // �¿��� ���İ�

	CPlayer*				m_pPlayer;	// ��� ������ �÷��̾�

	_int					m_iQuestItem; // ���� 

	INVENTYPE				m_eInvenType; // ���������� ��ų����
	
#pragma endregion

	CTexture*				m_pInventoryTexCom[INVENTORYID_END]; // ������ �ִ� �迭
	_matrix                 m_matInventoryWolrd[INVENTORYID_END]; // ������ �ִ� �迭

#pragma region UI
#pragma region Item
	// ������ �κ��丮 ����
	vector<CGameObject*>	m_vecItem; // ������ �迭

	tagItemSpace			m_sItemSpaceAry[INVEN_BUTTON12 - 2]; // ������ ĭ �迭
	tagEquipCheck			m_sItemEquipCheck; // ��� ���� ���� ����ü
	tagPlayerUI				m_sPlayerUIAry[PLAYER_UI_END]; // �÷��̾� UI �迭
	tagPlayerStatFont		m_sPlayerStatFont[PLAYER_UI_END]; // �÷��̾� Stat ��Ʈ �迭
	tagItemStatUI			m_sItemStatUIAry[ITEMUI_END]; // ������ ���� UI �迭
	tagItemStatFont			m_sItemStatFont[ITEMUI_END]; // ������ ���� Font

	// ���� �̳Ѱ� �߰��� �ϱⰡ ����� ���� ������.
	RECT					m_curHPrc;
	RECT					m_curMPrc;
#pragma endregion

#pragma region Skill
	// ��ų �κ��丮 ����
	vector<tagInvenSkill>	m_vecSkill; // ��ų �迭

	tagSkillSpace			m_sSkillSpaceAry[INVEN_BUTTON12 - 2]; // ��ų ĭ �迭
	tagSkillBookUI			m_sSkillBookUI; // ��ų ���� ���� ����ü
	tagSkillRingUI			m_sSkillRingAry[MAX_SKILL_SLOT]; // ���� ��ų 4ĭ ����
	tagSkillStatFont		m_sPlayerSkillFont[SKILL_FONT_END]; // ��ų ��Ʈ �迭
	tagInvenSkill*			m_saveSkill; // ������ ��ų ����

	_matrix					m_sBigSkillRing; // ū ��
	CTexture*				m_pBigSkillRingTex; // ū ��

	_int					m_iPickSpace; // ������ �����̽� �ε���
	RECT					m_SkillSelectRc; // ���� ����

	_bool					m_bPickMode; // �� ���
	_bool					m_bSizeUp;   // ���� ����� ���� bool ����
	LERP_FLOAT_INFO			m_tSizeLerp; // ��ų �� ��� �� ����� ����
#pragma endregion

	// ����
	tagLine					m_sLineAry[INVEN_LINE - 16]; // ���� �迭
	_bool					m_bTabItemPick; // ������ �� ����
	_bool					m_bTabSkillPick; // ��ų �� ����

#pragma endregion

#pragma region ��Ʈ
	// ������ ���� ��Ʈ
	RECT		m_ItemNameRc;
	RECT		m_ItemLvRc;
	// �ɷ� ����ġ ��Ʈ
	RECT		m_ResultHpRc;
	RECT		m_ResultDmgRc;
	RECT		m_ResultMagicRc;
#pragma endregion

#pragma region ����ŷ
	// ����ŷ
	CGameObject*	m_pMannequin;
	CTexture*		m_pMannequinTexCom[_uint(CLASS_TYPE::TYPEEND)]; // ���� �迭
	CAnimation*		m_pMannequinAniCom[_uint(CLASS_TYPE::TYPEEND)]; // �ִ� �迭
	_matrix			m_matMannequinWorld; //

	CTexture*		m_pShadowTexCom;   // ����ŷ �׸���
	_matrix			m_matShadowWorld;  // ����ŷ �׸���

	CLASS_TYPE		m_eMannequinClass; // ����ŷ�� Ŭ����(����) 
#pragma endregion
	
#pragma region  fancy

	// ����
	CTexture*	 m_pFancyLTexCom;
	_matrix		 m_matFancyLWorld;
	// ������
	CTexture*	 m_pFancyRTexCom;
	_matrix		 m_matFancyRWorld;
	// ��Ʈ
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

