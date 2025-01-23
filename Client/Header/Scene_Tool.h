#pragma once

#include "Scene.h"

class CScene_Tool : public Engine::CScene
{
private:
	explicit CScene_Tool(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CScene_Tool();

public:
	virtual HRESULT		Ready_Scene() override;
	virtual _int		Update_Scene(const _float& fTimeDelta) override;
	virtual void		LateUpdate_Scene() override;
	virtual void		Render_Scene() override;

private:
	HRESULT				Ready_Layer_Camera();

	HRESULT				Ready_Layer_Terrain();

	HRESULT				Ready_Layer_Environment();
	HRESULT				Ready_Layer_Monster();
	HRESULT				Ready_Layer_Npc();
	HRESULT				Ready_Layer_Item();

public:
	static CScene_Tool* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void		Free() override;
};

