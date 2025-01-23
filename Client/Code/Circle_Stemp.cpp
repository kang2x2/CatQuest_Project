#include "stdafx.h"

#include "Export_Function.h"
#include "EventMgr.h"

#include "Circle_Stemp.h"

CCircle_Stemp::CCircle_Stemp(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& _pPos)
	: CEffect(pGraphicDev, OBJ_ID::EFFECT_CIRCLE_STEMP)
{
	m_vPos = _pPos;

	ZeroMemory(&m_tLerpSize, sizeof(LERP_FLOAT_INFO));
	ZeroMemory(&m_tLerpAlpha, sizeof(LERP_FLOAT_INFO));
}

CCircle_Stemp::CCircle_Stemp(const CCircle_Stemp& rhs)
	: CEffect(rhs)
{
}

CCircle_Stemp::~CCircle_Stemp()
{
}

HRESULT CCircle_Stemp::Ready_Object()
{
	__super::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_bActive = true;

	m_tLerpSize.Init_Lerp(LERP_MODE::EASE_IN);
	m_tLerpSize.Set_Lerp(0.2f, 2.f, 4.f);

	m_tLerpAlpha.Init_Lerp(LERP_MODE::EASE_OUT);
	m_tLerpAlpha.Set_Lerp(0.3f, 200.f, 0.f);

	return S_OK;
}

_int CCircle_Stemp::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_WDUI, this);

	m_tLerpSize.Update_Lerp(fTimeDelta);
	m_tLerpAlpha.Update_Lerp(fTimeDelta);

	m_pTransformCom->Set_Scale(_vec3{ m_tLerpSize.fCurValue, m_tLerpSize.fCurValue * 0.4f, m_tLerpSize.fCurValue * 0.4f});

	m_pTransformCom->Set_Pos(_vec3{ m_vPos.x, 0.8f, m_vPos.z + 0.02f});

	return iExit;
}

void CCircle_Stemp::LateUpdate_Object()
{
	__super::LateUpdate_Object();
	
	if (!m_tLerpAlpha.bActive)
		CEventMgr::GetInstance()->Delete_Obj(this);
}

void CCircle_Stemp::Render_Object()
{
	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(_int(m_tLerpAlpha.fCurValue), 255, 255, 255));

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

	m_pTextureCom->Render_Texture();

	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));


}

HRESULT CCircle_Stemp::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTransformCom = dynamic_cast<CTransform*>(CProtoMgr::GetInstance()->Clone_Proto(COMPONENT_TYPE::TRANSFORM, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].emplace(COMPONENT_TYPE::TRANSFORM, pComponent);

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Big_Circle_Stemp", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

}


CCircle_Stemp* CCircle_Stemp::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& _pPos)
{
	CCircle_Stemp* pInstance = new CCircle_Stemp(pGraphicDev, _pPos);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Hedgehog_Stemp Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CCircle_Stemp::Free()
{
	__super::Free();
}
