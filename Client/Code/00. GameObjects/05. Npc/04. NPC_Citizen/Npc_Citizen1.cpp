#include "stdafx.h"
#include "Npc_Citizen1.h"

#include "Export_Function.h"

#include "Shadow_Npc.h"

CNpc_Citizen1::CNpc_Citizen1(LPDIRECT3DDEVICE9 pGraphicDev)
	: CNpc(pGraphicDev, OBJ_ID::NPC_CITIZEN_1)
{
}

CNpc_Citizen1::CNpc_Citizen1(const CNpc& rhs)
	: CNpc(rhs)
{
}


CNpc_Citizen1::~CNpc_Citizen1()
{
}

HRESULT CNpc_Citizen1::Ready_Object()
{
	CNpc::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom, STATE_TYPE::FRONT_IDLE, 0.1f, true);

	m_pTransformCom->Set_Pos(_vec3{ 80.f, m_pTransformCom->Get_Scale().y + 1.f, 125.f });
	m_pTransformCom->Set_Scale(_vec3{ 2.f, 2.f, 2.f });

	if (CManagement::GetInstance()->Get_PlayMode() == PLAY_MODE::GAME)
		CEventMgr::GetInstance()->Add_Obj(L"Npc_Citizen1_Shadow", CShadow_Npc::Create(m_pGraphicDev, this));

	m_szName = L"Npc_Citizen1";

	return S_OK;
}

_int CNpc_Citizen1::Update_Object(const _float& fTimeDelta)
{
	_int iExit = CNpc::Update_Object(fTimeDelta);

	return iExit;
}

void CNpc_Citizen1::LateUpdate_Object()
{
	CNpc::LateUpdate_Object();
}

void CNpc_Citizen1::Render_Object()
{
	CNpc::Render_Object();
}

void CNpc_Citizen1::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CNpc_Citizen1::OnCollision_Stay(CGameObject* _pColObj)
{
	switch (_pColObj->Get_Type())
	{
	case Engine::OBJ_TYPE::PLAYER:
	{
		m_bCol = true;
	}
	break;
	default:
		break;
	}
}

void CNpc_Citizen1::OnCollision_Exit(CGameObject* _pColObj)
{
	m_bCol = false;
}

HRESULT CNpc_Citizen1::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Npc_Citizen1", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CNpc_Citizen1* CNpc_Citizen1::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CNpc_Citizen1* pInstance = new CNpc_Citizen1(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Npc_Citizen1 Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CNpc_Citizen1::Free()
{
	CNpc::Free();
}
