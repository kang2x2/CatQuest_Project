#include "..\..\Header\CameraMgr.h"

#include "..\..\Header\GameObject.h"

#include "Transform.h"
#include "Management.h"

IMPLEMENT_SINGLETON(CCameraMgr)

CCameraMgr::CCameraMgr()
	: m_pCurCamera(nullptr)
	, m_pPreCamera(nullptr)
	, m_bBlending(false)
	, m_eCurAction(CAMERA_ACTION::NONE)
	, m_bFix(FALSE)
	, m_bBoss(FALSE)
{
}

CCameraMgr::~CCameraMgr()
{
	Free();
}

CCameraObject * CCameraMgr::Get_Camera(const _tchar * pCameraTag)
{
	return nullptr;
}

HRESULT CCameraMgr::Add_Camera(const _tchar * pCameraTag, CCameraObject * pCameraObject)
{
	CCameraObject* pCamera = Find_Camera(pCameraTag);

	if (nullptr != pCamera) return E_FAIL;

	m_mapCamera.emplace(pCameraTag, pCameraObject);

	return S_OK;
}

HRESULT CCameraMgr::Set_MainCamera(const _tchar * pCameraTag)
{
	CCameraObject* pChangeCamera = Find_Camera(pCameraTag);

	NULL_CHECK_RETURN(pChangeCamera, E_FAIL);

	if (1 == m_mapCamera.size())
		m_pCurCamera = m_pPreCamera = pChangeCamera;
	else
	{
		FAILED_CHECK_RETURN(Change_Camera(pCameraTag), E_FAIL);
		return S_OK;
	}

	FAILED_CHECK_RETURN(Set_ViewSpace()	, E_FAIL);
	FAILED_CHECK_RETURN(Set_Projection(), E_FAIL);
	FAILED_CHECK_RETURN(Set_Viewport()	, E_FAIL);

	return S_OK;
}

HRESULT CCameraMgr::Change_Camera(const _tchar * pCameraTag)
{
	CCameraObject* pChangeCamera = Find_Camera(pCameraTag);

	NULL_CHECK_RETURN(pChangeCamera, E_FAIL);

	m_pPreCamera = m_pCurCamera;

	m_pCurCamera = pChangeCamera;

	m_bBlending = true;

	FAILED_CHECK_RETURN(Set_ViewSpace()	, E_FAIL);
	FAILED_CHECK_RETURN(Set_Projection(), E_FAIL);
	FAILED_CHECK_RETURN(Set_Viewport()	, E_FAIL);

	return S_OK;
}

const _matrix& CCameraMgr::Get_Billboard_X()
{
	NULL_CHECK_RETURN(m_pCurCamera, _matrix{});

	NULL_CHECK_RETURN(m_pCurCamera->Get_CameraCom(), _matrix{});

	return m_pCurCamera->Get_CameraCom()->m_matBillboardX;
}

const _matrix& CCameraMgr::Get_Billboard_Y()
{
	NULL_CHECK_RETURN(m_pCurCamera, _matrix{});

	NULL_CHECK_RETURN(m_pCurCamera->Get_CameraCom(), _matrix{});

	return m_pCurCamera->Get_CameraCom()->m_matBillboardY;
}

const _matrix& CCameraMgr::Get_WorldMat()
{
	NULL_CHECK_RETURN(m_pCurCamera, _matrix{});

	NULL_CHECK_RETURN(m_pCurCamera->Get_CameraCom(), _matrix{});

	return m_pCurCamera->Get_CameraCom()->m_matWorld;
}

void CCameraMgr::Start_Fade(const FADE_MODE& _eMode)
{
	NULL_CHECK(m_pCurCamera);

	m_pCurCamera->Start_Fade(_eMode);
}

HRESULT CCameraMgr::Set_ViewSpace()
{
	NULL_CHECK_RETURN(m_pCurCamera, E_FAIL);

	m_pCurCamera->Get_CameraCom()->Set_ViewSpace();

	return S_OK;
}

HRESULT CCameraMgr::Set_Projection()
{
	NULL_CHECK_RETURN(m_pCurCamera, E_FAIL);

	m_pCurCamera->Get_CameraCom()->Set_Projection();

	return S_OK;
}

HRESULT CCameraMgr::Set_Viewport()
{
	NULL_CHECK_RETURN(m_pCurCamera, E_FAIL);

	m_pCurCamera->Get_CameraCom()->Set_Viewport();

	return S_OK;
}

