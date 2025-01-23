#include "VioletDragonState_FullDown_Fly.h"
#include "Export_Function.h"
#include "Monster.h"
#include "Player.h"
#include "VioletDragon.h"
CVioletDragonState_FullDown_Fly::CVioletDragonState_FullDown_Fly(LPDIRECT3DDEVICE9 pGraphicDev)
	:CState(pGraphicDev)
	, m_fAccTime(0.f)

{
}

CVioletDragonState_FullDown_Fly::~CVioletDragonState_FullDown_Fly()
{
}

HRESULT CVioletDragonState_FullDown_Fly::Ready_State(CStateMachine* pOwner)
{
    if (nullptr != pOwner)
    {
        m_pOwner = pOwner;
    }
    m_eState = STATE_TYPE::BOSS_FULLDOWN_FLY;
    
    m_fAccTime = 0.f;
    m_bSound = false;
    

	return S_OK;
}

STATE_TYPE CVioletDragonState_FullDown_Fly::Update_State(const _float& fTimeDelta)
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



    if (m_bSound == false && pOwenrCurAnimation->Get_CurFrame() == 8)
    {
        m_bSound = true;
        CSoundMgr::GetInstance()->PlaySound(L"map_transition_fast2.wav", CHANNEL_ID::MONSTER_BOSS_2, 1.f);
    }

    m_fAccTime += fTimeDelta;
    
   // pOwnerTransform->Set_Pos(_vec3{ vOwnerPos.x, 100.f , vOwnerPos.z });

  /*  if (m_fAccTime >= 1.5)
    {
        pOwnerTransform->Set_Dir(_vec3{ 0.f, 1.f, 0.f });
    }
    pOwnerTransform->Translate(fTimeDelta * vOwnerSpeed);*/


#pragma region State Change
    // FullDown 상태는 FullDown Down 상태로만 전이 한다

    // State Change 

    if (m_fAccTime >= 4.f)
    {
        CCameraMgr::GetInstance()->Start_Action(CAMERA_ACTION::BOSS_SKILL_IN);
        m_fAccTime = 0.f;
        return STATE_TYPE::BOSS_FULLDOWN_DOWN;
    }
    return STATE_TYPE::BOSS_FULLDOWN_FLY;
#pragma endregion
	
}

void CVioletDragonState_FullDown_Fly::LateUpdate_State()
{
}

void CVioletDragonState_FullDown_Fly::Render_State()
{
}

STATE_TYPE CVioletDragonState_FullDown_Fly::Key_Input(const _float& fTimeDelta)
{
    return m_eState;
}

CVioletDragonState_FullDown_Fly* CVioletDragonState_FullDown_Fly::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{

    CVioletDragonState_FullDown_Fly* pInstance = new CVioletDragonState_FullDown_Fly(pGraphicDev);

    if (FAILED(pInstance->Ready_State(pOwner)))
    {
        Safe_Release(pInstance);
        MSG_BOX("VioletDragonState Fly Create Failed");
        return nullptr;

    }

    return pInstance;
}

void CVioletDragonState_FullDown_Fly::Free()
{

	__super::Free();

}
