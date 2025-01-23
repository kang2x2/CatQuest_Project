#include "..\..\Header\GameObject.h"

#include "Management.h"
#include "ProtoMgr.h"
#include "CameraMgr.h"

#include "Transform.h"
#include "Collider.h"
#include "VIBuffer.h"
#include "Animator.h"

CGameObject::CGameObject(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_TYPE& _eType, const OBJ_ID& _eID)
	: m_pGraphicDev(pGraphicDev)
	, m_pParentObj(nullptr)
	, m_pTransformCom(nullptr)
	, m_pColliderCom(nullptr)
	, m_pBufferCom(nullptr)
	, m_pAnimatorCom(nullptr)
	, m_pRigidBodyCom(nullptr)
	, m_eType(_eType)
	, m_bEventSwitch(false)
	, m_bEnter(false)
	, m_eID(_eID)
	, m_eUILayer(UI_LAYER::LV0)
	, m_bMaintain(false)
{
	m_pGraphicDev->AddRef();
}

CGameObject::CGameObject(const CGameObject & rhs)
	: m_pGraphicDev(rhs.m_pGraphicDev)
{
	m_pGraphicDev->AddRef();
}

CGameObject::~CGameObject()
{
}

CComponent * CGameObject::Get_Component(const COMPONENT_TYPE& _eType, COMPONENTID eID)
{
	CComponent*		pComponent = Find_Component(_eType, eID);

	NULL_CHECK_RETURN(pComponent, nullptr);

	return pComponent;
}

HRESULT CGameObject::Ready_Object(void)
{
	CComponent*			pComponent = nullptr;

	pComponent = m_pTransformCom = dynamic_cast<CTransform*>(CProtoMgr::GetInstance()->Clone_Proto(COMPONENT_TYPE::TRANSFORM, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].emplace(COMPONENT_TYPE::TRANSFORM, pComponent);

	return S_OK;
}

_int CGameObject::Update_Object(const _float & fTimeDelta)
{
	for (auto& iter : m_mapComponent[ID_DYNAMIC])
		iter.second->Update_Component(fTimeDelta);
	
	return 0;
}

void CGameObject::LateUpdate_Object(void)
{
	for (auto& iter : m_mapComponent[ID_DYNAMIC])
		iter.second->LateUpdate_Component();
	
	Set_ViewZ();
}

void CGameObject::Render_Object(void)
{
	NULL_CHECK(m_pColliderCom);

	if(CManagement::GetInstance()->Is_Debug())
		m_pColliderCom->Render_Collider();
}

CGameObject * CGameObject::Get_Child(const _uint & _iIndex)
{
	if (m_vecChilds.empty()) return nullptr;

	if (m_vecChilds.size() < _iIndex)
		return nullptr;
	else
		return m_vecChilds[_iIndex];
}

const _float& CGameObject::Get_ViewZ()
{
	return m_fViewZ;
}

void CGameObject::Set_ViewZ()
{
	NULL_CHECK(m_pTransformCom);

	_matrix		matCamWorld;
	_vec3		vCamPos;

	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matCamWorld);

	D3DXMatrixInverse(&matCamWorld, NULL, &matCamWorld);

	memcpy(&vCamPos, &matCamWorld.m[3][0], sizeof(_vec3));

	m_fViewZ = D3DXVec3Length(&(vCamPos - m_pTransformCom->Get_Info(INFO_POS)));
}

const _bool CGameObject::Is_Component(const COMPONENT_TYPE& _eType, COMPONENTID eID) 
{
	CComponent* pComponent = Find_Component(_eType, eID);

	NULL_CHECK_RETURN(pComponent, FALSE);

	return TRUE;
}

CComponent * CGameObject::Find_Component(const COMPONENT_TYPE& _eType, COMPONENTID eID)
{	
	auto	iter = m_mapComponent[eID].find(_eType);
	
	if (iter == m_mapComponent[eID].end())
		return nullptr;

	return iter->second;
}

void CGameObject::Free()
{
	for (size_t i = 0; i < ID_END; ++i)
	{
		for_each(m_mapComponent[i].begin(), m_mapComponent[i].end(), CDeleteMap());
		m_mapComponent[i].clear();
	}

	Safe_Release(m_pGraphicDev);
}
