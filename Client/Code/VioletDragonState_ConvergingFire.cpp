#include "VioletDragonState_ConvergingFire.h"
#include "Export_Function.h"
#include "Monster.h"
#include "Player.h"
#include "Dagger.h"
#include "EventMgr.h"
#include "VioletDragon.h"
#include "SoundMgr.h"

CVioletDragonState_ConvergingFire::CVioletDragonState_ConvergingFire(LPDIRECT3DDEVICE9 pGraphicDev)
	:CState(pGraphicDev)
	, m_fAccTime(0.f)
{
}

CVioletDragonState_ConvergingFire::~CVioletDragonState_ConvergingFire()
{
}

HRESULT CVioletDragonState_ConvergingFire::Ready_State(CStateMachine* pOwner)
{
    if (nullptr != pOwner)
    {
        m_pOwner = pOwner;
    }
    m_eState = STATE_TYPE::BOSS_CONVERGING_FIRE;

    m_fAccTime = 0.f;


    m_bSound = false;

    m_bBullet1 = false;
    m_bBullet2 = false;
    m_bBullet3 = false;
    m_bBullet4 = false;

    m_bBullet5 = false;
    m_bBullet6 = false;
    m_bBullet7 = false;
    m_bBullet8 = false;

    m_bBullet9  = false;
    m_bBullet10 = false;
    m_bBullet11 = false;
    m_bBullet12 = false;

    m_bBullet13 = false;
    m_bBullet14 = false;
    m_bBullet15 = false;
    m_bBullet16 = false;


    m_bSound1 = false;
    m_bSound2 = false;
    m_bSound3 = false;
    m_bSound4 = false;
    m_bSound5 = false;
    m_bSound6 = false;
    m_bSound7 = false;
    m_bSound8 = false;
    m_bSound9 = false;
    m_bSound10 = false;
    m_bSound11 = false;
    m_bSound12 = false;
    m_bSound13 = false;
    m_bSound14 = false;
    m_bSound15 = false;
    m_bSound16 = false;


    return S_OK;
}

STATE_TYPE CVioletDragonState_ConvergingFire::Update_State(const _float& fTimeDelta)
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





