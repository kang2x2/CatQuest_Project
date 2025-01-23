#pragma once

#include "Component.h"
#include "Animation.h"

BEGIN(Engine)

class CAnimation;

class ENGINE_DLL CAnimator : public CComponent
{
private:
	explicit CAnimator();
	explicit CAnimator(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CAnimator(const CAnimator& rhs, CGameObject* _pOwnerObject);
	virtual ~CAnimator();

public:
	HRESULT					Ready_Animator();
	void					Update_Animator(const _float& fTimeDelta);
	void					Render_Animator();

public:
	CAnimation*				Get_CurAniamtion() { return m_pCurAnimation; }

public:
	HRESULT					Add_Animation(STATE_TYPE eState, CAnimation* pAnimation);
	void					Set_Animation(STATE_TYPE eState);


private:
	map<STATE_TYPE, CAnimation*>	m_AnimationMap;
	CAnimation*						m_pCurAnimation;
	STATE_TYPE						m_eCurState;


public:
	static CAnimator*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent*		Clone(CGameObject* _pOwnerObject);

private:
	virtual void			Free();

};

END