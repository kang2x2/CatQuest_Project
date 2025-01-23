#pragma once
#include "GameObject.h"
#include "Monster.h"

BEGIN(Engine)

class CCubeCol;
class CCollider;

END

class CTurretSkull : public CMonster
{
protected:

	explicit CTurretSkull(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CTurretSkull(const CMonster& rhs);
	virtual ~CTurretSkull();


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

private:
	CTexture*			m_pTextureCom;

	CGameObject*		m_pPlayer;

	_float				m_fLength;
	_vec3				m_vDir;
	_uint				m_iDirZ;

	random_device		m_Random;

	LERP_FLOAT_INFO		m_tPosY;
	_float				m_fHigh;
	_float				m_fLow;

	_bool				m_bAttack;


public:
	static				CTurretSkull* Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void		Free() override;




};


