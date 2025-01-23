#pragma once

#include "GameObject.h"

BEGIN(Engine)

class ENGINE_DLL CVirtualCamera : public CGameObject
{
protected:
	explicit CVirtualCamera(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CVirtualCamera(const CVirtualCamera& rhs);
	virtual ~CVirtualCamera();

public:
	virtual HRESULT						Ready_Object(void);
	virtual _int						Update_Object(const _float& fTimeDelta);
	virtual void						LateUpdate_Object(void);
	virtual void						Render_Object(void);

public:

private:

protected:
	LPDIRECT3DDEVICE9					m_pGraphicDev;

public:
	virtual void						Free();
};


END