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
	wstring					m_strQuestContent; // 퀘스트 내용
	_bool					m_bClear; // 클리어 여부
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
	wstring					m_strQuestName; // 퀘스트 이름
	vector<tagQuestContent> m_tQuestContent; // 퀘스트 내용
	vector<CGameObject*>	m_vNpcList;		// 관련 Npc를 담을 배열
	vector<CGameObject*>	m_vItemList;	// 보상 아이템을 담을 배열
	vector<CSkill*>			m_vSkillList;	// 보상 스킬을 담을 배열
	CShadeUI*				m_pShadeUI;		// 보상 연출 시 화면 검게
	CSkillGetEffect*		m_pSkillGetUI;  // 보상 연출
	CWeaponGetEffect*		m_pWeaponGetUI;  // 보상 연출
	_int					m_iLevel;		// 퀘스트 단계
	CGameObject*			m_pPlayer;      // 플레이어

	_bool					m_bShowQuestView; // 퀘스트 내용을 띄우고 싶을때만
	_bool					m_bReadyNext;	  // 아이템 중복 획득 방지용 대기 변수
	_bool					m_bStartQuest;    // 레벨 진입 시 최초 한 번만.

	_bool					m_bReadyTalk;    // Idle일 때만 대화 가능.
	STATE_TYPE				ePlayerState;    // Idle일 때만 대화 가능.

private:
	virtual void			Free();
};

