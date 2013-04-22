
#ifdef __GNUC__
#  define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#endif

#include <unistd.h>
#include <cryptopp/md5.h>
#include <cryptopp/hex.h>
#include <iostream>

int main()
{
    CryptoPP::Weak1::MD5 hash;

    byte digest[CryptoPP::Weak1::MD5::DIGESTSIZE];
    std::string message = "";

    hash.CalculateDigest(digest, (byte*) message.c_str(), message.length());

    std::string output;
    CryptoPP::HexEncoder encoder;

    encoder.Attach(new CryptoPP::StringSink(output));
    encoder.Put(digest, sizeof(digest));
    encoder.MessageEnd();

    std::cout << output << std::endl;

    return 0;
}