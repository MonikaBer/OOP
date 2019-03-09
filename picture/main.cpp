#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "picture/picture.hpp"
#include "dec.hpp"
using namespace std;


int main(int argc, char** argv){
  if ( argc != 2 ) {
      cout << "usage: ./pixels ./resources\n";
      return 1;
  }

  std::vector <Picture> pictures;
  Picture p(21, 21);
  string number;
  for ( int i = 1; i <= 5; i++ ) {
      number = to_string(i);
      std::ifstream ifs (string(argv[1]) + "/p" + number + ".txt");
      p = Picture::loadPicture(ifs);
      pictures.push_back( p );
  }

  int choice, nr, nr2, h, w;
  while (1) {
    menu();
    cin >> choice;
    switch (choice) {
      case 1:
          nr = pictureChoice();
          cout << pictures[nr-1];
          break;
      case 2:
          nr = pictureChoice();
          cout << "\nPodaj wspolrzedne pixela (pionowa wsp. -> 0 - 20, pozioma wsp. -> 0 - 20): ";
          cin >> h >> w;
          try {
              if (pictures[nr - 1].getPixel(h, w)) cout << "\n'*' - bialy pixel";
              else cout << "\n' ' - czarny pixel";
          } catch (out_of_range &e) {
              cout << "Pixel poza obrazkiem.";
          }
          break;
      case 3:
          nr = pictureChoice();
          cout << "\nPodaj wspolrzedne pixela (pionowa wsp. -> 0 - 20, pozioma wsp. -> 0 - 20): ";
          cin >> h >> w;
          try {
              pictures[nr - 1].flipPixel(h, w);
          } catch (out_of_range &e) {
              cout << "Pixel poza obrazkiem.";
          }
          break;
      case 4:
          nr = pictureChoice();
          nr2 = pictureChoice();
          cout << "\n\nWybranie obrazki po sumie logicznej:\n" << pictures[nr-1] + pictures[nr2-1];
          break;
      case 5:
          nr = pictureChoice();
          nr2 = pictureChoice();
          cout << "\n\nWybranie obrazki po iloczynie logicznym:\n" << pictures[nr-1] * pictures[nr2-1];
          break;
      case 6:
          nr = pictureChoice();
          cout << pictures[nr-1];
          cout << "---------------------\n";
          cout << pictures[nr-1].mirrorImage();
          break;
      case 7:
          cout << "\n\nKONIEC PROGRAMU\n\n";
          return 0;
      default:
          cout << "\nNiepoprawny wybor. Wybierz jeszcze raz: ";
          cin >> choice;
          break;
    }
    cout << flush;
  }
}