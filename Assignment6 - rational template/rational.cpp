/*!*****************************************************************************
\file    rational.cpp
\author  Eric Lin
\par     DP email: eric.lin@digipen.edu
\par     Course: CS170
\par     Programming Assignment #6
\date    04-08-2022

\brief
  This program contains overloaded operators with templates in order to
  manipulate given rationals.
  
  - operator-
      Returns the negative sign of the rational.

  - operator+=, operator-=, operator*=, operator /=        
      Takes a argument rational and performs an operation with it against
      another rational. Returns the rational.

  - operator+, operator-, operator*, operator/
      Takes a argument rational and performs an operation with it against
      another rational. Returns a copy of the final rational.

  - operator<, operator>, operator==, operator<=, operator>=
      Calculates the length (in characters) of a given string first with tabs, 
      and again after tabs have been converted to a given amount of spaces.

  - CheckSign
      Reverses the signs of the numerator and denominator.
      
  - CheckGCD
      Simplifies the given rational using its GCD.

  - GCD
      Performs Euclid's Algorithm on the given rational. Returns the GCD.
      
*******************************************************************************/

#include "rational.h"
#include <iomanip>  // setw
#include <cstdlib>  // abs

namespace CS170 {
    template <typename T> 
    int Rational<T>::width = 0; // no padding by default

/*!*****************************************************************************
\brief
    Default constructor for class Rational.

\return 
    N/A
*******************************************************************************/
    template <typename T> 
    Rational<T>::Rational()               : n(0),  d(1)   {}

/*!*****************************************************************************
\brief
    Conversion from type T to rational.

\return 
    N/A
*******************************************************************************/
    template <typename T> 
    Rational<T>::Rational( T i )        : n(i),  d(1)   {}
 
/*!*****************************************************************************
\brief
   Constructor for class Rational.

\return 
    N/A
*******************************************************************************/
    template <typename T> 
    Rational<T>::Rational(T _n, T _d) : n(_n), d(_d)  { CheckSign(); CheckGCD(); }

/*!*****************************************************************************
\brief
    Returns the negative sign of the rational.

\return 
    Returns the negative sign of the rational.
*******************************************************************************/
    template <typename T>
    Rational<T> Rational<T>::operator-() const
    {
        return Rational(-n, d);
    }

/*!*****************************************************************************
\brief
    Returns the rational after being summed with another rational.

\param
    rhs - right hand side rational.

\return 
    Returns the original rational as the sum of the two rationals.
*******************************************************************************/
    template <typename T>
    Rational<T>& Rational<T>::operator+= (Rational<T> const & rhs)
    {
        *this = *this + rhs;

        CheckGCD();

        return *this;
    }

/*!*****************************************************************************
\brief
    Returns the rational after being subtracted from another rational.

\param
    rhs - right hand side rational.

\return 
    Returns the original rational as the difference of the two rationals.
*******************************************************************************/
    template <typename T>
    Rational<T>& Rational<T>::operator-= (Rational<T> const & rhs)
    {
        *this = *this - rhs;

        CheckGCD();

        return *this;
    }

/*!*****************************************************************************
\brief
    Returns the rational after being multiplied with another rational.

\param
    rhs - right hand side rational.

\return 
    Returns the original rational as the product of the two rationals.
*******************************************************************************/
    template <typename T>
    Rational<T>& Rational<T>::operator*= (Rational<T> const & rhs)
    {
        *this = *this * rhs;

        return *this;
    }

/*!*****************************************************************************
\brief
    Returns the rational after being divided with another rational.

\param
    rhs - right hand side rational.

\return 
    Returns the original rational as the quotient of the two rationals.
*******************************************************************************/
    template <typename T>
    Rational<T>& Rational<T>::operator/= (Rational<T> const & rhs)
    {
        *this = *this / rhs;

        return *this;
    }

/*!*****************************************************************************
\brief
    Returns the sum of two rationals.

\param
    rhs - right hand side rational.

\return 
    Returns the sum of two rationals as a new rational.
*******************************************************************************/
    template <typename T>
    Rational<T> Rational<T>::operator+ (Rational<T> const & rhs) const
    {
        // Variables for the new numerator and denominator
        T new_denom = d * rhs.d;
        T new_num = n * rhs.d + rhs.n * d;

        // Create new Rational with new numerator and denominator
        Rational<T> fraction = Rational(new_num, new_denom);

        // Check GCD
        fraction.CheckGCD();

        return fraction;
    }

/*!*****************************************************************************
\brief
    Returns the difference of two rationals.

\param
    rhs - right hand side rational.

\return 
    Returns the difference of two rationals as a new rational.
*******************************************************************************/
    template <typename T>
    Rational<T> Rational<T>::operator- (Rational<T> const & rhs) const
    {
        Rational<T> fraction = Rational(-rhs.n, rhs.d);

        return *this + fraction;
    }

/*!*****************************************************************************
\brief
    Returns the product of two rationals.

\param
    rhs - right hand side rational.

\return 
    Returns the product of two rationals as a new rational.
*******************************************************************************/
    template <typename T>
    Rational<T> Rational<T>::operator* (Rational<T> const & rhs) const
    {
        Rational<T> fraction = Rational(n * rhs.n, d * rhs.d);
        fraction.CheckGCD();

        return fraction;
    }

/*!*****************************************************************************
\brief
    Returns the quotient of two rationals.

\param
    rhs - right hand side rational.

\return 
    Returns the quotient of two rationals as a new rational.
*******************************************************************************/
    template <typename T>
    Rational<T> Rational<T>::operator/ (Rational<T> const & rhs) const
    {
        Rational<T> fraction = Rational(n * rhs.d, d * rhs.n);
        fraction.CheckGCD();

        return fraction;
    }

/*!*****************************************************************************
\brief
    Compares less than between two rationals.

\param
    op2 - the rational being compared against.

\return 
    Returns true if the first rational is less than the second; false otherwise.
*******************************************************************************/
    template <typename T>
    bool Rational<T>::operator< (Rational<T> const & op2) const 
    { 
        return (n*op2.d < d*op2.n); 
    }

/*!*****************************************************************************
\brief
    Compares greater than between two rationals.

\param
    op2 - the rational being compared against.

\return 
    Returns true if the first rational is greater than the second; false 
    otherwise.
*******************************************************************************/
    template <typename T>
    bool Rational<T>::operator> (Rational<T> const& op2) const
    {
        return (n*op2.d > d*op2.n); 
    }

/*!*****************************************************************************
\brief
    Compares equality between two rationals

\param
    op2 - the rational being compared against.

\return 
    Returns true if the rationals are equal; false otherwise.
*******************************************************************************/
    template <typename T>
    bool Rational<T>::operator== (Rational<T> const& op2) const
    {
        return (n*op2.d == d*op2.n);
    }

/*!*****************************************************************************
\brief
    Compares inequality between two rationals.

\param
    op2 - the rational being compared against.

\return 
    Returns true if the rationals are not equal; false otherwise.
*******************************************************************************/
    template <typename T>
    bool Rational<T>::operator!= (Rational<T> const& op2) const
    {
        return (n*op2.d != d*op2.n);
    }

/*!*****************************************************************************
\brief
    Compares less than or equal to between two rationals

\param
    op2 - the rational being compared against.

\return 
    Returns true if the first rational is less than or equal to the second,
    false otherwise.
*******************************************************************************/
    template <typename T>
    bool Rational<T>::operator<= (Rational<T> const& op2) const
    {
        return (n*op2.d <= d*op2.n);
    }

/*!*****************************************************************************
\brief
    Compares greather than or equal to between two rationals

\param
    op2 - the rational being compared against.

\return 
    Returns true if the first rational is greater than or equal to the second,
    false otherwise.
*******************************************************************************/
    template <typename T>
    bool Rational<T>::operator>= (Rational<T> const& op2) const
    {
        return (n*op2.d >= d*op2.n);
    }

/*!*****************************************************************************
\brief
    Compares greather than or equal to between two rationals

\param
    op2 - the rational being compared against.

\return 
    Returns true if the first rational is greater than or equal to the second,
    false otherwise.
*******************************************************************************/

    template <typename U> 
    std::ostream& operator<<( std::ostream& os, Rational<U> const& r ) 
    {
        os << std::setw( r.width ) << r.n;
        if ( r.d != 1 ) { os << "/" << std::setw( r.width-1 ) << r.d; }
        else            { os <<        std::setw( r.width ) << " "; }
        return os;
    }
    ////////////////////////////////////////////////////////////////////////
    template <typename T> 
    void Rational<T>::CheckSign() 
    {
        if ( d<0 ) { n *= -1; d*= -1; }
    }
    ////////////////////////////////////////////////////////////////////////
    template <typename T> 
    void Rational<T>::CheckGCD() 
    {
        int gcd = GCD();
        n = n/gcd;
        d = d/gcd;
    }
    ////////////////////////////////////////////////////////////////////////
    template <typename T> 
    int Rational<T>::GCD() const 
    {
        int a=std::abs(n), b=std::abs(d);
        while ( a && b ) {
            if ( a < b ) { b = b%a; }
            else         { a = a%b; }
        }
        if ( a==0 ) return b;
        else        return a;
    }
}
