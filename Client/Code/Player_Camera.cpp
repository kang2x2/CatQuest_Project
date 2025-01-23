#include "stdafx.h"
#include "..\Header\Player_Camera.h"

#include "Export_Function.h"

#include "FadeUI.h"
#include"BossSceneMgr.h"	
#include "Engine_Define.h"
#include "MiniGameMgr_Bingo.h"

CPlayer_Camera::CPlayer_Camera(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CCameraObject(pGraphicDev)
	, m_pFadeUI(nullptr)
	, m_eFadeMode(FADE_MODE::TYPEEND)
	, m_bDrag(TRUE)
	, m_bBackView(FALSE)
	, m_bFlightView(FALSE)
	, m_bBossDistLerp(FALSE)
	, m_bBossVec3Lerp(FALSE)
{

}
CPlayer_Camera::CPlayer_Camera(const CPlayer_Camera& rhs)
	: Engine::CCameraObject(rhs)
{
	ZeroMemory(&m_fJumpDelta, sizeof(LERP_FLOAT_INFO));
	ZeroMemory(&m_fFlightDelta, sizeof(LERP_FLOAT_INFO));
}

CPlayer_Camera::~CPlayer_Camera()
{
}

HRESULT CPlayer_Camera::Ready_Object(void)
{
	CCameraObject::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_fDefaultHeight	= 80.f;
	m_fNearZoom			= CAM_DISTANCE_DEFAULT;
	m_fFarZoom			= CAM_DISTANCE_MAX;
	m_pCameraCom->m_fDistance = m_fNearZoom;

	m_pTransformCom->Set_Pos(_vec3{ 0.f, m_fDefaultHeight, -m_pCameraCom->m_fDistance });
	m_pCameraCom->m_fSpeedZoom = 100.f;

	m_bMaintain = true; // 씬 변경시 유지 (사용시 팀장 보고)

	m_szName = L"Player_Camera";

	m_pCameraCom->Set_CameraType(CAMERA_TYPE::PLAYER_CAMERA);

	m_pFadeUI = CFadeUI::Create(m_pGraphicDev);
	CEventMgr::GetInstance()->Add_Obj(m_pFadeUI->Get_Name(), m_pFadeUI);

	return S_OK;
}

Engine::_int CPlayer_Camera::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Set_Zoom(fTimeDelta);

	if (m_pCameraCom->m_tFOVLerp.bActive)
	{
		m_pCameraCom->m_tFOVLerp.Update_Lerp(fTimeDelta);
		m_pCameraCom->m_tProj.FOV = m_pCameraCom->m_tFOVLerp.fCurValue;
		m_pCameraCom->Set_Projection();
	}

	if (m_pCameraCom->m_tHeightLerp.bActive)
	{
		m_pCameraCom->m_tHeightLerp.Update_Lerp(fTimeDelta);
	}
	
	if (m_pCameraCom->m_tVec3Lerp.bActive)
	{
		m_pCameraCom->m_tVec3Lerp.Update_Lerp(fTimeDelta);

	}

	if (m_pCameraCom->m_tDistanceLerp.bActive)
	{
		m_pCameraCom->m_tDistanceLerp.Update_Lerp(fTimeDelta);
		m_pCameraCom->m_fDistance = m_pCameraCom->m_tDistanceLerp.fCurValue;
	}

	m_fJumpDelta.Update_Lerp(fTimeDelta);
	m_fFlightDelta.Update_Lerp(fTimeDelta);

	return iExit;
}

void CPlayer_Camera::LateUpdate_Object(void)
{
	__super::LateUpdate_Object();

	Set_ViewSpace();
}

