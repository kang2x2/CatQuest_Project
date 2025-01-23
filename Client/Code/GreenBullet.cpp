#include "GreenBullet.h"
#include "Export_Function.h"
#include "Player.h"


CGreenBullet::CGreenBullet(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos, _vec3 _vDir, CGameObject* pOwner)
    : CBasicProjectile(pGraphicDev , OBJ_ID::PROJECTILE_GREEN_BULLET)
{
    m_vPos = _vPos;
    m_vDir = _vDir;
    m_pOwner = pOwner;
     

    ZeroMemory(&m_tAlpha, sizeof(LERP_FLOAT_INFO));
}

CGreenBullet::CGreenBullet(const CProjectile& rhs)
    : CBasicProjectile(rhs)
{
}

CGreenBullet::~CGreenBullet()
{
}

HRESULT CGreenBullet::Ready_Object()
{
    __super::Ready_Object();
    FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
    
    
    m_pTransformCom->Set_Pos(m_vPos);
    m_pTransformCom->Set_Dir(m_vDir);


    // Lerp
    m_bInit = false;
    m_bEnd = false;

    m_Check = false;

    m_fDamage = 5.f;

    m_fSpeed = 20.f;

    m_szName = L"Projectile_FoxFire";

    return S_OK;
}

_int CGreenBullet::Update_Object(const _float& fTimeDelta)
{
    if (false == m_bInit)
    {
        m_tAlpha.Init_Lerp();
        m_tAlpha.eMode = LERP_MODE::EXPONENTIAL;
        m_tAlpha.Set_Lerp(0.3f, 80.f, 255.f);
        m_bInit = true;
    }
    if (true == m_bEnd)
    {
        m_tAlpha.Init_Lerp();
        m_tAlpha.eMode = LERP_MODE::EXPONENTIAL;
        m_tAlpha.Set_Lerp(1.f, 255.f, 0.f);
        m_bEnd = false;
    }

    if (m_pOwner->Is_Active() == false)
    {
        CEventMgr::GetInstance()->Delete_Obj(this);
    }

    Engine::Add_RenderGroup(RENDER_ALPHA, this);
    _int iExit = __super::Update_Object(fTimeDelta);


    m_tAlpha.Update_Lerp(fTimeDelta);

    
   
    m_pTransformCom->Translate(fTimeDelta * m_fSpeed);

    m_fAccTime += fTimeDelta;

    if (m_vDir == _vec3{ 0.f, 0.f, 0.f })
    {
        m_vDir = _vec3{ 0.f, 0.f, -1.f };
    }

    if (false == m_bEnd && m_fAccTime >= 1.5f && m_Check == false)
    {
        m_bEnd = true;
        m_Check = true;
    }

    if (m_fAccTime >= 2.5f)
    {

        CEventMgr::GetInstance()->Delete_Obj(this);
    
    }



    return iExit;
}


void CGreenBullet::LateUpdate_Object()
{
    __super::LateUpdate_Object();
}


void CGreenBullet::Render_Object()
{
    m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(_int(m_tAlpha.fCurValue), 255, 255, 255));

    m_pTextureCom->Render_Texture(); // 텍스처 세팅 -> 버퍼 세팅 순서 꼭!

    m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

    m_pBufferCom->Render_Buffer();

    m_pGraphicDev->SetTexture(0, NULL);
    m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));

    __super::Render_Object();
}

void CGreenBullet::OnCollision_Enter(CGameObject* _pColObj)
{
    CGameObject* pPlayer = dynamic_cast<CPlayer*>(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::PLAYER, L"Player"));
  

    switch (_pColObj->Get_Type())
    {
    case OBJ_TYPE::PLAYER:

        dynamic_cast<CPlayer*>(pPlayer)->Damaged(m_fDamage, m_pOwner);
        CEventMgr::GetInstance()->Delete_Obj(this);
        break;
    default:
        break;
    }


}

void CGreenBullet::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CGreenBullet::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CGreenBullet::Add_Component()
{
    CComponent* pComponent;

    // Texture
    pComponent = m_pTextureCom  = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Projectile_RedBullet", this));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

    return S_OK;
}

CGreenBullet* CGreenBullet::Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos , _vec3 _vDir, CGameObject* pOwner)
{
    CGreenBullet* pInstance = new CGreenBullet(pGraphicDev,_vPos, _vDir, pOwner);

    if (FAILED(pInstance->Ready_Object()))
    {
        Safe_Release(pInstance);

        MSG_BOX("Green Bullet Create Failed");
        return nullptr;
    }

    return pInstance;
}

void CGreenBullet::Free()
{
    __super::Free();
}
