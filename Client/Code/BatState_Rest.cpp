#include "BatState_Rest.h"
#include "Export_Function.h"
#include "Player.h"
#include "SoundMgr.h"
#include "Bat_AfterImg.h"

CBatState_Rest::CBatState_Rest(LPDIRECT3DDEVICE9 pGraphicDev)
    : CState(pGraphicDev)
    , m_fAccTime(0.f)
    , m_fChaseRange(0.f)
    , m_fComeBackRange(0.f)
    , m_fPatrolRange(0.f)
    , m_fPlayerTargetRange(0.f)
    , m_fAttackRange(0.f)
    , m_fPosShakeRange(0.f)
    , m_fAddHeight(0.f)
    , m_fAddRot(0.f)
    , m_fScaleDown(0.f)
{
}

CBatState_Rest::~CBatState_Rest()
{
}

HRESULT CBatState_Rest::Ready_State(CStateMachine* pOwner)
{
    if (nullptr != pOwner)
    {
        m_pOwner = pOwner;
    }
    m_eState = STATE_TYPE::MONATTACK;

    // ���¿� ���� ���� ��ġ
    m_fPatrolRange = 1.f;  // Patrol ����
    m_fChaseRange = 10.f; // Chase ����
    m_fComeBackRange = 20.f; // ComeBack ���� - ����ġ -> �� ��ġ
    m_fPlayerTargetRange = 10.f; // ComeBack ���� - ����ġ -> �÷��̾� ��ġ
    m_fAttackRange = 3.f;  // Attack ����
    m_fPosShakeRange = 1.f;

    m_fPosShakeRange *= -0.2f;
    m_fAccTime = 0.f;
    m_fAddHeight += 1.2f;
    m_fAddRot += 0.3f;
    m_fScaleDown -= 0.01;


    m_iCreateAfterImg = 0.f;

    m_bAssault = false;
    m_bAfterImg = false;


    return S_OK;
}

STATE_TYPE CBatState_Rest::Update_State(const _float& fTimeDelta)
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
    _vec3       vDir = vPlayerPos - vOwnerPos;            // ���� ���� [�÷��̾� - ����]
    _vec3       vOriginDir = vOwnerOriginPos - vOwnerPos; // ���� ���� [����ġ  - ����]

    // Distance
    _float      fPlayerDistance = (D3DXVec3Length(&vDir));       // �÷��̾���� �Ÿ�
    _float      fOriginDistance = (D3DXVec3Length(&vOriginDir)); // �� ��ġ���� �Ÿ�


    m_fAccTime += fTimeDelta;


    // x �̵� ���⿡ ���� ������ ��ȯ 
    if (vOwnerPos.x < (vPlayerPos).x && vOwnerScale.x < 0)
    {
        pOwnerTransform->Set_Scale({ -vOwnerScale.x , vOwnerScale.y, vOwnerScale.z });
    }
    else if (vOwnerPos.x > (vPlayerPos).x && vOwnerScale.x > 0)
    {
        pOwnerTransform->Set_Scale({ -vOwnerScale.x , vOwnerScale.y, vOwnerScale.z });
    }



    // ����Ʈ 
    if (!m_listAfterImg.empty())
    {
        if (m_listAfterImg.front() != nullptr)
        {
            m_listAfterImg.front()->Set_Active(true);
            CEventMgr::GetInstance()->Add_Obj(L"Bat_AfterImg", m_listAfterImg.front());
            m_listAfterImg.pop_front();
        }
    }
  
    // ����
    if (m_bAssault == false)
    {

        if (fPlayerDistance >= 5.f && m_fAccTime >= 0.5f  && fPlayerDistance <= 20.f  )
        {
            m_bAssault = true;
            dynamic_cast<CMonster*>(m_pOwner->Get_OwnerObject())->Set_MoveSpeed(30.f);
            pOwnerTransform->Set_Dir({ vDir.x, 0.f, vDir.z });
            CSoundMgr::GetInstance()->PlaySound(L"flying_swish_Big.wav", CHANNEL_ID::MONSTER_BAT, SOUND_VOLUME_MON_FLY_ATTACK);
            m_bAfterImg = true;
        }
    }

    // �ܻ�
    if(m_bAfterImg == true)
    {
        if ( m_iCreateAfterImg % 1 == 0 && m_listAfterImg.size() <= 5)
        {
           CGameObject* pAfterImg = CBat_AfterImg::Create(m_pGraphicDev, m_pOwner->Get_OwnerObject());
            m_listAfterImg.push_back(pAfterImg);

            ++m_iCreateAfterImg;

            if (m_iCreateAfterImg >= 100)
            {
                m_iCreateAfterImg = 0;
            }

        }

    }

    if (fPlayerDistance <= 5.f && m_fAccTime >= 0.7f )
    {
        pOwnerTransform->Set_Dir(vec3.zero);

        m_bAfterImg = false;

        // ���߸� �ܻ� ���� 
        if (!m_listAfterImg.empty())
        {
            for (auto iter : m_listAfterImg)
            {
                CEventMgr::GetInstance()->Delete_Obj(iter);
            }
            m_listAfterImg.clear();
        }
        m_iCreateAfterImg = 0;

    }

    pOwnerTransform->Translate(fTimeDelta * vOwnerSpeed);




