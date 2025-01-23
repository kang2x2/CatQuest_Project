#pragma once

#include "CameraObject.h"

BEGIN(Engine)

END

enum class TOOL_VIEW { DEFAULT, INGAME, LINE, TYPEEND }; 
// 디폴트 뷰 / 인게임 뷰 / 라인 그리기 위한 직교 뷰

class CTool_Camera : public Engine::CCameraObject
{
private:
	explicit CTool_Camera(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CTool_Camera(const CTool_Camera& rhs);
	virtual ~CTool_Camera();

public:
	virtual HRESULT			Ready_Object(void) override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object(void) override;

public:
	void					Key_Input(const _float& fTimeDelta);
	const TOOL_VIEW&		Get_ViewType() const { return m_eView; }

private:
	HRESULT					Add_Component(void);
	void					Update_Perspevtive(const _float& fTimeDelta); // 디폴트, 인게임
	void					Update_Orthographic(const _float& fTimeDelta);// 라인

public:
	static CTool_Camera* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	_float					m_fDefaultHeight;

	_float					m_fNearZoom;		// 줌 최대 거리 (휠 조작시)	
	_float					m_fFarZoom;			// 줌 최소 거리 (")

	TOOL_VIEW				m_eView;
private:
	virtual void			Free() override;

};