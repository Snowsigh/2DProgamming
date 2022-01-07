#include "KProtocol.h"
#include <string>

// data << header << index << name << damage << mesage;
// data >> header >> index >> name >> damage >> mesage;

class KPacket
{
public:
	char* m_pOffset;
	char* c_str() { return m_pOffset; }
	UPACKET m_uPacket;
	void PutData(const char* pData, int iSize);
	void GetData(const char* pData, int iSize);
public:
	KPacket& operator << (int data);
	KPacket& operator << (long data);
	KPacket& operator << (short data);
	KPacket& operator << (float data);
	KPacket& operator << (char* data);
	KPacket& operator << (std::string data);
public:
	KPacket& operator >> (int& data);
	KPacket& operator >> (long& data);
	KPacket& operator >> (short& data);
	KPacket& operator >> (float& data);
	KPacket& operator >> (char* data);
	KPacket& operator >> (std::string& data);
public:
	KPacket();
	KPacket(WORD iType);
	KPacket(const KPacket& packet);

private:

};