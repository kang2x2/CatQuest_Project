#include "stdafx.h"
#include "Skill_Player_Fly.h"

#include "Export_Function.h"

#include "Effect_FlyLighting.h"
#include "Calculator.h"
#include "RangeObj.h"
#include "GameObject.h"
#include "Player.h"
#include "Monster.h"

CSkill_Player_Fly::CSkill_Player_Fly(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID)
    : CSkill(pGraphicDev, _eID)
{
}

CSkill_Player_Fly::CSkill_Player_Fly(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
    : CSkill(pGraphicDev, _pOwnerObject, OBJ_ID::SKILL_PLAYER_FLY)
{
}

CSkill_Player_Fly::CSkill_Player_Fly(const CSkill_Player_Fly& rhs)
    : CSkill(rhs)
{
}

CSkill_Player_Fly::~CSkill_Player_Fly()
{
}

HRESULT CSkill_Player_Fly::Ready_Object()
{
    CSkill::Ready_Object();


    FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

    m_fSkillDamage = 30;
    m_iSkillUsage = 0;


    m_bActive = false;
    m_bIsEffectEnd = false;
    m_bAttack = false;

    m_pTransformCom->Set_Scale(_vec3{ 3.f, 3.f, 3.f });
    m_pTransformCom->Set_Pos(m_pOwnerObject->Get_Transform()->Get_Info(INFO::INFO_POS));

    m_fontColor = D3DCOLOR_ARGB(255, 102, 0, 102);

    return S_OK;
}

_int CSkill_Player_Fly::Update_Object(const _float& fTimeDelta)
{
    _int iExit = __super::Update_Object(fTimeDelta);

    NULL_CHECK_RETURN(m_pOwnerObject, E_FAIL);

    if (!m_pOwnerObject->Is_Active())
    {
        CEventMgr::GetInstance()->Delete_Obj(this);
        return iExit;
    }
    if (this->Is_Active())
    {
        m_pRangeObj->Set_Active(true);
    }

    Engine::Add_RenderGroup(RENDER_ALPHA, this);

    Picking_Terrain();

    m_pAICom->Chase_Target(&m_vMousePos, fTimeDelta, 15.f);
    m_pTransformCom->Translate(fTimeDelta * 15.f);

    return iExit;
}

void CSkill_Player_Fly::LateUpdate_Object()
{
    if (m_bAttack)
        m_bAttack = false;

    _vec3 vDir = m_pOwnerObject->Get_Transform()->Get_Info(INFO::INFO_POS) - m_pTransformCom->Get_Info(INFO::INFO_POS);
    _float fLength = D3DXVec3Length(&vDir);

    if (fLength > 40)
        m_pTransformCom->Set_Pos(m_pOwnerObject->Get_Transform()->Get_Info(INFO::INFO_POS));

    __super::LateUpdate_Object();
}

void CSkill_Player_Fly::Render_Object()
{
    // 빌보드 해제
    m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(200, 255, 255, 255));

    _matrix matWorld = m_pTransformCom->Get_WorldMat();
    _matrix matBill;
    _vec3 vPos;

    memcpy(&vPos, &matWorld.m[3], sizeof(_vec3));
    vPos.y = 0.02f;

    matWorld *= *D3DXMatrixInverse(&matBill, NULL, &CCameraMgr::GetInstance()->Get_Billboard_X());
    memcpy(&matWorld.m[3], &vPos, sizeof(_vec3));

    m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);

    m_pTargetTexCom->Render_Texture();
    m_pTargetBuffer->Render_Buffer();

    m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));

    __super::Render_Object();
}

void CSkill_Player_Fly::OnCollision_Enter(CGameObject* _pColObj)
{
  
}

void CSkill_Player_Fly::OnCollision_Stay(CGameObject* _pColObj)
{
    switch (_pColObj->Get_Type())
    {
    case Engine::OBJ_TYPE::MONSTER:
    {
        if (m_bAttack)
            static_cast<CMonster*>(_pColObj)->Damaged(m_fSkillDamage + rand() % 10);
    }
    break;
    default:
    {
    }
    break;
    } // Switch end
}

