#pragma once

#include "GameObject.h"

BEGIN(Engine)

class CTerrainTex;
class CTexture;

END

class CTerrain : public Engine::CGameObject
{
public:
	explicit CTerrain(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID);
	explicit CTerrain(const CTerrain& rhs);
	virtual ~CTerrain();

public:
	virtual HRESULT		Ready_Object(void) override;
	virtual _int		Update_Object(const _float& fTimeDelta) override;
	virtual void		LateUpdate_Object(void) override;
	virtual void		Render_Object(void) override;

private:
	HRESULT				Add_Component(void);

protected:
	CTexture*			m_pTextureCom = nullptr;

public:
	static CTerrain*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID);

protected:
	_bool				m_bTool;

protected:
	virtual void		Free() override;

};