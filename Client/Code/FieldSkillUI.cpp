#include "stdafx.h"
#include "FieldSkillUI.h"
#include "Export_Function.h"

#include "RingUI.h"
#include "Player.h"
#include "Skill.h"

#include "SoundMgr.h"

CFieldSkillUI::CFieldSkillUI(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUI(pGraphicDev, OBJ_ID::UI_FILEDSKILL)
	, m_bIsOn(false), m_pPlayer(nullptr)
{
	for (size_t i = 0; i < 4; ++i)
	{
		m_pPlayerSkill[i] = nullptr;
	}
}

CFieldSkillUI::CFieldSkillUI(const CFieldSkillUI& rhs)
	: CUI(rhs)
{
}

CFieldSkillUI::~CFieldSkillUI()
{
}

HRESULT CFieldSkillUI::Ready_Object()
{
	
	m_eUIType = UI_TYPE::VIEW;
	m_eUILayer = UI_LAYER::LV1;

	m_bPlaySound = false;

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_bShirnk = true;
	m_bReach = false;
	m_fReach = 25.f;
	for (_uint i = 0; i < 4; ++i)
		m_bPick[i] = false;
	for (_uint i = 0; i < 4; ++i)
		m_bSkill[i] = false;



	// 쉐이드 설정
	D3DXMatrixIdentity(&m_UImatWorld);
	m_fPosX = WINCX >> 1;
	m_fPosY = WINCY >> 1;
	m_fSizeX = WINCX;
	m_fSizeY = WINCY;
	m_UImatWorld._41 = m_fPosX;
	m_UImatWorld._42 = m_fPosY;
	m_UImatWorld._11 = m_fSizeX;
	m_UImatWorld._22 = m_fSizeY;
	
	D3DXMatrixIdentity(&m_matMouse);

	for (_uint i = 0; i < 17; ++i)
	{
		D3DXMatrixIdentity(&m_matWorldUI[i]);
	}
	// 큰링설정 200.f 192.f
	m_RingPosX[0] = WINCX * 0.5f;
	m_RingPosY[0] = WINCY * 0.5f;
	m_RingSizeX[0] = 320.f;
	m_RingSizeY[0] = 306.4f;
	m_matWorldUI[0]._41 = m_RingPosX[0];
	m_matWorldUI[0]._42 = m_RingPosY[0];
	m_matWorldUI[0]._11 = m_RingSizeX[0];
	m_matWorldUI[0]._22 = m_RingSizeY[0];

	// 화살1 설정
	m_ArrowPosX[0] = WINCX * 0.43f;
	m_ArrowPosY[0] = WINCY * 0.5f;
	m_ArrowSizeX = 25.6;
	m_ArrowSizeY = 14;
	m_matWorldUI[13]._11 = m_ArrowSizeX;
	m_matWorldUI[13]._22 = m_ArrowSizeY;
	_matrix matRot;
	D3DXMatrixRotationZ(&matRot, D3DXToRadian(90));
	m_matWorldUI[13] *= matRot;
	m_matWorldUI[13]._41 = m_ArrowPosX[0];
	m_matWorldUI[13]._42 = m_ArrowPosY[0];
	// 화살2 설정
	m_ArrowPosX[1] = WINCX * 0.57f;
	m_ArrowPosY[1] = WINCY * 0.5f;
	m_matWorldUI[14]._11 = m_ArrowSizeX;
	m_matWorldUI[14]._22 = m_ArrowSizeY;
	_matrix matRot1;
	D3DXMatrixRotationZ(&matRot1, D3DXToRadian(270));
	m_matWorldUI[14] *= matRot1;
	m_matWorldUI[14]._41 = m_ArrowPosX[1];
	m_matWorldUI[14]._42 = m_ArrowPosY[1];
	// 화살3 설정
	m_ArrowPosX[2] = WINCX * 0.5f;
	m_ArrowPosY[2] = WINCY * 0.61f;
	m_matWorldUI[15]._11 = m_ArrowSizeX;
	m_matWorldUI[15]._22 = m_ArrowSizeY;
	m_matWorldUI[15]._41 = m_ArrowPosX[2];
	m_matWorldUI[15]._42 = m_ArrowPosY[2];
	// 화살4 설정
	m_ArrowPosX[3] = WINCX * 0.5f;
	m_ArrowPosY[3] = WINCY * 0.39f;
	m_matWorldUI[16]._11 = m_ArrowSizeX;
	m_matWorldUI[16]._22 = m_ArrowSizeY;
	_matrix matRot2;
	D3DXMatrixRotationZ(&matRot2, D3DXToRadian(180));
	m_matWorldUI[16] *= matRot2;
	m_matWorldUI[16]._41 = m_ArrowPosX[3];
	m_matWorldUI[16]._42 = m_ArrowPosY[3];


	// 스킬1
	m_SkillPosX[0] = WINCX * 0.5f;
	m_SkillPosY[0] = WINCY * 0.84f;
	m_SkillSizeX = 74.25f;
	m_SkillSizeY = 74.25f;
	m_matWorldUI[1]._41 = m_SkillPosX[0];
	m_matWorldUI[1]._42 = m_SkillPosY[0];
	m_matWorldUI[1]._11 = m_SkillSizeX;
	m_matWorldUI[1]._22 = m_SkillSizeY;

	// 스킬2
	m_SkillPosX[1] = WINCX * 0.69f;
	m_SkillPosY[1] = WINCY * 0.5f;
	m_matWorldUI[2]._41 = m_SkillPosX[1];
	m_matWorldUI[2]._42 = m_SkillPosY[1];
	m_matWorldUI[2]._11 = m_SkillSizeX;
	m_matWorldUI[2]._22 = m_SkillSizeY;

	// 스킬3
	m_SkillPosX[2] = WINCX * 0.31f;
	m_SkillPosY[2] = WINCY * 0.5f;
	m_matWorldUI[3]._41 = m_SkillPosX[2];
	m_matWorldUI[3]._42 = m_SkillPosY[2];
	m_matWorldUI[3]._11 = m_SkillSizeX;
	m_matWorldUI[3]._22 = m_SkillSizeY;

	// 스킬4
	m_SkillPosX[3] = WINCX * 0.5f;
	m_SkillPosY[3] = WINCY * 0.18;
	m_matWorldUI[4]._41 = m_SkillPosX[3];
	m_matWorldUI[4]._42 = m_SkillPosY[3];
	m_matWorldUI[4]._11 = m_SkillSizeX;
	m_matWorldUI[4]._22 = m_SkillSizeY;

	// 마나링1
	m_ManaSizeX = 30.f;
	m_ManaSizeY = 34.f;
	m_matWorldUI[5]._41 = m_SkillPosX[0];
	m_matWorldUI[5]._42 = m_SkillPosY[0] - 75;
	m_matWorldUI[5]._11 = m_ManaSizeX;
	m_matWorldUI[5]._22 = m_ManaSizeY;
	// 마나링2
	m_matWorldUI[6]._41 = m_SkillPosX[1];
	m_matWorldUI[6]._42 = m_SkillPosY[1] - 75;
	m_matWorldUI[6]._11 = m_ManaSizeX;
	m_matWorldUI[6]._22 = m_ManaSizeY;
	// 마나링3
	m_matWorldUI[7]._41 = m_SkillPosX[2];
	m_matWorldUI[7]._42 = m_SkillPosY[2] - 75;
	m_matWorldUI[7]._11 = m_ManaSizeX;
	m_matWorldUI[7]._22 = m_ManaSizeY;
	// 마나링4
	m_matWorldUI[8]._41 = m_SkillPosX[3];
	m_matWorldUI[8]._42 = m_SkillPosY[3] - 75;
	m_matWorldUI[8]._11 = m_ManaSizeX;
	m_matWorldUI[8]._22 = m_ManaSizeY;

	// 작은링 1
	m_RingSizeX[1] = 90.f;
	m_RingSizeY[1] = 86.175f;
	m_matWorldUI[9]._41 = m_SkillPosX[0];
	m_matWorldUI[9]._42 = m_SkillPosY[0];
	m_matWorldUI[9]._11 = m_RingSizeX[1];
	m_matWorldUI[9]._22 = m_RingSizeY[1];
	// 작은링 2
	m_matWorldUI[10]._41 = m_SkillPosX[1];
	m_matWorldUI[10]._42 = m_SkillPosY[1];
	m_matWorldUI[10]._11 = m_RingSizeX[1];
	m_matWorldUI[10]._22 = m_RingSizeY[1];
	// 작은링 3
	m_matWorldUI[11]._41 = m_SkillPosX[2];
	m_matWorldUI[11]._42 = m_SkillPosY[2];
	m_matWorldUI[11]._11 = m_RingSizeX[1];
	m_matWorldUI[11]._22 = m_RingSizeY[1];
	// 작은링 4
	m_matWorldUI[12]._41 = m_SkillPosX[3];
	m_matWorldUI[12]._42 = m_SkillPosY[3];
	m_matWorldUI[12]._11 = m_RingSizeX[1];
	m_matWorldUI[12]._22 = m_RingSizeY[1];

	// 스킬 픽
	 m_rcPick[0] = { long(m_SkillPosX[0] - m_SkillSizeX / 2.f) , long(m_SkillPosY[0] - m_SkillSizeY / 2.f) ,
		 long(m_SkillPosX[0] + m_SkillSizeX / 2.f) , long(m_SkillPosY[0] + m_SkillSizeY / 2.f) };
	 m_rcPick[1] = { long(m_SkillPosX[1] - m_SkillSizeX / 2.f) , long(m_SkillPosY[1] - m_SkillSizeY / 2.f) ,
		long(m_SkillPosX[1] + m_SkillSizeX / 2.f) , long(m_SkillPosY[1] + m_SkillSizeY / 2.f) };
	 m_rcPick[2] = { long(m_SkillPosX[2] - m_SkillSizeX / 2.f) , long(m_SkillPosY[2] - m_SkillSizeY / 2.f) ,
		long(m_SkillPosX[2] + m_SkillSizeX / 2.f) , long(m_SkillPosY[2] + m_SkillSizeY / 2.f) };
	 m_rcPick[3] = { long(m_SkillPosX[3] - m_SkillSizeX / 2.f) , long(m_SkillPosY[3] - m_SkillSizeY / 2.f) ,
		long(m_SkillPosX[3] + m_SkillSizeX / 2.f) , long(m_SkillPosY[3] + m_SkillSizeY / 2.f) };
	 // 마나링 폰트
	 m_rcFont[0] = { long(m_SkillPosX[3] + 2 - m_ManaSizeX / 2.f) , long(m_SkillPosY[3] + 40 - m_ManaSizeY / 2.f) ,
		long(m_SkillPosX[3] + m_ManaSizeX / 2.f) , long(m_SkillPosY[3] + m_ManaSizeY / 2.f) };
	 m_rcFont[1] = { long(m_SkillPosX[1] + 2 - m_ManaSizeX / 2.f) , long(m_SkillPosY[1] + 52 - m_ManaSizeY / 2.f) ,
		long(m_SkillPosX[1] + m_ManaSizeX / 2.f) , long(m_SkillPosY[1] + m_ManaSizeY / 2.f) };
	 m_rcFont[2] = { long(m_SkillPosX[2] + 2 - m_ManaSizeX / 2.f) , long(m_SkillPosY[2] + 52 - m_ManaSizeY / 2.f) ,
		long(m_SkillPosX[2] + m_ManaSizeX / 2.f) , long(m_SkillPosY[2] + m_ManaSizeY / 2.f) };
	 m_rcFont[3] = { long(m_SkillPosX[0] + 2 - m_ManaSizeX / 2.f) , long(m_SkillPosY[0] + 40 - m_ManaSizeY / 2.f) ,
	   long(m_SkillPosX[0] + m_ManaSizeX / 2.f) , long(m_SkillPosY[0] + m_ManaSizeY / 2.f) };
	return S_OK;
}

_int CFieldSkillUI::Update_Object(const _float& fTimeDelta)
{

	_int iExit = __super::Update_Object(fTimeDelta);

	Mouse_Input();

	if (m_bIsOn)
	{
		if (nullptr == m_pPlayer)
			m_pPlayer = dynamic_cast<CPlayer*>(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::PLAYER, L"Player"));
		if (nullptr != m_pPlayer)
		{
			Set_Skill();
		}


		if (m_bShirnk)
		{
			_vec3 vOut = m_pUITransform[0]->Lerp(_vec3{ m_RingSizeX[0] , m_RingSizeY[0], 0.f }, _vec3{ 240.f , 230.f, 0.f }, 0.1f, fTimeDelta);
			if (vOut.x != -99)
			{
				m_matWorldUI[0]._11 = vOut.x;
				m_matWorldUI[0]._22 = vOut.y;
			}
			else
				m_bShirnk = false;
		}
		if (!m_bReach)
		{
			_vec3 vOut = m_pUITransform[1]->Lerp(_vec3{ m_ArrowPosX[0] , m_ArrowPosY[0], 0.f }
			, _vec3{ m_ArrowPosX[0] - m_fReach , m_ArrowPosY[0], 0.f }, 0.6f, fTimeDelta);
			if (vOut.x != -99)
			{
				m_matWorldUI[13]._41 = vOut.x;
				m_matWorldUI[13]._42 = vOut.y;
			}
			vOut = m_pUITransform[2]->Lerp(_vec3{ m_ArrowPosX[1] , m_ArrowPosY[1], 0.f }
			, _vec3{ m_ArrowPosX[1] + m_fReach , m_ArrowPosY[1], 0.f }, 0.6f, fTimeDelta);
			if (vOut.x != -99)
			{
				m_matWorldUI[14]._41 = vOut.x;
				m_matWorldUI[14]._42 = vOut.y;
			}
			vOut = m_pUITransform[3]->Lerp(_vec3{ m_ArrowPosX[2] , m_ArrowPosY[2], 0.f }
			, _vec3{ m_ArrowPosX[2], m_ArrowPosY[2] + m_fReach, 0.f }, 0.6f, fTimeDelta);
			if (vOut.x != -99)
			{
				m_matWorldUI[15]._41 = vOut.x;
				m_matWorldUI[15]._42 = vOut.y;
			}
			vOut = m_pUITransform[4]->Lerp(_vec3{ m_ArrowPosX[3] , m_ArrowPosY[3], 0.f }
			, _vec3{ m_ArrowPosX[3], m_ArrowPosY[3] - m_fReach, 0.f }, 0.6f, fTimeDelta);
			if (vOut.x != -99)
			{
				m_matWorldUI[16]._41 = vOut.x;
				m_matWorldUI[16]._42 = vOut.y;
			}
			else
				m_bReach = true;
		}
		if (m_bReach)
		{
			_vec3 vOut = m_pUITransform[1]->Lerp(_vec3{ m_ArrowPosX[0] - m_fReach , m_ArrowPosY[0], 0.f }
			, _vec3{ m_ArrowPosX[0], m_ArrowPosY[0], 0.f }, 0.6f, fTimeDelta);
			if (vOut.x != -99)
			{
				m_matWorldUI[13]._41 = vOut.x;
				m_matWorldUI[13]._42 = vOut.y;
			}
			vOut = m_pUITransform[2]->Lerp(_vec3{ m_ArrowPosX[1] + m_fReach , m_ArrowPosY[1], 0.f }
			, _vec3{ m_ArrowPosX[1] , m_ArrowPosY[1], 0.f }, 0.6f, fTimeDelta);
			if (vOut.x != -99)
			{
				m_matWorldUI[14]._41 = vOut.x;
				m_matWorldUI[14]._42 = vOut.y;
			}
			vOut = m_pUITransform[3]->Lerp(_vec3{ m_ArrowPosX[2] , m_ArrowPosY[2] + m_fReach, 0.f }
			, _vec3{ m_ArrowPosX[2], m_ArrowPosY[2], 0.f }, 0.6f, fTimeDelta);
			if (vOut.x != -99)
			{
				m_matWorldUI[15]._41 = vOut.x;
				m_matWorldUI[15]._42 = vOut.y;
			}
			vOut = m_pUITransform[4]->Lerp(_vec3{ m_ArrowPosX[3] , m_ArrowPosY[3] - m_fReach, 0.f }
			, _vec3{ m_ArrowPosX[3], m_ArrowPosY[3], 0.f }, 0.6f, fTimeDelta);
			if (vOut.x != -99)
			{
				m_matWorldUI[16]._41 = vOut.x;
				m_matWorldUI[16]._42 = vOut.y;
			}
			else
				m_bReach = false;
		}

	}
	
	return iExit;
}

