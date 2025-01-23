
#pragma once

#include "LineObject.h"

BEGIN(Engine)

class CGameObject;
class CLineObject;

class CCollider;
class CCircleCollider;
class CRectCollider;
class CSphereCollider;

union COLLIDER_ID
{
	struct
	{
		_uint iLeft_id;
		_uint iRight_id;
	};
	_ulonglong ID;
};

class ENGINE_DLL CCollisionMgr : public CBase
{
	DECLARE_SINGLETON(CCollisionMgr)

public:
	explicit CCollisionMgr();
	virtual ~CCollisionMgr();

public:
	void							Check_Collision(const OBJ_TYPE& _eType1, 
													const OBJ_TYPE& _eType2,
													const OBJ_TYPE& _eParentType = OBJ_TYPE::TYPEEND, // _eType2이 Range일 경우, 부모 타입
													const COL_TYPE& _eColType1 = COL_TYPE::RECT, 
													const COL_TYPE& _eColType2 = COL_TYPE::RECT);

	void							Check_Line_Collision(const OBJ_TYPE& _eType); 

	HRESULT							Add_Line(CLineObject* const _pObj) { NULL_CHECK_RETURN(_pObj, E_FAIL);
																			m_vecLine.push_back(_pObj); return S_OK; }

private:
	const _bool						Check_Rect(CGameObject* const _pObj1, CGameObject* const _pObj2);
	const _bool						Check_Rect_Circle(CGameObject* const _pObj1, CGameObject* const _pObj2);
	const _bool						Check_Line_Rect(CGameObject* const _pObj1, CLineObject* const _pObj2);
	const _int						Check_CCW(const _vec3& _vLineStart, const _vec3& _vLineEnd, const _vec3& _vPT);
	const _vec3&					Get_LineCollision_Data(const _vec3& vDir, _vec3* _vRectPtList, _vec3* _vLinePtList);

	const _bool						Check_Range(CGameObject* const _pObj, CGameObject* const _pRange); // 오브젝트 vs 반경

private:
	void							Set_Info(map<_ulonglong, _bool>::iterator& _iter, CCollider* _pCol1, CCollider* _pCol2);

private:
	map<_ulonglong, _bool>			m_mapColInfo;		// 충돌체간 이전 프레임 충돌 정보
	
	vector<CLineObject*>			m_vecLine;			// 모든 라인을 가지고 있다.

private:
	virtual void					Free();
};

END
