#include "stdafx.h"
#include "Effect_Ora.h"

#include "Export_Function.h"
#include "Player.h"

CEffect_Ora::CEffect_Ora(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
	: CEffect(pGraphicDev, _pOwnerObject, OBJ_ID::EFFECT_PLAYABLE_SHADOW), m_pTextureCom(nullptr)
{
	m_pOwnerobject = _pOwnerObject;
}

CEffect_Ora::CEffect_Ora(const CEffect_Ora& rhs)
	: CEffect(rhs)
	, m_pTextureCom(rhs.m_pTextureCom)
{
}

CEffect_Ora::~CEffect_Ora()
{
}

HRESULT CEffect_Ora::Ready_Object()
{
	__super::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 4.f, 5.f, 4.f });
	m_pTransformCom->Set_Pos(m_pOwnerobject->Get_Transform()->Get_Info(INFO::INFO_POS));

	m_bActive = false;

	return S_OK;
}

_int CEffect_Ora::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);
	Engine::Add_RenderGroup(RENDER_ALPHA, this);


	m_pTransformCom->Set_Pos(m_pOwnerobject->Get_Transform()->Get_Info(INFO::INFO_POS));

	return iExit;
}

void CEffect_Ora::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CEffect_Ora::Render_Object()
{
	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(220, 255, 255, 255));
	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

	m_pTextureCom->Render_Texture();
	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));
}

HRESULT CEffect_Ora::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Ora", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	return S_OK;
}

void CEffect_Ora::Play_Effect(const _vec3& _vPos, const _vec3& _vSize)
{
	m_vOffSet = _vPos;
	m_vSize = _vSize;
	m_bActive = true;
}

CEffect_Ora* CEffect_Ora::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
{
	CEffect_Ora* pInstance = new CEffect_Ora(pGraphicDev, _pOwnerObject);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Ora Effect Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CEffect_Ora::Free()
{
	__super::Free();
}
