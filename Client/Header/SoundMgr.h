#pragma once

#include "Engine_Define.h"
#include "Base.h"
#include "stdafx.h"

class CSoundMgr : public CBase
{
	/* ---------------------------- 수정시 반드시 팀장 보고 ---------------------------- */

	DECLARE_SINGLETON(CSoundMgr)

private:
	CSoundMgr();
	~CSoundMgr();

public:
	void						Initialize();
	void						Update(const _float& fTimeDelta);
	void						Release(); 

public:
	void						PlaySound(TCHAR* pSoundKey, CHANNEL_ID eID, float fVolume);
	HRESULT						ChangeBGM(TCHAR* pSoundKey, const BGM_TYPE& _eType);
	void						StopAll();
	void						SetChannelVolume(CHANNEL_ID eID, float fVolume);
	HRESULT						PlayBGM(TCHAR* pSoundKey, const BGM_TYPE& _eType); 

	const BGM_TYPE&				Get_CurBgm_Type() const { return m_eCurBgmType; }

public:
	void						Lerp_Volume_CurBGM(const LERP_MODE& _eMode, const _float& _fTime, const _float& _fStartVolume, const _float& _fEndVolume);

	const _float&				Get_CurBGMVolume() const { return m_LerpCurBgmVolume.fCurValue; }

private:
	void						StopSound(CHANNEL_ID eID);
	void						LoadSoundFile(); 

private:
	map<TCHAR*, FMOD_SOUND*>	m_mapSound; 
	FMOD_CHANNEL*				m_pChannelArr[(_uint)CHANNEL_ID::TYPEEND]; 
	FMOD_SYSTEM*				m_pSystem; 

	LERP_FLOAT_INFO				m_LerpCurBgmVolume;
	LERP_FLOAT_INFO				m_LerpPrevBgmVolume;

	_bool						m_bPlayingBGM;
	_bool						m_bChangeBGM;

	BGM_TYPE					m_eCurBgmType;

private:
	virtual void				Free();
};

