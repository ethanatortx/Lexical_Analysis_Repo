from datetime import datetime
try:
     # Python 2.6-2.7 
     from HTMLParser import HTMLParser
except ImportError:
     # Python 3
     from html.parser import HTMLParser
import urllib.request as u
import csv
global dictionary_of_sentences
dictionary_of_sentences = [ ]
def word_is_interesting(word):
     listOfBad = ["a", "an", "the", "or", "he", "her", "they", "but", "who", "has", "for", "from", "and", "was", "your", "you", "that", "have", "with", "his", "her", "this", "will", "our", "not", "all", "than", "how", "since", "also", "about", "still", "had", "been", "can", "it", "its", "it's", "are", "were"]
     for w in listOfBad:
          if w.lower()==word.lower():
               return False
     return True

def sentence_is_good(toCheck):
     if (toCheck == toCheck.upper()):
          return False
     banned_words = ['copyright', 'writen by', 'newsletter', 'password', 'subscribe']
     for phrase in banned_words:
          if(phrase.lower() in toCheck.lower()):
               return False
     banned_groups = [ ['create', 'new', 'password'], ['all', 'rights', 'reserved'], ['Please', 'confirm', 'the', 'information', 'below'], ['readers', 'like', 'you'], ['read', 'our'], ['cookie', 'advertising', 'policy'], ['disable', 'ad', 'blocker'], ['share', 'this', 'video'], ['watch', 'this', 'video'], ['watch', 'next'], ['sign', 'in'], ['copy', 'this', 'your', 'clipboard'] ]
     for group in banned_groups:
          strikes = 0
          for item in group:
               if(item.lower() in toCheck.lower()):
                    strikes+=1
          if (strikes/len(group))>.5:
               return False
     return True

def analyze(article, search_term, followLinks):
     h = HTMLParser()
     try:
          response = u.urlopen(article)
     except:
          return
     #Try to open the page. If it doesn't work, exit the page.

     html = response.read().decode()
     temp = ""     
     title = "No Title"
     array_of_sentences = []
     pos = 0
     bracketOn = False
     ampersandOn = False
     strLast = ""
     siteList = []
     while pos < len(html):
          i = html[pos]
          if i == ">":
               bracketOn = False
          elif i == "<":
               bracketOn = True
               if(temp[-1:] in ".!?") or html[pos+1:pos+2] == "/a":
                    if temp != "":
                         #print(temp)
                         array_of_sentences.append(temp)
               temp = ""
          elif i=="&":
               ampersandOn = False
               temp2 = "&"
               while html[pos] != ";":
                    pos+=1
                    try:
                         temp2+=html[pos]
                    except:
                         break
               temp+=h.unescape(temp2)
          elif not bracketOn:
               temp+=str(i)
          if bracketOn:
                if strLast == "<":
                    if(i == "a"):
                         tempStr = ""
                         while html[pos+1]!="\"":
                              pos+=1
                         pos+=1
                         while html[pos+1]!="\"":
                              pos+=1
                              tempStr+=html[pos]
                         if("https://" in tempStr or "http://" in tempStr) and followLinks:
                              if(search_term.lower() in tempStr.lower()):
                                   siteList.append(tempStr)
                    if('title' in html[pos:pos+6].lower()):
                         pos+=1
                         while html[pos]!=">":
                              pos+=1
                         tempStr = ""
                         pos+=1
                         while html[pos]!="<":
                              tempStr+=html[pos]
                              pos+=1
                         title = tempStr
          pos+=1
          strLast = i
     #Everything above this point really just functions as sketchy regex
     #Todo... replace this with actual regex
     title = h.unescape(title)
     if ("google plus" in title or "facebook" in title or search_term.lower() not in title.lower()):
          return
     fixedTitle = ""
     for i in title:
          if i.lower() in 'abcdefghijklmnopqrstuvwxyz1234567890\':':
               fixedTitle+=i
          else:
               if(fixedTitle[:-1] != " "):
                    fixedTitle+=" "
               #Make sure not to add two spaces in a row

     text_file = open(fixedTitle+".txt", "w")
     text_file.write(article)
     text_file.write('\n\n')     
     #Make a text file
     global dictionary_of_sentences
     dictionary_of_sentences.append(array_of_sentences)
     for sentence in array_of_sentences:
          if sentence_is_good(sentence):
               text_file.write(sentence)
               text_file.write('\n\n')
     text_file.close()
     print("Analyzed: " + title)
search_term = input("Search Term: ")
analyzeGoal = 5
numberArticles = input("Analyze how many articles? ")
if(numberArticles.isnumeric()):
     analyzeGoal= int(numberArticles)
else:
     print("That wasn't a number!")
     time.sleep(1000)
start = datetime.now()

q = 'https://www.google.com/webhp?sourceid=chrome-instant&ion=1&espv=2&ie=UTF-8#safe=strict&tbm=nws&q=senate'
q = "https://news.google.com/news?q=" + search_term.replace(" ", "+") + "&output=rss"
q.encode('utf-8').strip()
listOfArticles = []
h = HTMLParser()
response = u.urlopen(q)
html = response.read()
html = html.decode()
pos = 0
number_analyzed_articles = 0
while pos < len(html) and number_analyzed_articles < analyzeGoal:
     if (html[pos:pos+4] == "http"):
          tempStr = ""
          while(html[pos] != "&"):
               tempStr+=html[pos]
               pos+=1
          if "thehill" not in tempStr and "news.google" not in tempStr and "youtube" not in tempStr:
               #Note: The New York Times doesn't play nice with Python's urllib
               #At one point, the New York Times was banned as a source
               try:
                    analyze(tempStr, search_term, False)
                    number_analyzed_articles+=1
               except:
                    number_analyzed_articles -=1
     pos+=1

popularWords = { }

number_of_words = 0
for article in dictionary_of_sentences:
     for sentence in article:
          for w in sentence.split(" "):
               if(w.split("’")[0] != w):
                    word = w.split("’")[0]
               elif(w.split("'")[0] != w):
                    word = w.split("'")[0]
               else:
                    word = w
               number_of_words+=1
               try:
                    if(popularWords[word.lower()]):
                         popularWords[word.lower()]+=1
                    else:
                         popularWords[word.lower()]=1
               except:
                    if len(word)<10 and len(word)>2 and "<" not in word and ">" not in word:
                         popularWords[word.lower()] = 1
good_words_array = []
for word in popularWords:
     if popularWords[word] > analyzeGoal*2 and word_is_interesting(word):
          good_words_array.append((word, popularWords[word]))
for i in range(len(good_words_array)):
     for j in range(len(good_words_array)-i):
          if((good_words_array[i])[1]<(good_words_array[i+j])[1]):
               tmp = good_words_array[i]
               good_words_array[i] = good_words_array[i+j]
               good_words_array[i+j] = tmp
count = 0
for i in range(len(good_words_array)):
     count+=1
     if count < len(good_words_array)/3 :
          print(good_words_array[i])
print("")
print("")
print("Analyzed [", number_of_words, "] words about [", search_term, "] in [", str(datetime.now()-start)[5:], "] seconds!")
