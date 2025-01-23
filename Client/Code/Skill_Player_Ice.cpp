#include "stdafx.h"
#include "Skill_Player_Ice.h"

#include "Export_Function.h"

#include "Effect_Ice.h"
#include "Effect_Range_Quater.h"
#include "SphereCollider.h"
#include "RangeObj.h"
#include "GameObject.h"
#include "Player.h"

CSkill_Player_Ice::CSkill_Player_Ice(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID)
    : CSkill(pGraphicDev, _eID)
{
}

CSkill_Player_Ice::CSkill_Player_Ice(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
    : CSkill(pGraphicDev, _pOwnerObject, OBJ_ID::SKILL_PLAYER_ICE)
{
}

CSkill_Player_Ice::CSkill_Player_Ice(const CSkill_Player_Ice& rhs)
    : CSkill(rhs)
{
}

CSkill_Player_Ice::~CSkill_Player_Ice()
{
}

HRESULT CSkill_Player_Ice::Ready_Object()
{
    CSkill::Ready_Object();

    m_fSkillDamage = 30;
    m_iSkillUsage = 2;
    m_iLv = 0;

    m_bActive = false;
    m_bAttackStart = false;
    //m_pTransformCom->Set_Scale(_vec3{ 10.f, 10.f, 10.f });

    FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

    m_fontColor = D3DCOLOR_ARGB(255, 0, 102, 153);
    m_contentStr = L"적을 얼려서 느리게 만듭니다!";

    return S_OK;
}

_int CSkill_Player_Ice::Update_Object(const _float& fTimeDelta)
{
    _int iExit = CSkill::Update_Object(fTimeDelta);

    NULL_CHECK_RETURN(m_pOwnerObject, E_FAIL);

    if (!m_pOwnerObject->Is_Active())
    {
        CEventMgr::GetInstance()->Delete_Obj(this);
        return iExit;
    }
    m_pTransformCom->Set_Pos(m_pOwnerObject->Get_Transform()->Get_Info(INFO::INFO_POS));
 
    
    //m_pRangeObj->Update_Object(fTimeDelta);

    Engine::Add_RenderGroup(RENDER_NONALPHA, this);

    if (!m_bAttackStart && m_pSKillEffect->Get_Animator()->Get_CurAniamtion()->Get_CurFrame() == 4)
    {
        static_cast<CPlayer*>(m_pOwnerObject)->Set_Skill(true);
        m_bAttackStart = true;
    }


    if (!m_pSKillEffect->Is_Active())
    {
        CCameraMgr::GetInstance()->Start_Action(CAMERA_ACTION::PLAYER_ATK_TO_IDL);
        m_bAttackStart = false;
        m_bActive = false;
    }


    return iExit;
}

void CSkill_Player_Ice::LateUpdate_Object()
{
    //m_pRangeObj->LateUpdate_Object();
    CSkill::LateUpdate_Object();
}

void CSkill_Player_Ice::Render_Object()
{
    //m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());
    //m_pBufferCom->Render_Buffer();
    //m_pRangeObj->Render_Object();
    CSkill::Render_Object();
}

HRESULT CSkill_Player_Ice::Add_Component()
{
    CEffect_Ice* pIceEffect = CEffect_Ice::Create(m_pGraphicDev, this);
    NULL_CHECK_RETURN(pIceEffect, E_FAIL);
    FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Player_IceSkill_Effect", pIceEffect), E_FAIL);
    m_pSKillEffect = pIceEffect;
    m_pSKillEffect->Set_Maintain(TRUE); // 수정시 팀장보고

   /* CRangeObj* pGameObject = CRangeObj::Create(m_pGraphicDev, this, 10.f);
    CSphereCollider* pShpere = dynamic_cast<CSphereCollider*>(pGameObject->Get_Component(COMPONENT_TYPE::COL_SPHERE, ID_STATIC));
    pShpere->Set_Radius(20.f);
    NULL_CHECK_RETURN(pGameObject, E_FAIL);
    CEventMgr::GetInstance()->Add_Obj(L"Player_IceSkill_Sphere", pGameObject);
    m_pRangeObj = pGameObject;*/

   /* CComponent* pComponent = m_pColliderCom = dynamic_cast<CRectCollider*>(Engine::Clone_Proto(COMPONENT_TYPE::COL_RECT, this));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::COL_RECT, pComponent);*/


    return S_OK;
}

HRESULT CSkill_Player_Ice::Play()
{
    NULL_CHECK_RETURN(m_pOwnerObject, E_FAIL);

    if (static_cast<CPlayer*>(m_pOwnerObject)->Get_PlayerClass() == CLASS_TYPE::NINJA)
        static_cast<CPlayer*>(m_pOwnerObject)->Off_Clocking();

    _vec3 vOwnerPos = m_pOwnerObject->Get_Transform()->Get_Info(INFO::INFO_POS);
   
    m_pSKillEffect->Play_Effect(_vec3{ vOwnerPos.x, 0.01f, vOwnerPos.z + 2 });
   
    m_bActive = true;

    CCameraMgr::GetInstance()->Shake_Camera(0.15, 30);
    CSoundMgr::GetInstance()->PlaySoundW(L"skill_freezepaw.wav", CHANNEL_ID::PLAYER_2, VOLUME_PLAYER_SKILL);
    return S_OK;
}

HRESULT CSkill_Player_Ice::End()
{
    return S_OK;
}

CSkill_Player_Ice* CSkill_Player_Ice::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
{
    CSkill_Player_Ice* pInstance = new CSkill_Player_Ice(pGraphicDev, _pOwnerObject);

    if (FAILED(pInstance->Ready_Object()))
    {
        Safe_Release(pInstance);

        MSG_BOX("Skill_Player_Ice Create Failed");
        return nullptr;
    }

    return pInstance;
}

void CSkill_Player_Ice::Free()
{
    __super::Free();
}
