#include <iostream>
#include <string>
using namespace std;
void removeStopWord(string sentencewords[], int & size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < sentencewords[i].length(); j++)
        {
            sentencewords[i][j] = toupper(sentencewords[i][j]);
        }
    }

    for (int i = 0; i < size; i++)
    {
        if (sentencewords[i] == "A" || sentencewords[i] == "AN" || sentencewords[i] == "AND" || sentencewords[i] == "ARE" || sentencewords[i] == "AS" || sentencewords[i] == "AT" || sentencewords[i] == "BE" || sentencewords[i] == "BUT" || sentencewords[i] == "BY" || sentencewords[i] == "FOR" ||
            sentencewords[i] == "IF" || sentencewords[i] == "IN" || sentencewords[i] == "INTO" || sentencewords[i] == "IS" || sentencewords[i] == "IT" || sentencewords[i] == "NO" || sentencewords[i] == "NOT" || 
            sentencewords[i] == "OF" || sentencewords[i] == "ON" || sentencewords[i] == "OR" || sentencewords[i] == "SUCH" || sentencewords[i] == "THAT" || sentencewords[i] == "THE" || sentencewords[i] == "THEIR" || sentencewords[i] == "THESE" || sentencewords[i] == "THEY" || sentencewords[i] == "THIS" || sentencewords[i] == "TO" || sentencewords[i] == "WAS" || sentencewords[i] == "WILL" || sentencewords[i] == "WITH"){
        
            for (int j = i; j < size-1; j++)
            {
                sentencewords[j] = sentencewords[j + 1];
                
            }
            i--;
            size--;
        }
    }
        
    }

    void printArray(string A[],int maxsize){
        int i;
        for(i=0;i<maxsize;i++){
            cout<<A[i]<<"|";
        }
    }

int main(){
    int size=5;
    string array[size]={"bonjour ","this","is","beautiful","was"};
    removeStopWord(array,size);
    printArray(array,size);

}