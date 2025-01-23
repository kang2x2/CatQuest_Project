#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "Engine_Define.h"


BEGIN(Engine)

class CTexture;
class CRcTex;


END

class CUI : public Engine::CGameObject
{

protected:

	explicit CUI(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID);
	explicit CUI(const CUI& rhs);
	virtual ~CUI();


public: 
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

protected:
	virtual HRESULT			Add_Component() PURE;

protected:
	
	CTexture*				m_pTextureCom;
	UI_TYPE					m_eUIType;


	_matrix					m_UImatWorld;

	// Image Pos
	_float					m_fPosX;
	_float					m_fPosY;

	// Image Size
	_float					m_fSizeX;
	_float					m_fSizeY;
	
	// Image Size Multiple
	_float					m_fMultipleSizeX;
	_float					m_fMultipleSizeY;


protected:
	virtual void			Free() override;

	

};
