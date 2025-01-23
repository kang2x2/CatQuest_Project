#pragma once

#include "Scene.h"

class CScene_World : public Engine::CScene
{
private:
	explicit CScene_World(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CScene_World();

public:
	virtual HRESULT		Ready_Scene() override;
	virtual _int		Update_Scene(const _float& fTimeDelta) override;
	virtual void		LateUpdate_Scene() override;
	virtual void		Render_Scene() override;

public:
	void				Finish_Game(); 
	void				Set_IsShowEnding() { m_bShowEnding = true; } // 엔딩 영상
private:
	HRESULT				Ready_Layer_Camera();
	HRESULT				Ready_Layer_UI(); 
	HRESULT				Ready_Layer_Player(); 
	HRESULT				Ready_Layer_Effect(); 
	HRESULT				Ready_Layer_Other();

	HRESULT				Ready_Load(); 

	HRESULT				Ready_Layer_KSH();
	HRESULT				Ready_Layer_KJM();
	HRESULT				Ready_Layer_LHJ();
	HRESULT				Ready_Layer_YC(); 

	void SetupVertexFog(DWORD Color, DWORD Mode, BOOL UseRange, FLOAT Density);


public:
	static CScene_World*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	LPDIRECT3DSURFACE9  m_pBackBuffer = nullptr; // Back Buffer
	HWND				m_hVideo;

	_bool				m_bEndingFade;
	_bool				m_bFinish;
	_bool				m_bShowEnding; // 엔딩 영상 보기
	_float				m_fAcc;

	LERP_FLOAT_INFO		m_tLerpVideoVolume;


private:
	virtual void		Free() override;
};

