#pragma once

#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CAI : public CComponent
{
protected:
	explicit CAI();
	explicit CAI(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CAI(const CAI& rhs);
	virtual ~CAI();



public:
	virtual	void	Free(void);
};

END