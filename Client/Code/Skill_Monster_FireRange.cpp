#include "Skill_Monster_FireRange.h"
#include "Export_Function.h"

#include "Effect_Range_Quater.h"



CSkill_Monster_FireRange::CSkill_Monster_FireRange(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID)
    : CSkill(pGraphicDev, _eID)
{
}

CSkill_Monster_FireRange::CSkill_Monster_FireRange(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
    : CSkill(pGraphicDev, _pOwnerObject, OBJ_ID::SKILL_MONSTER_BASIC)
{
}

CSkill_Monster_FireRange::CSkill_Monster_FireRange(const CSkill_Monster_FireRange& rhs)
    : CSkill(rhs)
{
}

CSkill_Monster_FireRange::~CSkill_Monster_FireRange()
{
}

HRESULT CSkill_Monster_FireRange::Ready_Object()
{
    __super::Ready_Object();

    m_bActive = false;

    m_fSkillDamage = 0;

    m_pBaseRangeEffect = nullptr;

    FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

    return S_OK;
}

_int CSkill_Monster_FireRange::Update_Object(const _float& fTimeDelta)
{

    _int iExit = CSkill::Update_Object(fTimeDelta);
    if (!m_pOwnerObject->Is_Active())
    {
        CEventMgr::GetInstance()->Delete_Obj(m_pRangeEffect);
        CEventMgr::GetInstance()->Delete_Obj(m_pBaseRangeEffect);
        CEventMgr::GetInstance()->Delete_Obj(m_pSKillEffect);
        CEventMgr::GetInstance()->Delete_Obj(this);
        return iExit;
    }
    m_pTransformCom->Set_Pos(m_pOwnerObject->Get_Transform()->Get_Info(INFO::INFO_POS));

    Engine::Add_RenderGroup(RENDER_NONALPHA, this);

    return iExit;
}

void CSkill_Monster_FireRange::LateUpdate_Object()
{
    __super::LateUpdate_Object();
}

void CSkill_Monster_FireRange::Render_Object()
{
    __super::Render_Object();
}

HRESULT CSkill_Monster_FireRange::Add_Component()
{
    //CEffect_Range_Quater* pRangeEffect = CEffect_Range_Quater::Create(m_pGraphicDev, this, EFFECT_RANGE_QUATER_TYPE::CIRCLE_SKILL_RED);
    //NULL_CHECK_RETURN(pRangeEffect, E_FAIL);
    //FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Monster_Basic", pRangeEffect), E_FAIL);
    //m_pRangeEffect = pRangeEffect;

      // Effect Range Quater - Base
    m_pBaseRangeEffect = CEffect_Range_Quater::Create(m_pGraphicDev, this, EFFECT_RANGE_QUATER_TYPE::CIRCLE_SKILL_RED);
    NULL_CHECK_RETURN(m_pBaseRangeEffect, E_FAIL);
    FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Monster_Basic_Base", m_pBaseRangeEffect), E_FAIL);




    return S_OK;
}

HRESULT CSkill_Monster_FireRange::Play()
{
    _vec3 vOwnerPos = m_pOwnerObject->Get_Transform()->Get_Info(INFO::INFO_POS);
    OBJ_ID eObjID = m_pOwnerObject->Get_ID();


    m_pBaseRangeEffect->Play_Effect(_vec3{ vOwnerPos.x, 0.01f, vOwnerPos.z + 4 });
    m_pBaseRangeEffect->Alphaing(0.01f, 240.f, 240.f);
    m_pBaseRangeEffect->Scaling(0.01f, 1.f, 1.f);

    m_bActive = true;


    return S_OK;
}

HRESULT CSkill_Monster_FireRange::End()
{

    //m_pRangeEffect->Set_Active(false);
    m_pBaseRangeEffect->Set_Active(false);

    return S_OK;
}

CSkill_Monster_FireRange* CSkill_Monster_FireRange::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
{
    CSkill_Monster_FireRange* pInstance = new CSkill_Monster_FireRange(pGraphicDev, _pOwnerObject);

    if (FAILED(pInstance->Ready_Object()))
    {
        Safe_Release(pInstance);

        MSG_BOX("Skill_Monster_Basic Create Failed");
        return nullptr;
    }

    return pInstance;
}

void CSkill_Monster_FireRange::Free()
{
}
