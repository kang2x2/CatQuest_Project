#pragma once
#include "Environment.h"

BEGIN(Engine)

class CTexture;

END

class CPillar : public CEnvironment
{
protected:
	explicit CPillar(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID);
	explicit CPillar(const CPillar& rhs);
	virtual ~CPillar();

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

