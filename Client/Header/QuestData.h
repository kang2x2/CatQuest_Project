#pragma once
#include "GameObject.h"
#include "Skill.h"
#include "SkillGetEffect.h"
#include "WeaponGetEffect.h"
#include "ShadeUI.h"

BEGIN(Engine)
END

enum NPC_NAME
{
	KING, MAGE, SMITH, SOLDIER, CITIZEN1, CITIZEN2
};

struct tagQuestContent
{
	wstring					m_strQuestContent; // ����Ʈ ����
	_bool					m_bClear; // Ŭ���� ����
};

class CQuestData : public CBase
{
public:
	explicit CQuestData();
	virtual ~CQuestData();

public:
	virtual void  Init(LPDIRECT3DDEVICE9 m_pGraphicDev, CGameObject* _pPlayer)   = 0;
	virtual _bool Update(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pIndicator, _bool* _IsAble) = 0;

public:
	virtual wstring					Get_QuestName()	   { return m_strQuestName; }
	virtual vector<tagQuestContent> Get_QuestContent() { return m_tQuestContent; }
	virtual _bool					Get_ShowQuestView() { return m_bShowQuestView; }
	virtual void					Set_ReadyNext() { m_bReadyNext = true; }

	virtual void					Set_ReadyTalk(CGameObject* _pNpc, _bool isTalk);

	virtual void					Set_TestLevel(_int _iLevel)
	{
		m_iLevel = _iLevel;
	}
protected:
	wstring					m_strQuestName; // ����Ʈ �̸�
	vector<tagQuestContent> m_tQuestContent; // ����Ʈ ����
	vector<CGameObject*>	m_vNpcList;		// ���� Npc�� ���� �迭
	vector<CGameObject*>	m_vItemList;	// ���� �������� ���� �迭
	vector<CSkill*>			m_vSkillList;	// ���� ��ų�� ���� �迭
	CShadeUI*				m_pShadeUI;		// ���� ���� �� ȭ�� �˰�
	CSkillGetEffect*		m_pSkillGetUI;  // ���� ����
	CWeaponGetEffect*		m_pWeaponGetUI;  // ���� ����
	_int					m_iLevel;		// ����Ʈ �ܰ�
	CGameObject*			m_pPlayer;      // �÷��̾�

	_bool					m_bShowQuestView; // ����Ʈ ������ ���� ��������
	_bool					m_bReadyNext;	  // ������ �ߺ� ȹ�� ������ ��� ����
	_bool					m_bStartQuest;    // ���� ���� �� ���� �� ����.

	_bool					m_bReadyTalk;    // Idle�� ���� ��ȭ ����.
	STATE_TYPE				ePlayerState;    // Idle�� ���� ��ȭ ����.

private:
	virtual void			Free();
};

