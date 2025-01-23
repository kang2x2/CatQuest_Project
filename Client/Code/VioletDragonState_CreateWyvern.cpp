#include "VioletDragonState_CreateWyvern.h"
#include "Export_Function.h"
#include "Monster.h"
#include "Player.h"
#include "EventMgr.h"
#include "FoxFire.h"
#include "VioletDragon.h"


// Create Monster
#include "Hedgehog.h"
#include "WyvernRed.h"
#include "Bat.h"
#include "Ram.h"
#include "Wyvern.h"
#include "Fox.h"



CVioletDragonState_CreateWyvern::CVioletDragonState_CreateWyvern(LPDIRECT3DDEVICE9 pGraphicDev)
	:CState(pGraphicDev)
	, m_fAccTime(0.f)

{
}

CVioletDragonState_CreateWyvern::~CVioletDragonState_CreateWyvern()
{
}

HRESULT CVioletDragonState_CreateWyvern::Ready_State(CStateMachine* pOwner)
{
    if (nullptr != pOwner)
    {
        m_pOwner = pOwner;
    }
    m_eState = STATE_TYPE::BOSS_CREATE_WYVERN;
    
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

    m_bCreateWyvern11 = false;
    m_bCreateWyvern12 = false;


    // Other
    m_Monster1 = false;
    m_Monster2 = false;

    m_Monster3 = false;
    m_Monster4 = false;

    m_Monster5 = false;
    m_Monster6 = false;

    m_Monster7 = false;
    m_Monster8 = false;



    vCreatePosition = vec3.zero;
    vCreateBossPosition = vec3.zero;

	return S_OK;
}

