#include "stdafx.h"
#include "RangeObj.h"

#include "Export_Function.h"

#include "SphereCollider.h"

CRangeObj::CRangeObj(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject, const _float& _fRadius)
	: Engine::CGameObject(pGraphicDev, OBJ_TYPE::RANGE_OBJ, OBJ_ID::RANGE_OBJ)
	, m_pOwnerObject(_pOwnerObject)
	, m_fRadius(_fRadius)
	, m_bSetPos(false)
{
	this->Set_Parent(_pOwnerObject);
	ZeroMemory(&m_vPos, sizeof(_vec3));
}

CRangeObj::CRangeObj(const CRangeObj& rhs)
	: Engine::CGameObject(rhs)
{
}

CRangeObj::~CRangeObj()
{
}

HRESULT CRangeObj::Ready_Object()
{
	CGameObject::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}

_int CRangeObj::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	if (!m_pOwnerObject->Is_Active())
	{
		Set_Active(false);

		return iExit;
	}


	Engine::Add_RenderGroup(RENDER_NONALPHA, this);

	return iExit;
}

void CRangeObj::LateUpdate_Object()
{
	__super::LateUpdate_Object();

	_vec3 vOwnerPos;

	if (m_bSetPos)
		vOwnerPos = m_vPos;
	else
		vOwnerPos = m_pOwnerObject->Get_Transform()->Get_Info(INFO_POS);


	if (m_pOwnerObject->Get_ID() != OBJ_ID::SKILL_BOSS_BLOODYTHUNDER || m_pOwnerObject->Get_ID() != OBJ_ID::SKILL_BOSS_BLUETHUNDER)
	{

		m_pTransformCom->Set_Pos(_vec3{ vOwnerPos.x, 0.f, vOwnerPos.z }); // 레인지의 y 포지션은 계산을 위해 0으로 잡는다.
	}



}

void CRangeObj::Render_Object()
{
	_matrix  matWorld = Get_Transform()->Get_WorldMat();

	_matrix matBill;
	D3DXMatrixIdentity(&matBill);

	_vec3 vPos, vScale;

	if (m_bSetPos)
		vPos = m_vPos;
	else
		memcpy(&vPos, &matWorld.m[3], sizeof(_vec3));

	vScale = m_pTransformCom->Get_Scale();

	matWorld *= *D3DXMatrixInverse(&matBill, NULL, &CCameraMgr::GetInstance()->Get_Billboard_X());
	memcpy(&matWorld.m[3], &vPos, sizeof(_vec3));

	matWorld._11 = vScale.x;
	matWorld._22 = vScale.y;
	matWorld._33 = vScale.z;

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);

	__super::Render_Object();
}

void CRangeObj::OnCollision_Enter(CGameObject* _pColObj)
{
	m_pOwnerObject->OnCollision_Enter(_pColObj);
}

void CRangeObj::OnCollision_Stay(CGameObject* _pColObj)
{
	m_pOwnerObject->OnCollision_Stay(_pColObj);
}

void CRangeObj::OnCollision_Exit(CGameObject* _pColObj)
{
	m_pOwnerObject->OnCollision_Exit(_pColObj);
}

void CRangeObj::Set_Radius(const _float& _fRadius)
{
	m_fRadius = _fRadius;

	CSphereCollider* pCol = dynamic_cast<CSphereCollider*>(m_pColliderCom);

	NULL_CHECK(pCol);

	pCol->Set_Radius(m_fRadius);
}

HRESULT CRangeObj::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pColliderCom = dynamic_cast<CSphereCollider*>(Engine::Clone_Proto(COMPONENT_TYPE::COL_SPHERE, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::COL_SPHERE, pComponent);

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	return S_OK;
}

CRangeObj* CRangeObj::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject, const _float& _fRadius)
{
	CRangeObj* pInstance = new CRangeObj(pGraphicDev, _pOwnerObject, _fRadius);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("RangeObj Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CRangeObj::Free()
{
	__super::Free();
}
