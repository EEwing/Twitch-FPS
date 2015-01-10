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
   double GetMagnitude() const;

   Vector normalize() const;
   static double dot(Vector, Vector);
   Vector cross(Vector) const;

   // Utility functions
   char  *toString() const;

   // Overloaded operators
   Vector operator+(const Vector&) const;

   Vector operator-(const Vector&) const;

   Vector operator*(const double&) const;

   Vector operator/(const Vector&) const;
   Vector operator/(const double&) const;

};
inline Vector operator*(double s, const Vector &v) {
   return v*s;
}
bool   operator==(const Vector&, const Vector&);
bool   operator!=(const Vector&, const Vector&);

#endif
