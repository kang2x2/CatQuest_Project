#pragma once

/*

	* 배경 로고 하나 띄워두고 컴포넌트와 텍스처를 로딩한다.
	
*/

#include "Scene.h"

class CLoadingThread;
class CFadeUI;

class CScene_Intro : public Engine::CScene
{
private:
	explicit CScene_Intro(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CScene_Intro();

public:
	virtual HRESULT		Ready_Scene() override;
	virtual _int		Update_Scene(const _float& fTimeDelta) override;
	virtual void		LateUpdate_Scene() override;
	virtual void		Render_Scene() override;



private:
	HRESULT				Ready_Prototype();
	HRESULT				Ready_Layer_Environment();

private:
	CLoadingThread*		m_pLoading;
	LPDIRECT3DSURFACE9  m_pBackBuffer = nullptr; // Back Buffer
	HWND				m_hVideo;


	CFadeUI*			m_pUI;
	LERP_FLOAT_INFO		m_tLerpVideoVolume;


public:
	static CScene_Intro*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void		Free() override;

};

