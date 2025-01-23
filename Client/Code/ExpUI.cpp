#include "ExpUI.h"
#include "Export_Function.h"

#include "Player.h"

CExpUI::CExpUI(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUI(pGraphicDev, OBJ_ID::UI_EXP), m_pPlayer(nullptr), m_bIsExpChange(false), m_fCurExpRatio(0.f), m_fAcc(0.f)
{
}

CExpUI::CExpUI(const CExpUI& rhs)
	: CUI(rhs)
{
	m_pPlayer = rhs.m_pPlayer;
}

CExpUI::~CExpUI()
{
}

HRESULT CExpUI::Ready_Object()
{
	m_eUIType = UI_TYPE::VIEW;

	for (_uint i = 0; i < 3; ++i)
	{
		D3DXMatrixIdentity(&m_matExpUI[i]);
	}
	

	m_fPosX = 184;
	m_fPosY = 70;

	m_fSizeX = 78;
	m_fSizeY = 30 * 0.6f;

	m_matExpUI[0]._41 = m_fPosX;
	m_matExpUI[0]._42 = WINCY - m_fPosY;

	m_matExpUI[0]._11 = m_fSizeX;
	m_matExpUI[0]._22 = m_fSizeY;

	m_matExpUI[1]._41 = m_fPosX;
	m_matExpUI[1]._42 = WINCY - m_fPosY;

	m_matExpUI[1]._11 = m_fSizeX;
	m_matExpUI[1]._22 = m_fSizeY;

	m_matExpUI[2]._41 = m_fPosX + 76.f;
	m_matExpUI[2]._42 = WINCY - m_fPosY - 1;

	m_matExpUI[2]._11 = 48.f;
	m_matExpUI[2]._22 = 47.f * 0.6f;

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_fAlpha = 0.f;
	m_fBarSizeX = 0.f;

	m_bGone = false;

	m_fCurExpRatio = 0.f;

	return S_OK;
}

_int CExpUI::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	if (m_bIsExpChange)
	{
		m_fAcc += fTimeDelta;

		if (2.f < m_fAcc && !m_bGone)
		{
			m_fAcc = 0.f;
			m_tAlpha.Init_Lerp(LERP_MODE::EASE_IN);
			m_tAlpha.Set_Lerp(0.5f, 255, 0);
			m_bGone = true;
		}
	}

	if (m_bGone)
	{
		if (m_fAlpha <= 1.f)
		{
			m_fAlpha = 0;
			m_bIsExpChange = false;
			m_bGone = false;
		}
	}

	if (nullptr == m_pPlayer)
		m_pPlayer = dynamic_cast<CPlayer*>(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::PLAYER, L"Player"));

	if (nullptr != m_pPlayer)
	{
		_float fExpRatio = m_pPlayer->Get_StatInfo().fCurExp / m_pPlayer->Get_StatInfo().fMaxExp;

		if (1.f <= fExpRatio)
			fExpRatio = 1.f;

		if (fExpRatio != m_fCurExpRatio)
		{
			if (0.f >= m_fAlpha)
			{
				m_tAlpha.Init_Lerp(LERP_MODE::EASE_IN);
				m_tAlpha.Set_Lerp(0.2f, 0.f, 255.f);
			}
			m_tSize.Init_Lerp();
			m_tSize.Set_Lerp(0.5f, m_fCurExpRatio, fExpRatio);

			m_fCurExpRatio = fExpRatio;
			m_bIsExpChange = true;
			m_bGone = false;
			m_fAcc = 0.f;
		}
	}
	
	m_tSize.Update_Lerp(fTimeDelta);
	m_tAlpha.Update_Lerp(fTimeDelta);

	return iExit;
}

void CExpUI::LateUpdate_Object()
{
	if (m_tSize.bActive)
	{
		float fMoveX = (1.f - m_tSize.fCurValue) * m_fSizeX;

		m_matExpUI[1]._11 = m_tSize.fCurValue * m_fSizeX;
		m_matExpUI[1]._41 = m_fPosX - fMoveX;
	}
	if (m_fCurExpRatio <= 0 && !m_tSize.bActive)
	{
		float fMoveX = (1.f - m_fCurExpRatio) * m_fSizeX;

		m_matExpUI[1]._11 = m_fCurExpRatio * m_fSizeX;
		m_matExpUI[1]._41 = m_fPosX - fMoveX;
	}
	
	m_fAlpha = m_tAlpha.fCurValue;

	__super::LateUpdate_Object();
}

void CExpUI::Render_Object()
{
	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));
	
	if (m_bIsExpChange)
	{
		m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB((_uint)m_fAlpha, 255, 255, 255));

		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matExpUI[0]);
		m_pTextureCom->Render_Texture(7);
		m_pBufferCom->Render_Buffer();

		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matExpUI[1]);
		m_pTextureCom->Render_Texture(8);
		m_pBufferCom->Render_Buffer();

		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matExpUI[2]);
		m_pTextureCom->Render_Texture(13);
		m_pBufferCom->Render_Buffer();

		m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

HRESULT CExpUI::Add_Component()
{

	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_UI_Bar", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);
	
	return S_OK;
}

CExpUI* CExpUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CExpUI* pInstance = new CExpUI(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("ExpUI Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CExpUI::Free()
{
	__super::Free();

}
