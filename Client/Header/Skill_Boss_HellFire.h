#pragma once
#include "Skill.h"
class CSkill_Boss_HellFire :  public CSkill
{
protected:
	explicit CSkill_Boss_HellFire(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CSkill_Boss_HellFire(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);
	explicit CSkill_Boss_HellFire(const CSkill_Boss_HellFire& rhs);
	virtual ~CSkill_Boss_HellFire();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

public:
	virtual void			OnCollision_Enter(CGameObject* _pColObj);
	virtual void			OnCollision_Stay(CGameObject* _pColObj);
	virtual void			OnCollision_Exit(CGameObject* _pColObj);



private:
	HRESULT					Add_Component();


public:
	virtual HRESULT         EarlyPlay();
	virtual HRESULT			Play();
	virtual HRESULT			LatePlay();
	virtual HRESULT         LastPlay();
	virtual HRESULT         FinalPlay();

	virtual	HRESULT         EarlyEnd();
	virtual HRESULT			End();
	virtual HRESULT			LateEnd();
	virtual HRESULT         LastEnd();
	virtual HRESULT			FinalEnd();


	const _bool				Is_Base_End() const { return m_bBaseEffectEnd; }; 
	const _bool				Is_Skill_End() const { return m_bSkillEffectEnd; };

public:

	static CSkill_Boss_HellFire* Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);

private:
	// Front
	CEffect_Range_Quater* m_pBaseRangeEffect1;
	CEffect_Range_Quater* m_pBaseRangeEffect2;
	CEffect_Range_Quater* m_pBaseRangeEffect3;
	CEffect_Range_Quater* m_pBaseRangeEffect4;
	// Right
	CEffect_Range_Quater* m_pBaseRangeEffect5;
	CEffect_Range_Quater* m_pBaseRangeEffect6;
	CEffect_Range_Quater* m_pBaseRangeEffect7;
	CEffect_Range_Quater* m_pBaseRangeEffect8;
	// Left
	CEffect_Range_Quater* m_pBaseRangeEffect9;
	CEffect_Range_Quater* m_pBaseRangeEffect10;
	CEffect_Range_Quater* m_pBaseRangeEffect11;
	CEffect_Range_Quater* m_pBaseRangeEffect12;
	//Back
	CEffect_Range_Quater* m_pBaseRangeEffect13;
	CEffect_Range_Quater* m_pBaseRangeEffect14;
	CEffect_Range_Quater* m_pBaseRangeEffect15;
	CEffect_Range_Quater* m_pBaseRangeEffect16;


	// Front
	CSkillEffect*		 m_pSKillEffect1;
	CSkillEffect*		 m_pSKillEffect2;
	CSkillEffect*		 m_pSKillEffect3;
	CSkillEffect*		 m_pSKillEffect4;
	// Right
	CSkillEffect*		 m_pSKillEffect5;
	CSkillEffect*		 m_pSKillEffect6;
	CSkillEffect*		 m_pSKillEffect7;
	CSkillEffect*		 m_pSKillEffect8;
	// Left					 
	CSkillEffect*		 m_pSKillEffect9;
	CSkillEffect*		 m_pSKillEffect10;
	CSkillEffect*		 m_pSKillEffect11;
	CSkillEffect*		 m_pSKillEffect12;
	// Back					 
	CSkillEffect*		 m_pSKillEffect13;
	CSkillEffect*		 m_pSKillEffect14;
	CSkillEffect*		 m_pSKillEffect15;
	CSkillEffect*		 m_pSKillEffect16;


	_bool		m_bBaseEffectEnd;
	_bool	    m_bSkillEffectEnd;

	_float		m_AttackDamage;
	_bool		m_bAttack;


	// 충돌 범위 
	// Front
	CGameObject* m_pRangeObj1;
	CGameObject* m_pRangeObj2;
	CGameObject* m_pRangeObj3;
	CGameObject* m_pRangeObj4;
	//Right
	CGameObject* m_pRangeObj5;
	CGameObject* m_pRangeObj6;
	CGameObject* m_pRangeObj7;
	CGameObject* m_pRangeObj8;
	//Left
	CGameObject* m_pRangeObj9;
	CGameObject* m_pRangeObj10;
	CGameObject* m_pRangeObj11;
	CGameObject* m_pRangeObj12;
	// Back
	CGameObject* m_pRangeObj13;
	CGameObject* m_pRangeObj14;
	CGameObject* m_pRangeObj15;
	CGameObject* m_pRangeObj16;


protected:

	virtual void			Free();





};