STATE_TYPE CVioletDragonState_CreateWyvern::Update_State(const _float& fTimeDelta)
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

    STATINFO OwnerStat = dynamic_cast<CMonster*>(m_pOwner->Get_OwnerObject())->Get_StatInfo();
 


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

 

    // x 이동 방향에 따라 스케일 전환 
    if (vOwnerPos.x <= (vPlayerPos).x && vOwnerScale.x <= 0)
    {
        pOwnerTransform->Set_Scale({ -vOwnerScale.x , vOwnerScale.y, vOwnerScale.z });
    }
    else if (vOwnerPos.x > (vPlayerPos).x && vOwnerScale.x > 0)
    {
        pOwnerTransform->Set_Scale({ -vOwnerScale.x , vOwnerScale.y, vOwnerScale.z });
    }
    

    // Time 
    m_fAccTime += fTimeDelta;
    
    if( m_fAccTime >= 1.5f)
    { 
        // Very Near 1
        if (m_bCreateWyvern1 == false )
        {
            CGameObject* m_pCreateWyvern1 = CWyvernRed::Create(m_pGraphicDev);
            _vec3 CreateWyvernScale = m_pCreateWyvern1->Get_Transform()->Get_Scale();
            m_pCreateWyvern1->Get_Transform()->Set_Pos(_vec3{ vCreatePosition.x +10.f ,CreateWyvernScale.y ,vCreatePosition.z });
            CEventMgr::GetInstance()->Add_Obj(L"Boss_Create_Wyvern1", m_pCreateWyvern1);
            m_bCreateWyvern1 = true;   
        }

        // Very Near 2
        if (m_bCreateWyvern2 == false)
        {
            CGameObject* m_pCreateWyvern2 = CWyvernRed::Create(m_pGraphicDev);
            _vec3 CreateWyvernScale = m_pCreateWyvern2->Get_Transform()->Get_Scale();
            m_pCreateWyvern2->Get_Transform()->Set_Pos(_vec3{ vCreatePosition.x - 10.f ,CreateWyvernScale.y ,vCreatePosition.z });
            CEventMgr::GetInstance()->Add_Obj(L"Boss_Create_Wyvern2", m_pCreateWyvern2);
            m_bCreateWyvern2 = true;
        }

        ///////////////////////
        
        // Near 1
        if (m_bCreateWyvern3 == false)
        {
            CGameObject* m_pCreateWyvern3 = CWyvernRed::Create(m_pGraphicDev);
            _vec3 CreateWyvernScale = m_pCreateWyvern3->Get_Transform()->Get_Scale();
            m_pCreateWyvern3->Get_Transform()->Set_Pos(_vec3{ vCreatePosition.x - 15.f ,CreateWyvernScale.y ,vCreatePosition.z + 15.f });
            CEventMgr::GetInstance()->Add_Obj(L"Boss_Create_Wyvern3", m_pCreateWyvern3);
            m_bCreateWyvern3 = true;
        }

        // Near 2
        if (m_bCreateWyvern4 == false)
        {
            CGameObject* m_pCreateWyvern4= CWyvernRed::Create(m_pGraphicDev);
            _vec3 CreateWyvernScale = m_pCreateWyvern4->Get_Transform()->Get_Scale();
            m_pCreateWyvern4->Get_Transform()->Set_Pos(_vec3{ vCreatePosition.x +15.f ,CreateWyvernScale.y ,vCreatePosition.z  +15.f});
            CEventMgr::GetInstance()->Add_Obj(L"Boss_Create_Wyvern4", m_pCreateWyvern4);
            m_bCreateWyvern4 = true;
        }


        // Near 3
        if (m_bCreateWyvern5 == false)
        {
            CGameObject* m_pCreateWyvern5 = CWyvernRed::Create(m_pGraphicDev);
            _vec3 CreateWyvernScale = m_pCreateWyvern5->Get_Transform()->Get_Scale();
            m_pCreateWyvern5->Get_Transform()->Set_Pos(_vec3{ vCreatePosition.x - 15.f ,CreateWyvernScale.y ,vCreatePosition.z -15.f });
            CEventMgr::GetInstance()->Add_Obj(L"Boss_Create_Wyvern5", m_pCreateWyvern5);
            m_bCreateWyvern5 = true;
        }


        // Near 4
        if (m_bCreateWyvern6 == false)
        {
            CGameObject* m_pCreateWyvern6 = CWyvernRed::Create(m_pGraphicDev);
            _vec3 CreateWyvernScale = m_pCreateWyvern6->Get_Transform()->Get_Scale();
            m_pCreateWyvern6->Get_Transform()->Set_Pos(_vec3{ vCreatePosition.x +15.f ,CreateWyvernScale.y ,vCreatePosition.z  -15.f});
            CEventMgr::GetInstance()->Add_Obj(L"Boss_Create_Wyvern6", m_pCreateWyvern6);
            m_bCreateWyvern6 = true;
        }


        //  Normal 1
        if (m_bCreateWyvern7 == false)
        {
            CGameObject* m_pCreateWyvern7 = CWyvernRed::Create(m_pGraphicDev);
            _vec3 CreateWyvernScale = m_pCreateWyvern7->Get_Transform()->Get_Scale();
            m_pCreateWyvern7->Get_Transform()->Set_Pos(_vec3{ vCreatePosition.x - 20.f ,CreateWyvernScale.y ,vCreatePosition.z -20.f });
            CEventMgr::GetInstance()->Add_Obj(L"Boss_Create_Wyvern7", m_pCreateWyvern7);
            m_bCreateWyvern7 = true;
        }

        //   Normal 2
        if (m_bCreateWyvern8 == false)
        {
            CGameObject* m_pCreateWyvern8 = CWyvernRed::Create(m_pGraphicDev);
            _vec3 CreateWyvernScale = m_pCreateWyvern8->Get_Transform()->Get_Scale();
            m_pCreateWyvern8->Get_Transform()->Set_Pos(_vec3{ vCreatePosition.x - 20.f ,CreateWyvernScale.y ,vCreatePosition.z +20.f});
            CEventMgr::GetInstance()->Add_Obj(L"Boss_Create_Wyvern8", m_pCreateWyvern8);
            m_bCreateWyvern8 = true;
        }


        // Normal 3
        if (m_bCreateWyvern9 == false)
        {
            CGameObject* m_pCreateWyvern9 = CWyvernRed::Create(m_pGraphicDev);
            _vec3 CreateWyvernScale = m_pCreateWyvern9->Get_Transform()->Get_Scale();
            m_pCreateWyvern9->Get_Transform()->Set_Pos(_vec3{ vCreatePosition.x +20.f ,CreateWyvernScale.y ,vCreatePosition.z  - 20.f});
            CEventMgr::GetInstance()->Add_Obj(L"Boss_Create_Wyvern9", m_pCreateWyvern9);
            m_bCreateWyvern9 = true;
        }


        //  Normal 4
        if (m_bCreateWyvern10 == false)
        {
            CGameObject* m_pCreateWyvern10 = CWyvernRed::Create(m_pGraphicDev);
            _vec3 CreateWyvernScale = m_pCreateWyvern10->Get_Transform()->Get_Scale();
            m_pCreateWyvern10->Get_Transform()->Set_Pos(_vec3{ vCreatePosition.x + 20.f ,CreateWyvernScale.y ,vCreatePosition.z +20.f});
            CEventMgr::GetInstance()->Add_Obj(L"Boss_Create_Wyvern10", m_pCreateWyvern10);
            m_bCreateWyvern10 = true;
        }


        /////////////////


        // far 1
        if (m_bCreateWyvern11 == false)
        {
            CGameObject* m_pCreateWyvern11 = CWyvernRed::Create(m_pGraphicDev);
            _vec3 CreateWyvernScale = m_pCreateWyvern11->Get_Transform()->Get_Scale();
            m_pCreateWyvern11->Get_Transform()->Set_Pos(_vec3{ vCreatePosition.x -25.f ,CreateWyvernScale.y ,vCreatePosition.z });
            CEventMgr::GetInstance()->Add_Obj(L"Boss_Create_Wyvern11", m_pCreateWyvern11);
            m_bCreateWyvern11 = true;
        }


        // far 2
        if (m_bCreateWyvern12 == false)
        {
            CGameObject* m_pCreateWyvern12 = CWyvernRed::Create(m_pGraphicDev);
            _vec3 CreateWyvernScale = m_pCreateWyvern12->Get_Transform()->Get_Scale();
            m_pCreateWyvern12->Get_Transform()->Set_Pos(_vec3{ vCreatePosition.x + 25.f ,CreateWyvernScale.y ,vCreatePosition.z });
            CEventMgr::GetInstance()->Add_Obj(L"Boss_Create_Wyvern12", m_pCreateWyvern12);
            m_bCreateWyvern12 = true;
        }
        



        // Other Monster 
        if (m_Monster1 == false)      // Hedgehog
        {
            CGameObject* m_pCreateMon1 = CHedgehog::Create(m_pGraphicDev);
            _vec3 CreateMonScale = m_pCreateMon1->Get_Transform()->Get_Scale();
            m_pCreateMon1->Get_Transform()->Set_Pos(_vec3{ vCreatePosition.x ,CreateMonScale.y ,vCreatePosition.z -10.f });
            CEventMgr::GetInstance()->Add_Obj(L"Boss_Create_Monster1", m_pCreateMon1);
            m_Monster1 = true;
        }

        if (m_Monster2 == false)  // Bat
        {
            CGameObject* m_pCreateMon2 = CBat::Create(m_pGraphicDev);
            _vec3 CreateMonScale = m_pCreateMon2->Get_Transform()->Get_Scale();
            m_pCreateMon2->Get_Transform()->Set_Pos(_vec3{ vCreatePosition.x ,CreateMonScale.y ,vCreatePosition.z + 10.f });
            CEventMgr::GetInstance()->Add_Obj(L"Boss_Create_Monster2", m_pCreateMon2);
            m_Monster2 = true;
        }

        if (m_Monster3 == false) // Wyvern
        {
            CGameObject* m_pCreateMon3 = CWyvern::Create(m_pGraphicDev);
            _vec3 CreateMonScale = m_pCreateMon3->Get_Transform()->Get_Scale();
            m_pCreateMon3->Get_Transform()->Set_Pos(_vec3{ vCreatePosition.x - 18.f ,CreateMonScale.y ,vCreatePosition.z + 10.f });
            CEventMgr::GetInstance()->Add_Obj(L"Boss_Create_Monster3", m_pCreateMon3);
            m_Monster3 = true;
        }

        if (m_Monster4 == false)
        {
            CGameObject* m_pCreateMon4 = CWyvern::Create(m_pGraphicDev);
            _vec3 CreateMonScale = m_pCreateMon4->Get_Transform()->Get_Scale();
            m_pCreateMon4->Get_Transform()->Set_Pos(_vec3{ vCreatePosition.x +18.f ,CreateMonScale.y ,vCreatePosition.z + 10.f });
            CEventMgr::GetInstance()->Add_Obj(L"Boss_Create_Monster4", m_pCreateMon4);
            m_Monster4 = true;
        }

        if (m_Monster5 == false)
        {
            CGameObject* m_pCreateMon5 = CRam::Create(m_pGraphicDev);
            _vec3 CreateMonScale = m_pCreateMon5->Get_Transform()->Get_Scale();
            m_pCreateMon5->Get_Transform()->Set_Pos(_vec3{ vCreatePosition.x - 18.f ,CreateMonScale.y ,vCreatePosition.z -10.f });
            CEventMgr::GetInstance()->Add_Obj(L"Boss_Create_Wyvern12", m_pCreateMon5);
            m_Monster5 = true;
        }

        if (m_Monster6 == false)
        {
            CGameObject* m_pCreateMon6 = CRam::Create(m_pGraphicDev);
            _vec3 CreateMonScale = m_pCreateMon6->Get_Transform()->Get_Scale();
            m_pCreateMon6->Get_Transform()->Set_Pos(_vec3{ vCreatePosition.x +18.f ,CreateMonScale.y ,vCreatePosition.z  -10.f });
            CEventMgr::GetInstance()->Add_Obj(L"Boss_Create_Wyvern12", m_pCreateMon6);
            m_Monster6 = true;
        }

        if (m_Monster7 == false)
        {
            CGameObject* m_pCreateMon7 = CFox::Create(m_pGraphicDev);
            _vec3 CreateMonScale = m_pCreateMon7->Get_Transform()->Get_Scale();
            m_pCreateMon7->Get_Transform()->Set_Pos(_vec3{ vCreatePosition.x ,CreateMonScale.y ,vCreatePosition.z + 25.f });
            CEventMgr::GetInstance()->Add_Obj(L"Boss_Create_Wyvern12", m_pCreateMon7);
            m_Monster7 = true;
        }

        if (m_Monster8 == false)
        {
            CGameObject* m_pCreateMon8 = CFox::Create(m_pGraphicDev);
            _vec3 CreateMonScale = m_pCreateMon8->Get_Transform()->Get_Scale();
            m_pCreateMon8->Get_Transform()->Set_Pos(_vec3{ vCreatePosition.x ,CreateMonScale.y ,vCreatePosition.z -25.f });
            CEventMgr::GetInstance()->Add_Obj(L"Boss_Create_Wyvern12", m_pCreateMon8);
            m_Monster8 = true;
        }



    }

