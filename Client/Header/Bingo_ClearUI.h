#pragma once
#include "UI.h"

class CBingo_ClearUI : public CUI
{

protected:

	explicit CBingo_ClearUI(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CBingo_ClearUI(const CBingo_ClearUI& rhs);
	virtual ~CBingo_ClearUI();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

	void					Ready_Lerp();
private:
	virtual HRESULT			Add_Component() override;

private:
	// 등장 러프
	LERP_FLOAT_INFO			m_tSizeUpLerp;
	LERP_FLOAT_INFO			m_tSizeReturnLerp;

	// 소멸 러프
	LERP_FLOAT_INFO			m_tDelSizeUpLerp;
	LERP_FLOAT_INFO			m_tDelSizeDownLerp;

	// 부유 러프
	LERP_FLOAT_INFO			m_tPosUpLerp;
	LERP_FLOAT_INFO			m_tPosDownLerp;

	// 삭제 러프
	LERP_FLOAT_INFO			m_tDeleteLerp;

	// 현재 사이즈
	_float					m_fCurSize;

	// 러프 레벨
	_int					m_iLerpLevel;

	_bool					m_bUp;
public:

	static CBingo_ClearUI* Create(LPDIRECT3DDEVICE9 pGraphicDev);


protected:
	virtual void			Free() override;
};

