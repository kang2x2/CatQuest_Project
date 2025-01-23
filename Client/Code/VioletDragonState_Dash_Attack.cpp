#include "VioletDragonState_Dash_Attack.h"
#include "Export_Function.h"
#include "Monster.h"
#include "Player.h"
#include "VioletDragon.h"
#include "SoundMgr.h"

CVioletDragonState_Dash_Attack::CVioletDragonState_Dash_Attack(LPDIRECT3DDEVICE9 pGraphicDev)
	:CState(pGraphicDev)
	, m_fAccTime(0.f)
{
}

CVioletDragonState_Dash_Attack::~CVioletDragonState_Dash_Attack()
{
}

HRESULT CVioletDragonState_Dash_Attack::Ready_State(CStateMachine* pOwner)
{
	if (nullptr != pOwner)
	{
		m_pOwner = pOwner;
	}
	m_eState = STATE_TYPE::BOSS_DASH_ATTACK;

	m_fAccTime = 0.f;
    
    m_bAssault = false;
    m_bDirSelect = false;

	return S_OK;
}

STATE_TYPE CVioletDragonState_Dash_Attack::Update_State(const _float& fTimeDelta)
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


    // Time
    m_fAccTime += fTimeDelta;

    //if (m_bDirSelect == false)
    //{
    //    m_bDirSelect == true;
    //    // x 이동 방향에 따라 스케일 전환 
    //    if (vOwnerPos.x <= (vPlayerPos).x && vOwnerScale.x <= 0)
    //    {
    //        pOwnerTransform->Set_Scale({ -vOwnerScale.x , vOwnerScale.y, vOwnerScale.z });
    //    }
    //    else if (vOwnerPos.x > (vPlayerPos).x && vOwnerScale.x > 0)
    //    {
    //        pOwnerTransform->Set_Scale({ -vOwnerScale.x , vOwnerScale.y, vOwnerScale.z });
    //    }
    // 
    //}
  

    if (m_bAssault == false  && pOwenrCurAnimation->Is_End())
    {
       
        if (m_fAccTime >= 0.2f )
        {
            dynamic_cast<CMonster*>(m_pOwner->Get_OwnerObject())->Set_MoveSpeed(60.f);
            pOwnerTransform->Set_Dir({ vDir.x, 0.f, vDir.z });
            CSoundMgr::GetInstance()->PlaySound(L"DragonDash.wav", CHANNEL_ID::MONSTER_BOSS_1, 0.7f);
           
            m_bAssault = true;
        }
    }
  


    pOwnerTransform->Translate(fTimeDelta * vOwnerSpeed);



    if (dynamic_cast<CMonster*>(m_pOwner->Get_OwnerObject())->Get_StatInfo().bDead == true)
    {
        return STATE_TYPE::BOSSDEAD;
    }



    //// 현재 상태의 기능
    //dynamic_cast<CAIComponent*>(pOwnerAI)->Chase_Target(&vPlayerPos, fTimeDelta, vOwnerSpeed);
    //pOwnerTransform->Translate(fTimeDelta * vOwnerSpeed *2 );
    //

#pragma region State Change

    if (fOriginDistance >= 40.f)
    {
        m_bDirSelect = false;
        m_fAccTime = 0.f;
        m_bAssault = false;
        dynamic_cast<CMonster*>(m_pOwner->Get_OwnerObject())->Set_MoveSpeed(8.f);

        return STATE_TYPE::BOSS_READY_PATTERN;
    }




    if ( m_fAccTime >=1.5f)
    {
        m_bDirSelect = false;
        m_fAccTime = 0.f;
        m_bAssault =false;
        dynamic_cast<CMonster*>(m_pOwner->Get_OwnerObject())->Set_MoveSpeed(8.f);

        return STATE_TYPE::BOSS_READY_PATTERN;
    }

    return STATE_TYPE::BOSS_DASH_ATTACK;

#pragma endregion



}

void CVioletDragonState_Dash_Attack::LateUpdate_State()
{
}

void CVioletDragonState_Dash_Attack::Render_State()
{
}

STATE_TYPE CVioletDragonState_Dash_Attack::Key_Input(const _float& fTimeDelta)
{
    return m_eState;
}

CVioletDragonState_Dash_Attack* CVioletDragonState_Dash_Attack::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
    CVioletDragonState_Dash_Attack* pInstance = new CVioletDragonState_Dash_Attack(pGraphicDev);

    if (FAILED(pInstance->Ready_State(pOwner)))
    {
        Safe_Release(pInstance);
        MSG_BOX("VioletDragonState Dash_Attack Create Failed");
        return nullptr;

    }
    return pInstance;

}

void CVioletDragonState_Dash_Attack::Free()
{
    __super::Free();
}
