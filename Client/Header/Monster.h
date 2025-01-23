#pragma once

#include "GameObject.h"

class CRangeObj;
class CSkill;

BEGIN(Engine)
class CTexture;
class CAIComponent;
class CRcTex;
class CStateMachine;
class CAnimator;
END

class CMonster : public Engine::CGameObject
{
protected:
	explicit CMonster(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID);
	explicit CMonster(const CMonster& rhs);
	virtual ~CMonster();

public:
	virtual HRESULT			Ready_Object		() override;
	virtual _int			Update_Object		(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object	() override;
	virtual void			Render_Object		() override;


public:
	virtual void			OnCollision_Enter(CGameObject* _pColObj);
	virtual void			OnCollision_Stay(CGameObject* _pColObj);
	virtual void			OnCollision_Exit(CGameObject* _pColObj);

#pragma region Access Methood

#pragma region MOVEINFO

public:
	const MOVEINFO&		Get_MoveInfo() const { return m_tMoveInfo; }



	void				Set_MoveSpeed(const _float& _fMoveSpeed)		{ m_tMoveInfo.fMoveSpeed = _fMoveSpeed; }
	void				Set_RotSpeed(const _float& _fRotSpeed)			{ m_tMoveInfo.fRotSpeed = _fRotSpeed; }

	void				Add_MoveSpeed(const _float& _fMoveSpeed)		{ m_tMoveInfo.fMoveSpeed += _fMoveSpeed; }
	void				Add_RotSpeed(const _float& _fRotSpeed)			{ m_tMoveInfo.fRotSpeed += _fRotSpeed; }



#pragma endregion

#pragma region STATINFO
public:

	const	STATINFO& Get_StatInfo() const { return m_tStatInfo; }

	const		 _bool& Is_Dead() const { return m_tStatInfo.bDead; }

	void				Set_Dead(const _bool& _bDead = TRUE) { m_tStatInfo.bDead = _bDead; }

	void				Set_MaxHP(const _float& _fMaxHp) { m_tStatInfo.fMaxHP = _fMaxHp; }
	void				Set_CurHP(const _float& _fCurHp) { m_tStatInfo.fCurHP = _fCurHp; }

	void				Set_MaxMP(const _float& _fMaxMp) { m_tStatInfo.fMaxMP = _fMaxMp; }
	void				Set_CurMP(const _float& _fCurMp) { m_tStatInfo.fCurMP = _fCurMp; }

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

	void				Add_MaxExp(const _float& _fMaxExp) { m_tStatInfo.fMaxExp += _fMaxExp; }
	void				Add_CurExp(const _float& _fCurExp) { m_tStatInfo.fCurExp += _fCurExp; }

	void				Add_AD(const _float& _fAD) { m_tStatInfo.fAD += _fAD; }
	void				Add_DF(const _float& _fDF) { m_tStatInfo.fDF += _fDF; }

	void				Add_Gold(const _float& _fGold) { m_tStatInfo.fGold += _fGold; }

	void				Add_Level(const _uint& _iLevel) { m_tStatInfo.iLevel += _iLevel; }
#pragma endregion

	const _vec3&		Get_OriginPos() const    { return m_vOriginPos; }
	const _float&		Get_PatternTime() const { return fPatternTime; }
	 
	_float			Get_MaxJumpY()  { return m_fMaxJumpY; }
	void			Set_MaxJumpY(_float MaxJumpY) { m_fMaxJumpY = MaxJumpY; }
	void			Set_AccTime(_float AccTime) { m_fAccTime = AccTime; }

	CStateMachine*  Get_StateM() { return m_pStateMachineCom; }

#pragma endregion

private:
	HRESULT					Add_Component();

public:
	void					Damaged(const _float& fDamage, CGameObject* pObj = nullptr);

	_bool					IsHit() { return m_bHit; }
	void					Set_Hit(_bool bHit) { m_bHit = bHit; }

	_bool					IsAttack() { return m_bAttack; }
	void					Set_Attack(_bool bAttack) { m_bAttack = bAttack; }

	CStateMachine*			Get_StateMachine() { return m_pStateMachineCom; }

protected:
	MOVEINFO				m_tMoveInfo;
	STATINFO				m_tStatInfo;

	_float					fPatternTime;
	_float					m_fAccTime;

	_vec3					m_vOriginPos;

	_float					m_fJumpingSpeed; 
	_float					m_fMaxJumpY;
	_vec3					m_vImageSize; 
	
	_bool					m_bHit;				// Demaged
	_bool					m_bAttack;			// Attack
	_bool					m_bInit;			// Lateinit 


	// Skill
	_bool					m_bSkill;
	_bool					m_bLateSkill;
	_bool					m_bBaseSkill;

	CSkill*					m_pSkill;
	CSkill*					m_pBaseSkill;


	// Alpha lerp
	LERP_FLOAT_INFO         m_tAlpha;


	//Sound
	_bool                    m_bAttackSound;



	// Attack
	_bool					m_bAttackCheck;
	_bool					m_bAttackCheck2;

protected:
	
	CTexture*				m_pTextureCom[_uint(STATE_TYPE::TYPEEND)];
	CAIComponent*			m_pAICom;
	CStateMachine*			m_pStateMachineCom;

	// << : Test : Range Test
	enum class RANGE_TYPE { BASIC_ATTACK, SKILL_ATK1, TYPEEND };
	CRangeObj* arrRangeObj[(UINT)RANGE_TYPE::TYPEEND]; // Set Active·Î »óÈ²¿¡ ¸Â°Ô ²°´Ù Ä×´Ù
	// >> :

protected:
	virtual void			Free() override;

};

