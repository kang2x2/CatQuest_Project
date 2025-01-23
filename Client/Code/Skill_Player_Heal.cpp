#include "stdafx.h"
#include "Skill_Player_Heal.h"

#include "Export_Function.h"

#include "SphereCollider.h"
#include "RangeObj.h"
#include "GameObject.h"
#include "Player.h"
#include "HealEffect.h"

CSkill_Player_Heal::CSkill_Player_Heal(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID)
    : CSkill(pGraphicDev, _eID)
{
}

CSkill_Player_Heal::CSkill_Player_Heal(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
    : CSkill(pGraphicDev, _pOwnerObject, OBJ_ID::SKILL_PLAYER_HEAL)
{
}

CSkill_Player_Heal::CSkill_Player_Heal(const CSkill_Player_Heal& rhs)
    : CSkill(rhs)
{
}

CSkill_Player_Heal::~CSkill_Player_Heal()
{
}

HRESULT CSkill_Player_Heal::Ready_Object()
{
    CSkill::Ready_Object();

    //m_iSkillUsage = 2;
    //m_iLv = 0;

    m_bAttackStart = false;
    m_bActive = false;
    m_bIsHeal = false;

    FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

    m_pHeal = nullptr;

    return S_OK;
}

_int CSkill_Player_Heal::Update_Object(const _float& fTimeDelta)
{
    _int iExit = CSkill::Update_Object(fTimeDelta);

    NULL_CHECK_RETURN(m_pOwnerObject, E_FAIL);

    if (!m_pOwnerObject->Is_Active())
    {
        CEventMgr::GetInstance()->Delete_Obj(this);
        return iExit;
    }
    m_pTransformCom->Set_Pos(m_pOwnerObject->Get_Transform()->Get_Info(INFO::INFO_POS));


    if (!m_bIsHeal && m_pHeal != nullptr && static_cast<CHealEffect*>(m_pHeal)->Is_Heal())
    {
        NULL_CHECK_RETURN(m_pOwnerObject, E_FAIL);

        _float fHeal = 50.f;
        static_cast<CPlayer*>(m_pOwnerObject)->Regen_HP(fHeal + rand() % 10);
        m_bIsHeal = true;
    }


    return iExit;
}

void CSkill_Player_Heal::LateUpdate_Object()
{
    if (m_pHeal->Is_Active() == false)
    {
        m_bActive = false;
    }
  
    CSkill::LateUpdate_Object();
}

void CSkill_Player_Heal::Render_Object()
{
    CSkill::Render_Object();
}

HRESULT CSkill_Player_Heal::Add_Component()
{
    return S_OK;
}

HRESULT CSkill_Player_Heal::Play()
{
    m_pHeal = nullptr;
    m_bIsHeal = false;

    CGameObject* pHeal = CHealEffect::Create(m_pGraphicDev, this);
    NULL_CHECK_RETURN(pHeal, E_FAIL);
    FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Effect_Heal", pHeal), E_FAIL);
    m_pHeal = pHeal;

    m_bActive = true;

    return S_OK;
}

HRESULT CSkill_Player_Heal::End()
{
    return S_OK;
}

CSkill_Player_Heal* CSkill_Player_Heal::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
{
    CSkill_Player_Heal* pInstance = new CSkill_Player_Heal(pGraphicDev, _pOwnerObject);

    if (FAILED(pInstance->Ready_Object()))
    {
        Safe_Release(pInstance);

        MSG_BOX("Skill_Player_Heal Create Failed");
        return nullptr;
    }

    return pInstance;
}

void CSkill_Player_Heal::Free()
{
    __super::Free();
}
