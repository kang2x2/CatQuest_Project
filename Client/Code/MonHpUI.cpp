#include "MonHpUI.h"
#include "Export_Function.h"

#include "Monster.h"

CMonHpUI::CMonHpUI(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUI(pGraphicDev, OBJ_ID::UI_HP), m_pMonster(nullptr), m_fHpRatio(1.f), m_fCurRatio(1.f)
{
}

CMonHpUI::CMonHpUI(const CMonHpUI& rhs)
	: CUI(rhs)
{
}

CMonHpUI::~CMonHpUI()
{
}

HRESULT CMonHpUI::Ready_Object()
{
	CGameObject::Ready_Object();

	m_eUIType = UI_TYPE::VIEW;

	m_bShow = false;
	m_iAlpha = 0;

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	for (_uint i = 0; i < 5; ++i)
		D3DXMatrixIdentity(&m_matUI[i]);

	m_fSizeX = 15.f;
	m_fSizeY = 15.f;
	m_fBarMultiX = 1.6f;
	m_fBarMultiY = 0.5f;

	m_fCapSizeX = 24.f;
	m_fCapSizeY = 23.5f;
	m_fCapMultiX = 0.5f;
	m_fCapMultiY = 0.5f;

	m_fBarRealX = m_fSizeX * m_fBarMultiX;
	m_fBarRealY = m_fSizeY * m_fBarMultiY;
	m_fCapRealX = m_fCapSizeX * m_fCapMultiX;
	m_fCapRealY = m_fCapSizeY * m_fCapMultiY;


	m_matUI[0]._11 = m_fBarRealX;
	m_matUI[0]._22 = m_fBarRealY;

	m_matUI[1]._11 = m_fBarRealX;
	m_matUI[1]._22 = m_fBarRealY;

	m_matUI[2]._11 = m_fCapRealX;
	m_matUI[2]._22 = m_fCapRealY;

	m_matUI[3]._11 = m_fCapRealX;
	m_matUI[3]._22 = m_fCapRealY;

	m_matUI[4]._11 = m_fBarRealX;
	m_matUI[4]._22 = m_fBarRealY;

	/*m_pUITransformCom[0]->Set_Scale(_vec3{ 1.4f, 0.4f, 1.f });
	m_pUITransformCom[1]->Set_Scale(_vec3{ 1.4f, 0.4f, 1.f });
	m_pUITransformCom[2]->Set_Scale(_vec3{ 0.6f, 0.6f, 1.f });
	m_pUITransformCom[3]->Set_Scale(_vec3{ 0.6f, 0.6f, 1.f });
	m_pUITransformCom[4]->Set_Scale(_vec3{ 1.4f, 0.4f, 1.f });*/

	return S_OK;
}

_int CMonHpUI::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);
	
	if (nullptr == m_pMonster)
	{
		CEventMgr::GetInstance()->Delete_Obj(this);  // 삭제
		return	iExit;
	}


	if (nullptr != m_pMonster)
		m_fCurRatio = dynamic_cast<CMonster*>(m_pMonster)->Get_StatInfo().fCurHP / dynamic_cast<CMonster*>(m_pMonster)->Get_StatInfo().fMaxHP;

	if (dynamic_cast<CMonster*>(m_pMonster)->Get_StatInfo().bDead)
	{
		CEventMgr::GetInstance()->Delete_Obj(this);  // 삭제
		return iExit;
	}

	if (1.f < m_fCurRatio)
	{
		m_fCurRatio = 1.f;
		m_fHpRatio = m_fCurRatio;
	}

	if (m_bShow && !m_tAlpha.bActive)
	{
		m_tAlpha.Init_Lerp(LERP_MODE::EASE_IN);
		m_tAlpha.Set_Lerp(0.2f, m_iAlpha, 255);
		m_tAlpha.fCurValue = m_tAlpha.fStartValue;
	}
	else if (!m_bShow && !m_tAlpha.bActive)
	{
		m_tAlpha.Init_Lerp(LERP_MODE::EASE_IN);
		m_tAlpha.Set_Lerp(0.2f, m_iAlpha, 0);
		m_tAlpha.fCurValue = m_tAlpha.fStartValue;
	}

	m_tAlpha.Update_Lerp(fTimeDelta);

	return iExit;
}

