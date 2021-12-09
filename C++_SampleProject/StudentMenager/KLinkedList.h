#pragma once
#include <iostream>
#include <list>
#include <map>
struct KStudent
{
	std::string STRname;
	std::string STRaddress;
	std::string STRnumber;
	std::map <std::string, int> MAPsexual;

};
class KNode
{
public:
	KStudent m_Student;
	KNode *m_KTail;

	KNode()
	{
		m_KTail = nullptr;

	}


private:

};

class KLinkedList
{
public:
	void Init(int ivalue);
	void Remove(std::string NameValue = "전체삭제");
	void Draw();
private:
	void AddList(std::string _STR, int _int);

public:
	KNode* m_RootNode;
	int iTotalCount = 0;
	KLinkedList()
	{
		m_RootNode = nullptr;
	}

private:

};

