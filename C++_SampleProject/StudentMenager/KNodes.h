#pragma once
#include "KStudent.h"


class KNode
{
public:
	KStudent m_Student;
	KNode* m_KTail;

	KNode()
	{
		m_KTail = nullptr;
	}

private:

};