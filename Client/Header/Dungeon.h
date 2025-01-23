#pragma once
#include "Environment.h"

BEGIN(Engine)

class CTexture;

END

class CDungeon : public CEnvironment
{
protected:
	explicit CDungeon(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID);
	explicit CDungeon(const CDungeon& rhs);
	virtual ~CDungeon();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;
	virtual void			Play_ColLogic(const _float& fTimeDelta) override;

private:
	HRESULT					Add_Component();

protected:
	_bool					m_bReservedSceneChange;

protected:
	virtual void			Free() override;

};

