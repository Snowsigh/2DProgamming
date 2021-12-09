#include "KLinkedList.h"
void KLinkedList::Init(int ivalue)
{
	m_RootNode = new KNode;
	
	for (int iNode = 0; iNode < ivalue; iNode++)
	{
		std::string STRsupject;
		int iPoint;
		std::cin >> STRsupject >> iPoint;
		AddList(STRsupject, iPoint);
	}
}
void KLinkedList::AddList(std::string _STR, int _int)
{
	if (m_RootNode->m_KTail == nullptr)
	{
		KNode* m_kNode = new KNode;
		m_kNode->m_Student.MAPsexual.insert(make_pair(_STR, _int));
		m_kNode->m_KTail = m_RootNode;
		m_RootNode->m_KTail = m_kNode;
	}
	else
	{
		KNode* m_LastTail =	m_RootNode->m_KTail;
		while (m_LastTail->m_KTail != m_RootNode)
		m_LastTail = m_LastTail->m_KTail;

		KNode* m_kNode = new KNode;
		m_kNode->m_Student.MAPsexual.insert(make_pair(_STR, _int));
		m_LastTail->m_KTail = m_kNode;
		m_kNode->m_KTail = m_RootNode;
	}
	iTotalCount++;
}
void KLinkedList::Remove(std::string NameValue)
{
	if (NameValue == "전체삭제")
	{
		while (m_RootNode->m_KTail != m_RootNode)
		{
			KNode* tmp;
			KNode* ftmp;
			tmp = m_RootNode;
			ftmp = m_RootNode;

			while (tmp->m_KTail != m_RootNode)
			{
				ftmp = tmp;
				tmp = tmp->m_KTail;
			}
			ftmp->m_KTail = m_RootNode;
			delete tmp;
			iTotalCount--;
		}
		delete m_RootNode;
		iTotalCount--;
	}
	else
	{
		if (m_RootNode->m_Student.STRname == NameValue)
		{
			KNode* tmp;
			tmp = m_RootNode->m_KTail;

			while (tmp->m_KTail != m_RootNode)
				tmp = tmp->m_KTail;
			tmp->m_KTail = m_RootNode->m_KTail;

			delete m_RootNode;
			iTotalCount--;
		}

		KNode* tmp = nullptr;
		KNode* ftmp = nullptr;
		tmp = m_RootNode->m_KTail;
		ftmp = tmp;
		while (tmp->m_Student.STRname != NameValue)
		{
			ftmp = tmp;
			tmp = tmp->m_KTail;

		}
		ftmp->m_KTail = tmp->m_KTail;
		delete tmp;
		iTotalCount--;

	}

}
void KLinkedList::Draw()
{
	KNode* tmp;
	tmp = m_RootNode->m_KTail;
	for (int iNode = 0; iNode < iTotalCount; iNode++)
	{
		std::cout << tmp->m_Student.STRname << "  " << tmp->m_Student.STRnumber << "  " << tmp->m_Student.STRaddress << "  " << "과학  " << tmp->m_Student.MAPsexual.at("과학") << "\n";
		tmp = tmp->m_KTail;
	}
	
	
}