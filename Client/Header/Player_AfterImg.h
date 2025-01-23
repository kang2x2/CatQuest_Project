#pragma once
#include "GameObject.h"

BEGIN(Engine)

class CRcTex;
class CTexture;
class CAnimator;
class CAnimation;

END

class CPlayer;

class CPlayer_AfterImg : public CGameObject
{
protected:
	explicit CPlayer_AfterImg(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID);
	explicit CPlayer_AfterImg(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);
	explicit CPlayer_AfterImg(const CPlayer_AfterImg& rhs);
	virtual ~CPlayer_AfterImg();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

private:
	HRESULT					Add_Component();

public:
	_bool&					Is_Off() { return m_bOff; }

private:
	CGameObject*			m_pOwner;
	CTexture*				m_pNinjaTextureCom[_uint(STATE_TYPE::TYPEEND)];

	_uint					m_iCurFrame;
	_vec3					m_vCurPos;
	STATE_TYPE				m_eCurState;

	_uint					m_iAlpha;
	LERP_FLOAT_INFO			m_tAlpha;

	_bool					m_bOff;

public:
	static CPlayer_AfterImg* Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);

protected:
	virtual void			Free();
};