#pragma once
#include "Flag.h"

BEGIN(Engine)

END

class CFlagThai : public CFlag
{
protected:
	explicit CFlagThai(LPDIRECT3DDEVICE9 pGraphicDev, CFlagOwner* _owner);
	explicit CFlagThai(const CFlag& rhs);
	virtual ~CFlagThai();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;


private:
	HRESULT		Add_Component();


private:

public:
	static				CFlagThai* Create(LPDIRECT3DDEVICE9 pGraphicDev, CFlagOwner* _owner);

protected:
	virtual void		Free() override;


};

