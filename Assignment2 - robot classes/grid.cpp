/*!*****************************************************************************
\file    grid.cpp
\author  Eric Lin
\par     DP email: eric.lin@digipen.edu
\par     Course: CS170
\par     Programming Assignment #1
\date    01-17-2021

\brief
  This program creates and manipulates parts of a grid.
  
  - Create          
      Creates a 2D world grid with given dimensions.

  - Destroy        
      Destroys previously created world grid.

  - Inside   
      Tests if given (x, y) coordinates are within the created grid.

  - Mark 
      Places a marker on the world grid.
      
  - Marked       
      Tests if given (x, y) coordinates is a grid marker.
*******************************************************************************/

#include <cstdlib>
#include <cassert>
#include "grid.h"

#define MARKED 1

namespace CS170
{
    //class Grid 
    //{
        
        // Struct that stores all variables needed for the grid.
        //struct _Grid
        //{
        //    int *grid_;     // pointer at grid.
        //    int x_position; // x-dimension of the grid.
        //    int y_position; // y-dimension of the grid.
        //};

/*!*****************************************************************************
\brief
  Creates a world grid.

\param x
  The x-dimensions of the grid.

\param y
  The y-dimensions of the grid.

\return 
  The instance of the grid.
*******************************************************************************/
        Grid::Grid(int x, int y)
        {
            // Allocate new memory for grid
            data = new int[x * y]();  

            // Create grid with given dimensions
            x_max = x;
            y_max = y;

        }

/*!*****************************************************************************
\brief
  Destroys a previously created world grid.

\param grid
  The instance of the previously created grid.

\return 
  N/A.
*******************************************************************************/
        Grid::~Grid()
        {
            delete[] data;            
        }

/*!*****************************************************************************
\brief
  Checks if the given x and y coordinates of the robot are inside the given 
  grid instance.

\param grid
  The instance of the created grid.

\param x
  The x-coordinate of the robot.

\param y
  The y-coordinate of the robot.

\return 
  N/A.
*******************************************************************************/
        bool Grid::Inside(int x, int y)
        {
            /* If x and y coordinates are within the grid dimensions and are
            negative, then they are inside. Return true */
            if(x < x_max && y < y_max && x >= 0 && y >= 0)
            {
                return true;
            }
            /* Otherwise, not inside: false */
            else
            {
                return false;
            }
        }

/*!*****************************************************************************
\brief
  Places a marker on the world grid.

\param grid
  The instance of the created grid.

\param x
  The x-coordinate of the mark being placed.

\param y
  The y-coordinate of the mark being placed.

\return 
  N/A.
*******************************************************************************/
        void Grid::Mark(int x, int y)
        {
            // * Set the posiion in the grid to MARKED */
            data[y_max * x + y] = MARKED;
        }

/*!*****************************************************************************
\brief
  Tests if the given x and y coordinates contain a marker on the grid.

\param grid
  The instance of the created grid.

\param x
  The x-coordinate of the spot being checked.

\param y
  The y-coordinate of the spot being checked.

\return 
  N/A.
*******************************************************************************/
        bool Grid::Marked(int x, int y)
        {
            /* If the given position is marked, return true */
            if(data[y_max * x + y] == MARKED)
            {
                return true;
            }
            /* Otherwise, false */
            else
            {
                return false;
            }
        }
    //}
}
