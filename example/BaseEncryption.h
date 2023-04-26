#include <iostream>
#include <dlfcn.h>
#include <string>

namespace BaseEncryption
{
    std::string Encrypt(std::string text,std::string key);
    std::string Decrypt(std::string text,std::string key);
}


void* handle = dlopen("libencryption.so", RTLD_LAZY);

std::string getMessageEncrypted() {
    typedef void (*rzb)(std::string**);
    rzb razor = (rzb) dlsym(handle, "getEncrypted");
    std::string *link;
    razor(&link);
    return *link;
}

std::string getMessageDecrypted() {
    typedef void (*rzb)(std::string**);
    rzb razor = (rzb) dlsym(handle, "getDecrypted");
    std::string *link;
    razor(&link);
    return *link;
}

std::string BaseEncryption::Encrypt(std::string text,std::string key) {
    typedef void signal(std::string,std::string);
    void* signal_ad = dlsym(handle, "EncryptMessage");
    signal* msg = reinterpret_cast<signal*>(signal_ad);
    msg(key,text);
    msg = NULL;
    signal_ad = NULL;
    return getMessageEncrypted();
}

std::string BaseEncryption::Decrypt(std::string text,std::string key) {
    typedef void signal(std::string,std::string);
    void* signal_ad = dlsym(handle, "DecryptMessage");
    signal* msg = reinterpret_cast<signal*>(signal_ad);
    msg(key,text);
    msg = NULL;
    signal_ad = NULL;
    return getMessageDecrypted();
}

