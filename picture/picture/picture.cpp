#include <iostream>
#include <stdexcept>
#include <algorithm>
#include "picture.hpp"
using namespace std;

Picture::Picture(unsigned int height, unsigned int width)
{
    h = height;
    w = width;
    picture[h] = set<unsigned int>();  //ustawienie sentinela poniżej końcowego wiersza obrazka

    //powyższym zapisem gwarantujemy że mapa nigdy nie jest pusta, co ułatwia działanie na niej
}

std::ostream & operator<<(std::ostream & out, const Picture & picture){
    unsigned int current_h = 0;
    auto it = picture.picture.begin();     //ustawienie iteratora na początkowy element mapy
    while ( current_h < picture.h ){       //dopóki nie wychodzimy poza mapę w pionie
      while ( current_h < it->first ){     //dopóki biężący indeks wiersza jest mniejszy od kolejnego indeksu wiersza w mapie
          for ( unsigned int i = 0; i < picture.w; i++ )  out << " ";   //wypisanie czarnych pixeli
          out << "\n" ;                                        //(it->first) oznacza indeks wiersza w mapie
          current_h++;
      }
      if ( current_h == picture.h )  return out;    //wyszliśmy poza obrazek

      // teraz jesteśmy w wierszu, który występuje w mapie
      auto its = it->second.begin();    //iterator its wskazuje początkową pozycję w wierszu w mapie
      unsigned int current_w = 0;
      while ( current_w < picture.w ){  //dopóki nie wyjdziemy poza wiersz (poza set)
        while ( current_w < *its ){     //dopóki indeks bieżącej kolumny jest mniejszy od indeksu kolejnej kolumny w set
            out << " ";                 //wypisanie czarnego pixela
            current_w++;
        }
        if ( current_w == picture.w )  break;  //wyszliśmy poza obrazek
        //biały pixel o współrzędnych current_h i current_w jest w mapie
        out << "*";
        current_w++;
        its++;
      }
      out << "\n";
      current_h++;
      it++;
    }

    return out;
}

//funkcja getPixel zwraca true gdy pixel o podanych wspórzędnych jest biały i false w przeciwnym wypadku
const bool Picture::getPixel(const unsigned int h, const unsigned int w){
  if ( h >= this->h || w >= this->w ) throw std::out_of_range("Pixel poza obrazkiem!");
  auto it = this->picture.find(h);
  if ( it == this->picture.end() )  return false;
  auto its = it->second.find(w);
  if ( its == it->second.end() )  return false;

  return true;
}

void Picture::flipPixel(const unsigned int h, const unsigned int w){
  if ( h >= this->h || w >= this->w ) throw std::out_of_range("Pixel poza obrazkiem!");
  auto it = this->picture.find(h);
  if ( it == this->picture.end() ){
    it = this->picture.insert(std::pair<unsigned int, set<unsigned int>>
                                      (h, set<unsigned int>({this->w}))).first;  //ustawienie sentinela na końcu wiersza
  }
  auto its = it->second.find(w);   //szukamy podanej pozycji w wierszu
  if ( its == it->second.end() ) {
    it->second.insert(w);          //takiej pozycji nie ma, więc trzeba ją stworzyć, żeby z pixela czarnego zrobić biały
  } else {
    it->second.erase(w);           //taka pozycja jest, więc usuwamy ją, by z białego pixela zrobić czarny
    if ( it->second.size() == 1 )  picture.erase(it);   //nie ma już białych pixeli w tym wierszu, więc usuwamy wiersz
  }
}

const Picture Picture::operator+( const Picture & picture2 ) const {
  Picture resultedPicture(*this);
  resultedPicture += picture2;
  return resultedPicture;
}

const Picture Picture::operator*( const Picture & picture2 ) const {
  Picture resultedPicture(*this);
  resultedPicture *= picture2;
  return resultedPicture;
}

Picture Picture::operator+=( const Picture & picture2 ) {
  auto it1 = this->picture.begin();
  auto it2 = picture2.picture.begin();

  if ( this->h != picture2.h || this->w != picture2.w )
      throw std::out_of_range("Operacja sumy obrazkow niemozliwa, bo mają one rozne wymiary!");

  while ( it1->first < this->h ){         //dopóki nie wyjdziemy poza p1 w pionie
    while ( it2->first < it1->first ){    //dopóki wiersza o takim indeksie nie ma w p1
      this->picture[it2->first] = it2->second;
      it2++;
    }
    if ( it2->first == it1->first ){
      it1->second.insert(it2->second.begin(), it2->second.end());   //połączenie wierszy o tym samym nr
      it2++;
    }
    it1++;
  }

  return *this;
}

Picture Picture::operator*=( const Picture & picture2 ) {
  auto it1 = this->picture.begin();
  auto it2 = picture2.picture.begin();

  if ( this->h != picture2.h || this->w != picture2.w )
      throw std::out_of_range("Operacja iloczynu obrazkow niemozliwa, bo mają one rozne wymiary!");

  while ( it1->first < this->h ){                  //dopóki nie wyjdziemy poza p1 w pionie
    while ( it2->first < it1->first ) it2++;       //dopóki wiersza o takim indeksie nie ma w p1
    if ( it2->first == it1->first ){               //wiersz o tym samym nr w p1 i p2
      std::set<unsigned int> intersection;         //set zastępczy
      //przecięcie
      set_intersection(it1->second.begin(),it1->second.end(),it2->second.begin(),it2->second.end(),
                       std::inserter(intersection,intersection.begin()));
      this->picture[it1->first] = intersection;    //wstawienie nowego set

      it1++;
    } else {
      it1 = this->picture.erase(it1);
    }
  }

  return *this;
}

//odbicie lustrzane względem osi pod obrazkiem
const Picture Picture::mirrorImage(){
  Picture resultedPicture(this->h, this->w);

  for ( auto it : this->picture ) {           //iteracja po mapie
    if ( it.first == this->h )  break;
    resultedPicture.picture[this->h - 1 -it.first] = it.second;
  }
  resultedPicture.picture[this->h] = this->picture[h];

  return resultedPicture;
}

Picture Picture::loadPicture(std::istream & in){
  unsigned int h, w;
  in >> h >> w;         //pobranie wymiarów obrazka
  in.get();             //wczytanie znaku końca linii
  Picture p1( h, w );
  for ( unsigned int i = 0; i < h; i++ ) {
    string s;
    std::getline(in, s);
    if ( s.size() != w )  throw "Ilosc wczytanych znakow nie zgadza się z wymiarem poziomym obrazka";
    for ( unsigned int j = 0; j < w; j++ ) {
        if ( s[j] == '*' )  p1.flipPixel(i,j);
    }
  }

  return p1;
}