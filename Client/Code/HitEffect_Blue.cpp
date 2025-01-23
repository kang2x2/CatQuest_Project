#include "HitEffect_Blue.h"
#include "Export_Function.h"



CHitEffect_Blue::CHitEffect_Blue(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& _pPos)
    : CEffect(pGraphicDev, OBJ_ID::EFFECT_HIT_BLUE)
{
    m_vPos = _pPos;

}

CHitEffect_Blue::CHitEffect_Blue(const CEffect& rhs)
    : CEffect(rhs)
{
}

CHitEffect_Blue::~CHitEffect_Blue()
{
}

HRESULT CHitEffect_Blue::Ready_Object()
{

	__super::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);


	m_pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom, STATE_TYPE::FRONT_IDLE, 0.1f, FALSE);


	m_bActive = true;

    return S_OK;
}

_int CHitEffect_Blue::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);
	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	m_pTransformCom->Set_Pos({ m_vPos.x , m_vPos.y, m_vPos.z - 0.1f });
	m_pTransformCom->Set_Scale(_vec3{ 3.f, 3.f, 0.1f });
	m_pAnimation->Update_Animation(fTimeDelta);

	if (m_pAnimation->Is_End())
	{
		CEventMgr::GetInstance()->Delete_Obj(this);
	}


	return iExit;
}

void CHitEffect_Blue::LateUpdate_Object()
{



	__super::LateUpdate_Object();
}

void CHitEffect_Blue::Render_Object()
{
	__super::Render_Object();

	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));

	m_pAnimation->Render_Animation();

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));
}

HRESULT CHitEffect_Blue::Add_Component()
{
	CComponent* pComponent = nullptr;

	
	// Texture
	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Projectile_Hit_Green", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);
	

	// Buffer
	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	// animation
	//CAnimation* pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom, STATE_TYPE::FRONT_IDLE, 0.1f, FALSE);
	//m_pAnimatorCom->Add_Animation(STATE_TYPE::FRONT_IDLE, pAnimation);




    return S_OK;
}

CHitEffect_Blue* CHitEffect_Blue::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& _pPos)
{
	CHitEffect_Blue* pInstance = new CHitEffect_Blue(pGraphicDev, _pPos);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Hit purple Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CHitEffect_Blue::Free()
{
	m_pAnimation->Release();
	__super::Free();
}
