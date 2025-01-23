#include "IndicatorUI.h"
#include "Export_Function.h"

#include "Player.h"
#include "QuestMgr.h"
#include "ZoomUI.h"

CIndicatorUI::CIndicatorUI(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUI(pGraphicDev, OBJ_ID::UI_INDICATOR), m_pTarget(nullptr), m_pPlayer(nullptr), m_bShrink(true)
{
}

CIndicatorUI::CIndicatorUI(const CIndicatorUI& rhs)
	: CUI(rhs)
{
	m_pTarget = rhs.m_pTarget;
}

CIndicatorUI::~CIndicatorUI()
{
	Free();
}

HRESULT CIndicatorUI::Ready_Object()
{
	CGameObject::Ready_Object();

	m_eUIType = UI_TYPE::VIEW;

	D3DXMatrixIdentity(&m_UImatWorld);

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_vIndicDir = _vec3{ 0.f, 1.f, 0.f };

	m_fSizeX = 51.f;
	m_fSizeY = 42.f;

	m_bOut = false;

	return S_OK;
}

_int CIndicatorUI::Update_Object(const _float& fTimeDelta)
{
	if (m_pTarget)
	{
		_int iExit = __super::Update_Object(fTimeDelta);

		if (nullptr == m_pPlayer)
			m_pPlayer = dynamic_cast<CPlayer*>(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::PLAYER, L"Player"));

		Get_ViewPos_Target();


		_float fScale = 0.7f;
		if (m_bShrink)
		{
			_vec3 vOut = m_pTransformCom->Lerp(_vec3{ m_UImatWorld._11, m_UImatWorld._22, 0.f }
			, _vec3{ m_UImatWorld._11 * fScale, m_UImatWorld._22 * fScale, 0.f }, 0.8f, fTimeDelta, LERP_MODE::SMOOTHERSTEP);
			if (vOut.x != -99)
			{
				m_UImatWorld._11 = vOut.x;
				m_UImatWorld._22 = vOut.y;
			}
			else
			{
				m_bShrink = false;
			}

		}
		if (!m_bShrink)
		{
			_vec3 vOut = m_pTransformCom->Lerp(_vec3{ m_UImatWorld._11 * fScale, m_UImatWorld._22 * fScale, 0.f }
			, _vec3{ m_UImatWorld._11, m_UImatWorld._22, 0.f }, 0.6f, fTimeDelta, LERP_MODE::SMOOTHERSTEP);
			if (vOut.x != -99)
			{
				m_UImatWorld._11 = vOut.x;
				m_UImatWorld._22 = vOut.y;
			}
			else
			{
				m_bShrink = true;
			}
		}
		return iExit;
	}
	return 0;
}

void CIndicatorUI::LateUpdate_Object()
{
	if (m_pTarget)
	{
		CGameObject* pUIZoom = CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"UI_Zoom");
		NULL_CHECK(pUIZoom);

		if (static_cast<CZoomUI*>(pUIZoom)->Get_ZoomState() == 1)
			m_bOut = true;
		else
			m_bOut = false;

		__super::LateUpdate_Object();
	}
}

void CIndicatorUI::Render_Object()
{
	if (m_pTarget)
	{
		if (CQuestMgr::GetInstance()->Get_IsAble() && m_fTargetLength > 10.f)
		{
			m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));
			m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_UImatWorld);

			m_pTextureCom->Render_Texture();
			m_pBufferCom->Render_Buffer();

			__super::Render_Object();
		}
	}
}

