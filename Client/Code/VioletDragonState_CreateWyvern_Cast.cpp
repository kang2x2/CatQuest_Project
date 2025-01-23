#include "VioletDragonState_CreateWyvern_Cast.h"
#include "Export_Function.h"
#include "Monster.h"
#include "Player.h"
#include "EventMgr.h"
#include "WyvernRed.h"
#include "Hedgehog.h"
#include "FoxFire.h"
#include "VioletDragon.h"
CVioletDragonState_CreateWyvern_Cast::CVioletDragonState_CreateWyvern_Cast(LPDIRECT3DDEVICE9 pGraphicDev)
	:CState(pGraphicDev)
	, m_fAccTime(0.f)

{
}

CVioletDragonState_CreateWyvern_Cast::~CVioletDragonState_CreateWyvern_Cast()
{
}

HRESULT CVioletDragonState_CreateWyvern_Cast::Ready_State(CStateMachine* pOwner)
{
    if (nullptr != pOwner)
    {
        m_pOwner = pOwner;
    }
    m_eState = STATE_TYPE::BOSS_CREATE_CAST;
    
    m_fAccTime = 0.f;
    
    m_bInit = false;

    m_bCreateWyvern1 = false;
    m_bCreateWyvern2 = false;

    m_bCreateWyvern3 = false;
    m_bCreateWyvern4 = false;
    m_bCreateWyvern5 = false;
    m_bCreateWyvern6 = false;

    m_bCreateWyvern7 = false;
    m_bCreateWyvern8 = false;
    m_bCreateWyvern9 = false;
    m_bCreateWyvern10 = false; 

    vCreatePosition = vec3.zero;
    vCreateBossPosition = vec3.zero;

	return S_OK;
}

