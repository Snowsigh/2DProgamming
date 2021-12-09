#include "KLinkedList.h"

int main()
{
	KLinkedList m_KLinkedList;
	m_KLinkedList.Init(2);
	m_KLinkedList.Draw();
	m_KLinkedList.Remove("전체삭제");
	return 0;
}