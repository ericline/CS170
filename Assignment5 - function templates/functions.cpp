/*!*****************************************************************************
\file    functions.cpp
\author  Eric Lin
\par     DP email: eric.lin@digipen.edu
\par     Course: CS170
\par     Programming Assignment #5
\date    03-21-2021

\brief
  This program includes functions used to manipulate arrays and ranges 
  using templates.
  
  - display
      Prints an array from the given beginning to end.

  - swap
      Swaps two pointers

  - min_element
      Returns pointer to the smallest element.

  - max_element
      Returns pointer to the largest element.

  - swap_ranges
      Swaps two ranges.
      
  - remove
      Removes specified value from the range.

  - fill
      Overwrites all elements in the range with a given value.

  - count
      Counts all elements in the given range with a given value.

  - sum
      Adds all elements of the array together.

  - copy
      Copys all elements from one range to another.

  - equal
      Determines if two ranges are equal.

  - replace
      Replace all the elements in the array with the given value.
    
  - find
      Returns a pointer to the first element with the given value.
      
*******************************************************************************/
#include <iostream>
#include "functions.h"

namespace CS170 
{
/*!*****************************************************************************
\brief
    Prints out an array within the given range.

\param begin
    Pointer to the start of array.

\param end
    Pointer to end of array.

\return 
    void
*******************************************************************************/
  template <typename T>
    void display( T const *begin, T const *end )
    {
      if( begin != end ) std::cout << *begin++;
      while( begin<end ) {
        std::cout << ", " << *begin;
        ++begin;
      }
      std::cout << std::endl;
    }

/*!*****************************************************************************
\brief
    Swaps two pointers

\param left
    First argument.

\param end
    Second argument.

\return 
    void
*******************************************************************************/
  template <typename T>
    void swap( T *left, T *right )
    {
      T temp( *right );
      ( *right ) = ( *left );
      ( *left ) = temp;
    }

/*!*****************************************************************************
\brief
    Returns pointer to smallest element.

\param begin
    Pointer to the start of array.

\param end
    Pointer to end of array.

\return 
    Pointer to smallest array.
*******************************************************************************/
  template <typename T>
    T* min_element( T *begin, T *end )
    {
      T* min=begin;
      while( begin!=end ) {
        if( *begin<*min ) min=begin;
        ++begin;
      }
      return min;
    }

/*!*****************************************************************************
\brief
    Returns pointer to smallest element.

\param begin
    Pointer to the start of array.

\param end
    Pointer to end of array.

\return 
    Pointer to smallest array.
*******************************************************************************/
  template <typename T>
    T const* min_element( T const *begin, T const *end )
    {
      T const* min=begin;
      while( begin!=end ) {
        if( *begin<*min ) min=begin;
        ++begin;
      }
      return min;
    }

/*!*****************************************************************************
\brief
    Returns pointer to largest element.

\param begin
    Pointer to the start of array.

\param end
    Pointer to end of array.

\return 
    Pointer to largest array.
*******************************************************************************/
  template <typename T>
    T* max_element(T *begin, T *end)
    {
        T *max = begin;
        while(begin != end)
        {
            if(*begin > *max)
            max = begin;

            begin++;
        }
        return max;
    }

/*!*****************************************************************************
\brief
    Returns pointer to largest element.

\param begin
    Pointer to the start of array.

\param end
    Pointer to end of array.

\return 
    Pointer to largest array.
*******************************************************************************/
  template <typename T>
    T const* max_element(T const *begin, T const *end)
    {
        T const *max = begin;
        while(begin != end)
        {
            if(*begin > *max)
            max=begin;

            begin++;
        }
        return max;
    }

/*!*****************************************************************************
\brief
    Swaps two ranges.

\param r1
    Pointer to the start of the first array.

\param end
    Pointer to end of first array.

\param r2
    Pointer to second array.

\return 
    void
*******************************************************************************/
  template <typename T>
    void swap_ranges(T *r1, T *end, T *r2)
    {
        while(r1 != end)
        {
            swap(r1, r2);

            ++r1;
            ++r2;
        }
    }

/*!*****************************************************************************
\brief
    Removes all occurances of a given value in a specific range.

\param begin
    Pointer to the start of array.

\param end
    Pointer to end of array.

\param item
    Value to be removed.

\return 
    Pointer to end of new range without removed values.
*******************************************************************************/
  template <typename T>
    T* remove(T *begin, T *end, T item)
    {
        {
        T *found_block = begin;
        T *new_begin = begin;
        T *previous = begin;

        found_block = find(begin, end, item);

        while(found_block != end)
        {
            new_begin = begin;

            while(new_begin != end)
            {
                previous = new_begin;
                ++new_begin;
            }

            swap(found_block, previous);
            end = previous;

            new_begin = found_block;
            previous = found_block;

            if(new_begin != end)
            {
                ++new_begin;
                while(new_begin != end)
                {
                    swap(new_begin, previous);
                    previous = new_begin;

                    ++new_begin;   
                }
            }

            found_block = find(begin, end, item);
        }
        
        return end;
    }

/*!*****************************************************************************
\brief
    Overwrite all elements in the range with a given value.

\param begin
    Pointer to the start of array.

\param end
    Pointer to end of array.

\param value
    Value to be filled in.

\return 
    Pointer to largest array.
*******************************************************************************/
  template <typename T>
    void fill(T *begin, T *end, T value)
    {
        while(begin != end)
        {
            *begin = value;

            ++begin;
        }
    }

/*!*****************************************************************************
\brief
    Returns the number of occurances of a given value in a range.

\param begin
    Pointer to the start of array.

\param end
    Pointer to end of array.

\param value
    Value to be counted.

\return 
    Integer value of number of occurances.
*******************************************************************************/
  template <typename T>
    int count(T *begin, T *end, T value)
    {
        int count = 0;
        while(begin != end) // run through array
        {
            if(*begin == value) // if the value is the value
            count++;            // increment count
            
            ++begin;
        }

        return count;   // return total count
    }

/*!*****************************************************************************
\brief
    Determines the sum of all elements in the range.

\param begin
    Pointer to the start of array.

\param end
    Pointer to end of array.

\return 
    Type T sum of all elements.
*******************************************************************************/
  template <typename T>
    T sum(T *begin, T *end)
    {
        T sum = T();
        while(begin != end)
        {
            sum += *begin;

            ++begin;
        }

        return sum;
    }

/*!*****************************************************************************
\brief
    Copys all elements from one range to another.

\param r1
    Pointer to the start of the first array.

\param end
    Pointer to end of first array.

\param r2
    Pointer to second newly copied array.

\return 
    Pointer to the second array.
*******************************************************************************/
  template <typename T, typename N>
    N* copy(const T *r1, const T *end, N *r2)
    {
        while(r1 != end)
        {
            *r2 = *r1;

            ++r1;
            ++r2;
        }

        return r2;
    }

/*!*****************************************************************************
\brief
    Determines whether two ranges are equal.

\param r1
    Pointer to the start of the first array.

\param end
    Pointer to end of first array.

\param r2
    Pointer to second array.

\return 
    True if both ranges are equal, false otherwise.
*******************************************************************************/
  template <typename T, typename N>
    bool equal(T *r1, T *end, N *r2)
    {
        while(r1 != end)
        {
            if(*r1 != *r2)
            {
                return false;
            }
            ++r1;
            ++r2;
        }

        return true;
    }

/*!*****************************************************************************
\brief
    Finds and replaces an old value with a new value on a given range.

\param begin
    Pointer to the start of the array.

\param end
    Pointer to end of the array.

\param old_item
    Value to be replaced.

\param new_item
    Value to be replacement.

\return 
    void
*******************************************************************************/
  template <typename T>
    void replace(T *begin, T *end, T old_item, T new_item)
    {
        while(begin != end)
        {
            if(*begin == old_item)
            {
                *begin = new_item;
            }

            ++begin;
        }
    }

/*!*****************************************************************************
\brief
    Finds a given value on a range.

\param begin
    Pointer to the start of the array.

\param end
    Pointer to end of the array.

\param item
    Value to be found

\return 
    Pointer in the position of the found value.
*******************************************************************************/
  template <typename T>
    T* find(T *begin, T *end, T item)
    {   
        while(begin != end)
        {
            if(*begin == item)
            {
                return begin;
            }
            ++begin;
        }
        return end;
    }

/*!*****************************************************************************
\brief
    Finds a given value on a range.

\param begin
    Pointer to the start of the array.

\param end
    Pointer to end of the array.

\param item
    Value to be found

\return 
    Pointer in the position of the found value.
*******************************************************************************/
  template <typename T>
    T const* find(T const* begin, T const* end, T item)
    {
        while(begin != end)
        {
            if(*begin == item)
            {
                return begin;
            }
            ++begin;
        }
        return end;
    }
}

