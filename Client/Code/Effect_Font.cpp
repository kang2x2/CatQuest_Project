#include "stdafx.h"
#include "Effect_Font.h"

#include "Export_Function.h"

CEffect_Font::CEffect_Font(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* pOwner, _uint iNumb, FONT_TYPE eFont)
	: CEffect(pGraphicDev, pOwner, OBJ_ID::EFFECT_FONT), m_iNumb(iNumb), m_eFontType(eFont)
{
	
}

CEffect_Font::CEffect_Font(const CEffect_Font& rhs)
	: CEffect(rhs)
{
}

CEffect_Font::~CEffect_Font()
{
}

HRESULT CEffect_Font::Ready_Object()
{
	__super::Ready_Object();

	m_bActive = true;

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	switch (m_eFontType)
	{
	case Engine::FONT_TYPE::DAMAGE:
		m_strFont = to_wstring(m_iNumb);
		m_vColor = { 251, 199, 54 };
		break;
	case Engine::FONT_TYPE::HIT:
		m_strFont = L"-" + to_wstring(m_iNumb);
		m_vColor = { 253, 3, 0 };
		break;
	case Engine::FONT_TYPE::GOLD:
		m_strFont = L"+" + to_wstring(m_iNumb);
		m_vColor = { 251, 246, 27 };
		break;
	case Engine::FONT_TYPE::EXP:
		m_strFont = L"+" + to_wstring(m_iNumb);
		m_vColor = { 58, 254, 253 };
		break;
	case Engine::FONT_TYPE::HEAL:
		m_strFont = to_wstring(m_iNumb);
		m_vColor = { 255, 112, 212 };
		break;
	default:
		break;
	}

	m_vFontPos = { m_pOwnerobject->Get_Transform()->Get_Info(INFO::INFO_POS).x,
		m_pOwnerobject->Get_Transform()->Get_Info(INFO::INFO_POS).y, m_pOwnerobject->Get_Transform()->Get_Info(INFO::INFO_POS).z };

	_matrix matView = CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Get_MatView();
	_matrix matProj = CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Get_MatProj();
	D3DVIEWPORT9 pViewport = CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Get_ViewPort();

	D3DXVec3TransformCoord(&m_vFontPos, &m_vFontPos, &matView);
	D3DXVec3TransformCoord(&m_vFontPos, &m_vFontPos, &matProj);

	_float ScreenX = m_vFontPos.x * (pViewport.Width / 2) + pViewport.X + (pViewport.Width / 2);
	_float ScreenY;
	if(m_eFontType != FONT_TYPE::HIT)
		ScreenY =(-m_vFontPos.y * (pViewport.Height / 2) + pViewport.Y + (pViewport.Height / 2)) - 50;
	else
		ScreenY =(-m_vFontPos.y * (pViewport.Height / 2) + pViewport.Y + (pViewport.Height / 2)) + 50;

	m_vFontPos = { ScreenX, ScreenY, 0.f };

	m_fRectRad = 100.f;

	m_rcFont.left = m_vFontPos.x - m_fRectRad;
	m_rcFont.top = m_vFontPos.y - m_fRectRad;
	m_rcFont.right = m_vFontPos.x + m_fRectRad;
	m_rcFont.bottom = m_vFontPos.y + m_fRectRad;

	m_rcFont2.left = m_vFontPos.x - m_fRectRad + 1.2;
	m_rcFont2.top = m_vFontPos.y - m_fRectRad + 1;
	m_rcFont2.right = m_vFontPos.x + m_fRectRad + 1.2;
	m_rcFont2.bottom = m_vFontPos.y + m_fRectRad + 1;

	m_fAlpha = 255.f;

	m_tAlpha.Init_Lerp(LERP_MODE::EXPONENTIAL);
	m_tPosY.Init_Lerp(LERP_MODE::EASE_OUT);

	m_tAlpha.Set_Lerp(1.f, m_fAlpha, 0.f);
	if (m_eFontType != FONT_TYPE::HIT)
		m_tPosY.Set_Lerp(0.8f, m_vFontPos.y, m_vFontPos.y - 120);
	else
		m_tPosY.Set_Lerp(0.8f, m_vFontPos.y, m_vFontPos.y + 120);

	return S_OK;
}

