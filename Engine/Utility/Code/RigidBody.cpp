#include "..\..\Header\RigidBody.h"

#include "GameObject.h"
#include "Export_Function.h"
#include "CameraMgr.h"
CRigidBody::CRigidBody()
{
	
}

CRigidBody::CRigidBody(LPDIRECT3DDEVICE9 pGraphicDev)
	: CComponent(pGraphicDev, COMPONENT_TYPE::RIGIDBODY)
{
	/*--------------------- ! 수정이나 추가시 반드시 팀장 보고 !  ---------------------*/

	ZeroMemory(&m_vForce, sizeof(_vec3));
	ZeroMemory(&m_vAcc, sizeof(_vec3));
	ZeroMemory(&m_vVelocity, sizeof(_vec3));

	m_fMass		= 8.f;
	m_fMaxSpeed = DF_RB_MAXSPEED;
	m_fFriction = 0.05f;
	m_vGravity	= vec3.down;
	m_bJump		= FALSE;
	m_fStartY	= 0.f;
	m_bKnockUp	= FALSE;
}

CRigidBody::CRigidBody(const CRigidBody& rhs, CGameObject* _pOwnerObject)
	: CComponent(rhs, _pOwnerObject)
	, m_vForce(rhs.m_vForce)
	, m_vAcc(rhs.m_vAcc)
	, m_vVelocity(rhs.m_vVelocity)
	, m_vGravity(rhs.m_vGravity)
	, m_fMass(rhs.m_fMass)
	, m_fMaxSpeed(rhs.m_fMaxSpeed)
	, m_fFriction(rhs.m_fFriction)
	, m_bJump(rhs.m_bJump)
	, m_fStartY(rhs.m_fStartY)
	, m_bKnockUp(rhs.m_bKnockUp)

{
	Ready_RigidBody();
}

CRigidBody::~CRigidBody()
{
}

HRESULT CRigidBody::Ready_RigidBody()
{

	return S_OK;
}

void CRigidBody::LateUpdate_Component()
{
	/*--------------------- ! 수정이나 추가시 반드시 팀장 보고 !  ---------------------*/

	// 현재 속도 계산
	NULL_CHECK(m_pOwnerObject);

	if (m_bJump || m_bKnockUp)
	{
		const _vec3 vGrabity{ 0.f, -4.f, 0.f };
		m_vForce += (vGrabity * m_fMass);
	}
	else
	{
		m_vForce += (m_vGravity * m_fMass);
		m_vForce.y = 0;
	}

	if (D3DXVec3Length(&m_vForce) > 0.f && (!m_bJump && !m_bKnockUp)) // 임시 마찰  // && !m_bKnockUp
		m_vForce -= m_vForce * m_fFriction;

	m_vAcc = m_vForce / m_fMass;
	                 
	m_vVelocity = m_vAcc * Engine::Get_TimeDelta(L"Timer_FPS65");

	if (D3DXVec3Length(&m_vVelocity) > m_fMaxSpeed)
	{
		D3DXVec3Normalize(&m_vVelocity, &m_vVelocity);
		m_vVelocity *= m_fMaxSpeed;
	}
	
	_vec3 vPos = m_pOwnerObject->Get_Transform()->Get_Info(INFO_POS);

	vPos += m_vVelocity;

	if (m_bJump || m_bKnockUp) // m_bKnockUp
	{
		if (vPos.y < m_fStartY)
		{
			m_bJump = FALSE;
			m_bKnockUp = FALSE;
			vPos.y = m_fStartY;
		}
	}

	m_pOwnerObject->Get_Transform()->Set_Pos(vPos);
}

void CRigidBody::Knock_Back(const _vec3& _vDir, const _float& _fImpulse)
{
	/*--------------------- ! 수정이나 추가시 반드시 팀장 보고 !  ---------------------*/

	_vec3 vDir;

	if (1.3f < D3DXVec3Length(&_vDir))
		D3DXVec3Normalize(&vDir, &_vDir);
	else
		vDir = _vDir;

	Add_Impulse(vDir * _fImpulse);
}

void CRigidBody::Knock_Back(CGameObject* _pAttacker, const _float& _fImpulse)
{
	/*--------------------- ! 수정이나 추가시 반드시 팀장 보고 !  ---------------------*/

	NULL_CHECK(_pAttacker);

	_vec3 vDir = m_pOwnerObject->Get_Transform()->Get_Info(INFO_POS) - _pAttacker->Get_Transform()->Get_Info(INFO_POS);

	D3DXVec3Normalize(&vDir, &vDir);

	Add_Impulse(vDir * _fImpulse);
}

void CRigidBody::Knock_Up(const _float& _fImpulse)
{
	if (m_bKnockUp) return;

	Set_MaxSpeed(DF_RB_MAXSPEED);
	m_bKnockUp = TRUE;
	Add_Impulse(vec3.up * _fImpulse);
	m_fStartY = m_pOwnerObject->Get_Transform()->Get_Info(INFO_POS).y;
}

void CRigidBody::Knock_Up(const _vec3& _vDir, const _float& _fImpulse)
{
	if (m_bKnockUp) return;

	_vec3 vDir;

	if (1.3f < D3DXVec3Length(&_vDir))
		D3DXVec3Normalize(&vDir, &_vDir);
	else
		vDir = _vDir;

	Set_MaxSpeed(DF_RB_MAXSPEED);
	m_bKnockUp = TRUE;
	Add_Impulse(vDir * _fImpulse);
	m_fStartY = m_pOwnerObject->Get_Transform()->Get_Info(INFO_POS).y;
}

void CRigidBody::Jump()
{
	if (!CCameraMgr::GetInstance()->Get_CurCamera()->Is_BackView() || m_bJump)
		return;

	Set_MaxSpeed(DF_RB_MAXSPEED);
	m_bJump = TRUE;
	Add_Impulse(vec3.up * JUMP_POWER);
	m_fStartY = m_pOwnerObject->Get_Transform()->Get_Info(INFO_POS).y;
}


CRigidBody* CRigidBody::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CRigidBody* pInstance = new CRigidBody(pGraphicDev);

	if (FAILED(pInstance->Ready_RigidBody()))
	{
		Safe_Release(pInstance);
		MSG_BOX("RigidBody Create Failed");
		return nullptr;
	}

	return pInstance;
}

CComponent* CRigidBody::Clone(CGameObject* _pOwnerObject)
{
	return new CRigidBody(*this, _pOwnerObject);
}

void CRigidBody::Free()
{
	CComponent::Free();
}
