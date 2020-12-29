#include <iostream>
#include <bits/stdc++.h>
#include "BitVector.h"
#include <string.h>
#include <fstream>
using namespace std;

class BloomFilter
{
    BitVector *bitvector;
    int NoOfBits;
    long HashValues[6];
    long p = 16777212;
    inline unsigned long long Power(unsigned long long num, int curr) //To Calculate Power of 2 to convert Binary
    {
        if (num * curr != 0)
        {
            for (int i = 0; i < curr; i++)
            {
                num *= num;
            }
            return num;
        }
        return 0;
    }

public:
    BloomFilter() // Constructor use N0OfBits Constant because of Our File
    {
        NoOfBits = 728000;
        bitvector = new BitVector(NoOfBits);
        for (int i = 0; i < 7; i++)
        {
            HashValues[i] = 1;
            RandNumber(HashValues[i]); //Store Random Hash Value to Make Random Hash Functions
        }
    }
    long long StringToInt(string Temp, int HashFuncNum) //Convert String From File into integer
    {
        unsigned long long Sum = 0;

        int Size = Temp.size();
        for (int i = 0; i < Temp.size(); i++)
        {
            char Te = Temp.at(i);
            int curr = (int)Te;
            Size--;
            Sum = Sum + (Power(HashValues[HashFuncNum], Size) * curr);
            Sum = Sum % p;
        }
        return Sum;
    }

    void RandNumber(long &Num) //Generate 32 bit Long Random Number
    {
        bool arr[23];
        for (int i = 0; i < 24; i++) // Rand Can't Generate Such a Long number so
        {                            //Generate Each bit seperately
            arr[i] = rand() % 2;
        }
        int j = 23;
        for (int i = 0; i < 24; i++) //Convert Binary Number into Int
        {
            Num = Num + (Power(2, i) * arr[j]);
            j--;
        }
        Num %= 728000; // Because No should be Smaller then whole size
    }
    void PrintRand() // Print Random Values Stored in array For Hash Functions
    {
        for (int i = 0; i < 7; i++)
        {
            cout << HashValues[i] << endl;
        }
    }
    int HashFunction(int index, string Word)
    {
        long long Num = StringToInt(Word, index);
        return (Num % p) % NoOfBits;
    }
    void SetBits(string Word) //Set the Bits According to Word Passed
    {
        for (int i = 0; i < 6; i++) //TO use 6 Hash Functions
        {
            bitvector->set(HashFunction(i, Word)); //Get the Hashed Value and Set that Bit
        }
    }
    void GetBits(string Word, bool Array[6]) //Print the Bits According to Word Passed
    {
        for (int i = 0; i < 6; i++) //TO use 6 Hash Functions
        {
            Array[i] = bitvector->get(HashFunction(i, Word)); //Get Hashed Value and Print that bit
        }
    }
};
void LoadDictionary(BloomFilter &Bloom) //As the names States it Load the Complete dictionary into the
{                                       //Bit vector
    string FileName = "dict.txt";
    fstream File;
    string Word;
    File.open(FileName.c_str());

    while (File >> Word) //Set the bits of Bit Vector According the Dictionary word
    {
        Bloom.SetBits(Word);
    }
}
bool CheckTheWord(string input, BloomFilter &BLoom) //Check the Entered Word
{
    bool Array[6];
    BLoom.GetBits(input, Array); //Check the bits of bit vector according to the word
    for (int i = 0; i < 6; i++)
    {
        if (!Array[i]) //If any bit is not set it means The words are not same
        {
            cout << endl
                 << "[" << input << "]" << endl; //if there is mistake then print that word
                                                 //i.e [example]
            return false;
        }
    }
    return true;
}
void CheckthePara(string Input, BloomFilter &BLoom)
{
    stringstream input(Input);
    string word;
    while (input >> word)
    {
        CheckTheWord(word, BLoom);
    }
}
int main()
{
    BloomFilter BLoom;
    LoadDictionary(BLoom);
    string input;
    cout << "Enter The Text" << endl;
    getline(cin, input);
    CheckthePara(input, BLoom);
    return 0;
}