_int CEffect_Font::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);
	Engine::Add_RenderGroup(RENDER_VIEWUI, this);

	if (m_fAlpha <= 0)
		CEventMgr::GetInstance()->Delete_Obj(this);

	m_tAlpha.Update_Lerp(fTimeDelta);
	m_tPosY.Update_Lerp(fTimeDelta);

	return iExit;
}

void CEffect_Font::LateUpdate_Object()
{
	m_fAlpha = m_tAlpha.fCurValue;
	m_vFontPos.y = m_tPosY.fCurValue;

	Caculate();

	__super::LateUpdate_Object();
}

void CEffect_Font::Render_Object()
{
	CGraphicDev::GetInstance()->Get_EffectFont1()->DrawTextW(NULL, m_strFont.c_str(), -1,
		&m_rcFont, DT_CENTER | DT_VCENTER, D3DCOLOR_ARGB((_uint)m_fAlpha, 72, 43, 11));

	CGraphicDev::GetInstance()->Get_EffectFont2()->DrawTextW(NULL, m_strFont.c_str(), -1,
		&m_rcFont2, DT_CENTER | DT_VCENTER, D3DCOLOR_ARGB((_uint)m_fAlpha, (_uint)m_vColor.x, (_uint)m_vColor.y, (_uint)m_vColor.z));

	if (m_eFontType == FONT_TYPE::EXP)
	{
		CGraphicDev::GetInstance()->Get_XpFont1()->DrawTextW(NULL, L"xp", -1,
			&m_rcFontxp, DT_CENTER | DT_VCENTER, D3DCOLOR_ARGB((_uint)m_fAlpha, 72, 43, 11));

		CGraphicDev::GetInstance()->Get_XpFont2()->DrawTextW(NULL, L"xp", -1,
			&m_rcFontxp, DT_CENTER | DT_VCENTER, D3DCOLOR_ARGB((_uint)m_fAlpha, (_uint)m_vColor.x, (_uint)m_vColor.y, (_uint)m_vColor.z));
	}


	__super::Render_Object();
}

HRESULT CEffect_Font::Add_Component()
{
	CComponent* pComponent = nullptr;

	/*pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);*/

	return S_OK;
}

void CEffect_Font::Play_Effect(const _vec3& _vPos, const _vec3& _vSize)
{
}

void CEffect_Font::Caculate()
{
	m_rcFont.left = m_vFontPos.x - m_fRectRad;
	m_rcFont.top = m_vFontPos.y - m_fRectRad;
	m_rcFont.right = m_vFontPos.x + m_fRectRad;
	m_rcFont.bottom = m_vFontPos.y + m_fRectRad;
	 
	m_rcFont2.left = m_vFontPos.x - m_fRectRad + 1.2;
	m_rcFont2.top = m_vFontPos.y - m_fRectRad + 1;
	m_rcFont2.right = m_vFontPos.x + m_fRectRad + 1.2;
	m_rcFont2.bottom = m_vFontPos.y + m_fRectRad + 1 ;

	if (m_eFontType == FONT_TYPE::EXP)
	{
		m_rcFontxp.left = m_vFontPos.x - m_fRectRad + 90;
		m_rcFontxp.top = m_vFontPos.y - m_fRectRad + 8;
		m_rcFontxp.right = m_vFontPos.x + m_fRectRad + 90;
		m_rcFontxp.bottom = m_vFontPos.y + m_fRectRad + 8;
	}
}

CEffect_Font* CEffect_Font::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* pOwner, _uint iNumb, FONT_TYPE eFont)
{
	CEffect_Font* pInstance = new CEffect_Font(pGraphicDev, pOwner, iNumb, eFont);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Effect_Font Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CEffect_Font::Free()
{
	__super::Free();
}
