try:
     # Python 2.6-2.7 
     from HTMLParser import HTMLParser
except ImportError:
     # Python 3
     from html.parser import HTMLParser
import urllib.request as u
import csv
def check_conditions(i):
     banned_phrases = ['all rights reserved', 'copyright', 'writen by', 'newsletter']
     for phrase in banned_phrases:
          if(phrase.lower() in i.lower()):
               return False
     banned_groups = [ ['readers', 'like', 'you'], ['read', 'our'], ['cookie', 'advertising', 'policy'] ]
     for group in banned_groups:
          strikes = 0
          for item in group:
               if(item.lower() in i.lower()):
                    strikes+=1
          if strikes/len(group)>.5:
               return False
     return True
def analyze(article):
     h = HTMLParser()
     response = u.urlopen(article)
     html = response.read()
     temp = ""
     html = html.decode()
     
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
                    temp2+=html[pos]
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
                         if("https://ap" in tempStr):
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
     fixedTitle = ""
     for i in title:
          if i.lower() in 'abcdefghijklmnopqrstuvwxyz1234567890':
               fixedTitle+=i
          else:
               fixedTitle+=" "
     text_file = open(fixedTitle+".txt", "w")
     for i in arrOfSentences:
           if check_conditions(i):
                 text_file.write(i)
                 text_file.write('\n\n')
     text_file.close()
     print("Analyzed: " + title)
     return siteList

q = 'http://bigstory.ap.org/article/3b2706cb4d3f41e39137b175ff6d0b84/10-things-know-today'
listOfArticles = analyze(q)
for article in listOfArticles:
     analyze(article)
