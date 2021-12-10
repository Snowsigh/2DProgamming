#include "KLinkedList.h"
void KLinkedList::run()
{
	bool isRun = true;
	int istudenttmp = 0;
	int itmp;
	std::string STRname = "��ü����";

	while (isRun)
	{
		
		if (m_RootNode == nullptr)
		{
			//system("cls");
			std::cout << "===============�л��������α׷�===============" << std::endl;
			std::cout << "===============����� �л��Դϱ�?===============" << std::endl;
			std::cin >> istudenttmp;
			if(std::cin.fail())
			{
				std::cout << "===============���� �̻��մϴ�===============" << std::endl;
				std::cin.clear();
				std::cin.ignore(1024, '\n');
				
				istudenttmp = NULL;
				continue;
			}
			else
			{
				Init(istudenttmp);
			}
		}
		std::cout << "===============� �۾��� ���Ͻʴϱ�?===============" << std::endl;
		std::cout << "===============�߰�|1|����|2|���|3|����|4|�ҷ�����|5|ȭ�������|6|����|7|===============" << std::endl;
		std::cin >> itmp;
		switch (itmp)
		{
		case 1:
			AddList();
			break;
		case 2:
			std::cout << "===============�����Ͻ� �л����� �Է����ּ���(��ü������ ���Ѵٸ� '��ü����'�� Ÿ�����Ͻʽÿ�)===============" << std::endl;
			std::cin >> STRname;
			Remove(STRname);
			break;
		case 3:
			Draw();
			Select();
			break;
		case 4:
			fileOutput();
			break;
		case 5:
			fileInput();
			break;
		case 6:
			system("cls");
			break;
		case 7:
			isRun = false;
			break;
		default:
			isRun = false;
			break;
		}
		
	}
}
void KLinkedList::Init(int ivalue)
{
	m_RootNode = new KNode;
	
	for (int iNode = 0; iNode < ivalue; iNode++)
	{
		AddList();
	}
}
void KLinkedList::AddList()
{
	if (m_RootNode->m_KTail == nullptr)
	{
		KNode* m_kNode = new KNode;
		{
			std::cout << "\n===============�л������� ����ϰڽ��ϴ�===============" << std::endl;
			std::string STRname;
			std::string STRadd;
			std::string STRnum;
			std::cout << "�л��� �̸��� �����ּ���  " << std::endl;
			std::cin >> STRname;
			std::cout << "�л��� �ּҸ� �����ּ���  " << std::endl;
			std::cin >> STRadd;
			std::cout << "�л��� �ڵ�����ȣ�� �����ּ���  " << std::endl;
			std::cin >> STRnum;

			m_kNode->m_Student.STRname = STRname;
			m_kNode->m_Student.STRaddress = STRadd;
			m_kNode->m_Student.STRnumber = STRnum;
			std::cout << "===============�л������� ��ϵǾ����ϴ�===============" << std::endl;

		}//�л��̸��߰�
		{
			std::string STRsupject;
			int iPoint;
			while (true)
			{
				std::cout << "������ ������ �����ּ���  " << std::endl;
				std::cin >> m_kNode->m_Student.iSubJect;
				if (std::cin.fail())
				{
					std::cout << "===============���� �̻��մϴ�===============" << std::endl;
					std::cin.clear();
					std::cin.ignore(1024, '\n');

				}
				else
				{
					break;
				}
			}
			for (int iSub = 0; iSub < m_kNode->m_Student.iSubJect; iSub++)
			{
				std::cout << "===============����� ������ �Է��Ͽ��ּ���===============" << std::endl;
				std::cin >> STRsupject >> iPoint;
				m_kNode->m_Student.MAPrecord.insert(make_pair(STRsupject, iPoint));
			}
		}//�л������߰�
		std::cout << "===============��� ������ ��ϵǾ����ϴ�===============" << std::endl;
		std::cout << m_kNode->m_Student.STRname << "  " << m_kNode->m_Student.STRaddress << "  " << m_kNode->m_Student.STRnumber << std::endl;

		std::map<std::string, int>::iterator iter= m_kNode->m_Student.MAPrecord.begin();
		for (; iter != m_kNode->m_Student.MAPrecord.end(); iter++)
		{
			std::cout  << iter->first << "  " << iter->second << std::endl;
		}
		std::cout << "===============�ش� ������ ��ϵǾ����ϴ�===============" << std::endl;
		std::cout << std::endl;

		m_kNode->m_KTail = m_RootNode;
		m_RootNode->m_KTail = m_kNode;
	}
	else
	{
		KNode* m_LastTail =	m_RootNode->m_KTail;
		while (m_LastTail->m_KTail != m_RootNode)
		m_LastTail = m_LastTail->m_KTail;

		KNode* m_kNode = new KNode;
		{
			std::cout << "===============�л������� ����ϰڽ��ϴ�===============" << std::endl;
			std::string STRname;
			std::string STRadd;
			std::string STRnum;
			std::cout << "�л��� �̸��� �����ּ���  " << std::endl;
			std::cin >> STRname;
			std::cout << "�л��� �ּҸ� �����ּ���  " << std::endl;
			std::cin >> STRadd;
			std::cout << "�л��� �ڵ�����ȣ�� �����ּ���  " << std::endl;
			std::cin >> STRnum;

			m_kNode->m_Student.STRname = STRname;
			m_kNode->m_Student.STRaddress = STRadd;
			m_kNode->m_Student.STRnumber = STRnum;
			std::cout << "===============�л������� ��ϵǾ����ϴ�===============" << std::endl;

		}//�л��̸��߰�
		{
			
			std::string STRsupject;
			int iPoint;
			while (true)
			{
				std::cout << "������ ������ �����ּ���  " << std::endl;
				std::cin >> m_kNode->m_Student.iSubJect;
				if (std::cin.fail())
				{
					std::cout << "===============���� �̻��մϴ�===============" << std::endl;
					std::cin.clear();
					std::cin.ignore(1024, '\n');

				}
				else
				{
					break;
				}
			}
			
			for (int iSub = 0; iSub < m_kNode->m_Student.iSubJect; iSub++)
			{
				std::cout << "===============����� ������ �Է��Ͽ��ּ���===============" << std::endl;
				
				std::cin >> STRsupject >> iPoint;
				if (iPoint == false)
				{
					std::cout << "===============������ �̻��մϴ�, 0������ �����մϴ�===============" << std::endl;
					iPoint = 0;
				}
				m_kNode->m_Student.MAPrecord.insert(make_pair(STRsupject, iPoint));
			}
		}//�л������߰�
		std::cout << "===============��� ������ ��ϵǾ����ϴ�===============" << std::endl;
		std::cout << m_kNode->m_Student.STRname << "  " << m_kNode->m_Student.STRaddress << "  " << m_kNode->m_Student.STRnumber << std::endl;

		std::map<std::string, int>::iterator iter = m_kNode->m_Student.MAPrecord.begin();
		for (; iter != m_kNode->m_Student.MAPrecord.end(); iter++)
		{
			std::cout << iter->first << "  " << iter->second << std::endl;;
		}
		std::cout << "===============�ش� ������ ��ϵǾ����ϴ�===============" << std::endl;
		std::cout << std::endl;

		m_LastTail->m_KTail = m_kNode;
		m_kNode->m_KTail = m_RootNode;
	}
	iTotalCount++;
}
void KLinkedList::Remove(std::string NameValue)
{
	if (m_RootNode->m_KTail == nullptr)
	{
		return;
	}
	if (NameValue == "��ü����")
	{
		std::cout << "===============��ü���� �˴ϴ�===============" << std::endl;
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
			tmp = nullptr;
			iTotalCount--;
		}
		delete m_RootNode;
		m_RootNode = nullptr;
		iTotalCount--;
	}
	else
	{
		std::cout << "==============="<< NameValue << " �л� ������ ���� �˴ϴ�============== = " << std::endl;
		if (m_RootNode->m_Student.STRname == NameValue)
		{
			KNode* tmp;
			tmp = m_RootNode->m_KTail;

			while (tmp->m_KTail != m_RootNode)
				tmp = tmp->m_KTail;
			tmp->m_KTail = m_RootNode->m_KTail;

			delete m_RootNode;
			m_RootNode = nullptr;
			iTotalCount--;
		}

		KNode* tmp = nullptr;
		KNode* ftmp = nullptr;
		tmp = m_RootNode->m_KTail;
		ftmp = m_RootNode;
		while (tmp->m_Student.STRname != NameValue)
		{
			ftmp = tmp;
			tmp = tmp->m_KTail;
			if (tmp->m_KTail == m_RootNode)
			{
				std::cout << "===============�л� ������ �����ϴ�============= = " << std::endl;
				return;
			}
		}
		ftmp->m_KTail = tmp->m_KTail;
		delete tmp;
		tmp = nullptr;
		iTotalCount--;

	}

}
void KLinkedList::Draw()
{
	if (m_RootNode->m_KTail == nullptr)
	{
		return;
	}
	KNode* tmp;
	tmp = m_RootNode->m_KTail;
	for (int iNode = 0; iNode < iTotalCount; iNode++)
	{
		std::cout << "==============="<< tmp->m_Student.STRname << " �л� ����============== = " << std::endl;
		std::cout << tmp->m_Student.STRname << "  " << tmp->m_Student.STRaddress << "  " << tmp->m_Student.STRnumber << std::endl;
		std::map<std::string, int>::iterator iter = tmp->m_Student.MAPrecord.begin();
		for (; iter != tmp->m_Student.MAPrecord.end(); iter++)
		{
			std::cout << iter->first << "  " << iter->second << std::endl;
		}

		tmp = tmp->m_KTail;
	}
	
	
}
void KLinkedList::Select()
{
	if (m_RootNode->m_KTail == nullptr)
	{
		return;
	}
	std::string STRtmpname;
	KNode* tmp = m_RootNode->m_KTail;

	std::cout << "===============� �л��� ã���ʴϱ�?===============" << std::endl;
	std::cout << "===============ã���ô� �л��� ���ٸ� �ƹ�Ű�� �����ֽʽÿ�===============" << std::endl;
	std::cin >> STRtmpname;
	std::cout << std::endl;

	while (tmp->m_Student.STRname != STRtmpname)
	{
		if (tmp->m_KTail == m_RootNode)
		{
			std::cout << "===============�ش��ϴ� �̸��� �����ϴ�===============" << std::endl;
			break;
		}
		tmp = tmp->m_KTail;
	}
	if (tmp->m_Student.STRname == STRtmpname)
	{
		std::cout << "===============" << tmp->m_Student.STRname << " �л� ����============== = " << std::endl;
		std::cout << tmp->m_Student.STRname << "  " << tmp->m_Student.STRaddress << "  " << tmp->m_Student.STRnumber << std::endl;
		std::map<std::string, int>::iterator iter = tmp->m_Student.MAPrecord.begin();
		for (; iter != tmp->m_Student.MAPrecord.end(); iter++)
		{
			std::cout << iter->first << "  " << iter->second << std::endl;
		}

		std::string STRtmp;
		std::cout << "===============�����Ͻðڽ��ϱ�? Y/N===============" << std::endl;
		std::cin >> STRtmp;

		if (STRtmp == "Y" || STRtmp == "Yes" || STRtmp == "YES" || STRtmp == "yes" || STRtmp == "y")
		{
			Remove(tmp->m_Student.STRname);
			std::cout << "===============�����Ǿ����ϴ�===============" << std::endl;
			std::cout << std::endl;
			system("cls");
			std::cout << "===============���� �л� �����Դϴ�===============" << std::endl;
			Draw();
		}
		else
		{
			std::cout << "===============3���� ȭ���� �����˴ϴ�===============" << std::endl;
			Sleep(3000);
			system("cls");
			return;
		}

	}
}
void KLinkedList::fileInput()
{
	std::cout << "===============������ �ҷ��ɴϴ�===============" << std::endl;
	std::cout << "***************��� �����Ͱ� �����ǰ� �ҷ��ɴϴ�***************" << std::endl;
	Remove();

	FILE* fp;

	m_RootNode = new KNode;
	KNode* tmp = m_RootNode;

	

	fopen_s(&fp,"StudentData.txt", "rb");
	
	if (fp == NULL)
	{
		std::cout << "===============������ �ҷ��ü� �����ϴ�===============" << std::endl;
		return;
	}
	fread(&iTotalCount, sizeof(int), 1, fp);

	for (int iNode = 0; iNode < iTotalCount; iNode++)
	{
		tmp->m_KTail = new KNode;
		fread(tmp->m_KTail, sizeof(KNode), 1, fp);

		for (int iSub = 0; iSub < tmp->m_KTail->m_Student.iSubJect; iSub++)
		{		

			fread(&tmp->m_KTail->m_Student.MAPrecord, sizeof(std::map<std::string,int>), 1, fp); // �ҷ����� �ȵ�, �޸� ������, �������� �ٲ����

		}
		tmp = tmp->m_KTail;

	}
	fclose(fp);
	tmp->m_KTail = m_RootNode;
	std::cout << "===============�ҷ��� �л� ���� �Դϴ�===============" << std::endl;
	Draw();
	
}
void KLinkedList::fileOutput()
{
	KNode* tmp = m_RootNode->m_KTail;
	FILE* fp;
	std::cout << "===============������ ���� ����ϴ�===============" << std::endl;
	fopen_s(&fp,"StudentData.txt", "wb");

	fwrite(&iTotalCount, sizeof(int), 1, fp);

	for(int iNode = 0; iNode < iTotalCount; iNode++)
	{
		std::map<std::string, int> MAPtmp = tmp->m_Student.MAPrecord;
		tmp->m_Student.MAPrecord.clear();
		fwrite(tmp, sizeof(KNode), 1, fp);

		std::map<std::string, int>::iterator iter;
		iter = MAPtmp.begin();
		for (int iSub = 0; iSub < tmp->m_Student.iSubJect; iSub++)
		{
			fwrite(&iter, sizeof(std::map<std::string, int>), 1, fp); //������ ������ ���� �������� �ٲ����
			iter++;
		}
		
		
		tmp = tmp->m_KTail;
	} 

	fclose(fp);
	std::cout << "===============������ �����Ͽ����ϴ�===============" << std::endl;


}