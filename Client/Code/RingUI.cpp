#include "RingUI.h"
#include "Export_Function.h"

#include "Player.h"

CRingUI::CRingUI(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* pOwner)
     :CUI(pGraphicDev, OBJ_ID::UI_RING), m_pOwner(pOwner)
{
}

CRingUI::CRingUI(const CRingUI& rhs)
	: CUI(rhs)
{
}

CRingUI::~CRingUI()
{
}

HRESULT CRingUI::Ready_Object()
{
	CGameObject::Ready_Object();


	m_eUIType = UI_TYPE::WORLD;
	//m_eUILayer = UI_LAYER::LV1;

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 4.f, 4.f, 4.f });

	m_iTranslucent = 225;
	m_bIsReach = true;
	m_fAcc = 0;

	m_bStart = false;
	m_bWork = false;

	return S_OK;
}

_int CRingUI::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);


	if (!m_bStart && static_cast<CPlayer*>(m_pOwner)->Get_StateM()->Get_CurState() == STATE_TYPE::FRONT_IDLE)
	{
		m_tAlpha.Init_Lerp(LERP_MODE::SMOOTHSTEP);
		m_tAlpha.Set_Lerp(1.4f, 0.f, m_iTranslucent);

		m_bStart = true;
	}

	if (m_tAlpha.bActive)
	{
		m_tAlpha.Update_Lerp(fTimeDelta);
		m_iAlpha = m_tAlpha.fCurValue;
	}
	if (m_bStart && !m_tAlpha.bActive)
	{
		m_bWork = true;
	}



	if (m_bWork)
	{
		m_fAcc += fTimeDelta;

		if (0.01f < m_fAcc)
		{
			if (m_bIsReach)
			{
				m_iTranslucent--;
				if (100 >= m_iTranslucent)
					m_bIsReach = false;
			}
			else if (!m_bIsReach)
			{
				m_iTranslucent++;
				if (225 <= m_iTranslucent)
					m_bIsReach = true;
			}

			m_fAcc = m_fAcc - 0.01f;
		}
	}
	

	return iExit;
}

void CRingUI::LateUpdate_Object()
{
	Follow_Player();

	__super::LateUpdate_Object();

}

void CRingUI::Render_Object()
{
	if (CCameraMgr::GetInstance()->Get_CurCamera()->Is_BackView())
		return;


	if (m_bWork)
	{
		m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));
		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

		if (static_cast<CPlayer*>(m_pOwner)->Get_PlayerClass() == CLASS_TYPE::THORN)
		{
			m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(m_iTranslucent, 255, 215, 0));
		}
		else
			m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(m_iTranslucent, 255, 255, 255));

		m_pTextureCom->Render_Texture();
		m_pBufferCom->Render_Buffer();

		m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	else
	{
		if (m_bStart)
		{
			m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());
			m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(m_iAlpha, 255, 255, 255));

			m_pTextureCom->Render_Texture();
			m_pBufferCom->Render_Buffer();

			m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}
	

	__super::Render_Object();
}

HRESULT CRingUI::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_UI_Ring", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);


	return S_OK;
}

void CRingUI::Follow_Player()
{
	NULL_CHECK(m_pOwner);

	_vec3		vPlayerPosition;
	vPlayerPosition = m_pOwner->Get_Transform()->Get_Info(INFO_POS);

	m_pTransformCom->Set_Pos({ vPlayerPosition.x, vPlayerPosition.y, vPlayerPosition.z + 0.2f });
}

CRingUI* CRingUI::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* pOwner)
{
	CRingUI* pInstance = new CRingUI(pGraphicDev, pOwner);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("RingUI Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CRingUI::Free()
{
	__super::Free();

}
