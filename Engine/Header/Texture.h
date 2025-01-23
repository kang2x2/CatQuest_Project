#pragma once

#include "Component.h"

BEGIN(Engine)

class CGameObject;

class ENGINE_DLL CTexture : public CComponent
{
public:
	explicit CTexture();
	explicit CTexture(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CTexture(const CTexture& rhs, CGameObject* _pOwnerObject);
	virtual ~CTexture();

public:
	HRESULT								Ready_Texture(TEXTUREID eType, const _tchar* pPath, const _uint& iCnt);
	void								Render_Texture(const _uint& iIndex = 0);	// 정점 출력 전에, 디바이스에게 텍스처 정보를 넘겨준다.

	_uint&								Get_TexCnt() { return m_iTexCnt; }

	// 성혁 추가
	LPDIRECT3DTEXTURE9*					Get_Texture(_uint iCnt = 0)		{ return (LPDIRECT3DTEXTURE9*)&m_vecTexture[iCnt]; };
	const _tchar*						Get_TexturePath()	{ return m_vecPathForImGui[0]; }
	// 준 추가
	void								Set_Texture(LPDIRECT3DTEXTURE9 pTexture, _uint iCnt = 0) { m_vecTexture[iCnt] = pTexture; };

private:
	vector<IDirect3DBaseTexture9*>		m_vecTexture;
	vector<const _tchar*>				m_vecPathForImGui; // 성혁 추가
	_uint								m_iTexCnt;

public:
	static CTexture*					Create(LPDIRECT3DDEVICE9 pGraphicDev, TEXTUREID eType, _tchar* pPath, const _uint& iCnt = 1);
	virtual CComponent*					Clone(CGameObject* _pOwnerObject);

private:
	virtual void						Free();
};

END