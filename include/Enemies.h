/*
 * MAZE Game Framework
 * Written by Dr. Dhanyu Amarasinghe Spring 2018
 */
#ifndef ENEMIES_H
#define ENEMIES_H

#include<CommonThings.h>
#include <Maze.h>
#include <time.h>
#include <thread>
#include <string>
#include <math.h>       /* ceil */
#include <wall.h>

class Enemies
{
    public:
        Enemies();                          // constructor
        virtual ~Enemies();                 // DeConstructor
        void initEnm(int, int, char *);     // Initialize Enemy
        bool checkEnemyCollision(string dir,wall*,Enemies,int);
        void placeEnemy(int,int);           // place enemy
        void drawEnemy();                   // Draw Enemy with Animation
        void moveEnemy(string);             // move Enemy left,right,up,down
        void animate();                     // Animate sprite
        GridLoc getEnemyLoc();              // Return Enemy current grid location

        bool ecollision;
        int gridSize;                       // Grid size of the maze
        float unitWidth;                    // Unit width of the grid
        int stepsPerMove;                   // Step count for animation
        bool live;                          // Status of the Enemy
        bool checkEnemyPresent(string, Enemies, Enemies , int closest_enemy);
        bool enemyBushCollision(string ,loc ,Enemies);
        int numberOfEnemies;
        char *enemyDir;
        int numberOfWallsN;
        bool enemycollision;
        bool bushcollision;
        loc enmLoc;                        // location of the enemy
    protected:

    private:
         int frames;                        // number of frames generally
         float t;                           // steps for animation count
         GLuint enmTex;                     // Image Texture

         float xmax, xmin,ymax,ymin;        // Animated Texture mapping
         bool up,down,left,right;           // move direction
         float moveDis=0;                   // Moving distance for animation


};

#endif // ENEMIES_H
