#pragma once
#include <iostream>
#include <list>
#include <map>
#include <Windows.h>
struct KStudent
{
	std::string STRname;
	std::string STRaddress;
	std::string STRnumber;
	std::map <std::string, int> MAPrecord;
	int iSubJect = 0;
	
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
	void run();
	
	void Remove(std::string NameValue = "전체삭제");
	void Draw();
	void Select();

	void fileInput();
	void fileOutput();
private:
	void AddList();

public:
	KNode* m_RootNode;
	int iTotalCount = 0;
	KLinkedList()
	{
		m_RootNode = nullptr;
	}

private:

};

