#ifndef __LEXICAL_H_INCLUDED__
#define __LEXICAL_H_INCLUDED__

#include<iostream>
#include<string>
using namespace std;

class Lexical
{
	public:
		int substringCount(string source, string sub)
		{
			int sourceLen = source.length();
			int subLen = sub.length();
				
			if(sourceLen == 0 || subLen == 0)
				return 0;
			int count = 0;
			for(int i = 0; i <= sourceLen - subLen; i++)
			{	
				if(source.substr(i, subLen).compare(sub) == 0)
					count++;
			}
			
			return count;
		};

		int wordCount(string source)
		{
			int len = source.length();
			int count = 0;
			for(int i = 0; i < len; i++)
			{
				if(i == 0)
					count++;
				else if(((source[i] <= 90 && source[i] >= 65) || (source[i] <= 122 && source[i] >= 97)) && (source[i-1] == ' '))
					count++;
			}
			return count;
		};

		//needs to be fixed
		int uniqueWordCount(string source)
		{
			int len = source.length();
				
			//sort input into an array
			string arraySource[wordCount(source)] = {};
			int arrayPos = 0;
			for(int i = 0; i < len; i++)
			{
				if(i == 0)
				{
					int lengthWord = 0;
					for(int k = i; k < len; k++)
					{
						lengthWord++;
						if(source[k] == ' ' || source[k] == '.')
						{
							break;
						}
					}
					arraySource[arrayPos] = source.substr(i, lengthWord);
					arrayPos++;
				}
				else if(((source[i] <= 90 && source[i] >= 65) || (source[i] <= 122 && source[i] >= 97)) && (source[i-1] == ' '))
				{
					int lengthWord = 0;
					for(int k = i; k < len; k++)
					{
						lengthWord++;
						if(source[k] == ' ' || source[k] == '.')
						{
							break;
						}
					}
					arraySource[arrayPos] = source.substr(i, lengthWord);
					arrayPos++;
				}
			}
			
			//determine how many occurences are unique
			int count = 0;
			string alreadyCounted = " ";
			for(int z = 0; z < wordCount(source); z++)
			{
				if(alreadyCounted.find(" " + arraySource[z] + " ") == string::npos)
				{
					count++;
					alreadyCounted += arraySource[z] + " ";
				}
			}
			
			return count;
		};

		int sentenceCount(string source)
		{
			return substringCount(source, ".");
		};

		double avgWordsPerSentence(int totalWords, int sentences)
		{
			return double(totalWords) / sentences;
		};

		double lexDensity(int unique, int total)
		{
			return double(unique) / total * 100;
		};
};

#endif