void CSkill_Player_Fly::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CSkill_Player_Fly::Add_Component()
{

    CComponent* pComponent = nullptr;

    pComponent = m_pTargetTexCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Skill_Flight_Target", this));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

    pComponent = m_pTargetBuffer = dynamic_cast<CTerrainRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_TERRAIN_RC_TEX, this));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_TERRAIN_RC_TEX, pComponent);

    pComponent = m_pAICom = dynamic_cast<CAIComponent*>(Engine::Clone_Proto(COMPONENT_TYPE::AICOM, this));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_DYNAMIC].emplace(COMPONENT_TYPE::AICOM, pComponent);

    CEffect_FlyLighting* pFlyEffect = CEffect_FlyLighting::Create(m_pGraphicDev, this);
    NULL_CHECK_RETURN(pFlyEffect, E_FAIL);
    FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Player_FlySkill_Effect", pFlyEffect), E_FAIL);
    m_pSKillEffect = pFlyEffect;
    m_pSKillEffect->Set_Maintain(TRUE); // 수정시 팀장보고

    CRangeObj* pGameObject = CRangeObj::Create(m_pGraphicDev, this, 5.f);
    CSphereCollider* pShpere = dynamic_cast<CSphereCollider*>(pGameObject->Get_Component(COMPONENT_TYPE::COL_SPHERE, ID_STATIC));
    pShpere->Set_Radius(5.f);
    NULL_CHECK_RETURN(pGameObject, E_FAIL);
    CEventMgr::GetInstance()->Add_Obj(L"Player_FlySkill_Sphere", pGameObject);
    m_pRangeObj = pGameObject;
    m_pRangeObj->Set_Maintain(TRUE);

    

    return S_OK;
}

HRESULT CSkill_Player_Fly::Play()
{
    if (!m_bActive)
        return E_FAIL;

    _vec3 vOwnerPos = m_pTransformCom->Get_Info(INFO::INFO_POS);
    m_pSKillEffect->Play_Effect(_vec3{ vOwnerPos.x, 0.02f, vOwnerPos.z + 1 });
    CCameraMgr::GetInstance()->Shake_Camera(0.15, 30);
    m_bAttack = true;
    return S_OK;
}

HRESULT CSkill_Player_Fly::End()
{
    return S_OK;
}

void CSkill_Player_Fly::Picking_Terrain()
{
    SCENE_TYPE eSceneType = CManagement::GetInstance()->Get_CurScene()->Get_SceneType();
    CGameObject* pCurTerrain = nullptr;

    switch (eSceneType)
    {
    case Engine::SCENE_TYPE::WORLD:
        pCurTerrain = CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::TERRAIN, L"Terrain_Tool");
        break;
    case Engine::SCENE_TYPE::DUNGEON_SWAMP:
        pCurTerrain = CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::TERRAIN, L"Terrain_Tool");
        break;
    default:
        break;
    }

    POINT pt;
    GetCursorPos(&pt);
    ScreenToClient(g_hWnd, &pt);

    _vec3 vecMouse;
    if (nullptr != pCurTerrain)
        vecMouse = CCalculator::GetInstance()->RealMouse_Picking(m_pGraphicDev, pt, pCurTerrain);
    else
        return;

    vecMouse.y = 0.02;
    m_vMousePos = vecMouse;
  
  
}

CSkill_Player_Fly* CSkill_Player_Fly::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
{
    CSkill_Player_Fly* pInstance = new CSkill_Player_Fly(pGraphicDev, _pOwnerObject);

    if (FAILED(pInstance->Ready_Object()))
    {
        Safe_Release(pInstance);

        MSG_BOX("Skill_Player_Fly Create Failed");
        return nullptr;
    }

    return pInstance;
}

void CSkill_Player_Fly::Free()
{
    __super::Free();
}
