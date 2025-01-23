#pragma once
#include "UI.h"

class CPlayer;

class CFlightUI : public CUI     // 뷰포트 사용 | 화면에 고정된 표시를 위한 UI  프로토타입 입니다.
{

protected:

	explicit CFlightUI(LPDIRECT3DDEVICE9 pGraphicDev, CPlayer* pPlayer);
	explicit CFlightUI(const CFlightUI& rhs);
	virtual ~CFlightUI();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

private:
	virtual HRESULT			Add_Component() override;

private:
	CPlayer*	m_pPlayer;

public:

	static CFlightUI*		Create(LPDIRECT3DDEVICE9 pGraphicDev, CPlayer* pPlayer);


protected:
	virtual void			Free() override;
};