void CFieldSkillUI::LateUpdate_Object()
{

	if (m_bIsOn)
	{
		Mouse_Update();
		Picking_UI();

		__super::LateUpdate_Object();
	}
	
}

void CFieldSkillUI::Render_Object()
{

	if (m_bIsOn)
	{
	
		m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));
		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_UImatWorld);
		// 쉐이드 비스무리
		m_pTextureCom->Render_Texture();
		m_pBufferCom->Render_Buffer();

		m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(128, 255, 255, 255));
		// 큰링
		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matWorldUI[0]);
		m_pUITextureCom[0]->Render_Texture();
		m_pBufferCom->Render_Buffer();

		

		if (!m_bShirnk)
		{
			m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(200, 255, 255, 255));
			// 작은 화살표
			m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matWorldUI[13]);
			m_pUITextureCom[1]->Render_Texture();
			m_pBufferCom->Render_Buffer();

			m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matWorldUI[14]);
			m_pUITextureCom[1]->Render_Texture();
			m_pBufferCom->Render_Buffer();

			m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matWorldUI[15]);
			m_pUITextureCom[1]->Render_Texture();
			m_pBufferCom->Render_Buffer();

			m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matWorldUI[16]);
			m_pUITextureCom[1]->Render_Texture();
			m_pBufferCom->Render_Buffer();

			m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));

			// 작은링1
			if (m_bPick[0] && m_pPlayerSkill[0] !=nullptr)
			{
				m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matWorldUI[9]);
				m_pUITextureCom[0]->Render_Texture();
				m_pBufferCom->Render_Buffer();
			}
			// 작은링2
			if (m_bPick[1] && m_pPlayerSkill[1] != nullptr)
			{
				m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matWorldUI[10]);
				m_pUITextureCom[0]->Render_Texture();
				m_pBufferCom->Render_Buffer();
			}
			// 작은링3
			if (m_bPick[2] && m_pPlayerSkill[2] != nullptr)
			{
				m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matWorldUI[11]);
				m_pUITextureCom[0]->Render_Texture();
				m_pBufferCom->Render_Buffer();
			}
			if (m_bPick[3] && m_pPlayerSkill[3] != nullptr)
			{
				// 작은링4
				m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matWorldUI[12]);
				m_pUITextureCom[0]->Render_Texture();
				m_pBufferCom->Render_Buffer();
			}
			
			
			if (m_pPlayerSkill[0] != nullptr)
			{
				// 스킬1
				if (dynamic_cast<CPlayer*>(m_pPlayer)->Get_StatInfo().fCurMP < m_pPlayerSkill[0]->Get_SkillUsage())
				{
					m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 100, 100, 100));
					m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matWorldUI[1]);
					m_pUITextureCom[2]->Render_Texture(m_iSkillKind[0]);
					m_pBufferCom->Render_Buffer();
					m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));
				}
				else
				{
					m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matWorldUI[1]);
					m_pUITextureCom[2]->Render_Texture(m_iSkillKind[0]);
					m_pBufferCom->Render_Buffer();
				}
				// 마나링1
				m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matWorldUI[5]);
				m_pUITextureCom[3]->Render_Texture();
				m_pBufferCom->Render_Buffer();

			
				CGraphicDev::GetInstance()->Get_SkillFont()->DrawTextW(NULL, to_wstring(static_cast<CSkill*>(m_pPlayerSkill[0])->Get_SkillUsage()).c_str(), -1,
					&m_rcFont[0], DT_CENTER | DT_NOCLIP, D3DCOLOR_ARGB(220, 216, 0, 255));
			}
			
			if (m_pPlayerSkill[1] != nullptr)
			{
				// 스킬2
				if (dynamic_cast<CPlayer*>(m_pPlayer)->Get_StatInfo().fCurMP < m_pPlayerSkill[1]->Get_SkillUsage())
				{
					m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 100, 100, 100));
					m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matWorldUI[2]);
					m_pUITextureCom[2]->Render_Texture(m_iSkillKind[1]);
					m_pBufferCom->Render_Buffer();
					m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));
				}
				else
				{
					m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matWorldUI[2]);
					m_pUITextureCom[2]->Render_Texture(m_iSkillKind[1]);
					m_pBufferCom->Render_Buffer();
				}
				// 마나링2
				m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matWorldUI[6]);
				m_pUITextureCom[3]->Render_Texture();
				m_pBufferCom->Render_Buffer();

				CGraphicDev::GetInstance()->Get_SkillFont()->DrawTextW(NULL, to_wstring(static_cast<CSkill*>(m_pPlayerSkill[1])->Get_SkillUsage()).c_str(), -1,
					&m_rcFont[1], DT_CENTER | DT_NOCLIP, D3DCOLOR_ARGB(220, 216, 0, 255));
			}
			
			if (m_pPlayerSkill[2] != nullptr)
			{
				// 스킬3
				if (dynamic_cast<CPlayer*>(m_pPlayer)->Get_StatInfo().fCurMP < m_pPlayerSkill[2]->Get_SkillUsage())
				{
					m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 100, 100, 100));
					m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matWorldUI[3]);
					m_pUITextureCom[2]->Render_Texture(m_iSkillKind[2]);
					m_pBufferCom->Render_Buffer();
					m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));
				}
				else
				{
					m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matWorldUI[3]);
					m_pUITextureCom[2]->Render_Texture(m_iSkillKind[2]);
					m_pBufferCom->Render_Buffer();
				}
				// 마나링3
				m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matWorldUI[7]);
				m_pUITextureCom[3]->Render_Texture();
				m_pBufferCom->Render_Buffer();

				CGraphicDev::GetInstance()->Get_SkillFont()->DrawTextW(NULL, to_wstring(static_cast<CSkill*>(m_pPlayerSkill[2])->Get_SkillUsage()).c_str(), -1,
					&m_rcFont[2], DT_CENTER | DT_NOCLIP, D3DCOLOR_ARGB(220, 216, 0, 255));
			}
			
			if (m_pPlayerSkill[3] != nullptr)
			{
				// 스킬4
				if (dynamic_cast<CPlayer*>(m_pPlayer)->Get_StatInfo().fCurMP < m_pPlayerSkill[3]->Get_SkillUsage())
				{
					m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 100, 100, 100));
					m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matWorldUI[4]);
					m_pUITextureCom[2]->Render_Texture(m_iSkillKind[3]);
					m_pBufferCom->Render_Buffer();
					m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));
				}
				else
				{
					m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matWorldUI[4]);
					m_pUITextureCom[2]->Render_Texture(m_iSkillKind[3]);
					m_pBufferCom->Render_Buffer();
				}
				// 마나링4
				m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matWorldUI[8]);
				m_pUITextureCom[3]->Render_Texture();
				m_pBufferCom->Render_Buffer();

				CGraphicDev::GetInstance()->Get_SkillFont()->DrawTextW(NULL, to_wstring(static_cast<CSkill*>(m_pPlayerSkill[3])->Get_SkillUsage()).c_str(), -1,
					&m_rcFont[3], DT_CENTER | DT_NOCLIP, D3DCOLOR_ARGB(220, 216, 0, 255));
			}
		}
		
		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matMouse);
		m_pCursorTexCom->Render_Texture();
		m_pBufferCom->Render_Buffer();


		__super::Render_Object();
	
	}
}

