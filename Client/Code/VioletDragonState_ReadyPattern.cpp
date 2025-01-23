#include "VioletDragonState_ReadyPattern.h"
#include "Export_Function.h"
#include "Player.h"
#include "VioletDragon.h"
#include "SoundMgr.h"
#include "Engine_Define.h"

CVioletDragonState_ReadyPattern::CVioletDragonState_ReadyPattern(LPDIRECT3DDEVICE9 pGraphicDev)
    : CState(pGraphicDev)
    , m_fAccTime(0.f)
    , m_fChaseRange(0.f)
    , m_fComeBackRange(0.f)
    , m_fPatrolRange(0.f)
    , m_fPlayerTargetRange(0.f)
    , m_fAttackRange(0.f)
{
}

CVioletDragonState_ReadyPattern::~CVioletDragonState_ReadyPattern()
{
}

HRESULT CVioletDragonState_ReadyPattern::Ready_State(CStateMachine* pOwner)
{
    if (nullptr != pOwner)
    {
        m_pOwner = pOwner;
    }
    m_eState = STATE_TYPE::BACK_ATTACK;

    // 상태에 전이 조건 수치
    m_fPatrolRange = 5.f;  // Patrol 전이
    m_fChaseRange = 20.f; // Chase 전이
    m_fComeBackRange = 10.f; // ComeBack 전이 - 현위치 -> 원 위치
    m_fPlayerTargetRange = 20.f; // ComeBack 전이 - 현위치 -> 플레이어 위치
    m_fAttackRange = 10.f;  // Attack 전이


    m_bSound = false;
    return S_OK;
}

STATE_TYPE CVioletDragonState_ReadyPattern::Update_State(const _float& fTimeDelta)
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
    _vec3       vDir = vPlayerPos - vOwnerPos;            // 방향 벡터 [플레이어 - 몬스터]
    _vec3       vOriginDir = vOwnerOriginPos - vOwnerPos; // 방향 벡터 [원위치  - 몬스터]

    // Distance
    _float      fPlayerDistance = (D3DXVec3Length(&vDir));       // 플레이어와의 거리
    _float      fOriginDistance = (D3DXVec3Length(&vOriginDir)); // 원 위치와의 거리



    if (dynamic_cast<CMonster*>(m_pOwner->Get_OwnerObject())->Get_StatInfo().bDead == true)
    {
        return STATE_TYPE::BOSSDEAD;
    }

    if (m_bSound == false)
    {

        CSoundMgr::GetInstance()->PlaySound(L"magic_appear_2.wav", CHANNEL_ID::MONSTER_BOSS_0, 1.f);
        m_bSound = true;
    }


   
    if (pOwenrCurAnimation->Get_CurFrame() == 7.f)
    {


        _float fPosPMX   = rand() % 2;
        _float fPosPMZ   = rand() % 2;
        _float fRandomX = rand()  % 15;
        _float fRandomZ = rand()  % 15;

        if (fPosPMX == 1)
        {

            if (fPosPMZ == 1)
            {
                pOwnerTransform->Set_Pos(_vec3{ vOwnerOriginPos.x + fRandomX, vOwnerOriginPos.y, vOwnerOriginPos.z + fRandomZ });
            }
            else
            {
                pOwnerTransform->Set_Pos(_vec3{ vOwnerOriginPos.x + fRandomX, vOwnerOriginPos.y, vOwnerOriginPos.z - fRandomZ });
            }

        }
        else
        {
            if (fPosPMZ == 1)
            {
                pOwnerTransform->Set_Pos(_vec3{ vOwnerOriginPos.x - fRandomX, vOwnerOriginPos.y, vOwnerOriginPos.z + fRandomZ });
            }
            else
            {
                pOwnerTransform->Set_Pos(_vec3{ vOwnerOriginPos.x - fRandomX, vOwnerOriginPos.y, vOwnerOriginPos.z - fRandomZ });
            }
        }
     
    }
    


#pragma region State Change


    //  Cast -> Action

    if (m_pOwner->Get_Animator()->Get_CurAniamtion()->Is_End())
    {
        m_bSound = false;
        if (Owner_bHP90 == true && Owner_bHP60 == true && Owner_bHP30 == true)
        {
            return STATE_TYPE::BOSS_CREATE_CAST;
        }


        if (Owner_bHP90 == true && Owner_bHP60 == true && Owner_bHP30 == false)
        {
            return STATE_TYPE::BOSS_BLOODY_CAST;

        }

        if (Owner_bHP90 == true && Owner_bHP60 == false && Owner_bHP30 == false)
        {
            return STATE_TYPE::BOSS_CONVERGING_CAST;
        }
   
    }

    return STATE_TYPE::BOSS_READY_PATTERN;

}

void CVioletDragonState_ReadyPattern::LateUpdate_State()
{
    
}

void CVioletDragonState_ReadyPattern::Render_State()
{
   

}

STATE_TYPE CVioletDragonState_ReadyPattern::Key_Input(const _float& fTimeDelta)
{
 
    return m_eState;
}

CVioletDragonState_ReadyPattern* CVioletDragonState_ReadyPattern::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
    CVioletDragonState_ReadyPattern* pInstance = new CVioletDragonState_ReadyPattern(pGraphicDev);

    if (FAILED(pInstance->Ready_State(pOwner)))
    {
        Safe_Release(pInstance);
        MSG_BOX("WyvernState ComeBack Create Failed");
        return nullptr;

    }

    return pInstance;
}

void CVioletDragonState_ReadyPattern::Free()
{
    __super::Free();
}