void CPlayer_Camera::Start_Fade(const FADE_MODE& _eMode)
{
	switch (_eMode)
	{
	case Engine::FADE_MODE::ENTER_WORLD:
		m_pFadeUI->Start_Fade(4.f, 255.f, 0.f, TRUE, LERP_MODE::EASE_IN); break;
	case Engine::FADE_MODE::BLACK_FADE_IN:
		m_pFadeUI->Start_Fade(1.5f, 255.f, 0.f, FALSE, LERP_MODE::EASE_IN); break;
	case Engine::FADE_MODE::BLACK_FADE_OUT:
		m_pFadeUI->Start_Fade(0.5f, 0.f, 255.f, FALSE, LERP_MODE::EASE_OUT); break;
	case Engine::FADE_MODE::WHITE_FADE_IN:
		m_pFadeUI->Start_Fade(2.5f, 255.f, 0.f, TRUE, LERP_MODE::EASE_IN); break;
	case Engine::FADE_MODE::WHITE_FADE_OUT:
		m_pFadeUI->Start_Fade(3.5f, 0.f, 255.f, TRUE, LERP_MODE::EASE_OUT); break;
	default:
		break;
	}
	m_eFadeMode = _eMode;
}

const _bool& CPlayer_Camera::Is_Fade()
{
	NULL_CHECK_RETURN(m_pFadeUI, FALSE);

	return m_pFadeUI->Is_Fade();
}


HRESULT CPlayer_Camera::Add_Component(void)
{
	CComponent*			pComponent = nullptr;

	return S_OK;
}


void CPlayer_Camera::Set_Zoom(const _float& fTimeDelta)
{
	_long dwMouse = 0;

	if (dwMouse = CInputDev::GetInstance()->Get_DIMouseMove(DIMS_Z))
	{
		const _float fLerpTime = 0.8f;

		if (!m_bDrag && 0 < dwMouse)
		{
			m_pCameraCom->m_tDistanceLerp.Init_Lerp(LERP_MODE::SMOOTHERSTEP);

			m_pCameraCom->Lerp_FOV(fLerpTime, m_pCameraCom->m_tProj.FOV, CAM_FOV_DEFAULT, LERP_MODE::SMOOTHERSTEP);
			m_pCameraCom->m_tDistanceLerp.Set_Lerp(fLerpTime, m_pCameraCom->m_fDistance, CAM_DISTANCE_DEFAULT);

			m_bDrag = TRUE;
		}
		else if (m_bDrag && 0 > dwMouse)
		{
			m_pCameraCom->m_tDistanceLerp.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
			
			if (SCENE_TYPE::DUNGEON_TEMPLE == CManagement::GetInstance()->Get_CurScene()->Get_SceneType())
			{
				/*m_pCameraCom->Lerp_FOV(fLerpTime, m_pCameraCom->m_tProj.FOV, CAM_FOV_BINGO, LERP_MODE::SMOOTHERSTEP);
				m_pCameraCom->m_tDistanceLerp.Set_Lerp(fLerpTime, m_pCameraCom->m_fDistance, CAM_DISTANCE_BINGO);*/
			}
			else
			{
				m_pCameraCom->Lerp_FOV(fLerpTime, m_pCameraCom->m_tProj.FOV, CAM_FOV_DRAG_MAX, LERP_MODE::SMOOTHERSTEP);
				m_pCameraCom->m_tDistanceLerp.Set_Lerp(fLerpTime, m_pCameraCom->m_fDistance, CAM_DISTANCE_MAX);
			}
			
			m_bDrag = FALSE;
		}
	}
}

