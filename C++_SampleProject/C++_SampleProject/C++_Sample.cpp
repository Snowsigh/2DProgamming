#include <iostream>

int main()
{
	FILE* fp;
	fopen_s(&fp, "Text.txt", "w");
	char szData[] = "KKO";
	fprintf(fp, szData);
	fclose(fp);

	FILE* fpRead;
	fopen_s(&fpRead, "Text.txt", "r");
	char rzData[10];
	fscanf_s(fpRead,"%s ", rzData, sizeof(fpRead));
	fclose(fpRead);

	printf("%s\n", rzData);
	return 0;
}