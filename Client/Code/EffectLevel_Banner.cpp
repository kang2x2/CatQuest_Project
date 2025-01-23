#include "stdafx.h"
#include "EffectLevel_Banner.h"
#include "Export_Function.h"
#include "Player.h"

CEffectLevel_Banner::CEffectLevel_Banner(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
	: CEffect(pGraphicDev, _pOwnerObject, OBJ_ID::EFFECT_LEVELUP_BANNER)
{
	m_pOwnerobject = _pOwnerObject;
}

CEffectLevel_Banner::CEffectLevel_Banner(const CEffectLevel_Banner& rhs)
	: CEffect(rhs)
{
}

CEffectLevel_Banner::~CEffectLevel_Banner()
{
}

HRESULT CEffectLevel_Banner::Ready_Object()
{
	__super::Ready_Object();

	m_eUILayer = UI_LAYER::LV1;

	NULL_CHECK_RETURN(m_pOwnerobject, E_FAIL);

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	
	m_fBannerSizeX = 120.f;
	m_fBannerSizeY = 55.f;

	m_fEmbleSizeX = 48.f;
	m_fEmbleSizeY = 64.f;


	m_fAcc = 0.f;

	m_bReadyEnd = false;
	m_bActive = false;

	for (_uint i = 0; i < 2; ++i)
	{
		D3DXMatrixIdentity(&m_matEffect[i]);
	}

	return S_OK;
}

_int CEffectLevel_Banner::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);
	Engine::Add_RenderGroup(RENDER_VIEWUI, this);

	if (m_t_fSize_Banner.fCurValue >= 5 && !m_t_fSize_Banner.bActive)
	{
		m_fAcc += fTimeDelta;

		if (m_fAcc > 3.f)
		{
			m_t_fSize_Banner.Init_Lerp(LERP_MODE::EXPONENTIAL);
			m_t_vSize_Emble.Init_Lerp(LERP_MODE::EXPONENTIAL);

			m_t_fSize_Banner.Set_Lerp(0.1f, m_fBannerSizeX, 0.f);
			m_t_vSize_Emble.Set_Lerp(0.1f, _vec3{ m_fEmbleSizeX, m_fEmbleSizeY, 0.f }, vec3.zero);

			m_t_fPosition_Emble.Init_Lerp(LERP_MODE::SMOOTHSTEP);
			m_t_fPosition_Emble.Set_Lerp(0.1f, 20, 70);
			m_t_fPosition_Emble.fCurValue = m_t_fPosition_Emble.fStartValue;
			m_bReadyEnd = true;
		}
	}
	if (m_t_fPosition_Emble.fCurValue <= 0 && !m_t_vSize_Emble.bActive)
	{
		m_t_fPosition_Emble.Init_Lerp(LERP_MODE::EXPONENTIAL);
		m_t_fPosition_Emble.Set_Lerp(0.1f, 0, 20);
	}

	m_t_fSize_Banner.Update_Lerp(fTimeDelta);
	m_t_vSize_Emble.Update_Lerp(fTimeDelta);
	m_t_fPosition_Emble.Update_Lerp(fTimeDelta);

	return iExit;
}

void CEffectLevel_Banner::LateUpdate_Object()
{
	if (m_t_fSize_Banner.bActive)
	{
		m_matEffect[0]._11 = m_t_fSize_Banner.fCurValue;
	}
	if (m_t_vSize_Emble.bActive)
	{
		_vec3 vEmble_Size = _vec3{ m_matEffect[1]._11, m_matEffect[1]._22, 0.f };
		vEmble_Size = m_t_vSize_Emble.vCurVec;
		m_matEffect[1]._11 = vEmble_Size.x;
		m_matEffect[1]._22 = vEmble_Size.y;
	}

	
	Follow_Owner();
	Follow_Emble();


	if (m_bReadyEnd && !m_t_fSize_Banner.bActive)
		m_bActive = false;

	__super::LateUpdate_Object();
}

void CEffectLevel_Banner::Render_Object()
{
	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matEffect[0]);
	m_pTex_Banner->Render_Texture();
	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matEffect[1]);
	m_pTex_Emble->Render_Texture();
	m_pBufferCom->Render_Buffer();


	if (m_bReadyEnd)
		return;

	if(!m_t_vSize_Emble.bActive)
		CGraphicDev::GetInstance()->Get_LevelUpFont()->DrawTextW(NULL, m_strLv.c_str(), -1,
			&m_rcFont, DT_CENTER |DT_VCENTER, D3DCOLOR_ARGB(200, 0, 0, 0));

}

