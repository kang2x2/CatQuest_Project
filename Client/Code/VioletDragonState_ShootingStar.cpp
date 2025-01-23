#include "VioletDragonState_ShootingStar.h"
#include "Player.h"
#include "Export_Function.h"
#include "EventMgr.h"
#include "Monster.h"
#include "BlueStar_Bullet.h"
#include "VioletDragon.h"
#include "SoundMgr.h"

CVioletDragonState_ShootingStar::CVioletDragonState_ShootingStar(LPDIRECT3DDEVICE9 pGraphicDev)
	:CState(pGraphicDev)
	, m_fAccTime(0.f)
{
}

CVioletDragonState_ShootingStar::~CVioletDragonState_ShootingStar()
{
}

HRESULT CVioletDragonState_ShootingStar::Ready_State(CStateMachine* pOwner)
{
	if (nullptr != pOwner)
	{
		m_pOwner = pOwner;
	}
	m_eState = STATE_TYPE::BOSS_SHOOTING_STAR;

	m_fAccTime = 0.f;


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

    m_bBullet17 = false;
    m_bBullet18 = false;
    m_bBullet19 = false;
    m_bBullet20 = false;
               
    m_bBullet21 = false;
    m_bBullet22 = false;
    m_bBullet23 = false;
    m_bBullet24 = false;
                
    m_bBullet25 = false;
    m_bBullet26 = false;
    m_bBullet27 = false;
    m_bBullet28 = false;





	return S_OK;
}

STATE_TYPE CVioletDragonState_ShootingStar::Update_State(const _float& fTimeDelta)
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


