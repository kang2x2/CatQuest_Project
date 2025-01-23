#pragma once
#include "UI.h"



class CRingUI : public CUI     // 뷰포트 사용 | 화면에 고정된 표시를 위한 UI  프로토타입 입니다.
{

protected:

	explicit CRingUI(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* pOwner);
	explicit CRingUI(const CRingUI& rhs);
	virtual ~CRingUI();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

private:
	virtual HRESULT			Add_Component() override;

	void	Follow_Player();

private:
	CGameObject*			m_pOwner;

	_uint					m_iTranslucent;
	_float					m_fAcc;
	_bool					m_bIsReach;

	LERP_FLOAT_INFO			m_tAlpha;
	_uint					m_iAlpha;
	_bool					m_bStart;
	_bool					m_bWork;

public:
	static CRingUI*			Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* pOwner);


protected:
	virtual void			Free() override;
};

