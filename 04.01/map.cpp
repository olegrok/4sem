#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <functional>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <iterator>
#include <locale.h>
#include <locale>
#include <boost/locale.hpp>
#include <boost/locale/generator.hpp>

struct Word{
  std::string word;
  int freq;

  Word(std::string&);
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
  friend class dicIter;
public:
  Dictionary(){};
  Dictionary(const Dictionary& dic);
  ~Dictionary(){};
  Dictionary& operator=(const Dictionary& dic)
  {
    vec = dic.vec;
    return *this;
  }

  void insert(std::string &);
  void insert(std::string &&);
  void insert(std::vector<std::string> &);
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

Word::Word(std::string& str){
  word.resize(str.size());
  std::transform(str.begin(), str.end(), word.begin(), tolower);
  //word = str;
  freq = 1;
}

Word::Word(const Word& wd)
{
  word = wd.word;
  freq = wd.freq;
}

void Dictionary::insert(std::string &str){
  Word w(str);
  auto it = std::find_if(vec.begin(), vec.end(), bind1st(std::equal_to<Word>(),w));
  if(it != vec.end())
    it->freq++;
  else
    vec.push_back(Word(str));
}

void Dictionary::insert(std::string &&move){
  std::string str;
  std::swap(str, move);
  insert(str);
}

void Dictionary::insert(std::vector<std::string> &vec){
  for(auto i : vec){
    if(i != "")
      insert(i);
    }
}

void Dictionary::show(Word wd)
{
  std::cout << wd.word << "\t\t\t" << wd.freq << std::endl;
}

void Dictionary::stat(){
  std::for_each(vec.begin(), vec.end(), show);
}

void Dictionary::fileLoad(std::string filename){
  std::ifstream F;
  F.open(filename, std::ios::in);
  std::string str;
  std::vector<std::string> vecStr;
  //auto it = std::back_insert_iterator< std::vector<std::string> >(vecStr);
  while(!F.eof()){
    F >> str;
    boost::split(vecStr, str, boost::bind(!boost::is_alnum(), _1));
    insert(vecStr);
  }

  F.close();
}

void Dictionary::sort(){
  std::sort(vec.begin(), vec.end(), _cmp);
}

class dicIter : public std::iterator<std::output_iterator_tag, Dictionary>{
  explicit dicIter(Dictionary& dic);
  dicIter& operator*(){

  }
};


int main()
{
  setlocale(LC_ALL, "");
  std::locale::global(std::locale("ru_RU.UTF-8"));
  std::locale utf8_locale("ru_RU.UTF-8");
  std::locale::global(utf8_locale);

  //std::cout << std::endl << setlocale(LC_ALL, "ru_RU.UTF-8");
  Dictionary dic;
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
