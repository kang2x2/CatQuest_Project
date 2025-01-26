#pragma once
#include "Flag.h"

BEGIN(Engine)

END

class CFlagUSA : public CFlag
{
protected:
	explicit CFlagUSA(LPDIRECT3DDEVICE9 pGraphicDev, CFlagOwner* _owner);
	explicit CFlagUSA(const CFlag& rhs);
	virtual ~CFlagUSA();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;


private:
	HRESULT		Add_Component();


private:

public:
	static				CFlagUSA* Create(LPDIRECT3DDEVICE9 pGraphicDev, CFlagOwner* _owner);

protected:
	virtual void		Free() override;


};