void CIndicatorUI::Get_ViewPos_Target()
{
	if (CQuestMgr::GetInstance()->Get_IsAble())
	{
		D3DXMatrixIdentity(&m_UImatWorld);
		_vec3 vTargetWorldPos = m_pTarget->Get_Transform()->Get_Info(INFO::INFO_POS);
		_vec3 vPlayerWorldPos = m_pPlayer->Get_Transform()->Get_Info(INFO::INFO_POS);

		_vec3 vTargetDir = vTargetWorldPos - vPlayerWorldPos;
		m_fTargetLength = D3DXVec3Length(&vTargetDir);
		D3DXVec3Normalize(&vTargetDir, &vTargetDir);

		
		if (m_bOut)
		{
			_matrix matView = CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Get_MatView();
			_matrix matProj = CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Get_MatProj();
			D3DVIEWPORT9 pViewport = CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Get_ViewPort();

			D3DXVec3TransformCoord(&vTargetWorldPos, &vTargetWorldPos, &matView);
			D3DXVec3TransformCoord(&vTargetWorldPos, &vTargetWorldPos, &matProj);

			_float ScreenX = vTargetWorldPos.x * (pViewport.Width / 2) + pViewport.X + (pViewport.Width / 2);
			_float ScreenY = WINCY - (-vTargetWorldPos.y * (pViewport.Height / 2) + pViewport.Y + (pViewport.Height / 2));

			m_UImatWorld._11 = m_fSizeX;
			m_UImatWorld._22 = m_fSizeY;

			m_UImatWorld._41 = ScreenX;
			m_UImatWorld._42 = ScreenY + 50;
			
			if (ScreenX < 0 || ScreenX > WINCX ||
				ScreenY < 0 || ScreenY > WINCY)
			{
				_vec3 vIndicPos = vPlayerWorldPos + (vTargetDir * 80);

				_matrix matView = CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Get_MatView();
				_matrix matProj = CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Get_MatProj();
				D3DVIEWPORT9 pViewport = CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Get_ViewPort();

				D3DXVec3TransformCoord(&vIndicPos, &vIndicPos, &matView);
				D3DXVec3TransformCoord(&vIndicPos, &vIndicPos, &matProj);

				_float ScreenX = vIndicPos.x * (pViewport.Width / 2) + pViewport.X + (pViewport.Width / 2);
				_float ScreenY = WINCY - (-vIndicPos.y * (pViewport.Height / 2) + pViewport.Y + (pViewport.Height / 2));

				if (ScreenX >= WINCX - 200)
					ScreenX = WINCX - 200;
				else if (ScreenX <= 200)
					ScreenX = 200;
				if (ScreenY >= WINCY - 100)
					ScreenY = WINCY - 100;
				else if (ScreenY <= 100)
					ScreenY = 100;

				if (vTargetDir.z < 0)
				{
					m_UImatWorld._11 = m_fSizeX;
					m_UImatWorld._22 = m_fSizeY;

				}
				else
				{
					m_UImatWorld._11 = m_fSizeX;
					m_UImatWorld._22 = -m_fSizeY;

				}


				m_UImatWorld._41 = ScreenX;
				m_UImatWorld._42 = ScreenY;
			}

		}
		else if (25.f >= m_fTargetLength)
		{
			_matrix matView = CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Get_MatView();
			_matrix matProj = CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Get_MatProj();
			D3DVIEWPORT9 pViewport = CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Get_ViewPort();

			D3DXVec3TransformCoord(&vTargetWorldPos, &vTargetWorldPos, &matView);
			D3DXVec3TransformCoord(&vTargetWorldPos, &vTargetWorldPos, &matProj);

			_float ScreenX = vTargetWorldPos.x * (pViewport.Width / 2) + pViewport.X + (pViewport.Width / 2);
			_float ScreenY = WINCY - (-vTargetWorldPos.y * (pViewport.Height / 2) + pViewport.Y + (pViewport.Height / 2));

			m_UImatWorld._11 = m_fSizeX;
			m_UImatWorld._22 = m_fSizeY;

			m_UImatWorld._41 = ScreenX;
			m_UImatWorld._42 = ScreenY + 80;

		}
		else
		{
			_vec3 vIndicPos = vPlayerWorldPos + (vTargetDir * 26.5f);

			_matrix matView = CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Get_MatView();
			_matrix matProj = CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Get_MatProj();
			D3DVIEWPORT9 pViewport = CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Get_ViewPort();

			D3DXVec3TransformCoord(&vIndicPos, &vIndicPos, &matView);
			D3DXVec3TransformCoord(&vIndicPos, &vIndicPos, &matProj);

			_float ScreenX = vIndicPos.x * (pViewport.Width / 2) + pViewport.X + (pViewport.Width / 2);
			_float ScreenY = WINCY - (-vIndicPos.y * (pViewport.Height / 2) + pViewport.Y + (pViewport.Height / 2));

			if (ScreenX > WINCX - 200)
				ScreenX = WINCX - 200;
			else if (ScreenX < 200)
				ScreenX = 200;
			if (ScreenY > WINCY - 100)
				ScreenY = WINCY - 100;
			else if (ScreenY < 100)
				ScreenY = 100;

			if (vTargetDir.z < 0)
			{
				m_UImatWorld._11 = m_fSizeX;
				m_UImatWorld._22 = m_fSizeY;

				
			}
			else
			{
				m_UImatWorld._11 = m_fSizeX;
				m_UImatWorld._22 = -m_fSizeY;

			}


			m_UImatWorld._41 = ScreenX;
			m_UImatWorld._42 = ScreenY;
		}
	}
}

HRESULT CIndicatorUI::Add_Component()
{

	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_UI_Indicator", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);


	return S_OK;
}

CIndicatorUI* CIndicatorUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CIndicatorUI* pInstance = new CIndicatorUI(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("IndicatorUI Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CIndicatorUI::Free()
{
	__super::Free();

}
