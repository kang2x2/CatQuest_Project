#pragma once
#include "Flag.h"

BEGIN(Engine)

END

class CFlagStart : public CFlag
{
protected:
	explicit CFlagStart(LPDIRECT3DDEVICE9 pGraphicDev, CFlagOwner* _owner);
	explicit CFlagStart(const CFlag& rhs);
	virtual ~CFlagStart();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

public:
	void					Set_Texture(const FLAG_TAG& _eID);

private:
	HRESULT		Add_Component();

public:
	_bool		Get_IsShow() { return m_bShow; }
	void		Set_IsShow(_bool _isShow) { m_bShow = _isShow; }



private:
	_bool			m_bShow;
	_float			m_fTranslucent;

	LERP_FLOAT_INFO m_tAlphaLerp;
	LERP_FLOAT_INFO m_tDeAlphaLerp;

public:
	static				CFlagStart* Create(LPDIRECT3DDEVICE9 pGraphicDev, CFlagOwner* _owner);

protected:
	virtual void		Free() override;


};

