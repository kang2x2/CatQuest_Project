#pragma once
#include "Environment.h"

BEGIN(Engine)

class CTexture;

END

class CTree : public CEnvironment
{
protected:
	explicit CTree(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID);
	explicit CTree(const CTree& rhs);
	virtual ~CTree();

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

