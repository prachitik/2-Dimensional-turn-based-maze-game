/*
 * MAZE Game Framework
 * Written by Dr. Dhanyu Amarasinghe Spring 2018
 */

#include <Enemies.h>
#include <iostream>

using namespace std;



Timer *T1 = new Timer();                             // Set Timer for animation
Enemies::Enemies()
{
    //ctor
    enmLoc.x=0;
    enmLoc.y=0;

    xmax =1;
    ymax =0.25;
    xmin =0;
    ymin =0;
    up= down = left=right=false;
    live = true;
    numberOfEnemies = 4;
    numberOfEnemies = 4;
}

Enemies::~Enemies()
{
    //dtor
}

void Enemies::initEnm(int grid,int numFrames, char * FileName)
{
    gridSize = grid;
    frames = numFrames;
    xmax =1/(float)frames;
    T1->Start();
    t = (float)(2.0/grid)/frames;
    unitWidth = (float)2.0/gridSize;
    enmTex = TextureLoader(FileName);
}


void Enemies::drawEnemy()
{
    if(live){
        glColor3f(1.0,1.0,1.0);
    glBindTexture(GL_TEXTURE_2D,enmTex);


    glPushMatrix();
    animate();
    glTranslatef(enmLoc.x,enmLoc.y,0.0);

    glScaled(1.0/(float)gridSize,1.0/(float)gridSize,1);

    glBegin(GL_POLYGON);
        glTexCoord2f(xmin,ymin);
        glVertex3f(1,1,0.0f);

        glTexCoord2f(xmax,ymin);
        glVertex3f(-1,1,0.0f);

        glTexCoord2f(xmax,ymax);
        glVertex3f(-1,-1,0.0f);

        glTexCoord2f(xmin,ymax);
        glVertex3f(1,-1,0.0f);
     glEnd();
     glPopMatrix();
    }

}

void Enemies::placeEnemy(int x, int y)
{
    unitWidth = 2.0/gridSize;
    x+=1;
    y+=1;
    enmLoc.x =  -1-unitWidth/2+(unitWidth)*x;
    enmLoc.y =  -1-unitWidth/2+(unitWidth)*y;
}

void Enemies::moveEnemy(string dir)
{
    cout<<"inside moveEnemy............"<<endl;
  if(moveDis<=0){
  if(dir=="up" && !enemycollision && !ecollision && !bushcollision){up=true; down=left=right=false;}
   else if(dir=="down" && !enemycollision && !ecollision && !bushcollision){down=true; up=left=right=false;}
   else if(dir=="left" && !enemycollision && !ecollision && !bushcollision){left=true; down=up=right=false;}
   else if(dir=="right" && !enemycollision && !ecollision && !bushcollision){right=true; down=left=up=false;}
   else{up=left=right=false;}
    }
}

bool Enemies::checkEnemyCollision(string dir,wall *W,Enemies E,int closest_enemy)
{
    cout<<"inside checkEnemyCollision"<<endl;
    //cout<<"E.enmLoc.x"<<E.enmLoc.x<<"E.enmLoc.y"<<E.enmLoc.y<<endl;
    cout<<"closest enemy:::  "<<closest_enemy<<endl;


    ecollision = true;
    //int ne=closest_enemy;
    for(int i =0; i< numberOfWallsN; i++){
//cout<<"wallBrk"<<W[i].wallBrk.x <<"wallBrk"<<W[i].wallBrk.y <<endl;
       //int j=strcmp(dir, "up");
        if(dir.compare("up") == 0)
        {
            if((E.enmLoc.y - (W[i].wallBrk.y - unitWidth/2 )< unitWidth/2)&&
               (-E.enmLoc.y+ (W[i].wallBrk.y - unitWidth/2 )< unitWidth/2))
            {
                if((W[i].wallBrk.x + 3*unitWidth/4 > E.enmLoc.x)&&
                   (W[i].wallBrk.x - 3*unitWidth/4 < E.enmLoc.x))
                {
                    return true;
                }
            }

        }

        if(dir.compare("down")==0)
        {
            if((E.enmLoc.y - (W[i].wallBrk.y + unitWidth/2 )< unitWidth/2)&&
               (-E.enmLoc.y+ (W[i].wallBrk.y + unitWidth/2 )< unitWidth/2))
            {
                if((W[i].wallBrk.x + 3*unitWidth/4 > E.enmLoc.x)&&
                   ( W[i].wallBrk.x - 3*unitWidth/4 < E.enmLoc.x))
                {
                    return true;
                }
            }
        }

        if(dir.compare("left")==0)
        {
            if((E.enmLoc.x - (W[i].wallBrk.x + unitWidth/2 )< unitWidth/2)&&
               (-E.enmLoc.x+ (W[i].wallBrk.x + unitWidth/2 )< unitWidth/2))
            {
                if((W[i].wallBrk.y + 3*unitWidth/4 > E.enmLoc.y )&&
                   ( W[i].wallBrk.y - 3*unitWidth/4 < E.enmLoc.y))
                {
                    return true;
                }
            }
        }

        if(dir.compare("right")==0)
        {
            if((E.enmLoc.x - (W[i].wallBrk.x - unitWidth/2) < unitWidth/2)&&
               (-E.enmLoc.x+ (W[i].wallBrk.x - unitWidth/2 )< unitWidth/2))
            {
                if((W[i].wallBrk.y + 3*unitWidth/4 > E.enmLoc.y)&&
                   ( W[i].wallBrk.y - 3*unitWidth/4 < E.enmLoc.y))
                {
                    return true;
                }
            }
        }
    }
    ecollision = false;
    return false;
    }


