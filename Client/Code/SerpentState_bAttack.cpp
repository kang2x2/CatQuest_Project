#include "SerpentState_bAttack.h"
#include "Export_Function.h"
#include "Player.h"
#include "Firework_Bullet.h"

CSerpentState_bAttack::CSerpentState_bAttack(LPDIRECT3DDEVICE9 pGraphicDev)
    : CState(pGraphicDev)
    , m_fAccTime(0.f)
{
}

CSerpentState_bAttack::~CSerpentState_bAttack()
{
}

HRESULT CSerpentState_bAttack::Ready_State(CStateMachine* pOwner)
{
    if (nullptr != pOwner)
    {
        m_pOwner = pOwner;
    }
    m_eState = STATE_TYPE::BACK_MONATTACK;



    // ���¿� ���� ���� ��ġ
    m_fPatrolRange = 1.f;  // Patrol ����
    m_fChaseRange = 10.f; // Chase ����
    m_fComeBackRange = 20.f; // ComeBack ���� - ����ġ -> �� ��ġ
    m_fPlayerTargetRange = 10.f; // ComeBack ���� - ����ġ -> �÷��̾� ��ġ
    m_fAttackRange = 20.f;  // Attack ����



    return S_OK;
}

STATE_TYPE CSerpentState_bAttack::Update_State(const _float& fTimeDelta)
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
   // pOwnerTransform->Set_Dir(vec3.zero);
   // pOwnerTransform->Translate(fTimeDelta * vOwnerSpeed);






#pragma region State Change
   // back Attack �켱����
   // attack - chase - Comeback
    m_fAccTime += fTimeDelta;
    if (m_fAccTime >= 2.f)
    {
        CGameObject* pProjectile = CFirework_Bullet::Create(m_pGraphicDev, vOwnerPos, pPlayer, m_pOwner->Get_OwnerObject());
        NULL_CHECK_RETURN(pProjectile, m_eState);
        CEventMgr::GetInstance()->Add_Obj(L"FireWork_Bullet", pProjectile);

        /*  random_device Random;
          std::mt19937 gen(Random());

          std::uniform_int_distribution<int> xDist(0, 6);

          switch (xDist(gen))
          {
          case 0:
              CSoundMgr::GetInstance()->PlaySound(L"BallSound.wav", CHANNEL_ID::MONSTER_BOSS_0, 0.5f);
              break;
          case 1:
              CSoundMgr::GetInstance()->PlaySound(L"BallSound.wav", CHANNEL_ID::MONSTER_BOSS_1, 0.5f);
              break;
          case 2:
              CSoundMgr::GetInstance()->PlaySound(L"BallSound.wav", CHANNEL_ID::MONSTER_BOSS_2, 0.5f);
              break;
          case 3:
              CSoundMgr::GetInstance()->PlaySound(L"BallSound.wav", CHANNEL_ID::MONSTER_FISH, 0.5f);
              break;
          case 4:
              CSoundMgr::GetInstance()->PlaySound(L"BallSound.wav", CHANNEL_ID::MONSTER_HEDGEHOG, 0.5f);
              break;
          case 5:
              CSoundMgr::GetInstance()->PlaySound(L"BallSound.wav", CHANNEL_ID::MONSTER_WYVERN_RED, 0.5f);
              break;
          case 6:
              CSoundMgr::GetInstance()->PlaySound(L"BallSound.wav", CHANNEL_ID::MONSTER_BAT, 0.5f);
              break;
          default:
              break;
          }*/

        m_fAccTime = 0.f;
        return STATE_TYPE::BACK_MONREST;

    }
    return STATE_TYPE::BACK_MONATTACK;

   


#pragma endregion

  
}

void CSerpentState_bAttack::LateUpdate_State()
{

}

void CSerpentState_bAttack::Render_State()
{
    
}

STATE_TYPE CSerpentState_bAttack::Key_Input(const _float& fTimeDelta)
{
 
    return m_eState;
}

CSerpentState_bAttack* CSerpentState_bAttack::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
    CSerpentState_bAttack* pInstance = new CSerpentState_bAttack(pGraphicDev);

    if (FAILED(pInstance->Ready_State(pOwner)))
    {
        Safe_Release(pInstance);
        MSG_BOX("BatState Attack Create Failed");
        return nullptr;

    }

    return pInstance;
}

void CSerpentState_bAttack::Free()
{
    __super::Free();
}
