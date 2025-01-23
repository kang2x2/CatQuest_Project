#ifndef Engine_Macro_h__
#define Engine_Macro_h__

#include <iostream>

namespace Engine
{
#define	VK_MAX				0xff

#define	MIN_STR				64
#define	MAX_STR				256

#define	MAX_GROUP			32

#define NPC_IDLE_FRAME      8

#define HITCOLOR_A					255
#define HITCOLOR_R					255
#define HITCOLOR_G					120
#define HITCOLOR_B					120

#define WINDFORCE					0.1

	/*--------------------- ! (점선 안의 내용) 수정이나 추가시 반드시 팀장 보고 !  ---------------------*/

#define	DF_CAMERA_SHAKE_INTENSITY	25.f
#define	DF_CAMERA_SHAKE_TIME		0.13f

#define	DF_RB_KNOCKBACK				10000.f
#define DF_RB_KNOCKUP				800.f

#define	WINCX						1280
#define	WINCY						720

// Cam Diatance
#define CAM_DISTANCE_DEFAULT		23.f
#define CAM_DISTANCE_BINGO			60.f
#define	CAM_DISTANCE_MAX			70.f
#define	CAM_DISTANCE_JUMP			17.f

// Cam FOV

#define CAM_FOV_DEFAULT				D3DXToRadian(60.f)
#define CAM_FOV_PLAYER_RANGE		D3DXToRadian(70.f) // 원거리 공격
#define CAM_FOV_PLAYER_FLIGHT		D3DXToRadian(80.f)
#define CAM_FOV_PLAYER_ATTACK		D3DXToRadian(57.f) // 근거리 공격
#define	CAM_FOV_DRAG_MAX			D3DXToRadian(90.f) // 드래그시 FOV
#define	CAM_FOV_QUEST_TAKL			D3DXToRadian(50.f)	
#define CAM_FOV_BINGO				D3DXToRadian(80.f)


#define CAM_FOV_BOSS_DELTA			D3DXToRadian(10.f)
#define CAM_FOV_BOSS_SKILL			D3DXToRadian(85.f)

//#define CAM_FOV_BOSS_DEFAULT		(CAM_FOV_DEFAULT + D3DXToRadian(CAM_FOV_BOSS_DELTA))

// Cam Height
#define CAM_HEIGHT_MAG					1.5f
#define CAM_HEIGHT_JUMP					1.5f

// VTX
#define	VTXCNTX							257
#define VTXCNTZ							257
#define VTXITV							3

// Player Pos
#define START_POS_WORLD_X				346.f //  BOSS_POS_X			//346.f
#define START_POS_WORLD_Z				120.f // (BOSS_POS_Z - 50)	//120.f
#define START_POS_DUNGEON_X				53.f 
#define START_POS_DUNGEON_Z				32.f // 204 168
#define START_POS_TEMPLE_X				156.f 
#define START_POS_TEMPLE_Z				311.f // 204 168
#define WORLD_DUNGEON_ENTERANCE_X		204.f
#define WORLD_DUNGEON_ENTERANCE_Z		168.f
#define WORLD_TEMPLE_ENTERANCE_X		630.f
#define WORLD_TEMPLE_ENTERANCE_Z		137.f

#define	MINIGAME_JUMP_RESET_POS			_vec3{ 360.f, 3.f , 280.f }

#define BOSS_POS_X						552.f
#define BOSS_POS_Z						530.f


#define	JUMP_POWER						600.f
#define	SLIP_SPEED						25.f 
#define FLIGHT_SPEED					15.f // 15.f
	
#define	DF_RB_MAXSPEED					40.f
#define DF_SLEEP_MAXDPEED				0.3f

// Terrain Size
#define	TERRAIN_SIZE_WORLD				330.f // 150 Tile * 150 Tile
#define	TERRAIN_SIZE_DUNGEON			165.f // 74 Tile * 74 Tile

//Sound (수정시 보고 필수)
#define SOUND_VOLUME_BGM				0.3f

#define SOUND_VOLUME_MON_HIT			1.f
#define SOUND_VOLUME_MON_ATTACK			0.5f
#define SOUND_VOLUME_MON_DEATH		    1.f

#define SOUND_VOLUME_MON_FLY_ATTACK     1.f
#define SOUND_VOLUME_MON_FOOT_ATTACK    1.f

#define SOUND_VOLUME_MONSKILL_FIRE      0.5f
#define SOUND_VOLUME_MONSKILL_BEAM		0.5f
#define SOUND_VOLUME_MONSKILL_ICE		0.5f
#define SOUND_VOLUME_MONSKILL_THUNDER   0.5f

#define VOLUME_PLAYER_SKILL				0.7f
#define VOLUME_PLAYER_ROLL				0.7f
#define VOLUME_PLAYER_WALK				1.f
#define VOLUME_PLAYER_HIT				0.7f
#define VOLUME_PLAYER_FLY				0.7f
#define VOLUME_PLAYER_ATTACK			1.f
#define VOLUME_PLAYER_MAGICATTACK		0.7f
#define VOLUME_PLAYER_WATER				0.8f

#define VOLUME_PLAYER_UI				0.7f
#define VOLUME_PLAYER_LEVEL				0.7f

#define VOLUME_PLAYER_GOLDPICK			1.f
#define VOLUME_PLAYER_EXPPICK			1.f

// 환경
#define ENVIRONMENT_BUSH 				1.f

// 인벤토리
#define INVETORY_BAG					1.f
#define INVETORY_ARMOR_EQUIP			1.f
#define INVETORY_SKILL_CLICK			1.f
#define INVETORY_SKILL_EQUIP			1.f
#define INVETORY_SKILL_UNEQUIP			1.f
#define INVETORY_TAB_CLICK				1.f

// Get
#define ITEM_SKILL_GET_EFFECT			0.5f

// Bingo
#define BINGO_FAIL_SOUND				1.f
#define BINGO_SUCCES_SOUND				1.f
#define BINGO_CLEAR_SOUND				1.f
#define BINGO_ALLCLEAR_SOUND			0.5f
#define BINGO_SHOW_SOUND				1.f
#define BINGO_DROP_FIST					1.f
#define BINGO_DROP_BIGFIST				1.f
#define BINGO_COL_FIST					1.f

// Cloud Size Alpha
#define OBJ_CLOUD_MAX_ALPHA 200
#define OBJ_CLOUD_MAX_ALPHA_MAG 10.f

#define OBJ_CLOUD_SHADOW_MAX_ALPHA 150
#define OBJ_CLOUD_SHADOW_MAX_ALPHA_MAG 3.f

#define OBJ_CLOUD_MAX_SIZE_MAG 2.f

