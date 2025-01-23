#include "BoomEffect_Green.h"
#include "Export_Function.h"



CBoomEffect_Green::CBoomEffect_Green(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& _pPos)
    : CEffect(pGraphicDev, OBJ_ID::EFFECT_BOOM_GREEN)
{
    m_vPos = _pPos;

}

CBoomEffect_Green::CBoomEffect_Green(const CEffect& rhs)
    : CEffect(rhs)
{
}

CBoomEffect_Green::~CBoomEffect_Green()
{
}

HRESULT CBoomEffect_Green::Ready_Object()
{

	__super::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);


	m_pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom, STATE_TYPE::FRONT_IDLE, 0.1f, FALSE);


	m_bActive = true;

    return S_OK;
}

_int CBoomEffect_Green::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);
	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	m_pTransformCom->Set_Pos({ m_vPos.x , m_vPos.y, m_vPos.z - 0.1f });
	m_pTransformCom->Set_Scale(_vec3{ 2.f, 2.f, 0.1f });
	m_pAnimation->Update_Animation(fTimeDelta);

	if (m_pAnimation->Is_End())
	{
		CEventMgr::GetInstance()->Delete_Obj(this);
	}


	return iExit;
}

void CBoomEffect_Green::LateUpdate_Object()
{



	__super::LateUpdate_Object();
}

void CBoomEffect_Green::Render_Object()
{
	__super::Render_Object();

	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));

	m_pAnimation->Render_Animation();

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));
}

HRESULT CBoomEffect_Green::Add_Component()
{
	CComponent* pComponent = nullptr;

	
	// Texture
	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Projectile_Boom_Green", this));
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

CBoomEffect_Green* CBoomEffect_Green::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& _pPos)
{
	CBoomEffect_Green* pInstance = new CBoomEffect_Green(pGraphicDev, _pPos);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Hit purple Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CBoomEffect_Green::Free()
{
	m_pAnimation->Release();
	__super::Free();
}
