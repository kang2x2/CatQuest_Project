#pragma once

#include "Scene.h"

class CLoadingThread;

class CScene_Dungeon_Temple : public Engine::CScene
{
private:
	explicit CScene_Dungeon_Temple(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CScene_Dungeon_Temple();

public:
	virtual HRESULT		Ready_Scene() override;
	virtual _int		Update_Scene(const _float& fTimeDelta) override;
	virtual void		LateUpdate_Scene() override;
	virtual void		Render_Scene() override;

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

private:

public:
	static CScene_Dungeon_Temple* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void		Free() override;

};

