#include "ComeBack_Bullet.h"
#include "Export_Function.h"
#include "EventMgr.h"
#include "Player.h"
#include "SoundMgr.h"
#include "HitEffect_Purple.h"
#include "BoomEffect_Purple.h"


CComBack_Bullet::CComBack_Bullet(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos, CGameObject* pTarget, CGameObject* pOwner, _float fCombackTime)
	: CBossProjectile(pGraphicDev, OBJ_ID::PROJECTILE_BOSS_CONVERGING)
{

	m_vPos = _vPos;
	m_pTarget = pTarget;
	m_pOwner = pOwner;

    m_fChaseTime = fCombackTime;

    ZeroMemory(&m_tAlpha, sizeof(LERP_FLOAT_INFO));
}

CComBack_Bullet::CComBack_Bullet(const CProjectile& rhs)
	: CBossProjectile(rhs)
{
}

CComBack_Bullet::~CComBack_Bullet()
{
}

HRESULT CComBack_Bullet::Ready_Object()
{
	__super::Ready_Object();
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);


	m_pTransformCom->Set_Pos(m_vPos);
	//m_pTransformCom->Set_Dir(m_vDir);

    m_vOriginPos = m_pTransformCom->Get_Info(INFO_POS);
    m_bComeBack = false;
    m_bStop = false;
    m_fDamage = 10.f;


	m_fSpeed = 5.f;
    m_fAccTime = 0.f;
	m_szName = L"Projectile_Boss_ComeBack_Bullet";


    m_bInit = false;

    m_check1 = false;
    m_check2 = false;
    m_check3 = false;
    m_check4 = false;
    m_check5 = false;

    m_bFirstStop = false;
    m_bSecondStop = false;
    m_bSpread = false;
    m_bCollect = false;
 

    m_bDown = false;
    m_bUp = false;


	return S_OK;
}

