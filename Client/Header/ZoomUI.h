#pragma once
#include "UI.h"

class CZoomUI : public CUI     // 뷰포트 사용 | 화면에 고정된 표시를 위한 UI  프로토타입 입니다.
{

protected:

	explicit CZoomUI(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CZoomUI(const CZoomUI& rhs);
	virtual ~CZoomUI();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

private:
	virtual HRESULT			Add_Component() override;

public:
	_uint&					Get_ZoomState() { return m_iZoomState; }

private:
	_uint					m_iZoomState;
	_bool					m_bZoom;

public:

	static CZoomUI*		Create(LPDIRECT3DDEVICE9 pGraphicDev);


protected:
	virtual void			Free() override;
};

