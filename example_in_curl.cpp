#include <iostream>
#include <string>
#include <curl/curl.h>
#include "BaseEncryption.h"

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}



int CurlTest(void)
{
  CURL *curl;
  CURLcode res;
  std::string readBuffer;

  curl = curl_easy_init();
  std::string key = "HSYBXIWOZXU"; // You can Put Values in key but key length must be more than 10 for perfect encryption and decryption
  //example - For Decrypt BaseEncryption::Decrypt("YourTexy, "YourKey");
  //example - For Encrypt BaseEncryption::Encrypt("YourText, "YourKey");
  std::string linkenc = BaseEncryption::Decrypt("HoEqZexJzkSUTPz JrxiKLFa",key); // https://google.com
  const char * link = linkenc.c_str();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, link);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    std::cout << readBuffer << std::endl;
  }
  return 0;
}

// sample encrypt a text
 
void sample(){
   std::string key = "HSYBXIWOZXU";
   std::string text_to_enc = "https://google.com";
   std::cout << BaseEncryption::Encrypt(text_to_enc, key);
}