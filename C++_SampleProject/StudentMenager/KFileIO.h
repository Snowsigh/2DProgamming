#pragma once
#include "KNodes.h"
template <typename K, typename G>
class KFileIO
{
public:
	int iCount = 0;
public:
	K* fileInput(G _NodeInfoData);
	void fileOutput(const K* _Node, const int _ivalue, G _NodeInfoData);
public:
	int NodeCount();
};

template <typename K, typename G>
K* KFileIO<K,G>::fileInput(G _NodeInfoData)
{
	K* m_tmpRootNode = new K;

	FILE* fp;

	K* tmp = m_tmpRootNode;




	fopen_s(&fp, "StudentData.txt", "rb");

	if (fp == NULL)
	{
		std::cout << "===============파일을 불러올수 없습니다===============" << std::endl;
		fclose(fp);

		return nullptr;
	}

	fread(&iCount, sizeof(int), 1, fp);



	for (int iNode = 0; iNode < iCount; iNode++)
	{
		tmp->m_KTail = new K;
		int itmp;

		fread(&tmp->m_KTail->m_Student.info, sizeof(G), 1, fp);
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

	tmp->m_KTail = m_tmpRootNode;
	return m_tmpRootNode;



}
template <typename K, typename G>
void KFileIO<K,G>::fileOutput(const K* _Node, const int _ivalue, G _NodeInfoData)
{
	K* tmp = _Node->m_KTail;
	FILE* fp;


	std::cout << "===============파일을 새로 만듭니다===============" << std::endl;

	fopen_s(&fp, "StudentData.txt", "wb");




	fwrite(&_ivalue, sizeof(int), 1, fp);

	for (int iNode = 0; iNode < _ivalue; iNode++)
	{

		fwrite(&tmp->m_Student.info, sizeof(G), 1, fp);
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
template <typename K, typename G>
int KFileIO<K,G>::NodeCount()
{
	return iCount;
}

