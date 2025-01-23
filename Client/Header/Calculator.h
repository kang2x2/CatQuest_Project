#pragma once
#include "Engine_Define.h"
#include "Base.h"

BEGIN(Engine)

class CGameObject;

class CCalculator : public CBase
{
	DECLARE_SINGLETON(CCalculator)

private:
	explicit CCalculator();
	virtual ~CCalculator();

public:
	bool	Mouse_Picking(LPDIRECT3DDEVICE9 pGraphicDev, POINT pt, _vec3* pVPos, CGameObject* pTerrainVertex);

	_vec3&	RealMouse_Picking(LPDIRECT3DDEVICE9 pGraphicDev, POINT pt, CGameObject* pTerrainVertex);

private:
	virtual void Free() override;
};

END
