#pragma once
#include "GameObject.h"
#include "Monster.h"

BEGIN(Engine)

class CCubeCol;
class CCollider;

END

class CBat : public CMonster
{
protected:

	explicit CBat(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CBat(const CMonster& rhs);
	virtual ~CBat();


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

	//잔상용 리스트
	list<CGameObject*>			m_listAfterImg;
	_uint						m_iCreateAfterImg;



public:
	static				CBat* Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void		Free() override;




};