void Enemies::animate()
{

if(moveDis < unitWidth)
{

if(T1->GetTicks()<1000)
   {

if(up)
   {
       if(enmLoc.y< 1-unitWidth/2 && !ecollision && !enemycollision && !bushcollision)
        {
            enmLoc.y += t;
         }
        else if(ecollision && enemycollision && bushcollision)
        enmLoc.x -= t;

        moveDis +=t;
        xmin +=1/(float)frames;
        xmax +=1/(float)frames;
        ymin =0.0;
        ymax =0.25;
        if(xmax>1){
                xmax =1/(float)frames;
                xmin =0;
            }
    }

  else if(down)
   {
         if(enmLoc.y > -1+unitWidth/2 && !ecollision && !enemycollision && !bushcollision)
           {
              enmLoc.y -= t;
           }
           else if(ecollision && enemycollision && bushcollision)
           enmLoc.y -= t;
           moveDis +=t;
            xmin +=1/(float)frames;
            xmax +=1/(float)frames;
            ymin =0.25;
            ymax =0.5;

            if(xmax>1){
                xmax =1/(float)frames;
                xmin =0;
            }

   }
   else if(left)
   {
       if(enmLoc.x>-1+unitWidth/2 && !ecollision && !enemycollision && !bushcollision)
        {
            enmLoc.x -= t;
         }
         else if(ecollision && enemycollision && bushcollision)
         enmLoc.x -= t;
         moveDis +=t;

        xmin +=1/(float)frames;
        xmax +=1/(float)frames;
        ymin =0.75;
        ymax =1.0;

        if(xmax>1){
                xmax =1/(float)frames;
                xmin =0;
            }
   }

   else if(right)
   {
       if(enmLoc.x<1-unitWidth/2 && !ecollision && !enemycollision && !bushcollision)
          {
              enmLoc.x += t;
           }
           else if(ecollision && enemycollision && bushcollision)
            enmLoc.x -= t;

           moveDis +=t;

            xmin +=1/(float)frames;
            xmax +=1/(float)frames;
            ymin =0.5;
            ymax =0.75;

            if(xmax>1){
                xmax =1/(float)frames;
                xmin =0;
              }
     }

  }else T1->Reset();
}
 else {moveDis =0;down=up=left=right=false; }
}


GridLoc Enemies::getEnemyLoc()
{
   GridLoc val;
   val.x = (int)(ceil((enmLoc.x +(1-unitWidth))/unitWidth));
   val.y = (int)(ceil((enmLoc.y +(1-unitWidth))/unitWidth));

    return val;
}

