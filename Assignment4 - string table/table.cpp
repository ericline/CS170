/*!*****************************************************************************
\file    table.cpp
\author  Eric Lin
\par     DP email: eric.lin@digipen.edu
\par     Course: CS170
\par     Programming Assignment #4
\date    03-12-2021

\brief
  This program implements overloaded operators and functions used in 
  manipulating given string tables located in the driver.cpp file.
  
  - operator=
      Assigns one table to another.

  - operator+
      Adds one table to together.

  - operator*
      Tensor product of two tables.

  - operator()
      Getter and setter for all tables.

  - Reverse(pos 1, pos 2)
      Reverses string in table at given positions.
      
  - Reverse(pos)
      Reverses row in table at given position.

  - Reverse()
      Transposes the string table.
      
*******************************************************************************/

#include "table.h"
#include <iomanip>
#include <algorithm> // std::reverse, std::swap

namespace CS170 {

/*!*****************************************************************************
\brief
    Constructor for class Table.

\return 
    N/A
*******************************************************************************/
    Table::Table(unsigned int rows, unsigned int cols)
    {
        Rows_ = rows;
        Cols_ = cols;
        ppData = new std::string* [Rows_]; // pointers to rows
        for (unsigned int i = 0; i < Rows_; i++) 
        {
            ppData[i] = new std::string [Cols_]();  // rows with data
        }  
    }

/*!*****************************************************************************
\brief
    Destructor for class Table.

\return 
    N/A
*******************************************************************************/
    Table::~Table()
    {
        for (unsigned int i=0; i < Rows_; i++) 
        {
            delete [] ppData[i];
        }

        delete[] ppData;
    }

/*!*****************************************************************************
\brief
    Copy constructor for class Table.

\return 
    N/A
*******************************************************************************/
    Table::Table(Table const & rhs)
    {
        Rows_ = 0;
        Cols_ = 0;
        ppData = NULL;

        *this = rhs;
    }

/*!*****************************************************************************
\brief
    Overloaded assignment operator for class Table.

\return 
    Table
*******************************************************************************/
    Table& Table::operator=(Table const & rhs)
    {
        
        if(ppData == rhs.ppData)
        {
            return *this;
        }

        for (unsigned int i=0; i < Rows_; i++) 
        {
            delete [] ppData[i];
        }

        delete[] ppData;

        Rows_ = rhs.Rows_;
        Cols_ = rhs.Cols_;
        ppData = new std::string* [Rows_]; // pointers to rows
        for (unsigned int i = 0; i < Rows_; i++) 
        {
            ppData[i] = new std::string [Cols_]();  // rows with data
        }  

        // Fill table
        unsigned i, j;
        for(i = 0; i < Rows_; i++)
        {
            for(j = 0; j < Cols_; j++)
            {
                ppData[i][j] = rhs.ppData[i][j];
            }
        }

        return *this;
    }

/*!*****************************************************************************
\brief
    Getter and setter function for class Table.

\return 
    ppData at given position r, c.
*******************************************************************************/
    std::string & Table::operator()( unsigned int r, unsigned int c )
    {
        return ppData[r][c];
    }

/*!*****************************************************************************
\brief
    Getter function for class Table.

\return 
    ppData at given position r, c.
*******************************************************************************/
    std::string const & Table::operator () ( unsigned int r, unsigned int c ) const
    {
        return ppData[r][c];
    }

/*!*****************************************************************************
\brief
    Overloaded addition operator for class Table.

\return 
    New Table that is the sum of the two added Tables.
*******************************************************************************/
    Table Table::operator+(Table const & rhs) const
    {
        unsigned int addRows, addCols;

        addRows = Rows_;
        addCols = Cols_;

        if(addRows < rhs.Rows_)
        {
            addRows = rhs.Rows_;
        }

        if(addCols < rhs.Cols_)
        {
            addCols = rhs.Cols_;
        }

        Table temp(addRows, addCols);

        unsigned int r, c;
        for(r = 0; r < addRows; r++)
        {
            for(c = 0; c < addCols; c++)
            {
                if(r < Rows_ && c < Cols_)
                {
                    temp(r, c) += ppData[r][c];
                }

                if(r < rhs.Rows_ && c < rhs.Cols_)
                {
                    temp(r, c) += rhs.ppData[r][c];
                }
            }
        }

        return temp;
    }
/*!*****************************************************************************
\brief
    Overloaded multiplication operator for class Table. Uses the tensor product.

\return 
    New Table that is the tensor product of the two added Tables.
*******************************************************************************/
    Table Table::operator*(Table const & rhs) const
    {
        Table temp(Rows_ * rhs.Rows_, Cols_ * rhs.Cols_);

        unsigned i, j, k, l;
        for(i = 0; i < Rows_; i++)
        {
            for(j = 0; j < Cols_; j++)
            {
                for(k = 0; k < rhs.Rows_; k++)
                {
                    for(l = 0; l < rhs.Cols_; l++)
                    {
                        temp(i * rhs.Rows_ + k, j * rhs.Cols_ + l) = ppData[i][j] + rhs.ppData[k][l];
                    }
                }
            }
        }

        return temp;
    }

/*!*****************************************************************************
\brief
    Overloaded reverse function that reverses the string at position pos1, pos2.

\return 
    void
*******************************************************************************/
    void Table::Reverse(int pos1, int pos2)
    {
        std::reverse(ppData[pos1][pos2].begin(), ppData[pos1][pos2].end());

    }

/*!*****************************************************************************
\brief
    Overloaded reverse function that reverses the row at the given position.

\return 
    void
*******************************************************************************/
    void Table::Reverse(int pos)
    {
        unsigned i;
        for(i = 0; i < Cols_ / 2; i++)
        {
            std::swap(ppData[pos][i], ppData[pos][Cols_ - i - 1]);
        }
    }

/*!*****************************************************************************
\brief
    Overloaded reverse function that transposes the string table, reversing the
    rows and columns.

\return 
    void
*******************************************************************************/
    void Table::Reverse()
    {
        Table temp = *this;
        
        for (unsigned int i = 0; i < Rows_; i++) 
        {
            delete [] ppData[i];
        }

        delete[] ppData;

        std::swap(Rows_, Cols_);

        ppData = new std::string* [Rows_]; // pointers to rows
        for (unsigned int i = 0; i < Rows_; i++) 
        {
            ppData[i] = new std::string [Cols_]();  // rows with data
        }

        unsigned i, j;
        for(i = 0; i < Rows_; i++)
        {
            for(j = 0; j < Cols_; j++)
            {
                ppData[i][j] = temp(j, i);
            }
        }
    }

/*!*****************************************************************************
\brief
    Prints out the the string table.

\return 
    void
*******************************************************************************/
    void Table::Display( std::ostream & os ) const
    {
        for( unsigned int r=0; r<Rows_; ++r ) {
            for( unsigned int c=0; c<Cols_; ++c ) {
                os << ppData[r][c] << " ";
            }
            os << std::endl;
        }
    }

/*!*****************************************************************************
\brief
    Prints out the the string table in a more fancy format.

\return 
    void
*******************************************************************************/
    void Table::Display2( std::ostream & os ) const
    {
        unsigned int* word_length = new unsigned int[Cols_]();

        unsigned i, j;
        std::string horizontal_line;

        for(i = 0; i < Rows_; i++)
        {
            for(j = 0; j < Cols_; j++)
            {
                if(word_length[j] < ppData[i][j].length())
                {
                    word_length[j] = static_cast<unsigned int>(ppData[i][j].length());
                }
            }
        }

        for(i = 0; i < Cols_; i++)
        {
            horizontal_line += '+';
            
            for(j = 0; j < word_length[i] + 2; j++)
            {
                horizontal_line += '-';
            }
        }

        horizontal_line += '+';

        for(i = 0; i < Rows_; i++) 
        {
            os << horizontal_line << std::endl;

            for(j = 0; j < Cols_; j++) 
            {
                os << "| ";
                os << std::setw(static_cast<int>(word_length[j])) << ppData[i][j] << " ";

            }
            os << "|" << std::endl;
        }

        os << horizontal_line << std::endl;

        delete[] word_length;

    }

/*!*****************************************************************************
\brief
    Overloaded print operator.

\return 
    os.
*******************************************************************************/
    std::ostream & operator<<(std::ostream & os, Table const & t)
    {
        // t.Display2( os );   // fancy (see fancy_out* )
        t.Display( os );   // simple (see out* )

        return os;
    }


}
