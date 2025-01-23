#pragma once

/*

    반경 내 충돌을 감지하는 오브젝트
    
    충돌시 이 객체를 가지고 있는 주인에게 콜리전 메시지를 발생시킨다.
    
    플레이어나 몬스터의 스킬 공격 반경, 몬스터의 추격 반경등으로 사용하면된다.
    
    플레이어나 몬스터는 이 객체를 멤버변수로 가지고, 자신들의 Ready에서 직접 생성해주고 매니지먼트에게 보내주면 된다.
    
    사용할 일이 많지 않다면 사용 시점에 Set_Active()함수로 켜주고, 종료할 때 꺼주는 것도 좋은 방법이다.

*/

#include "GameObject.h"

BEGIN(Engine)

END

class CRangeObj : public Engine::CGameObject
{
private:
    explicit CRangeObj(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject, const _float& _fRadius);
    explicit CRangeObj(const CRangeObj& rhs);
    virtual ~CRangeObj();


public:
    virtual HRESULT		Ready_Object() override;
    virtual _int		Update_Object(const _float& fTimeDelta) override;
    virtual void		LateUpdate_Object() override;
    virtual void		Render_Object() override;


public:
    virtual void		OnCollision_Enter(CGameObject* _pColObj);
    virtual void		OnCollision_Stay(CGameObject* _pColObj);
    virtual void		OnCollision_Exit(CGameObject* _pColObj);

    CGameObject*        Get_OwnerObj() const { return m_pOwnerObject; }

public:
    void                Set_Radius(const _float& _fRadius);
    const _float&       Get_Radius() const { return m_fRadius; }
    void                Set_Pos(const _vec3 _vPos) { m_vPos = _vPos; m_bSetPos = true; }

private:
    HRESULT				Add_Component();

private:
    CGameObject*        m_pOwnerObject;
    _float              m_fRadius;

    _vec3               m_vPos; // 직접 넣기도 가능 
    _bool               m_bSetPos;

public:
    static              CRangeObj* Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject, const _float& _fRadius);

private:
    virtual void		Free() override;
};