HRESULT CCameraMgr::Set_LookAt(CGameObject* pLookAt)
{
	NULL_CHECK_RETURN(m_pCurCamera, E_FAIL);

	m_pCurCamera->Get_CameraCom()->Set_LookAt(pLookAt);

	return S_OK;
}

HRESULT CCameraMgr::Set_Follow(CGameObject* pFollow)
{
	NULL_CHECK_RETURN(m_pCurCamera, E_FAIL);

	m_pCurCamera->Get_CameraCom()->Set_Follow(pFollow);

	return S_OK;
}

void CCameraMgr::Shake_Camera(const _float& _fTime, const _float& _fIntensity)
{
	m_pCurCamera->Get_CameraCom()->Shake_Camera(_fTime, _fIntensity);
}

const _bool& CCameraMgr::Is_Shake_Camera() const
{
	return m_pCurCamera->Get_CameraCom()->Is_Shake_Camera();
}

void CCameraMgr::Stop_Shake()
{
	m_pCurCamera->Get_CameraCom()->Stop_Shake();
}

const _bool& CCameraMgr::Is_Fade()
{
	NULL_CHECK_RETURN(m_pCurCamera, FALSE);

	return m_pPreCamera->Is_Fade();
}

const _bool& CCameraMgr::Is_BackView() const
{
	NULL_CHECK_RETURN(m_pCurCamera, E_FAIL);

	return m_pCurCamera->Is_BackView();
}

