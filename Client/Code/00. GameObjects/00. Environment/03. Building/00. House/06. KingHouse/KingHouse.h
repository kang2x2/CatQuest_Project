#pragma once
#include "GameObject.h"
#include "House.h"

BEGIN(Engine)

class CCollider;

END

class CKingHouse : public CHouse
{
protected:
	explicit CKingHouse(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CKingHouse(const CHouse& rhs);
	virtual ~CKingHouse();

public:
	virtual HRESULT		Ready_Object() override;
	virtual _int		Update_Object(const _float& fTimeDelta) override;
	virtual void		LateUpdate_Object() override;
	virtual void		Render_Object() override;

public:
	virtual void		Alpha_Update();
private:
	HRESULT				Add_Component();

	CTexture*	m_pTextureCom2;
	CVIBuffer*	m_pBufferCom2;

	_int		m_iTranslucent;

public:
	static				CKingHouse* Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void		Free() override;

};

