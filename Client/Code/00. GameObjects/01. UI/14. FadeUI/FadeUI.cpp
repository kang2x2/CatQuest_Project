#include "FadeUI.h"
#include "Export_Function.h"

#include "Player.h"

#include "Player_Camera.h"

CFadeUI::CFadeUI(LPDIRECT3DDEVICE9 pGraphicDev)
	: CUI(pGraphicDev, OBJ_ID::UI_BACKGROUND)
	, m_eFadeColor(FADE_COLOR::WHITE)
	, m_bDelete(TRUE)
{
	ZeroMemory(&m_tLerpAlpha, sizeof(LERP_FLOAT_INFO));
}

CFadeUI::CFadeUI(const CFadeUI& rhs)
	: CUI(rhs)
{
}

CFadeUI::~CFadeUI()
{
}

HRESULT CFadeUI::Ready_Object()
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_eUIType = UI_TYPE::VIEW;

	m_eUILayer = UI_LAYER::LV1;

	m_szName = L"FadeUI";
	
	m_bMaintain = TRUE;

	D3DXMatrixIdentity(&m_matWorld);

	m_matWorld._41 = (WINCX >> 1);
	m_matWorld._42 = (WINCY >> 1);
	m_matWorld._11 = WINCX;
	m_matWorld._22 = WINCY;

	return S_OK;
}
static int k = 0;
_int CFadeUI::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);
	cout << ++k << "\n업데이트\t" << m_tLerpAlpha.fCurValue << endl;
	m_tLerpAlpha.Update_Lerp(fTimeDelta);

	return iExit;
}

void CFadeUI::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CFadeUI::Render_Object()
{
	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(_int(m_tLerpAlpha.fCurValue), 255, 255, 255));

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matWorld);

	if (FADE_COLOR::WHITE == m_eFadeColor)
	{
		m_pUITextureCom[(UINT)FADE_COLOR::WHITE]->Render_Texture();
	}
	else
	{
		m_pUITextureCom[(UINT)FADE_COLOR::BLACK]->Render_Texture();
	}

	m_pBufferCom->Render_Buffer();

	if (!m_tLerpAlpha.bActive && !m_bDelete)
	{
		CPlayer_Camera* pCam = dynamic_cast<CPlayer_Camera*>(CCameraMgr::GetInstance()->Get_CurCamera());
		
		NULL_CHECK(pCam);

		if (FADE_MODE::BLACK_FADE_OUT == pCam->Get_FadeMode() || FADE_MODE::WHITE_FADE_OUT == pCam->Get_FadeMode())
			return; // 페이드 아웃일 때에는 굳이 페이드를 끌 필요 없음 (어차피 다시 켜줘야하니까)

		Set_Active(FALSE);
	}

	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));
	cout << "페이드\t" << m_tLerpAlpha.fCurValue << endl;
}

void CFadeUI::Start_Fade(const _float _fTime, const _float& _fStartvalue, const _float _fEndValue, const _bool& _bWhite, const LERP_MODE& _eMode, const _bool _bDelete)
{
	Set_Active(TRUE);

	if (!_bDelete)
		m_bDelete = TRUE;

	m_tLerpAlpha.Init_Lerp(_eMode);
	m_tLerpAlpha.Set_Lerp(_fTime, _fStartvalue, _fEndValue);

	if (_bWhite)
		m_eFadeColor = FADE_COLOR::WHITE;
	else
		m_eFadeColor = FADE_COLOR::BLACK;
}

HRESULT CFadeUI::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pUITextureCom[(UINT)FADE_COLOR::WHITE] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Background_White", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pUITextureCom[(UINT)FADE_COLOR::BLACK] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Background_Black", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	return S_OK;
}

CFadeUI* CFadeUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CFadeUI* pInstance = new CFadeUI(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Fade UI Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CFadeUI::Free()
{
	__super::Free();
}
