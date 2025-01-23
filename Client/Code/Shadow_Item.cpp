#include "stdafx.h"
#include "Shadow_Item.h"

#include "Export_Function.h"

#include "Monster.h"

CShadow_Item::CShadow_Item(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
	: CEffect(pGraphicDev, _pOwnerObject, OBJ_ID::EFFECT_ITEM_SHADOW), m_pTextureCom(nullptr)
{
	m_pOwnerobject = _pOwnerObject;
}

CShadow_Item::CShadow_Item(const CShadow_Item& rhs)
	: CEffect(rhs)
	, m_pTextureCom(rhs.m_pTextureCom)
{
}

CShadow_Item::~CShadow_Item()
{
}

HRESULT CShadow_Item::Ready_Object()
{
	__super::Ready_Object();

	// CGameObject::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_bActive = true;
	m_InitY = m_pOwnerobject->Get_Transform()->Get_Info(INFO_POS).y;

	return S_OK;
}

_int CShadow_Item::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	if (!m_pOwnerobject->Is_Active())
	{
		CEventMgr::GetInstance()->Delete_Obj(this);
		return iExit;
	}

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	m_fSize = fabs(m_InitY - m_pOwnerobject->Get_Transform()->Get_Info(INFO_POS).y);

	return iExit;
}

void CShadow_Item::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CShadow_Item::Render_Object()
{
	if (!m_pOwnerobject->Is_Active())
	{
		CEventMgr::GetInstance()->Delete_Obj(this);
		return;
	}

	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(220, 255, 255, 255));
	// 장판 텍스처 출력
	// 빌보드 해제
	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

	_matrix matWorld = m_pOwnerobject->Get_Transform()->Get_WorldMat();
	_matrix matBill;
	_vec3 vPos;

	memcpy(&vPos, &matWorld.m[3], sizeof(_vec3));
	vPos.y -= matWorld._22 + 0.02f;
	vPos.z -= matWorld._22 * 0.75f;

	matWorld *= *D3DXMatrixInverse(&matBill, NULL, &CCameraMgr::GetInstance()->Get_Billboard_X());
	memcpy(&matWorld.m[3], &vPos, sizeof(_vec3));

	matWorld._11 = 0.5f - m_fSize * 0.5f;
	matWorld._33 = 0.5f - m_fSize * 0.5f;

	m_pTextureCom->Render_Texture(); // 텍스처 세팅 -> 버퍼 세팅 순서 꼭!

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);

	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetTexture(0, NULL);

	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));
	// CEffect::Render_Object();
}

HRESULT CShadow_Item::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Shadow_Creature", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

void CShadow_Item::Play_Effect(const _vec3& _vPos, const _vec3& _vSize)
{
	m_vOffSet = _vPos;
	m_vSize = _vSize;
	m_bActive = true;
}

CShadow_Item* CShadow_Item::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
{
	CShadow_Item* pInstance = new CShadow_Item(pGraphicDev, _pOwnerObject);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Shadow_Item Effect Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CShadow_Item::Free()
{
	__super::Free();
}
