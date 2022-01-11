#include "KPacket.h"

void KPacket::PutData(const char* pData, int iSize)
{
	m_uPacket.ph.len += iSize;
	memcpy(m_pOffset, pData, iSize); // Offset에 데이터 카피
	m_pOffset += iSize; // ? char 포인터에 int형 더하면 주소값 이동?
}

void KPacket::GetData(const char* pData, int iSize)
{
	memcpy(const_cast<char*>(pData), m_pOffset, iSize); // 받아온 데이터(Offset) pdata 카피
	m_pOffset += iSize;
}

KPacket& KPacket::operator<<(int data)
{
	PutData((char*)&data, sizeof(int));
	return *this;
	
}

KPacket& KPacket::operator<<(long data)
{
	PutData((char*)&data, sizeof(long));
	return *this;
}

KPacket& KPacket::operator<<(short data)
{
	PutData((char*)&data, sizeof(short));
	return *this;
}

KPacket& KPacket::operator<<(float data)
{
	PutData((char*)&data, sizeof(float));
	return *this;
}

KPacket& KPacket::operator<<(char* data)
{
	PutData(data, strlen(data)+1);
	return *this;
}
KPacket& KPacket::operator<<(std::string data)
{
	PutData(data.c_str(), data.size() + 1);
	return *this;
}
//PutData

KPacket& KPacket::operator>>(int& data)
{
	GetData((char*)&data, sizeof(int));
	return *this;
}

KPacket& KPacket::operator>>(long& data)
{
	GetData((char*)&data, sizeof(long));
	return *this;
}

KPacket& KPacket::operator>>(short& data)
{
	GetData((char*)&data, sizeof(short));
	return *this;
}

KPacket& KPacket::operator>>(float& data)
{
	GetData((char*)&data, sizeof(float));
	return *this;
}

KPacket& KPacket::operator>>(char* data)
{
	int iSize = strlen(m_pOffset) + 1;
	GetData(data, iSize);
	return *this;
}
KPacket& KPacket::operator>>(std::string& data)
{
	int iSize = strlen(m_pOffset) + 1;
	GetData(data.c_str(), iSize);
	return *this;
}

KPacket::KPacket()
{
	ZeroMemory(&m_uPacket, sizeof(UPACKET));
	m_uPacket.ph.len = PACKET_HEADER_SIZE;
	m_pOffset = m_uPacket.msg;
}

KPacket::KPacket(WORD iType)
{
	ZeroMemory(&m_uPacket, sizeof(UPACKET));
	m_uPacket.ph.len = PACKET_HEADER_SIZE;
	m_uPacket.ph.type = iType;
	m_pOffset = m_uPacket.msg;
}

KPacket::KPacket(const KPacket& packet)
{
	m_uPacket.ph = packet.m_uPacket.ph;
	memcpy(m_uPacket.msg, packet.m_uPacket.msg, sizeof(char) * 4096);
	m_pOffset = m_uPacket.msg;
}

KPacket::~KPacket()
{

}
