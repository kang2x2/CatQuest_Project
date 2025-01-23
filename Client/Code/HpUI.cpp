#include "HpUI.h"
#include "Export_Function.h"

#include "Player.h"

CHpUI::CHpUI(LPDIRECT3DDEVICE9 pGraphicDev)
     :CUI(pGraphicDev, OBJ_ID::UI_HP), m_pPlayer(nullptr), m_fHpRatio(1.f), m_fCurRatio(1.f)
{
}

CHpUI::CHpUI(const CHpUI& rhs)
	: CUI(rhs)
{
}

CHpUI::~CHpUI()
{
}

HRESULT CHpUI::Ready_Object()
{
	CGameObject::Ready_Object();

	m_eUIType = UI_TYPE::WORLD;
	m_eUILayer = UI_LAYER::LV1;

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pUITransformCom[0]->Set_Scale(_vec3{ 2.f, 0.6f, 1.f });
	m_pUITransformCom[1]->Set_Scale(_vec3{ 2.f, 0.6f, 1.f });
	m_pUITransformCom[2]->Set_Scale(_vec3{ 0.9f, 0.9f, 1.f });
	m_pUITransformCom[3]->Set_Scale(_vec3{ 0.9f, 0.9f, 1.f });
	m_pUITransformCom[4]->Set_Scale(_vec3{ 2.f, 0.6f, 1.f });

	m_bStart = false;
	m_bWork = false;
	m_iAlpha = 0;

	return S_OK;
}

_int CHpUI::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);
	
	if (nullptr == m_pPlayer)
		m_pPlayer = dynamic_cast<CPlayer*>(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::PLAYER, L"Player"));

	if (nullptr != m_pPlayer)
	{
		m_fCurRatio = m_pPlayer->Get_StatInfo().fCurHP / m_pPlayer->Get_StatInfo().fMaxHP;

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
		

	if (1.f < m_fCurRatio)
	{
		m_fCurRatio = 1.f;
		m_fHpRatio = m_fCurRatio;
	}

	

	return iExit;
}

void CHpUI::LateUpdate_Object()
{
	Follow_Player();

	_vec3 vInitPosition = m_pUITransformCom[1]->Get_Info(INFO::INFO_POS);

	float fMoveX = (1.0f - m_fCurRatio) * 2.0f;
	_vec3 vNewPosition = _vec3(vInitPosition.x - fMoveX, vInitPosition.y, vInitPosition.z);

	m_pUITransformCom[1]->Set_Scale(_vec3{ 2.0f * m_fCurRatio, 0.6f, 1.0f });
	m_pUITransformCom[1]->Set_Pos(vNewPosition);

	if (m_fCurRatio >= 1.f)
	{
		m_pUITransformCom[4]->Set_Scale(_vec3{ 2.f, 0.6f, 1.f });
		m_pUITransformCom[4]->Reset_Lerp();
	}
	else if (m_fCurRatio >= m_fHpRatio && m_fCurRatio < 1.f)
	{
		m_pUITransformCom[4]->Set_Scale(_vec3{ 1.6f * m_fCurRatio, 0.4f, 1.0f });
		m_pUITransformCom[4]->Set_Pos(vNewPosition);
		m_pUITransformCom[4]->Reset_Lerp();
		m_fHpRatio = m_fCurRatio;

	}
	else if (m_fCurRatio != m_fHpRatio && m_fCurRatio < 1.f)
	{
		_vec3 vOutScale = m_pUITransformCom[4]->Lerp(m_pUITransformCom[4]->Get_Scale()
			, m_pUITransformCom[1]->Get_Scale(), 1.2f, Engine::Get_TimeDelta(L"Timer_FPS65"));

		if (vOutScale.z != -99)
		{
			_vec3 vGoldInitPosition = m_pUITransformCom[4]->Get_Info(INFO::INFO_POS);

			float fGoldMoveX = (1.0f - (vOutScale.x / 2.f)) * 2.0f;
			_vec3 vGoldNewPosition = _vec3(vGoldInitPosition.x - fGoldMoveX, vGoldInitPosition.y, vGoldInitPosition.z);

			m_pUITransformCom[4]->Set_Scale(vOutScale);
			m_pUITransformCom[4]->Set_Pos(vGoldNewPosition);
		}
		else
			m_fHpRatio = m_fCurRatio;
	}

	if (m_fCurRatio == m_fHpRatio)
	{
		m_pUITransformCom[4]->Set_Scale(_vec3{ 2.0f * m_fCurRatio, 0.6f, 1.0f });
		m_pUITransformCom[4]->Set_Pos(vNewPosition);
		m_pUITransformCom[4]->Reset_Lerp();
	}
	
	__super::LateUpdate_Object();

}

