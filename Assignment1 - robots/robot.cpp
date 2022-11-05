/*!*****************************************************************************
\file    robot.cpp
\author  Eric Lin
\par     DP email: eric.lin@digipen.edu
\par     Course: CS170
\par     Programming Assignment #1
\date    01-17-2021

\brief
  This program creates robots with instructions and manipulates them over 
  a grid.
  
  - Create          
      Creates a robot grid based on the given x-coordinate.

  - Destroy
      Destroys a previously created robot.

  - Move
      Given a set of instructions, moves or changes the orientation of a robot.

  - QueryPosition
      Gets the position and orientation of a robot and determines whether it is
      off or on the grid.

*******************************************************************************/

#include <cassert>
#include "grid.h"
#include "robot.h"

namespace CS170 
{
    namespace Robot 
    {

        struct _Robot
        {
            Grid::Instance myGrid;
            int x_pos;
            int y_pos;
            Orientation orientation;
            bool alive;
        };
/*!*****************************************************************************
\brief
  Creates a robot with given position and orientation on the grid.

\param _x
  The x-coordinates of the robot.

\param _y
  The y-coordinates of the robot.

\param orientation
  The directional orientation of the robot.

\\param _grid
  The grid that the robot is being spawned on

\return 
  The instance of the newly created robot.
*******************************************************************************/
        Instance Create(int _x, int _y, Orientation orientation, Grid::Instance _grid) 
        {
            // Create robot and set its position and orientation on the grid.
            Instance robot = new _Robot();
            robot->myGrid = _grid;
            robot->x_pos = _x;
            robot->y_pos = _y;
            robot->orientation = orientation;

            // Check if robot is placed inside grid
            if(Grid::Inside(_grid, _x, _y))
            {
                // If robot is inside grid, set as alive
                robot->alive = true;
            }
            else
            {
                // If robot is not inside grid, set as not alive or missing
                robot->alive = false;
            }
            
            // Return robot instance
            return robot;
        }

/*!*****************************************************************************
\brief
  Destroys a previously created robot.

\param robot
  The instance of the previously created robot.

\return 
  N/A.
*******************************************************************************/
        void Destroy(Instance robot) 
        {
            delete robot;
        }

/*!*****************************************************************************
\brief
  Gives robot a single command to move or change orientation. Also places marks
  after robot deaths and moves robot back if robot is on marked spot and in
  danger.

\param robot
  The instance of the previously created robot.

\param cmd
  The given command, 'f' being move forward, 'l' being turn left and 
  'r' being turn right.

\return 
  N/A.
*******************************************************************************/
        void Move(Instance robot, char cmd)
        {
            // Store previous x and y positions
            int previous_x = robot->x_pos;
            int previous_y = robot->y_pos;

            // Test if robot is alive first
            if(robot->alive)
            {
                // If command is f, move forward based on orientation
                if(cmd == 'f')
                {
                    switch(robot->orientation)
                    {
                        case 0:
                        robot->y_pos -= 1;
                        break;

                        case 1:
                        robot->x_pos += 1;
                        break;

                        case 2:
                        robot->y_pos += 1;
                        break;

                        case 3:
                        robot->x_pos -= 1; 
                        break;

                        default:
                        return;
                        break;
                    }

                    // If current space robot is on is marked and robot is no longer inside the grid
                    if(Grid::Marked(robot->myGrid, previous_x, previous_y) && !Grid::Inside(robot->myGrid, robot->x_pos, robot->y_pos))
                    {
                        // move robot back to previous position
                        robot->x_pos = previous_x;
                        robot->y_pos = previous_y;
                    }
                    
                    // If robot is not inside grid
                    if(!(Grid::Inside(robot->myGrid, robot->x_pos, robot->y_pos)))
                    {
                        // set robot to no longer alive
                        robot->alive = false;

                        // mark robot's previous position
                        Grid::Mark(robot->myGrid, previous_x, previous_y);
                    }
                }

                // Change orientation to face left if command is 'l'
                else if(cmd == 'l')
                {
                    robot->orientation = static_cast<Orientation>((robot->orientation+3)%4); 
                }

                // Change orientation to face right if command is 'r'
                else if(cmd == 'r')
                {
                    robot->orientation = static_cast<Orientation>((robot->orientation+1)%4);
                }

            }

        }

/*!*****************************************************************************
\brief
  Gets the position and orientation of the robot and determines whether it is
  alive or lost.

\param robot
  The instance of the previously created robot.

\param x
  Pointer to robot's x-coordinate.

\param y
  Pointer to robot's y-coordinate.

\param o
  Pointer to robot's orientation.

\return 
  True if robot is on grid, otherwise false, robot is lost.
*******************************************************************************/
        bool QueryPosition(Instance robot, int* x, int* y, Orientation *o)
        {
            // Store robot's current coordinates and orientation
            *x = robot->x_pos;
            *y = robot->y_pos;
            *o = robot->orientation;

            // If robot is alive, return true
            if(robot->alive)
            {
                return true;
            }
            // Otherwise, return false
            else
            {
                return false;
            }

        }

    }
}
