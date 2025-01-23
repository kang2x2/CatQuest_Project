#include "PlayerState_fSleep.h"

#include "Export_Function.h"

CPlayerState_fSleep::CPlayerState_fSleep(LPDIRECT3DDEVICE9 pGraphicDev)
    : CState(pGraphicDev)
{
}

CPlayerState_fSleep::~CPlayerState_fSleep()
{
}

HRESULT CPlayerState_fSleep::Ready_State(CStateMachine* pOwner)
{
    if (nullptr != pOwner)
        m_pOwner = pOwner;

    m_eState = STATE_TYPE::FRONT_SLEEP;

    return S_OK;
}

STATE_TYPE CPlayerState_fSleep::Update_State(const _float& fTimeDelta)
{
    if (!m_bEnter)
    {
        m_fAccTime = 0.f;
        m_bEnter = true;
    }

    m_fAccTime += fTimeDelta;
    if (m_fAccTime >= 4.8f)
    {
        m_bEnter = false;
        return STATE_TYPE::FRONT_WAKE;
    } 
    else
        return m_eState;

    return m_eState;
        
}

void CPlayerState_fSleep::LateUpdate_State()
{
   
}

void CPlayerState_fSleep::Render_State()
{
    //cout << "지금은 잠" << endl;
}

STATE_TYPE CPlayerState_fSleep::Key_Input(const _float& fTimeDelta)
{
    return STATE_TYPE();
}

CPlayerState_fSleep* CPlayerState_fSleep::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
    CPlayerState_fSleep* pInstance = new CPlayerState_fSleep(pGraphicDev);

    if (FAILED(pInstance->Ready_State(pOwner)))
    {
        Safe_Release(pInstance);
        MSG_BOX("Player fSleepState Create Failed");
        return nullptr;
    }

    return pInstance;
}

void CPlayerState_fSleep::Free()
{
    __super::Free();
}
