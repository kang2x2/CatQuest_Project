#include "PlayerState_fWake.h"

#include "Export_Function.h"

CPlayerState_fWake::CPlayerState_fWake(LPDIRECT3DDEVICE9 pGraphicDev)
    : CState(pGraphicDev)
{
}

CPlayerState_fWake::~CPlayerState_fWake()
{
}

HRESULT CPlayerState_fWake::Ready_State(CStateMachine* pOwner)
{
    if (nullptr != pOwner)
        m_pOwner = pOwner;

    m_eState = STATE_TYPE::FRONT_WAKE;

    return S_OK;
}

STATE_TYPE CPlayerState_fWake::Update_State(const _float& fTimeDelta)
{
    if (!m_bEnter)
    {
        m_bEnter = true;
    }

    if (m_pOwner->Is_AnimationEnd())
    {
        m_bEnter = false;
        return STATE_TYPE::FRONT_IDLE;
    } 
    else
        return m_eState;
        
}

void CPlayerState_fWake::LateUpdate_State()
{
   
}

void CPlayerState_fWake::Render_State()
{
    //cout << "지금은 일어나기" << endl;
}

STATE_TYPE CPlayerState_fWake::Key_Input(const _float& fTimeDelta)
{
    return STATE_TYPE();
}

CPlayerState_fWake* CPlayerState_fWake::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
    CPlayerState_fWake* pInstance = new CPlayerState_fWake(pGraphicDev);

    if (FAILED(pInstance->Ready_State(pOwner)))
    {
        Safe_Release(pInstance);
        MSG_BOX("Player fWakeState Create Failed");
        return nullptr;
    }

    return pInstance;
}

void CPlayerState_fWake::Free()
{
    __super::Free();
}
