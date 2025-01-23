#include "PlayerState_fRoll.h"

#include "Export_Function.h"
#include "SoundMgr.h"
#include "MoveDust.h"

CPlayerState_fRoll::CPlayerState_fRoll(LPDIRECT3DDEVICE9 pGraphicDev)
    : CState(pGraphicDev)
{
}

CPlayerState_fRoll::~CPlayerState_fRoll()
{
}

HRESULT CPlayerState_fRoll::Ready_State(CStateMachine* pOwner)
{
    if (nullptr != pOwner)
        m_pOwner = pOwner;

    m_eState = STATE_TYPE::FRONT_ROLL;

    return S_OK;
}

STATE_TYPE CPlayerState_fRoll::Update_State(const _float& fTimeDelta)
{
    if (!m_bEnter)
    {
        CGameObject* p = CMoveDust::Create(m_pGraphicDev, m_pOwner->Get_OwnerObject());
        CEventMgr::GetInstance()->Add_Obj(L"MoveDust", p);

        CSoundMgr::GetInstance()->PlaySoundW(L"roll_2.wav", CHANNEL_ID::PLAYER_0, VOLUME_PLAYER_ROLL);

        if (CInputDev::GetInstance()->Get_DIKeyState(DIK_SPACE) && CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_A) && CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_S))
        {
            m_vDir = vec3.left + vec3.back;
        }
        else if (CInputDev::GetInstance()->Get_DIKeyState(DIK_SPACE) && CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_D) && CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_S))
        {
            m_vDir = vec3.right + vec3.back;
        }
        else if (CInputDev::GetInstance()->Get_DIKeyState(DIK_SPACE) && CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_A))
        {
            m_vDir = vec3.left;
        }
        else if (CInputDev::GetInstance()->Get_DIKeyState(DIK_SPACE) && CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_D))
        {
            m_vDir = vec3.right;
        }
        else if (CInputDev::GetInstance()->Get_DIKeyState(DIK_SPACE) && CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_S))
        {
            m_vDir = vec3.back;
        }

        m_bEnter = true;
    }

    if (static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Is_LockOn())
    {
        m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(m_vDir, fTimeDelta * 30.f);
        static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Set_PlayerLook(m_vDir);
    }
    else
    {
        m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(fTimeDelta * 30.f);
    }
   

    if (m_pOwner->Is_AnimationEnd())
    {
        m_bEnter = false;
        return STATE_TYPE::FRONT_IDLE;
    } 
    else
        return m_eState;
        
}

void CPlayerState_fRoll::LateUpdate_State()
{
   
}

void CPlayerState_fRoll::Render_State()
{
    //cout << "지금은 앞구르기" << endl;
}

STATE_TYPE CPlayerState_fRoll::Key_Input(const _float& fTimeDelta)
{
    return STATE_TYPE();
}

CPlayerState_fRoll* CPlayerState_fRoll::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
    CPlayerState_fRoll* pInstance = new CPlayerState_fRoll(pGraphicDev);

    if (FAILED(pInstance->Ready_State(pOwner)))
    {
        Safe_Release(pInstance);
        MSG_BOX("Player fRollState Create Failed");
        return nullptr;
    }

    return pInstance;
}

void CPlayerState_fRoll::Free()
{
    __super::Free();
}
