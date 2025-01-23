#include "Firework_Bullet.h"
#include "Export_Function.h"
#include "EventMgr.h"
#include "Player.h"

#include "Firework_Sub_Bullet.h"

CFirework_Bullet::CFirework_Bullet(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos, CGameObject* pTarget, CGameObject* pOwner)
    : CBasicProjectile(pGraphicDev, OBJ_ID::PROJECTILE_FIREWORK_BULLET)
{
    m_vPos = _vPos;
    m_pTarget = pTarget;
    m_pOwner = pOwner;
}

CFirework_Bullet::CFirework_Bullet(const CProjectile& rhs)
    : CBasicProjectile(rhs)
{
}

CFirework_Bullet::~CFirework_Bullet()
{
}

HRESULT CFirework_Bullet::Ready_Object()
{
    __super::Ready_Object();
    FAILED_CHECK_RETURN(Add_Component(), E_FAIL);


    m_pTransformCom->Set_Pos(m_vPos);
    m_pTransformCom->Set_Dir(m_vDir);


    //m_fSpeed = 18.f;

    m_szName = L"Projectile_FireWorkBullet";

    //m_fDamage = 6.f + rand() % 3;

    m_fScale = 0.f;

    m_bDelete = false;


    m_tPosY.Init_Lerp(LERP_MODE::EXPONENTIAL);
    m_tPosY.Set_Lerp(1.2f, m_vPos.y, m_pTarget->Get_Transform()->Get_Info(INFO::INFO_POS).y);
    m_tPosY.fCurValue = m_tPosY.fStartValue;

    m_bShrink = false;

    return S_OK;
}

_int CFirework_Bullet::Update_Object(const _float& fTimeDelta)
{
    Engine::Add_RenderGroup(RENDER_ALPHA, this);
    _int iExit = __super::Update_Object(fTimeDelta);

   
    if (m_tPosY.bActive)
    {
        m_pTransformCom->Set_PosY(m_tPosY.fCurValue);
    }
    else if(!m_bShrink && !m_tPosY.bActive)
    {
        m_tScale.Init_Lerp(LERP_MODE::EASE_IN);
        m_tScale.Set_Lerp(0.5f, m_pTransformCom->Get_Scale().x, m_pTransformCom->Get_Scale().x * 0.5);
        m_tScale.fCurValue = m_tPosY.fStartValue;

        _vec3 vPos = m_pTransformCom->Get_Info(INFO::INFO_POS);
        CGameObject* pBullet = CFirework_Sub_Bullet::Create(m_pGraphicDev, vPos, vec3.forward, m_pOwner);
        NULL_CHECK_RETURN(pBullet, E_FAIL);
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Firework_Sub", pBullet);
        pBullet = CFirework_Sub_Bullet::Create(m_pGraphicDev, vPos, vec3.forward, m_pOwner);
        NULL_CHECK_RETURN(pBullet, E_FAIL);
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Firework_Sub", pBullet);
        pBullet = CFirework_Sub_Bullet::Create(m_pGraphicDev, vPos, vec3.forward + vec3.right, m_pOwner);
        NULL_CHECK_RETURN(pBullet, E_FAIL);
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Firework_Sub", pBullet);
        pBullet = CFirework_Sub_Bullet::Create(m_pGraphicDev, vPos, vec3.right, m_pOwner);
        NULL_CHECK_RETURN(pBullet, E_FAIL);
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Firework_Sub", pBullet);
        pBullet = CFirework_Sub_Bullet::Create(m_pGraphicDev, vPos, vec3.back + vec3.right, m_pOwner);
        NULL_CHECK_RETURN(pBullet, E_FAIL);
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Firework_Sub", pBullet);
        pBullet = CFirework_Sub_Bullet::Create(m_pGraphicDev, vPos, vec3.back, m_pOwner);
        NULL_CHECK_RETURN(pBullet, E_FAIL);
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Firework_Sub", pBullet);
        pBullet = CFirework_Sub_Bullet::Create(m_pGraphicDev, vPos, vec3.back + vec3.left, m_pOwner);
        NULL_CHECK_RETURN(pBullet, E_FAIL);
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Firework_Sub", pBullet);
        pBullet = CFirework_Sub_Bullet::Create(m_pGraphicDev, vPos, vec3.left, m_pOwner);
        NULL_CHECK_RETURN(pBullet, E_FAIL);
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Firework_Sub", pBullet);
        pBullet = CFirework_Sub_Bullet::Create(m_pGraphicDev, vPos, vec3.forward + vec3.left, m_pOwner);
        NULL_CHECK_RETURN(pBullet, E_FAIL);
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Firework_Sub", pBullet);

     
        m_bShrink = true;
    }

    if (m_tScale.bActive)
    {
        m_pTransformCom->Set_Scale(_vec3{ m_tScale.fCurValue, m_tScale.fCurValue , m_tScale.fCurValue });
    }
    else if (!m_tScale.bActive && m_bShrink)
    {
        CEventMgr::GetInstance()->Delete_Obj(this);
    }

  

    m_tPosY.Update_Lerp(fTimeDelta);
    m_tScale.Update_Lerp(fTimeDelta);

    return iExit;
}


void CFirework_Bullet::LateUpdate_Object()
{
    __super::LateUpdate_Object();
}


void CFirework_Bullet::Render_Object()
{
    //m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(m_iAlpha, 255, 255, 255));

    m_pTextureCom->Render_Texture(); // 텍스처 세팅 -> 버퍼 세팅 순서 꼭!

    m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

    m_pBufferCom->Render_Buffer();

    m_pGraphicDev->SetTexture(0, NULL);

    //m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));

    __super::Render_Object();
}

void CFirework_Bullet::OnCollision_Enter(CGameObject* _pColObj)
{

   /* CGameObject* pPlayer = dynamic_cast<CPlayer*>(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::PLAYER, L"Player"));


    switch (_pColObj->Get_Type())
    {
    case OBJ_TYPE::PLAYER:

        dynamic_cast<CPlayer*>(pPlayer)->Damaged(m_fDamage, this);
        CEventMgr::GetInstance()->Delete_Obj(this);
        break;
    default:
        break;
    }*/
}

void CFirework_Bullet::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CFirework_Bullet::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CFirework_Bullet::Add_Component()
{
    CComponent* pComponent;

    // Texture
    pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Projectile_GreenBullet", this));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

    // AI
    pComponent = m_pAICom = dynamic_cast<CAIComponent*>(Engine::Clone_Proto(COMPONENT_TYPE::AICOM, this));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_DYNAMIC].emplace(COMPONENT_TYPE::AICOM, pComponent);

    return S_OK;
}

CFirework_Bullet* CFirework_Bullet::Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos, CGameObject* pTarget, CGameObject* pOwner)
{
    CFirework_Bullet* pInstance = new CFirework_Bullet(pGraphicDev, _vPos, pTarget, pOwner);

    if (FAILED(pInstance->Ready_Object()))
    {
        Safe_Release(pInstance);

        MSG_BOX("Firework_Bullet Create Failed");
        return nullptr;
    }

    return pInstance;
}

void CFirework_Bullet::Free()
{
    __super::Free();
}
