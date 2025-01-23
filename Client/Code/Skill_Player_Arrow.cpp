#include "stdafx.h"
#include "Skill_Player_Arrow.h"

#include "Export_Function.h"

#include "Calculator.h"
#include "RangeObj.h"
#include "GameObject.h"
#include "Player.h"
#include "Monster.h"

CSkill_Player_Arrow::CSkill_Player_Arrow(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID)
    : CSkill(pGraphicDev, _eID)
{
}

CSkill_Player_Arrow::CSkill_Player_Arrow(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
    : CSkill(pGraphicDev, _pOwnerObject, OBJ_ID::SKILL_PLAYER_FLY)
{
}

CSkill_Player_Arrow::CSkill_Player_Arrow(const CSkill_Player_Arrow& rhs)
    : CSkill(rhs)
{
}

CSkill_Player_Arrow::~CSkill_Player_Arrow()
{
}

HRESULT CSkill_Player_Arrow::Ready_Object()
{
    CSkill::Ready_Object();

    m_eUILayer = UI_LAYER::LV2;

    D3DXMatrixIdentity(&m_matRot);

    FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

    m_fSkillDamage = 30;
    m_iSkillUsage = 0;


    m_bActive = false;
    m_bIsEffectEnd = false;
    m_bAttack = false;

    m_pTransformCom->Set_Scale(_vec3{ 2.f, 2.f, 1.5f });

    return S_OK;
}

_int CSkill_Player_Arrow::Update_Object(const _float& fTimeDelta)
{
    _int iExit = __super::Update_Object(fTimeDelta);

    NULL_CHECK_RETURN(m_pOwnerObject, E_FAIL);

    if (!m_pOwnerObject->Is_Active())
    {
        CEventMgr::GetInstance()->Delete_Obj(this);
        return iExit;
    }
  
    Engine::Add_RenderGroup(RENDER_WDUI, this);

    Picking_Terrain();

    if (static_cast<CPlayer*>(m_pOwnerObject)->Is_Fly())
    {
        m_vMousePos.y = m_pOwnerObject->Get_Transform()->Get_Info(INFO::INFO_POS).y;
    }

    _vec3 vDir = m_vMousePos - m_pOwnerObject->Get_Transform()->Get_Info(INFO::INFO_POS);
    D3DXVec3Normalize(&vDir, &vDir);
    _vec3 vArrowPos = m_pOwnerObject->Get_Transform()->Get_Info(INFO::INFO_POS) + (vDir * 5.2);
    m_pTransformCom->Set_Dir(vDir);

    _vec3		vAxis = *D3DXVec3Cross(&vAxis, &vec3.right, &vDir);
    _float		fDot = D3DXVec3Dot(&vec3.right, &vDir);
    _float		fAngle = acosf(fDot);

    if (vDir.z > 0)
        fAngle *= -1;

    m_pTransformCom->Set_Rot(_vec3{ 0.f, fAngle, 0.f });

    m_pTransformCom->Set_Pos(vArrowPos);

    
    return iExit;
}

void CSkill_Player_Arrow::LateUpdate_Object()
{
    if (m_bAttack)
        m_bAttack = false;

    __super::LateUpdate_Object();
}

void CSkill_Player_Arrow::Render_Object()
{
    // ºôº¸µå ÇØÁ¦
    m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(200, 255, 255, 255));

    _matrix matWorld = m_pTransformCom->Get_WorldMat();
    _matrix matBill;
    _vec3 vPos;

    memcpy(&vPos, &matWorld.m[3], sizeof(_vec3));

    matWorld *= *D3DXMatrixInverse(&matBill, NULL, &CCameraMgr::GetInstance()->Get_Billboard_X());
    memcpy(&matWorld.m[3], &vPos, sizeof(_vec3));

 
    m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);

    m_pTargetTexCom->Render_Texture();
    m_pTargetBuffer->Render_Buffer();

    m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));

    __super::Render_Object();
}

void CSkill_Player_Arrow::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CSkill_Player_Arrow::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CSkill_Player_Arrow::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CSkill_Player_Arrow::Add_Component()
{
    CComponent* pComponent = nullptr;

    pComponent = m_pTargetTexCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_UI_Arrow", this));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

    pComponent = m_pTargetBuffer = dynamic_cast<CTerrainRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_TERRAIN_RC_TEX, this));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_TERRAIN_RC_TEX, pComponent);

    pComponent = m_pAICom = dynamic_cast<CAIComponent*>(Engine::Clone_Proto(COMPONENT_TYPE::AICOM, this));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_DYNAMIC].emplace(COMPONENT_TYPE::AICOM, pComponent);

    return S_OK;
}

HRESULT CSkill_Player_Arrow::Play()
{
    if (!m_bActive)
        return E_FAIL;

    m_bAttack = true;
    return S_OK;
}

HRESULT CSkill_Player_Arrow::End()
{
    return S_OK;
}

void CSkill_Player_Arrow::Picking_Terrain()
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

    vecMouse.y = 3.f;
    m_vMousePos = vecMouse;
    m_vMousePos.y = m_pOwnerObject->Get_Transform()->Get_Info(INFO::INFO_POS).y;
}

CSkill_Player_Arrow* CSkill_Player_Arrow::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
{
    CSkill_Player_Arrow* pInstance = new CSkill_Player_Arrow(pGraphicDev, _pOwnerObject);

    if (FAILED(pInstance->Ready_Object()))
    {
        Safe_Release(pInstance);

        MSG_BOX("Skill_Player_Arrow Create Failed");
        return nullptr;
    }

    return pInstance;
}

void CSkill_Player_Arrow::Free()
{
    __super::Free();
}