bool Enemies::checkEnemyPresent(string dir,Enemies E1, Enemies E2, int closest_enemy)
{
    cout<<"checkEnemyPresent: "<<unitWidth<<endl;
    E1.enemycollision = true;
    if(dir.compare("up") == 0)
        {
            cout<<"E1.dir: "<<dir<<endl;
            if((E1.enmLoc.y - (E2.enmLoc.y - unitWidth/2 )< unitWidth/2)&&
               (-E1.enmLoc.y+ (E2.enmLoc.y - unitWidth/2 )< unitWidth/2))
            {
                if((E2.enmLoc.x + 3*unitWidth/4 > E1.enmLoc.x)&&
                   (E2.enmLoc.x - 3*unitWidth/4 < E1.enmLoc.x))
                {
                    return true;
            }
                }

        }

        if(dir.compare("down")==0)
        {
            if((E1.enmLoc.y - (E2.enmLoc.y + unitWidth/2 )< unitWidth/2)&&
               (-E1.enmLoc.y+ (E2.enmLoc.y + unitWidth/2 )< unitWidth/2))
            {
                if((E2.enmLoc.x + 3*unitWidth/4 > E1.enmLoc.x)&&
                   ( E2.enmLoc.x - 3*unitWidth/4 < E1.enmLoc.x))
                {
                    return true;
                }
            }
        }

        if(dir.compare("left")==0)
        {
            if((E1.enmLoc.x - (E2.enmLoc.x + unitWidth/2 )< unitWidth/2)&&
               (-E1.enmLoc.x+ (E2.enmLoc.x + unitWidth/2 )< unitWidth/2))
            {
                if((E2.enmLoc.y + 3*unitWidth/4 > E1.enmLoc.y )&&
                   ( E2.enmLoc.y - 3*unitWidth/4 < E1.enmLoc.y))
                {
                    return true;
                }
            }
        }

        if(dir.compare("right")==0)
        {
            if((E1.enmLoc.x - (E2.enmLoc.x - unitWidth/2) < unitWidth/2)&&
               (-E1.enmLoc.x+ (E2.enmLoc.x - unitWidth/2 )< unitWidth/2))
            {
                if((E2.enmLoc.y + 3*unitWidth/4 > E1.enmLoc.y)&&
                   ( E2.enmLoc.y - 3*unitWidth/4 < E1.enmLoc.y))
                {
                    return true;
                }
            }
        }
    enemycollision = false;
    return false;
}



bool Enemies::enemyBushCollision(string dir,loc bushLoc,Enemies E)
{
    cout<<"inside checkEnemyCollision"<<endl;
    //cout<<"E.enmLoc.x"<<E.enmLoc.x<<"E.enmLoc.y"<<E.enmLoc.y<<endl;
    //cout<<"closest enemy:::  "<<closest_enemy<<endl;


    bushcollision = true;

    //for(int i =0; i< numberOfWallsN; i++){

        if(dir.compare("up") == 0)
        {
            if((E.enmLoc.y - (bushLoc.y - unitWidth/2 )< unitWidth/2)&&
               (-E.enmLoc.y+ (bushLoc.y - unitWidth/2 )< unitWidth/2))
            {
                if((bushLoc.x + 3*unitWidth/4 > E.enmLoc.x)&&
                   (bushLoc.x - 3*unitWidth/4 < E.enmLoc.x))
                {
                    return true;
                }
            }

        }

        if(dir.compare("down")==0)
        {
            if((E.enmLoc.y - (bushLoc.y + unitWidth/2 )< unitWidth/2)&&
               (-E.enmLoc.y+ (bushLoc.y + unitWidth/2 )< unitWidth/2))
            {
                if((bushLoc.x + 3*unitWidth/4 > E.enmLoc.x)&&
                   ( bushLoc.x - 3*unitWidth/4 < E.enmLoc.x))
                {
                    return true;
                }
            }
        }

        if(dir.compare("left")==0)
        {
            if((E.enmLoc.x - (bushLoc.x + unitWidth/2 )< unitWidth/2)&&
               (-E.enmLoc.x+ (bushLoc.x + unitWidth/2 )< unitWidth/2))
            {
                if((bushLoc.y + 3*unitWidth/4 > E.enmLoc.y )&&
                   ( bushLoc.y - 3*unitWidth/4 < E.enmLoc.y))
                {
                    return true;
                }
            }
        }

        if(dir.compare("right")==0)
        {
            if((E.enmLoc.x - (bushLoc.x - unitWidth/2) < unitWidth/2)&&
               (-E.enmLoc.x+ (bushLoc.x - unitWidth/2 )< unitWidth/2))
            {
                if((bushLoc.y + 3*unitWidth/4 > E.enmLoc.y)&&
                   ( bushLoc.y - 3*unitWidth/4 < E.enmLoc.y))
                {
                    return true;
                }
            }
        }
    //}
    bushcollision = false;
    return false;
    }
