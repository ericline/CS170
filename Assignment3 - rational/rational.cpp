/*!*****************************************************************************
\file    rational.cpp
\author  Eric Lin
\par     DP email: eric.lin@digipen.edu
\par     Course: CS170
\par     Programming Assignment #3
\date    02-14-2021

\brief
  This program takes implements overloaded operators used in manipulating given
  rationals located in the driver.cpp file.
  
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
#include <iomanip>  // std::setw

namespace CS170 {

    int Rational::width = 0; // no padding by default

/*!*****************************************************************************
\brief
   Constructor for class Rational.

\return 
    N/A
*******************************************************************************/
    Rational::Rational(): n(0),  d(1)   
    {

    }
/*!*****************************************************************************
\brief
   Conversion from int to rational.

\return 
    N/A
*******************************************************************************/
    Rational::Rational( int i ): n(i),  d(1)   
    {

    }
/*!*****************************************************************************
\brief
   Constructor for class Rational.

\return 
    N/A
*******************************************************************************/
    Rational::Rational(int _n, int _d) : n(_n), d(_d)  
    { 
        CheckSign(); 
        CheckGCD(); 
    }
/*!*****************************************************************************
\brief
   Returns the negative sign of the rational.

\return 
    Returns the negative sign of the rational.
*******************************************************************************/
    Rational Rational::operator- () const 
    { 
        return Rational(-n,d);

    }
/*!*****************************************************************************
\brief
   Overloaded operators for +, -, *, /, +=, -=, *=, /=.

\param
   The other rational being tested against.

\return 
    Returns the final rational after the given operation.
*******************************************************************************/
    Rational& Rational::operator+= (Rational const & rhs)
    {
        *this = *this + rhs;

        CheckGCD();

        return *this;
    }

    Rational& Rational::operator-= (Rational const & rhs)
    {
        *this = *this - rhs;

        CheckGCD();

        return *this;
    }

    Rational& Rational::operator*= (Rational const & rhs)
    {
        // Multiple the fractions together
        n *= rhs.n;
        d *= rhs.d;

        CheckGCD();

        return *this;
    }

    Rational& Rational::operator/= (Rational const & rhs)
    {
        // Multiple the fraction of the first by the inverse of the second
        n *= rhs.d;
        d *= rhs.n;
        CheckGCD();

        return *this;
    }

    Rational Rational::operator+ (Rational const & rhs) const
    {
        // Variables for the new numerator and denominator
        int new_num;
        int new_denom;

        // Calculate new denominator
        new_denom = d * rhs.d;

        // Calculate new numerators
        new_num = n * rhs.d + rhs.n * d;

        // Create new Rational with new numerator and denominator
        Rational fraction = Rational(new_num, new_denom);

        // Check GCD
        fraction.CheckGCD();

        return fraction;
    }

    Rational Rational::operator- (Rational const & rhs) const
    {
        Rational fraction = Rational(-rhs.n, rhs.d);

        return *this + fraction;
    }

    Rational Rational::operator* (Rational const & rhs) const
    {
        Rational fraction = Rational(n * rhs.n, d * rhs.d);
        fraction.CheckGCD();

        return fraction;
    }

    Rational Rational::operator/ (Rational const & rhs) const
    {
        Rational fraction = Rational(n * rhs.d, d * rhs.n);
        fraction.CheckGCD();

        return fraction;
    }


/*!*****************************************************************************
\brief
   Overloaded operators for <, >, ==, !=, <=, >=.

\param op2
   The other rational being tested against.

\return 
    Returns the true if the the statement is true, false otherwise.
*******************************************************************************/
    bool Rational::operator< (Rational const & op2) const 
    { 
        return (n*op2.d < d*op2.n); 
    }

    bool Rational::operator> (Rational const& op2) const
    {
        return (n*op2.d > d*op2.n); 
    }

    bool Rational::operator== (Rational const& op2) const
    {
        return (n*op2.d == d*op2.n);
    }

    bool Rational::operator!= (Rational const& op2) const
    {
        return (n*op2.d != d*op2.n);
    }

    bool Rational::operator<= (Rational const& op2) const
    {
        return (n*op2.d <= d*op2.n);
    }

    bool Rational::operator>= (Rational const& op2) const
    {
        return (n*op2.d >= d*op2.n);
    }



    ////////////////////////////////////////////////////////////////////////
    std::ostream& operator<<( std::ostream& os, Rational const& r ) 
    {
        os << std::setw( r.width ) << r.n;
        if ( r.d != 1 ) { os << "/" << std::setw( r.width-1 ) << r.d; }
        else            { os <<        std::setw( r.width ) << " "; }
        return os;
    }
    ////////////////////////////////////////////////////////////////////////
    void Rational::CheckSign() 
    {
        if ( d<0 ) { n *= -1; d*= -1; }
    }
    ////////////////////////////////////////////////////////////////////////
    void Rational::CheckGCD() 
    {
        int gcd = GCD();
        n = n/gcd;
        d = d/gcd;
    }
    ////////////////////////////////////////////////////////////////////////
    // Euclid's algorithm
    // Returns greatest common divisor
    int Rational::GCD() const 
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
