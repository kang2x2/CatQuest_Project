#pragma once
#include "Skill.h"
class CSkill_Boss_CreateWyvern : public CSkill
{
protected:
	explicit CSkill_Boss_CreateWyvern(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CSkill_Boss_CreateWyvern(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);
	explicit CSkill_Boss_CreateWyvern(const CSkill_Boss_CreateWyvern& rhs);
	virtual ~CSkill_Boss_CreateWyvern();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

public:
	virtual void			OnCollision_Enter(CGameObject* _pColObj) {};
	virtual void			OnCollision_Stay(CGameObject* _pColObj) {};
	virtual void			OnCollision_Exit(CGameObject* _pColObj) {};


private:
	HRESULT					Add_Component();


public:
	virtual HRESULT			Play();
	virtual HRESULT			LatePlay();
	virtual HRESULT			End();


public:

	static CSkill_Boss_CreateWyvern* Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);

private:

	// wyvern
	CEffect_Range_Quater* m_pBaseRangeEffect1;
	CEffect_Range_Quater* m_pBaseRangeEffect2;
	CEffect_Range_Quater* m_pBaseRangeEffect3;
	CEffect_Range_Quater* m_pBaseRangeEffect4;
	CEffect_Range_Quater* m_pBaseRangeEffect5;
	CEffect_Range_Quater* m_pBaseRangeEffect6;
	CEffect_Range_Quater* m_pBaseRangeEffect7;
	CEffect_Range_Quater* m_pBaseRangeEffect8;
	CEffect_Range_Quater* m_pBaseRangeEffect9;
	CEffect_Range_Quater* m_pBaseRangeEffect10;

	CEffect_Range_Quater* m_pBaseRangeEffect11;
	CEffect_Range_Quater* m_pBaseRangeEffect12;



	// Other
	CEffect_Range_Quater* m_pBaseRangeEffect13;
	CEffect_Range_Quater* m_pBaseRangeEffect14;
	CEffect_Range_Quater* m_pBaseRangeEffect15;
	CEffect_Range_Quater* m_pBaseRangeEffect16;
	CEffect_Range_Quater* m_pBaseRangeEffect17;
	CEffect_Range_Quater* m_pBaseRangeEffect18;
	CEffect_Range_Quater* m_pBaseRangeEffect19;
	CEffect_Range_Quater* m_pBaseRangeEffect20;





	_vec3 vCreatePosition;
	_vec3 vCreateBossPosition;

protected:
	virtual void			Free();



};