void CFieldSkillUI::Picking_UI()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	pt.y = WINCY - pt.y;

	if (PtInRect(&m_rcPick[0], pt) && m_pPlayerSkill[0] != nullptr)
	{
		m_bPick[0] = true;
		if (!m_bPlaySound)
		{
			CSoundMgr::GetInstance()->PlaySoundW(L"world_button.wav", CHANNEL_ID::UI_3, VOLUME_PLAYER_UI);
			m_bPlaySound = true;
		}
			
	}
	else if (PtInRect(&m_rcPick[1], pt) && m_pPlayerSkill[1] != nullptr)
	{
		m_bPick[1] = true;
		if (!m_bPlaySound)
		{
			CSoundMgr::GetInstance()->PlaySoundW(L"world_button.wav", CHANNEL_ID::UI_3, VOLUME_PLAYER_UI);
			m_bPlaySound = true;
		}
	}
		
	else if (PtInRect(&m_rcPick[2], pt) && m_pPlayerSkill[2] != nullptr)
	{
		m_bPick[2] = true;
		if (!m_bPlaySound)
		{
			CSoundMgr::GetInstance()->PlaySoundW(L"world_button.wav", CHANNEL_ID::UI_3, VOLUME_PLAYER_UI);
			m_bPlaySound = true;
		}
	}
	else if (PtInRect(&m_rcPick[3], pt) && m_pPlayerSkill[3] != nullptr)
	{
		m_bPick[3] = true;
		if (!m_bPlaySound)
		{
			CSoundMgr::GetInstance()->PlaySoundW(L"world_button.wav", CHANNEL_ID::UI_3, VOLUME_PLAYER_UI);
			m_bPlaySound = true;
		}
	}
	else
	{
		for (_uint i = 0; i < 4; ++i)
			m_bPick[i] = false;
		for (_uint i = 0; i < 4; ++i)
			m_bSkill[i] = false;

		m_bPlaySound = false;
	}


}

