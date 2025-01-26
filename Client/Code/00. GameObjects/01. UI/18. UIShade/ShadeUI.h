#pragma once
#include "UI.h"

BEGIN(Engine)

class CTexture;

END

class CShadeUI : public CUI     // 뷰포트 사용 | 화면에 고정된 표시를 위한 UI  프로토타입 입니다.
{

protected:
	explicit CShadeUI(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CShadeUI(const CShadeUI& rhs);
	virtual ~CShadeUI();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

private:
	virtual HRESULT			Add_Component() override;

private:
	_matrix			m_matBack;
	LERP_FLOAT_INFO	m_tTranslucentLerp;
	_int			m_iTranslucent;

public:
	static CShadeUI* Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void			Free() override;
};

