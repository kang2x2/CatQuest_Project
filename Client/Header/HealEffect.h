#pragma once
#include "Effect.h"

BEGIN(Engine)

class CTexture;
class CAnimation;

END

#define	SPARKLE_COUNT 4

struct tagHealSparkle1
{
	CTexture* m_pSparkle1_TexCom;
	CTransform* m_pSparkle1_TransCom;
	LERP_FLOAT_INFO m_tPosLerpX;
	LERP_FLOAT_INFO m_tPosLerpY;
	LERP_FLOAT_INFO m_tSizeUpLerp;
	LERP_FLOAT_INFO m_tSizeDownLerp;
};

struct tagHealSparkle2
{
	CTexture* m_pSparkle2_TexCom;
	CTransform* m_pSparkle2_TransCom;
	LERP_FLOAT_INFO m_tSizeUpLerp;
	LERP_FLOAT_INFO m_tSizeDownLerp;
};

class CHealEffect : public CEffect
{
	explicit CHealEffect(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);
	explicit CHealEffect(const CHealEffect& rhs);
	virtual ~CHealEffect();

public:
	virtual HRESULT				Ready_Object() override;
	virtual _int				Update_Object(const _float& fTimeDelta) override;
	virtual void				LateUpdate_Object() override;
	virtual void				Render_Object() override;

	void						Ready_Lerp();
	void						Sparkle2_Update(const _float& fTimeDelta);

public:
	_bool&						Is_Heal() { return m_bHeal; }

private:
	HRESULT						Add_Component();
	virtual void				Play_Effect(const _vec3& _vPos, const _vec3& _vSize = vec3.one) override;

private:
	// 낙하
	CTexture*		m_pDropTexCom;
	CTransform*		m_pDropTransCom;
	LERP_FLOAT_INFO m_tDropLerp;
	_bool			m_bActiveDrop;

	// 파우더
	CTexture*		m_pPawTexCom;
	CTransform*		m_pPawTransCom;
	LERP_FLOAT_INFO m_tPawSizeLerp;
	LERP_FLOAT_INFO m_tPawTlLerp;
	_int			m_iPawTranslucent;

	// 스파클1
	tagHealSparkle1 m_vecSparkle1[SPARKLE_COUNT];
	// 스파클2
	tagHealSparkle2 m_vecSparkle2[SPARKLE_COUNT];

	_int		m_iEffectLevel;
	_int		m_iSparkleCount; // 다음 단계로 넘어가기 위함.
	_int		m_iSparkle2Level; // 스파클2만을 위한 레벨

	_bool		m_bHeal;

public:
	static CHealEffect* Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);

private:
	virtual void				Free() override;
};

