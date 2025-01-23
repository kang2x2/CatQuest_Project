#include "stdafx.h"
#include "Shadow_Player.h"

#include "Export_Function.h"
#include "Player.h"

CShadow_Player::CShadow_Player(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
	: CEffect(pGraphicDev, _pOwnerObject, OBJ_ID::EFFECT_PLAYABLE_SHADOW), m_pTextureCom(nullptr)
{
	m_pOwnerobject = _pOwnerObject;
}

CShadow_Player::CShadow_Player(const CShadow_Player& rhs)
	: CEffect(rhs)
	, m_pTextureCom(rhs.m_pTextureCom)
{
}

CShadow_Player::~CShadow_Player()
{
}

HRESULT CShadow_Player::Ready_Object()
{
	__super::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_bActive = true;

	return S_OK;
}

_int CShadow_Player::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);
	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CShadow_Player::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CShadow_Player::Render_Object()
{
	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(220, 255, 255, 255));
	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

	// ºôº¸µå ÇØÁ¦
	_matrix matWorld = m_pOwnerobject->Get_Transform()->Get_WorldMat();
	_matrix matBill;
	_vec3 vPos;

	memcpy(&vPos, &matWorld.m[3], sizeof(_vec3));
	vPos.y -= matWorld._22 + 0.02f;

	if (static_cast<CPlayer*>(m_pOwnerobject)->Get_StateM()->Get_CurState() == STATE_TYPE::FRONT_FLIGHT ||
		static_cast<CPlayer*>(m_pOwnerobject)->Is_Fly() ||
		m_pOwnerobject->Get_RigidBody()->Is_Jump() || m_pOwnerobject->Get_RigidBody()->Is_KnockUp())
	{
		vPos.y = 0.02f;
		vPos.z += 0.8f;
	}
	else if (CCameraMgr::GetInstance()->Get_CurCamera()->Is_BackView())
	{
		vPos.y -= 0.02f;
		vPos.z += 1.35f;
	}
		

	matWorld *= *D3DXMatrixInverse(&matBill, NULL, &CCameraMgr::GetInstance()->Get_Billboard_X());
	memcpy(&matWorld.m[3], &vPos, sizeof(_vec3));

	if (static_cast<CPlayer*>(m_pOwnerobject)->Get_StateM()->Get_CurState() == STATE_TYPE::FRONT_FLIGHT ||
		static_cast<CPlayer*>(m_pOwnerobject)->Is_Fly() ||
		m_pOwnerobject->Get_RigidBody()->Is_Jump())
	{
		matWorld._11 = matWorld._11 * 0.35f;
		matWorld._33 = matWorld._33 * 0.25f;
		m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(200, 255, 255, 255));
	}
	else
	{
		matWorld._11 = matWorld._11 * 0.4f;
		matWorld._33 = matWorld._33 * 0.3f;
	}
	

	m_pTextureCom->Render_Texture(); 

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);

	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetTexture(0, NULL);

	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));
}

HRESULT CShadow_Player::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Shadow_Creature", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

void CShadow_Player::Play_Effect(const _vec3& _vPos, const _vec3& _vSize)
{
	m_vOffSet = _vPos;
	m_vSize = _vSize;
	m_bActive = true;
}

CShadow_Player* CShadow_Player::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
{
	CShadow_Player* pInstance = new CShadow_Player(pGraphicDev, _pOwnerObject);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Shadow_Player Effect Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CShadow_Player::Free()
{
	__super::Free();
}
