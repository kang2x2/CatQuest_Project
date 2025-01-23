#include "PlayerState_fDie.h"

#include "Export_Function.h"

CPlayerState_fDie::CPlayerState_fDie(LPDIRECT3DDEVICE9 pGraphicDev)
    : CState(pGraphicDev)
{
}

CPlayerState_fDie::~CPlayerState_fDie()
{
}

HRESULT CPlayerState_fDie::Ready_State(CStateMachine* pOwner)
{
    if (nullptr != pOwner)
        m_pOwner = pOwner;

    m_eState = STATE_TYPE::FRONT_DIE;

    return S_OK;
}

STATE_TYPE CPlayerState_fDie::Update_State(const _float& fTimeDelta)
{
    if (!m_bEnter)
    {
        m_bEnter = true;
    }

    if (m_pOwner->Is_AnimationEnd())
    {
        m_bEnter = false;
        static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Set_Dead(false);
        static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Set_CurHP(static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_StatInfo().fMaxHP);
        return STATE_TYPE::FRONT_WAKE;
    } 
    else
        return m_eState;
        
}

void CPlayerState_fDie::LateUpdate_State()
{
   
}

void CPlayerState_fDie::Render_State()
{
    //cout << "Áö±ÝÀº µÚÁü" << endl;
}

STATE_TYPE CPlayerState_fDie::Key_Input(const _float& fTimeDelta)
{
    return STATE_TYPE();
}

CPlayerState_fDie* CPlayerState_fDie::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
    CPlayerState_fDie* pInstance = new CPlayerState_fDie(pGraphicDev);

    if (FAILED(pInstance->Ready_State(pOwner)))
    {
        Safe_Release(pInstance);
        MSG_BOX("Player fDieState Create Failed");
        return nullptr;
    }

    return pInstance;
}

void CPlayerState_fDie::Free()
{
    __super::Free();
}
