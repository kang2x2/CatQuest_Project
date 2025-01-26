#include "stdafx.h"
#include "Npc_King.h"

#include "Export_Function.h"

#include "Shadow_Npc.h"

#include "TalkMgr.h"
#include "QuestMgr.h"

CNpc_King::CNpc_King(LPDIRECT3DDEVICE9 pGraphicDev)
	: CNpc(pGraphicDev, OBJ_ID::NPC_KING)
{
}

CNpc_King::CNpc_King(const CNpc& rhs)
	: CNpc(rhs)
{
}


CNpc_King::~CNpc_King()
{
}

HRESULT CNpc_King::Ready_Object()
{
	CNpc::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom, STATE_TYPE::FRONT_IDLE, 0.1f, true);

	m_pTransformCom->Set_Pos(_vec3{ 340.f, m_pTransformCom->Get_Scale().y + 2.f, 80.f });
	m_pTransformCom->Set_Scale(_vec3{ 3.0f, 3.6f, 3.0f });

	if(CManagement::GetInstance()->Get_PlayMode() == PLAY_MODE::GAME)
		CEventMgr::GetInstance()->Add_Obj(L"Npc_King_Shadow", CShadow_Npc::Create(m_pGraphicDev, this));

	m_szName = L"Npc_King";

	return S_OK;
}

_int CNpc_King::Update_Object(const _float& fTimeDelta)
{
	_int iExit = CNpc::Update_Object(fTimeDelta);

	return iExit;
}

void CNpc_King::LateUpdate_Object()
{
	CNpc::LateUpdate_Object();
}

void CNpc_King::Render_Object()
{
	CNpc::Render_Object();
}

void CNpc_King::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CNpc_King::OnCollision_Stay(CGameObject* _pColObj)
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

void CNpc_King::OnCollision_Exit(CGameObject* _pColObj)
{
	m_bCol = false;
}

HRESULT CNpc_King::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Npc_King", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CNpc_King* CNpc_King::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CNpc_King* pInstance = new CNpc_King(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Npc_King Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CNpc_King::Free()
{
	CNpc::Free();
}
