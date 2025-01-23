#include "Firework_Sub_Bullet.h"
#include "Export_Function.h"
#include "EventMgr.h"
#include "Player.h"

CFirework_Sub_Bullet::CFirework_Sub_Bullet(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos, _vec3 _vDir, CGameObject* pOwner)
    : CBasicProjectile(pGraphicDev, OBJ_ID::PROJECTILE_FIREWORK_SUB_BULLET)
{
    m_vPos = _vPos;
    m_vDir = _vDir;
    m_pOwner = pOwner;
}

CFirework_Sub_Bullet::CFirework_Sub_Bullet(const CProjectile& rhs)
    : CBasicProjectile(rhs)
{
}

CFirework_Sub_Bullet::~CFirework_Sub_Bullet()
{
}

HRESULT CFirework_Sub_Bullet::Ready_Object()
{
    __super::Ready_Object();
    FAILED_CHECK_RETURN(Add_Component(), E_FAIL);


    m_pTransformCom->Set_Pos(m_vPos);
    m_pTransformCom->Set_Dir(m_vDir);
    m_pTransformCom->Set_Scale(_vec3{ 0.9f, 0.9f, 0.9f });

    m_fSpeed = 25.f;

    m_szName = L"Projectile_FireWork_Sub_Bullet";

    m_fDamage = 10.f + rand() % 3;

    m_bDelete = false;

    m_fLength = 0.f;

    return S_OK;
}

_int CFirework_Sub_Bullet::Update_Object(const _float& fTimeDelta)
{
    Engine::Add_RenderGroup(RENDER_ALPHA, this);
    _int iExit = __super::Update_Object(fTimeDelta);

    if (m_fLength >= 20)
        CEventMgr::GetInstance()->Delete_Obj(this);

    m_pTransformCom->Translate(fTimeDelta * m_fSpeed);

    return iExit;
}


void CFirework_Sub_Bullet::LateUpdate_Object()
{
    _vec3 vDir = m_vPos - m_pTransformCom->Get_Info(INFO::INFO_POS);
    m_fLength = D3DXVec3Length(&vDir);

    __super::LateUpdate_Object();
}


void CFirework_Sub_Bullet::Render_Object()
{
    //m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(m_iAlpha, 255, 255, 255));

    m_pTextureCom->Render_Texture(); // 텍스처 세팅 -> 버퍼 세팅 순서 꼭!

    m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

    m_pBufferCom->Render_Buffer();

    m_pGraphicDev->SetTexture(0, NULL);

    //m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));

    __super::Render_Object();
}

void CFirework_Sub_Bullet::OnCollision_Enter(CGameObject* _pColObj)
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

void CFirework_Sub_Bullet::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CFirework_Sub_Bullet::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CFirework_Sub_Bullet::Add_Component()
{
    CComponent* pComponent;

    // Texture
    pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Projectile_StarBullet_Another", this));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

    // AI
    pComponent = m_pAICom = dynamic_cast<CAIComponent*>(Engine::Clone_Proto(COMPONENT_TYPE::AICOM, this));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_DYNAMIC].emplace(COMPONENT_TYPE::AICOM, pComponent);

    return S_OK;
}

CFirework_Sub_Bullet* CFirework_Sub_Bullet::Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos, _vec3 _vDir, CGameObject* pOwner)
{
    CFirework_Sub_Bullet* pInstance = new CFirework_Sub_Bullet(pGraphicDev, _vPos, _vDir, pOwner);

    if (FAILED(pInstance->Ready_Object()))
    {
        Safe_Release(pInstance);

        MSG_BOX("Firework_Sub_Bullet Create Failed");
        return nullptr;
    }

    return pInstance;
}

void CFirework_Sub_Bullet::Free()
{
    __super::Free();
}