void CPlayer_Camera::Set_ViewSpace() 
{
	// 플레이어의 최종 포지션 결정 이후에 해당 함수가 호출되어야 한다!
	
	NULL_CHECK(m_pCameraCom->m_pLookAt);
	NULL_CHECK(m_pCameraCom->m_pFollow);

	// Enter Ingame Lerp (월드 최초 입장)
	if (m_pCameraCom->m_tHeightLerp.bActive 
		&& CAMERA_ACTION::SCENE_ENTER_INGAME == CCameraMgr::GetInstance()->Get_CurCameraAction()
		|| CAMERA_ACTION::SCENE_EXIT_INGAME == CCameraMgr::GetInstance()->Get_CurCameraAction())
	{
		Lerp_Enter_Scene();
		return;
	}

	// Enter Fiels Lerp (씬변경시)
	if (m_pCameraCom->m_tHeightLerp.bActive && CAMERA_ACTION::SCENE_ENTER_FIELD == CCameraMgr::GetInstance()->Get_CurCameraAction())
	{
		Lerp_Enter_Scene();
		return;
	}

	// Change Target Lerp
	else if (CAMERA_ACTION::OBJ_CHANGE_TARGET == CCameraMgr::GetInstance()->Get_CurCameraAction())// || CAMERA_ACTION::START_BOSS == CCameraMgr::GetInstance()->Get_CurCameraAction())
	{
		//if (!m_pCameraCom->m_tVec3Lerp.bActive) return;

		Lerp_Change_Target();
		return;
	}

	_vec3 vFollowPos, vLookPos, vLerpPos{};

	// INTRO
	if (CBossSceneMgr::GetInstance()->Is_BossIntroAnimation_End() && !CBossSceneMgr::GetInstance()->Get_CurPage(PAGE::FADE_OUT))
	{
		vFollowPos = m_pCameraCom->m_pFollow->Get_Transform()->Get_Info(INFO_POS);

		CGameObject* pBoss = CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::MONSTER, L"Monster_VioletDragon");

		if (nullptr != pBoss)
		{
			// 팔로우 포지션 결정
			_vec3 vBossPos = pBoss->Get_Transform()->Get_Info(INFO_POS);
		/*	if (!m_bBossVec3Lerp)
			{
				_vec3 vLerp; _vec3 vTarget;
				vTarget =  vFollowPos + (_vec3{ (vBossPos.x - vFollowPos.x), 0.f, (vBossPos.z - vFollowPos.z) } *0.5f);
				D3DXVec3Lerp(&vLerp, &vBossPos, &vTarget, Engine::Get_TimeDelta(L"Timer_FPS65") * 0.01f);
				vFollowPos = vLerp;

				cout << D3DXVec3Length(&(vFollowPos - vTarget)) << endl;
				if (0.05f > D3DXVec3Length(&(vFollowPos - vTarget)))
				{
					m_bBossVec3Lerp = TRUE;
				}
			}
			else
			{*/
				vFollowPos += (_vec3{ (vBossPos.x - vFollowPos.x), 0.f, (vBossPos.z - vFollowPos.z) } *0.5f);
				m_vBossScenePrevPos = vFollowPos;

			//}

			// 디스턴스 결정
			_float fDist = D3DXVec3Length(&(vBossPos - CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::PLAYER, L"Player")->Get_Transform()->Get_Info(INFO_POS)));
		/*	if (!m_bBossDistLerp)
			{
				_float fCamDist = CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->m_fDistance;
				if (fCamDist < fDist)
				{
					CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->m_fDistance += Engine::Get_TimeDelta(L"Timer_FPS65");

					if (CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->m_fDistance >= fDist)
						m_bBossDistLerp = TRUE;
				}
				else
				{
					CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->m_fDistance -= Engine::Get_TimeDelta(L"Timer_FPS65");

					if (CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->m_fDistance <= fDist)
						m_bBossDistLerp = TRUE;
				}

			}
			else
			{*/
				if (7.f <= fDist)
				{
					_float fCamDist = CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->m_fDistance;
					CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->m_fDistance = CAM_DISTANCE_DEFAULT + fDist * 0.2f;
				}

			//}
			m_fBossScenePrevDist = CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->m_fDistance;
		}
		else
		{
			vFollowPos = m_vBossScenePrevPos;
			CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->m_fDistance = m_fBossScenePrevDist;
		}
	}
	else
	{
		vFollowPos = m_pCameraCom->m_pFollow->Get_Transform()->Get_Info(INFO_POS);
	}

	vLookPos = m_pCameraCom->m_tVspace.LookAt;
	_float fLerpValue = 8.f;
	D3DXVec3Lerp(&vLerpPos, &vLookPos, &vFollowPos, Engine::Get_TimeDelta(L"Timer_FPS65") * fLerpValue); 
	vLerpPos.y = vFollowPos.y; // 플레이어 추적시 y 값 흔들림 보정 wwsa 

	vLerpPos.y = m_pCameraCom->m_fInitLookY; // 이거 예외처리 필요
	

	// 02. 타겟까지의 디스턴스에 따른 카메라의 높이값을 구한다.
	_vec3 vDir1 = m_pTransformCom->Get_Info(INFO_POS) - vLerpPos;
	_vec3 vDir2 = { vDir1.x, 0.f, vDir1.z };
	D3DXVec3Normalize(&vDir1, &vDir1);
	D3DXVec3Normalize(&vDir2, &vDir2);
	_float fTheta = D3DXVec3Dot(&vDir1, &vDir2);
	_float fY = 0.f;

	
	if (m_fFlightDelta.bActive || m_bFlightView) // 카메라 높이 세팅 (점프뷰라면, 카메라의 높이를 높인다)	
		fY = (sinf(fTheta) * m_pCameraCom->m_fDistance * CAM_HEIGHT_MAG) + (m_fFlightDelta.fCurValue);
	else // 카메라 높이 세팅 (백뷰라면, 카메라의 높이를 낮춘다 -> 일반뷰라면 0들어감)	 
		fY = (sinf(fTheta) * m_pCameraCom->m_fDistance * CAM_HEIGHT_MAG) - (m_fJumpDelta.fCurValue * 0.25f); // m_fJumpDelta.fCurValue는 백뷰에서 사용

	// 백뷰라면 바라보는 시점의 높이를 높인다.
	vLerpPos.y += m_fJumpDelta.fCurValue * 0.5f;

	m_pTransformCom->Set_Pos(_vec3{ vLerpPos.x,
									fY,
									vLerpPos.z - m_pCameraCom->m_fDistance }); // m_fJumpDelta.fCurValue는 백뷰에서 사용





	m_pCameraCom->m_tVspace.Eye = m_pTransformCom->Get_Info(INFO_POS);
	m_pCameraCom->m_tVspace.LookAt = vLerpPos;  // m_pCameraCom->m_pLookAt->Get_Transform()->Get_Info(INFO_POS); //vLerpPos;
	m_pCameraCom->m_tVspace.Up = vec3.up;
}

