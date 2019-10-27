/*
 * MAZE Game Framework
 * Written by Dr. Dhanyu Amarasinghe Spring 2018
 */

#include <Maze.h>


Maze::Maze()
{

}

Maze::Maze(int gSize)                                        // Constructor
{
    //ctor
    gridSize =gSize;

    unitWidth = (float)2/gridSize;
    liveChest = true;
    liveSetOfArrws=true;
}

Maze::~Maze()
{
    //dtor
}
void Maze::loadChestImage(char* FileName)
{
    chestTex = TextureLoader(FileName);
}
void Maze::loadBushImage(char* FileName)
{
    bushTex = TextureLoader(FileName);
}
void Maze::loadLeftArrowImage(char* FileName)
{
    LeftArrowTex = TextureLoader(FileName);
}
void Maze::loadRightArrowImage(char* FileName)
{
    RightArrowTex = TextureLoader(FileName);
}
void Maze::loadUpArrowImage(char* FileName)
{
    UpArrowTex = TextureLoader(FileName);
}
void Maze::loadDownArrowImage(char* FileName)
{
    DownArrowTex = TextureLoader(FileName);
}
void Maze::loadYouWinImage(char* FileName)
{
    youWinTex = TextureLoader(FileName);
}

void Maze::loadGameOverImage(char* FileName)
{
    gameOverTex = TextureLoader(FileName);
}


void Maze::loadBackgroundImage(char* FileName)
{
   bakTex = TextureLoader(FileName);
}

void Maze::loadSetOfArrowsImage(char* FileName)
{
    ArrBnchTex =  TextureLoader(FileName);
}

void Maze::placeChest(int x, int y)
{
   chestLoc.x =  converter(x,y).x;
   chestLoc.y =  converter(x,y).y;
}

void Maze::placeYouWin(int x, int y)
{
   youWinLoc.x =  converter(x,y).x;
   youWinLoc.y =  converter(x,y).y;
}

void Maze::placeGameOver(int x, int y)
{
   gameOverLoc.x =  converter(x,y).x;
   gameOverLoc.y =  converter(x,y).y;
}

void Maze::placeBush(int x, int y)
{
   bushLoc.x =  converter(x,y).x;
   bushLoc.y =  converter(x,y).y;
}

void Maze::placeStArrws(int x, int y)
{
   setOfArrsLoc.x =  converter(x,y).x;
   setOfArrsLoc.y =  converter(x,y).y;
}

void Maze::placeLeftArrow(int x, int y)
{
   LeftArrowLoc.x = converter(x,y).x;
   LeftArrowLoc.y = converter(x,y).y;
}

void Maze::placeRightArrow(int x, int y)
{
   RightArrowLoc.x = converter(x,y).x;
   RightArrowLoc.y = converter(x,y).y;
}

void Maze::placeUpArrow(int x, int y)
{
   UpArrowLoc.x = converter(x,y).x;
   UpArrowLoc.y = converter(x,y).y;
}

void Maze::placeDownArrow(int x, int y)
{
   DownArrowLoc.x = converter(x,y).x;
   DownArrowLoc.y = converter(x,y).y;
}

GridLoc Maze::GetChestLoc()
{
   GridLoc val;

   val.x = (int)(ceil((chestLoc.x +(1-unitWidth))/unitWidth));
   val.y = (int)(ceil((chestLoc.y +(1-unitWidth))/unitWidth));

   return val;
}

GridLoc Maze::GetBushLoc()
{
   GridLoc val;

   val.x = (int)(ceil((bushLoc.x +(1-unitWidth))/unitWidth));
   val.y = (int)(ceil((bushLoc.y +(1-unitWidth))/unitWidth));

   return val;
}

GridLoc Maze::GetLeftArrowLoc()
{
   GridLoc val;

   val.x = (int)(ceil((LeftArrowLoc.x +(1-unitWidth))/unitWidth));
   val.y = (int)(ceil((LeftArrowLoc.y +(1-unitWidth))/unitWidth));

   return val;
}

GridLoc Maze::GetRightArrowLoc()
{
   GridLoc val;

   val.x = (int)(ceil((RightArrowLoc.x +(1-unitWidth))/unitWidth));
   val.y = (int)(ceil((RightArrowLoc.y +(1-unitWidth))/unitWidth));

   return val;
}
GridLoc Maze::GetUpArrowLoc()
{
   GridLoc val;

   val.x = (int)(ceil((UpArrowLoc.x +(1-unitWidth))/unitWidth));
   val.y = (int)(ceil((UpArrowLoc.y +(1-unitWidth))/unitWidth));

   return val;
}