void CFieldSkillUI::Mouse_Update()
{
	POINT CursorUIpt;
	GetCursorPos(&CursorUIpt);
	ScreenToClient(g_hWnd, &CursorUIpt);

	CursorUIpt.y = WINCY - CursorUIpt.y;

	m_matMouse._41 = CursorUIpt.x;
	m_matMouse._42 = CursorUIpt.y - 70.f * 0.3f;
	m_matMouse._11 = 70.f * 0.3f;
	m_matMouse._22 = 87.f * 0.3f;
}

void CFieldSkillUI::Mouse_Input()
{
	if (CInputDev::GetInstance()->Get_DIMouseState(DIM_RB))
	{
		if(!m_bIsOn)
			CSoundMgr::GetInstance()->PlaySoundW(L"scroll_select.wav", CHANNEL_ID::UI_3, VOLUME_PLAYER_UI);

		m_bIsOn = true;
		
		CManagement::GetInstance()->Get_Layer(OBJ_TYPE::PLAYER)->Layer_SetActive(false);
		CManagement::GetInstance()->Get_Layer(OBJ_TYPE::MONSTER)->Layer_SetActive(false);
		CManagement::GetInstance()->Get_Layer(OBJ_TYPE::EFFECT)->Layer_SetActive(false);

		CRingUI* pRingUI = static_cast<CRingUI*>
			(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"UI_Ring"));
		pRingUI->Set_Active(false);

		m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 235, 168, 35));

		
	}
	else
	{
		if (m_bIsOn)
		{
			CManagement::GetInstance()->Get_Layer(OBJ_TYPE::PLAYER)->Layer_SetActive(true);
			CManagement::GetInstance()->Get_Layer(OBJ_TYPE::EFFECT)->Layer_SetActive(true);
			CManagement::GetInstance()->Get_Layer(OBJ_TYPE::MONSTER)->Layer_SetActive(true);
		}
		m_bIsOn = false;
		
		Play_SKill();

		Reset_SkillUI();

		

		CRingUI* pRingUI = static_cast<CRingUI*>
			(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"UI_Ring"));
		pRingUI->Set_Active(true);

		
	}
}

