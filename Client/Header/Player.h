#pragma once

#include "GameObject.h"
#include "Inventory.h"

class CRangeObj;

BEGIN(Engine)

class CRcTex;
class CTexture;
class CStateMachine;
class CAnimator;
END

class CSkill;
class CEffect;
class CUI;
class CPlayer_AfterImg;

class CPlayer : public Engine::CGameObject
{
private:
	explicit CPlayer(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CPlayer(const CPlayer& rhs);
	virtual ~CPlayer();

public:
	virtual HRESULT		Ready_Object() override;
	virtual _int		Update_Object(const _float& fTimeDelta) override;
	virtual void		LateUpdate_Object() override;
	virtual void		Render_Object() override;

public:
	virtual void		OnCollision_Enter(CGameObject* _pColObj);
	virtual void		OnCollision_Stay(CGameObject* _pColObj);
	virtual void		OnCollision_Exit(CGameObject* _pColObj);

public:


#pragma region Access Methood

#pragma region MOVEINFO

public:
	const MOVEINFO&		Get_MoveInfo() const { return m_tMoveInfo; }

	void				Set_MoveSpeed(const _float& _fMoveSpeed) { m_tMoveInfo.fMoveSpeed = _fMoveSpeed; }
	void				Set_RotSpeed(const _float& _fRotSpeed) { m_tMoveInfo.fRotSpeed = _fRotSpeed; }

	void				Add_MoveSpeed(const _float& _fMoveSpeed) { m_tMoveInfo.fMoveSpeed += _fMoveSpeed; }
	void				Add_RotSpeed(const _float& _fRotSpeed) { m_tMoveInfo.fRotSpeed += _fRotSpeed; }

#pragma endregion

#pragma region STATINFO
public:

	const STATINFO& Get_StatInfo() const { return m_tStatInfo; }

	const _bool& Is_Dead() const { return m_tStatInfo.bDead; }

	void				Set_Dead(const _bool& _bDead = TRUE) { m_tStatInfo.bDead = _bDead; }

	void				Set_MaxHP(const _float& _fMaxHp) { m_tStatInfo.fMaxHP = _fMaxHp; }
	void				Set_CurHP(const _float& _fCurHp) { m_tStatInfo.fCurHP = _fCurHp; }

	void				Set_MaxMP(const _float& _fMaxMp) { m_tStatInfo.fMaxMP = _fMaxMp; }
	void				Set_CurMP(const _float& _fCurMp) { m_tStatInfo.fCurMP = _fCurMp; }

	void				Set_MaxDef(const _float& _fMaxDef) { m_tStatInfo.fMaxDef = _fMaxDef; }
	void				Set_CurDef(const _float& _fCurDef) { m_tStatInfo.fCurDef = _fCurDef; }

	void				Set_MaxExp(const _float& _fMaxExp) { m_tStatInfo.fMaxExp = _fMaxExp; }
	void				Set_CurExp(const _float& _fCurExp) { m_tStatInfo.fCurExp = _fCurExp; }

	void				Set_AD(const _float& _fAD) { m_tStatInfo.fAD = _fAD; }
	void				Set_DF(const _float& _fDF) { m_tStatInfo.fDF = _fDF; }

	void				Set_Gold(const _float& _fGold) { m_tStatInfo.fGold = _fGold; }

	void				Set_Level(const _uint& _iLevel) { m_tStatInfo.iLevel = _iLevel; }

	void				Add_MaxHP(const _float& _fMaxHp) { m_tStatInfo.fMaxHP += _fMaxHp; }
	void				Add_CurHP(const _float& _fCurHp) { m_tStatInfo.fCurHP += _fCurHp; }

	void				Add_MaxMP(const _float& _fMaxMp) { m_tStatInfo.fMaxMP += _fMaxMp; }
	void				Add_CurMP(const _float& _fCurMp) { m_tStatInfo.fCurMP += _fCurMp; }

	void				Add_MaxDef(const _float& _fMaxDef) { m_tStatInfo.fMaxDef += _fMaxDef; }
	void				Add_CurDef(const _float& _fCurDef) { m_tStatInfo.fCurDef += _fCurDef; }

	void				Add_MaxExp(const _float& _fMaxExp) { m_tStatInfo.fMaxExp += _fMaxExp; }
	void				Add_CurExp(const _float& _fCurExp) { m_tStatInfo.fCurExp += _fCurExp; }

	void				Add_AD(const _float& _fAD) { m_tStatInfo.fAD += _fAD; }
	void				Add_DF(const _float& _fDF) { m_tStatInfo.fDF += _fDF; }

	void				Add_Gold(const _float& _fGold) { m_tStatInfo.fGold += _fGold; }

	void				Add_Level(const _uint& _iLevel) { m_tStatInfo.iLevel += _iLevel; }
#pragma endregion

#pragma region OTHER

	void				Set_CurGroudType(const GROUND_TYPE& _eType)	{ m_eCurGroundType = _eType; }
	const GROUND_TYPE&	Get_CurGroundType() const					{ return m_eCurGroundType; }

#pragma endregion

#pragma endregion


public:
	// Ŭ���� ü����
	void				Class_Change(const CLASS_TYPE& _eType);
	CLASS_TYPE&			Get_PlayerClass() { return m_eClass; }


	void				Damaged(const _float& fDamage, CGameObject* pObj);
	void				Regen_HP(const _float& fHeal);
	void				Regen_Mana();
	void				Using_Mana(const _uint& iUsage);

	_bool&				Is_Attack() { return m_bAttack; }
	void				Set_Attack(_bool bBool) { m_bAttack = bBool; }

	_bool&				Is_Hit() { return m_bHit; }
	void				Set_HIt(const _bool& bHit) { m_bHit = bHit; }

	_bool&				Is_Skill() { return m_bSkill; }
	void				Set_Skill(const _bool& bSkill) { m_bSkill = bSkill; }

	// ��ų���Լ�
	CSkill*				Get_SkillSlot(const _uint& m_iSkill) { return m_arrSkillSlot[m_iSkill]; }
	void				Set_SkillSlot(const _uint& _iIndex, CSkill* pSkill) { m_arrSkillSlot[_iIndex] = pSkill; }

	_bool&				Is_MonsterThere()		{ return m_bIsMonster; }
	_vec3&				Get_MonTargetDir()		{ return m_vMonTargetDir; }
	_float&				Get_MonTargetLength()	{ return m_fMonTargetLength; }
	CGameObject*		Get_MonTarget();

	void				Set_PlayerDirNormal(const _vec3& vDir);
	void				Set_PlayerLook(const _vec3& vDir);

	// �÷��̾� �ö���Ʈ ��ų ���� ����
	_bool&				Has_Flight() { return m_bhasFlight; }
	void				Set_HasFlight(const _bool& bHas) { m_bhasFlight = bHas; }

	// ������Ʈ�ӽ� ��������
	CStateMachine*		Get_StateM() { return m_pStateMachineCom; }

	// �÷��̾ Idle�����϶��� ���ɼ��ְ� ���ּ���
	_bool&				Is_PlayerTalking()					 { return m_bIsTalking; }
	void				Set_PlayerTalk(const _bool& bTalk)	 { m_bIsTalking = bTalk; }
	// �κ��丮
	void				Set_Inventory(CGameObject* _pInven) { m_pInven = _pInven; }
	CGameObject*		Get_Inventory() { return m_pInven; }

	void				CloseTarget_Dis(CGameObject* pTarget);
	_bool&				Is_Boss() { return m_bIsBoss; }

	CGameObject*		MageBall_Target();
	_vec3&				Get_BallDir()		  { return m_vBallDir; }
	CGameObject*		Get_BallTarget()	  { return m_pBallTarget; }
	_bool				Is_BallTarget();

	_bool&				Get_Clocking() { return m_bClocking; }
	void				Off_Clocking() { m_bClocking = false; m_iClockAlpha = 255; }

	_bool&				Is_Fly()					{ return m_bFly; }
	void				Set_Fly(const _bool& _bFly) { m_bFly = _bFly; }

	CSkill*				Get_FlySkill() { return m_pSkillFly; }

	// ����
	const _bool			Is_Jump() const;

	const _uint&		Get_ClockAlpha() const { return m_iClockAlpha; }

	// ��ǲ ����
	void				Block_Input(const _bool& _eBlock) { m_bBlockInput = _eBlock; }
	const _bool&		Is_Block() const { return m_bBlockInput; }

	// ����
	_bool&				Is_LockOn() { return m_bLockOn; }
	CSkill*				Get_SkillArrow() { return m_pSkillArrow; }

private:
	HRESULT				Add_Component();
	void				Key_Input(const _float& fTimeDelta);

	void				Regen_Def(const _float& fTimeDelta);
	
	void				Clocking_Time(const _float& fTimeDelta);

	void				Create_ThornSparkle(const _float& fTimeDelta);

	void				LevelUp();

private:
	MOVEINFO					m_tMoveInfo;
	STATINFO					m_tStatInfo;

	GROUND_TYPE					m_eCurGroundType; // ���� �÷��̾ ��ġ�� �׶��� ����

private:
	CTexture*					m_pTextureCom[_uint(STATE_TYPE::TYPEEND)];
	CTexture*					m_pNinjaTextureCom[_uint(STATE_TYPE::TYPEEND)];
	CTexture*					m_pMageTextureCom[_uint(STATE_TYPE::TYPEEND)];
	CTexture*					m_pThornTextureCom[_uint(STATE_TYPE::TYPEEND)];
	CStateMachine*				m_pStateMachineCom;
	CAnimator*					m_pClassAnimator[_uint(CLASS_TYPE::TYPEEND)];

	_uint						m_iTempMode;

	// Ŭ���� Ÿ��
	CLASS_TYPE					m_eClass;

	// �� ���� ��� ����
	_float						m_fAccDef;

	// �ǰ�, ���� �Һ���
	_bool						m_bHit;
	_bool						m_bAttack;

	// ��ų��� �� ��ų���� ����
	_bool						m_bSkill;
	CSkill*						m_arrSkillSlot[4];
	CSkill*						m_arrSkill[(UINT)SKILL_TYPE::TYPEEND];

	CSkill*						m_pSkillHeal;


	// ��������
	_bool						m_bIsMonster;
	_bool						m_bIsBoss;
	_float						m_fMonTargetLength;
	_vec3						m_vMonTargetDir;
	CGameObject*				m_pMonTarget;

	// ���Ҷ� ������ �ֱ�
	_bool						m_bIsTalking;
	
	// ���ڲٳ�
	_bool						m_bhasFlight;
	_bool						m_bFly;
	CSkill*						m_pSkillFly;
	
	// ������ȭ��
	CSkill*						m_pSkillArrow;
	_bool						m_bLockOn;

	// �̻��Ϲ߻�
	_float						m_fBallTargetLenght;
	_vec3						m_vBallDir;
	CGameObject*				m_pBallTarget;

	// ����
	_bool						m_bClocking;
	_float						m_fClockingAcc;
	_uint						m_iClockAlpha;

	// ����Ʈ
	CEffect*				    m_pEffectOra;
	CEffect*					m_pEffectBanner;
	CEffect*					m_pEffectShine;
	// �ɼ�Ŀ ��¦��
	_float						m_fThornAcc;

	// UI
	CUI*						m_pRingUI;
	CUI*						m_pFlyUI;

	//�ܻ�� ����Ʈ
	list<CGameObject*>			m_listAfterImg;
	_uint						m_iCreateAfterImg;
	

	/////////////////////////////////
	// << : Test : Range Test
	enum class RANGE_TYPE { BASIC_ATTACK, SKILL_ATK1, TYPEEND };
	CRangeObj* arrRangeObj[(UINT)RANGE_TYPE::TYPEEND]; // Set Active�� ��Ȳ�� �°� ���� �״�
	// >> :

	// �κ��丮
	CGameObject* m_pInven;

	// ��ǲ ����
	_bool		m_bBlockInput;

public:
	static CPlayer*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void		Free() override;

};

