#include "stdafx.h"
#include "Shadow_Boss.h"

#include "Export_Function.h"

#include "Monster.h"

CShadow_Boss::CShadow_Boss(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
	: CEffect(pGraphicDev, _pOwnerObject, OBJ_ID::EFFECT_BOSS_SHADOW), m_pTextureCom(nullptr)
	, m_bUp(false), m_bDown(false)
{
	m_pOwnerobject = _pOwnerObject;
}

CShadow_Boss::CShadow_Boss(const CShadow_Boss& rhs)
	: CEffect(rhs)
	, m_pTextureCom(rhs.m_pTextureCom)
{
}

CShadow_Boss::~CShadow_Boss()
{
}

HRESULT CShadow_Boss::Ready_Object()
{
	__super::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_bActive = true;

	m_tIntorLerpX.Init_Lerp(LERP_MODE::EASE_IN);
	m_tIntorLerpX.Set_Lerp(0.75f, 0.25f, 0.6f);
	m_tIntorLerpZ.Init_Lerp(LERP_MODE::EASE_IN);
	m_tIntorLerpZ.Set_Lerp(0.75f, 0.45f, 0.8f);

	m_tFullUpLerpX.Init_Lerp(LERP_MODE::EASE_IN);
	m_tFullUpLerpX.Set_Lerp(0.25f, 0.6f, 0.08f);
	m_tFullUpLerpZ.Init_Lerp(LERP_MODE::EASE_IN);
	m_tFullUpLerpZ.Set_Lerp(0.25f, 0.8f, 0.1f);

	m_tFullDownLerpX.Init_Lerp(LERP_MODE::EASE_IN);
	m_tFullDownLerpX.Set_Lerp(0.25f, 0.08f, 0.6f);
	m_tFullDownLerpZ.Init_Lerp(LERP_MODE::EASE_IN);
	m_tFullDownLerpZ.Set_Lerp(0.25f, 0.1f, 0.8f);


	m_szName = L"Shadow_Boss";

	return S_OK;
}

_int CShadow_Boss::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);
	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	if (!m_pOwnerobject->Is_Active())
	{
		CEventMgr::GetInstance()->Delete_Obj(this);
		return iExit;
	}

	if (dynamic_cast<CMonster*>(m_pOwnerobject)->Get_StateM()->Get_CurState() == STATE_TYPE::BOSS_INTRO_DOWN)
	{
		m_tIntorLerpX.Update_Lerp(fTimeDelta);
		m_tIntorLerpZ.Update_Lerp(fTimeDelta);
	}

	if (dynamic_cast<CMonster*>(m_pOwnerobject)->Get_StateM()->Get_CurState() == STATE_TYPE::BOSS_FULLDOWN_FLY)
	{
		if (!m_bUp && dynamic_cast<CMonster*>(m_pOwnerobject)->Get_StateM()->Get_Animator()->Get_CurAniamtion()->Get_CurFrame() > 10)
		{
			m_bDown = false;
			m_tFullUpLerpX.Init_Lerp(LERP_MODE::EASE_IN);
			m_tFullUpLerpX.Set_Lerp(0.5f, 0.6f, 0.08f);
			m_tFullUpLerpZ.Init_Lerp(LERP_MODE::EASE_IN);
			m_tFullUpLerpZ.Set_Lerp(0.5f, 0.8f, 0.1f);
			m_bUp = true;
		}
	}
	else if (dynamic_cast<CMonster*>(m_pOwnerobject)->Get_StateM()->Get_CurState() == STATE_TYPE::BOSS_FULLDOWN_DOWN)
	{
		if (!m_bDown)
		{
			m_bUp = false;
			m_tFullDownLerpX.Init_Lerp(LERP_MODE::EASE_IN);
			m_tFullDownLerpX.Set_Lerp(0.25f, 0.08f, 0.6f);
			m_tFullDownLerpZ.Init_Lerp(LERP_MODE::EASE_IN);
			m_tFullDownLerpZ.Set_Lerp(0.25f, 0.1f, 0.8f);
			m_bDown = true;
		}
	}

	if (m_bUp)
	{
		m_tFullUpLerpX.Update_Lerp(fTimeDelta);
		m_tFullUpLerpZ.Update_Lerp(fTimeDelta);
	}
	else if (m_bDown)
	{
		m_tFullDownLerpX.Update_Lerp(fTimeDelta);
		m_tFullDownLerpZ.Update_Lerp(fTimeDelta);
	}

	return iExit;
}

void CShadow_Boss::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CShadow_Boss::Render_Object()
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

	// 인트로
	if (m_tIntorLerpZ.bActive && m_tIntorLerpX.bActive)
	{
		matWorld._11 = matWorld._11 * m_tIntorLerpX.fCurValue; // 그림자 x사이즈
		matWorld._33 = matWorld._33 * m_tIntorLerpZ.fCurValue; // 그림자 z사이즈
	}
	// 공중으로
	else if (m_bUp)
	{
		matWorld._11 = matWorld._11 * m_tFullUpLerpX.fCurValue; // 그림자 x사이즈
		matWorld._33 = matWorld._33 * m_tFullUpLerpZ.fCurValue; // 그림자 z사이즈
	}
	// 찍기
	else if (m_bDown)
	{
		matWorld._11 = matWorld._11 * m_tFullDownLerpX.fCurValue; // 그림자 x사이즈
		matWorld._33 = matWorld._33 * m_tFullDownLerpZ.fCurValue; // 그림자 z사이즈
	}
	else
	{
		matWorld._11 = matWorld._11 * 0.6f; // 그림자 x사이즈
		matWorld._33 = matWorld._33 * 0.8f; // 그림자 z사이즈
	}

	m_pTextureCom->Render_Texture();

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);

	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetTexture(0, NULL);

	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));
}

HRESULT CShadow_Boss::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Shadow_Creature", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

void CShadow_Boss::Play_Effect(const _vec3& _vPos, const _vec3& _vSize)
{
	m_vOffSet = _vPos;
	m_vSize = _vSize;
	m_bActive = true;
}

CShadow_Boss* CShadow_Boss::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
{
	CShadow_Boss* pInstance = new CShadow_Boss(pGraphicDev, _pOwnerObject);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Shadow_Boss Effect Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CShadow_Boss::Free()
{
	__super::Free();
}
