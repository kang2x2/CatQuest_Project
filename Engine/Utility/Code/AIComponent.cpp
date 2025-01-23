#include "..\..\Header\AIComponent.h"
#include "GameObject.h"
#include "Transform.h"
#include <ctime>

#include <iostream>

CAIComponent::CAIComponent()
{
}

CAIComponent::CAIComponent(LPDIRECT3DDEVICE9 pGraphicDev)
	: CComponent(pGraphicDev, COMPONENT_TYPE::AICOM)
{
}

CAIComponent::CAIComponent(const CAIComponent& rhs, CGameObject* _pOwnerObject)
	: CComponent(rhs, _pOwnerObject)
{
}

CAIComponent::~CAIComponent()
{
}

HRESULT CAIComponent::Ready_AICom()
{
	 
	return S_OK;
}

_int CAIComponent::Update_Component(const _float& fTimeDelta)
{
	return 0;
}


void CAIComponent::Random_Move(const _float& fTimeDelta, const _float& fSpeed)
{
	_int RandomDir;

	_vec3 vOwnerScale = m_pOwnerObject->Get_Transform()->Get_Scale();


	RandomDir = rand() % 12 + 1;
	//m_pOwnerObject->Get_Transform()->Set_Dir(vec3.zero);

	//float PreDirX = m_pOwnerObject->Get_Transform()->Get_Dir().x;

	switch (RandomDir)
	{
	case 1:
		m_pOwnerObject->Get_Transform()->Set_Dir(vec3.right);
		break;
	case 2:
		m_pOwnerObject->Get_Transform()->Set_Dir(vec3.zero);  // 멈춤
		break;
	case 3:
		m_pOwnerObject->Get_Transform()->Set_Dir(vec3.left);
		break;
	case 4:
		m_pOwnerObject->Get_Transform()->Set_Dir(vec3.forward);
		break;
	case 5:
		m_pOwnerObject->Get_Transform()->Set_Dir(vec3.back);
		break;
	case 6:
		m_pOwnerObject->Get_Transform()->Set_Dir(vec3.zero);  // 멈춤
		break;
	case 7:
		m_pOwnerObject->Get_Transform()->Set_Dir({ 1.f,0.f,1.f }); // 오른 대각 위
		break;
	case 8:
		m_pOwnerObject->Get_Transform()->Set_Dir({ -1.f,0.f,1.f }); // 왼 대각 위
		break;
	case 9:
		m_pOwnerObject->Get_Transform()->Set_Dir({ 1.f,0.f,-1.f }); // 오른 대각 아래
		break;
	case 10:
		m_pOwnerObject->Get_Transform()->Set_Dir(vec3.zero);  // 멈춤
		break;
	case 11:
		m_pOwnerObject->Get_Transform()->Set_Dir({ -1.f, 0.f, -1.f }); // 왼 대각 아래 
		break;
	case 12:
		m_pOwnerObject->Get_Transform()->Set_Dir(vec3.zero);  // 멈춤
		break;
	default:
		m_pOwnerObject->Get_Transform()->Set_Dir(vec3.zero);
		break;
	}

	float CurDirX = m_pOwnerObject->Get_Transform()->Get_Dir().x;

	//cout << PreDirX << "\t" << CurDirX << endl;


	if (CurDirX < 0  && vOwnerScale.x >0)
	{
		m_pOwnerObject->Get_Transform()->Set_Scale({ -vOwnerScale.x, vOwnerScale.y, vOwnerScale.z });
	}
	else if (CurDirX > 0 && vOwnerScale.x < 0)
	{
		m_pOwnerObject->Get_Transform()->Set_Scale({ -vOwnerScale.x, vOwnerScale.y, vOwnerScale.z });
	}
	else
	{
		m_pOwnerObject->Get_Transform()->Set_Scale({ vOwnerScale.x, vOwnerScale.y, vOwnerScale.z });
	}

}


void CAIComponent::Chase_TargetY(const _vec3* pTargetPos, const _float& fTimeDelta, const _float& fSpeed)
{
	_vec3 vOwnerDir;
	vOwnerDir = CComponent::Get_OwnerObject()->Get_Transform()->Get_Dir();

	_vec3 vOwnerPos;
	vOwnerPos = CComponent::Get_OwnerObject()->Get_Transform()->Get_Info(INFO_POS);

	_vec3 vDir = *pTargetPos - vOwnerPos;



	vOwnerPos += *D3DXVec3Normalize(&vDir, &vDir) * fTimeDelta * fSpeed;

	_matrix		matRot = *Compute_LookAtTarget(pTargetPos);
	_matrix		matScale, matTrans;

	_vec3	vOwnerScale;
	vOwnerScale = CComponent::Get_OwnerObject()->Get_Transform()->Get_Scale();

	D3DXMatrixScaling(&matScale, vOwnerScale.x, vOwnerScale.y, vOwnerScale.z);

	D3DXMatrixTranslation(&matTrans, vOwnerPos.x, vOwnerPos.y, vOwnerPos.z);


	_matrix		m_matWorld = CComponent::Get_OwnerObject()->Get_Transform()->Get_WorldMat();
	m_matWorld = matScale * matRot * matTrans;


	// 월드 반영
	//CComponent::Get_OwnerObject()->Get_Transform()->Set_Pos({ m_matWorld._41, m_matWorld._42, m_matWorld._43 });


	_vec3 vNormalDir = *D3DXVec3Normalize(&vDir, &vDir);


	// Y값은 안따라가게 제거한 방향 벡터로 설정
	CComponent::Get_OwnerObject()->Get_Transform()->Set_Dir({ vNormalDir.x , vNormalDir.y, vNormalDir.z });



	// x 이동 방향에 따라 스케일 전환 
	if (vOwnerPos.x < (*pTargetPos).x && vOwnerScale.x < 0)
	{
		m_pOwnerObject->Get_Transform()->Set_Scale({ -vOwnerScale.x , vOwnerScale.y, vOwnerScale.z });
	}
	else if (vOwnerPos.x > (*pTargetPos).x && vOwnerScale.x > 0)
	{
		m_pOwnerObject->Get_Transform()->Set_Scale({ -vOwnerScale.x , vOwnerScale.y, vOwnerScale.z });
	}




}

