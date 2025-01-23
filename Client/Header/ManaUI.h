#pragma once
#include "UI.h"

class CPlayer;

class CManaUI : public CUI     // 뷰포트 사용 | 화면에 고정된 표시를 위한 UI  프로토타입 입니다.
{

protected:

	explicit CManaUI(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CManaUI(const CManaUI& rhs);
	virtual ~CManaUI();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

private:
	virtual HRESULT			Add_Component() override;

	void					Follow_Player();

private:
	CTransform*				m_pUITransformCom[5];

	CPlayer*				m_pPlayer;
	_float					m_fMpRatio;
	_float					m_fCurRatio;

	LERP_FLOAT_INFO			m_tAlpha;
	_uint					m_iAlpha;
	_bool					m_bStart;
	_bool					m_bWork;

public:
	static CManaUI*			Create(LPDIRECT3DDEVICE9 pGraphicDev);


protected:
	virtual void			Free() override;
};

