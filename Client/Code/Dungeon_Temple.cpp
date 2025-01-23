#include "stdafx.h"
#include "Dungeon_Temple.h"

#include "Export_Function.h"
#include "Scene_Dungeon_Swamp.h"
#include "Scene_Dungeon_Temple.h"
#include "Scene_World.h"
#include "QuestMgr.h"

CDungeon_Temple::CDungeon_Temple(LPDIRECT3DDEVICE9 pGraphicDev)
	: CDungeon(pGraphicDev, OBJ_ID::ENVIRONMENT_ENTERANCE_DUNGEON_TEMPLE)
{
}

CDungeon_Temple::CDungeon_Temple(const CDungeon& rhs)
	: CDungeon(rhs)
{
}

CDungeon_Temple::~CDungeon_Temple()
{
}

HRESULT CDungeon_Temple::Ready_Object()
{
	CDungeon::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 3.f, 3.f, 3.f });
	m_pTransformCom->Set_Pos(_vec3{ 50.f, m_pTransformCom->Get_Scale().y, 80.f });
	
	m_szName = L"Dungeon_Temple";
	
	return S_OK;
}

_int CDungeon_Temple::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CDungeon_Temple::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CDungeon_Temple::Render_Object()
{
	__super::Render_Object();

	if (m_bReservedSceneChange && !CCameraMgr::GetInstance()->Is_Fade())
	{
		if (CManagement::GetInstance()->Get_CurScene()->Get_SceneType() == SCENE_TYPE::WORLD)
		{
			CScene* pScene = nullptr;
			pScene = CScene_Dungeon_Temple::Create(m_pGraphicDev);
			NULL_CHECK(pScene); // 예외처리 추가
			CEventMgr::GetInstance()->Change_Scene(pScene);
			CQuestMgr::GetInstance()->Set_IsAble(false);
		}
		else if (CManagement::GetInstance()->Get_CurScene()->Get_SceneType() == SCENE_TYPE::DUNGEON_TEMPLE)
		{
			CScene* pScene = nullptr;
			pScene = CScene_World::Create(m_pGraphicDev);
			NULL_CHECK(pScene); // 예외처리 추가
			CEventMgr::GetInstance()->Change_Scene(pScene);
			CQuestMgr::GetInstance()->Set_IsAble(false);
		}
	}
}

void CDungeon_Temple::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CDungeon_Temple::OnCollision_Stay(CGameObject* _pColObj)
{
	switch (_pColObj->Get_Type())
	{
	case Engine::OBJ_TYPE::PLAYER:
	{
		m_bCol = true;
		if (!m_bReservedSceneChange && CInputDev::GetInstance()->Key_Down('E'))
		{
			m_bReservedSceneChange = true;
			CCameraMgr::GetInstance()->Start_Fade(FADE_MODE::BLACK_FADE_OUT);
		}
	}
	break;
	default:
		break;
	}
}

void CDungeon_Temple::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CDungeon_Temple::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Dungeon_Temple", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CDungeon_Temple* CDungeon_Temple::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CDungeon_Temple* pInstance = new CDungeon_Temple(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Dungeon_Temple Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CDungeon_Temple::Free()
{
	__super::Free();
}
