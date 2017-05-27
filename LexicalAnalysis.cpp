#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
using namespace std;

int countSubstring(const string& str, const string& sub)
{
	if(sub.length()== 0) 
		return 0;
	int count = 0;
	for(int offset = str.find(sub); offset != string::npos; offset = str.find(sub,offset + sub.length())) 
	{
		++count;
	}
	return count;
}

int uniqueWords(const string& str) 
{	
	string Total = "";
	string concat = "";
	int z = 0;
	for(int i = 0; i < str.length(); i++)
	{
		if(str[i] == ' ' || i == str.length()-1) {
			if((Total.find(concat + " ")) > str.length() && (Total.find(concat + ".")) > str.length()) {
				Total += concat + " ";
				concat = "";
				z += 1;
				
			}
			else {
				concat = " ";
			}
		}
		else {
			concat += str[i];
		}
	}
	cout << z;
	return z;
}

string readIn(string source)
{
	//source = "Donald Trump arrives in Bethlehem for talks with Abbas    Palestine News   Al Jazeera.txt";
	ifstream infile;
	string result;
	string final;
	string sentence;
	infile.open(source, ifstream::in);
	if(infile.is_open())
	{
		while(getline(source, sentence))
		{
			for(int i = 0; i < sentence; i++)
			{
				char c = sentence[i];
				final = final + " " + c;
			}

		}
		infile.close();
	}
	else{cout << "ERROR BEOTCH";}
}



int main()
{
	cout << "Which file would you like to display?";
	string open;
	cin >> open;
	string source = readIn("Donald Trump arrives in Bethlehem for talks with Abbas    Palestine News   Al Jazeera.txt");
	int totWords = countSubstring(source, " ") + 1;
	int sentances = countSubstring(source, ".");
	cout << "substring count: " << countSubstring(source, "is") << '\n';
	cout << "number of words: " << countSubstring(source, " ")  + 1 << '\n';
	cout << "number of sentances: " << countSubstring(source, ".") << '\n';
	cout << "words per sentance is: " << (double)totWords/sentances << '\n';
	double uniWord = uniqueWords(source) + 1;
	double fin = uniWord / (countSubstring(source, " ")  + 1);
	double finfin = fin * 100;
	cout << "Lexical Analysis is: " << finfin;

return 0;
}