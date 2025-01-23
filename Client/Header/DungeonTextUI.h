#pragma once
#include "UI.h"

class CDungeonTextUI : public CUI  // 뷰포트 사용 | 피킹이 가능한 형태의 UI 입니다
{

protected:

	explicit CDungeonTextUI(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CDungeonTextUI(const CDungeonTextUI& rhs);
	virtual ~CDungeonTextUI();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

private:
	virtual HRESULT			Add_Component() override;

private:
	LERP_FLOAT_INFO			m_tAlpha;
	_float					m_fTranslucent;
	
	_float					m_fAcc;

public:
	static CDungeonTextUI* Create(LPDIRECT3DDEVICE9 pGraphicDev);


protected:
	virtual void			Free() override;

};