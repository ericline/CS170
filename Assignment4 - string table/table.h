#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <fstream>
#include <iostream>

namespace CS170 {
    class Table {

        // Table rows and columns
        unsigned int Rows_;
        unsigned int Cols_;

        std::string **ppData;

        public:
        Table(unsigned int rows, unsigned int cols);
        ~Table();
        Table(Table const & rhs);

        Table operator+(Table const & rhs) const;
        Table& operator=(Table const & rhs);
        Table operator*(Table const & rhs) const;
        void Reverse(int pos1, int pos2);
        void Reverse(int pos);
        void Reverse();


        // getter and setter (overloaded similar to operator[] from notes)
        std::string       & operator () ( unsigned int r, unsigned int c );
        std::string const & operator () ( unsigned int r, unsigned int c ) const;

        // Display functions
        void Display( std::ostream & os ) const;    // provided
        void Display2( std::ostream & os ) const;   // fancy    (10% of your grade)
    };

    std::ostream & operator<<( std::ostream & os, Table const& t );
}
#endif
