#include "SoundMgr.h"
#include "Export_Function.h"

/* ---------------------------- 수정시 반드시 팀장 보고 ---------------------------- */

IMPLEMENT_SINGLETON(CSoundMgr)

CSoundMgr::CSoundMgr()
{
	m_pSystem = nullptr; 

	m_bPlayingBGM = FALSE;
	m_bChangeBGM = FALSE;

	m_eCurBgmType = BGM_TYPE::NONE;

	ZeroMemory(&m_LerpCurBgmVolume, sizeof(LERP_FLOAT_INFO));
	ZeroMemory(&m_LerpPrevBgmVolume, sizeof(LERP_FLOAT_INFO));
}

CSoundMgr::~CSoundMgr()
{
	Release(); 
}

void CSoundMgr::Initialize()
{
	FMOD_System_Create(&m_pSystem);
	
	FMOD_System_Init(m_pSystem, 32, FMOD_INIT_NORMAL, NULL);

	LoadSoundFile(); 
}

void CSoundMgr::Update(const _float& fTimeDelta)
{
	if (m_bPlayingBGM && m_LerpPrevBgmVolume.bActive)
	{
		m_LerpPrevBgmVolume.Update_Lerp(fTimeDelta);

		FMOD_Channel_SetVolume(m_pChannelArr[(_uint)CHANNEL_ID::BGM_PREV], m_LerpPrevBgmVolume.fCurValue);

		if (m_bChangeBGM && !m_LerpPrevBgmVolume.bActive && 0.f == m_LerpPrevBgmVolume.fCurValue) 
			StopSound(CHANNEL_ID::BGM_PREV);
	}

	if (m_bPlayingBGM && m_LerpCurBgmVolume.bActive)
	{
		m_LerpCurBgmVolume.Update_Lerp(fTimeDelta);

		FMOD_Channel_SetVolume(m_pChannelArr[(_uint)CHANNEL_ID::BGM_CUR], m_LerpCurBgmVolume.fCurValue);

		if (m_bChangeBGM && !m_LerpCurBgmVolume.bActive && 0.f == m_LerpCurBgmVolume.fCurValue) 
			StopSound(CHANNEL_ID::BGM_CUR);
	}
}
void CSoundMgr::Release()
{
	for (auto& Mypair : m_mapSound)
	{
		delete[] Mypair.first;
		FMOD_Sound_Release(Mypair.second);
	}
	m_mapSound.clear(); 

	FMOD_System_Release(m_pSystem);
	FMOD_System_Close(m_pSystem);
}

void CSoundMgr::PlaySound(TCHAR * pSoundKey, CHANNEL_ID eID, float fVolume)
{
	StopSound(eID);

	map<TCHAR*, FMOD_SOUND*>::iterator iter; 

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), 
		[&](auto& iter)->bool 
	{
		return !lstrcmp(pSoundKey, iter.first);
	});
	
	if (iter == m_mapSound.end())
		return;

	FMOD_BOOL bPlay = FALSE; 

	if (FMOD_Channel_IsPlaying(m_pChannelArr[(_uint)eID], &bPlay))
	{
		FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, iter->second, FALSE, &m_pChannelArr[(_uint)eID]);
	}

	FMOD_Channel_SetVolume(m_pChannelArr[(_uint)eID], fVolume);

	FMOD_System_Update(m_pSystem);
}

HRESULT CSoundMgr::PlayBGM(TCHAR * pSoundKey, const BGM_TYPE& _eType)
{
	m_eCurBgmType = _eType;

	if (!m_bPlayingBGM) // 최초 브금 (월드 입장)
	{
		m_bPlayingBGM = TRUE;
		m_LerpCurBgmVolume.Init_Lerp(LERP_MODE::EASE_OUT);
		m_LerpCurBgmVolume.Set_Lerp(4.f, 0.f, SOUND_VOLUME_BGM);
	}

	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), [&](auto& iter)->bool
	{
		return !lstrcmp(pSoundKey, iter.first);
	});
	
	if (iter == m_mapSound.end())
		return E_FAIL;

	FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, iter->second, FALSE, &m_pChannelArr[(_uint)CHANNEL_ID::BGM_CUR]);
	FMOD_Channel_SetMode(m_pChannelArr[(_uint)CHANNEL_ID::BGM_CUR], FMOD_LOOP_NORMAL);
	FMOD_Channel_SetVolume(m_pChannelArr[(_uint)CHANNEL_ID::BGM_CUR], m_LerpCurBgmVolume.fCurValue);
	FMOD_System_Update(m_pSystem);
	
	return S_OK;
}