void CMonHpUI::LateUpdate_Object()
{
	m_iAlpha = m_tAlpha.fCurValue;

	Follow_Owner();

	_vec3 vInitPosition = m_matUI[1].m[3];

	float fMoveX = (1.0f - m_fCurRatio) * m_fBarRealX;
	_vec3 vNewPosition = _vec3(vInitPosition.x - fMoveX, vInitPosition.y, 0.f);

	m_matUI[1]._11 = m_fBarRealX * m_fCurRatio;
	memcpy(&m_matUI[1].m[3], &vNewPosition, sizeof(_vec3));
	/*m_pUITransformCom[1]->Set_Scale(_vec3{ 1.6f * m_fCurRatio, 0.4f, 1.0f });
	m_pUITransformCom[1]->Set_Pos(vNewPosition);*/

	if (m_fCurRatio >= 1.f)
	{
		m_matUI[4]._11 = m_fBarRealX;
		//m_pUITransformCom[4]->Set_Scale(_vec3{ 1.6f, 0.4f, 1.f });
		m_pUITransformCom[4]->Reset_Lerp();
	}
	else if (m_fCurRatio >= m_fHpRatio && m_fCurRatio < 1.f)
	{
		m_matUI[4]._11 = m_fBarRealX * m_fCurRatio;
		memcpy(&m_matUI[4].m[3], &vNewPosition, sizeof(_vec3));
		m_pUITransformCom[4]->Reset_Lerp();
		m_fHpRatio = m_fCurRatio;

	}
	else if (m_fCurRatio <= m_fHpRatio && m_fCurRatio < 1.f)
	{
		_vec3 vHpSize{ m_matUI[1]._11, m_matUI[1]._22, 0.f };
		_vec3 vGoldSize{ m_matUI[4]._11, m_matUI[4]._22, 0.f };

		/*_vec3 vOutScale = m_pUITransformCom[4]->Lerp(m_pUITransformCom[4]->Get_Scale()
			, m_pUITransformCom[1]->Get_Scale(), 1.2f, Engine::Get_TimeDelta(L"Timer_FPS65"));*/

		_vec3 vOutScale = m_pUITransformCom[4]->Lerp(vGoldSize, vHpSize, 1.2f, Engine::Get_TimeDelta(L"Timer_FPS65"));

		if (vOutScale.z != -99)
		{
			/*	_vec3 vGoldInitPosition = m_pUITransformCom[4]->Get_Info(INFO::INFO_POS);

				float fGoldMoveX = (1.0f - (vOutScale.x / 1.6f)) * 1.6f;
				_vec3 vGoldNewPosition = _vec3(vGoldInitPosition.x - fGoldMoveX, vGoldInitPosition.y, vGoldInitPosition.z);

				m_pUITransformCom[4]->Set_Scale(vOutScale);
				m_pUITransformCom[4]->Set_Pos(vGoldNewPosition);*/
			_vec3 vGoldInitPosition = m_matUI[4].m[3];
			float fGoldMoveX = (1.0f - (vOutScale.x / m_fBarRealX)) * m_fBarRealX;
			_vec3 vGoldNewPosition = _vec3(vGoldInitPosition.x - fGoldMoveX, vGoldInitPosition.y, 0.f);

			m_matUI[4]._11 = vOutScale.x;
			memcpy(&m_matUI[4].m[3], &vGoldNewPosition, sizeof(_vec3));
		}
		else
			m_fHpRatio = m_fCurRatio;
	}
	if (m_fCurRatio == m_fHpRatio)
	{
		m_matUI[4]._11 = m_fBarRealX * m_fCurRatio;
		memcpy(&m_matUI[4].m[3], &vNewPosition, sizeof(_vec3));
		m_pUITransformCom[4]->Reset_Lerp();
	}

	if (m_pMonster->Get_ID() != OBJ_ID::MONSTER_TURRETSKULL)
	{
		if (dynamic_cast<CMonster*>(m_pMonster)->Get_StateMachine()->Get_CurState() == STATE_TYPE::CHASE ||
			dynamic_cast<CMonster*>(m_pMonster)->Get_StateMachine()->Get_CurState() == STATE_TYPE::BACK_CHASE ||
			dynamic_cast<CMonster*>(m_pMonster)->Get_StateMachine()->Get_CurState() == STATE_TYPE::MONATTACK ||
			dynamic_cast<CMonster*>(m_pMonster)->Get_StateMachine()->Get_CurState() == STATE_TYPE::BACK_MONATTACK ||
			dynamic_cast<CMonster*>(m_pMonster)->Get_StateMachine()->Get_CurState() == STATE_TYPE::MONREST ||
			dynamic_cast<CMonster*>(m_pMonster)->Get_StateMachine()->Get_CurState() == STATE_TYPE::BACK_MONREST ||
			dynamic_cast<CMonster*>(m_pMonster)->IsHit())
		{
			m_bShow = true;
		}
		else
		{
			m_bShow = false;
		}
	}
	else
	{

	}
	

	__super::LateUpdate_Object();

}

