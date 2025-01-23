#include "stdafx.h"
#include "Cloud2.h"

#include "Export_Function.h"

#include "Cloud2_Shadow.h"
#include "CameraMgr.h"

#include "ZoomUI.h"

CCloud2::CCloud2(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 vPos)
	: CEffect(pGraphicDev, OBJ_ID::EFFECT_CLOUD_2), m_vCloudPos(vPos)
{
}

CCloud2::CCloud2(const CCloud2& rhs)
	: CEffect(rhs), m_pTextureCom(rhs.m_pTextureCom)
{
}

CCloud2::~CCloud2()
{
}

HRESULT CCloud2::Ready_Object()
{
	// __super::Ready_Object();

	CGameObject::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_real_distribution<float> xDist1(10.f, 15.f);
	m_fDeadTime = xDist1(gen);
	m_fAccTime = 0.f;

	m_bDead_Start = false;

	m_iAlpha = OBJ_CLOUD_MAX_ALPHA;
	m_bStart = true;
	/*m_tLerpAlpha.Init_Lerp(LERP_MODE::SMOOTHSTEP);
	m_tLerpAlpha.Set_Lerp(5.f, 0, 200);*/

	std::uniform_real_distribution<float> xDist2(1.5f, 5.f);
	m_fSpeed = xDist2(gen);

	m_pTransformCom->Set_Scale(_vec3{ 5.f, 3.f, 5.f });
	Set_RandomSize();
	m_pTransformCom->Set_Pos(_vec3{ m_vCloudPos.x, Set_RandomHeight(), m_vCloudPos.z });

	// Add_GameObject를 호출할 때 this가 NULL이다 확인하자.
	CEventMgr::GetInstance()->Add_Obj(L"Cloud2_Shadow", CCloud2_Shadow::Create(m_pGraphicDev, this));

	return S_OK;
}

_int CCloud2::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);
	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	m_pTransformCom->Set_Pos(
		{ this->m_pTransformCom->Get_Info(INFO_POS).x + 0.2f * fTimeDelta * m_fSpeed ,
		 this->m_pTransformCom->Get_Info(INFO_POS).y ,
		 this->m_pTransformCom->Get_Info(INFO_POS).z }
	);

	if (!m_tLerpAlpha.bActive)
		m_bStart = false;


	if (m_bStart)
	{
		m_tLerpAlpha.Update_Lerp(fTimeDelta);
		m_iAlpha = m_tLerpAlpha.fCurValue;

		return iExit;
	}

	m_fAccTime += fTimeDelta;
	if (m_fAccTime >= m_fDeadTime && !m_bDead_Start)
	{
		m_tLerpAlpha.Init_Lerp(LERP_MODE::SMOOTHSTEP);
		m_tLerpAlpha.Set_Lerp(5.f, m_iAlpha, 0);
		m_tLerpAlpha.fCurValue = m_tLerpAlpha.fStartValue;
		m_bDead_Start = true;
	}



	if (m_bDead_Start)
	{
		m_tLerpAlpha.Update_Lerp(fTimeDelta);
		m_iAlpha = m_tLerpAlpha.fCurValue;

		if (m_iAlpha == 0)
			CEventMgr::GetInstance()->Delete_Obj(this);
	}

	return iExit;
}

void CCloud2::LateUpdate_Object()
{
	if (!m_bDead_Start && !m_bStart)
	{
		m_iAlpha = (_int)(Get_Distance_From_Camera() * OBJ_CLOUD_MAX_ALPHA_MAG);

		if (OBJ_CLOUD_MAX_ALPHA < m_iAlpha) m_iAlpha = OBJ_CLOUD_MAX_ALPHA;
	}

	__super::LateUpdate_Object();
}

void CCloud2::Render_Object()
{
	/*CZoomUI* pUI = static_cast<CZoomUI*>(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"UI_Zoom"));
	NULL_CHECK(pUI);
	if (pUI->Get_ZoomState() == 1)
		return;*/


	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(m_iAlpha, 255, 255, 255));
	m_pTextureCom->Render_Texture(); // 텍스처 세팅 -> 버퍼 세팅 순서 꼭!

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetTexture(0, NULL);

	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

	CEffect::Render_Object();

	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));
}

HRESULT CCloud2::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Colud2", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	return S_OK;
}

void CCloud2::Play_Effect(const _vec3& _vPos, const _vec3& _vSize)
{
	m_vOffSet = _vPos;
	m_vSize = _vSize;
	m_bActive = true;
}

const _float CCloud2::Get_Distance_From_Camera()
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

void CCloud2::Set_RandomSize()
{
	_vec3 vScale = m_pTransformCom->Get_Scale();

	_float fMag = (rand() % 10 + 1) * 0.1f;
	fMag += rand() % 2 + 1;
	if (OBJ_CLOUD_MAX_SIZE_MAG < fMag)
		fMag = OBJ_CLOUD_MAX_SIZE_MAG;
	vScale *= fMag;
	m_pTransformCom->Set_Scale(_vec3{ vScale });
}

const _float CCloud2::Set_RandomHeight()
{
	return (rand() % 5 + 15);

}

CCloud2* CCloud2::Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 vPos)
{
	CCloud2* pInstance = new CCloud2(pGraphicDev, vPos);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Effect_Cloud2 Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CCloud2::Free()
{
	__super::Free();
}