void CPlayer_Camera::Lerp_Enter_Scene()
{ 
	_vec3 vFollowPos = m_pCameraCom->m_pFollow->Get_Transform()->Get_Info(INFO_POS);
	_vec3 vLookPos = vFollowPos;

	vLookPos.y += m_pCameraCom->m_tHeightLerp.fCurValue;

	_vec3 vDir1 = m_pTransformCom->Get_Info(INFO_POS) - vLookPos;
	_vec3 vDir2 = { vDir1.x, 0.f, vDir1.z };
	D3DXVec3Normalize(&vDir1, &vDir1);
	D3DXVec3Normalize(&vDir2, &vDir2);
	_float fTheta = D3DXVec3Dot(&vDir1, &vDir2);
	_float fY = sinf(fTheta) * m_pCameraCom->m_fDistance * CAM_HEIGHT_MAG;

	m_pTransformCom->Set_Pos(_vec3{ vLookPos.x,
									fY,
									vLookPos.z - m_pCameraCom->m_fDistance });

	m_pCameraCom->m_tVspace.Eye = m_pTransformCom->Get_Info(INFO_POS);
	m_pCameraCom->m_tVspace.LookAt = vLookPos;  
	m_pCameraCom->m_tVspace.Up = vec3.up;

	if (!m_pCameraCom->m_tHeightLerp.bActive)
		CCameraMgr::GetInstance()->Set_CurCameraAction(CAMERA_ACTION::NONE);
}