STATE_TYPE CVioletDragonState_CreateWyvern_Cast::Update_State(const _float& fTimeDelta)
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

    STATINFO OwnerStat = dynamic_cast<CMonster*>(m_pOwner->Get_OwnerObject())->Get_StatInfo();



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

    if (m_bInit == false)
    {
        m_bInit = true;
        vCreatePosition = vPlayerPos;
        vCreateBossPosition = vOwnerPos;
    }

 
  





    // Time 
    m_fAccTime += fTimeDelta;
    
    if(fPlayerDistance <= 100.f && m_fAccTime >= 2.f)
    { 
        // Very Near 1
        if (m_bCreateWyvern1 == false )
        {
            CGameObject* m_pCreateWyvern1 = CWyvernRed::Create(m_pGraphicDev);
            _vec3 CreateWyvernScale = m_pCreateWyvern1->Get_Transform()->Get_Scale();
            m_pCreateWyvern1->Get_Transform()->Set_Pos(_vec3{ vCreatePosition.x +5.f ,CreateWyvernScale.y ,vCreatePosition.z });
            CEventMgr::GetInstance()->Add_Obj(L"Boss_Create_Wyvern1", m_pCreateWyvern1);
            m_bCreateWyvern1 = true;   
        }

        // Very Near 2
        if (m_bCreateWyvern2 == false)
        {
            CGameObject* m_pCreateWyvern2 = CWyvernRed::Create(m_pGraphicDev);
            _vec3 CreateWyvernScale = m_pCreateWyvern2->Get_Transform()->Get_Scale();
            m_pCreateWyvern2->Get_Transform()->Set_Pos(_vec3{ vCreatePosition.x - 5.f ,CreateWyvernScale.y ,vCreatePosition.z });
            CEventMgr::GetInstance()->Add_Obj(L"Boss_Create_Wyvern2", m_pCreateWyvern2);
            m_bCreateWyvern2 = true;
        }


        // Near 1
        if (m_bCreateWyvern3 == false)
        {
            CGameObject* m_pCreateWyvern3 = CWyvernRed::Create(m_pGraphicDev);
            _vec3 CreateWyvernScale = m_pCreateWyvern3->Get_Transform()->Get_Scale();
            m_pCreateWyvern3->Get_Transform()->Set_Pos(_vec3{ vCreatePosition.x - 10.f ,CreateWyvernScale.y ,vCreatePosition.z + 10.f });
            CEventMgr::GetInstance()->Add_Obj(L"Boss_Create_Wyvern3", m_pCreateWyvern3);
            m_bCreateWyvern3 = true;
        }

        // Near 2
        if (m_bCreateWyvern4 == false)
        {
            CGameObject* m_pCreateWyvern4= CWyvernRed::Create(m_pGraphicDev);
            _vec3 CreateWyvernScale = m_pCreateWyvern4->Get_Transform()->Get_Scale();
            m_pCreateWyvern4->Get_Transform()->Set_Pos(_vec3{ vCreatePosition.x +10.f ,CreateWyvernScale.y ,vCreatePosition.z  +10.f});
            CEventMgr::GetInstance()->Add_Obj(L"Boss_Create_Wyvern4", m_pCreateWyvern4);
            m_bCreateWyvern4 = true;
        }


        // Near 3
        if (m_bCreateWyvern5 == false)
        {
            CGameObject* m_pCreateWyvern5 = CWyvernRed::Create(m_pGraphicDev);
            _vec3 CreateWyvernScale = m_pCreateWyvern5->Get_Transform()->Get_Scale();
            m_pCreateWyvern5->Get_Transform()->Set_Pos(_vec3{ vCreatePosition.x - 10.f ,CreateWyvernScale.y ,vCreatePosition.z -10.f });
            CEventMgr::GetInstance()->Add_Obj(L"Boss_Create_Wyvern5", m_pCreateWyvern5);
            m_bCreateWyvern5 = true;
        }


        // Near 4
        if (m_bCreateWyvern6 == false)
        {
            CGameObject* m_pCreateWyvern6 = CWyvernRed::Create(m_pGraphicDev);
            _vec3 CreateWyvernScale = m_pCreateWyvern6->Get_Transform()->Get_Scale();
            m_pCreateWyvern6->Get_Transform()->Set_Pos(_vec3{ vCreatePosition.x +10.f ,CreateWyvernScale.y ,vCreatePosition.z  -10.f});
            CEventMgr::GetInstance()->Add_Obj(L"Boss_Create_Wyvern6", m_pCreateWyvern6);
            m_bCreateWyvern6 = true;
        }


        // Boss Near 1
        if (m_bCreateWyvern7 == false)
        {
            CGameObject* m_pCreateWyvern7 = CWyvernRed::Create(m_pGraphicDev);
            _vec3 CreateWyvernScale = m_pCreateWyvern7->Get_Transform()->Get_Scale();
            m_pCreateWyvern7->Get_Transform()->Set_Pos(_vec3{ vCreateBossPosition.x - 5.f ,CreateWyvernScale.y ,vCreateBossPosition.z -5.f });
            CEventMgr::GetInstance()->Add_Obj(L"Boss_Create_Wyvern7", m_pCreateWyvern7);
            m_bCreateWyvern7 = true;
        }

        //  Boss Near 2
        if (m_bCreateWyvern8 == false)
        {
            CGameObject* m_pCreateWyvern8 = CWyvernRed::Create(m_pGraphicDev);
            _vec3 CreateWyvernScale = m_pCreateWyvern8->Get_Transform()->Get_Scale();
            m_pCreateWyvern8->Get_Transform()->Set_Pos(_vec3{ vCreateBossPosition.x - 5.f ,CreateWyvernScale.y ,vCreateBossPosition.z +5.f});
            CEventMgr::GetInstance()->Add_Obj(L"Boss_Create_Wyvern8", m_pCreateWyvern8);
            m_bCreateWyvern8 = true;
        }


        // Boss Near 3
        if (m_bCreateWyvern9 == false)
        {
            CGameObject* m_pCreateWyvern9 = CWyvernRed::Create(m_pGraphicDev);
            _vec3 CreateWyvernScale = m_pCreateWyvern9->Get_Transform()->Get_Scale();
            m_pCreateWyvern9->Get_Transform()->Set_Pos(_vec3{ vCreateBossPosition.x +5.f ,CreateWyvernScale.y ,vCreateBossPosition.z  - 5.f});
            CEventMgr::GetInstance()->Add_Obj(L"Boss_Create_Wyvern9", m_pCreateWyvern9);
            m_bCreateWyvern9 = true;
        }


        // Boss Near 4
        if (m_bCreateWyvern10 == false)
        {
            CGameObject* m_pCreateWyvern10 = CWyvernRed::Create(m_pGraphicDev);
            _vec3 CreateWyvernScale = m_pCreateWyvern10->Get_Transform()->Get_Scale();
            m_pCreateWyvern10->Get_Transform()->Set_Pos(_vec3{ vCreateBossPosition.x + 5.f ,CreateWyvernScale.y ,vCreateBossPosition.z +5.f});
            CEventMgr::GetInstance()->Add_Obj(L"Boss_Create_Wyvern10", m_pCreateWyvern10);
            m_bCreateWyvern10 = true;
        }


    }

#pragma region State Change


    if (dynamic_cast<CMonster*>(m_pOwner->Get_OwnerObject())->Get_StatInfo().bDead == true)
    {
        return STATE_TYPE::BOSSDEAD;
    }




    if (m_pOwner->Get_Animator()->Get_CurAniamtion()->Is_End())
    {

        return STATE_TYPE::BOSS_CREATE_WYVERN;
    }

   return STATE_TYPE::BOSS_CREATE_CAST;

#pragma endregion
	
}

void CVioletDragonState_CreateWyvern_Cast::LateUpdate_State()
{
 
}

void CVioletDragonState_CreateWyvern_Cast::Render_State()
{
 
}

STATE_TYPE CVioletDragonState_CreateWyvern_Cast::Key_Input(const _float& fTimeDelta)
{

    return m_eState;
}

CVioletDragonState_CreateWyvern_Cast* CVioletDragonState_CreateWyvern_Cast::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{

    CVioletDragonState_CreateWyvern_Cast* pInstance = new CVioletDragonState_CreateWyvern_Cast(pGraphicDev);

    if (FAILED(pInstance->Ready_State(pOwner)))
    {
        Safe_Release(pInstance);
        MSG_BOX("VioletDragonState CreateWyvern Create Failed");
        return nullptr;

    }

    return pInstance;
}

void CVioletDragonState_CreateWyvern_Cast::Free()
{

	__super::Free();

}
