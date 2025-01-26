#pragma once
#include "Environment.h"

BEGIN(Engine)

class CTexture;

END

class CGrass : public CEnvironment
{
protected:
	explicit CGrass(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID);
	explicit CGrass(const CGrass& rhs);
	virtual ~CGrass();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;
	virtual void			Play_ColLogic(const _float& fTimeDelta) override;
private:
	HRESULT					Add_Component();

protected:
	virtual void			Free() override;

};

