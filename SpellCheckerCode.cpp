//Name : Munawar Hussain
//Roll No: 19L-2309

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

public:
    long Power(int num, int curr) //To Calculate Power of 2 to convert Binary
    {
        long Sum = 0;
        if (num * curr != 0)
        {
            Sum = num * num;
            for (int i = 2; i < curr; i++)
            {
                Sum *= num;
            }
            return Sum;
        }
        return 0;
    }
    BloomFilter() // Constructor use N0OfBits Constant because of Our File
    {
        NoOfBits = 728000;
        bitvector = new BitVector(NoOfBits);
        for (int i = 0; i < 6; i++)
        {
            RandNumber(HashValues[i]); //Store Random Hash Value to Make Random Hash Functions
        }
    }
    long long StringToInt(string Temp, int HashFuncNum) //Convert String From File into integer
    {
        unsigned long long Sum = 0;
        int Size = 0;
        for (int i = 0; i < Temp.size(); i++)
        {
            char Te = Temp.at(i);
            int curr = (int)Te;
            if (curr >= 65 && curr <= 90)
            {
                curr = curr + 32;
            }
            Size++;
            Sum = (Sum % 16777212) + (Power(HashValues[HashFuncNum], Size) * curr);
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
        Num %= p; // Because No should be Smaller then whole size
    }
    void PrintRand() // Print Random Values Stored in array For Hash Functions
    {
        for (int i = 0; i < 7; i++)
        {
            cout << HashValues[i] << endl;
        }
    }
    int HashFunction(int index, string Word) //It Return the Random index
    {
        long long Num = StringToInt(Word, index); //Convert the Entered Word into Num
        Num = Num % NoOfBits;
        if (Num < 0) //This is the Check if the value is Negative make it Possitive
        {
            Num = Num * -1;
        }
        return Num;
    }
    void SetBits(string Word) //Set the Bits According to Word Passed
    {
        for (int i = 0; i < 6; i++) //TO use 6 Hash Functions
        {
            bitvector->set(HashFunction(i, Word)); //Get the Hashed Value and Set that Bit
        }
    }
    void Display(int Num)
    {
        float Percentage = (Num * 100 * 100 * 80) / NoOfBits; //As the NoOfBits are large so to Get Correct percentage
        if (Num == 90)                                        //I multiplied it
        {                                                     //In the Next Tern as it increase 100 so let's hard Code it
            cout << " wait for few Second File is Loading " << 100 << "%" << endl;
        }
        else
        {
            cout << " wait for few Second File is Loading " << Percentage << "%" << endl;
        }

        for (int i = 0; i < Num; i++) //The Uper Boundry of Line
        {
            cout << "_";
        }
        cout << endl;
        for (int i = 0; i < Num; i++)
        {
            cout << "|";
        }
        cout << endl;
        for (int i = 0; i < Num; i++) //The Lower Boundry of Line
        {
            cout << "-";
        }
        cout << endl;
    }

    bool GetBits(string Word) //Print the Bits According to Word Passed
    {
        int count = 0;
        for (int i = 0; i < 6; i++) //TO use 6 Hash Functions
        {
            if (bitvector->get(HashFunction(i, Word)))
            {
                count++;
            }
            //Get Hashed Value and Print that bit
        }
        return (count == 6);
    }
};
void LoadDictionary(BloomFilter &Bloom) //As the names States it Load the Complete dictionary into the
{
    cout << "\033[2J\033[1;1H";
    cout << "           Wait for few Seconds Dictionary is Loading" << endl; //Bit vector
    string FileName = "dict.txt";
    fstream File;
    string Word;
    File.open(FileName.c_str());
    int Count = 0;
    int i = 0;
    while (File >> Word) //Set the bits of Bit Vector According the Dictionary word
    {
        Bloom.SetBits(Word);
        i++;
        if (i == 1000)
        {
            Count++;
            if (Count == 80)
            {
                cout << "";
            }

            Bloom.Display(Count);
            i = 0;
        }
    }
    cout << "             Dictionary is Loaded " << endl;
}
bool CheckTheWord(string input, BloomFilter &BLoom) //Check the Entered Word
{

    if (!BLoom.GetBits(input))
    {
        cout << "[" << input << " ]" << endl;
    }; //Check the bits of bit vector according to the word

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