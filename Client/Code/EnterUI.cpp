#include "EnterUI.h"
#include "Export_Function.h"
#include "Player.h"

CEnterUI::CEnterUI(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUI(pGraphicDev, OBJ_ID::UI_ENTER), m_bIsOn(false), m_bIsShirk(false), m_bIsExpand(false), m_bIsStart(false), m_bIsEnd(false)
	, m_eUIEnter(UIENTER_TYPE::TYPEEND)
{
}

CEnterUI::CEnterUI(const CEnterUI& rhs)
	: CUI(rhs)
{
}

CEnterUI::~CEnterUI()
{
}

HRESULT CEnterUI::Ready_Object()
{
	CGameObject::Ready_Object();

	m_eUIType = UI_TYPE::WORLD;

	D3DXMatrixIdentity(&m_UImatWorld);

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_fSizeX = 0.f;
	m_fSizeY = 0.5f;

	m_pTransformCom->Set_Scale(_vec3{ m_fSizeX, m_fSizeY, 0.f });

	return S_OK;
}

_int CEnterUI::Update_Object(const _float& fTimeDelta)
{
	if (m_bIsOn)
	{
		_int iExit = __super::Update_Object(fTimeDelta);

		if (m_bIsStart)
		{
			m_fSizeX += 10.f * fTimeDelta;
			m_fSizeY += 10.f * fTimeDelta;

			if (2.5f <= m_fSizeX)
			{
				m_bIsShirk = true;
				m_bIsStart = false;
			}

		}

		if (m_bIsEnd)
		{
			m_fSizeX -= 10.f * fTimeDelta;
			m_fSizeY -= 10.f * fTimeDelta;

			if (0 >= m_fSizeX)
			{
				m_fSizeX = 0.f;
				m_fSizeY = 0.5f;

				m_bIsOn = false;
				m_bIsEnd = false;

			}
		}

		if (m_bIsExpand)
		{
			m_fSizeX += 1.f * fTimeDelta;
			m_fSizeY += 1.f * fTimeDelta;

			if (2.5f < m_fSizeX)
			{
				m_bIsExpand = false;
				m_bIsShirk = true;
			}
		}

		if (m_bIsShirk)
		{
			m_fSizeX -= 1.5f * fTimeDelta;
			m_fSizeY -= 1.5f * fTimeDelta;

			if (2.f > m_fSizeX)
			{
				m_bIsExpand = true;
				m_bIsShirk = false;
			}
		}



		return iExit;
	}
	return 0;
}

void CEnterUI::LateUpdate_Object()
{
	if (m_bIsOn)
	{
		m_pTransformCom->Set_Scale(_vec3{ m_fSizeX, m_fSizeY, 0.f });

		__super::LateUpdate_Object();
	}

}

void CEnterUI::Render_Object()
{
	NULL_CHECK(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::PLAYER, L"Player"));
	//if(static_cast<CPlayer*>(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::PLAYER, L"Player"))->Is_PlayerTalking())
	//	return;

	if (m_bIsOn)
	{
		m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));
		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

		m_pTextureCom->Render_Texture(_uint(m_eUIEnter));
		m_pBufferCom->Render_Buffer();

		__super::Render_Object();
	}

}

void CEnterUI::EnterUI_On(UIENTER_TYPE eUIEnter, CGameObject* pObj)
{
	if (true == m_bIsOn)
		return;

	m_bIsOn = true;
	m_bIsStart = true;
	m_eUIEnter = eUIEnter;

	_vec3 vObjWorldPos = pObj->Get_Transform()->Get_Info(INFO::INFO_POS);

	vObjWorldPos.y += 5.75f;

	m_pTransformCom->Set_Pos(vObjWorldPos);

}

void CEnterUI::EnterUI_Off()
{
	m_bIsStart = false;
	m_bIsExpand = false;
	m_bIsShirk = false;
	m_bIsEnd = true;
}

HRESULT CEnterUI::Add_Component()
{

	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_UI_Enter", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);


	return S_OK;
}

CEnterUI* CEnterUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CEnterUI* pInstance = new CEnterUI(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("EnterUI Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CEnterUI::Free()
{
	__super::Free();

}