void CHpUI::Render_Object()
{
	if (CCameraMgr::GetInstance()->Get_CurCamera()->Is_BackView())
		return;

	if (m_bWork)
	{
		m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pUITransformCom[0]->Get_WorldMat());
		m_pTextureCom->Render_Texture(7);
		m_pBufferCom->Render_Buffer();

		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pUITransformCom[4]->Get_WorldMat());
		m_pTextureCom->Render_Texture(10);
		m_pBufferCom->Render_Buffer();

		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pUITransformCom[1]->Get_WorldMat());
		m_pTextureCom->Render_Texture(1);
		m_pBufferCom->Render_Buffer();

		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pUITransformCom[2]->Get_WorldMat());
		m_pTextureCom->Render_Texture(0);
		m_pBufferCom->Render_Buffer();

		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pUITransformCom[3]->Get_WorldMat());
		m_pTextureCom->Render_Texture(6);
		m_pBufferCom->Render_Buffer();
	}
	else
	{
		if (m_bStart)
		{
			m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(m_iAlpha, 255, 255, 255));

			m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

			m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pUITransformCom[0]->Get_WorldMat());
			m_pTextureCom->Render_Texture(7);
			m_pBufferCom->Render_Buffer();

			m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pUITransformCom[4]->Get_WorldMat());
			m_pTextureCom->Render_Texture(10);
			m_pBufferCom->Render_Buffer();

			m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pUITransformCom[1]->Get_WorldMat());
			m_pTextureCom->Render_Texture(1);
			m_pBufferCom->Render_Buffer();

			m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pUITransformCom[2]->Get_WorldMat());
			m_pTextureCom->Render_Texture(0);
			m_pBufferCom->Render_Buffer();

			m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pUITransformCom[3]->Get_WorldMat());
			m_pTextureCom->Render_Texture(6);
			m_pBufferCom->Render_Buffer();

			m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	
	}
	

}

HRESULT CHpUI::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_UI_Bar", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	for (_uint i = 0; i < 5; ++i)
	{
		pComponent = m_pUITransformCom[i] = dynamic_cast<CTransform*>(Engine::Clone_Proto(COMPONENT_TYPE::TRANSFORM, this));
		NULL_CHECK_RETURN(pComponent, E_FAIL);
		m_mapComponent[ID_DYNAMIC].emplace(COMPONENT_TYPE::TRANSFORM, pComponent);
	}

	return S_OK;
}

void CHpUI::Follow_Player()
{
	CTransform* pPlayerTransform = dynamic_cast<CTransform*>(Engine::Get_Component(OBJ_TYPE::PLAYER, L"Player", COMPONENT_TYPE::TRANSFORM, COMPONENTID::ID_DYNAMIC));
	NULL_CHECK(pPlayerTransform);

	_vec3		vPlayerPosition;
	vPlayerPosition = pPlayerTransform->Get_Info(INFO_POS);

	m_pUITransformCom[0]->Set_Pos({ vPlayerPosition.x , vPlayerPosition.y, vPlayerPosition.z - 4.2f });
	m_pUITransformCom[1]->Set_Pos({ vPlayerPosition.x, vPlayerPosition.y, vPlayerPosition.z - 4.2f });
	m_pUITransformCom[2]->Set_Pos({ vPlayerPosition.x - 2.6f, vPlayerPosition.y, vPlayerPosition.z - 4.2f });
	m_pUITransformCom[3]->Set_Pos({ vPlayerPosition.x + 1.95f, vPlayerPosition.y, vPlayerPosition.z - 4.2f });
	m_pUITransformCom[4]->Set_Pos({ vPlayerPosition.x, vPlayerPosition.y, vPlayerPosition.z - 4.2f });
}

CHpUI* CHpUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CHpUI* pInstance = new CHpUI(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("HpUI Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CHpUI::Free()
{
	__super::Free();

}
