#include "DragonState_bIdle.h"
#include "Export_Function.h"

CDragonState_bIdle::CDragonState_bIdle(LPDIRECT3DDEVICE9 pGraphicDev)
    :CState(pGraphicDev)
{
}

CDragonState_bIdle::~CDragonState_bIdle()
{
}

HRESULT CDragonState_bIdle::Ready_State(CStateMachine* pOwner)
{
    if (nullptr != pOwner)
    {
        m_pOwner = pOwner;
    }

    m_eState = STATE_TYPE::BACK_IDLE;


    return S_OK;
}

STATE_TYPE CDragonState_bIdle::Update_State(const _float& fTimeDelta)
{

    // 임시
    STATE_TYPE eState = Key_Input(fTimeDelta);

    return eState;
}

void CDragonState_bIdle::LateUpdate_State()
{
   
}

void CDragonState_bIdle::Render_State()
{
    //cout << "Back_Idle" << endl;
}

STATE_TYPE CDragonState_bIdle::Key_Input(const _float& fTimeDelta)
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
        return STATE_TYPE::BACK_ATTACK;
    }


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
            pDragonTransform->Set_Scale({ 12.f, 12.f, 2.f });
           
        }
        else
        {
            pDragonTransform->Set_Scale({ -12.f, 12.f, 2.f });

        }
        return STATE_TYPE::BACK_IDLE;
    }







    return m_eState;
}

CDragonState_bIdle* CDragonState_bIdle::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
    CDragonState_bIdle* pInstance = new CDragonState_bIdle(pGraphicDev);

    if (FAILED(pInstance->Ready_State(pOwner)))
    {
        Safe_Release(pInstance);
        MSG_BOX("DragonState bIdleState Create Failed");
        return nullptr;

    }

    return pInstance;
}

void CDragonState_bIdle::Free()
{
    __super::Free();
}