HRESULT CCameraMgr::Start_Action(const CAMERA_ACTION& _eMode, const _vec3& _vStartPos, const _vec3& _vEndPos, const _bool& _bFix)
{	
	/*--------------------- ! �����̳� �߰��� �ݵ�� ���� ���� !  ---------------------*/

	NULL_CHECK_RETURN(m_pCurCamera, E_FAIL);

	m_bFix = _bFix;

	if (CAMERA_TYPE::PLAYER_CAMERA == m_pCurCamera->Get_CameraCom()->Get_CameraType())
	{
		_float fCurFOV = m_pCurCamera->Get_CameraCom()->Get_Projection().FOV;
		_float fTargetFOV = 0.f;

		// ���� ���� ��ų ������(In ~ End)�̶�� ����
		if ((m_eCurAction == CAMERA_ACTION::BOSS_SKILL_IN && _eMode != CAMERA_ACTION::BOSS_SKILL_OUT ) 
			|| (m_eCurAction == CAMERA_ACTION::BOSS_SKILL_OUT && m_pCurCamera->Get_CameraCom()->m_tFOVLerp.bActive))
			return S_OK;

		switch (_eMode)
		{
		// BOSS
		case Engine::CAMERA_ACTION::BOSS_SKILL_IN :
		{
			fTargetFOV = CAM_FOV_BOSS_SKILL;
			m_pCurCamera->Get_CameraCom()->Lerp_FOV(0.7f, fCurFOV, fTargetFOV, LERP_MODE::SMOOTHERSTEP);
		}
		break;
		case Engine::CAMERA_ACTION::BOSS_SKILL_OUT:
		{
			fTargetFOV = CAM_FOV_DEFAULT + CAM_FOV_BOSS_DELTA;
			m_pCurCamera->Get_CameraCom()->Lerp_FOV(0.7f, fCurFOV, fTargetFOV, LERP_MODE::SMOOTHERSTEP);
		}
		break;

		// IDLE -> OTHER
		case Engine::CAMERA_ACTION::PLAYER_IDL_TO_ATK : 
		{
			if (m_bBoss)
				fTargetFOV = CAM_FOV_PLAYER_ATTACK + CAM_FOV_BOSS_DELTA;
			else
				fTargetFOV = CAM_FOV_PLAYER_ATTACK;

			m_pCurCamera->Get_CameraCom()->Lerp_FOV(0.15f, fCurFOV, fTargetFOV, LERP_MODE::SMOOTHERSTEP);
		}
		break;
		case Engine::CAMERA_ACTION::PLAYER_IDL_TO_FLY : 
		{
			if (m_bBoss)
				fTargetFOV = CAM_FOV_PLAYER_FLIGHT + CAM_FOV_BOSS_DELTA;
			else
				fTargetFOV = CAM_FOV_PLAYER_FLIGHT;

			m_pCurCamera->Set_FlightView(TRUE);
			m_pCurCamera->Get_CameraCom()->Lerp_FOV(1.f, fCurFOV, fTargetFOV, LERP_MODE::SMOOTHERSTEP); 
		}
		break;

		// OTHER -> OTHER
		case Engine::CAMERA_ACTION::PLAYER_ATK_TO_IDL : 
		{
			if (m_bBoss)
				fTargetFOV = CAM_FOV_DEFAULT + CAM_FOV_BOSS_DELTA;
			else
				fTargetFOV = CAM_FOV_DEFAULT;

			m_pCurCamera->Get_CameraCom()->Lerp_FOV( 0.15f, fCurFOV, fTargetFOV, LERP_MODE::SMOOTHERSTEP);
		}
		break;
		case Engine::CAMERA_ACTION::PLAYER_FLY_TO_IDL : 
		{
			if (m_bBoss)
				fTargetFOV = CAM_FOV_DEFAULT + CAM_FOV_BOSS_DELTA;
			else
				fTargetFOV = CAM_FOV_DEFAULT;

			m_pCurCamera->Set_FlightView(FALSE);
			m_pCurCamera->Get_CameraCom()->Lerp_FOV(1.f, fCurFOV, fTargetFOV, LERP_MODE::SMOOTHERSTEP); break;
		}


		// TOP & BACK
		case Engine::CAMERA_ACTION::PLAYER_TOP_TO_BACK:
		{
			if (CAMERA_TYPE::PLAYER_CAMERA == m_pCurCamera->Get_CameraCom()->Get_CameraType())
				m_pCurCamera->Set_BackView(TRUE);
		}
		break;

		case Engine::CAMERA_ACTION::PLAYER_BACK_TO_TOP:
		{
			if (CAMERA_TYPE::PLAYER_CAMERA == m_pCurCamera->Get_CameraCom()->Get_CameraType())
				m_pCurCamera->Set_BackView(FALSE);
		}
		break;



		case Engine::CAMERA_ACTION::SCENE_ENTER_INGAME:
		{
		/*
		
			*	�ʵ�� ����� �÷��̾� ������ ī�޶� �������� ����
			

			1. ī�޶� �÷��̾� + y20�� Ÿ������ �ϴ� Eye�� ��ġ��Ų��.

			2. Look�� y�� �����Ͽ� �÷��̾���� ������.

			3. �÷��̾� y�� ��ġ�Ǹ� ������ �����Ѵ�.

		*/
			_vec3 vPlayerPos;		// �÷��̾� ���� ������
			_vec3 vLerpStartLookAt; // �÷��̾� ���� ������ y + fHeight
			const _float fHeight = 25.f;
			_vec3 vCamInitEye;		// �÷��̾� ���������ǿ����� ī�޶� ������

			CGameObject* pPlayer = m_pCurCamera->Get_CameraCom()->Get_Follow();

			NULL_CHECK_RETURN(pPlayer, E_FAIL);

			vPlayerPos = pPlayer->Get_Transform()->Get_Info(INFO_POS);
			vLerpStartLookAt = _vec3{ vPlayerPos.x, vPlayerPos.y + fHeight, vPlayerPos.z };


			// �÷��̾� ���� ������ y + 20 ��ġ�� ī�޶� ��ġ��Ų��.
			CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Set_Eye(vCamInitEye);
			vCamInitEye = CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Calculate_Nonelerp_Eye(vLerpStartLookAt).Eye;

			// ���� y���� ���� ������ �����ϰ�, ī�޶��� �������Ϳ����� �ش� y �������� ������ �Ͽ� �������� ���� �� �� �ֵ��� �Ѵ�.
			m_pCurCamera->Get_CameraCom()->Lerp_Height(4.5f, fHeight, 0, LERP_MODE::SMOOTHERSTEP);
		}
			break;
		case Engine::CAMERA_ACTION::SCENE_EXIT_INGAME:
		{
			_float fEyeHeight = Get_CurCamera()->Get_CameraCom()->Get_ViewSpace().Eye.y;
			_float fDeltaHeight = 45.f;
			m_pCurCamera->Get_CameraCom()->Lerp_Height(4.8f, 0, fDeltaHeight, LERP_MODE::EASE_IN);
		}
			break;

		case Engine::CAMERA_ACTION::SCENE_ENTER_FIELD:
		{
			_vec3 vPlayerPos;		// �÷��̾� ���� ������
			_vec3 vLerpStartLookAt; // �÷��̾� ���� ������ y + fHeight
			const _float fHeight = 15.f;
			_vec3 vCamInitEye;		// �÷��̾� ���������ǿ����� ī�޶� ������

			CGameObject* pPlayer = m_pCurCamera->Get_CameraCom()->Get_Follow();

			NULL_CHECK_RETURN(pPlayer, E_FAIL);

			vPlayerPos = pPlayer->Get_Transform()->Get_Info(INFO_POS);
			vLerpStartLookAt = _vec3{ vPlayerPos.x, vPlayerPos.y + fHeight, vPlayerPos.z };


			// �÷��̾� ���� ������ y + 20 ��ġ�� ī�޶� ��ġ��Ų��.
			vCamInitEye = CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Calculate_Nonelerp_Eye(vLerpStartLookAt).Eye;
			CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Set_Eye(vCamInitEye);

			// ���� y���� ���� ������ �����ϰ�, ī�޶��� �������Ϳ����� �ش� y �������� ������ �Ͽ� �������� ���� �� �� �ֵ��� �Ѵ�.
			m_pCurCamera->Get_CameraCom()->Lerp_Height(2.5f, fHeight, 0, LERP_MODE::SMOOTHERSTEP);
		}
		break;



		case Engine::CAMERA_ACTION::OBJ_CHANGE_TARGET:
		{
			/*
				���� ��ġ -> ���� ��ġ -> ���� ��ġ

				�ȷο� �� ����� ��ġ�� �����Ѵ�.

				���� ��ġ�� ������ġ�� ����Ʈ �Ű������� �����Ѵ�.
			*/

			// �� ���� ������ �Ÿ��� ����Ͽ� ���� �ð��� ���ϵ��� �Ѵ�.
			_float fDistance = D3DXVec3Length(&(_vStartPos - _vEndPos));

			_float fMag = 0.015f;

			// y�� ���� ������ ������ �Ѵ�.
			_vec3 vOrigin = _vStartPos;
			_vec3 vDest = _vEndPos;

			if(m_bBoss)
				m_pCurCamera->Get_CameraCom()->Lerp_Vec3(3.f, vOrigin, vDest, LERP_MODE::EASE_OUT);
			else
				m_pCurCamera->Get_CameraCom()->Lerp_Vec3(fDistance * fMag, vOrigin, vDest, LERP_MODE::SMOOTHERSTEP);		
		}
		break;


		// NPC
		case Engine::CAMERA_ACTION::START_NPC_TALK:
		{ 
			m_pCurCamera->Get_CameraCom()->Lerp_FOV(
			0.8f, fCurFOV, CAM_FOV_QUEST_TAKL, LERP_MODE::SMOOTHERSTEP); 
		}
		break;
		case Engine::CAMERA_ACTION::END_NPC_TALK:
		{
			m_pCurCamera->Get_CameraCom()->Lerp_FOV(
			0.5f, fCurFOV, CAM_FOV_DEFAULT, LERP_MODE::SMOOTHERSTEP);
		}
		break;


		// Boss
		case Engine::CAMERA_ACTION::START_BOSS:
		{
			m_bBoss = TRUE;

			fTargetFOV = CAM_FOV_DEFAULT + CAM_FOV_BOSS_DELTA;
		

			m_pCurCamera->Get_CameraCom()->Lerp_FOV(
				0.8f, fCurFOV, fTargetFOV, LERP_MODE::SMOOTHERSTEP);
		}
		break;

		case Engine::CAMERA_ACTION::END_BOSS:
		{
			m_bBoss = FALSE;

			fTargetFOV = CAM_FOV_DEFAULT;

			m_pCurCamera->Get_CameraCom()->Lerp_FOV(
				0.5f, fCurFOV, fTargetFOV, LERP_MODE::SMOOTHERSTEP);
		}
		break;
		
		
		
		default:
			break;
		}
		
	}

	Set_CurCameraAction(_eMode);

	return S_OK;
}

CCameraObject * CCameraMgr::Find_Camera(const _tchar * pCameraTag)
{
	auto		iter = find_if(m_mapCamera.begin(), m_mapCamera.end(), CTag_Finder(pCameraTag));

	if (iter == m_mapCamera.end())
		return nullptr;

	return iter->second;
}

void CCameraMgr::Blend_Camera()
{

}

void CCameraMgr::Free()
{
	//for_each(m_mapCamera.begin(), m_mapCamera.end(), CDeleteMap());
	//m_mapCamera.clear();
}
