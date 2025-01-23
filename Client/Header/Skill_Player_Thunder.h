#pragma once
#include "Skill.h"

BEGIN(Engine)



END

class CSkill_Player_Thunder :
    public CSkill
{
protected:
	explicit CSkill_Player_Thunder(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID);
	explicit CSkill_Player_Thunder(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);
	explicit CSkill_Player_Thunder(const CSkill_Player_Thunder& rhs);
	virtual ~CSkill_Player_Thunder();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

private:
			HRESULT			Add_Component();

public:
	virtual HRESULT			Play();
	virtual HRESULT			End();

private:
	CEffect_Range_Quater*	m_pGoldRange;
	_bool					m_bIsEffectEnd;

public:
	static CSkill_Player_Thunder* Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);

protected:
	virtual void			Free();
};