void CMonHpUI::Render_Object()
{

	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(m_iAlpha, 255, 255, 255));

	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

	/*m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pUITransformCom[0]->Get_WorldMat());
	m_pTextureCom->Render_Texture(7);
	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pUITransformCom[4]->Get_WorldMat());
	m_pTextureCom->Render_Texture(10);
	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pUITransformCom[1]->Get_WorldMat());
	m_pTextureCom->Render_Texture(1);
	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pUITransformCom[2]->Get_WorldMat());
	m_pTextureCom->Render_Texture(9);
	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pUITransformCom[3]->Get_WorldMat());
	m_pTextureCom->Render_Texture(6);
	m_pBufferCom->Render_Buffer();*/
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matUI[0]);
	m_pTextureCom->Render_Texture(7);
	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matUI[4]);
	m_pTextureCom->Render_Texture(10);
	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matUI[1]);
	m_pTextureCom->Render_Texture(1);
	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matUI[2]);
	m_pTextureCom->Render_Texture(9);
	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matUI[3]);
	m_pTextureCom->Render_Texture(6);
	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));

}

HRESULT CMonHpUI::Add_Component()
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

void CMonHpUI::Follow_Owner()
{
	CTransform* pMonsterTransform = m_pMonster->Get_Transform();
	NULL_CHECK(pMonsterTransform);
	_vec3 vMonsterPos = pMonsterTransform->Get_Info(INFO_POS);

	_matrix matView = CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Get_MatView();
	_matrix matProj = CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Get_MatProj();
	D3DVIEWPORT9 pViewport = CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Get_ViewPort();

	D3DXVec3TransformCoord(&vMonsterPos, &vMonsterPos, &matView);
	D3DXVec3TransformCoord(&vMonsterPos, &vMonsterPos, &matProj);

	_float fMonScreenX = vMonsterPos.x * (pViewport.Width / 2) + pViewport.X + (pViewport.Width / 2);
	_float fMonScreenY = WINCY - (-vMonsterPos.y * (pViewport.Height / 2) + pViewport.Y + (pViewport.Height / 2));


	/*m_pUITransformCom[0]->Set_Pos({ vMonsterPos.x , vMonsterPos.y, vMonsterPos.z - 3.5f });
	m_pUITransformCom[1]->Set_Pos({ vMonsterPos.x, vMonsterPos.y, vMonsterPos.z - 3.5f });
	m_pUITransformCom[2]->Set_Pos({ vMonsterPos.x - 1.9f, vMonsterPos.y, vMonsterPos.z - 3.5f });
	m_pUITransformCom[3]->Set_Pos({ vMonsterPos.x + 1.4f, vMonsterPos.y, vMonsterPos.z - 3.5f });
	m_pUITransformCom[4]->Set_Pos({ vMonsterPos.x , vMonsterPos.y, vMonsterPos.z - 3.5f });*/

	memcpy(&m_matUI[0].m[3], &_vec3{ fMonScreenX , fMonScreenY - 50.f, 0.f }, sizeof(_vec3));
	memcpy(&m_matUI[1].m[3], &_vec3{ fMonScreenX  , fMonScreenY - 50.f, 0.f }, sizeof(_vec3));
	memcpy(&m_matUI[2].m[3], &_vec3{ fMonScreenX - 34.f, fMonScreenY - 50.f, 0.f }, sizeof(_vec3));
	memcpy(&m_matUI[3].m[3], &_vec3{ fMonScreenX + 24.f, fMonScreenY - 50.f, 0.f }, sizeof(_vec3));
	memcpy(&m_matUI[4].m[3], &_vec3{ fMonScreenX , fMonScreenY - 50.f, 0.f }, sizeof(_vec3));
}

CMonHpUI* CMonHpUI::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* pMonster)
{
	CMonHpUI* pInstance = new CMonHpUI(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("MonHpUI Create Failed");
		return nullptr;
	}
	pInstance->Set_Owner(pMonster);

	return pInstance;
}

void CMonHpUI::Free()
{
	__super::Free();

}