void CPlayer_Camera::Lerp_Change_Target()
{
	_vec3 vFollowPos = m_pCameraCom->m_tVec3Lerp.vCurVec;

	if (0 == D3DXVec3Length(&vFollowPos))	return;
		
	_vec3 vLookPos = vFollowPos;

	// 02. 타겟까지의 디스턴스에 따른 카메라의 높이값을 구한다.
	_vec3 vDir1 = m_pTransformCom->Get_Info(INFO_POS) - vLookPos;
	_vec3 vDir2 = { vDir1.x, 0.f, vDir1.z };
	D3DXVec3Normalize(&vDir1, &vDir1);
	D3DXVec3Normalize(&vDir2, &vDir2);
	_float fTheta = D3DXVec3Dot(&vDir1, &vDir2);
	_float fY = sinf(fTheta) * m_pCameraCom->m_fDistance * CAM_HEIGHT_MAG;

	m_pTransformCom->Set_Pos(_vec3{ vLookPos.x,
									fY,
									vLookPos.z - m_pCameraCom->m_fDistance });


	m_pCameraCom->m_tVspace.Eye = m_pTransformCom->Get_Info(INFO_POS);
	m_pCameraCom->m_tVspace.LookAt = vLookPos;  // m_pCameraCom->m_pLookAt->Get_Transform()->Get_Info(INFO_POS); //vLerpPos;
	m_pCameraCom->m_tVspace.Up = vec3.up;

	if (!m_pCameraCom->m_tVec3Lerp.bActive && !CCameraMgr::GetInstance()->Is_Fix())
		CCameraMgr::GetInstance()->Set_CurCameraAction(CAMERA_ACTION::NONE);
}

void CPlayer_Camera::Free()
{
	__super::Free();
}

CPlayer_Camera* CPlayer_Camera::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CPlayer_Camera*	pInstance = new CPlayer_Camera(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Player Camera Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CPlayer_Camera::Set_BackView(const _bool& _bBackView)
{
	if (_bBackView && !m_bBackView)
	{
		m_pCameraCom->m_tDistanceLerp.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
		m_pCameraCom->m_tDistanceLerp.Set_Lerp(1.f, m_pCameraCom->m_fDistance, CAM_DISTANCE_JUMP);
		m_fJumpDelta.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
		m_fJumpDelta.Set_Lerp(1.f, 0, 10.f);
		m_bBackView = TRUE;
	}
	else if(!_bBackView && m_bBackView)
	{
		m_pCameraCom->m_tDistanceLerp.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
		m_pCameraCom->m_tDistanceLerp.Set_Lerp(1.f, m_pCameraCom->m_fDistance, CAM_DISTANCE_DEFAULT);

		m_fJumpDelta.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
		m_fJumpDelta.Set_Lerp(1.f, 10.f, 0);
		m_fJumpDelta.fCurValue = 10.f;

		m_bBackView = FALSE;
	}
}

void CPlayer_Camera::Set_FlightView(const _bool& _bFlightView)
{
	if (_bFlightView && !m_bFlightView)
	{
		m_fFlightDelta.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
		m_fFlightDelta.Set_Lerp(1.f, 0.f, 8.f);
		m_bFlightView = TRUE;

	}
	else if (!_bFlightView && m_bFlightView)
	{
		//m_fFlightDelta.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
		m_fFlightDelta.bActive = TRUE;
		m_fFlightDelta.fCurTime = 0.f;
		m_fFlightDelta.eMode = LERP_MODE::SMOOTHERSTEP;
		m_fFlightDelta.Set_Lerp(1.f, m_fFlightDelta.fCurValue, 0.f);

		m_bFlightView = FALSE;
	}
}