	/*--------------------- ! (점선 안의 내용) 수정이나 추가시 반드시 팀장 보고 !  ---------------------*/



#define SCREEN_MSG(_message, _rc) CGraphicDev::GetInstance()->Get_Font()->\
										DrawText(NULL, _message, lstrlen(_message), &_rc,\
										DT_CENTER | DT_NOCLIP, D3DCOLOR_ARGB(150, 255, 255, 255));\
										rc.top += 20;

#define	CONSOLE_OUT_VEC3(_msg, _vPos) std::cout << _msg << "\t" << _vPos.x << "\t" << _vPos.y << "\t" << _vPos.z << std::endl;

#ifndef	MSG_BOX
#define	MSG_BOX(_message)	MessageBox(NULL, TEXT(_message), L"System Message", MB_OK)
#endif

#define	BEGIN(NAMESPACE)	namespace NAMESPACE {
#define	END					}

#define	USING(NAMESPACE)	using namespace NAMESPACE;

#ifdef	ENGINE_EXPORTS
#define ENGINE_DLL			_declspec(dllexport)
#else
#define ENGINE_DLL			_declspec(dllimport)
#endif

#define NULL_CHECK( _ptr)	\
	{if( _ptr == 0){ return;}}

#define NULL_CHECK_RETURN( _ptr, _return)	\
	{if( _ptr == 0){return _return;}}

#define NULL_CHECK_MSG( _ptr, _message )		\
	{if( _ptr == 0){MessageBox(NULL, _message, L"System Message",MB_OK);}}

#define NULL_CHECK_RETURN_MSG( _ptr, _return, _message )	\
	{if( _ptr == 0){MessageBox(NULL, _message, L"System Message",MB_OK);return _return;}}


#define FAILED_CHECK(_hr)	if( ((HRESULT)(_hr)) < 0 )	\
	{ MessageBoxW(NULL, L"Failed", L"System Error",MB_OK); return E_FAIL;}

#define FAILED_CHECK_RETURN(_hr, _return)	if( ((HRESULT)(_hr)) < 0 )		\
	{ MessageBoxW(NULL, L"Failed", L"System Error",MB_OK); return _return;}

#define FAILED_CHECK_MSG( _hr, _message)	if( ((HRESULT)(_hr)) < 0 )	\
	{ MessageBoxW(NULL, _message, L"System Message",MB_OK); return E_FAIL;}

#define FAILED_CHECK_RETURN_MSG( _hr, _return, _message)	if( ((HRESULT)(_hr)) < 0 )	\
	{ MessageBoxW(NULL, _message, L"System Message",MB_OK); return _return;}



#define NO_COPY(CLASSNAME)								\
		private:										\
		CLASSNAME(const CLASSNAME&);					\
		CLASSNAME& operator = (const CLASSNAME&);		

#define DECLARE_SINGLETON(CLASSNAME)					\
		NO_COPY(CLASSNAME)								\
		private:										\
		static CLASSNAME*	m_pInstance;				\
		public:											\
		static CLASSNAME*	GetInstance( void );		\
		static void DestroyInstance( void );			

#define IMPLEMENT_SINGLETON(CLASSNAME)					\
		CLASSNAME*	CLASSNAME::m_pInstance = NULL;		\
		CLASSNAME*	CLASSNAME::GetInstance( void )	{	\
			if(NULL == m_pInstance) {					\
				m_pInstance = new CLASSNAME;			\
			}											\
			return m_pInstance;							\
		}												\
		void CLASSNAME::DestroyInstance( void ) {		\
			if(NULL != m_pInstance)	{					\
				delete m_pInstance;						\
				m_pInstance = NULL;						\
			}											\
		}
}

#endif // Engine_Macro_h__
