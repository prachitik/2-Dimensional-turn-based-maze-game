/*
 * MAZE Game Framework
 * Written by Dr. Dhanyu Amarasinghe Spring 2018
 */
#ifndef MAZE_H
#define MAZE_H

#include<CommonThings.h>
#include<string.h>
#include<gl/gl.h>
#include<GL/glut.h>
#include<SOIL.h>
#include<iostream>
#include <Timer.h>
#include <math.h>       /* ceil */

using namespace std;



class Maze
{
    public:
        Maze();                           // Constructor
        Maze(int);                        // Overload Constructor
        virtual ~Maze();                  // Deconstructor

      void loadBackgroundImage(char *);   // set an image for the background
      void loadSetOfArrowsImage(char *);  // set an image for the Arrow Bundle
      void loadChestImage(char *);        // set an image for the Arrow
      void loadBushImage(char *);
      void loadLeftArrowImage(char *);
      void loadRightArrowImage(char *);
      void loadUpArrowImage(char *);
      void loadDownArrowImage(char *);
      void loadYouWinImage(char *);
      void loadGameOverImage(char *);
      void drawBackground();              // Draw background image
      void drawGrid();                    // Draw Grid
      void drawArrows();                  // Draw set of Arrows
      void drawChest();                   // Draw Chest
      void drawYouWin();
      void drawGameOver();
      void drawBush();
      void drawLeftArrow();
      void drawRightArrow();
      void drawUpArrow();
      void drawDownArrow();
      int getGridSize();                  // return grid size

      void placeChest(int,int);           // Place Chest
      GridLoc GetChestLoc();              // Return grid location of the chest

      void placeYouWin(int,int);
      GridLoc GetYouWinLoc();

      void placeGameOver(int,int);
      GridLoc GetGameOver();

      void placeBush(int,int);           // Place Bush
      GridLoc GetBushLoc();              // Return grid location of the Bush

      void placeLeftArrow(int,int);
      GridLoc GetLeftArrowLoc();

      void placeRightArrow(int,int);
      GridLoc GetRightArrowLoc();

      void placeUpArrow(int,int);
      GridLoc GetUpArrowLoc();

      void placeDownArrow(int,int);
      GridLoc GetDownArrowLoc();

      void placeStArrws(int,int);         // Place set of arrows
      GridLoc GetStArrwsLoc();            // Return grid location of the arrows


      float spin;                         // for spin chest
      bool liveChest;                     // status of the chest (collected or not)
      bool liveSetOfArrws;                // status of the arrows(collected or not)
      loc LeftArrowLoc;
      loc RightArrowLoc;
      loc UpArrowLoc;
      loc DownArrowLoc;
      GridLoc GetMouseClickLoc();
    loc MouseClickLoc;
    loc bushLoc;
    protected:

      int gridSize;                       // grid size
      float unitWidth;                    // Unit width of the grid

    private:

      GLuint bakTex;                       // Handler for background texture
      GLuint ArrBnchTex;                   // Handler for set of arrows texture
      GLuint chestTex;                     // Handler for Chest texture
      GLuint youWinTex;
      GLuint gameOverTex;                  // Handler for game over texture
      GLuint bushTex;
      GLuint LeftArrowTex;
      GLuint RightArrowTex;
      GLuint UpArrowTex;
      GLuint DownArrowTex;
      loc chestLoc;                        // chest Location
      loc youWinLoc;
      loc gameOverLoc;
                              // bush Location
      loc setOfArrsLoc;                    // arrows Location
      loc converter(int, int);             // convert grid size to viewport
};

#endif // MAZE_H