#pragma region Cur State Function


      // x 이동 방향에 따라 스케일 전환 
    if (vOwnerPos.x < (vPlayerPos).x && vOwnerScale.x < 0)
    {
        pOwnerTransform->Set_Scale({ -vOwnerScale.x , vOwnerScale.y, vOwnerScale.z });
    }
    else if (vOwnerPos.x > (vPlayerPos).x && vOwnerScale.x > 0)
    {
        pOwnerTransform->Set_Scale({ -vOwnerScale.x , vOwnerScale.y, vOwnerScale.z });
    }

    _float fSoundVolm = 0.7f;


    if (m_bSound == false)
    {
        CSoundMgr::GetInstance()->PlaySound(L"BulletStopSound2.mp3", CHANNEL_ID::MONSTER_SERPENT , fSoundVolm);
        m_bSound = true;
    }



    m_fAccTime += fTimeDelta;

    if (m_bBullet1 == false && m_fAccTime >= 0.5f) //1 
    {
        CSoundMgr::GetInstance()->PlaySound(L"magic_appear.wav", CHANNEL_ID::MONSTER_BOSS_0, fSoundVolm);

        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging1",
            CDagger::Create(m_pGraphicDev, { vOwnerPos.x - 10.f , vOwnerPos.y  , vOwnerPos.z }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet1 = true;
    }
    if (m_fAccTime >= 3.5f   && m_bSound1 == false)
    {
        CSoundMgr::GetInstance()->PlaySound(L"magic_appear_2.wav", CHANNEL_ID::MONSTER_BOSS_1,  1.f);
        m_bSound1 = true;
    }



    if (m_bBullet2 == false && m_fAccTime >= 0.6f) //2
    {
       // CSoundMgr::GetInstance()->PlaySound(L"magic_appear.wav", CHANNEL_ID::MONSTER_BOSS_1, fSoundVolm);

        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging2",
            CDagger::Create(m_pGraphicDev, { vOwnerPos.x + 10.f , vOwnerPos.y , vOwnerPos.z  }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet2 = true;
    }
    //if (m_fAccTime >= 3.6f)
    //{
    //    CSoundMgr::GetInstance()->PlaySound(L"masic_appear_2.wav", CHANNEL_ID::MONSTER_BOSS_1, fSoundVolm);

    //}



    if (m_bBullet3 == false && m_fAccTime >= 0.7f) //3
    {
        CSoundMgr::GetInstance()->PlaySound(L"magic_appear.wav", CHANNEL_ID::MONSTER_BOSS_2, fSoundVolm);

        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging3",
            CDagger::Create(m_pGraphicDev, { vOwnerPos.x - 8.f , vOwnerPos.y , vOwnerPos.z - 2.f }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet3 = true;
    }
    if (m_fAccTime >= 3.7f   && m_bSound3 == false)
    {
        CSoundMgr::GetInstance()->PlaySound(L"magic_appear_2.wav", CHANNEL_ID::MONSTER_BOSS_2, 1.f);
        m_bSound3 = true;
    }


    if (m_bBullet4 == false && m_fAccTime >= 0.8f) //4
    {
       // CSoundMgr::GetInstance()->PlaySound(L"magic_appear.wav", CHANNEL_ID::MONSTER_FISH, fSoundVolm);

        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging4",
            CDagger::Create(m_pGraphicDev, { vOwnerPos.x + 8.f , vOwnerPos.y , vOwnerPos.z - 2.f }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet4 = true;
    }
    //if (m_fAccTime >= 3.8f)
    //{
    //    CSoundMgr::GetInstance()->PlaySound(L"masic_appear_2.wav", CHANNEL_ID::MONSTER_FISH, fSoundVolm);

    //}



    if (m_bBullet5 == false && m_fAccTime >= 0.9f) //5
    {
        CSoundMgr::GetInstance()->PlaySound(L"magic_appear.wav", CHANNEL_ID::MONSTER_SERPENT, fSoundVolm);

        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging5",
            CDagger::Create(m_pGraphicDev, { vOwnerPos.x -6.f , vOwnerPos.y , vOwnerPos.z - 4.f }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet5 = true;
    }
    if (m_fAccTime >= 3.9f  && m_bSound5 == false )
    {
        CSoundMgr::GetInstance()->PlaySound(L"magic_appear_2.wav", CHANNEL_ID::MONSTER_SERPENT, 1.f);
        m_bSound5 = true;
    }



    if (m_bBullet6 == false && m_fAccTime >= 1.f) //6
    {
        //CSoundMgr::GetInstance()->PlaySound(L"magic_appear.wav", CHANNEL_ID::MONSTER_BOSS_0, fSoundVolm);

        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging6",
            CDagger::Create(m_pGraphicDev, { vOwnerPos.x + 6.f , vOwnerPos.y , vOwnerPos.z - 4.f }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet6 = true;
    }
    //if (m_fAccTime >= 4.f)
    //{
    //    CSoundMgr::GetInstance()->PlaySound(L"masic_appear_2.wav", CHANNEL_ID::MONSTER_BOSS_0, fSoundVolm);

    //}



    if (m_bBullet7 == false && m_fAccTime >= 1.1f) //7
    {
        CSoundMgr::GetInstance()->PlaySound(L"magic_appear.wav", CHANNEL_ID::MONSTER_BOSS_1, fSoundVolm);

        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging7",
            CDagger::Create(m_pGraphicDev, { vOwnerPos.x -4.f , vOwnerPos.y , vOwnerPos.z -6.f }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet7 = true;
    }
    if (m_fAccTime >= 4.1f  && m_bSound7 == false )
    {
        CSoundMgr::GetInstance()->PlaySound(L"magic_appear_2.wav", CHANNEL_ID::MONSTER_BOSS_1, 1.f);
        m_bSound7 = true;
    }

    if (m_bBullet8 == false && m_fAccTime >= 1.2f) //8
    {
       // CSoundMgr::GetInstance()->PlaySound(L"magic_appear.wav", CHANNEL_ID::MONSTER_BOSS_2, fSoundVolm);

        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging8",
            CDagger::Create(m_pGraphicDev, { vOwnerPos.x + 4.f , vOwnerPos.y , vOwnerPos.z - 6.f }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet8 = true;
    }
 /*   if (m_fAccTime >= 4.2f)
    {
        CSoundMgr::GetInstance()->PlaySound(L"masic_appear_2.wav", CHANNEL_ID::MONSTER_BOSS_2, fSoundVolm);

    }*/


    ///// cicle 1 end/////// 



    if (m_bBullet9 == false && m_fAccTime >= 1.3f) //9
    {
        CSoundMgr::GetInstance()->PlaySound(L"magic_appear.wav", CHANNEL_ID::MONSTER_FISH, fSoundVolm);

        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging9",
            CDagger::Create(m_pGraphicDev, { vOwnerPos.x - 2.f , vOwnerPos.y -2.f , vOwnerPos.z - 6.f }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet9 = true;
    }
    if (m_fAccTime >= 4.3f   && m_bSound9 == false)
    {
        CSoundMgr::GetInstance()->PlaySound(L"magic_appear_2.wav", CHANNEL_ID::MONSTER_FISH, 1.f);
        m_bSound9 = true;
    }

    if (m_bBullet10 == false && m_fAccTime >= 1.4f) //10
    {
      //  CSoundMgr::GetInstance()->PlaySound(L"magic_appear.wav", CHANNEL_ID::MONSTER_SERPENT, fSoundVolm);

        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging10",
            CDagger::Create(m_pGraphicDev, { vOwnerPos.x + 2.f , vOwnerPos.y - 2.f , vOwnerPos.z - 6.f }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet10 = true;
    }
  /*  if (m_fAccTime >= 4.4f)
    {
        CSoundMgr::GetInstance()->PlaySound(L"masic_appear_2.wav", CHANNEL_ID::MONSTER_SERPENT, fSoundVolm);

    }*/

    if (m_bBullet11 == false && m_fAccTime >= 1.5f) //11
    {
        CSoundMgr::GetInstance()->PlaySound(L"magic_appear.wav", CHANNEL_ID::MONSTER_BOSS_0, fSoundVolm);

        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging11",
            CDagger::Create(m_pGraphicDev, { vOwnerPos.x - 4.f , vOwnerPos.y - 2.f  , vOwnerPos.z - 4.f }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet11 = true;
    }
    if (m_fAccTime >= 4.5f  &&  m_bSound11 == false)
    {
        CSoundMgr::GetInstance()->PlaySound(L"magic_appear_2.wav", CHANNEL_ID::MONSTER_BOSS_1, 1.f);
        m_bSound11 = true;
    }


    if (m_bBullet12 == false && m_fAccTime >= 1.6f) //12
    {
      //  CSoundMgr::GetInstance()->PlaySound(L"magic_appear.wav", CHANNEL_ID::MONSTER_BOSS_1, fSoundVolm);

        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging12",
            CDagger::Create(m_pGraphicDev, { vOwnerPos.x + 4.f , vOwnerPos.y - 2.f  , vOwnerPos.z - 4.f }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet12 = true;
    }
 /*   if (m_fAccTime >= 4.6f)
    {
        CSoundMgr::GetInstance()->PlaySound(L"masic_appear_2.wav", CHANNEL_ID::MONSTER_BOSS_1, fSoundVolm);

    }*/

    if (m_bBullet13 == false && m_fAccTime >= 1.7f) //13
    {
        CSoundMgr::GetInstance()->PlaySound(L"magic_appear.wav", CHANNEL_ID::MONSTER_BOSS_2, fSoundVolm);

        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging13",
            CDagger::Create(m_pGraphicDev, { vOwnerPos.x - 6.f , vOwnerPos.y - 2.f  , vOwnerPos.z - 2.f }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet13 = true;
    }
    if (m_fAccTime >= 4.7f &&  m_bSound13 == false )
    {
        CSoundMgr::GetInstance()->PlaySound(L"magic_appear_2.wav", CHANNEL_ID::MONSTER_BOSS_2, 1.f);
        m_bSound13 = true;
    }


    if (m_bBullet14 == false && m_fAccTime >= 1.8f) //14
    {
       // CSoundMgr::GetInstance()->PlaySound(L"magic_appear.wav", CHANNEL_ID::MONSTER_FISH, fSoundVolm);

        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging14",
            CDagger::Create(m_pGraphicDev, { vOwnerPos.x + 6.f , vOwnerPos.y - 2.f , vOwnerPos.z - 2.f }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet14 = true;
    }
    //if (m_fAccTime >= 4.8f)
    //{
    //    CSoundMgr::GetInstance()->PlaySound(L"masic_appear_2.wav", CHANNEL_ID::MONSTER_FISH, fSoundVolm);

    //}


    if (m_bBullet15 == false && m_fAccTime >= 1.9f) //15
    {
        CSoundMgr::GetInstance()->PlaySound(L"magic_appear.wav", CHANNEL_ID::MONSTER_SERPENT, fSoundVolm);

        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging15",
            CDagger::Create(m_pGraphicDev, { vOwnerPos.x - 8.f , vOwnerPos.y - 2.f , vOwnerPos.z }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet15 = true;
    }
    if (m_fAccTime >= 4.9f   &&  m_bSound15 == false)
    {
        CSoundMgr::GetInstance()->PlaySound(L"magic_appear_2.wav", CHANNEL_ID::MONSTER_SERPENT, 1.f);
        m_bSound15 = true;
    }



    if (m_bBullet16 == false && m_fAccTime >= 2.f) //16
    {
      //  CSoundMgr::GetInstance()->PlaySound(L"magic_appear.wav", CHANNEL_ID::MONSTER_BOSS_0, fSoundVolm);

        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging16",
            CDagger::Create(m_pGraphicDev, { vOwnerPos.x + 8.f , vOwnerPos.y - 2.f  , vOwnerPos.z }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet16 = true;
    }
    //if (m_fAccTime >= 5.f)
    //{
    //    CSoundMgr::GetInstance()->PlaySound(L"masic_appear_2.wav", CHANNEL_ID::MONSTER_BOSS_0, fSoundVolm);

    //}

#pragma endregion



#pragma region State Change


    if (Owner_bHP90 == true && Owner_bHP60 == true && Owner_bHP30 == false)
    {
        return STATE_TYPE::BOSS_FULLDOWN_FLY;
    }


    if (m_fAccTime >= 5.f)
    {
        m_fAccTime = 0.f;
        m_bSound = false;

        m_bBullet1 = false;
        m_bBullet2 = false;
        m_bBullet3 = false;
        m_bBullet4 = false;

        m_bBullet5 = false;
        m_bBullet6 = false;
        m_bBullet7 = false;
        m_bBullet8 = false;

        m_bBullet9 = false;
        m_bBullet10 = false;
        m_bBullet11 = false; 
        m_bBullet12 = false;

        m_bBullet13 = false;
        m_bBullet14 = false;
        m_bBullet15 = false;
        m_bBullet16 = false;
    


        m_bSound1 = false;
        m_bSound2 = false;
        m_bSound3 = false;
        m_bSound4 = false;
        m_bSound5 = false;
        m_bSound6 = false;
        m_bSound7 = false;
        m_bSound8 = false;
        m_bSound9 = false;
        m_bSound10 = false;
        m_bSound11 = false;
        m_bSound12 = false;
        m_bSound13 = false;
        m_bSound14 = false;
        m_bSound15 = false;
        m_bSound16 = false;
      
        return STATE_TYPE::BOSS_SHOOTING_STAR;
    }

    return STATE_TYPE::BOSS_CONVERGING_FIRE;

#pragma endregion


}


void CVioletDragonState_ConvergingFire::LateUpdate_State()
{
}

void CVioletDragonState_ConvergingFire::Render_State()
{
}

STATE_TYPE CVioletDragonState_ConvergingFire::Key_Input(const _float& fTimeDelta)
{
    return m_eState;
}

CVioletDragonState_ConvergingFire* CVioletDragonState_ConvergingFire::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
    CVioletDragonState_ConvergingFire* pInstance = new CVioletDragonState_ConvergingFire(pGraphicDev);

    if (FAILED(pInstance->Ready_State(pOwner)))
    {
        Safe_Release(pInstance);
        MSG_BOX("VioletDragonState Converging_Fire Create Failed");
        return nullptr;

    }

    return pInstance;
}

void CVioletDragonState_ConvergingFire::Free()
{
    __super::Free();
}