GridLoc Maze::GetDownArrowLoc()
{
   GridLoc val;

   val.x = (int)(ceil((DownArrowLoc.x +(1-unitWidth))/unitWidth));
   val.y = (int)(ceil((DownArrowLoc.y +(1-unitWidth))/unitWidth));

   return val;
}

GridLoc Maze::GetMouseClickLoc()
{
   GridLoc val;

   val.x = (int)(ceil((MouseClickLoc.x +(1-unitWidth))/unitWidth));
   val.y = (int)(ceil((MouseClickLoc.y +(1-unitWidth))/unitWidth));

   return val;
}



GridLoc Maze::GetStArrwsLoc()
{
    GridLoc val;

   val.x = (int)(ceil((setOfArrsLoc.x +(1-unitWidth))/unitWidth));
   val.y = (int)(ceil((setOfArrsLoc.y +(1-unitWidth))/unitWidth));

   return val;
}


int Maze::getGridSize()
{
  return gridSize;
}


void Maze::drawBackground()
{
    glColor3f(1.0,1.0,1.0);
    glBindTexture(GL_TEXTURE_2D,bakTex);

    glBegin(GL_QUADS);
        glTexCoord2f(0,1);
        glVertex3f(1,-1,0.0f);

       glTexCoord2f(0,0);
        glVertex3f(1,1,0.0f);

        glTexCoord2f(1,0);
        glVertex3f(-1,1,0.0f);

        glTexCoord2f(1,1);
        glVertex3f(-1,-1,0.0f);
     glEnd();
}


void Maze::drawGrid()
{
   float a;
   glColor4f(1.0,1.0,1.0,0.2);
   glDisable(GL_TEXTURE_2D);
   glPointSize(1);
   glBegin(GL_LINES);

   for(int i =0;i<gridSize;i++)
    {
        if(i == 4 || i == 5 || i== 6)
        {

        }
        else
        {
         a = -1+(float)unitWidth*i;
         glVertex3f(a,1,-0.4);
         glVertex3f(a,-1,-0.4);
         glVertex3f(-1,a,0.4);
         glVertex3f(1,a,0.4);
        }
    }
    glEnd();
    glEnable(GL_TEXTURE_2D);
}

void Maze::drawArrows()
{
    if(liveSetOfArrws)
    {

    glColor3f(1.0,1.0,1.0);

    glTranslatef(setOfArrsLoc.x,setOfArrsLoc.y,1.0);
    glRotated(-spin,0,0,1);

    glBindTexture(GL_TEXTURE_2D,ArrBnchTex);
    glScaled(1.0/(float)(gridSize),1.0/(float)(gridSize),1.0);

    glBegin(GL_QUADS);
        glTexCoord2f(0,1);
        glVertex3f(1,-1,0.0f);

       glTexCoord2f(0,0);
        glVertex3f(1,1,0.0f);

        glTexCoord2f(1,0);
        glVertex3f(-1,1,0.0f);

        glTexCoord2f(1,1);
        glVertex3f(-1,-1,0.0f);
     glEnd();
    }
}

void Maze::drawChest()
{
    if(liveChest){
    glColor3f(1.0,1.0,1.0);

    glTranslatef(chestLoc.x,chestLoc.y,1.0);

    glBindTexture(GL_TEXTURE_2D,chestTex);
    glScaled(1.0/(float)(gridSize+5),1.0/(float)(gridSize+5),1.0);
    glRotated(spin,0,0,1);

    glBegin(GL_QUADS);
        glTexCoord2f(0,1);
        glVertex3f(1,-1,0.0f);

       glTexCoord2f(0,0);
        glVertex3f(1,1,0.0f);

        glTexCoord2f(1,0);
        glVertex3f(-1,1,0.0f);

        glTexCoord2f(1,1);
        glVertex3f(-1,-1,0.0f);
     glEnd();

     spin +=0.5;
    }
}

void Maze::drawYouWin()
{
    glColor3f(1.0,1.0,1.0);

    glTranslatef(youWinLoc.x,youWinLoc.y,1.0);

    glBindTexture(GL_TEXTURE_2D,youWinTex);
    glScaled(1.0/(float)(gridSize+5),1.0/(float)(gridSize+5),1.0);
    glRotated(spin,0,0,1);

    glBegin(GL_QUADS);
        glTexCoord2f(0,1);
        glVertex3f(1,-1,0.0f);

       glTexCoord2f(0,0);
        glVertex3f(1,1,0.0f);

        glTexCoord2f(1,0);
        glVertex3f(-1,1,0.0f);

        glTexCoord2f(1,1);
        glVertex3f(-1,-1,0.0f);
     glEnd();
}

loc Maze::converter(int x, int y)
{
       loc val;

        x+=1;
        y+=1;
       val.x = -1-unitWidth/2+(unitWidth)*x;
       val.y = -1-unitWidth/2+(unitWidth)*y;
       return val;
}


