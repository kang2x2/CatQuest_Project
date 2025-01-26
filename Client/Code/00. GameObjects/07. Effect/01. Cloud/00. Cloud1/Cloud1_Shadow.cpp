#include "stdafx.h"
#include "Cloud1_Shadow.h"
#include "Cloud1.h"
#include "Export_Function.h"
#include "CameraMgr.h"
CCloud1_Shadow::CCloud1_Shadow(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
	: CEffect(pGraphicDev, _pOwnerObject, OBJ_ID::EFFECT_CLOUD_1), m_pTextureCom(nullptr)
{
	m_pOwnerobject = _pOwnerObject;
}

CCloud1_Shadow::CCloud1_Shadow(const CCloud1_Shadow& rhs)
	: CEffect(rhs)
	, m_pTextureCom(rhs.m_pTextureCom)
{
}

CCloud1_Shadow::~CCloud1_Shadow()
{
}

HRESULT CCloud1_Shadow::Ready_Object()
{
	__super::Ready_Object();

	// CGameObject::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Pos(_vec3{ m_pOwnerobject->Get_Transform()->Get_Info(INFO_POS).x,
		0.02f,
		m_pOwnerobject->Get_Transform()->Get_Info(INFO_POS).z });
	m_pTransformCom->Set_Scale(m_pOwnerobject->Get_Transform()->Get_Scale());

	m_bActive = true;

	return S_OK;
}

_int CCloud1_Shadow::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);
	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	if (!m_pOwnerobject->Is_Active())
		CEventMgr::GetInstance()->Delete_Obj(this);

	m_pTransformCom->Set_Pos(m_pOwnerobject->Get_Transform()->Get_Info(INFO_POS));

	return iExit;
}

void CCloud1_Shadow::LateUpdate_Object()
{
	if (!m_pOwnerobject->Is_Active())
		CEventMgr::GetInstance()->Delete_Obj(this);
	m_iAlpha = static_cast<CCloud1*>(m_pOwnerobject)->Get_CloudAlpha();

	__super::LateUpdate_Object();
}

void CCloud1_Shadow::Render_Object()
{
	if (!m_pOwnerobject->Is_Active())
		CEventMgr::GetInstance()->Delete_Obj(this);
	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(m_iAlpha, 255, 255, 255));

	// 장판 텍스처 출력
	// 빌보드 해제
	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));
	
	_matrix matWorld = m_pOwnerobject->Get_Transform()->Get_WorldMat();
	_matrix matBill;
	_vec3 vPos;
	
	memcpy(&vPos, &matWorld.m[3], sizeof(_vec3));
	vPos += m_vOffSet;
	vPos.y = 0.02f;
	vPos.z -= 7;

	matWorld *= *D3DXMatrixInverse(&matBill, NULL, &CCameraMgr::GetInstance()->Get_Billboard_X());
	memcpy(&matWorld.m[3], &vPos, sizeof(_vec3));

	//matWorld._11 = m_vSize.x;
	//matWorld._22 = m_vSize.y;
	matWorld._33 = 2;

	m_pTextureCom->Render_Texture(); // 텍스처 세팅 -> 버퍼 세팅 순서 꼭!

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);

	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetTexture(0, NULL);

	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));
	// CEffect::Render_Object();
}

HRESULT CCloud1_Shadow::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Colud1_Shadow", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

void CCloud1_Shadow::Play_Effect(const _vec3& _vPos, const _vec3& _vSize)
{
	m_vOffSet = _vPos;
	m_vSize = _vSize;
	m_bActive = true;
}

const _float CCloud1_Shadow::Get_Distance_From_Camera()
{
	CGameObject* pCam = nullptr;

	pCam = CCameraMgr::GetInstance()->Get_CurCamera();

	NULL_CHECK_RETURN(pCam, 0.f);

	_vec3 vCamPos = pCam->Get_Transform()->Get_Info(INFO_POS);
	vCamPos.z += 5.f;

	_vec3 vDist = (vCamPos - m_pTransformCom->Get_Info(INFO_POS));

	// 깊이 차이만 고려한다.
	vDist.x = 0.f;
	vDist.y = 0.f;

	return fabs(D3DXVec3Length(&vDist));
}

CCloud1_Shadow* CCloud1_Shadow::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
{
	CCloud1_Shadow* pInstance = new CCloud1_Shadow(pGraphicDev, _pOwnerObject);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("CCloud1_Shadow Effect Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CCloud1_Shadow::Free()
{
	__super::Free();
}