void CAIComponent::Chase_Target(const _vec3* pTargetPos, const _float& fTimeDelta, const _float& fSpeed)
{
	_vec3 vOwnerDir;
	vOwnerDir = CComponent::Get_OwnerObject()->Get_Transform()->Get_Dir();

	_vec3 vOwnerPos;
	vOwnerPos = CComponent::Get_OwnerObject()->Get_Transform()->Get_Info(INFO_POS);

	_vec3 vDir = *pTargetPos - vOwnerPos;



	vOwnerPos += *D3DXVec3Normalize(&vDir, &vDir) * fTimeDelta * fSpeed;

	_matrix		matRot = *Compute_LookAtTarget(pTargetPos);
	_matrix		matScale, matTrans;

	_vec3	vOwnerScale;
	vOwnerScale = CComponent::Get_OwnerObject()->Get_Transform()->Get_Scale();

	D3DXMatrixScaling(&matScale, vOwnerScale.x, vOwnerScale.y, vOwnerScale.z);
	
	D3DXMatrixTranslation(&matTrans, vOwnerPos.x, vOwnerPos.y, vOwnerPos.z);


	_matrix		m_matWorld = CComponent::Get_OwnerObject()->Get_Transform()->Get_WorldMat();
	m_matWorld = matScale * matRot * matTrans;


	// 월드 반영
	//CComponent::Get_OwnerObject()->Get_Transform()->Set_Pos({ m_matWorld._41, m_matWorld._42, m_matWorld._43 });
	

	 _vec3 vNormalDir = *D3DXVec3Normalize(&vDir, &vDir);


	 // Y값은 안따라가게 제거한 방향 벡터로 설정
	 CComponent::Get_OwnerObject()->Get_Transform()->Set_Dir({ vNormalDir.x , 0.f, vNormalDir.z });

	 

	 // x 이동 방향에 따라 스케일 전환 
	if (vOwnerPos.x < (*pTargetPos).x && vOwnerScale.x <0)
	{
		m_pOwnerObject->Get_Transform()->Set_Scale({ -vOwnerScale.x , vOwnerScale.y, vOwnerScale.z });
	}
	else if (vOwnerPos.x > (*pTargetPos).x  && vOwnerScale.x > 0  )
	{
		m_pOwnerObject->Get_Transform()->Set_Scale({- vOwnerScale.x , vOwnerScale.y, vOwnerScale.z });
	}

	


}
const _matrix* CAIComponent::Compute_LookAtTarget(const _vec3* pTargetPos)
{
	
	_vec3 OwnerPos;
	OwnerPos = CComponent::Get_OwnerObject()->Get_Transform()->Get_Info(INFO_POS);

	_vec3 OwnerLook;
	OwnerLook = CComponent::Get_OwnerObject()->Get_Transform()->Get_Info(INFO_LOOK);
	
	_vec3 OwnerUp;
	OwnerUp = CComponent::Get_OwnerObject()->Get_Transform()->Get_Info(INFO_UP);
	
	_vec3 vDir = *pTargetPos - OwnerPos;


	_matrix		matRot;
	_vec3		vAxis;



	D3DXMatrixLookAtLH(&matRot, &OwnerPos, pTargetPos, &OwnerUp);

	return D3DXMatrixRotationAxis(
									&matRot,
									D3DXVec3Cross(&vAxis, &OwnerUp, &vDir),
									acosf(D3DXVec3Dot(D3DXVec3Normalize(&vDir, &vDir),
									D3DXVec3Normalize(&OwnerUp, &OwnerUp))));
	
	

}

CAIComponent* CAIComponent::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CAIComponent* pInstance = new CAIComponent(pGraphicDev);

	if (FAILED(pInstance->Ready_AICom()))
	{
		Safe_Release(pInstance);

		MSG_BOX("AIComponent Create Failed");
		return nullptr;
	}

	return pInstance;
}

CComponent* CAIComponent::Clone(CGameObject* _pOwnerObject)
{
	return new CAIComponent(*this, _pOwnerObject);
}

void CAIComponent::Free()
{
	CComponent::Free();
}