_int CComBack_Bullet::Update_Object(const _float& fTimeDelta)
{
    _vec3 vTargetPos = m_pTarget->Get_Transform()->Get_Info(INFO_POS);
    _vec3 vDir = -(vTargetPos - m_pTransformCom->Get_Info(INFO_POS));  // 타겟과의 방향 반대
    _vec3 vOwnerPos = m_pOwner->Get_Transform()->Get_Info(INFO_POS);
    _vec3 vOwnerDir = -(vOwnerPos - m_pTransformCom->Get_Info(INFO_POS)); // 주인과의 방향 반대 
    vOwnerDir = { vOwnerDir.x, 0.f, vOwnerDir.z }; // Y값 제거
    _vec3 vOriginDir = m_vOriginPos - m_pTransformCom->Get_Info(INFO_POS);
    _float fDistanceOrigin = D3DXVec3Length(&vOriginDir);


    if (false == m_bInit)
    {
        m_bInit = true;
        m_tAlpha.Init_Lerp();
        m_tAlpha.eMode = LERP_MODE::EXPONENTIAL;
        m_tAlpha.Set_Lerp(0.5f, 0.f, 255.f );
    }
    
    if (false == m_bFirstStop)
    {
        m_bFirstStop = true;
        m_tPos.Init_Lerp();
        m_tPos.Set_Lerp(0.1f, m_vPos, m_vPos);
    }
    if (true == m_bSpread)
    {
        m_bSpread = false;
        m_tPos.Init_Lerp();
        m_tPos.Set_Lerp(0.3f, m_vPos, _vec3{ m_vPos.x + 2*(vOwnerDir.x)  , m_vPos.y , m_vPos.z + 2*(vOwnerDir.z) });
    }
    if (true == m_bSecondStop)
    {
        m_bSecondStop = false;
        m_tPos.Init_Lerp();
        m_tPos.Set_Lerp( 0.1f, m_pTransformCom->Get_Info(INFO_POS), _vec3{ m_pTransformCom->Get_Info(INFO_POS).x ,
                                                                           m_pTransformCom->Get_Info(INFO_POS).y + 1.f , 
                                                                           m_pTransformCom->Get_Info(INFO_POS).z });                 
   
    }

    if (true == m_bDown)
    {
        m_bDown = false;
        m_tPos.Init_Lerp();
        m_tPos.Set_Lerp(0.1f, m_pTransformCom->Get_Info(INFO_POS), _vec3{ m_pTransformCom->Get_Info(INFO_POS).x ,
                                                                           m_pTransformCom->Get_Info(INFO_POS).y - 1.f ,
                                                                           m_pTransformCom->Get_Info(INFO_POS).z });

    }
    if (true == m_bUp)
    {
        m_bUp = false;
        m_tPos.Init_Lerp();
        m_tPos.Set_Lerp(0.1f, m_pTransformCom->Get_Info(INFO_POS), _vec3{ m_pTransformCom->Get_Info(INFO_POS).x ,
                                                                           m_pTransformCom->Get_Info(INFO_POS).y + 1.f ,
                                                                           m_pTransformCom->Get_Info(INFO_POS).z });


    }

    if (true == m_bCollect)
    {
        m_bCollect = false;
        m_tPos.Init_Lerp();
        m_tPos.Set_Lerp(0.2f, m_pTransformCom->Get_Info(INFO_POS), m_vOriginPos);
    }




    if (m_pOwner->Is_Active() == false)
    {
        CEventMgr::GetInstance()->Delete_Obj(this);
    }


    Engine::Add_RenderGroup(RENDER_ALPHA, this);
    _int iExit = __super::Update_Object(fTimeDelta);

  

    m_fAccTime += fTimeDelta;

    m_tAlpha.Update_Lerp(fTimeDelta);
    m_tPos.Update_Lerp(fTimeDelta);
    m_pTransformCom->Set_Pos(m_tPos.vCurVec);


    if (m_bSpread == false && m_check1 == false && m_fAccTime >= 1.f)
    {
        m_bSpread = true;
        m_check1 = true;
    }
    if (m_bSecondStop == false && m_check2 == false && m_fAccTime >= 1.3f)
    {
        m_bSecondStop = true;
        m_check2 = true;
    }
    if (m_bDown == false && m_check3 == false && m_fAccTime >= 1.6f)
    {
        m_bDown = true;
        m_check3 = true;

    }
    if (m_bUp == false && m_check4 == false && m_fAccTime >= 1.9f)
    {
        m_bUp = true;
        m_check4 = true;
    }

    if (m_bCollect == false && m_check5 == false && m_fAccTime >= m_fChaseTime)
    {
        m_bCollect = true;
        m_check5 = true;
    }
    if (( m_check5 == true  &&  fDistanceOrigin <= 1.f ) ||  m_fAccTime >= 5.f)
    {
        m_fAccTime = 0.f;
        CEventMgr::GetInstance()->Delete_Obj(this);
        CEventMgr::GetInstance()->Add_Obj(L"Bomm_ComeBackBullet_Effect", CBoomEffect_Purple::Create(m_pGraphicDev, m_pTransformCom->Get_Info(INFO_POS)));
        CSoundMgr::GetInstance()->PlaySound(L"enemy_impact", CHANNEL_ID::MONSTER_HEDGEHOG, 0.7f);
    }
  

 #pragma region Before Lerp

    //if (m_fAccTime < 1.f)
    //{
    //    m_pTransformCom->Set_Dir(vec3.zero);
    //}

    //if (m_bComeBack == false && m_bStop == false && m_fAccTime >= 1.f)
    //{
    //    m_fSpeed = 40.f;
    //    m_pTransformCom->Set_Dir(vOwnerDir);
    //    m_bStop = true;
    //    m_pTransformCom->Translate(fTimeDelta * m_fSpeed);

    //}
    //if (m_bComeBack == false && m_bStop == true && m_fAccTime >= 2.f)
    //{
    //    m_fSpeed = 0.f;
    //    m_bComeBack = true;
    //    // m_pTransformCom->Translate(fTimeDelta * m_fSpeed);
    //}

    //if (m_bComeBack == true && m_bStop == true && m_fAccTime >= m_fChaseTime)
    //{
    //    m_fSpeed = 40.f;
    //    CSoundMgr::GetInstance()->PlaySound(L"BulletSound1", CHANNEL_ID::MONSTER_BOSS_1, SOUND_VOLUME_MONSKILL_THUNDER);
    //    //m_pTransformCom->Set_Dir(vec3.zero);
    //    this->m_pAICom->Chase_TargetY(&m_vOriginPos, fTimeDelta, m_fSpeed);
    //}

    //if (m_bComeBack == true && m_bStop == true && fDistanceOrigin <= 1.f || m_fAccTime >= 6.f)
    //{
    //    m_fAccTime = 0.f;
    //    CEventMgr::GetInstance()->Delete_Obj(this);
    //    m_pTransformCom->Translate(fTimeDelta * m_fSpeed);
    //}
    //m_pTransformCom->Translate(fTimeDelta * m_fSpeed);

#pragma endregion



  

    return iExit;
}