#pragma region Cur state Function


    CCameraMgr::GetInstance()->Start_Action(CAMERA_ACTION::BOSS_SKILL_IN);






    //  // x 이동 방향에 따라 스케일 전환 
    //if (vOwnerPos.x <= (vPlayerPos).x && vOwnerScale.x <= 0)
    //{
    //    pOwnerTransform->Set_Scale({ -vOwnerScale.x , vOwnerScale.y, vOwnerScale.z });
    //}
    //else if (vOwnerPos.x > (vPlayerPos).x && vOwnerScale.x > 0)
    //{
    //    pOwnerTransform->Set_Scale({ -vOwnerScale.x , vOwnerScale.y, vOwnerScale.z });
    //}


    m_fAccTime += fTimeDelta;


    _float fSoundVol = 0.8f;


     // First Group
    if (m_bBullet1 == false && m_fAccTime >= 0.1f) //1 
    {
        CSoundMgr::GetInstance()->PlaySound(L"ShootingStar.mp3", CHANNEL_ID::MONSTER_BOSS_0, fSoundVol);
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging1",
            CBlueStar_Bullet::Create(m_pGraphicDev, { vOwnerPos.x - 8.f , vOwnerPos.y + 2.f , vOwnerPos.z - 5.f }, pPlayer, m_pOwner->Get_OwnerObject()));
       
        m_bBullet1 = true;
    }

    if (m_bBullet2 == false && m_fAccTime >= 0.1f) //2
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging2",
            CBlueStar_Bullet::Create(m_pGraphicDev, { vOwnerPos.x + 8.f , vOwnerPos.y + 2.f, vOwnerPos.z - 5.f }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet2 = true;
    }

    if (m_bBullet3 == false && m_fAccTime >= 0.1f) //3
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging3",
            CBlueStar_Bullet::Create(m_pGraphicDev, { vOwnerPos.x - 4.f , vOwnerPos.y + 6.f, vOwnerPos.z - 5.f }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet3 = true;
    }

    if (m_bBullet4 == false && m_fAccTime >= 0.1f) //4
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging4",
            CBlueStar_Bullet::Create(m_pGraphicDev, { vOwnerPos.x + 4.f , vOwnerPos.y + 6.f, vOwnerPos.z - 5.f }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet4 = true;
    }


    // Second Group
    if (m_bBullet5 == false && m_fAccTime >= 0.6f) //5
    {
        CSoundMgr::GetInstance()->PlaySound(L"ShootingStar.mp3", CHANNEL_ID::MONSTER_BOSS_1, fSoundVol);
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging5",
            CBlueStar_Bullet::Create(m_pGraphicDev, { vOwnerPos.x - 8.f , vOwnerPos.y + 2.f , vOwnerPos.z - 5.f }, pPlayer, m_pOwner->Get_OwnerObject()));

        m_bBullet5 = true;
    }

    if (m_bBullet6 == false && m_fAccTime >= 0.6f) //6
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging6",
            CBlueStar_Bullet::Create(m_pGraphicDev, { vOwnerPos.x + 8.f , vOwnerPos.y + 2.f, vOwnerPos.z - 5.f }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet6 = true;
    }

    if (m_bBullet7 == false && m_fAccTime >= 0.6f) //7
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging7",
            CBlueStar_Bullet::Create(m_pGraphicDev, { vOwnerPos.x - 4.f , vOwnerPos.y + 6.f, vOwnerPos.z - 5.f }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet7 = true;
    }

    if (m_bBullet8 == false && m_fAccTime >= 0.6f) //8
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging8",
            CBlueStar_Bullet::Create(m_pGraphicDev, { vOwnerPos.x + 4.f , vOwnerPos.y + 6.f, vOwnerPos.z - 5.f }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet8 = true;
    }



    // Third Group
    if (m_bBullet9 == false && m_fAccTime >= 1.1f) //9
    {
        CSoundMgr::GetInstance()->PlaySound(L"ShootingStar.mp3", CHANNEL_ID::MONSTER_BOSS_2, fSoundVol);
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging9",
            CBlueStar_Bullet::Create(m_pGraphicDev, { vOwnerPos.x - 8.f , vOwnerPos.y + 2.f , vOwnerPos.z - 5.f }, pPlayer, m_pOwner->Get_OwnerObject()));

        m_bBullet9 = true;
    }

    if (m_bBullet10 == false && m_fAccTime >= 1.1f) //10
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging10",
            CBlueStar_Bullet::Create(m_pGraphicDev, { vOwnerPos.x + 8.f , vOwnerPos.y + 2.f, vOwnerPos.z - 5.f }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet10 = true;
    }

    if (m_bBullet11 == false && m_fAccTime >= 1.1f) //11
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging11",
            CBlueStar_Bullet::Create(m_pGraphicDev, { vOwnerPos.x - 4.f , vOwnerPos.y + 6.f, vOwnerPos.z - 5.f }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet11 = true;
    }

    if (m_bBullet12== false && m_fAccTime >= 1.1f) //12
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging12",
            CBlueStar_Bullet::Create(m_pGraphicDev, { vOwnerPos.x + 4.f , vOwnerPos.y + 6.f, vOwnerPos.z - 5.f }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet12 = true;
    }

    // Fourth Group
    if (m_bBullet13 == false && m_fAccTime >= 1.6f) //13
    {
        CSoundMgr::GetInstance()->PlaySound(L"ShootingStar.mp3", CHANNEL_ID::MONSTER_BOSS_0, fSoundVol);
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging13",
            CBlueStar_Bullet::Create(m_pGraphicDev, { vOwnerPos.x - 8.f , vOwnerPos.y + 2.f , vOwnerPos.z - 5.f }, pPlayer, m_pOwner->Get_OwnerObject()));

        m_bBullet13 = true;
    }

    if (m_bBullet14 == false && m_fAccTime >= 1.6f) //14
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging14",
            CBlueStar_Bullet::Create(m_pGraphicDev, { vOwnerPos.x + 8.f , vOwnerPos.y + 2.f, vOwnerPos.z - 5.f }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet14 = true;
    }

    if (m_bBullet15 == false && m_fAccTime >= 1.6f) //15
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging15",
            CBlueStar_Bullet::Create(m_pGraphicDev, { vOwnerPos.x - 4.f , vOwnerPos.y + 6.f, vOwnerPos.z - 5.f }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet15 = true;
    }

    if (m_bBullet16 == false && m_fAccTime >= 1.6f) //16
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging16",
            CBlueStar_Bullet::Create(m_pGraphicDev, { vOwnerPos.x + 4.f , vOwnerPos.y + 6.f, vOwnerPos.z - 5.f }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet16 = true;
    }


    // Fivth Group
    if (m_bBullet17 == false && m_fAccTime >= 2.1f) //17
    {
        CSoundMgr::GetInstance()->PlaySound(L"ShootingStar.mp3", CHANNEL_ID::MONSTER_BOSS_0, fSoundVol);
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging17",
            CBlueStar_Bullet::Create(m_pGraphicDev, { vOwnerPos.x - 8.f , vOwnerPos.y + 2.f , vOwnerPos.z - 5.f }, pPlayer, m_pOwner->Get_OwnerObject()));

        m_bBullet17 = true;
    }

    if (m_bBullet18 == false && m_fAccTime >= 2.1f) //18
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging18",
            CBlueStar_Bullet::Create(m_pGraphicDev, { vOwnerPos.x + 8.f , vOwnerPos.y + 2.f, vOwnerPos.z - 5.f }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet18 = true;
    }

    if (m_bBullet19 == false && m_fAccTime >= 2.1f) //19
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging19",
            CBlueStar_Bullet::Create(m_pGraphicDev, { vOwnerPos.x - 4.f , vOwnerPos.y + 6.f, vOwnerPos.z - 5.f }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet19 = true;
    }

    if (m_bBullet20 == false && m_fAccTime >= 2.1f) //20
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging20",
            CBlueStar_Bullet::Create(m_pGraphicDev, { vOwnerPos.x + 4.f , vOwnerPos.y + 6.f, vOwnerPos.z - 5.f }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet20 = true;
    }



    // Fourth Group
    if (m_bBullet21 == false && m_fAccTime >= 2.6f) //21
    {
        CSoundMgr::GetInstance()->PlaySound(L"ShootingStar.mp3", CHANNEL_ID::MONSTER_BOSS_0, fSoundVol);
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging21",
            CBlueStar_Bullet::Create(m_pGraphicDev, { vOwnerPos.x - 8.f , vOwnerPos.y + 2.f , vOwnerPos.z - 5.f }, pPlayer, m_pOwner->Get_OwnerObject()));

        m_bBullet21 = true;
    }

    if (m_bBullet22 == false && m_fAccTime >= 2.6f) //22
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging22",
            CBlueStar_Bullet::Create(m_pGraphicDev, { vOwnerPos.x + 8.f , vOwnerPos.y + 2.f, vOwnerPos.z - 5.f }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet22 = true;
    }

    if (m_bBullet23 == false && m_fAccTime >= 2.6f) //23
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging23",
            CBlueStar_Bullet::Create(m_pGraphicDev, { vOwnerPos.x - 4.f , vOwnerPos.y + 6.f, vOwnerPos.z - 5.f }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet23 = true;
    }

    if (m_bBullet24 == false && m_fAccTime >= 2.6f) //24
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging24",
            CBlueStar_Bullet::Create(m_pGraphicDev, { vOwnerPos.x + 4.f , vOwnerPos.y + 6.f, vOwnerPos.z - 5.f }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet24 = true;
    }




    // Fourth Group
    if (m_bBullet25 == false && m_fAccTime >= 3.1f) //25
    {
        CSoundMgr::GetInstance()->PlaySound(L"ShootingStar.mp3", CHANNEL_ID::MONSTER_BOSS_0, fSoundVol);
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging25",
            CBlueStar_Bullet::Create(m_pGraphicDev, { vOwnerPos.x - 8.f , vOwnerPos.y + 2.f , vOwnerPos.z - 5.f }, pPlayer, m_pOwner->Get_OwnerObject()));

        m_bBullet25 = true;
    }

    if (m_bBullet26 == false && m_fAccTime >= 3.1f) //26
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging26",
            CBlueStar_Bullet::Create(m_pGraphicDev, { vOwnerPos.x + 8.f , vOwnerPos.y + 2.f, vOwnerPos.z - 5.f }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet26 = true;
    }

    if (m_bBullet27 == false && m_fAccTime >= 3.1f) //27
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging27",
            CBlueStar_Bullet::Create(m_pGraphicDev, { vOwnerPos.x - 4.f , vOwnerPos.y + 6.f, vOwnerPos.z - 5.f }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet27 = true;
    }

    if (m_bBullet28 == false && m_fAccTime >= 3.1f) //28
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging28",
            CBlueStar_Bullet::Create(m_pGraphicDev, { vOwnerPos.x + 4.f , vOwnerPos.y + 6.f, vOwnerPos.z - 5.f }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet28 = true;
    }



    // 현재 상태의 기능
    if (fPlayerDistance >= 8.f)
    {
        dynamic_cast<CAIComponent*>(pOwnerAI)->Chase_Target(&vPlayerPos, fTimeDelta, vOwnerSpeed);
        pOwnerTransform->Translate(fTimeDelta * vOwnerSpeed);
    }
    else
    {
        pOwnerTransform->Set_Dir(vec3.zero);
    }



