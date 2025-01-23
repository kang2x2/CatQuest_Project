#pragma once
#include "Skill.h"
class CSkill_Boss_BlueThunder :  public CSkill
{
protected:
	explicit CSkill_Boss_BlueThunder(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CSkill_Boss_BlueThunder(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);
	explicit CSkill_Boss_BlueThunder(const CSkill_Boss_BlueThunder& rhs);
	virtual ~CSkill_Boss_BlueThunder();

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
	virtual HRESULT			Play();
	virtual HRESULT			LatePlay();
	virtual HRESULT			End();
	virtual HRESULT			LateEnd();


	const _bool				Is_Base_End() const { return m_bBaseEffectEnd; }; 
	const _bool				Is_Skill_End() const { return m_bSkillEffectEnd; };

public:

	static CSkill_Boss_BlueThunder* Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);

private:

	CEffect_Range_Quater* m_pBaseRangeEffect1;
	CEffect_Range_Quater* m_pBaseRangeEffect2;
	CEffect_Range_Quater* m_pBaseRangeEffect3;
	CEffect_Range_Quater* m_pBaseRangeEffect4;

	CEffect_Range_Quater* m_pBaseRangeEffect5;
	CEffect_Range_Quater* m_pBaseRangeEffect6;
	CEffect_Range_Quater* m_pBaseRangeEffect7;
	CEffect_Range_Quater* m_pBaseRangeEffect8;


	CSkillEffect*		  m_pSKillEffect1;
	CSkillEffect*		  m_pSKillEffect2;
	CSkillEffect*		  m_pSKillEffect3;
	CSkillEffect*		  m_pSKillEffect4;

	CSkillEffect*		  m_pSKillEffect5;
	CSkillEffect*		  m_pSKillEffect6;
	CSkillEffect*		  m_pSKillEffect7;
	CSkillEffect*		  m_pSKillEffect8;


	// 충돌 범위
	CGameObject* m_pRangeObj1;
	CGameObject* m_pRangeObj2;
	CGameObject* m_pRangeObj3;
	CGameObject* m_pRangeObj4;

	CGameObject* m_pRangeObj5;
	CGameObject* m_pRangeObj6;
	CGameObject* m_pRangeObj7;
	CGameObject* m_pRangeObj8;


	
	_bool		m_bBaseEffectEnd;
	_bool	    m_bSkillEffectEnd;


	_bool					m_bAttack;


protected:
	virtual void			Free();





};

