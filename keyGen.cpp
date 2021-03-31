#include "keyGen.h"

/*
Function to calculate gratest common factor of two numbers.
Implements an euclidean algorithm.
*/
int gratestCommonFactor(unsigned int a, unsigned int b)
{
    while (a % b != 0)
    {
        unsigned int tmp = a;
        a = b;
        b = tmp % a;
    }
    return b;
}

/*
Create a file with name "primesFile.txt",
that contains prime numbers in range [lowLimit, highLimit].
*/
void primeFileGen(unsigned int lowLimit, unsigned int highLimit)
{
    std::vector<bool> prime(highLimit + 1, true);
    prime[0] = prime[1] = false;
    for (unsigned int i = 2; i <= highLimit; ++i)
    {
        if (prime[i])
        {
            if (i * 1ll * i <= highLimit)
            {
                for (unsigned int j = i * i; j <= highLimit; j += i)
                {
                    prime[j] = false;
                }
            }
        }
    }

    std::ofstream primesFile("primesFile.txt", std::ios::out);
    if (!primesFile.is_open())
    {
        std::cerr << "Can't create \"primesFile.txt\"." << std::endl;
        exit(1);
    }
    unsigned int counter = 0;
    for (unsigned int i = lowLimit; i <= highLimit; ++i)
    {
        if (prime[i])
        {
            ++counter;
        }
    }
    primesFile << counter << ' ';
    for (unsigned int i = lowLimit; i <= highLimit; ++i)
    {
        if (prime[i])
        {
            primesFile << i << ' ';
        }
    }
    primesFile.close();
}


/*
Fill the vector of intgers on heap with numbers from
"primesFile.txt".
*/
std::vector<unsigned int>* fillVectorFromPrimeFile()
{
    std::ifstream primesFile("primesFile.txt", std::ios::in);
    if (!primesFile.is_open())
    {
        std::cerr << "Can't open \"primesFile.txt\".";
        exit(1);
    }
    unsigned int size;
    primesFile >> size;
    std::vector<unsigned int>* primesVector = new std::vector<unsigned int>(size);

    for (unsigned int i = 0; i < size; ++i)
    {
        primesFile >> (*primesVector)[i];
    }
    primesFile.close();
    return primesVector;
}

/*
Calculate inverse number using extended euclidean algorithm.
( number * inverseNumber % module = 1 ).
At the start we have x0 = 0, x1 = 1, then we iterating
until module % number == 0.
x<i> = x<i - 2> - q<i - 1> * x<i - 1>, where
q = module / number.
*/
unsigned int calculateInverseNumber(unsigned int number, unsigned int module)
{
    int xIMinusTwo = 0, xIMinusOne = 1, x, savedModule = module, q;

    for (;;)
    {
        q = module / number;
        x = xIMinusTwo - q * xIMinusOne;
        unsigned int tmp = module % number;
        module = number;
        number = tmp;
        if ((module % number) == 0)
        {
            break;
        }
        xIMinusTwo = xIMinusOne;
        xIMinusOne = x;
    }
    if (x < 0)
    {
        return savedModule + x;
    }
    return x;
}


/*
1. Randomly choose two numbers (p, q)
2. Calculate module (p * q) of p and q
3. Calculate euler function of p and q
    - euler function of two prime numbers p and q equals (p - 1) * (q - 1)
4. Calculate open exponent that
    -prime
    -less than euler function
    -mutually prime to euler function

set of number {open exponent, module} is a public key

5. Calculate inverse modulo number (secret exponent) to open expoent

set of number {secret exponent, module} is a private key
*/
void keyGen(std::vector<unsigned int>* primesVector, std::string keyName)
{
    srand(time(NULL));
    unsigned int p = (*primesVector)[(rand() % (*primesVector).size())];
    unsigned int q = (*primesVector)[(rand() % (*primesVector).size())];
    unsigned int module = p * q;
    unsigned int eulerFunc = (p - 1) * (q - 1);
    unsigned int openExponent;
    unsigned int openExponentMaxIndex = 0;
    unsigned int delta = (*primesVector).size() / 4;
    for (unsigned int i = (*primesVector).size() / 2; delta >= 1; )
    {
        if ((*primesVector)[i] < eulerFunc)
        {
            openExponentMaxIndex = i;
            i += delta;
        }
        else if ((*primesVector)[i] > eulerFunc)
        {
            i -= delta;
        }
        else if (((*primesVector)[i] == eulerFunc))
        {
            openExponentMaxIndex = i;
            break;
        }
        delta /= 2;
    }
    openExponent = (*primesVector)[(rand() % openExponentMaxIndex)];
    while (gratestCommonFactor(eulerFunc, openExponent) != 1)
    {
        openExponent = (*primesVector)[(rand() % openExponentMaxIndex)];
    }
    unsigned int secretExponent = calculateInverseNumber(openExponent, eulerFunc);
    Key pubKey(openExponent, module);
    Key privKey(secretExponent, module);
    std::string pubKeyFilename = keyName + ".pub.key";
    std::string privKeyFilename = keyName + ".priv.key";
    std::ofstream pubKeyFile(pubKeyFilename, std::ios::out);
    std::ofstream privKeyFile(privKeyFilename, std::ios::out);
    if (!pubKeyFile.is_open() || !privKeyFile.is_open())
    {
        throw std::ios_base::failure::failure("Can't create key files.");
    }
    pubKeyFile << pubKey;
    privKeyFile << privKey;
    pubKeyFile.close();
    privKeyFile.close();
}

/*
One function realization of all above
*/
void generate(std::string keyName, unsigned int lowLimit, unsigned int highLimit)
{
    std::ifstream primesFile("primesFile.txt", std::ios::in);
    if (!primesFile.is_open())
    {
        primesFile.close();
        primeFileGen(lowLimit, highLimit);
        primesFile.open("primesFile.txt", std::ios::in);
    }
    if (!primesFile.is_open())
    {
        std::cerr << "Can't open \"primesFile.txt\"." << std::endl;
        exit(1);
    }
    std::vector<unsigned int>* primes;
    primes = fillVectorFromPrimeFile();
    keyGen(primes, keyName);
    delete primes;
}
