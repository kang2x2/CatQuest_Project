#include "FishState_Patrol.h"
#include "Export_Function.h"
#include "Player.h"

CFishState_Patrol::CFishState_Patrol(LPDIRECT3DDEVICE9 pGraphicDev)
    : CState(pGraphicDev)
    , m_fAccTime(0.f)
    , m_fChaseRange(0.f)
    , m_fComeBackRange(0.f)
    , m_fPatrolRange(0.f)
    , m_fPlayerTargetRange(0.f)
    , m_fAttackRange(0.f)
{
}

CFishState_Patrol::~CFishState_Patrol()
{
}

HRESULT CFishState_Patrol::Ready_State(CStateMachine* pOwner)
{
    

    if (nullptr != pOwner)
    {
        m_pOwner = pOwner;
    }
    m_eState = STATE_TYPE::PATROL;

    // ���¿� ���� ���� ��ġ
    m_fPatrolRange = 1.f;  // Patrol ����
    m_fChaseRange = 10.f; // Chase ����
    m_fComeBackRange = 10.f; // ComeBack ���� - ����ġ -> �� ��ġ
    m_fPlayerTargetRange = 10.f; // ComeBack ���� - ����ġ -> �÷��̾� ��ġ
    m_fAttackRange = 20.f;  // Attack ����


    return S_OK;

}

STATE_TYPE CFishState_Patrol::Update_State(const _float& fTimeDelta)
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
    vPlayerPos.y = vOwnerPos.y;
    _vec3       vDir = vPlayerPos - vOwnerPos;            // ���� ���� [�÷��̾� - ����]
    _vec3       vOriginDir = vOwnerOriginPos - vOwnerPos; // ���� ���� [����ġ  - ����]

    // Distance
    _float      fPlayerDistance = (D3DXVec3Length(&vDir));       // �÷��̾���� �Ÿ�
    _float      fOriginDistance = (D3DXVec3Length(&vOriginDir)); // �� ��ġ���� �Ÿ�


   // ���� ������ ���
    m_fAccTime += fTimeDelta;

    if (vOwnerPatternTime <= m_fAccTime)
    {
        dynamic_cast<CAIComponent*>(pOwnerAI)->Random_Move(fTimeDelta, vOwnerSpeed);
        m_fAccTime = 0.f;
    }
    pOwnerTransform->Translate(fTimeDelta * vOwnerSpeed);




#pragma region State Change 
    // PATROL �켱����
    // Back Patrol - Chase - Comeback - Attack


   //  �ӽ� ��ġ�� Patrol ���� comback�� ���� ��


   // BACK Patrol ���� ����
    if (vOwnerDir.z > 0)
    {
        //cout << "Back patrol ����" << endl;
        return STATE_TYPE::BACK_PATROL;
    }

    if (dynamic_cast<CPlayer*>(pPlayer)->Get_Clocking() != true)
    {
        //// CHASE ���� ����
        //if (fPlayerDistance <= m_fChaseRange)
        //{
        //    if (vOwnerDir.z < 0)
        //    {
        //       // cout << "Chase ����" << endl;
        //       // pOwnerTransform->Set_Dir(vec3.zero);
        //        return STATE_TYPE::CHASE;
        //    }
        //    else
        //    {
        //       // cout << "Back Chase ����" << endl;
        //      //  pOwnerTransform->Set_Dir(vec3.zero);
        //        return STATE_TYPE::BACK_CHASE;
        //    }
        //}

   

        //  ATTACK ���� ����
        if (fPlayerDistance <= m_fAttackRange)
        {
            if (vDir.z < 0)
            {
               // cout << "attack ����" << endl;
               // pOwnerTransform->Set_Dir(vec3.zero);
                return STATE_TYPE::MONATTACK;
            }
            else
            {
               // cout << "back attack ����" << endl;
              //  pOwnerTransform->Set_Dir(vec3.zero);
                return STATE_TYPE::BACK_MONATTACK;
            }
        }
    }

    // COMEBACK ���� ����
    if (fOriginDistance >= m_fComeBackRange && fPlayerDistance > m_fPlayerTargetRange)
    {
        if (vOwnerDir.z < 0)
        {
            // cout << "comback ����" << endl;
            // pOwnerTransform->Set_Dir(vec3.zero);
            return STATE_TYPE::COMEBACK;
        }
        else
        {
            // cout << "back comback ����" << endl;
            // pOwnerTransform->Set_Dir(vec3.zero);
            return STATE_TYPE::BACK_COMEBACK;
        }
    }
    // Default
    return STATE_TYPE::PATROL;

#pragma endregion

  
}


void CFishState_Patrol::LateUpdate_State()
{

}

void CFishState_Patrol::Render_State()
{
    
}

STATE_TYPE CFishState_Patrol::Key_Input(const _float& fTimeDelta)
{
 
    return m_eState;
}

CFishState_Patrol* CFishState_Patrol::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
 {
    CFishState_Patrol* pInstance = new CFishState_Patrol(pGraphicDev);

    if (FAILED(pInstance->Ready_State(pOwner)))
    {
        Safe_Release(pInstance);
        MSG_BOX("Serpent Patrol Create Failed");
        return nullptr;

    }

    return pInstance;
}

void CFishState_Patrol::Free()
{
    __super::Free();
}
