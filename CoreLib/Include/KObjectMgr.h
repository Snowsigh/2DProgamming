#pragma once
#include "KObject2D.h"
using CollisionFunction = std::function<void(KBaseObject*, DWORD)>;
using SelectFunction = std::function<void(KBaseObject*, DWORD)>;

class KObjectMgr : public KSingleton<KObjectMgr>
{
private:
	int			m_iExcueteCollisionID;
	int			m_iExcueteSelectID;
	std::map<int, KBaseObject*>  m_ObjectList;
	std::map<int, KBaseObject*>  m_SelectList;
public:
	friend KSingleton< KObjectMgr>;
public:
	typedef std::map<int, CollisionFunction>::iterator FuncionIterator;
	std::map<int, CollisionFunction> m_fnCollisionExecute;
	typedef std::map<int, SelectFunction>::iterator FuncionIterator;
	std::map<int, SelectFunction> m_fnSelectExecute;
public:
	void  AddCollisionExecute(KBaseObject* owner, CollisionFunction func);
	void  DeleteCollisionExecute(KBaseObject* owner);
	void  AddSelectExecute(KBaseObject* owner, CollisionFunction func);
	void  DeleteSelectExecute(KBaseObject* owner);
	bool  Init();
	bool  Frame();
	bool  Releae();
private:
	KObjectMgr()
	{
		m_iExcueteCollisionID = 0;
		m_iExcueteSelectID = 0;
	};
public:
	virtual ~KObjectMgr() {};

};

#define I_ObjectMgr KObjectMgr::Get()