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

  - Get X, Get Y, GetO
      Gets the position or orientation of a robot

*******************************************************************************/

#include <cassert>
#include "grid.h"
#include "robot.h"

namespace CS170 
{
    //class Robot 
    //{

        //struct _Robot
        //{
        //    Grid::Instance myGrid;
        //    int x_pos;
        //    int y_pos;
        //    Orientation orientation;
        //    bool alive;
        //};
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
        Robot::Robot(Grid& _grid, int _x, int _y, Orientation orientation):grid(_grid) 
        {
            // Create robot and set its position and orientation on the grid.
            x = _x;
            y = _y;
            heading = orientation;

        }

/*!*****************************************************************************
\brief
  Destroys a previously created robot.

\param robot
  The instance of the previously created robot.

\return 
  N/A.
*******************************************************************************/
        Robot::~Robot() 
        {

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
        void Robot::Move (char cmd)
        {
            // Store previous x and y positions
            int previous_x = x;
            int previous_y = y;

            // Test if robot is alive first
            if(GetStatus())
            {
                // If command is f, move forward based on orientation
                if(cmd == 'f')
                {
                    switch(heading)
                    {
                        case 0:
                        y -= 1;
                        break;

                        case 1:
                        x += 1;
                        break;

                        case 2:
                        y += 1;
                        break;

                        case 3:
                        x -= 1; 
                        break;

                        default:
                        return;
                        break;
                    }

                    // If current space robot is on is marked and robot is no longer inside the grid
                    if(grid.Marked(previous_x, previous_y) && !(grid.Inside(x, y)))
                    {
                        // move robot back to previous position
                        x = previous_x;
                        y = previous_y;
                    }
                    
                    // If robot is not inside grid
                    if(!(grid.Inside(x, y)))
                    {
                        // mark robot's previous position
                        grid.Mark(previous_x, previous_y);
                    }
                }

                // Change orientation to face left if command is 'l'
                else if(cmd == 'l')
                {
                    heading = static_cast<Orientation>((heading+3)%4); 
                }

                // Change orientation to face right if command is 'r'
                else if(cmd == 'r')
                {
                    heading = static_cast<Orientation>((heading+1)%4);
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
        int Robot::GetX()
        {
            return x;
        }

        int Robot::GetY()
        {
            return y;
        }

        Robot::Orientation Robot::GetO()
        {
            return heading;
        }

        bool Robot::GetStatus()
        {
            if(grid.Inside(x, y))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    //}
}
