#pragma once
#include "Skill.h"


class CSkill_Monster_Thunder : public CSkill
{
protected:
	explicit CSkill_Monster_Thunder(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CSkill_Monster_Thunder(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);
	explicit CSkill_Monster_Thunder(const CSkill_Monster_Thunder& rhs);
	virtual ~CSkill_Monster_Thunder();

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


public:

	static CSkill_Monster_Thunder* Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);


private:
	CEffect_Range_Quater* m_pBaseRangeEffect;
	_bool								m_bAttack;

protected:
	virtual void			Free();

};

