#include "..\..\Header\LineObject.h"

#include "Export_Function.h"

#include "ProtoMgr.h"

CLineObject::CLineObject(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev, OBJ_TYPE::LINE, OBJ_ID::LINE)
	, m_eCurLineType(LINE_TYPE::TYPEEND)
	, m_ePrevLineType(LINE_TYPE::TYPEEND)

{
	CCollisionMgr::GetInstance()->Add_Line(this);
}

CLineObject::CLineObject(const CLineObject& rhs)
	: Engine::CGameObject(rhs)
	, m_eCurLineType(rhs.m_eCurLineType)
	, m_ePrevLineType(rhs.m_ePrevLineType)

{
}

CLineObject::~CLineObject()
{
}

HRESULT CLineObject::Ready_Object(const _vec3& vPoint1, const _vec3& vPoint2)
{
	CGameObject::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(vPoint1, vPoint2), E_FAIL);

	return S_OK;
}

_int CLineObject::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CLineObject::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CLineObject::Render_Object()
{
	__super::Render_Object(); // 콜라이더 출력
}

HRESULT CLineObject::Add_Component(const _vec3& vPoint1, const _vec3& vPoint2)
{
	CComponent* pComponent = nullptr;
	pComponent = m_pColliderCom = dynamic_cast<CLineCollider*>(CProtoMgr::GetInstance()->Clone_Proto(COMPONENT_TYPE::COL_LINE, this));
	static_cast<CLineCollider*>(m_pColliderCom)->Set_PointList(vPoint1, vPoint2);
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::COL_LINE, pComponent);

	return S_OK;
}

CLineObject* CLineObject::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPoint1, const _vec3& vPoint2)
{
	CLineObject* pInstance = new CLineObject(pGraphicDev);

	if (FAILED(pInstance->Ready_Object(vPoint1, vPoint2)))
	{
		Safe_Release(pInstance);

		MSG_BOX("Line Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CLineObject::Free()
{
	CGameObject::Free();
}
