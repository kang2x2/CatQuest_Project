#include "BlueStar_Bullet.h"
#include "Export_Function.h"
#include "Player.h"
#include "HitEffect_Blue.h"
#include "BoomEffect_Blue.h"
#include "SoundMgr.h"

CBlueStar_Bullet::CBlueStar_Bullet(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos, CGameObject* pTarget, CGameObject* pOwner)
    :CBasicProjectile(pGraphicDev, OBJ_ID::PROJECTILE_STAR_BULLET)
{
    m_vPos = _vPos;
    m_pTarget = pTarget;
    m_pOwner = pOwner;

    ZeroMemory(&m_tAlpha, sizeof(LERP_FLOAT_INFO));
}

CBlueStar_Bullet::CBlueStar_Bullet(const CProjectile& rhs)
    : CBasicProjectile(rhs)
{
}

CBlueStar_Bullet::~CBlueStar_Bullet()
{

}

HRESULT CBlueStar_Bullet::Ready_Object()
{
    __super::Ready_Object();
    FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

    
    m_pTransformCom->Set_Pos(m_vPos);
    m_pTransformCom->Set_Dir(_vec3{ 0.f, 0.f, 0.f });


    m_fSpeed = 20.f;

    m_vOriginPos = m_pTransformCom->Get_Info(INFO_POS);
    
    m_fDamage = 5.f;

    m_bInit = false;

    m_bChase = false;

    m_szName = L"Projectile_Star";


    m_bTargetChase = false;
    m_bBack = false;

    m_check1 = false;
    m_check2 = false;


    return S_OK;
 
}

_int CBlueStar_Bullet::Update_Object(const _float& fTimeDelta)
{

    _vec3 vTargetPos = m_pTarget->Get_Transform()->Get_Info(INFO_POS);
    _vec3 vBulletDir = vTargetPos - m_vPos;
    _vec3 vDir = -(vTargetPos - m_pTransformCom->Get_Info(INFO_POS));

    if (m_vOriginPos.x >= vTargetPos.x)
    {
        vDir.x - 40.f;
    }
    else
    {
        vDir.x + 40.f;
    }


    if (false == m_bInit)
    {
        m_bInit = true;
        m_tAlpha.Init_Lerp();
        m_tAlpha.Set_Lerp(0.5f, 0.f, 255.f);
    }

    if (false == m_bBack)
    {
        m_bBack = true;
        m_tPos.Init_Lerp();
        m_tPos.Set_Lerp(1.f, m_vPos, { m_vPos.x + vDir.x , m_vPos.y, m_vPos.z + vDir.z });
    }

    if (true == m_bTargetChase)
    {
        m_bTargetChase = false;
        m_tPos.Init_Lerp();
        m_tPos.Set_Lerp(1.f, m_pTransformCom->Get_Info(INFO_POS) , vTargetPos);
    }


    if (m_pOwner->Is_Active() == false)
    {
        CEventMgr::GetInstance()->Delete_Obj(this);
    }

    Engine::Add_RenderGroup(RENDER_ALPHA, this);
    _int iExit = __super::Update_Object(fTimeDelta);


    m_tAlpha.Update_Lerp(fTimeDelta);

    m_tPos.Update_Lerp(fTimeDelta);
    m_pTransformCom->Set_Pos(m_tPos.vCurVec);

    m_fAccTime += fTimeDelta;

 
    if (m_bBack == true && m_bTargetChase == false && m_check1 == false && m_fAccTime >= 1.f)
    {
        m_bTargetChase = true;
        m_check1 = true;
    }

    if (m_fAccTime >= 2.f)
    {
        CEventMgr::GetInstance()->Delete_Obj(this);
        CEventMgr::GetInstance()->Add_Obj(L"Bomm_BlueStar_Effect", CBoomEffect_Blue::Create(m_pGraphicDev, m_pTransformCom->Get_Info(INFO_POS)));
        CSoundMgr::GetInstance()->PlaySound(L"enemy_impact", CHANNEL_ID::MONSTER_HEDGEHOG, 0.7f);
    }

    // Lerp Before
    //m_pTransformCom->Set_Dir(vDir);
    //m_fAccTime += fTimeDelta;
    // 
    //if (m_vOriginPos.x >= vTargetPos.x)
    //{
    //    vDir.x - 40.f;
    //}
    //else
    //{
    //    vDir.x + 40.f;
    //}
    // 
    //if (m_fAccTime >= 1.f && m_bChase == false)
    //{
    //    m_fSpeed = 60.f;
    //    m_pTransformCom->Set_Dir(vBulletDir);
    //    //this->m_pAICom->Chase_TargetY(&vTargetPos, fTimeDelta, m_fSpeed);
    //    m_bChase == true;
    //}
    //if (m_fAccTime >= 3.f)
    //{
    //    CEventMgr::GetInstance()->Delete_Obj(this);
    //}
    //m_pTransformCom->Translate(fTimeDelta * m_fSpeed);


    return iExit;
}

void CBlueStar_Bullet::LateUpdate_Object()
{
    __super::LateUpdate_Object();
}

void CBlueStar_Bullet::Render_Object()
{
    m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(_int(m_tAlpha.fCurValue), 255, 255, 255));

    m_pTextureCom->Render_Texture(); // 텍스처 세팅 -> 버퍼 세팅 순서 꼭!

    m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

    m_pBufferCom->Render_Buffer();

    m_pGraphicDev->SetTexture(0, NULL);

    m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));

    __super::Render_Object();
}

void CBlueStar_Bullet::OnCollision_Enter(CGameObject* _pColObj)
{

    CGameObject* pPlayer = dynamic_cast<CPlayer*>(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::PLAYER, L"Player"));


    switch (_pColObj->Get_Type())
    {
    case OBJ_TYPE::PLAYER:

        dynamic_cast<CPlayer*>(pPlayer)->Damaged(m_fDamage, this);
        CEventMgr::GetInstance()->Add_Obj(L"Hit_Bluestar_Effect", CHitEffect_Blue::Create(m_pGraphicDev, m_pTransformCom->Get_Info(INFO_POS)));
        CSoundMgr::GetInstance()->PlaySound(L"enemy_impact2", CHANNEL_ID::MONSTER_HEDGEHOG, 1.f);
        CEventMgr::GetInstance()->Delete_Obj(this);
        break;
    default:
        break;
    }

}

void CBlueStar_Bullet::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CBlueStar_Bullet::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CBlueStar_Bullet::Add_Component()
{
    CComponent* pComponent;

    // Texture
    pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Projectile_BlueStar", this));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

    // AI
    pComponent = m_pAICom = dynamic_cast<CAIComponent*>(Engine::Clone_Proto(COMPONENT_TYPE::AICOM, this));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_DYNAMIC].emplace(COMPONENT_TYPE::AICOM, pComponent);

    return S_OK;
}

CBlueStar_Bullet* CBlueStar_Bullet::Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos, CGameObject* pTarget, CGameObject* pOwner)
{
    CBlueStar_Bullet* pInstance = new CBlueStar_Bullet(pGraphicDev, _vPos, pTarget, pOwner);

    if (FAILED(pInstance->Ready_Object()))
    {
        Safe_Release(pInstance);

        MSG_BOX("BlueStar Create Failed");
        return nullptr;
    }

    return pInstance;
}

void CBlueStar_Bullet::Free()
{
    __super::Free();
}