#pragma region State Change


    //// BACK_ MONREST ����
    //if (vOwnerDir.z > vPlayerPos.z)
    //{
    //   // cout <<  "back monattack ����" << endl;
    //    return STATE_TYPE::BACK_MONREST;
    //}



    if (m_fAccTime >= 2.f)  // �� �� �� ���� ����
    {
        m_bAssault = false;

        dynamic_cast<CMonster*>(m_pOwner->Get_OwnerObject())->Set_MoveSpeed(3.f);
        m_fAccTime = 0.f;

        if (dynamic_cast<CPlayer*>(pPlayer)->Get_Clocking() != true)
        {
           

            // CHASE ���� ����
            if (fPlayerDistance <= m_fChaseRange)
            {
                if (vOwnerDir.z < 0)
                {
                    // cout << "Chase ����" << endl;
                    // pOwnerTransform->Set_Dir(vec3.zero);
                    return STATE_TYPE::CHASE;
                }
                else
                {
                    // cout << "Back Chase ����" << endl;
                   //  pOwnerTransform->Set_Dir(vec3.zero);
                    return STATE_TYPE::BACK_CHASE;
                }
            }
            // PATROL ���� ����
            if (fPlayerDistance >= m_fPlayerTargetRange && fOriginDistance <= m_fPatrolRange)
            {
                if (vOwnerDir.z < 0)
                {
                    //  cout << "patrol ����" << endl;
                    //  pOwnerTransform->Set_Dir(vec3.zero);
                    return STATE_TYPE::PATROL;
                }
                else
                {
                    //  cout << "Back patrol ����" << endl;
                    //  pOwnerTransform->Set_Dir(vec3.zero);
                    return STATE_TYPE::BACK_PATROL;
                }

            }

            //  ATTACK ���� ����
            if (fPlayerDistance <= m_fAttackRange)
            {
                if (vOwnerDir.z < 0)
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
        if (fOriginDistance >= m_fComeBackRange || fPlayerDistance > m_fPlayerTargetRange)
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

  

    }
    
    return STATE_TYPE::MONREST;


#pragma endregion

}

void CBatState_Rest::LateUpdate_State()
{

}

void CBatState_Rest::Render_State()
{
    
}

STATE_TYPE CBatState_Rest::Key_Input(const _float& fTimeDelta)
{
 
    return m_eState;
}

CBatState_Rest* CBatState_Rest::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
    CBatState_Rest* pInstance = new CBatState_Rest(pGraphicDev);

    if (FAILED(pInstance->Ready_State(pOwner)))
    {
        Safe_Release(pInstance);
        MSG_BOX("HedgehogState Attack Create Failed");
        return nullptr;

    }

    return pInstance;
}

void CBatState_Rest::Free()
{
    __super::Free();
}
