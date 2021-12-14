#include "KFileIO.h"

KNode* KFileIO::fileInput()
{
	KNode* m_tmpRootNode = new KNode;

	FILE* fp;

	KNode* tmp = m_tmpRootNode;




	fopen_s(&fp, "StudentData.txt", "rb");

	if (fp == NULL)
	{
		std::cout << "===============������ �ҷ��ü� �����ϴ�===============" << std::endl;
		fclose(fp);

		return nullptr;
	}

	fread(&iCount, sizeof(int), 1, fp);

	

	for (int iNode = 0; iNode < iCount; iNode++)
	{
		tmp->m_KTail = new KNode;
		int itmp;

		fread(&tmp->m_KTail->m_Student.info, sizeof(KInfo), 1, fp);
		fread(&tmp->m_KTail->m_Student.iSubJect, sizeof(int), 1, fp);



		for (int iSub = 0; iSub < tmp->m_KTail->m_Student.iSubJect; iSub++)
		{


			fread(&tmp->m_KTail->m_Student.STRtmp, sizeof(std::string), 1, fp); //�����ذ�Ϸ� : ��������, Ŭ���������� �޾ƿð�� ������ �ּҰ��� �Ҿ�����鼭 ������ ���� ����
			fread(&itmp, sizeof(int), 1, fp);

			tmp->m_KTail->m_Student.mapSubject.insert(std::make_pair(tmp->m_KTail->m_Student.STRtmp, itmp));
		}

		tmp = tmp->m_KTail;


	}


	fclose(fp);

	tmp->m_KTail = m_tmpRootNode;
	return m_tmpRootNode;


	
}
void KFileIO::fileOutput(const KNode* _Node,const int _ivalue)
{
	KNode* tmp = _Node->m_KTail;
	FILE* fp;


	std::cout << "===============������ ���� ����ϴ�===============" << std::endl;

	fopen_s(&fp, "StudentData.txt", "wb");




	fwrite(&_ivalue, sizeof(int), 1, fp);

	for (int iNode = 0; iNode < _ivalue; iNode++)
	{

		fwrite(&tmp->m_Student.info, sizeof(KInfo), 1, fp);
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


	std::cout << "===============������ �����Ͽ����ϴ�===============" << std::endl;


}

int KFileIO::NodeCount()
{
	return iCount;
}