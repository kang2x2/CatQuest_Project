#include "BasicProjectile.h"
#include "Player.h"


CBasicProjectile::CBasicProjectile(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID)
    : CProjectile(pGraphicDev, _eID)
{
}

CBasicProjectile::CBasicProjectile(const CProjectile& rhs)
    : CProjectile(rhs)
{
}

CBasicProjectile::~CBasicProjectile()
{
}

HRESULT CBasicProjectile::Ready_Object()
{
    __super::Ready_Object();


    FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

    return S_OK;
}

_int CBasicProjectile::Update_Object(const _float& fTimeDelta)
{
    _int iExit = __super::Update_Object(fTimeDelta);


    return iExit;
}

void CBasicProjectile::LateUpdate_Object()
{
    __super::LateUpdate_Object();
}

void CBasicProjectile::Render_Object()
{
    __super::Render_Object();
}

void CBasicProjectile::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CBasicProjectile::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CBasicProjectile::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CBasicProjectile::Add_Component()
{

    return S_OK;
}

void CBasicProjectile::Free()
{
    __super::Free();
}
