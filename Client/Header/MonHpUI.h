#pragma once
#include "UI.h"

class CMonster;

class CMonHpUI : public CUI     // 뷰포트 사용 | 화면에 고정된 표시를 위한 UI  프로토타입 입니다.
{

protected:

	explicit CMonHpUI(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CMonHpUI(const CMonHpUI& rhs);
	virtual ~CMonHpUI();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

private:
	virtual HRESULT			Add_Component() override;

	void					Follow_Owner();
	void					Set_Owner(CGameObject* pMonster) { m_pMonster = pMonster; }

private:
	CTransform*				m_pUITransformCom[5];

	CGameObject*			m_pMonster;
	_float					m_fHpRatio;
	_float					m_fCurRatio;

	_float					m_fCapSizeX;
	_float					m_fCapSizeY;

	_float					m_fBarMultiX;
	_float					m_fBarMultiY;
	_float					m_fCapMultiX;
	_float					m_fCapMultiY;

	_float					m_fBarRealX;
	_float					m_fBarRealY;
	_float					m_fCapRealX;
	_float					m_fCapRealY;


	_matrix					m_matUI[5];

	LERP_FLOAT_INFO			m_tAlpha;
	_uint					m_iAlpha;
	_bool					m_bShow;


public:
	static CMonHpUI*			Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* pMonster);


protected:
	virtual void			Free() override;
};

