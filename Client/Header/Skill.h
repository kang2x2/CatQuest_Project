#pragma once

#include "Engine_Define.h"
#include "GameObject.h"
#include "SoundMgr.h"
#include "Effect_Range_Quater.h"
#include "SkillEffect.h"

/*

	* 해당 클래스를 상속 받아 각 스킬을 구현하도록 한다.
	
	* CSkillEffect
	* CEffect_Range_Quater
	* CCollier
	* CTransform
	

	- 플레이어 / 몬스터
		- 스킬 벡터
			- 스킬 1
				- 스킬 이펙트
				- 장판 이펙트
				- 콜라이더
			- 스킬 2
				- 스킬 이펙트
				- 장판 이펙트
				- 콜라이더
	구조

	1. 플레이어 또는 몬스터는 자신이 사용할 스킬을 멤버변수로 갖는다(이 클래스 타입) -> 여러 스킬 사용시 컨테이너 사용

	2. 스킬은 이 클래스를 상속받아 개별 스킬 클래스를 구현한다.

		- 하나의 스킬은 CSkillEffect / CEffect_Range_Quater / CCollier / CTransform의 변수를 갖는다(CEffect_Range_Quater는 선택)

		- 스킬 사용시, CSkillEffect와 CEffect_Range_Quater의 사용 함수를 호출하도록 한다.

*/

class CSkillEffect;
class CEffect_Range_Quater;
class CRangeObj;

class CSkill : public CGameObject
{
protected:
	explicit CSkill(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID);
	explicit CSkill(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject, const OBJ_ID& _eID);
	explicit CSkill(const CSkill& rhs);
	virtual ~CSkill();

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
	virtual HRESULT			End();

	void					Set_SkillPlay(const _float& bPlay)		{ m_bPlay = bPlay; }
	const _bool				Is_End() const { return m_bPlay; }; // 스킬 시전이 끝났는지

	CGameObject*			Get_SkillOwner() { return m_pOwnerObject; }

	void					Set_SkillDamage(const _float& pDamage)  { m_fSkillDamage = pDamage; }
	void					Set_SkillUsage(const _uint& pUsage)	{ m_iSkillUsage = pUsage; }

	const _float&			Get_SkillDamage() const { return m_fSkillDamage; }
	const _uint&			Get_SkillUsage()  const { return m_iSkillUsage; }

	// 성혁 추가
	const D3DCOLOR& Get_SkillFontColor() const { return m_fontColor; }
	const wstring&  Get_SkillContent()   const { return m_contentStr; }

	_int			Get_SkillLv() { return m_iLv; }
	void			Skill_LvUp(_int _PlusLv) { m_iLv += _PlusLv; }

protected:
	CGameObject*			m_pOwnerObject;
	_bool					m_bPlay;

	CSkillEffect*			m_pSKillEffect; // 빔이나 불 같은 스킬
	CEffect_Range_Quater*	m_pRangeEffect; // 스킬 아래 깔리는 장판
	
	CGameObject*			m_pRangeObj;

	_float					m_fSkillDamage;
	_uint					m_iSkillUsage;

	_bool					m_bAttackStart;

	// 성혁 추가
	D3DCOLOR				m_fontColor;
	wstring					m_contentStr;
	_int					m_iLv;


protected:
	virtual void			Free();
};

