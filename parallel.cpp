#include <stdlib.h>
#include <omp.h>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

string substring(int start, int length, string strword)
{
    string a = "";
    for (int i = start; i < length; i++)
    {
        a += strword[i];
    }
    return a;
}

int find_all(string sen, string word)
{
    int wordLen = word.length();
    int start = 0;
    int endword = wordLen;
    int finLength = sen.length();
    int count = 0;
    string senWord = "";
    for (int i = 0; i <= sen.length(); i++)
    {
        if (endword > finLength)
        {
            break;
        }
        senWord = substring(start, endword, sen);
        if ((senWord.compare(word)) == 0)
        {
            count++;
            if (endword > finLength)
            {
                break;
            }
        }
        start += 1;
        endword += 1;
    }
    return count;
}

int display(string path, string word_to_search)
{
    int totalCount = 0;
    string line;
    int count = 1;
    ifstream myfile(path);
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            totalCount += find_all(line, word_to_search);
            count++;
        }
        myfile.close(); // Close file after use
    }
    else
    {
        cout << "File not open\n" << endl;
    }
    return totalCount;
}

int main()
{
    string Path = "";
    string word_to_search = "";
    cout << "Enter a word to search: ";
    cin >> word_to_search;
    double time = omp_get_wtime();
#pragma omp parallel for
    for (int i = 1; i <= 5; i++)
    {
        string npath = "File" + to_string(i) + ".txt";

        #pragma omp critical
        cout << "Total Count is " + to_string(display(npath, word_to_search)) << " from file " + to_string(i) << endl;
    }
    time = omp_get_wtime() - time;
    cout << "Time is " + to_string(time) << endl;
    return 0;
}
