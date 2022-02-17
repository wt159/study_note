#include <string>
#include <stdio.h>
#include <iostream>
#if defined(WIN32)||defined(WINCE)||defined(WIN64)
#include <objbase.h>
#else
#include <uuid/uuid.h> 
#endif

std::string GetUUID(std::string& strUUID)
{
    strUUID = "";
#if defined(WIN32)||defined(WINCE)||defined(WIN64)
    GUID guid;
    if ( !CoCreateGuid(&guid) )
    {
        char buffer[64] = {0};
        _snprintf_s(buffer, sizeof(buffer),
            //"%08X%04X%04X%02X%02X%02X%02X%02X%02X%02X%02X",    //大写
            "%08x%04x%04x%02x%02x%02x%02x%02x%02x%02x%02x",        //小写
            guid.Data1, guid.Data2, guid.Data3,
            guid.Data4[0], guid.Data4[1], guid.Data4[2],
            guid.Data4[3], guid.Data4[4], guid.Data4[5], 
            guid.Data4[6], guid.Data4[7]);
        strUUID = buffer;
    }
#else
    char str[64] = {0};
    uuid_t uu;
    uuid_generate(uu);
    uuid_unparse(uu, str);
    strUUID = str;
#endif
    return strUUID;  
}  


int main(void)
{
    std::string str;
    std::cout << GetUUID(str) << std::endl;
}