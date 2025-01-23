#include "stdafx.h"
#include "Shadow_Npc.h"

#include "Export_Function.h"

CShadow_Npc::CShadow_Npc(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
	: CEffect(pGraphicDev, _pOwnerObject, OBJ_ID::EFFECT_NPC_SHADOW), m_pTextureCom(nullptr)
{
	m_pOwnerobject = _pOwnerObject;
}

CShadow_Npc::CShadow_Npc(const CShadow_Npc& rhs)
	: CEffect(rhs)
	, m_pTextureCom(rhs.m_pTextureCom)
{
}

CShadow_Npc::~CShadow_Npc()
{
}

HRESULT CShadow_Npc::Ready_Object()
{
	__super::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_bActive = true;

	return S_OK;
}

_int CShadow_Npc::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);
	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CShadow_Npc::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CShadow_Npc::Render_Object()
{
	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(220, 255, 255, 255));
	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

	// 빌보드 해제
	_matrix matWorld = m_pOwnerobject->Get_Transform()->Get_WorldMat();
	_matrix matBill;
	_vec3 vPos;
	
	memcpy(&vPos, &matWorld.m[3], sizeof(_vec3));
	vPos.y -= matWorld._22 + 0.02f;
	vPos.z -= matWorld._22 * 0.75f;

	matWorld *= *D3DXMatrixInverse(&matBill, NULL, &CCameraMgr::GetInstance()->Get_Billboard_X());
	memcpy(&matWorld.m[3], &vPos, sizeof(_vec3));
	
	matWorld._11 = matWorld._11 * 0.6f; // 그림자 x사이즈
	matWorld._33 = matWorld._33 * 0.4f; // 그림자 z사이즈

	m_pTextureCom->Render_Texture(); 

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);

	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetTexture(0, NULL);

	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));
}

HRESULT CShadow_Npc::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Shadow_Creature", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

void CShadow_Npc::Play_Effect(const _vec3& _vPos, const _vec3& _vSize)
{
	m_vOffSet = _vPos;
	m_vSize = _vSize;
	m_bActive = true;
}

CShadow_Npc* CShadow_Npc::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
{
	CShadow_Npc* pInstance = new CShadow_Npc(pGraphicDev, _pOwnerObject);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Shadow_Npc Effect Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CShadow_Npc::Free()
{
	__super::Free();
}
