#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

int countSubstring(const std::string& str, const std::string& sub)
{
	if(sub.length()== 0) 
		return 0;
	int count = 0;
	for(int offset = str.find(sub); offset != std::string::npos; offset = str.find(sub,offset + sub.length())) 
	{
		++count;
	}
	return count;
}

int uniqueWords(const std::string& str) 
{	
	std::string Total = "";
	std::string concat = "";
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
	std::cout << z;
	return z;
}

std::string readIn(std::string source)
{
	//source = "Donald Trump arrives in Bethlehem for talks with Abbas    Palestine News   Al Jazeera.txt"
	std::ifstream infile;
	std::string sentence, final;
	int count = 0;
	infile.open(source);
	if(infile.is_open())
	{
		std::cout << "Pass " << ++count << "...\n";
		while(std::getline(infile, sentence, '\n'))
		{
			final.append(sentence);
		}
		infile.close();
	}

	return final;
}



int main()
{
	std::cout << "Which file would you like to display?";
	std::string open;
	std::cin >> open;
	std::string source = readIn(open);
	int totWords = countSubstring(source, " ") + 1;
	int sentances = countSubstring(source, ".");
	std::cout << "substring count: " << countSubstring(source, "is") << '\n';
	std::cout << "number of words: " << countSubstring(source, " ")  + 1 << '\n';
	std::cout << "number of sentances: " << countSubstring(source, ".") << '\n';
	std::cout << "words per sentance is: " << (double)totWords/sentances << '\n';
	double uniWord = uniqueWords(source) + 1;
	double fin = uniWord / (countSubstring(source, " ")  + 1);
	double finfin = fin * 100;
	std::cout << "Lexical Analysis is: " << finfin;

return 0;
}