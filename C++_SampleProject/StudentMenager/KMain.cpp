#include "KLinkedList.h"
#include "KFileIO.h"
template <typename KT, typename GT>
void run(KT _DataType, GT _DataInfoType);
int main()
{
	KNode Knode;
	run(Knode, Knode.m_Student.info);

	return 0;
}
template <typename KT, typename GT>
void run<KT>(KT _DataType, GT _DataInfoType)
{
	KLinkedList<KT> m_KLinkedList;
	KFileIO<KT,GT> m_IO;
	
	{
		bool isRun = true;
		int istudenttmp = 0;
		int itmp;
		std::string STRname = "전체삭제";

		while (isRun)
		{

			if (m_KLinkedList.m_RootNode == nullptr)
			{
				//system("cls");
				std::cout << "===============학생관리프로그램===============" << std::endl;
				std::cout << "===============몇명의 학생입니까?===============" << std::endl;
				std::cin >> istudenttmp;
				if (std::cin.fail())
				{
					std::cout << "===============값이 이상합니다===============" << std::endl;
					std::cin.clear();
					std::cin.ignore(1024, '\n');

					istudenttmp = NULL;
					continue;
				}
				else
				{
					m_KLinkedList.Init(istudenttmp);
				}
			}
			std::cout << "===============어떤 작업을 원하십니까?===============" << std::endl;
			std::cout << "===============추가|1|삭제|2|출력|3|저장|4|불러오기|5|화면지우기|6|종료|7|===============" << std::endl;
			std::cin >> itmp;
			switch (itmp)
			{
			case 1:
				m_KLinkedList.AddList();
				break;
			case 2:
				std::cout << "===============삭제하실 학생명을 입력해주세요(전체삭제를 원한다면 '전체삭제'를 타이핑하십시오)===============" << std::endl;
				std::cin >> STRname;
				m_KLinkedList.Remove(STRname);
				break;
			case 3:
				m_KLinkedList.Draw();
				m_KLinkedList.Select();
				break;
			case 4:
				m_IO.fileOutput(m_KLinkedList.m_RootNode, m_KLinkedList.iTotalCount, _DataInfoType);
				break;
			case 5:

				KT* Nodetmp;
				std::cout << "===============파일을 불러옵니다===============" << std::endl;
				std::cout << "***************모든 데이터가 삭제되고 불러옵니다***************" << std::endl;
				m_KLinkedList.Remove();
				if ((Nodetmp = m_IO.fileInput(_DataInfoType)) != nullptr)
				{
					m_KLinkedList.m_RootNode = Nodetmp;
					Nodetmp = nullptr;
					m_KLinkedList.iTotalCount = m_IO.NodeCount();
					std::cout << "===============불러온 학생 정보 입니다===============" << std::endl;
					m_KLinkedList.Draw();
				}

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
}