#pragma region State Change
   
    if (dynamic_cast<CMonster*>(m_pOwner->Get_OwnerObject())->Get_StatInfo().bDead == true)
    {
        return STATE_TYPE::BOSSDEAD;
    }


    if (m_fAccTime >= 3.f )
    {
        m_fAccTime = 0.f;
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

        m_bCreateWyvern11 = false;
        m_bCreateWyvern12 = false;
 

        //Other
        m_Monster1 = false;
        m_Monster2 = false;
        m_Monster3 = false;
        m_Monster4 = false;
        m_Monster5 = false;
        m_Monster6 = false;
        m_Monster7 = false;
        m_Monster8 = false;

        m_bInit = false;


        return STATE_TYPE::BOSS_BLUE_CAST;


    /*    if (vOwnerPos.z > vPlayerPos.z)
        {
            return STATE_TYPE::BOSS_CHASE3;
        }
        else
        {
            return STATE_TYPE::BOSS_BACK_CHASE3;
        }*/
    }


   return STATE_TYPE::BOSS_CREATE_WYVERN;

#pragma endregion
	
}

void CVioletDragonState_CreateWyvern::LateUpdate_State()
{
 
}

void CVioletDragonState_CreateWyvern::Render_State()
{
 
}

STATE_TYPE CVioletDragonState_CreateWyvern::Key_Input(const _float& fTimeDelta)
{

    return m_eState;
}

CVioletDragonState_CreateWyvern* CVioletDragonState_CreateWyvern::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{

    CVioletDragonState_CreateWyvern* pInstance = new CVioletDragonState_CreateWyvern(pGraphicDev);

    if (FAILED(pInstance->Ready_State(pOwner)))
    {
        Safe_Release(pInstance);
        MSG_BOX("VioletDragonState CreateWyvern Create Failed");
        return nullptr;

    }

    return pInstance;
}

void CVioletDragonState_CreateWyvern::Free()
{

	__super::Free();

}
