#pragma once
#include "UI.h"

BEGIN(Engine)

class CTexture;

END

class CQuest_DialogUI : public CUI     // 뷰포트 사용 | 화면에 고정된 표시를 위한 UI  프로토타입 입니다.
{

protected:
	explicit CQuest_DialogUI(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CQuest_DialogUI(const CQuest_DialogUI& rhs);
	virtual ~CQuest_DialogUI();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

public:
	_bool&					Is_DialogEnd() { return m_bEnd; }
	_bool&					Is_DialogDead() { return m_bDead; }
	HRESULT					Ready_Dialog(wstring strDialog, DIALOG_TYPE _bDialogType = DIALOG_TYPE::DIALOG_NORMAL);
	_bool					EndLerp_Dialog();

	void					End_Dialog();

private:
	virtual HRESULT			Add_Component() override;
	void					Typing_Effect(const _float& fTimeDelta);

private:
	// 텍스처랑 매트릭스
	CTexture*				m_pUITextureCom;
	CTransform*				m_pUITransform;
	_matrix					m_matUI;
	

	// 띄울 텍스트랑 타이핑이펙트용 변수
	RECT					m_rcText;
	wstring					m_strDialog;
	wstring					m_strTyping;
	_uint					m_iTextCnt;
	_float					m_fAcc;

	// 내리고 올릴 변수
	_bool					m_bUp;
	_bool					m_bDown;
	
	// 다이얼로그 끝났는지 판단할 불값
	_bool					m_bEnd;
	_bool					m_bDead;

	// 다이얼로그 타입
	DIALOG_TYPE				m_bDialogType;
	// 다이얼로그 러프
	LERP_FLOAT_INFO			m_tSizeUpLerpX;
	LERP_FLOAT_INFO			m_tSizeUpLerpY;
	LERP_FLOAT_INFO			m_tSizeDownLerpX;
	LERP_FLOAT_INFO			m_tSizeDownLerpY;

	// 알파
	LERP_FLOAT_INFO			m_tAlphaUpLerp;
	LERP_FLOAT_INFO			m_tAlphaDownLerp;
	_float					m_fAlpha;

	//
	LERP_FLOAT_INFO			m_tAlphaFont;
	_float					m_fAlphaFont;

public:
	static CQuest_DialogUI* Create(LPDIRECT3DDEVICE9 pGraphicDev, wstring strDialog, DIALOG_TYPE _bDialogType = DIALOG_TYPE::DIALOG_NORMAL);


protected:
	virtual void			Free() override;
};


