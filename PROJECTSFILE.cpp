#include <iostream>
#include <string>
#include <cctype>
using namespace std;
int const maxsize = 100;
string determineFactoidType(string question)
{
    int i, start = 0,j=0;
    string keyword = "",array[2];
    for (i = 0; i < question.length(); i++)
    {
        question[i] = toupper(question[i]);
    } // upper case
    
    for(i=0;i<question.length();i++){
        if(question[i]==' ' ){
            if(i>start && j<2){
                array[j]=question.substr(start,i-start);
                j++;
            }
            start=i+1;
        }
    }

    if(array[0]=="HOW"){
        keyword=array[0]+array[1];
    }
    else if(array[0]=="WHEN" || array[0]=="WHERE" || array[0]=="WHO")
    keyword=array[0];

    if (keyword == "WHEN")
        return "time or date";
    if (keyword == "WHERE")
        return "location";
    if (keyword == "WHO")
        return "name of person";
    if (keyword == "HOWMANY" || keyword=="HOWMUCH")
    {
        return "numerical information";
    }
    return "that's not a factoid question";
}

int splittext(string text, string sentences[])
{
    int i, start = 0, length = text.length(), j = 0;
    for (i = 0; i <= length; i++)
    {
        if (i == length|| text[i] == '.' )
        {
            if (i > start)
            {
                sentences[j] = text.substr(start, i - start);
                j++;
            }
            start = i + 1;
        }
    }
    return j;
}

void removeStopWord(string sentencewords[], int &size)
{
 
    for (int i = 0; i < size; i++)
    {
        if (sentencewords[i] == "a" || sentencewords[i] == "an" || sentencewords[i] == "and" || sentencewords[i] == "are" || sentencewords[i] == "as" || sentencewords[i] == "at" || sentencewords[i] == "be" || sentencewords[i] == "but" || sentencewords[i] == "by" || sentencewords[i] == "for" ||
            sentencewords[i] == "if" || sentencewords[i] == "in" || sentencewords[i] == "into" || sentencewords[i] == "ia" || sentencewords[i] == "it" || sentencewords[i] == "no" || sentencewords[i] == "not" || sentencewords[i] == "of" ||
             sentencewords[i] == "on" || sentencewords[i] == "or" || sentencewords[i] == "such" || sentencewords[i] == "that" || sentencewords[i] == "the" || sentencewords[i] == "their" || sentencewords[i] == "these" || sentencewords[i] == "they" || sentencewords[i] == "this" || sentencewords[i] == "to" || sentencewords[i] == "was" || sentencewords[i] == "will" || sentencewords[i] == "with")
        {
            for (int j = i; j < size-1;j++)
            {
                sentencewords[j] = sentencewords[j + 1];
                
            }
            size--;
            i--;
        }
    }
}

int stringtoarray(string str, string arr[])
{
    int i, start = 0, j = 0;
    for (i = 0; i <= str.length(); i++)
    {
        if (str[i] == ' ' || str[i] == '.'|| i == str.length() ||str[i] == ',' || str[i] == '?'|| str[i] == '!' )
        {
            if (start < i)
            {
                arr[j] = str.substr(start, i - start);
                j++;
            }
            start = i + 1;
        }
    }
    return j;
}

double Similarity(string sentence1, string sentence2)
{
    string array1[maxsize], array2[maxsize];
    int size1, size2, i, j, count = 0;
   size1= stringtoarray(sentence1, array1);
   size2= stringtoarray(sentence2, array2);

    for (i = 0; i < size1; i++)
    {
        for (j = 0; j < size2; j++)
        {
            if (array1[i] == array2[j])
                count++;
        }
    }
    if (size1 < size2)
        return (double) count / size1;
    else
        return (double) count / size2;
}

bool checkPersonName(string sentencewords[], int MAXWORDS, string &Answer)
{
    int i, j;
    bool valid ;
    for (i = 0; i < MAXWORDS; i++)
    {
        valid = true;
        if (isupper(sentencewords[i][0]))
        {
            valid = true;
        
        for (j = 1; j < sentencewords[i].length(); j++)
        {
            if (isupper(sentencewords[i][j])){
                valid = false;
                break;
            }
        }
    }
    else continue;
        if (valid)
        {
            Answer = sentencewords[i];
            return true;
        }
    }
    return false;
}

