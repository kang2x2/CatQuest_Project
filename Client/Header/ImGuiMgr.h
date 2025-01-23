#pragma once

#include "Engine_Define.h"
#include "Base.h"

BEGIN(Engine)

class CLayer;
class CGameObject;
END

class CImGuiMgr : public CBase
{
	DECLARE_SINGLETON(CImGuiMgr)

private:
	explicit CImGuiMgr();
	virtual ~CImGuiMgr();

	
public: /* Life Cycle */
	HRESULT						ImGui_SetUp(LPDIRECT3DDEVICE9 pGraphicDev); 
	HRESULT						ImGui_SetDevice(LPDIRECT3DDEVICE9 pGraphicDev);
	void						ImGui_Update();
	void						ImGui_Render();

	void						Show_Header_Scene();
	void						Show_Header_Object();
	void						Show_Header_Light();

private: /* Img Path */
	HRESULT						Set_ImgPath(); // 맵 및 오브젝트 이미지 경로 셋업
	LPDIRECT3DTEXTURE9			LoadImageFile(const char* filePath); 
	string						wstring_to_utf8(const std::wstring& str); 

private: /* Object Picking Event */
	HRESULT						Clone_Object(const _vec3 _vPickPos); // 좌 클릭 오브젝트 클론
	CGameObject*				Clone(const OBJ_ID& _eID); // 실질적인 클론 수행
	HRESULT						Delete_Object(const _vec3 _vPickPos); // 우 클릭 오브젝트 삭제

private: /* File Save Load */
	HRESULT						Create_Scene();
	HRESULT						Save_Scene();   
	HRESULT						Delete_Scene();
	HRESULT						Change_Scene();

	HRESULT						Load_All_Scene(); 

public:
	HRESULT						Load_Scene(TCHAR* filePath);

private: /* Etc */
	const _vec3&				Get_ClickPos();
	void						Set_UnActive_Origin(); // 초기 프리팹 모두 비활성화 상태로 전환 -> 클론을 위한 프리팹에 불과

private:
	LPDIRECT3DDEVICE9			m_pGraphicDev;
	
private:
	virtual void				Free();
};


