#include "Chase_Bullet.h"
#include "Export_Function.h"
#include "EventMgr.h"
#include "Player.h"

CChase_Bullet::CChase_Bullet(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos, CGameObject* pTarget, CGameObject* pOwner)
    : CBasicProjectile(pGraphicDev, OBJ_ID::PROJECTILE_CHASE_BULLET)
{
    m_vPos = _vPos;
    m_pTarget = pTarget;
    m_pOwner = pOwner;
}

CChase_Bullet::CChase_Bullet(const CProjectile& rhs)
    : CBasicProjectile(rhs)
{
}

CChase_Bullet::~CChase_Bullet()
{
}

HRESULT CChase_Bullet::Ready_Object()
{
    __super::Ready_Object();
    FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
    
    
    m_pTransformCom->Set_Pos(m_vPos);
    m_pTransformCom->Set_Dir(m_vDir);
   
    m_pTransformCom->Set_Scale(_vec3{ 0.8f, 0.8f, 0.8f });

    m_fSpeed = 20.f;

    m_szName = L"Projectile_ChaseBullet";

    m_fDamage = 6.f + rand() % 3;

    m_iAlpha = 255;

    m_bDelete = false;

    return S_OK;
}

_int CChase_Bullet::Update_Object(const _float& fTimeDelta)
{
    Engine::Add_RenderGroup(RENDER_ALPHA, this);
    _int iExit = __super::Update_Object(fTimeDelta);

    m_fAccTime += fTimeDelta;

    if (m_fAccTime <= 2.f)
    {
        _vec3 vTargetPos = m_pTarget->Get_Transform()->Get_Info(INFO_POS);

        this->m_pAICom->Chase_TargetY(&vTargetPos, fTimeDelta, m_fSpeed);
    }
    else if(m_fAccTime >2.f && !m_bDelete)
    {
        m_tAlpha.Init_Lerp(LERP_MODE::EASE_IN);
        m_tAlpha.Set_Lerp(0.8f, m_iAlpha, 0);

        m_tSpeed.Init_Lerp(LERP_MODE::EASE_IN);
        m_tSpeed.Set_Lerp(0.8f, m_fSpeed, 0);

        m_bDelete = true;
    }

    m_tAlpha.Update_Lerp(fTimeDelta);
    m_tSpeed.Update_Lerp(fTimeDelta);

    if (m_bDelete)
    {
        m_iAlpha = m_tAlpha.fCurValue;
        m_fSpeed = m_tSpeed.fCurValue;
    }
    if (m_iAlpha <= 0)
    {
        CEventMgr::GetInstance()->Delete_Obj(this);
    }

   
   
    m_pTransformCom->Translate(fTimeDelta * m_fSpeed);

    
    return iExit;
}


void CChase_Bullet::LateUpdate_Object()
{
    __super::LateUpdate_Object();
}


void CChase_Bullet::Render_Object()
{
    m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(m_iAlpha, 255, 255, 255));

    m_pTextureCom->Render_Texture(); // 텍스처 세팅 -> 버퍼 세팅 순서 꼭!

    m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

    m_pBufferCom->Render_Buffer();

    m_pGraphicDev->SetTexture(0, NULL);

    m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));

    __super::Render_Object();
}

void CChase_Bullet::OnCollision_Enter(CGameObject* _pColObj)
{

    CGameObject* pPlayer = dynamic_cast<CPlayer*>(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::PLAYER, L"Player"));


    switch (_pColObj->Get_Type())
    {
    case OBJ_TYPE::PLAYER:

        dynamic_cast<CPlayer*>(pPlayer)->Damaged(m_fDamage, this);
        CEventMgr::GetInstance()->Delete_Obj(this);
        break;
    default:
        break;
    }
}

void CChase_Bullet::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CChase_Bullet::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CChase_Bullet::Add_Component()
{ 
    CComponent* pComponent;

    // Texture
    pComponent = m_pTextureCom  = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Projectile_RedBullet_Another", this));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

    // AI
    pComponent = m_pAICom = dynamic_cast<CAIComponent*>(Engine::Clone_Proto(COMPONENT_TYPE::AICOM, this));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_DYNAMIC].emplace(COMPONENT_TYPE::AICOM, pComponent);

    return S_OK;
}

CChase_Bullet* CChase_Bullet::Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos , CGameObject* pTarget, CGameObject* pOwner)
{
    CChase_Bullet* pInstance = new CChase_Bullet(pGraphicDev,_vPos, pTarget, pOwner);

    if (FAILED(pInstance->Ready_Object()))
    {
        Safe_Release(pInstance);

        MSG_BOX("ChaseBullet Create Failed");
        return nullptr;
    }

    return pInstance;
}

void CChase_Bullet::Free()
{
    __super::Free();
}
