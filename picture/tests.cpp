#include <iostream>
#include <cassert>
#include "picture/picture.hpp"
using namespace std;

void flipPixel_test() {  //test wstawienia pojedynczego pixela
  Picture p1(20,20);
  p1.flipPixel(10,10);

  for ( int h = 0; h < 20; h++ ) {
      for ( int w = 0; w < 20; w++ ){
          if ( w == 10 && h == 10 )   assert ( p1.getPixel(h, w) );
          else                        assert ( !p1.getPixel(h, w) );
      }
  }
}

void flipPixelTwice_test(){         //test podmiany tego samego pixela dwa razy
    Picture p1(20,20);

    p1.flipPixel(10,10);
    for ( int h = 0; h < 20; h++ ) {
        for (int w = 0; w < 20; w++) {
            if (w == 10 && h == 10) assert (p1.getPixel(h, w));
            else
                assert (!p1.getPixel(h, w));
        }
    }

    p1.flipPixel(10,10);
    for ( int h = 0; h < 20; h++ ) {
        for (int w = 0; w < 20; w++) {
            if (w == 10 && h == 10) assert (!p1.getPixel(h, w));
            else
                assert (!p1.getPixel(h, w));
        }
    }
}

void flipDiagonal_test() {         //test wstawienia pixeli na przekątnej
  Picture p1(20,20);
   for ( int h = 0; h < 20; h++ ) {
     p1.flipPixel(h, 19 - h);
   }

   for ( int h = 0; h < 20; h++ ) {
     for ( int w = 0; w < 20; w++ ){
       if ( w == 19 - h )   assert ( p1.getPixel(h, w) );
       else                 assert ( !p1.getPixel(h, w) );
     }
   }
}

void sumDiagonals_test() {             //test sumy dwóch obrazków (2 przekątnych)
    Picture p1(21, 21);
    Picture p2(21, 21);
    Picture resultedPicture(21, 21);

    for ( int h = 0; h < 21; h++ ) {
        p1.flipPixel(h, 20 - h);
    }
    for ( int h = 0; h < 21; h++ ) {
        p2.flipPixel(h, h);
    }
    resultedPicture = p1 + p2;

    for ( int h = 0; h < 21; h++ ) {
        for ( int w = 0; w < 21; w++ ){
            if ( w == 20 - h )  assert ( resultedPicture.getPixel(h, w) );
            else if ( w == h )  assert ( resultedPicture.getPixel(h, w) );
            else                assert ( !resultedPicture.getPixel(h, w) );
        }
    }
}

void sumEmptyPictures_test() {           //test sumy pustych obrazków
    Picture p1(21, 21);
    Picture p2(21, 21);
    Picture resultedPicture(21, 21);

    resultedPicture = p1 + p2;

    for ( int h = 0; h < 21; h++ ) {
        for ( int w = 0; w < 21; w++ ){
            assert ( !resultedPicture.getPixel(h,w) );
        }
    }
}

void multiplicationDiagonals_test() {     //test iloczynu dwóch obrazków (2 przekątnych)
    Picture p1(21, 21);
    Picture p2(21, 21);
    Picture resultedPicture(21, 21);

    for ( int h = 0; h < 21; h++ ) {
        p1.flipPixel(h, 20 - h);
    }
    for ( int h = 0; h < 21; h++ ) {
        p2.flipPixel(h, h);
    }
    resultedPicture = p1 * p2;

    for ( int h = 0; h < 21; h++ ) {
        for ( int w = 0; w < 21; w++ ) {
            if ( h == 10 && w == 10 )  { assert ( resultedPicture.getPixel(h, w) ); }
            else                       { assert ( !resultedPicture.getPixel(h, w) ); }
        }
    }
}

void multiplicationEmptyPictures_test() {           //test iloczynu dwóch pustych obrazków
    Picture p1(21, 21);
    Picture p2(21, 21);
    Picture resultedPicture(21, 21);

    resultedPicture = p1 * p2;

    for ( int h = 0; h < 21; h++ ) {
        for ( int w = 0; w < 21; w++ ){
            assert ( !resultedPicture.getPixel(h,w) );
        }
    }
}

void mirrorDiagonal_test(){               //test odbicia lustrzanego (przekątnej)
    Picture p1(21, 21);
    Picture mirrorPicture(21, 21);

    for ( int h = 0; h < 21; h++ ) {
        p1.flipPixel(h, 20 - h);
    }
    mirrorPicture = p1.mirrorImage();

    for ( int h = 0; h < 21; h++ ) {
        for ( int w = 0; w < 21; w++ ) {
            if ( h == w )  assert ( mirrorPicture.getPixel(h, w) );
            else           assert ( !mirrorPicture.getPixel(h, w) );
        }
    }
}

void mirrorPicture_test() {             //test odbicia lustrzanego
    unsigned int h, w;
    Picture p1(21, 21);
    Picture mirrorPicture(21, 21);

    h = 0;
    for ( w = 0; w < 21; w++ ) {
        p1.flipPixel(h, w);
    }
    for ( h = 1; h < 21; h++ ) {
        p1.flipPixel(h, 0);
        p1.flipPixel(h, 20);
    }

    mirrorPicture = p1.mirrorImage();

    for ( int h = 0; h < 21; h++ ) {
        for ( int w = 0; w < 21; w++ ) {
            if ( h == 20 )  assert( mirrorPicture.getPixel(h, w) );
            else if ( (w == 0 || w == 20) && h != 20 ) assert ( mirrorPicture.getPixel(h, w) );
            else   assert ( !mirrorPicture.getPixel(h,w) );
        }
    }
}

void mirrorEmptyPicture_test(){               //test odbicia lustrzanego pustego obrazka
    Picture p1(21, 21);
    Picture mirrorPicture(21, 21);

    mirrorPicture = p1.mirrorImage();

    for ( int h = 0; h < 21; h++ ) {
        for ( int w = 0; w < 21; w++ ) {
            assert ( !mirrorPicture.getPixel(h, w) );
        }
    }
}

int main(){
  cout << "TEST 1 -> FLIP_PIXEL_TEST\n";
  flipPixel_test();

  cout << "\nTEST 2 -> FLIP_PIXEL_TWICE_TEST\n";
  flipPixelTwice_test();

  cout << "\nTEST 3 -> FLIP_DIAGONAL_TEST\n";
  flipDiagonal_test();

  cout << "\nTEST 4 -> SUM_DIAGONALS_TEST\n";
  sumDiagonals_test();

  cout << "\nTEST 5 -> SUM_EMPTY_PICTURES_TEST\n";
  sumEmptyPictures_test();

  cout << "\nTEST 6 -> MULTIPLICATION_DIAGONALS_TEST\n";
  multiplicationDiagonals_test();

  cout << "\nTEST 7 -> MULTIPLICATION_EMPTY_PICTURES_TEST\n";
  multiplicationEmptyPictures_test();

  cout << "\nTEST 8 -> MIRROR_DIAGONAL_TEST\n";
  mirrorDiagonal_test();

  cout << "\nTEST 9 -> MIRROR_PICTURE_TEST\n";
  mirrorPicture_test();

  cout << "\nTEST 10 -> MIRROR_EMPTY_PICTURE_TEST\n";
  mirrorEmptyPicture_test();

  return 0;
}
