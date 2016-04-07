#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <functional>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>

struct Word{
  std::string word;
  int freq;

  Word(std::string);
  ~Word(){};
  Word(const Word& w);
  Word& operator=(const Word& w)
  {
    word = w.word;
    freq = w.freq;
    return *this;
  }

  bool operator==(const Word& w) const
  {
    return (word == w.word);
  }
};

class Dictionary{
public:
  Dictionary(){};
  Dictionary(const Dictionary& dic);
  ~Dictionary(){};
  Dictionary& operator=(const Dictionary& dic)
  {
    vec = dic.vec;
    return *this;
  }

  void insert(std::string);
  void stat();
  void fileLoad(std::string);
  void sort();

private:
  std::vector<Word> vec;
  static void show(Word);
  static bool _cmp(Word a, Word b){
    return (a.freq > b.freq);
  }
};

Word::Word(std::string str){
  std::transform(str.begin(), str.end(), str.begin(), tolower);
  word = str;
  freq = 1;
}

Word::Word(const Word& wd)
{
  word = wd.word;
  freq = wd.freq;
}

void Dictionary::insert(std::string str){
  Word w(str);
  auto it = std::find_if(vec.begin(), vec.end(), bind1st(std::equal_to<Word>(),w));
  if(it != vec.end())
    it->freq++;
  else
    vec.push_back(Word(str));
}

void Dictionary::show(Word wd)
{
  std::cout << wd.word << "\t" << wd.freq << std::endl;
}

void Dictionary::stat(){
  std::for_each(vec.begin(), vec.end(), show);
}

void Dictionary::fileLoad(std::string filename){
  std::ifstream F;
  F.open(filename, std::ios::in);
  std::vector<std::string> vecStr;
  std::string strBuf;
  while(!F.eof()){
    F >> strBuf;
    vecStr.push_back(strBuf);
  }

  std::vector<std::string> strs;
  std::vector<std::string> strsBuf;
  for(auto it = vecStr.begin(); it != vecStr.end(); it++){
    boost::split(strsBuf,*it,boost::is_any_of("\t\n;!,.&?\"\':()[]*-"));
    for(auto it2 = strsBuf.begin(); it2 != strsBuf.end(); it2++){
        if(!(*it2).empty())
        strs.push_back(*it2);
    }
  }

  for(auto it = strs.begin(); it != strs.end(); it++)
    insert(*it);
  F.close();
}

void Dictionary::sort(){
  std::sort(vec.begin(), vec.end(), _cmp);
}

int main()
{
  Dictionary dic;
  dic.insert("proga");
  dic.insert("proga");
  dic.insert("proga");
  dic.insert("proga");
  dic.insert("infa");
  dic.insert("infa");
  dic.insert("Infa");
  dic.stat();
  dic.insert("proga");
  dic.insert("proga");
  dic.insert("proga");
  dic.insert("proga");
  dic.insert("infa");
  dic.insert("infa");
  dic.insert("infa123");
  dic.insert("infa15");
  dic.fileLoad("book.txt");
  dic.sort();
  dic.stat();

  /*int max = 15;
  std::vector<int> vec;
  for(int i = 0; i < max; i++)
    vec.push_back(rand() % max);
  vec.push_back(10);
  sort(vec.begin(), vec.end(), cmp);
  for_each(vec.begin(), vec.end(), print);
  //std::cout << vec.back() << std::endl;
  //vec.pop_back();
  //std::cout << "Hello, World!" << std::endl;*/
  return 0;
}
