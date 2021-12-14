#include "KLinkedList.h"
void KLinkedList::run()
{
	bool isRun = true;
	int istudenttmp = 0;
	int itmp;
	std::string STRname = "전체삭제";

	while (isRun)
	{
		
		if (m_RootNode == nullptr)
		{
			//system("cls");
			std::cout << "===============학생관리프로그램===============" << std::endl;
			std::cout << "===============몇명의 학생입니까?===============" << std::endl;
			std::cin >> istudenttmp;
			if(std::cin.fail())
			{
				std::cout << "===============값이 이상합니다===============" << std::endl;
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
		std::cout << "===============어떤 작업을 원하십니까?===============" << std::endl;
		std::cout << "===============추가|1|삭제|2|출력|3|저장|4|불러오기|5|화면지우기|6|종료|7|===============" << std::endl;
		std::cin >> itmp;
		switch (itmp)
		{
		case 1:
			AddList();
			break;
		case 2:
			std::cout << "===============삭제하실 학생명을 입력해주세요(전체삭제를 원한다면 '전체삭제'를 타이핑하십시오)===============" << std::endl;
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
			std::cout << "\n===============학생정보를 등록하겠습니다===============" << std::endl;
			std::string STRname;
			std::string STRadd;
			std::string STRnum;
			std::cout << "학생의 이름을 적어주세요  " << std::endl;
			std::cin >> STRname;
			std::cout << "학생의 주소를 적어주세요  " << std::endl;
			std::cin >> STRadd;
			std::cout << "학생의 핸드폰번호를 적어주세요  " << std::endl;
			std::cin >> STRnum;

			m_kNode->m_Student.STRname = STRname;
			m_kNode->m_Student.STRaddress = STRadd;
			m_kNode->m_Student.STRnumber = STRnum;
			std::cout << "===============학생정보가 등록되었습니다===============" << std::endl;

		}//학생이름추가
		{
			std::string STRsupject;
			int iPoint;
			while (true)
			{
				std::cout << "과목의 개수를 적어주세요  " << std::endl;
				std::cin >> m_kNode->m_Student.iSubJect;
				if (std::cin.fail())
				{
					std::cout << "===============값이 이상합니다===============" << std::endl;
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
				std::cout << "===============과목과 점수를 입력하여주세요===============" << std::endl;
				std::cin >> STRsupject >> iPoint;

				if (iPoint == false)
				{
					std::cout << "===============점수가 이상합니다, 0점으로 기입합니다===============" << std::endl;
					iPoint = 0;
				}

				//std::string* STRtmp = new std::string(STRsupject.c_str());
				m_kNode->m_Student.mapSubject.insert(std::make_pair(STRsupject, iPoint));
				
			}
		}//학생성적추가
		std::cout << "===============모든 정보가 등록되었습니다===============" << std::endl;
		std::cout << m_kNode->m_Student.STRname << "  " << m_kNode->m_Student.STRaddress << "  " << m_kNode->m_Student.STRnumber << std::endl;

		std::map<std::string, int>::iterator iter;
		iter = m_kNode->m_Student.mapSubject.begin();

		for (int iSub = 0; iSub < m_kNode->m_Student.iSubJect; iSub++)
		{
			std::cout  << iter->first << "  " << iter->second << std::endl;
			iter++;
		}
		std::cout << "===============해당 정보로 등록되었습니다===============" << std::endl;
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
			std::cout << "===============학생정보를 등록하겠습니다===============" << std::endl;
			std::string STRname;
			std::string STRadd;
			std::string STRnum;
			std::cout << "학생의 이름을 적어주세요  " << std::endl;
			std::cin >> STRname;
			std::cout << "학생의 주소를 적어주세요  " << std::endl;
			std::cin >> STRadd;
			std::cout << "학생의 핸드폰번호를 적어주세요  " << std::endl;
			std::cin >> STRnum;

			m_kNode->m_Student.STRname = STRname;
			m_kNode->m_Student.STRaddress = STRadd;
			m_kNode->m_Student.STRnumber = STRnum;
			std::cout << "===============학생정보가 등록되었습니다===============" << std::endl;

		}//학생이름추가
		{
			
			std::string STRsupject;
			int iPoint;
			while (true)
			{
				std::cout << "과목의 개수를 적어주세요  " << std::endl;
				std::cin >> m_kNode->m_Student.iSubJect;
				if (std::cin.fail())
				{
					std::cout << "===============값이 이상합니다===============" << std::endl;
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
				std::cout << "===============과목과 점수를 입력하여주세요===============" << std::endl;
				
				std::cin >> STRsupject >> iPoint;
				
				if (iPoint == false)
				{
					std::cout << "===============점수가 이상합니다, 0점으로 기입합니다===============" << std::endl;
					iPoint = 0;
				}

				//std::string* STRtmp = new std::string(STRsupject.c_str());
				m_kNode->m_Student.mapSubject.insert(std::make_pair(STRsupject, iPoint));

				
				
			}
		}//학생성적추가
		std::cout << "===============모든 정보가 등록되었습니다===============" << std::endl;
		std::cout << m_kNode->m_Student.STRname << "  " << m_kNode->m_Student.STRaddress << "  " << m_kNode->m_Student.STRnumber << std::endl;

		std::map<std::string, int>::iterator iter;
		iter = m_kNode->m_Student.mapSubject.begin();

		for (int iSub = 0; iSub < m_kNode->m_Student.iSubJect; iSub++)
		{
			std::cout << iter->first << "  " << iter->second << std::endl;
			iter++;
		}

		std::cout << "===============해당 정보로 등록되었습니다===============" << std::endl;
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
	if (NameValue == "전체삭제")
	{
		std::cout << "===============전체삭제 됩니다===============" << std::endl;
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
		std::cout << "==============="<< NameValue << " 학생 정보가 삭제 됩니다============== = " << std::endl;
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
				std::cout << "===============학생 정보가 없습니다============= = " << std::endl;
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
		std::cout << "==============="<< tmp->m_Student.STRname << " 학생 정보============== = " << std::endl;
		std::cout << tmp->m_Student.STRname << "  " << tmp->m_Student.STRaddress << "  " << tmp->m_Student.STRnumber << std::endl;
		

		std::map<std::string, int>::iterator iter;
		iter = tmp->m_Student.mapSubject.begin();

		for (int iSub = 0; iSub < tmp->m_Student.iSubJect; iSub++)
		{
			std::cout << iter->first << "  " << iter->second << std::endl;
			iter++;
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

	std::cout << "===============어떤 학생을 찾으십니까?===============" << std::endl;
	std::cout << "===============찾으시는 학생이 없다면 아무키나 눌러주십시오===============" << std::endl;
	std::cin >> STRtmpname;
	std::cout << std::endl;

	while (tmp->m_Student.STRname != STRtmpname)
	{
		if (tmp->m_KTail == m_RootNode)
		{
			std::cout << "===============해당하는 이름이 없습니다===============" << std::endl;
			break;
		}
		tmp = tmp->m_KTail;
	}
	if (tmp->m_Student.STRname == STRtmpname)
	{
		std::cout << "===============" << tmp->m_Student.STRname << " 학생 정보============== = " << std::endl;
		std::cout << tmp->m_Student.STRname << "  " << tmp->m_Student.STRaddress << "  " << tmp->m_Student.STRnumber << std::endl;
	

		std::map<std::string, int>::iterator iter;
		iter = tmp->m_Student.mapSubject.begin();

		for (int iSub = 0; iSub < tmp->m_Student.iSubJect; iSub++)
		{
			std::cout << iter->first << "  " << iter->second << std::endl;
			iter++;
		}

		std::string STRtmp;
		std::cout << "===============삭제하시겠습니까? Y/N===============" << std::endl;
		std::cin >> STRtmp;

		if (STRtmp == "Y" || STRtmp == "Yes" || STRtmp == "YES" || STRtmp == "yes" || STRtmp == "y")
		{
			Remove(tmp->m_Student.STRname);
			std::cout << "===============삭제되었습니다===============" << std::endl;
			std::cout << std::endl;
			system("cls");
			std::cout << "===============남은 학생 정보입니다===============" << std::endl;
			Draw();
		}
		else
		{
			std::cout << "===============3초후 화면이 정리됩니다===============" << std::endl;
			Sleep(3000);
			system("cls");
			return;
		}

	}
}
void KLinkedList::fileInput()
{
	m_RootNode = new KNode;
	std::cout << "===============파일을 불러옵니다===============" << std::endl;
	std::cout << "***************모든 데이터가 삭제되고 불러옵니다***************" << std::endl;
	Remove();

	FILE* fp;
	
	KNode* tmp = m_RootNode;

	
	

	fopen_s(&fp,"StudentData.txt", "rb");
	
	if (fp == NULL)
	{
		std::cout << "===============파일을 불러올수 없습니다===============" << std::endl;
		fclose(fp);
		
		return;
	}

	fread(&iTotalCount, sizeof(int), 1, fp);
	

	for (int iNode = 0; iNode < iTotalCount; iNode++)
	{
		tmp->m_KTail = new KNode;
		int itmp;

		fread(&tmp->m_KTail->m_Student.STRname, sizeof(std::string), 1, fp);
		fread(&tmp->m_KTail->m_Student.STRaddress, sizeof(std::string), 1, fp);
		fread(&tmp->m_KTail->m_Student.STRnumber, sizeof(std::string), 1, fp);
		fread(&tmp->m_KTail->m_Student.iSubJect, sizeof(int), 1, fp);
		


		for (int iSub = 0; iSub < tmp->m_KTail->m_Student.iSubJect; iSub++)
		{
			

			fread(&tmp->m_KTail->m_Student.STRtmp, sizeof(std::string), 1, fp); //문제해결완료 : 지역변수, 클래스변수로 받아올경우 데이터 주소값을 잃어버리면서 엑세스 위반 에러
			fread(&itmp, sizeof(int), 1, fp);

			tmp->m_KTail->m_Student.mapSubject.insert(std::make_pair(tmp->m_KTail->m_Student.STRtmp, itmp));
		}

		tmp = tmp->m_KTail;
		
		
	}


	fclose(fp);
	
	tmp->m_KTail = m_RootNode;

	

	std::cout << "===============불러온 학생 정보 입니다===============" << std::endl;
	Draw();
}
void KLinkedList::fileOutput()
{
	KNode* tmp = m_RootNode->m_KTail;
	FILE* fp;
	

	std::cout << "===============파일을 새로 만듭니다===============" << std::endl;

	fopen_s(&fp,"StudentData.txt", "wb");

	

	
	fwrite(&iTotalCount, sizeof(int), 1, fp);

	for(int iNode = 0; iNode < iTotalCount; iNode++)
	{

		fwrite(&tmp->m_Student.STRname, sizeof(std::string), 1, fp);
		fwrite(&tmp->m_Student.STRaddress, sizeof(std::string), 1, fp);
		fwrite(&tmp->m_Student.STRnumber, sizeof(std::string), 1, fp);
		fwrite(&tmp->m_Student.iSubJect, sizeof(int), 1, fp);


		std::map<std::string, int>::iterator iter;
		iter = tmp->m_Student.mapSubject.begin();
		

		for (int iSub = 0; iSub < tmp->m_Student.iSubJect; iSub++) 
		{
			fwrite(&iter->first, sizeof(std::string), 1, fp);
			fwrite(&iter->second, sizeof(int), 1, fp);

			iter++;
			
		}
		
		tmp = tmp->m_KTail;
	} 

	fclose(fp);
	

	std::cout << "===============파일을 저장하였습니다===============" << std::endl;


}