#include "BossProjectile.h"
#include "Player.h"

CBossProjectile::CBossProjectile(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID)
	: CProjectile(pGraphicDev, _eID)
{
}

CBossProjectile::CBossProjectile(const CProjectile& rhs)
	: CProjectile(rhs)
{
}

CBossProjectile::~CBossProjectile()
{
}

HRESULT CBossProjectile::Ready_Object()
{
	__super::Ready_Object();


	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);


	return S_OK;
}

_int CBossProjectile::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);


	return iExit;
}

void CBossProjectile::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CBossProjectile::Render_Object()
{
	__super::Render_Object();
}

void CBossProjectile::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CBossProjectile::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CBossProjectile::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CBossProjectile::Add_Component()
{
	return S_OK;
}

void CBossProjectile::Free()
{
	__super::Free();
}
