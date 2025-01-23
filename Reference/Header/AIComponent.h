#pragma once
#include "Component.h"
#include "GameObject.h"

BEGIN(Engine)


class ENGINE_DLL CAIComponent : public CComponent
{
private: 
	explicit CAIComponent();
	explicit CAIComponent(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CAIComponent(const CAIComponent& rhs, CGameObject* _pOwnerObject);
	virtual ~CAIComponent();


public:
	HRESULT		Ready_AICom();
	_int		Update_Component(const _float& fTimeDelta);
public:
	// ai 이동 구현

	void	Chase_TargetY(const _vec3* pTargetPos, const _float& fTimeDelta, const _float& fSpeed);
	void	Chase_Target(const _vec3* pTargetPos, const _float& fTimeDelta, const _float& fSpeed);
	const	_matrix* Compute_LookAtTarget(const _vec3* pTargetPos);
	
	void	Random_Move(const _float& fTimeDelta, const _float& fSpeed);


public:
	static	CAIComponent*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
	
	virtual CComponent*			Clone(CGameObject* _pOwnerObject);


private:

	virtual void Free();

};

END