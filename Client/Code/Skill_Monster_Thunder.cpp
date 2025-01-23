#include "Skill_Monster_Thunder.h"
#include "EventMgr.h"
#include "Export_Function.h"

#include "Effect_Thunder.h"
#include "Effect_Range_Quater.h"

#include "RangeObj.h"
#include "Player.h"

CSkill_Monster_Thunder::CSkill_Monster_Thunder(LPDIRECT3DDEVICE9 pGraphicDev)
    :CSkill(pGraphicDev, OBJ_ID::SKILL_MONSTER_THUNDER)
{
}

CSkill_Monster_Thunder::CSkill_Monster_Thunder(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
    :CSkill(pGraphicDev, _pOwnerObject , OBJ_ID::SKILL_MONSTER_THUNDER)
{
}

CSkill_Monster_Thunder::CSkill_Monster_Thunder(const CSkill_Monster_Thunder& rhs)
    :CSkill(rhs)
{
}

CSkill_Monster_Thunder::~CSkill_Monster_Thunder()
{
}

HRESULT CSkill_Monster_Thunder::Ready_Object()
{
    __super::Ready_Object();


    m_bActive = false;

    m_fSkillDamage = 10.f;


    m_pBaseRangeEffect = nullptr;
   

    // Naming
    m_szName = L"Skill_Monster_Thunder";

    FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

    return S_OK;
}

_int CSkill_Monster_Thunder::Update_Object(const _float& fTimeDelta)
{
    _int iExit = __super::Update_Object(fTimeDelta);
    Engine::Add_RenderGroup(RENDER_ALPHA, this);


    // Dead condition
    if (!m_pOwnerObject->Is_Active())
    {
    
        m_pRangeEffect->Set_Active(false);
        End();
        
        CEventMgr::GetInstance()->Delete_Obj(m_pBaseRangeEffect);
        CEventMgr::GetInstance()->Delete_Obj(m_pRangeEffect);
        CEventMgr::GetInstance()->Delete_Obj(m_pSKillEffect);
        CEventMgr::GetInstance()->Delete_Obj(this);
        return iExit;
    }


    // Pos Setting
    _vec3 vPos = m_pOwnerObject->Get_Transform()->Get_Info(INFO_POS);
    m_pTransformCom->Set_Pos(vPos);

  

    // Skill Play Control
    if (!m_pSKillEffect->Is_Active())
    {
        End();
        m_bActive = false;
    }


    return iExit;
}

void CSkill_Monster_Thunder::LateUpdate_Object()
{
    __super::LateUpdate_Object();
}

void CSkill_Monster_Thunder::Render_Object()
{
    __super::Render_Object();
}

void CSkill_Monster_Thunder::OnCollision_Enter(CGameObject* _pColObj)
{
    switch (_pColObj->Get_Type())
    {
    case Engine::OBJ_TYPE::PLAYER:
    {
        CGameObject* pPlayer = dynamic_cast<CPlayer*>(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::PLAYER, L"Player"));
        dynamic_cast<CPlayer*>(pPlayer)->Damaged(m_fSkillDamage, this);
    }
    break;
    default:
    {
    }
    break;
    }

}

void CSkill_Monster_Thunder::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CSkill_Monster_Thunder::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CSkill_Monster_Thunder::Add_Component()
{
    // Skill Effect
    CSkillEffect* pThunderEffect = CEffect_Thunder::Create(m_pGraphicDev, this);
    NULL_CHECK_RETURN(pThunderEffect, E_FAIL);
    FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Monster_ThunderSkill_Effect", pThunderEffect), E_FAIL);
    m_pSKillEffect = pThunderEffect;

    // Effect Range Quater
    CEffect_Range_Quater* pRangeEffect = CEffect_Range_Quater::Create(m_pGraphicDev, this, EFFECT_RANGE_QUATER_TYPE::ARROW_RED);
    NULL_CHECK_RETURN(pRangeEffect, E_FAIL);
    FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Monster_ThunderSkill_Arrow", pRangeEffect), E_FAIL);
    m_pRangeEffect = pRangeEffect;

    // Effect Range Quater
    CEffect_Range_Quater* pRangeEffect2 = CEffect_Range_Quater::Create(m_pGraphicDev, this, EFFECT_RANGE_QUATER_TYPE::ARROW_BLUE);
    NULL_CHECK_RETURN(pRangeEffect2, E_FAIL);
    FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Monster_ThunderSkill_Arrow", pRangeEffect2), E_FAIL);
    m_pBaseRangeEffect = pRangeEffect2;




    //  Sklil range Obj
    CRangeObj* pGameObject = CRangeObj::Create(m_pGraphicDev, this, 5.f);
    CSphereCollider* pShpere = dynamic_cast<CSphereCollider*>(pGameObject->Get_Component(COMPONENT_TYPE::COL_SPHERE, ID_STATIC));
    pShpere->Set_Radius(15.f);
    NULL_CHECK_RETURN(pGameObject, E_FAIL);
    CEventMgr::GetInstance()->Add_Obj(L"Monster_Thunder_Sphere", pGameObject);
    m_pRangeObj = pGameObject;






    return S_OK;
}

HRESULT CSkill_Monster_Thunder::Play()
{

    _vec3 vOwnerPos = m_pOwnerObject->Get_Transform()->Get_Info(INFO::INFO_POS);
    OBJ_ID eObjID = m_pOwnerObject->Get_ID();

    m_pRangeEffect->Play_Effect(_vec3{ vOwnerPos.x, 0.01f, vOwnerPos.z });
    m_pRangeEffect->Alphaing(1.f, 240.f, 0.f);
    m_pRangeEffect->Scaling(0.01f, 1.f, 1.f);

    m_bActive = false;

    return S_OK;
}

HRESULT CSkill_Monster_Thunder::LatePlay()
{

    _vec3 vOwnerPos = m_pOwnerObject->Get_Transform()->Get_Info(INFO::INFO_POS);
    OBJ_ID eObjID = m_pOwnerObject->Get_ID();
   

    m_pRangeEffect->Set_Active(false);

    m_bActive = true;


    m_pRangeObj->Set_Active(true);

    m_pBaseRangeEffect->Play_Effect(_vec3{ vOwnerPos.x , 0.01f, vOwnerPos.z });
    m_pBaseRangeEffect->Alphaing(0.5f, 240.f, 0.f);

    m_pSKillEffect->Play_Effect(_vec3{ vOwnerPos.x, 0.01f, vOwnerPos.z });


    return S_OK;
}

HRESULT CSkill_Monster_Thunder::End()
{   

    m_pRangeEffect->Set_Active(false);
    m_pSKillEffect->Set_Active(false);
    m_pRangeObj->Set_Active(false);
    m_bActive = false;
    m_bAttack = false;
     

    return S_OK;
}

CSkill_Monster_Thunder* CSkill_Monster_Thunder::Create(LPDIRECT3DDEVICE9 pGraphicDev , CGameObject* _pOwnerObject)
{
    CSkill_Monster_Thunder* pInstance = new CSkill_Monster_Thunder(pGraphicDev, _pOwnerObject);

    if (FAILED(pInstance->Ready_Object()))
    {
        Safe_Release(pInstance);

        MSG_BOX("CSkill_Monster_Thunder Create Failed");
        return nullptr;
    }

    return pInstance;
}


void CSkill_Monster_Thunder::Free()
{
    __super::Free();
}
