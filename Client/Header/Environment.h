#pragma once

#include "GameObject.h"

BEGIN(Engine)

class CTexture;

END

class CEnvironment : public Engine::CGameObject
{
protected:
	explicit CEnvironment(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID);
	explicit CEnvironment(const CEnvironment& rhs);
	virtual ~CEnvironment();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

	virtual void			Play_ColLogic(const _float& fTimeDelta) {} // 충돌 로직
public:
	CTexture*				Get_Texture() { return m_pTextureCom; }
	_bool					Get_IsCol()	  { return m_bCol; }

private:
	HRESULT					Add_Component();

protected:
	CTexture*				m_pTextureCom = nullptr;

	_bool					m_bCol;
protected:
	virtual void			Free() override;
};

