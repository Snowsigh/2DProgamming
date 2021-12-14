#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <list>
#include <map>
#include <Windows.h>
#include <fstream>
#include <string.h>

struct KStudent
{
public:
	std::string STRname;
	std::string STRaddress;
	std::string STRnumber;
	int iSubJect = 0;
	std::multimap<std::string, int > mapSubject;
	std::string STRtmp;
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
	~KNode()
	{
		if (m_KTail != nullptr)
			delete m_KTail; m_KTail = nullptr;
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

