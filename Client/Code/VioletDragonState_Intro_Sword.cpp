#include "VioletDragonState_Intro_Sword.h"
#include "Export_Function.h"
#include "Player.h"
#include "VioletDragon.h"
#include "SoundMgr.h"
#include "CameraMgr.h"
#include "BossSceneMgr.h"
CVioletDragonState_Intro_Sword::CVioletDragonState_Intro_Sword(LPDIRECT3DDEVICE9 pGraphicDev)
    :CState(pGraphicDev)
{
}

CVioletDragonState_Intro_Sword::~CVioletDragonState_Intro_Sword()
{
}

HRESULT CVioletDragonState_Intro_Sword::Ready_State(CStateMachine* pOwner)
{

    if (nullptr != pOwner)
    {
        m_pOwner = pOwner;
    }
    m_eState = STATE_TYPE::BOSS_INTRO_SWORD;

    m_fAccTime = 0.f;

    return S_OK;
}

STATE_TYPE CVioletDragonState_Intro_Sword::Update_State(const _float& fTimeDelta)
{
    STATE_TYPE eState = m_eState;

    // Monstre Component ==============================
    // Monster - Ai Com
    CComponent* pOwnerAI = dynamic_cast<CAIComponent*>(m_pOwner->Get_OwnerObject()->Get_Component(COMPONENT_TYPE::AICOM, COMPONENTID::ID_DYNAMIC));
    NULL_CHECK_RETURN(pOwnerAI, eState);

    // Monster - Transform Com
    CTransform* pOwnerTransform = m_pOwner->Get_OwnerObject()->Get_Transform();
    NULL_CHECK_RETURN(pOwnerTransform, eState);

    //Monster - Animator
    CComponent* pOwnerAnimator = dynamic_cast<CAnimator*>(m_pOwner->Get_OwnerObject()->Get_Component(COMPONENT_TYPE::ANIMATOR, COMPONENTID::ID_STATIC));
    NULL_CHECK_RETURN(pOwnerAnimator, eState);

    // Monster - Cur Animation
    CAnimation* pOwenrCurAnimation = dynamic_cast<CAnimator*>(pOwnerAnimator)->Get_CurAniamtion();
    NULL_CHECK_RETURN(pOwenrCurAnimation, eState);

    //Monster - Cur HP Condition
    _bool Owner_bHP90 = dynamic_cast<CVioletDragon*>(m_pOwner->Get_OwnerObject())->Get_HP90();
    _bool Owner_bHP60 = dynamic_cast<CVioletDragon*>(m_pOwner->Get_OwnerObject())->Get_HP60();
    _bool Owner_bHP30 = dynamic_cast<CVioletDragon*>(m_pOwner->Get_OwnerObject())->Get_HP30();


    // Player Component ==============================
    // Player
    CGameObject* pPlayer = dynamic_cast<CPlayer*>(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::PLAYER, L"Player"));
    NULL_CHECK_RETURN(pPlayer, eState);

    // Player - Transform Com
    CTransform* pPlayerTransform = dynamic_cast<CTransform*>(Engine::Get_Component(OBJ_TYPE::PLAYER, L"Player", COMPONENT_TYPE::TRANSFORM, COMPONENTID::ID_DYNAMIC));
    NULL_CHECK_RETURN(pPlayerTransform, eState);


    // GET INFO =================================================================
    // Monster - Pos
    _vec3       vOwnerPos = pOwnerTransform->Get_Info(INFO_POS);
    NULL_CHECK_RETURN(vOwnerPos, eState);

    // Mosnter - Origin Pos
    _vec3       vOwnerOriginPos = dynamic_cast<CMonster*>(m_pOwner->Get_OwnerObject())->Get_OriginPos();
    NULL_CHECK_RETURN(vOwnerOriginPos, eState);

    // Monster - Speed
    _float      vOwnerSpeed = dynamic_cast<CMonster*>(m_pOwner->Get_OwnerObject())->Get_MoveInfo().fMoveSpeed;
    NULL_CHECK_RETURN(vOwnerSpeed, eState);

    // Monster - PatternTime
    _float      vOwnerPatternTime = dynamic_cast<CMonster*>(m_pOwner->Get_OwnerObject())->Get_PatternTime();
    NULL_CHECK_RETURN(vOwnerPatternTime, eState);

    // Monster - Scale
    _vec3 vOwnerScale = pOwnerTransform->Get_Scale();
    NULL_CHECK_RETURN(vOwnerScale, eState);

    // Monster - Dir
    _vec3 vOwnerDir = pOwnerTransform->Get_Dir();
    NULL_CHECK_RETURN(vOwnerDir, eState);

    // Player - Pos
    _vec3       vPlayerPos;
    vPlayerPos = pPlayerTransform->Get_Info(INFO_POS);
    NULL_CHECK_RETURN(pPlayerTransform, eState);


    // Setting Value
    // Dir Vector
    _vec3       vDir = vPlayerPos - vOwnerPos;            // ���� ���� [�÷��̾� - ����]
    _vec3       vOriginDir = vOwnerOriginPos - vOwnerPos; // ���� ���� [����ġ  - ����]

    // Distance
    _float      fPlayerDistance = (D3DXVec3Length(&vDir));       // �÷��̾���� �Ÿ�
    _float      fOriginDistance = (D3DXVec3Length(&vOriginDir)); // �� ��ġ���� �Ÿ�


    m_fAccTime += fTimeDelta;



    if (pOwenrCurAnimation->Is_End() && m_fAccTime >= 1.f)
    {
        m_fAccTime = 0.f;
     
        // ī�޶� �׼� �߰�
       /* CGameObject* pPlayer = CManagement::GetInstance()->Get_Player();
        CGameObject* pBoss = CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::MONSTER, L"Monster_VioletDragon");
        if (nullptr != pBoss && nullptr != pPlayer)
        {
            _vec3 vBossPos{ pBoss->Get_Transform()->Get_Info(INFO_POS).x, pPlayer->Get_Transform()->Get_Info(INFO_POS).y, pBoss->Get_Transform()->Get_Info(INFO_POS).z };

            CCameraMgr::GetInstance()->Start_Action(CAMERA_ACTION::OBJ_CHANGE_TARGET, vBossPos, pPlayer->Get_Transform()->Get_Info(INFO_POS));
        }*/

        CBossSceneMgr::GetInstance()->Set_BossIntroAnimation_End(); // ������ ����
        return STATE_TYPE::CHASE;
    }




    return STATE_TYPE::BOSS_INTRO_SWORD;
}


void CVioletDragonState_Intro_Sword::LateUpdate_State()
{

}

void CVioletDragonState_Intro_Sword::Render_State()
{
}

STATE_TYPE CVioletDragonState_Intro_Sword::Key_Input(const _float& fTimeDelta)
{
    return m_eState;
}

CVioletDragonState_Intro_Sword* CVioletDragonState_Intro_Sword::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
    CVioletDragonState_Intro_Sword* pInstance = new CVioletDragonState_Intro_Sword(pGraphicDev);

    if (FAILED(pInstance->Ready_State(pOwner)))
    {
        Safe_Release(pInstance);
        MSG_BOX("Violet Dragon Intro_Sword Create Failed");
        return nullptr;

    }

    return pInstance;
}

void CVioletDragonState_Intro_Sword::Free()
{
    __super::Free();
}
