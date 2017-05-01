try:
     # Python 2.6-2.7 
     from HTMLParser import HTMLParser
except ImportError:
     # Python 3
     from html.parser import HTMLParser
import urllib.request as u
import csv
global myDict
myDict = { }
def check_conditions(i):
     banned_phrases = ['all rights reserved', 'copyright', 'writen by', 'newsletter', 'password']
     for phrase in banned_phrases:
          if(phrase.lower() in i.lower()):
               return False
     banned_groups = [ ['create', 'new', 'password'], ['Please', 'confirm', 'the', 'information', 'below'], ['readers', 'like', 'you'], ['read', 'our'], ['cookie', 'advertising', 'policy'], ['disable', 'ad', 'blocker'], ['share', 'this', 'video'], ['watch', 'this', 'video'], ['watch', 'next'], ['sign', 'in']]
     for group in banned_groups:
          strikes = 0
          for item in group:
               if(item.lower() in i.lower()):
                    strikes+=1
          if strikes/len(group)>.5:
               return False
     if (i == i.upper()):
          return False
     return True
def analyze(article, searchTerm, followLinks):
     h = HTMLParser()
     try:
          response = u.urlopen(article)
     except:
          return
     html = response.read()
     html = html.decode()
     temp = ""
     
     title = "No Title"
     arrOfSentences = []
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
                         arrOfSentences.append(temp)
               temp = ""
          elif i=="&":
               ampersandOn = False
               temp2 = "&"
               while html[pos] != ";":
                    pos+=1
                    try:
                         temp2+=html[pos]
                    except:
                         return
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
                              if(searchTerm.lower() in tempStr.lower()):
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
     arrOfSentences.append(temp)
     title = h.unescape(title)
     if ("twitter" in title or "google plus" in title or "facebook" in title or searchTerm.lower() not in title.lower()):
          return None
     fixedTitle = ""
     for i in title:
          if i.lower() in 'abcdefghijklmnopqrstuvwxyz1234567890':
               fixedTitle+=i
          else:
               fixedTitle+=" "
     text_file = open(fixedTitle+".txt", "w")
     global myDict
     for sentence in siteList:
          print(sentence)
     for i in arrOfSentences:
           if check_conditions(i):
                for word in sentence:
                    if( myDict[word] == None):
                         myDict[word] = 0
                    myDict[word]+1
               text_file.write(i)
               text_file.write('\n\n')
     text_file.close()
     print("Analyzed: " + title)
     return siteList
searchTerm = input("Search Term: ")
q = 'https://www.google.com/webhp?sourceid=chrome-instant&ion=1&espv=2&ie=UTF-8#safe=strict&tbm=nws&q=senate'
q = "https://news.google.com/news?q=" + searchTerm.replace(" ", "+") + "&output=rss"
q.encode('utf-8').strip()
listOfArticles = []
h = HTMLParser()
response = u.urlopen(q)
html = response.read()
html = html.decode()
pos = 0
totalAnalyzed = 0
while pos < len(html) and totalAnalyzed < 10:
     if (html[pos:pos+4] == "http"):
          tempStr = ""
          while(html[pos] != "&"):
               tempStr+=html[pos]
               pos+=1
          #print(tempStr)
          if "twitter" not in tempStr and "thehill" not in tempStr and "news.google" not in tempStr and "nytimes" not in tempStr and "youtube" not in tempStr:
               #The New York Times doesn't play nice with Python's urllib
               try:
                    for i in analyze(tempStr, searchTerm, False):
                         print(i)
                         listOfArticles.append(i)
               except:
                    totalAnalyzed -=1
               totalAnalyzed+=1
     pos+=1
     if len(listOfArticles) > 20:
          pos = len(html)
for article in listOfArticles:
     analyze(article, searchTerm, False)
print("################")
print("### Finished ###")
print("################")
print(myDict)
for word in myDict:
     print(word)
     print(myDict[word])
     print("")          
