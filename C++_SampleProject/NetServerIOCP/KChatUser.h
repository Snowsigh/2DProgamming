#pragma once
#include <KNetUser.h>
class KChatUser : public KNetUser, public KObjectPool<KChatUser>
{

};