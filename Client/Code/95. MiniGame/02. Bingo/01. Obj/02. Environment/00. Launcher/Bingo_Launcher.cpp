#include "stdafx.h"
#include "Bingo_Launcher.h"

#include "Export_Function.h"

#include "EnterUI.h"

#include "MiniGameMgr_Bingo.h"

#include "SoundMgr.h"

CBingo_Launcher::CBingo_Launcher(LPDIRECT3DDEVICE9 pGraphicDev)
	: CEnvironment(pGraphicDev, OBJ_ID::BINGO_LAUNCHER)
	, m_bShowUI(true)
{
}

CBingo_Launcher::CBingo_Launcher(const CBingo_Launcher& rhs)
	: CEnvironment(rhs)
{
}

CBingo_Launcher::~CBingo_Launcher()
{
}

HRESULT CBingo_Launcher::Ready_Object()
{
	CEnvironment::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_eEnter = ENTER_TYPE::ENTER_NO;
	m_eInterType = INTERACTION_TYPE::INTERACTION_INSPECT;

	m_pTransformCom->Set_Scale(_vec3{ 0.7f, 1.3f, 1.5f });
	m_pTransformCom->Set_Pos(_vec3{ 92.5f , m_pTransformCom->Get_Scale().y, 15.f });

	m_szName = L"Bingo_Launcher";

	return S_OK;
}

_int CBingo_Launcher::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CBingo_Launcher::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CBingo_Launcher::Render_Object()
{
	m_pTextureCom->Render_Texture(); // 텍스처 세팅 -> 버퍼 세팅 순서 꼭!

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetTexture(0, NULL);

	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

	__super::Render_Object();
}

void CBingo_Launcher::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CBingo_Launcher::OnCollision_Stay(CGameObject* _pColObj)
{
	if (_pColObj->Get_Type() == OBJ_TYPE::PLAYER)
	{
		// 최초 상호작용 시 게임 세팅
		if (!CMiniGameMgr_Bingo::GetInstance()->Get_Active())
		{
			// UI 보여주기
			CEnterUI* m_pEnterUI = static_cast<CEnterUI*>
				(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"UI_Enter"));
			m_pEnterUI->EnterUI_On(UIENTER_TYPE::INSPECT, _pColObj);

			if (CInputDev::GetInstance()->Key_Down('E'))
			{
				CEnterUI* m_pEnterUI = static_cast<CEnterUI*>
					(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"UI_Enter"));
				m_pEnterUI->EnterUI_Off();

				CMiniGameMgr_Bingo::GetInstance()->Set_Active(true);
			}
		}
		else
		{
			// 아직 정답 국기들을 보여주지 않았을 때만
			if (!CMiniGameMgr_Bingo::GetInstance()->Get_FlagShow())
			{
				if (m_bShowUI)
				{
					CEnterUI* m_pEnterUI = static_cast<CEnterUI*>
						(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"UI_Enter"));

					m_pEnterUI->EnterUI_On(UIENTER_TYPE::INSPECT, _pColObj);
				}

				if (CInputDev::GetInstance()->Key_Down('E')) 
				{
					CSoundMgr::GetInstance()->PlaySound(L"catnap.wav", CHANNEL_ID::ENVIRONMENT_0, BINGO_SHOW_SOUND);
					CMiniGameMgr_Bingo::GetInstance()->Set_FlagShow(true);

					CEnterUI* m_pEnterUI = static_cast<CEnterUI*>
						(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"UI_Enter"));
					m_pEnterUI->EnterUI_Off();

					m_bShowUI = false;
				}
			}
		}
	}
}

void CBingo_Launcher::OnCollision_Exit(CGameObject* _pColObj)
{
	// 아직 정답 국기들을 보여주지 않았을 때만
	if (!CMiniGameMgr_Bingo::GetInstance()->Get_FlagShow())
	{
		CEnterUI* m_pEnterUI = static_cast<CEnterUI*>
			(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"UI_Enter"));

		m_pEnterUI->EnterUI_Off();
	}
}

HRESULT CBingo_Launcher::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Otehr_TownSanctuary", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CBingo_Launcher* CBingo_Launcher::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBingo_Launcher* pInstance = new CBingo_Launcher(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Bingo_Launcher Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CBingo_Launcher::Free()
{
	__super::Free();
}
