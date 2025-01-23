#include "DragonState_fIdle.h"
#include "Export_Function.h"

CDragonState_fIdle::CDragonState_fIdle(LPDIRECT3DDEVICE9 pGraphicDev)
    :CState(pGraphicDev)
{
}

CDragonState_fIdle::~CDragonState_fIdle()
{
}

HRESULT CDragonState_fIdle::Ready_State(CStateMachine* pOwner)
{
    if (nullptr != pOwner)
    {
        m_pOwner = pOwner;
    }

    m_eState = STATE_TYPE::FRONT_IDLE;

    return S_OK;
}

STATE_TYPE CDragonState_fIdle::Update_State(const _float& fTimeDelta)
{
    //상태 업데이트 조건
   

    // 임시
    STATE_TYPE eState = Key_Input(fTimeDelta);

 

    return eState;
}

void CDragonState_fIdle::LateUpdate_State()
{
}

void CDragonState_fIdle::Render_State()
{
    //cout << "Idle" << endl;
}

STATE_TYPE CDragonState_fIdle::Key_Input(const _float& fTimeDelta)
{
    // 사용안함
   

    // State Test

    CTransform* pPlayerTransform = dynamic_cast<CTransform*>(Engine::Get_Component(OBJ_TYPE::PLAYER, L"Player", COMPONENT_TYPE::TRANSFORM, COMPONENTID::ID_DYNAMIC));
    _vec3 PlayerPos = pPlayerTransform->Get_Info(INFO_POS);
    

    CTransform* pDragonTransform = dynamic_cast<CTransform*>(Engine::Get_Component(OBJ_TYPE::MONSTER, L"Monster_Dragon", COMPONENT_TYPE::TRANSFORM, COMPONENTID::ID_DYNAMIC));
    _vec3 DragonPos = pDragonTransform->Get_Info(INFO_POS);
  

    _float fDistance = D3DXVec3Length(&(PlayerPos - DragonPos));


    if (fDistance <= 15.f)
    {
        return STATE_TYPE::FRONT_ATTACK;
    }
    ////////////////////////////////////////////////// 플레이어 가까워지면 공격

    // State Test 2

    if (PlayerPos.z < DragonPos.z)
    {
        if (PlayerPos.x <= DragonPos.x)
        {
            pDragonTransform->Set_Scale({ -12.f, 12.f, 2.f });
        }
        else
        {
            pDragonTransform->Set_Scale({ 12.f, 12.f, 2.f });
        }
        return STATE_TYPE::FRONT_IDLE;
    }
    

    if (PlayerPos.z >= DragonPos.z)
    {
        if (PlayerPos.x <= DragonPos.x)
        {
            pDragonTransform->Set_Scale({ -12.f, 12.f, 2.f });
        }
        else
        {
            pDragonTransform->Set_Scale({ 12.f, 12.f, 2.f });
        }
        return STATE_TYPE::BACK_IDLE;
    }




    return m_eState;
}

CDragonState_fIdle* CDragonState_fIdle::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
    CDragonState_fIdle* pInstance = new CDragonState_fIdle(pGraphicDev);

    if (FAILED(pInstance->Ready_State(pOwner)))
    {
        Safe_Release(pInstance);
        MSG_BOX("DragonState fIdleState Create Failed");
        return nullptr;

    }

    return pInstance;
}

void CDragonState_fIdle::Free()
{
    __super::Free();
}
