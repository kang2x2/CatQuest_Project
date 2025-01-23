#pragma once
#include "Skill.h"

BEGIN(Engine)



END

class CSkill_Player_Ice :
    public CSkill
{
protected:
	explicit CSkill_Player_Ice(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID);
	explicit CSkill_Player_Ice(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);
	explicit CSkill_Player_Ice(const CSkill_Player_Ice& rhs);
	virtual ~CSkill_Player_Ice();

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

public:
	static CSkill_Player_Ice* Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);

protected:
	virtual void			Free();
};

