#pragma once
#include "Skill.h"

BEGIN(Engine)

class CTexture;
class CAIComponent;
class CVIBuffer;

END

class CSkill_Player_Arrow :
	public CSkill
{
protected:
	explicit CSkill_Player_Arrow(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID);
	explicit CSkill_Player_Arrow(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);
	explicit CSkill_Player_Arrow(const CSkill_Player_Arrow& rhs);
	virtual ~CSkill_Player_Arrow();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;


	virtual void			OnCollision_Enter(CGameObject* _pColObj);
	virtual void			OnCollision_Stay(CGameObject* _pColObj);
	virtual void			OnCollision_Exit(CGameObject* _pColObj);

private:
	HRESULT			Add_Component();

public:
	virtual HRESULT			Play();
	virtual HRESULT			End();

private:
	void	Picking_Terrain();

private:
	CTexture*		m_pTargetTexCom;
	CVIBuffer*		m_pTargetBuffer;
	CAIComponent*	m_pAICom;

	_vec3			m_vMousePos;


	_matrix			m_matRot;

	_bool			m_bAttack;
	_bool			m_bIsEffectEnd;



public:
	static CSkill_Player_Arrow* Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);

protected:
	virtual void			Free();
};

