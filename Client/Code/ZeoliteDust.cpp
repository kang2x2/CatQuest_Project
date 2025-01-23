#include "stdafx.h"

#include "Export_Function.h"

#include "ZeoliteDust.h"
#include "Player.h"
#include "SoundMgr.h"

CZeoliteDust::CZeoliteDust(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
	: CEffect(pGraphicDev, _pOwnerObject, OBJ_ID::EFFECT_ZEOLITE_DUST)
{
	m_pOwnerobject = _pOwnerObject;
}

CZeoliteDust::CZeoliteDust(const CZeoliteDust& rhs)
	: CEffect(rhs), m_pTextureCom(rhs.m_pTextureCom)
{
}

CZeoliteDust::~CZeoliteDust()
{
}

HRESULT CZeoliteDust::Ready_Object()
{
	__super::Ready_Object();

	// CGameObject::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom, STATE_TYPE::FRONT_IDLE, 0.1f, true);

	_int iRand = rand() % 10 - 5;

	m_pTransformCom->Set_Pos(_vec3{ m_pOwnerobject->Get_Transform()->Get_Info(INFO_POS).x + iRand,
		 0.2f,
		m_pOwnerobject->Get_Transform()->Get_Info(INFO_POS).z - 4.5f});
	m_pTransformCom->Set_Scale(_vec3{ 3.6f, 3.6f, 3.6f });

	m_bActive = true;
	m_iTranslucent = 250;
	m_iDeAlpha = 10;

	CSoundMgr::GetInstance()->PlaySound(L"Stone_Door.mp3", CHANNEL_ID::EFFECT_0, 1.f);

	return S_OK;
}

_int CZeoliteDust::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);
	Engine::Add_RenderGroup(RENDER_WDUI, this);

	m_pTransformCom->Set_Pos({
		m_pTransformCom->Get_Info(INFO_POS).x,
		4.f,
		98.f
		});

	m_pAnimation->Update_Animation(fTimeDelta);

	m_iTranslucent -= m_iDeAlpha;

	if (m_pAnimation->Is_End())
	{
		CEventMgr::GetInstance()->Delete_Obj(this);
	}

	if (!m_pOwnerobject->Is_Active())
	{
		CEventMgr::GetInstance()->Delete_Obj(this);
		return iExit;
	}

	return iExit;
}

void CZeoliteDust::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CZeoliteDust::Render_Object()
{
	NULL_CHECK(m_pOwnerobject);

	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(m_iTranslucent, 255, 255, 255));

	m_pAnimation->Render_Animation();

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));
}

HRESULT CZeoliteDust::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Move_Dust", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	return S_OK;
}

void CZeoliteDust::Play_Effect(const _vec3& _vPos, const _vec3& _vSize)
{
	m_vOffSet = _vPos;
	m_vSize = _vSize;
	m_bActive = true;
}

CZeoliteDust* CZeoliteDust::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
{
	CZeoliteDust* pInstance = new CZeoliteDust(pGraphicDev, _pOwnerObject);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Zeolite_Dust Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CZeoliteDust::Free()
{
	m_pAnimation->Release();
	__super::Free();
}
