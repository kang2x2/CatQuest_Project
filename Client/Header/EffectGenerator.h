#pragma once
#include "GameObject.h"

BEGIN(Engine)


END

class CPollen;
class CCloud1;
class CCloud2;
class CCloud3;

class CEffectGenerator : public Engine::CGameObject
{
private:
	explicit CEffectGenerator(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CEffectGenerator(const CEffectGenerator& rhs);
	virtual ~CEffectGenerator();

public:
	virtual HRESULT		Ready_Object() override;
	virtual _int		Update_Object(const _float& fTimeDelta) override;
	virtual void		LateUpdate_Object() override;
	virtual void		Render_Object() override;

public:
	void	Set_Locate(OBJ_ID _eLocation);


private:
	void	Pollen_Create(const _float& fTimeDelta);
	void	Pollen_Caculate_CreateTime();
	void	Pollen_Caculate_InitPos();

	void	Cloud_Create(const _float& fTimeDelta);
	void	Cloud_Caculate_CreateTime();
	void	Cloud_Caculate_InitPos();

	void	Snow_Create(const _float& fTimeDelta);
	void	Snow_Caculate_CreateTime();
	void	Snow_Caculate_InitPos();

	void	Rain_Create(const _float& fTimeDelta);
	void	Rain_Caculate_CreateTime();
	void	Rain_Caculate_InitPos();

private:
	CGameObject* m_pPlayer;
	_vec3		 m_vPlayerPos;

	OBJ_ID		m_ePlayerLocate;

	random_device m_Random;

	// 먼지
	list<CGameObject*>	 m_listPollen;
	_float				 m_fPollen_AccTime;
	_float				 m_fPollen_CreateTime;
	_vec3				 m_vPollen_CreatePos;

	// 구름
	list<CGameObject*>	 m_listCloud;
	_float				 m_fCloud_AccTime;
	_float				 m_fCloud_CreateTime;
	_vec3				 m_vCloud_CreatePos;
	_uint				 m_iChoice;

	// 눈
	list<CGameObject*>   m_listSnow;
	_float				 m_fSnow_AccTime;
	_float				 m_fSnow_CreateTime;
	_vec3				 m_vSnow_CreatePos;

	// 비
	list<CGameObject*>   m_listRain;
	_float				 m_fRain_AccTime;
	_float				 m_fRain_CreateTime;
	_vec3				 m_vRain_CreatePos;


public:
	static CEffectGenerator* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void		Free() override;
};

