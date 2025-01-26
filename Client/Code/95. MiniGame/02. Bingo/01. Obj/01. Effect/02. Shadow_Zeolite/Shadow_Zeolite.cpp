#include "stdafx.h"
#include "Shadow_Zeolite.h"

#include "Export_Function.h"

#include "Zeolite.h"

CShadow_Zeolite::CShadow_Zeolite(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
	: CEffect(pGraphicDev, _pOwnerObject, OBJ_ID::EFFECT_ZEOLITE_SHADOW), m_pTextureCom(nullptr)
{
	m_pOwnerobject = _pOwnerObject;
}

CShadow_Zeolite::CShadow_Zeolite(const CShadow_Zeolite& rhs)
	: CEffect(rhs)
	, m_pTextureCom(rhs.m_pTextureCom)
{
}

CShadow_Zeolite::~CShadow_Zeolite()
{
}

HRESULT CShadow_Zeolite::Ready_Object()
{
	__super::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_bActive = true;

	m_fPosZ = m_pOwnerobject->Get_Transform()->Get_Info(INFO_POS).y * 0.75f;

	m_fAlpha = 220.f;
	m_tAlphaLerp.Init_Lerp(LERP_MODE::EASE_IN);
	m_tAlphaLerp.Set_Lerp(5.f, 220.f, 0.f);
	return S_OK;
}

_int CShadow_Zeolite::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);
	if (!m_pOwnerobject->Is_Active())
	{
		CEventMgr::GetInstance()->Delete_Obj(this);
		return iExit;
	}
	if (dynamic_cast<CZeolite*>(m_pOwnerobject)->Get_IsDelete())
	{
		m_tAlphaLerp.Update_Lerp(fTimeDelta);
		m_fAlpha = m_tAlphaLerp.fCurValue;
	}

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CShadow_Zeolite::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CShadow_Zeolite::Render_Object()
{
	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB((_int)m_fAlpha, 255, 255, 255));
	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

	// 빌보드 해제
	_matrix matWorld = m_pOwnerobject->Get_Transform()->Get_WorldMat();
	_matrix matBill;
	_vec3 vPos;

	memcpy(&vPos, &matWorld.m[3], sizeof(_vec3));
	vPos.y = 0.02f;
	vPos.z = 98.f;

	matWorld *= *D3DXMatrixInverse(&matBill, NULL, &CCameraMgr::GetInstance()->Get_Billboard_X());
	memcpy(&matWorld.m[3], &vPos, sizeof(_vec3));

	matWorld._11 = matWorld._11 * 1.3f; // 그림자 x사이즈
	matWorld._33 = matWorld._33 * 0.7f + m_pOwnerobject->Get_Transform()->Get_Info(INFO_POS).y * 0.1f; // 그림자 z사이즈

	m_pTextureCom->Render_Texture();

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);

	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetTexture(0, NULL);

	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB((_int)m_fAlpha, 255, 255, 255));
}

HRESULT CShadow_Zeolite::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Shadow_Creature", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

void CShadow_Zeolite::Play_Effect(const _vec3& _vPos, const _vec3& _vSize)
{
	m_vOffSet = _vPos;
	m_vSize = _vSize;
	m_bActive = true;
}

CShadow_Zeolite* CShadow_Zeolite::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
{
	CShadow_Zeolite* pInstance = new CShadow_Zeolite(pGraphicDev, _pOwnerObject);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Shadow_Zeolite Effect Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CShadow_Zeolite::Free()
{
	__super::Free();
}
