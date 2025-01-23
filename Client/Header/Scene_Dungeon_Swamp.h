#pragma once

#include "Scene.h"

class CScene_Dungeon_Swamp : public Engine::CScene
{
private:
	explicit CScene_Dungeon_Swamp(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CScene_Dungeon_Swamp();

public:
	virtual HRESULT		Ready_Scene() override;
	virtual _int		Update_Scene(const _float& fTimeDelta) override;
	virtual void		LateUpdate_Scene() override;
	virtual void		Render_Scene() override;

private:

	HRESULT				Ready_Load(); // 데이터 로드

	HRESULT				Ready_Layer_Camera(); // 클라
	HRESULT				Ready_Layer_UI(); // 클라
	HRESULT				Ready_Layer_Player(); // 클라
	HRESULT				Ready_Layer_Effect(); // 클라
	HRESULT				Ready_Layer_Etc(); // 클라

	HRESULT				Ready_Layer_Terrain(); // 레이어 생성 따로 빼두고 삭제 예정
	HRESULT				Ready_Layer_Environment(); // 레이어 생성 따로 빼두고 삭제 예정
	HRESULT				Ready_Layer_Npc(); // 레이어 생성 따로 빼두고 삭제 예정
	HRESULT				Ready_Layer_Monster();  // 레이어 생성 따로 빼두고 삭제 예정
	HRESULT				Ready_Layer_Item(); // 레이어 생성 따로 빼두고 삭제 예정

	HRESULT				Ready_Layer_KSH(); // 개인 테스트용 추가
	HRESULT				Ready_Layer_KJM(); // 개인 테스트용 추가
	HRESULT				Ready_Layer_LHJ(); // 개인 테스트용 추가
	HRESULT				Ready_Layer_YC(); // 개인 테스트용 추가

public:
	static CScene_Dungeon_Swamp* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void		Free() override;
};

