#pragma once
#include "Flag.h"

BEGIN(Engine)

END

class CFlagJapen : public CFlag
{
protected:
	explicit CFlagJapen(LPDIRECT3DDEVICE9 pGraphicDev, CFlagOwner* _owner);
	explicit CFlagJapen(const CFlag& rhs);
	virtual ~CFlagJapen();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;


private:
	HRESULT		Add_Component();


private:

public:
	static				CFlagJapen* Create(LPDIRECT3DDEVICE9 pGraphicDev, CFlagOwner* _owner);

protected:
	virtual void		Free() override;


};