void CEffectLevel_Banner::Play_Effect(const _vec3& _vPos, const _vec3& _vSize)
{
	NULL_CHECK(m_pOwnerobject);

	ZeroMemory(&m_t_fSize_Banner, sizeof(LERP_FLOAT_INFO));
	ZeroMemory(&m_t_fPosition_Emble, sizeof(LERP_FLOAT_INFO));
	ZeroMemory(&m_t_vSize_Emble, sizeof(LERP_VEC3_INFO));

	m_fAcc = 0.f;
	m_bReadyEnd = false;
	m_fBanner_Y = 150.f;
	m_fEmble_Y = 115.f;

	_vec3 vPlayerPos = m_pOwnerobject->Get_Transform()->Get_Info(INFO::INFO_POS);

	_matrix matView = CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Get_MatView();
	_matrix matProj = CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Get_MatProj();
	D3DVIEWPORT9 pViewport = CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Get_ViewPort();

	D3DXVec3TransformCoord(&vPlayerPos, &vPlayerPos, &matView);
	D3DXVec3TransformCoord(&vPlayerPos, &vPlayerPos, &matProj);

	_float ScreenX = vPlayerPos.x * (pViewport.Width / 2) + pViewport.X + (pViewport.Width / 2);
	_float ScreenY = WINCY - (-vPlayerPos.y * (pViewport.Height / 2) + pViewport.Y + (pViewport.Height / 2));

	vPlayerPos = { ScreenX , ScreenY, 0.f };

	m_matEffect[0]._41 = vPlayerPos.x;
	m_matEffect[0]._42 = vPlayerPos.y + m_fBanner_Y;
	m_matEffect[1]._41 = floor(vPlayerPos.x + 0.5);
	vPlayerPos.y += m_fEmble_Y;
	m_matEffect[1]._42 = floor(vPlayerPos.y + 0.5);

	m_matEffect[0]._11 = 0;
	m_matEffect[0]._22 = m_fBannerSizeY;

	m_matEffect[1]._11 = 0;
	m_matEffect[1]._22 = 0;

	m_t_fSize_Banner.Init_Lerp(LERP_MODE::EASE_OUT);
	m_t_vSize_Emble.Init_Lerp(LERP_MODE::EASE_OUT);

	m_t_fSize_Banner.Set_Lerp(0.2f, 0.f, m_fBannerSizeX);
	m_t_vSize_Emble.Set_Lerp(0.2f, vec3.zero, _vec3{ m_fEmbleSizeX, m_fEmbleSizeY, 0.f});

	m_t_fPosition_Emble.Init_Lerp(LERP_MODE::SMOOTHSTEP);
	m_t_fPosition_Emble.Set_Lerp(0.1f, 40, 0);

	m_bActive = true;
}

void CEffectLevel_Banner::Follow_Owner()
{
	NULL_CHECK(m_pOwnerobject);

	_vec3 vPlayerPos = m_pOwnerobject->Get_Transform()->Get_Info(INFO::INFO_POS);

	_matrix matView = CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Get_MatView();
	_matrix matProj = CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Get_MatProj();
	D3DVIEWPORT9 pViewport = CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Get_ViewPort();

	D3DXVec3TransformCoord(&vPlayerPos, &vPlayerPos, &matView);
	D3DXVec3TransformCoord(&vPlayerPos, &vPlayerPos, &matProj);

	_float ScreenX = vPlayerPos.x * (pViewport.Width / 2) + pViewport.X + (pViewport.Width / 2);
	_float ScreenY = WINCY - (-vPlayerPos.y * (pViewport.Height / 2) + pViewport.Y + (pViewport.Height / 2));

	vPlayerPos = { ScreenX , ScreenY, 0.f };
	_vec3 vOwnerPos_Banner;
	_vec3 vOwnerPos_Emble = vOwnerPos_Banner = vPlayerPos;


	vOwnerPos_Banner.y += m_fBanner_Y;
	vOwnerPos_Emble.y += m_fEmble_Y;
	vOwnerPos_Emble.y += m_t_fPosition_Emble.fCurValue;

	m_matEffect[0]._41 = vOwnerPos_Banner.x;
	m_matEffect[0]._42 = vOwnerPos_Banner.y;

	m_matEffect[1]._41 = floor(vOwnerPos_Emble.x + 0.5);
	m_matEffect[1]._42 = floor(vOwnerPos_Emble.y + 0.5);

}

void CEffectLevel_Banner::Follow_Emble()
{
	_float fRadi = 102.f;
	_vec3 vRectPos = _vec3{ m_matEffect[1]._41, WINCY - m_matEffect[1]._42, 0.f };
		
	m_rcFont.left = vRectPos.x - fRadi;
	m_rcFont.right = vRectPos.x + fRadi;
	m_rcFont.top = vRectPos.y - 50;
	m_rcFont.bottom = vRectPos.y + 50;


	wstring strLevel = to_wstring(static_cast<CPlayer*>(m_pOwnerobject)->Get_StatInfo().iLevel);
	m_strLv = L"Level\n" + strLevel;
}

HRESULT CEffectLevel_Banner::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTex_Banner = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Banner_Blue", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTex_Emble = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_UI_Level", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	return S_OK;
}

CEffectLevel_Banner* CEffectLevel_Banner::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
{
	CEffectLevel_Banner* pInstance = new CEffectLevel_Banner(pGraphicDev, _pOwnerObject);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Level Effect_Banner Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CEffectLevel_Banner::Free()
{
	__super::Free();
}
