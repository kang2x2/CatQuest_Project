#pragma once
#include "Environment.h"

BEGIN(Engine)

class CTexture;

END

class CBush : public CEnvironment
{
protected:
	explicit CBush(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID);
	explicit CBush(const CBush& rhs);
	virtual ~CBush();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

	virtual void			Play_ColLogic(const _float& fTimeDelta) override; // 충돌 로직
	virtual void			Alpha_Update();
private:
	HRESULT					Add_Component();

protected:
	_vec3					m_vecInitScale;
	_vec3					m_vecEndScale;

	_bool					m_bTransSwitch1;
	_bool					m_bTransSwitch2;

	_int					m_iTranslucent;
	_int					m_iEndTranslucent;

	_bool					m_bReadySound;
protected:
	virtual void			Free() override;

};

