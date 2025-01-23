#pragma once
#include "UI.h"


BEGIN(Engine)

class CRcTex;
class CTexture;
class CTransform;

END

enum class FADE_COLOR { WHITE, BLACK, TYPEEND };

class CFadeUI : public CUI     // 뷰포트 사용 | 화면에 고정된 표시를 위한 UI  프로토타입 입니다.
{

protected:

	explicit CFadeUI(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CFadeUI(const CFadeUI& rhs);
	virtual ~CFadeUI();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

public:
	void					Start_Fade(const _float _fTime, const _float& _fStartvalue, const _float _fEndValue, 
										const _bool& _bWhite = FALSE, const LERP_MODE& _eMode = LERP_MODE::DEFAULT, const _bool _bDelete = TRUE);
	const _bool&			Is_Fade() const { return m_tLerpAlpha.bActive; }
	void					Set_Alpha(const _float _fAlpha) { m_tLerpAlpha.fCurValue = _fAlpha; }
private:
	virtual HRESULT			Add_Component() override;

private:

	_matrix					m_matWorld;
	LERP_FLOAT_INFO			m_tLerpAlpha; // Alpha Value
	FADE_COLOR				m_eFadeColor;

	_bool					m_bDelete;
	CTexture* m_pUITextureCom[(UINT)FADE_COLOR::TYPEEND];

public:

	static CFadeUI* Create(LPDIRECT3DDEVICE9 pGraphicDev);


protected:
	virtual void			Free() override;
};