void Maze::drawGameOver()
{
 glColor3f(1.0,1.0,1.0);

    glTranslatef(gameOverLoc.x,gameOverLoc.y,1.0);

    glBindTexture(GL_TEXTURE_2D,gameOverTex);
    glScaled(1.0/(float)(gridSize+5),1.0/(float)(gridSize+5),1.0);
    glRotated(spin,0,0,1);

    glBegin(GL_QUADS);
        glTexCoord2f(0,1);
        glVertex3f(1,-1,0.0f);

       glTexCoord2f(0,0);
        glVertex3f(1,1,0.0f);

        glTexCoord2f(1,0);
        glVertex3f(-1,1,0.0f);

        glTexCoord2f(1,1);
        glVertex3f(-1,-1,0.0f);
     glEnd();
}
void Maze::drawBush()
{
    glColor3f(1.0,1.0,1.0);

    glTranslatef(bushLoc.x,bushLoc.y,1.0);

    glBindTexture(GL_TEXTURE_2D,bushTex);
    glScaled(1.0/(float)(gridSize+2.5),1.0/(float)(gridSize+2.5),1.0);

    glBegin(GL_QUADS);
        glTexCoord2f(0,1);
        glVertex3f(1,-1,0.0f);

       glTexCoord2f(0,0);
        glVertex3f(1,1,0.0f);

        glTexCoord2f(1,0);
        glVertex3f(-1,1,0.0f);

        glTexCoord2f(1,1);
        glVertex3f(-1,-1,0.0f);
     glEnd();
    }


void Maze::drawLeftArrow()
{
    glColor3f(1.0,1.0,1.0);

    glTranslatef(LeftArrowLoc.x,LeftArrowLoc.y,1.0);

    glBindTexture(GL_TEXTURE_2D,LeftArrowTex);
    glScaled(1.0/(float)(gridSize+5),1.0/(float)(gridSize+5),1.0);

    glBegin(GL_QUADS);
        glTexCoord2f(0,1);
        glVertex3f(1,-1,0.0f);

       glTexCoord2f(0,0);
        glVertex3f(1,1,0.0f);

        glTexCoord2f(1,0);
        glVertex3f(-1,1,0.0f);

        glTexCoord2f(1,1);
        glVertex3f(-1,-1,0.0f);
     glEnd();
    }


    void Maze::drawRightArrow()
{
    glColor3f(1.0,1.0,1.0);

    glTranslatef(RightArrowLoc.x,RightArrowLoc.y,1.0);

    glBindTexture(GL_TEXTURE_2D,RightArrowTex);
    glScaled(1.0/(float)(gridSize+5),1.0/(float)(gridSize+5),1.0);

    glBegin(GL_QUADS);
        glTexCoord2f(0,1);
        glVertex3f(1,-1,0.0f);

       glTexCoord2f(0,0);
        glVertex3f(1,1,0.0f);

        glTexCoord2f(1,0);
        glVertex3f(-1,1,0.0f);

        glTexCoord2f(1,1);
        glVertex3f(-1,-1,0.0f);
     glEnd();
    }

void Maze::drawUpArrow()
{
    glColor3f(1.0,1.0,1.0);

    glTranslatef(UpArrowLoc.x,UpArrowLoc.y,1.0);

    glBindTexture(GL_TEXTURE_2D,UpArrowTex);
    glScaled(1.0/(float)(gridSize+5),1.0/(float)(gridSize+5),1.0);

    glBegin(GL_QUADS);
        glTexCoord2f(0,1);
        glVertex3f(1,-1,0.0f);

       glTexCoord2f(0,0);
        glVertex3f(1,1,0.0f);

        glTexCoord2f(1,0);
        glVertex3f(-1,1,0.0f);

        glTexCoord2f(1,1);
        glVertex3f(-1,-1,0.0f);
     glEnd();
    }

void Maze::drawDownArrow()
{
    glColor3f(1.0,1.0,1.0);

    glTranslatef(DownArrowLoc.x,DownArrowLoc.y,1.0);

    glBindTexture(GL_TEXTURE_2D,DownArrowTex);
    glScaled(1.0/(float)(gridSize+5),1.0/(float)(gridSize+5),1.0);

    glBegin(GL_QUADS);
        glTexCoord2f(0,1);
        glVertex3f(1,-1,0.0f);

       glTexCoord2f(0,0);
        glVertex3f(1,1,0.0f);

        glTexCoord2f(1,0);
        glVertex3f(-1,1,0.0f);

        glTexCoord2f(1,1);
        glVertex3f(-1,-1,0.0f);
     glEnd();
    }



