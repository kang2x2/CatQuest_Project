#include "DefUI.h"
#include "Export_Function.h"

#include "Player.h"

CDefUI::CDefUI(LPDIRECT3DDEVICE9 pGraphicDev)
     :CUI(pGraphicDev, OBJ_ID::UI_DEF), m_pPlayer(nullptr), m_fDefRatio(1.f)
{
}

CDefUI::CDefUI(const CDefUI& rhs)
	: CUI(rhs)
{
}

CDefUI::~CDefUI()
{
}

HRESULT CDefUI::Ready_Object()
{
	CGameObject::Ready_Object();

	m_eUIType = UI_TYPE::WORLD;
	m_eUILayer = UI_LAYER::LV1;

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pUITransformCom[0]->Set_Scale(_vec3{ 2.f, 0.6f, 1.f });
	m_pUITransformCom[1]->Set_Scale(_vec3{ 0.9f, 0.9f, 1.f });
	m_pUITransformCom[2]->Set_Scale(_vec3{ 0.9f, 0.9f, 1.f });

	m_bStart = false;
	m_bWork = false;
	m_iAlpha = 0;

	return S_OK;
}

_int CDefUI::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	if (nullptr == m_pPlayer)
		m_pPlayer = dynamic_cast<CPlayer*>(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::PLAYER, L"Player"));

	if (nullptr != m_pPlayer)
	{
		m_fDefRatio = m_pPlayer->Get_StatInfo().fCurDef / m_pPlayer->Get_StatInfo().fMaxDef;

		if (!m_bStart && static_cast<CPlayer*>(m_pPlayer)->Get_StateM()->Get_CurState() == STATE_TYPE::FRONT_IDLE)
		{
			m_tAlpha.Init_Lerp(LERP_MODE::SMOOTHSTEP);
			m_tAlpha.Set_Lerp(1.5f, 0.f, 255.f);

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
	}
		
	if (1.f < m_fDefRatio)
		m_fDefRatio = 1.f;

	return iExit;
}

void CDefUI::LateUpdate_Object()
{
	Follow_Player();

	_vec3 vInitPosition = m_pUITransformCom[0]->Get_Info(INFO::INFO_POS);

	float fMoveX = (1.0f - m_fDefRatio) * 2.0f;
	_vec3 vNewPosition = _vec3(vInitPosition.x - fMoveX, vInitPosition.y, vInitPosition.z);

	m_pUITransformCom[0]->Set_Scale(_vec3{ 2.0f * m_fDefRatio, 0.6f, 1.0f });
	m_pUITransformCom[0]->Set_Pos(vNewPosition);

	__super::LateUpdate_Object();

}

void CDefUI::Render_Object()
{
	if (CCameraMgr::GetInstance()->Get_CurCamera()->Is_BackView())
		return;

	if (m_bWork)
	{
		if (0 < m_pPlayer->Get_StatInfo().fCurDef)
		{
			m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

			m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pUITransformCom[0]->Get_WorldMat());
			m_pTextureCom->Render_Texture(5);
			m_pBufferCom->Render_Buffer();

			m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pUITransformCom[1]->Get_WorldMat());
			m_pTextureCom->Render_Texture(4);
			m_pBufferCom->Render_Buffer();

			m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pUITransformCom[2]->Get_WorldMat());
			m_pTextureCom->Render_Texture(6);
			m_pBufferCom->Render_Buffer();
		}
	}
	else
	{
		if (m_bStart)
		{
			if (0 < m_pPlayer->Get_StatInfo().fCurDef)
			{
				m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(m_iAlpha, 255, 255, 255));

				m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

				m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pUITransformCom[0]->Get_WorldMat());
				m_pTextureCom->Render_Texture(5);
				m_pBufferCom->Render_Buffer();

				m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pUITransformCom[1]->Get_WorldMat());
				m_pTextureCom->Render_Texture(4);
				m_pBufferCom->Render_Buffer();

				m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pUITransformCom[2]->Get_WorldMat());
				m_pTextureCom->Render_Texture(6);
				m_pBufferCom->Render_Buffer();

				m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));
			}
		}
		
	}
	
}

HRESULT CDefUI::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_UI_Bar", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	for (_uint i = 0; i < 3; ++i)
	{
		pComponent = m_pUITransformCom[i] = dynamic_cast<CTransform*>(Engine::Clone_Proto(COMPONENT_TYPE::TRANSFORM, this));
		NULL_CHECK_RETURN(pComponent, E_FAIL);
		m_mapComponent[ID_DYNAMIC].emplace(COMPONENT_TYPE::TRANSFORM, pComponent);
	}

	return S_OK;
}

void CDefUI::Follow_Player()
{
	CTransform* pPlayerTransform = dynamic_cast<CTransform*>(Engine::Get_Component(OBJ_TYPE::PLAYER, L"Player", COMPONENT_TYPE::TRANSFORM, COMPONENTID::ID_DYNAMIC));
	NULL_CHECK(pPlayerTransform);

	_vec3		vPlayerPosition;
	vPlayerPosition = pPlayerTransform->Get_Info(INFO_POS);

	m_pUITransformCom[0]->Set_Pos({ vPlayerPosition.x , vPlayerPosition.y, vPlayerPosition.z - 4.2f });
	m_pUITransformCom[1]->Set_Pos({ vPlayerPosition.x - 2.6f, vPlayerPosition.y, vPlayerPosition.z - 4.2f });
	m_pUITransformCom[2]->Set_Pos({ vPlayerPosition.x + 1.95f, vPlayerPosition.y, vPlayerPosition.z - 4.2f });
}

CDefUI* CDefUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CDefUI* pInstance = new CDefUI(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("DefUI Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CDefUI::Free()
{
	__super::Free();

}
