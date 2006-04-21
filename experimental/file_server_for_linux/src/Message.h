#ifndef _MONA_USERLIB_MESSAGE_
#define _MONA_USERLIB_MESSAGE_

#ifdef ON_LINUX
#include "types.h"
#else
#include <sys/types.h>
#endif

namespace MonAPI {

/*----------------------------------------------------------------------
    Message
----------------------------------------------------------------------*/
class Message {

public:
    static int send(dword tid, MessageInfo* info);
    static int send(dword tid, dword header, dword arg1 = 0, dword arg2 = 0, dword arg3 = 0, const char* str = NULL);
    static int receive(MessageInfo* info);
    static int reply(MessageInfo* info, dword arg2 = 0, dword arg3 = 0, const char* str = NULL);
    static int peek(MessageInfo* info, int index, int flags = 0);
    static void create(MessageInfo* info, dword header, dword arg1 = 0, dword arg2 = 0, dword arg3 = 0, const char* str = NULL);
    static bool exist();
    static dword lookup(const char* name);
    static dword lookupMainThread(const char* name);
    static dword lookupMainThread();

    static int sendReceiveA(MessageInfo* dst, dword tid, MessageInfo* info);

    static int sendReceive(MessageInfo* dst, dword tid, dword header, dword arg1 = 0, dword arg2 = 0, dword arg3 = 0, const char* str = NULL);

    static int receive(MessageInfo* dst, MessageInfo* src, bool(*equals)(MessageInfo* msg1, MessageInfo* msg2));

    static bool equalsHeader(MessageInfo* msg1, MessageInfo* msg2)
    {
        return (msg1->header == msg2->header);
    }

    static bool equalsFrom(MessageInfo* msg1, MessageInfo* msg2)
    {
        return (msg1->from == msg2->from);
    }

    static bool equalsFromHeader(MessageInfo* msg1, MessageInfo* msg2)
    {
        return (msg1->from == msg2->from) && (msg1->header == msg2->header);
    }

    static bool equalsFromHeaderArg1(MessageInfo* msg1, MessageInfo* msg2)
    {
        return (msg1->from == msg2->from) && (msg1->header == msg2->header) && (msg1->arg1 == msg2->arg1);
    }

    // hack for emulation on Linux
#ifdef ON_LINUX
    static void initialize();
    static void destroy();
    static int msqid;
#define M_BUFSIZ sizeof(MessageInfo)
    struct MessageBuf
    {
      long int type;
      char data[M_BUFSIZ];
    };
#endif

};

}

#endif
