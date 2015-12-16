#ifndef SHAPE_HPP
#define SHAPE_HPP

/*
  Shape has no texture
 */
class Shape {
public:
  //just draw the item at the origin point
  //the caller is resposible for setup matrix, texture, etc.
  virtual void draw() const  = 0;
};

#endif
