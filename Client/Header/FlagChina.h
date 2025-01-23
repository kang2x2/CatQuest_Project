#pragma once
#include "Flag.h"

BEGIN(Engine)

END

class CFlagChina : public CFlag
{
protected:
	explicit CFlagChina(LPDIRECT3DDEVICE9 pGraphicDev, CFlagOwner* _owner);
	explicit CFlagChina(const CFlag& rhs);
	virtual ~CFlagChina();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;


protected:
	virtual HRESULT		Add_RangeObj();

private:
	HRESULT		Add_Component();


private:

public:
	static				CFlagChina* Create(LPDIRECT3DDEVICE9 pGraphicDev, CFlagOwner* _owner);

protected:
	virtual void		Free() override;


};

