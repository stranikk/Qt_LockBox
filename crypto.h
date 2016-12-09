#ifndef CRYPTO_H
#define CRYPTO_H

#include <QString>
#include </usr/local/include/botan/botan.h>
#include </usr/local/include/botan/pipe.h>
#include </usr/local/include/botan/aes.h>
#include </usr/local/include/botan/filters.h>
#include <QObject>

using namespace std;
class Crypto
{
public:
    Crypto();
    string MyShifr(string, string, string, bool);
};

#endif // CRYPTO_H
