#include <map>
#include <set>

#ifndef PICTURE_HPP
#define PICTURE_HPP

class Picture{
private:
  std::map <unsigned int, std::set<unsigned int>> picture;
  unsigned int h, w;         //h - wymiar pionowy obrazka, w - wymiar poziomy obrazka

public:
  Picture(unsigned int, unsigned int);
  const Picture operator+(const Picture & picture2) const;
  Picture operator+=(const Picture & picture2);
  const Picture operator*(const Picture & picture2) const;
  Picture operator*=(const Picture & picture2);
  friend std::ostream & operator<<(std::ostream & out, const Picture & picture);
  void flipPixel(unsigned int, unsigned int);
  const bool getPixel(unsigned int, unsigned int);
  const Picture mirrorImage();
  static Picture loadPicture(std::istream & in);
};

#endif
