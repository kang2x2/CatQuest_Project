#pragma once
#include "UI.h"

class CPlayer;

class CExpUI : public CUI     // 뷰포트 사용 | 화면에 고정된 표시를 위한 UI  프로토타입 입니다.
{

protected:

	explicit CExpUI(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CExpUI(const CExpUI& rhs);
	virtual ~CExpUI();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

private:
	virtual HRESULT			Add_Component() override;

private:
	CPlayer* m_pPlayer;

	_float					m_fCurExpRatio;
	_matrix					m_matExpUI[3];
	_bool					m_bIsExpChange;
	_float					m_fAcc;
	
	LERP_FLOAT_INFO			m_tAlpha;
	_float					m_fAlpha;

	LERP_FLOAT_INFO			m_tSize;
	_float					m_fBarSizeX;

	_bool					m_bGone;

public:

	static CExpUI* Create(LPDIRECT3DDEVICE9 pGraphicDev);


protected:
	virtual void			Free() override;
};

