#pragma once
#include "GameObject.h"
#include "Monster.h"

class CRangeObj;
BEGIN(Engine)

class CCubeCol;
class CCollider;

END

class CVioletDragon : public CMonster
{
protected:

	explicit CVioletDragon(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CVioletDragon(const CMonster& rhs);
	virtual ~CVioletDragon();


public:
	virtual HRESULT		Ready_Object() override;
	virtual _int		Update_Object(const _float& fTimeDelta) override;
	virtual void		LateUpdate_Object() override;
	virtual void		Render_Object() override;


public:
	virtual void		OnCollision_Enter(CGameObject* _pColObj) override;
	virtual void		OnCollision_Stay(CGameObject* _pColObj) override;
	virtual void		OnCollision_Exit(CGameObject* _pColObj) override;

private:
	HRESULT				Add_Component();


public:
	static				CVioletDragon* Create(LPDIRECT3DDEVICE9 pGraphicDev);


public:
	
	_bool			Get_HP90() { return m_bHP_90; }
	_bool			Get_HP60() { return m_bHP_60; }
	_bool			Get_HP30() { return m_bHP_30; }

	void			Set_HP90(_bool _bHP80) { m_bHP_90 = _bHP80; }
	void			Set_HP60(_bool _bHP50) { m_bHP_60 = _bHP50; }
	void			Set_HP30(_bool _bHP20) { m_bHP_30 = _bHP20; }


private:

	CGameObject*			m_pBossHpUI;
	_bool					m_bStart;

	// Skill Full Down
	CSkill*					m_pFullDown;
	_bool					m_bFullDown;
	_float					m_FullDownTime;

	// Skill Bloody Thunder
	CSkill*					m_pBloodyThunder;
	_bool					m_bBloodyTunder;
	_bool					m_bBloodyLate;
	_float					m_BloodyTime;

	// Skill BlueThunder
	CSkill*					m_pBlueThunder;
	_bool					m_bBlueTunder;
	_bool					m_bBlueLate;
	_float					m_BlueTime;

	//Skill Hell Fire
	CSkill* m_pHellFire;
	_bool	m_bHellFire;
	_bool	m_bHellLate;
	_bool   m_bHellLast;
	_bool   m_bHellFin;
	_bool	m_bHellEnd;
	_float	m_HellTime;



	// Skill Create Wyvern
	CSkill*					m_pCreateWyvern;
	_bool					m_bCreatWyvernPlay;
	_bool					m_bCreatWyvernLate;
	_float					m_CreateTime;

	// Skill Near Attack 
	CSkill*					m_pNearAttack;
	_bool					m_bNearAttack;
	_bool					m_bNearAttackCheck;
	_float					m_NearAttackTime;


	// Hp state
	_bool					m_bHP_90;
	_bool					m_bHP_60;
	_bool					m_bHP_30;


	_float					m_DeadCreatTime;

	_float					m_fFullDownDamage;
	_float					m_fSoundCount;




protected:
	virtual void		Free() override;




};

