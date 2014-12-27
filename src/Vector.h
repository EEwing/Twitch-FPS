#ifndef VECTOR_H
#define VECTOR_H

#include <string>

class Vector {
  public:
   // Components
   double x, y, z;

   // Constructors
          Vector(double x, double y, double z);
          Vector(const Vector &);
          Vector(double *);
          Vector();

   // Class functions
   double GetMagnitude();

   Vector normalize();
   double dot(Vector);
   Vector cross(Vector);

   // Utility functions
   char  *toString();

   // Overloaded operators
   Vector operator+(const Vector&);

   Vector operator-(const Vector&);

   Vector operator*(const Vector&);
   Vector operator*(const double&);

   Vector operator/(const Vector&);
   Vector operator/(const double&);

   Vector operator%(const double&);
};

#endif