#pragma endregion



#pragma region State Change
    // State Change 

    if (Owner_bHP90 == true && Owner_bHP60 == true && Owner_bHP30 == false)
    {
        return STATE_TYPE::BOSS_FULLDOWN_FLY;
    }


    if (m_fAccTime >= 3.5f)
    {
        if (fPlayerDistance <= 15.f)
        {

            if (vOwnerPos.z >= vPlayerPos.z)
            {
                m_fAccTime = 0.f;

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


                m_bBullet17 = false;
                m_bBullet18 = false;
                m_bBullet19 = false;
                m_bBullet20 = false;

                m_bBullet21 = false;
                m_bBullet22 = false;
                m_bBullet23 = false;
                m_bBullet24 = false;

                m_bBullet25 = false;
                m_bBullet26 = false;
                m_bBullet27 = false;
                m_bBullet28 = false;

                CCameraMgr::GetInstance()->Start_Action(CAMERA_ACTION::BOSS_SKILL_OUT);

                return STATE_TYPE::BOSS_NEAR_ATTACK1;
            }
            else
            {
                m_fAccTime = 0.f;

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


                m_bBullet17 = false;
                m_bBullet18 = false;
                m_bBullet19 = false;
                m_bBullet20 = false;

                m_bBullet21 = false;
                m_bBullet22 = false;
                m_bBullet23 = false;
                m_bBullet24 = false;

                m_bBullet25 = false;
                m_bBullet26 = false;
                m_bBullet27 = false;
                m_bBullet28 = false;

                CCameraMgr::GetInstance()->Start_Action(CAMERA_ACTION::BOSS_SKILL_OUT);

                return STATE_TYPE::BOSS_BACK_NEAR_ATTACK1;
            }
        }

        m_fAccTime = 0.f;

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


        m_bBullet17 = false;
        m_bBullet18 = false;
        m_bBullet19 = false;
        m_bBullet20 = false;

        m_bBullet21 = false;
        m_bBullet22 = false;
        m_bBullet23 = false;
        m_bBullet24 = false;

        m_bBullet25 = false;
        m_bBullet26 = false;
        m_bBullet27 = false;
        m_bBullet28 = false;

        CCameraMgr::GetInstance()->Start_Action(CAMERA_ACTION::BOSS_SKILL_OUT);

     
        return STATE_TYPE::BOSS_SPREAD_CAST;
    }


    return STATE_TYPE::BOSS_SHOOTING_STAR;
#pragma endregion

 
}


void CVioletDragonState_ShootingStar::LateUpdate_State()
{
}

void CVioletDragonState_ShootingStar::Render_State()
{
}

STATE_TYPE CVioletDragonState_ShootingStar::Key_Input(const _float& fTimeDelta)
{
	return STATE_TYPE();
}

CVioletDragonState_ShootingStar* CVioletDragonState_ShootingStar::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
    CVioletDragonState_ShootingStar* pInstance = new CVioletDragonState_ShootingStar(pGraphicDev );

    if (FAILED(pInstance->Ready_State(pOwner)))
    {
        Safe_Release(pInstance);
        MSG_BOX("VioletDragonState ShootingStar Create Failed");
        return nullptr;

    }

    return pInstance;
}

void CVioletDragonState_ShootingStar::Free()
{
    __super::Free();
}