HRESULT CSoundMgr::ChangeBGM(TCHAR* pSoundKey, const BGM_TYPE& _eType)
{
	if (_eType == m_eCurBgmType) return E_FAIL;

	m_eCurBgmType = _eType;

	m_LerpPrevBgmVolume = m_LerpCurBgmVolume;
	m_pChannelArr[(_uint)CHANNEL_ID::BGM_PREV] = m_pChannelArr[(_uint)CHANNEL_ID::BGM_CUR];

	m_LerpPrevBgmVolume.Init_Lerp(LERP_MODE::EASE_OUT);
	m_LerpPrevBgmVolume.Set_Lerp(1.5f, SOUND_VOLUME_BGM, 0.f);

	m_LerpCurBgmVolume.Init_Lerp(LERP_MODE::EASE_OUT);
	m_LerpCurBgmVolume.Set_Lerp(2.f, 0.f, SOUND_VOLUME_BGM);
	
	PlayBGM(pSoundKey, _eType);

	m_bChangeBGM = TRUE;

	return S_OK;
}

void CSoundMgr::StopSound(CHANNEL_ID eID)
{
	FMOD_Channel_Stop(m_pChannelArr[(_uint)eID]);
}

void CSoundMgr::StopAll()
{
	for (int i = 0 ; i < (_uint)CHANNEL_ID::TYPEEND; ++i)
		FMOD_Channel_Stop(m_pChannelArr[i]);
}

void CSoundMgr::SetChannelVolume(CHANNEL_ID eID, float fVolume)
{
	FMOD_Channel_SetVolume(m_pChannelArr[(_uint)eID], fVolume);

	FMOD_System_Update(m_pSystem);
}

void CSoundMgr::Lerp_Volume_CurBGM(const LERP_MODE& _eMode, const _float& _fTime, const _float& _fStartVolume, const _float& _fEndVolume)
{
	m_LerpCurBgmVolume.Init_Lerp(_eMode);
	m_LerpCurBgmVolume.Set_Lerp(_fTime, _fStartVolume, _fEndVolume);

	m_bChangeBGM = FALSE; 
}

void CSoundMgr::LoadSoundFile()
{
	_finddata_t fd; 

	long long handle = _findfirst("../../Client/Bin/Resource/Sound/*.*", &fd); // 64bit니까 long lone이나 intptr_t으로 사용 (32bit는 long 사용 가능)

	if (handle == -1)
		return; 

	int iResult = 0; 

	char szCurPath[128] = "../../Client/Bin/Resource/Sound/";
	char szFullPath[128] = ""; 

	while (iResult != -1)
	{
		strcpy_s(szFullPath, szCurPath); 
		strcat_s(szFullPath, fd.name);

		FMOD_SOUND* pSound = nullptr; 
		FMOD_RESULT eRes = FMOD_System_CreateSound(m_pSystem, szFullPath, FMOD_HARDWARE, 0, &pSound);

		if (eRes == FMOD_OK)
		{
			int iLength = strlen(fd.name) + 1; 

			TCHAR* pSoundKey = new TCHAR[iLength];
			ZeroMemory(pSoundKey, sizeof(TCHAR) * iLength);

			MultiByteToWideChar(CP_ACP, 0, fd.name, iLength, pSoundKey, iLength);

			m_mapSound.emplace(pSoundKey, pSound);
		}

		iResult = _findnext(handle, &fd);
	}

	FMOD_System_Update(m_pSystem);

	_findclose(handle);
}

void CSoundMgr::Free()
{
}