void CComBack_Bullet::LateUpdate_Object()
{
    __super::LateUpdate_Object();
}

void CComBack_Bullet::Render_Object()
{
    m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(_int(m_tAlpha.fCurValue), 255, 255, 255));

    m_pTextureCom->Render_Texture(); // 텍스처 세팅 -> 버퍼 세팅 순서 꼭!

    m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

    m_pBufferCom->Render_Buffer();

    m_pGraphicDev->SetTexture(0, NULL);

    m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));

    __super::Render_Object();
}

void CComBack_Bullet::Comeback(const _float& fTimeDelta)
{
    this->m_pAICom->Chase_TargetY(&m_vOriginPos, fTimeDelta, m_fSpeed);
}

void CComBack_Bullet::OnCollision_Enter(CGameObject* _pColObj)
{

    CGameObject* pPlayer = dynamic_cast<CPlayer*>(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::PLAYER, L"Player"));


    switch (_pColObj->Get_Type())
    {
    case OBJ_TYPE::PLAYER:

        dynamic_cast<CPlayer*>(pPlayer)->Damaged(m_fDamage, this);
        CEventMgr::GetInstance()->Add_Obj(L"Hit_ComeBackBullet_Effect", CHitEffect_Purple::Create(m_pGraphicDev, m_pTransformCom->Get_Info(INFO_POS)));
        CSoundMgr::GetInstance()->PlaySound(L"enemy_impact2", CHANNEL_ID::MONSTER_HEDGEHOG, 1.f);
        //CEventMgr::GetInstance()->Delete_Obj(this);
        break;
    default:
        break;
    }

}

void CComBack_Bullet::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CComBack_Bullet::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CComBack_Bullet::Add_Component()
{
    CComponent* pComponent;

    // Texture
    pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Projectile_PupleBullet", this));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

    // AI
    pComponent = m_pAICom = dynamic_cast<CAIComponent*>(Engine::Clone_Proto(COMPONENT_TYPE::AICOM, this));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_DYNAMIC].emplace(COMPONENT_TYPE::AICOM, pComponent);

    return S_OK;
}


CComBack_Bullet* CComBack_Bullet::Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos, CGameObject* pTarget, CGameObject* pOwner, _float fCombackTime)
{
    CComBack_Bullet* pInstance = new CComBack_Bullet(pGraphicDev, _vPos, pTarget, pOwner, fCombackTime);

    if (FAILED(pInstance->Ready_Object()))
    {
        Safe_Release(pInstance);

        MSG_BOX("Converging_Bullet Create Failed");
        return nullptr;
    }

    return pInstance;
}

void CComBack_Bullet::Free()
{
    __super::Free();
}
