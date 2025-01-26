#pragma once
#include "Environment.h"

BEGIN(Engine)

class CTexture;

END

class CMountain : public CEnvironment
{
protected:
	explicit CMountain(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID);
	explicit CMountain(const CMountain& rhs);
	virtual ~CMountain();

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

