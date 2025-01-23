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
	HRESULT						Set_ImgPath(); // �� �� ������Ʈ �̹��� ��� �¾�
	LPDIRECT3DTEXTURE9			LoadImageFile(const char* filePath); 
	string						wstring_to_utf8(const std::wstring& str); 

private: /* Object Picking Event */
	HRESULT						Clone_Object(const _vec3 _vPickPos); // �� Ŭ�� ������Ʈ Ŭ��
	CGameObject*				Clone(const OBJ_ID& _eID); // �������� Ŭ�� ����
	HRESULT						Delete_Object(const _vec3 _vPickPos); // �� Ŭ�� ������Ʈ ����

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
	void						Set_UnActive_Origin(); // �ʱ� ������ ��� ��Ȱ��ȭ ���·� ��ȯ -> Ŭ���� ���� �����տ� �Ұ�

private:
	LPDIRECT3DDEVICE9			m_pGraphicDev;
	
private:
	virtual void				Free();
};


