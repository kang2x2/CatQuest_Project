#include "Projectile.h"

#include "EventMgr.h"
#include "Export_Function.h"


CProjectile::CProjectile(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID)
    :Engine::CGameObject(pGraphicDev, OBJ_TYPE::PROJECTILE, _eID)
    , m_fSpeed(0.f)
    , m_fAccTime(0.f)
{
}

CProjectile::CProjectile(const CProjectile& rhs)
    :Engine::CGameObject(rhs)
{
}

CProjectile::~CProjectile()
{
}

HRESULT CProjectile::Ready_Object()
{
    CGameObject::Ready_Object();

    FAILED_CHECK_RETURN(Add_Component(), E_FAIL);



    return S_OK;
}

_int CProjectile::Update_Object(const _float& fTimeDelta)
{
    _int iExit =__super::Update_Object(fTimeDelta);


    return iExit;
}

void CProjectile::LateUpdate_Object()
{

    __super::LateUpdate_Object();
}

void CProjectile::Render_Object()
{

    __super::Render_Object();

}

void CProjectile::OnCollision_Enter(CGameObject* _pColObj)
{
   
}

void CProjectile::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CProjectile::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CProjectile::Add_Component()
{
    CComponent* pComponent = nullptr;

    // AI
    pComponent = m_pAICom = dynamic_cast<CAIComponent*>(Engine::Clone_Proto(COMPONENT_TYPE::AICOM, this));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_DYNAMIC].emplace(COMPONENT_TYPE::AICOM, pComponent);


    // Rc Texture
    pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);


    // Rect Collider
    pComponent = m_pColliderCom = dynamic_cast<CRectCollider*>(Engine::Clone_Proto(COMPONENT_TYPE::COL_RECT, this));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::COL_RECT, pComponent);

    return S_OK;
}

void CProjectile::Free()
{
    __super::Free();
}