void CFieldSkillUI::Reset_SkillUI()
{
	m_bShirnk = true;
	m_bReach = false;

	for (_uint i = 0; i < 4; ++i)
		m_bPick[i] = false;
	for (_uint i = 0; i < 4; ++i)
		m_bSkill[i] = false;

	for (_uint i = 0; i < 4; ++i)
	{
		m_pPlayerSkill[i] = nullptr;
	}


	for (_uint i = 0; i < 5; ++i)
	{
		m_pUITransform[i]->Reset_Lerp();
	}
}

void CFieldSkillUI::Play_SKill()
{
	for (_uint i = 0; i < 4; ++i)
	{
		if (m_bPick[i])
		{
			if (m_pPlayerSkill[i] != nullptr && dynamic_cast<CPlayer*>(m_pPlayer)->Get_StatInfo().fCurMP >= m_pPlayerSkill[i]->Get_SkillUsage())
			{
				m_pPlayerSkill[i]->Play();
				m_pPlayer->Using_Mana(m_pPlayerSkill[i]->Get_SkillUsage());
				CCameraMgr::GetInstance()->Start_Action(CAMERA_ACTION::PLAYER_IDL_TO_ATK);
			}
		}
	}
}

void CFieldSkillUI::Set_Skill()
{
	for (_uint i = 0; i < 4; ++i)
	{
		CSkill* pSkill = m_pPlayer->Get_SkillSlot(i);
		if (pSkill != nullptr)
		{
			m_pPlayerSkill[i] = pSkill;
			OBJ_ID eSKillID = m_pPlayerSkill[i]->Get_ID();
			switch (eSKillID)
			{
			case Engine::OBJ_ID::SKILL_PLAYER_FIRE:
				m_iSkillKind[i] = 0;
				break;
			case Engine::OBJ_ID::SKILL_PLAYER_THUNDER:
				m_iSkillKind[i] = 1;
				break;
			case Engine::OBJ_ID::SKILL_PLAYER_ICE:
				m_iSkillKind[i] = 2;
				break;
			case Engine::OBJ_ID::SKILL_PLAYER_BEAM:
				m_iSkillKind[i] = 3;
				break;
			case Engine::OBJ_ID::SKILL_PLAYER_HEAL:
				m_iSkillKind[i] = 4;
				break;
			default:
				break;
			}
		}
	}
}

HRESULT CFieldSkillUI::Add_Component()
{

	CComponent* pComponent = nullptr;
	// 메인
	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_UI_Shade", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	// 서브
	pComponent = m_pUITextureCom[0] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_UI_Ring", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pUITextureCom[1] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_UI_SmallArrow", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pUITextureCom[2] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_UI_Skill", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pUITextureCom[3] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_UI_MpCircle", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pCursorTexCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Cursor", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	for (_uint i = 0; i < 5; ++i)
	{
		pComponent = m_pUITransform[i] = dynamic_cast<CTransform*>(Engine::Clone_Proto(COMPONENT_TYPE::TRANSFORM, this));
		NULL_CHECK_RETURN(pComponent, E_FAIL);
		m_mapComponent[ID_DYNAMIC].emplace(COMPONENT_TYPE::TRANSFORM, pComponent);
	}


	return S_OK;
}

CFieldSkillUI* CFieldSkillUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CFieldSkillUI* pInstance = new CFieldSkillUI(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("FieldSkillUI Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CFieldSkillUI::Free()
{
	__super::Free();

}
