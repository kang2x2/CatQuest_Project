#include "Pile_Bullet.h"
#include "Export_Function.h"
#include "EventMgr.h"
#include "Player.h"

CPile_Bullet::CPile_Bullet(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos, CGameObject* pTarget, CGameObject* pOwner)
    : CBasicProjectile(pGraphicDev, OBJ_ID::PROJECTILE_PILE_BULLET)
{
    m_vPos = _vPos;
    m_pTarget = pTarget;
    m_pOwner = pOwner;
}

CPile_Bullet::CPile_Bullet(const CProjectile& rhs)
    : CBasicProjectile(rhs)
{
}

CPile_Bullet::~CPile_Bullet()
{
}

HRESULT CPile_Bullet::Ready_Object()
{
    __super::Ready_Object();
    FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

    m_pTransformCom->Set_Scale(_vec3{ 2.f, 1.f, 1.f });

    m_fSpeed = 100.f;

    m_szName = L"Projectile_FireWork_Sub_Bullet";

    m_fDamage = 30.f + rand() % 5;

    m_bDelete = false;

    m_fLength = 0.f;

    m_iAlpha = 0;

    m_tAlpha.Init_Lerp(LERP_MODE::EXPONENTIAL);
    m_tAlpha.Set_Lerp(3.5f, 0, 255);

    return S_OK;
}

_int CPile_Bullet::Update_Object(const _float& fTimeDelta)
{
    Engine::Add_RenderGroup(RENDER_ALPHA, this);
    _int iExit = __super::Update_Object(fTimeDelta);

    if (!m_pOwner->Is_Active())
        CEventMgr::GetInstance()->Delete_Obj(this);

    m_tAlpha.Update_Lerp(fTimeDelta);

    if (m_tAlpha.bActive)
    {
        m_iAlpha = m_tAlpha.fCurValue;

        _vec3 vDir = m_pTarget->Get_Transform()->Get_Info(INFO::INFO_POS) - m_pOwner->Get_Transform()->Get_Info(INFO::INFO_POS);
        D3DXVec3Normalize(&vDir, &vDir);
        _vec3 vPilePos = m_pOwner->Get_Transform()->Get_Info(INFO::INFO_POS) + (vDir * 5.f);
        m_pTransformCom->Set_Dir(vDir);

        _vec3		vAxis = *D3DXVec3Cross(&vAxis, &vec3.right, &vDir);
        _float		fDot = D3DXVec3Dot(&vec3.right, &vDir);
        _float		fAngle = acosf(fDot);

        if (vDir.z > 0)
            fAngle *= -1;

        m_pTransformCom->Set_Rot(_vec3{ 0.f, fAngle, 0.f });

        m_pTransformCom->Set_Pos(vPilePos);


    }
    else
    {
        m_pTransformCom->Translate(fTimeDelta * m_fSpeed);
    }

    _vec3 vDir = m_pOwner->Get_Transform()->Get_Info(INFO::INFO_POS) - m_pTransformCom->Get_Info(INFO::INFO_POS);
    _float fLength = D3DXVec3Length(&vDir);
    if (fLength >= 100)
        CEventMgr::GetInstance()->Delete_Obj(this);


    return iExit;
}


void CPile_Bullet::LateUpdate_Object()
{

    __super::LateUpdate_Object();

       if (!m_pOwner->Is_Active())
        CEventMgr::GetInstance()->Delete_Obj(this);
}


void CPile_Bullet::Render_Object()
{
    if (!m_pOwner->Is_Active())
        CEventMgr::GetInstance()->Delete_Obj(this);
    m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(m_iAlpha, 255, 255, 255));

    _matrix matWorld = m_pTransformCom->Get_WorldMat();
    _matrix matBill;
    _vec3 vPos;

    memcpy(&vPos, &matWorld.m[3], sizeof(_vec3));

    matWorld *= *D3DXMatrixInverse(&matBill, NULL, &CCameraMgr::GetInstance()->Get_Billboard_X());
    memcpy(&matWorld.m[3], &vPos, sizeof(_vec3));

    m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);

    m_pTextureCom->Render_Texture();
    m_pCrossBuffer->Render_Buffer();

    m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));

    __super::Render_Object();
}

void CPile_Bullet::OnCollision_Enter(CGameObject* _pColObj)
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

void CPile_Bullet::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CPile_Bullet::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CPile_Bullet::Add_Component()
{
    CComponent* pComponent;

    // Texture
    pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Projectile_Pile", this));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

    // AI
    pComponent = m_pAICom = dynamic_cast<CAIComponent*>(Engine::Clone_Proto(COMPONENT_TYPE::AICOM, this));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_DYNAMIC].emplace(COMPONENT_TYPE::AICOM, pComponent);

    pComponent = m_pCrossBuffer = dynamic_cast<CTerrainRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_TERRAIN_RC_TEX, this));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_TERRAIN_RC_TEX, pComponent);

    return S_OK;
}

CPile_Bullet* CPile_Bullet::Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos, CGameObject* pTarget, CGameObject* pOwner)
{
    CPile_Bullet* pInstance = new CPile_Bullet(pGraphicDev, _vPos, pTarget, pOwner);

    if (FAILED(pInstance->Ready_Object()))
    {
        Safe_Release(pInstance);

        MSG_BOX("Pile_Bullet Create Failed");
        return nullptr;
    }

    return pInstance;
}

void CPile_Bullet::Free()
{
    __super::Free();
}
