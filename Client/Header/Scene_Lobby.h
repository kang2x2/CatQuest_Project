#pragma once

#include "Scene.h"

class CScene_Lobby : public Engine::CScene
{
private:
	explicit CScene_Lobby(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CScene_Lobby();

public:
	virtual HRESULT		Ready_Scene() override;
	virtual _int		Update_Scene(const _float& fTimeDelta) override;
	virtual void		LateUpdate_Scene() override;
	virtual void		Render_Scene() override;

private:
	HRESULT				Ready_Prototype();
	HRESULT				Ready_Layer_Environment();

private:

public:
	static CScene_Lobby* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void		Free() override;

};

