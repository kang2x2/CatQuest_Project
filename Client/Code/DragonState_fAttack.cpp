#include "DragonState_fAttack.h"
#include "Export_Function.h"

CDragonState_fAttack::CDragonState_fAttack(LPDIRECT3DDEVICE9 pGraphicDev)
	:CState(pGraphicDev)
{
}

CDragonState_fAttack::~CDragonState_fAttack()
{
}

HRESULT CDragonState_fAttack::Ready_State(CStateMachine* pOwner)
{
    if (nullptr != pOwner)
    {
        m_pOwner = pOwner;
    }

    m_eState = STATE_TYPE::FRONT_ATTACK;

    return S_OK;
}

STATE_TYPE CDragonState_fAttack::Update_State(const _float& fTimeDelta)
{
    //���� ������Ʈ ����

    // �ӽ�
    STATE_TYPE eState = Key_Input(fTimeDelta);



    if (m_pOwner->Is_AnimationEnd())
    {
        return STATE_TYPE::FRONT_IDLE;
    }
       

 
    return eState;
}

void CDragonState_fAttack::LateUpdate_State()
{



}

void CDragonState_fAttack::Render_State()
{

    // cout << "Attack" << endl;
}

STATE_TYPE CDragonState_fAttack::Key_Input(const _float& fTimeDelta)
{

    // �ӽ�
    if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_1))
    {
        return STATE_TYPE::FRONT_ATTACK;
    }

    return m_eState;
}

CDragonState_fAttack* CDragonState_fAttack::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
    CDragonState_fAttack* pInstance = new CDragonState_fAttack(pGraphicDev);

    if (FAILED(pInstance->Ready_State(pOwner)))
    {
        Safe_Release(pInstance);
        MSG_BOX("DragonState fAttackState Create Failed");
        return nullptr;

    }

    return pInstance;
}

void CDragonState_fAttack::Free()
{
    __super::Free();
}
