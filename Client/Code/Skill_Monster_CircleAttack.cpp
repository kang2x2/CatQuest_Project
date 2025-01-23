#include "Skill_Monster_CircleAttack.h"
#include "Export_Function.h"

#include "Effect_Range_Quater.h"
#include "Player.h"


CSkill_Monster_CircleAttack::CSkill_Monster_CircleAttack(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID)
    : CSkill(pGraphicDev, _eID)
{
}

CSkill_Monster_CircleAttack::CSkill_Monster_CircleAttack(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
    :CSkill(pGraphicDev, _pOwnerObject, OBJ_ID::SKILL_MONSTER_BASIC)
{
}

CSkill_Monster_CircleAttack::CSkill_Monster_CircleAttack(const CSkill_Monster_CircleAttack& rhs)
    :CSkill(rhs)
{
}

CSkill_Monster_CircleAttack::~CSkill_Monster_CircleAttack()
{
}

HRESULT CSkill_Monster_CircleAttack::Ready_Object()
{
    __super::Ready_Object();

    m_bActive = false;

    m_fSkillDamage = 10;

    m_pBaseRangeEffect = nullptr;

    FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

    return S_OK;
}

_int CSkill_Monster_CircleAttack::Update_Object(const _float& fTimeDelta)
{

    _int iExit = CSkill::Update_Object(fTimeDelta);
    if (!m_pOwnerObject->Is_Active())
    {
        End();
        CEventMgr::GetInstance()->Delete_Obj(m_pRangeEffect);
        CEventMgr::GetInstance()->Delete_Obj(m_pBaseRangeEffect);
        //CEventMgr::GetInstance()->Delete_Obj(m_pSKillEffect);
        CEventMgr::GetInstance()->Delete_Obj(this);
       
    }
    m_pTransformCom->Set_Pos(m_pOwnerObject->Get_Transform()->Get_Info(INFO::INFO_POS));


    //m_pRangeObj->Update_Object(fTimeDelta);

    Engine::Add_RenderGroup(RENDER_NONALPHA, this);

    
  

    return iExit;
}

void CSkill_Monster_CircleAttack::LateUpdate_Object()
{

    if (m_bActive)
    {
        m_bActive = false;
    }

    __super::LateUpdate_Object();
}

void CSkill_Monster_CircleAttack::Render_Object()
{
    __super::Render_Object();
}

void CSkill_Monster_CircleAttack::OnCollision_Enter(CGameObject* _pColObj)
{

}

void CSkill_Monster_CircleAttack::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CSkill_Monster_CircleAttack::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CSkill_Monster_CircleAttack::Add_Component()
{
    CEffect_Range_Quater* pRangeEffect = CEffect_Range_Quater::Create(m_pGraphicDev, this, EFFECT_RANGE_QUATER_TYPE::CIRCLE_ATTACK);
    NULL_CHECK_RETURN(pRangeEffect, E_FAIL);
    FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Monster_Basic", pRangeEffect), E_FAIL);
    m_pRangeEffect = pRangeEffect;
   
    m_pBaseRangeEffect = CEffect_Range_Quater::Create(m_pGraphicDev, this, EFFECT_RANGE_QUATER_TYPE::CIRCLE_ATTACK);
    NULL_CHECK_RETURN(m_pBaseRangeEffect, E_FAIL);
    FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Monster_Basic_Base", m_pBaseRangeEffect), E_FAIL);



    return S_OK;
}

HRESULT CSkill_Monster_CircleAttack::Play()
{
    _vec3 vOwnerPos = m_pOwnerObject->Get_Transform()->Get_Info(INFO::INFO_POS);
    OBJ_ID eObjID = m_pOwnerObject->Get_ID();

    _float     fRangeAlphaValue  = 180.f;

    _float     fBaseAlphaValue = 80.f;


    if (eObjID == OBJ_ID::MONSTER_HEDGEHOG)
    {
        m_pRangeEffect->Play_Effect(_vec3{ vOwnerPos.x, 0.01f, vOwnerPos.z + 4 });
        m_pRangeEffect->Alphaing(0.01f, fRangeAlphaValue, fRangeAlphaValue);
        m_pRangeEffect->Scaling(1.4f, 0.3f, 0.8f);    // 14 frame

        m_pBaseRangeEffect->Play_Effect(_vec3{ vOwnerPos.x, 0.01f, vOwnerPos.z + 4 });
        m_pBaseRangeEffect->Alphaing(0.01f, fBaseAlphaValue, fBaseAlphaValue);
        m_pBaseRangeEffect->Scaling(0.01f, 0.8f, 0.8f);

    }

    if (eObjID == OBJ_ID::MONSTER_RAM)
    {
        m_pRangeEffect->Play_Effect(_vec3{ vOwnerPos.x, 0.01f, vOwnerPos.z + 4 });
        m_pRangeEffect->Alphaing(0.01f, fRangeAlphaValue, fRangeAlphaValue);
        m_pRangeEffect->Scaling(1.6f, 0.3f, 0.8f);  // 16 frame

        m_pBaseRangeEffect->Play_Effect(_vec3{ vOwnerPos.x, 0.01f, vOwnerPos.z + 4 });
        m_pBaseRangeEffect->Alphaing(0.01f, fBaseAlphaValue, fBaseAlphaValue);
        m_pBaseRangeEffect->Scaling(0.01f, 0.8f, 0.8f);

    }

    if (eObjID == OBJ_ID::MONSTER_BAT)
    {

        m_pRangeEffect->Play_Effect(_vec3{ vOwnerPos.x, 0.01f, vOwnerPos.z + 4 });
        m_pRangeEffect->Alphaing(0.01f, fRangeAlphaValue, fRangeAlphaValue);
        m_pRangeEffect->Scaling(0.8f, 0.3f, 0.7f);     // 8 Frame

        m_pBaseRangeEffect->Play_Effect(_vec3{ vOwnerPos.x, 0.01f, vOwnerPos.z + 4 });
        m_pBaseRangeEffect->Alphaing(0.01f, fBaseAlphaValue, fBaseAlphaValue);
        m_pBaseRangeEffect->Scaling(0.01f, 0.7f, 0.7f);

    }

    if (eObjID == OBJ_ID::MONSTER_WYVERN )
    {
        m_pRangeEffect->Play_Effect(_vec3{ vOwnerPos.x, 0.01f, vOwnerPos.z + 4 });
        m_pRangeEffect->Alphaing(0.01f, fRangeAlphaValue, fRangeAlphaValue);
        m_pRangeEffect->Scaling(0.9f, 0.3f, 0.8f);    // 9 Frame

        m_pBaseRangeEffect->Play_Effect(_vec3{ vOwnerPos.x, 0.01f, vOwnerPos.z + 4 });
        m_pBaseRangeEffect->Alphaing(0.01f, fBaseAlphaValue, fBaseAlphaValue);
        m_pBaseRangeEffect->Scaling(0.01f, 0.8f, 0.8f);
    }

    if (eObjID == OBJ_ID::MONSTER_WYVERNRED)
    {
        m_pRangeEffect->Play_Effect(_vec3{ vOwnerPos.x, 0.01f, vOwnerPos.z + 4 });
        m_pRangeEffect->Alphaing(0.01f, fRangeAlphaValue, fRangeAlphaValue);
        m_pRangeEffect->Scaling(0.9f, 0.3f, 0.8f);    // 9 Frame

        m_pBaseRangeEffect->Play_Effect(_vec3{ vOwnerPos.x, 0.01f, vOwnerPos.z + 4 });
        m_pBaseRangeEffect->Alphaing(0.01f, fBaseAlphaValue, fBaseAlphaValue);
        m_pBaseRangeEffect->Scaling(0.01f, 0.8f, 0.8f);
    }

    if (eObjID == OBJ_ID::MONSTER_VIOLETDRAGON)
    {
        m_pRangeEffect->Play_Effect(_vec3{ vOwnerPos.x, 0.01f, vOwnerPos.z + 4 });
        m_pRangeEffect->Alphaing(0.01f, fRangeAlphaValue, fRangeAlphaValue);
        m_pRangeEffect->Scaling(0.9f, 0.3f, 1.2f);    // 18 Frame

        m_pBaseRangeEffect->Play_Effect(_vec3{ vOwnerPos.x, 0.01f, vOwnerPos.z + 4 });
        m_pBaseRangeEffect->Alphaing(0.01f, fBaseAlphaValue, fBaseAlphaValue);
        m_pBaseRangeEffect->Scaling(0.01f, 1.2f, 1.2f);
    }


    m_bActive = true;


    return S_OK;
}

HRESULT CSkill_Monster_CircleAttack::End()
{

    m_pRangeEffect->Set_Active(false);
    m_pBaseRangeEffect->Set_Active(false);

    return S_OK;
}

CSkill_Monster_CircleAttack* CSkill_Monster_CircleAttack::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
{
    CSkill_Monster_CircleAttack* pInstance = new CSkill_Monster_CircleAttack(pGraphicDev, _pOwnerObject);

    if (FAILED(pInstance->Ready_Object()))
    {
        Safe_Release(pInstance);

        MSG_BOX("Skill_Monster_Basic Create Failed");
        return nullptr;
    }

    return pInstance;
}

void CSkill_Monster_CircleAttack::Free()
{
}
