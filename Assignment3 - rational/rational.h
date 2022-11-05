#ifndef RATIONAL_H
#define RATIONAL_H
#include <fstream>  // std::fstream
#include <cstdlib>  // std::abs

namespace CS170 {
    class Rational {
        private:
            int n,d;
            static int width; // used by stream insertion, do not change
            ////////////////////////////////////////////////////////////////////////
            void CheckSign();
            void CheckGCD();
            int  GCD() const;
        public:

            Rational();
            Rational( int i );
            Rational(int _n, int _d);

            int numerator() const { return n; }

            int denominator() const { return d; }

            // set width for 
            static void Width( int w );

            ////////////////////////////////////////////////////////////////////////
            friend std::ostream& operator<<( std::ostream& os, Rational const& r );

            // unary negate
            Rational operator- () const;
            
            Rational& operator+= (Rational const & rhs);
            Rational& operator-= (Rational const & rhs);
            Rational& operator*= (Rational const & rhs);
            Rational& operator/= (Rational const & rhs);

            Rational operator+ (Rational const & rhs) const;
            Rational operator- (Rational const & rhs) const;
            Rational operator* (Rational const & rhs) const;
            Rational operator/ (Rational const & rhs) const;    



            ////////////////////////////////////////////////////////////////////////
            // comparisons
            bool operator<  (Rational const& op2) const;

            bool operator>  (Rational const& op2) const;
            bool operator== (Rational const& op2) const;
            bool operator!= (Rational const& op2) const;
            bool operator<= (Rational const& op2) const;
            bool operator>= (Rational const& op2) const;
            ////////////////////////////////////////////////////////////////////////

    };
}
#endif