bool checklocation(string sentencewords[], int MAXWORDS, string &Answer)
{
    int i, j;
    bool valid = true;
    for (i = 0; i < MAXWORDS; i++)
    {
         valid = true;
        for (j = 0; j < sentencewords[i].length(); j++)
        {
            if (isupper(sentencewords[i][j]) == false){
                valid = false;
            break;
        }
    }
        if (valid)
        {
            Answer = sentencewords[i];
            return true;
        }
    }
    return false;
}

bool checkDateTime(string sentencewords[], int MAXWORDS, string &Answer)
{
    for (int i = 0; i < MAXWORDS; i++)
    {
        string w = sentencewords[i];

        if (w.length() == 8 &&
            w[2] == ':' && w[5] == ':' &&
            isdigit(w[0]) && isdigit(w[1]) &&
            isdigit(w[3]) && isdigit(w[4]) &&
            isdigit(w[6]) && isdigit(w[7]))
        {
            Answer = w;
            return true;
        }

        if (w.length() == 10 &&
            (w[4] == '/' || w[4] == '-') &&
            w[4] == w[7] &&
            isdigit(w[0]) && isdigit(w[1]) &&
            isdigit(w[2]) && isdigit(w[3]) &&
            isdigit(w[5]) && isdigit(w[6]) &&
            isdigit(w[8]) && isdigit(w[9]))
        {
            Answer = w;
            return true;
        }
    }

    return false;
}

bool checkNumber(string sentencewords[], int MAXWORDS, string &Answer)
{
    int i, j;
    bool valid;
    for (i = 0; i < MAXWORDS; i++)
    {
        valid = true;
        if (sentencewords[i][0] != '-')
        {
            for (j = 0; j < sentencewords[i].length(); j++)
            {
                if (isdigit(sentencewords[i][j]) == false)
                {
                    valid = false;
                    break;
                }
            }
            if (valid)
            {
                Answer = sentencewords[i];
                return true;
            }
        }
        else
        {

            for (j = 1; j < sentencewords[i].length(); j++)
            {
                if (isdigit(sentencewords[i][j]) == false)
                {
                    valid = false;
                    break;
                }
            }
            if (valid)
            {
                Answer = sentencewords[i];
                return true;
            }
        }
        
    }
    return false;
}


int main()
{
    string question, questiontype, sentences[maxsize], text, sentencewords[maxsize];
    int size, sizesentencewords;
    text="The history of programming languages spans from documentation of early mechanical computers to modern tools for software development. Early programming languages were highly specialized, relying on mathematical notation and similarly obscure syntax. Throughout the 20th century, research in compiler theory led to the creation of high-level programming languages, which use a more accessible syntax to communicate instructions. the first high-level programming language was created by Konrad-zuse in 1943. The first high-level language to have an associated compiler was created by Corrado B ̈ohm in 1951. Konrad-zuse was born on 1910/06/22 , in GERMANY, was a notable civil engineer, pioneering computer scientist, inventor, and businessman.";
    cout << "enter the question";
    getline(cin, question);
    questiontype = determineFactoidType(question);
    size = splittext(text, sentences);
    for (int i = 0; i < size; i++)
    {
        sizesentencewords = stringtoarray(sentences[i], sentencewords);
        removeStopWord(sentencewords, sizesentencewords);
        sentences[i] = "";
        for (int k = 0; k < sizesentencewords; k++)
        {
            sentences[i] = sentences[i] + sentencewords[k];
            sentences[i] += " ";
        }
    }
    double maxsimilarity = Similarity(sentences[0], question);
    string save = sentences[0];
    for (int k = 1; k < size; k++)
    {
        if (maxsimilarity < Similarity(sentences[k], question))

        {
            save = sentences[k];
            maxsimilarity = Similarity(sentences[k], question);
        }
    }
    string savearray[maxsize], answer = "";
    int numberwords;
    numberwords = stringtoarray(save, savearray);
    if (questiontype == "time or date")
    {
        if (checkDateTime(savearray, numberwords, answer))
            cout << "the must appropriate answer is n/ " << answer;
    }
    else

        if (questiontype == "location")
    {
        if (checklocation(savearray, numberwords, answer))
            cout << "the most appropriate answer is  " << answer;
    }
    else if (questiontype == "name of person")
    {
        if (checkPersonName(savearray, numberwords, answer))
            cout << "the most appropriate answer is  " << answer;
    }

    else if (questiontype == "numerical information")
    {
        if (checkNumber(savearray, numberwords, answer))
            cout << "the most appropriate answer is  " << answer;
    }
    else
        cout << "the question is invallid";
}

