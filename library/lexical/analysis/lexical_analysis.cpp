
#include "..\lexical.h"

int main()
{
	string sourceText = "I was born in Lousiana down on the ol bayou raised on shrimps and catfish mamas good gumbo. I got the ramblin fever. Said goodbye to ma and pa. Crossed that ol red river and this is what I saw. I saw miles and miles of Texas 1000 stars up in the sky. I saw miles and miles of Texas gonna live here till I die.";
	
	int uniqueWords = uniqueWordCount(sourceText);
	int numWords = wordCount(sourceText);
	int numSentences = sentenceCount(sourceText);
	
	cout << "Occurences of \"is\": " << substringCount(sourceText, "is") << endl;
	cout << "Word Count: " << numWords << endl;
	cout << "Unique Word Count: " << uniqueWords << endl;
	cout << "Number of Sentences: " << numSentences << endl;
	cout << "Average number of words per sentence: " << avgWordsPerSentence(numWords, numSentences) << endl;
	cout << "Lexical density: " << lexDensity(uniqueWords, numWords);
}