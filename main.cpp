/*
 * MAZE Game Framework
 * Written by Dr. Dhanyu Amarasinghe Spring 2018
 */

#include <string.h>
#include <Maze.h>
#include <iostream>
#include <algorithm>
#include <map>
#include <Timer.h>
#include <player.h>
#include <path.h>
#define V 8
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <bfs.h>
#include <stdlib.h>
#include <Enemies.h>
#include <CommonThings.h>
#include <wall.h>
#include <math.h>
#include <bits/stdc++.h>



/* GLUT callback Handlers */

using namespace std;



Maze *M = new Maze(10);                         // Set Maze grid size
Player *P = new Player();                       // create player


//wall W1[100];                                    // wall with number of bricks
//wall W2[100];                                    // wall with number of bricks
wall W[100];

//int W1_size = 3;
//int W2_size = 3;
Enemies E[4];                                  // create number of enemies
Timer *T0 = new Timer();                        // animation timer

float wWidth, wHeight;                          // display window width and Height
float xPos,yPos;                                // Viewpoar mapping
float unitWidth= (float)2/10;
string node[10][10];
float FPS = 60.0;                                 // control render time
int i,time_now,time_prev;                         // timers
loc tOGLPos;
loc n1,n2,n3,n4,n5,n6;                          //Nodes
typedef pair<int, int> MyPairType;
bool block=false;
bfs B;

struct CompareSecond
{
    bool operator()(const MyPairType& left, const MyPairType& right) const
    {
        return left.second < right.second;
    }
};



void display(void);                             // Main Display : this runs in a loop

void resize(int width, int height)              // resizing case on the window
{
    wWidth = width;
    wHeight = height;

    if(width<=height)
        glViewport(0,(GLsizei) (height-width)/2,(GLsizei) width,(GLsizei) width);
    else
        glViewport((GLsizei) (width-height)/2 ,0 ,(GLsizei) height,(GLsizei) height);
}

void init()
{
    /*if(win_or_lose.compare("win")==0)
    {
     cout<<"winning";
    M->loadYouWinImage("images/tenor.gif");
    M->placeYouWin(5,5);
    }
    else if(win_or_lose.compare("lose")==0)
    {
    cout<<"losing";
    M->loadGameOverImage("images/game_over.jpg");
    M->placeGameOver(5,5);
    }
    else
    {*/
    glEnable(GL_COLOR_MATERIAL);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(0.0,0.0,0.0,0.0);
    gluOrtho2D(0, wWidth, 0, wHeight);

    T0->Start();                                        // set timer to 0

    glEnable(GL_BLEND);                                 //display images with transparent
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    P->isPlayerVisible=true;
    M->loadBackgroundImage("images/bak.jpg");           // Load maze background image
    M->loadChestImage("images/chest.png");               // load chest image
    M->placeChest(3,3);                                 // place chest in a grid


    M->loadBushImage("images/bush.png");               // load BUSH image
    M->placeBush(3,7);                                 // place BUSH in a grid

    M->loadLeftArrowImage("images/LeftArrow.png");
    M->placeLeftArrow(7,2);

    M->loadRightArrowImage("images/RightArrow.png");
    M->placeRightArrow(9,2);

    M->loadUpArrowImage("images/upArrow.png");
    M->placeUpArrow(8,3);

    M->loadDownArrowImage("images/downArrow.png");
    M->placeDownArrow(8,1);

    M->loadSetOfArrowsImage("images/arrwset.png");      // load set of arrows image
    M->placeStArrws(5,3);                               // place set of arrows

    P->initPlayer(M->getGridSize(),6,"images/p.png");   // initialize player pass grid size,image and number of frames
    P->loadArrowImage("images/arr.png");                // Load arrow image
    P->placePlayer(5,5);                                // Place player


    //W1.setWallSize(W1_size);
    //W2.setWallSize(W2_size);
   /* for(int i=1; i< W1_size+1;i++)
    {


                cout<<"M->getGridSize(): "<<M->getGridSize();
            W1[i].wallInit(M->getGridSize(),"images/wall.png");// Load walls
            W1[i].placeWall(i,5);                              // place each brick


    }*/


      /*for(int i=7; i< M->getGridSize();i++)
    {

                cout<<"M->getGridSize(): "<<M->getGridSize();
            W2[i].wallInit(M->getGridSize(),"images/wall.png");// Load walls
            W2[i].placeWall(i,5);                              // place each brick


    }*/
    for(int i=0; i< 26;i++)
    {
         W[i].wallInit(M->getGridSize(),"images/wall.png");// Load walls

    }
    W[0].placeWall(0,9);
    W[1].placeWall(2,8);
    W[2].placeWall(3,8);
    W[3].placeWall(6,8);
    W[4].placeWall(7,8);
    W[5].placeWall(0,7);
    W[6].placeWall(9,7);
    W[7].placeWall(4,6);
    W[8].placeWall(5,6);
    W[9].placeWall(1,4);
    W[10].placeWall(2,4);
    W[11].placeWall(3,4);
    W[12].placeWall(6,4);
    W[13].placeWall(7,4);
    W[14].placeWall(8,4);
    W[15].placeWall(3,2);
    W[16].placeWall(4,2);
    W[17].placeWall(6,2);
    W[18].placeWall(8,2);
    W[19].placeWall(9,2);
    W[20].placeWall(0,1);
    W[21].placeWall(1,1);
    W[22].placeWall(6,1);
    W[23].placeWall(3,0);
    W[24].placeWall(8,0);
    W[25].placeWall(9,9);




    for(int i=0; i<4;i++)
    {
        E[i].initEnm(M->getGridSize(),4,"images/e.png"); //Load enemy image
        E[i].placeEnemy(float(rand()%(M->getGridSize())),float(rand()%(M->getGridSize())));
        E[i].enemycollision = false;
        E[i].bushcollision = false;
        E[i].ecollision = false;
        E[i].numberOfWallsN = 26;
        //place enemies random x,y
    }
    P->numberOfWallsN = 26;
    }





void display(void)
{

    time_now = glutGet(GLUT_ELAPSED_TIME);
    if((time_now - time_prev) > 1000/FPS)
    {

  glClear (GL_COLOR_BUFFER_BIT);        // clear display screen

        glPushMatrix();
         M->drawBackground();
        glPopMatrix();


        for(int i=0; i<26;i++)
        {

           W[i].drawWall();

        }
        //W[21].drawWall();
         /*for(int i=7; i<M->getGridSize();i++)
        {


           W[i].drawWall();
        }*/

        glPushMatrix();
            M->drawGrid();
        glPopMatrix();

        glPushMatrix();
            P->drawplayer();
        glPopMatrix();

        for(int i=0; i<4;i++)
        {
        E[i].drawEnemy();
        }

        glPushMatrix();
            P->drawArrow();
        glPopMatrix();

         glPushMatrix();
           M->drawChest();
        glPopMatrix();

        glPushMatrix();
           M->drawBush();
        glPopMatrix();

        glPushMatrix();
        M->drawLeftArrow();
        glPopMatrix();

        glPushMatrix();
        M->drawRightArrow();
        glPopMatrix();

        glPushMatrix();
        M->drawUpArrow();
        glPopMatrix();

        glPushMatrix();
        M->drawDownArrow();
        glPopMatrix();

        glPushMatrix();
           M->drawArrows();
        glPopMatrix();

 /*       if(win_or_lose==true)
        {
            if(game_status.compare("lose")==0)
            {
            glPushMatrix();
          M->drawGameOver();
            glPopMatrix();
            }
            else
            {
            glPushMatrix();
          M->drawYouWin();
            glPopMatrix();
            }
        }*/
    glutSwapBuffers();
    time_now = time_prev;
    }  //End of if case
}




void key(unsigned char key, int x, int y)
{ //bool collide = false;
    switch (key)
    {
        case ' ':
          // if(!M->liveSetOfArrws)      // if setof arrows were picked by player
            //for(int i =0; i<26; i++){
                 if((P->getPlayerLoc().x == M->GetStArrwsLoc().x && P->getPlayerLoc().y == M->GetStArrwsLoc().y))
                {
                    M->liveSetOfArrws = false;
                    //collide = true;

                }
                if(!M->liveSetOfArrws){
                    P->shootArrow();
                }
           // }


        break;
        case 27 :                       // esc key to exit
        case 'q':
            exit(0);
            break;
    }

    glutPostRedisplay();
}

loc getConvertertedValue(int x, int y)
{
       loc val;

        x+=1;
        y+=1;
       val.x = -1-unitWidth/2+(unitWidth)*x;
       val.y = -1-unitWidth/2+(unitWidth)*y;
       return val;
}


loc GetOGLPos(int x, int y)
{
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ;
    GLdouble posX, posY, posZ;

    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetIntegerv( GL_VIEWPORT, viewport );

    winX = (float)x;
    winY = (float)viewport[3] - (float)y;
    glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );

    gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);


    xPos =posX ;

    yPos =posY ;
tOGLPos.x=ceil(10*xPos)/10;
tOGLPos.y=floor(10*yPos)/10;
/*cout<<"before";
cout<<"\n "<<xPos<<"  "<<yPos;
cout<<"after";
cout<<"\n "<<ceil(10*xPos)/10<<"  "<<floor(10*yPos)/10;
cout<<"now";*/
return tOGLPos;
}

 void idle(void)
{

    //Your Code here
    for(int i =0;i<4; i++){
        if(P->getArrowLoc().x == E[i].getEnemyLoc().x && P->getArrowLoc().y == E[i].getEnemyLoc().y){
            E[i].live = false;
        }
    }

    glutPostRedisplay();
}


void mouse(int btn, int state, int x, int y){

loc convertedValueLeft=getConvertertedValue(M->GetLeftArrowLoc().x,M->GetLeftArrowLoc().y);
loc convertedValueRight=getConvertertedValue(M->GetRightArrowLoc().x,M->GetRightArrowLoc().y);
loc convertedValueUp=getConvertertedValue(M->GetUpArrowLoc().x,M->GetUpArrowLoc().y);
loc convertedValueDown=getConvertertedValue(M->GetDownArrowLoc().x,M->GetDownArrowLoc().y);
cout<<"\n\n\n\n\n left conv x "<<convertedValueLeft.x<<"  conv y "<<convertedValueLeft.y;
cout<<"\n left conv x +0.1 "<<(convertedValueLeft.x+0.1)<<"  conv y "<<(convertedValueLeft.y-0.1);
cout<<"\n right conv x "<<convertedValueRight.x<<"  conv y "<<convertedValueRight.y;
cout<<"\n right conv x +0.1 "<<(convertedValueRight.x+0.1)<<"  conv y "<<(convertedValueRight.y-0.1);
cout<<"\n Up conv x "<<convertedValueUp.x<<"  conv y "<<convertedValueUp.y;
cout<<"\n Up conv x +0.1 "<<(convertedValueUp.x+0.1)<<"  conv y "<<(convertedValueUp.y-0.1);
cout<<"\n Down conv x "<<convertedValueDown.x<<"  conv y "<<convertedValueDown.y;
cout<<"\n Down conv x +0.1 "<<(convertedValueDown.x+0.1)<<"  conv y "<<(convertedValueDown.y-0.1);

switch(btn){
    case GLUT_LEFT_BUTTON:
        if(state==GLUT_DOWN){
            loc tOGLPos=GetOGLPos(x,y);
            cout<<"\n toglpos "<<tOGLPos.x<<"  "<<tOGLPos.y;
            if((tOGLPos.x>=convertedValueLeft.x&&tOGLPos.x<=(convertedValueLeft.x+0.11))&&(tOGLPos.y<=convertedValueLeft.y&&tOGLPos.y>=(convertedValueLeft.y-0.11)))
            {
                P->movePlayer("left");
            }
            else if((tOGLPos.x>=convertedValueRight.x&&tOGLPos.x<=(convertedValueRight.x+0.11))&&(tOGLPos.y<=convertedValueRight.y&&tOGLPos.y>=(convertedValueRight.y-0.11)))
            {
                P->movePlayer("right");
            }
            else if((tOGLPos.x>=convertedValueUp.x&&tOGLPos.x<=(convertedValueUp.x+0.11))&&(tOGLPos.y<=convertedValueUp.y&&tOGLPos.y>=(convertedValueUp.y-0.11)))
            {
                P->movePlayer("up");
            }
            else if((tOGLPos.x>=convertedValueDown.x&&tOGLPos.x<=(convertedValueDown.x+0.11))&&(tOGLPos.y<=convertedValueDown.y&&tOGLPos.y>=(convertedValueDown.y-0.11)))
            {
            P->movePlayer("down");
            }
        }
    break;

        /*case GLUT_RIGHT_BUTTON:

            if(state==GLUT_DOWN){
                cout<<"right click";
                GetOGLPos(x,y);
                P->movePlayer("right");
            }
        break;
*/
        /*case GLUT_DOWN:

            if(state==GLUT_DOWN){
                cout<<"right click";
                GetOGLPos(x,y);
                P->movePlayer("right");
            }
        break;

        case GLUT_RIGHT_BUTTON:

            if(state==GLUT_DOWN){
                cout<<"right click";
                GetOGLPos(x,y);
                P->movePlayer("right");
            }
        break;*/
        }
     glutPostRedisplay();
};

int distance(int x1,int y1,int x2,int y2)
{
return sqrt(pow(x2-x1,2)+pow(y2-y1,2)*1.0);
}

//std::pair<size_t, size_t>

loc find_position( const string ( &node )[10][10], string value )
{
    size_t row = 0;
    size_t col = 0;

    for ( ; row < 10; row++ )
    {
        col = 0;
        while ( col < 10 && node[row][col] != value ) col++;
        if ( col != 10 ) break;
    }

    loc n;
    n.x=col;
    n.y=row;
    return n;

    //return { row, col };
}

int getVertex(map<int, loc> vertex, loc findSrcVertex)
{
 for (auto itr = vertex.begin(); itr != vertex.end(); itr++)
        if(itr->second.x==findSrcVertex.x)
        {
            if(itr->second.y==findSrcVertex.y)
            {
                return itr->first;
            }
        }
}




int getBFSShortest(int i)
{

int dist;
map<int,loc> verticesLoc;

vector<int> adj[75];

string node[10][10]={{"n68","n69","n70","na","n71","n72","n73","n74","na","n75"},
                     {"na","na","n61","n62","n63","n64","na","n65","n66","n67"},
                     {"n56","n57","n58","na","na","n59","na","n60","na","na"},
                     {"n46","n47","n48","n49","n50","n51","n52","n53","n54","n55"},
                     {"n41","na","na","na","n43","n44","na","na","na","n45"},
                     {"n31","n32","n33","n34","n35","n36","n37","n38","n39","n40"},
                     {"n23","n24","n25","n26","na","na","n27","n28","n29","n30"},
                     {"na","n15","n16","n17","n18","n19","n20","n21","n22","na"},
                     {"n9","n10","na","na","n11","n12","na","na","n13","n14"},
                     {"na","n1","n2","n3","n4","n5","n6","n7","n8","na"}
					 };

loc n1=find_position(node,"n1");
loc n2=find_position(node,"n2");
loc n3=find_position(node,"n3");
loc n4=find_position(node,"n4");
loc n5=find_position(node,"n5");
loc n6=find_position(node,"n6");
loc n7=find_position(node,"n7");
loc n8=find_position(node,"n8");
loc n9=find_position(node,"n9");
loc n10=find_position(node,"n10");
loc n11=find_position(node,"n11");
loc n12=find_position(node,"n12");
loc n13=find_position(node,"n13");
loc n14=find_position(node,"n14");
loc n15=find_position(node,"n15");
loc n16=find_position(node,"n16");
loc n17=find_position(node,"n17");
loc n18=find_position(node,"n18");
loc n19=find_position(node,"n19");
loc n20=find_position(node,"n20");
loc n21=find_position(node,"n21");
loc n22=find_position(node,"n22");
loc n23=find_position(node,"n23");
loc n24=find_position(node,"n24");
loc n25=find_position(node,"n25");
loc n26=find_position(node,"n26");
loc n27=find_position(node,"n27");
loc n28=find_position(node,"n28");
loc n29=find_position(node,"n29");
loc n30=find_position(node,"n30");
loc n31=find_position(node,"n31");
loc n32=find_position(node,"n32");
loc n33=find_position(node,"n33");
loc n34=find_position(node,"n34");
loc n35=find_position(node,"n35");
loc n36=find_position(node,"n36");
loc n37=find_position(node,"n37");
loc n38=find_position(node,"n38");
loc n39=find_position(node,"n39");
loc n40=find_position(node,"n40");
loc n41=find_position(node,"n41");
loc n42=find_position(node,"n42");
loc n43=find_position(node,"n43");
loc n44=find_position(node,"n44");
loc n45=find_position(node,"n45");
loc n46=find_position(node,"n46");
loc n47=find_position(node,"n47");
loc n48=find_position(node,"n48");
loc n49=find_position(node,"n49");
loc n50=find_position(node,"n50");
loc n51=find_position(node,"n51");
loc n52=find_position(node,"n52");
loc n53=find_position(node,"n53");
loc n54=find_position(node,"n54");
loc n55=find_position(node,"n55");
loc n56=find_position(node,"n56");
loc n57=find_position(node,"n57");
loc n58=find_position(node,"n58");
loc n59=find_position(node,"n59");
loc n60=find_position(node,"n60");
loc n61=find_position(node,"n61");
loc n62=find_position(node,"n62");
loc n63=find_position(node,"n63");
loc n64=find_position(node,"n64");
loc n65=find_position(node,"n65");
loc n66=find_position(node,"n66");
loc n67=find_position(node,"n67");
loc n68=find_position(node,"n68");
loc n69=find_position(node,"n69");
loc n70=find_position(node,"n70");
loc n71=find_position(node,"n71");
loc n72=find_position(node,"n72");
loc n73=find_position(node,"n73");
loc n74=find_position(node,"n74");
loc n75=find_position(node,"n75");
verticesLoc.insert(pair<int, loc>(1,n1));
verticesLoc.insert(pair<int, loc>(2,n2));
verticesLoc.insert(pair<int, loc>(3,n3));
verticesLoc.insert(pair<int, loc>(4,n4));
verticesLoc.insert(pair<int, loc>(5,n5));
verticesLoc.insert(pair<int, loc>(6,n6));
verticesLoc.insert(pair<int, loc>(7,n7));
verticesLoc.insert(pair<int, loc>(8,n8));
verticesLoc.insert(pair<int, loc>(9,n9));
verticesLoc.insert(pair<int, loc>(10,n10));
verticesLoc.insert(pair<int, loc>(11,n11));
verticesLoc.insert(pair<int, loc>(12,n12));
verticesLoc.insert(pair<int, loc>(13,n13));
verticesLoc.insert(pair<int, loc>(14,n14));
verticesLoc.insert(pair<int, loc>(15,n15));
verticesLoc.insert(pair<int, loc>(16,n16));
verticesLoc.insert(pair<int, loc>(17,n17));
verticesLoc.insert(pair<int, loc>(18,n18));
verticesLoc.insert(pair<int, loc>(19,n19));
verticesLoc.insert(pair<int, loc>(20,n20));
verticesLoc.insert(pair<int, loc>(21,n21));
verticesLoc.insert(pair<int, loc>(22,n22));
verticesLoc.insert(pair<int, loc>(23,n23));
verticesLoc.insert(pair<int, loc>(24,n24));
verticesLoc.insert(pair<int, loc>(25,n25));
verticesLoc.insert(pair<int, loc>(26,n26));
verticesLoc.insert(pair<int, loc>(27,n27));
verticesLoc.insert(pair<int, loc>(28,n28));
verticesLoc.insert(pair<int, loc>(29,n29));
verticesLoc.insert(pair<int, loc>(30,n30));
verticesLoc.insert(pair<int, loc>(31,n31));
verticesLoc.insert(pair<int, loc>(32,n32));
verticesLoc.insert(pair<int, loc>(33,n33));
verticesLoc.insert(pair<int, loc>(34,n34));
verticesLoc.insert(pair<int, loc>(35,n35));
verticesLoc.insert(pair<int, loc>(36,n36));
verticesLoc.insert(pair<int, loc>(37,n37));
verticesLoc.insert(pair<int, loc>(38,n38));
verticesLoc.insert(pair<int, loc>(39,n39));
verticesLoc.insert(pair<int, loc>(40,n40));
verticesLoc.insert(pair<int, loc>(41,n41));
verticesLoc.insert(pair<int, loc>(42,n42));
verticesLoc.insert(pair<int, loc>(43,n43));
verticesLoc.insert(pair<int, loc>(44,n44));
verticesLoc.insert(pair<int, loc>(45,n45));
verticesLoc.insert(pair<int, loc>(46,n46));
verticesLoc.insert(pair<int, loc>(47,n47));
verticesLoc.insert(pair<int, loc>(48,n48));
verticesLoc.insert(pair<int, loc>(49,n49));
verticesLoc.insert(pair<int, loc>(50,n50));
verticesLoc.insert(pair<int, loc>(51,n51));
verticesLoc.insert(pair<int, loc>(52,n52));
verticesLoc.insert(pair<int, loc>(53,n53));
verticesLoc.insert(pair<int, loc>(54,n54));
verticesLoc.insert(pair<int, loc>(55,n55));
verticesLoc.insert(pair<int, loc>(56,n56));
verticesLoc.insert(pair<int, loc>(57,n57));
verticesLoc.insert(pair<int, loc>(58,n58));
verticesLoc.insert(pair<int, loc>(59,n59));
verticesLoc.insert(pair<int, loc>(60,n60));
verticesLoc.insert(pair<int, loc>(61,n61));
verticesLoc.insert(pair<int, loc>(62,n62));
verticesLoc.insert(pair<int, loc>(63,n63));
verticesLoc.insert(pair<int, loc>(64,n64));
verticesLoc.insert(pair<int, loc>(65,n65));
verticesLoc.insert(pair<int, loc>(66,n66));
verticesLoc.insert(pair<int, loc>(67,n67));
verticesLoc.insert(pair<int, loc>(68,n68));
verticesLoc.insert(pair<int, loc>(69,n69));
verticesLoc.insert(pair<int, loc>(70,n70));
verticesLoc.insert(pair<int, loc>(71,n71));
verticesLoc.insert(pair<int, loc>(72,n72));
verticesLoc.insert(pair<int, loc>(73,n73));
verticesLoc.insert(pair<int, loc>(74,n74));
verticesLoc.insert(pair<int, loc>(75,n75));

B.add_edge(adj, 1, 2);
B.add_edge(adj, 2, 3);
B.add_edge(adj, 3, 4);
B.add_edge(adj, 4, 5);
B.add_edge(adj, 5, 6);
B.add_edge(adj, 6, 7);
B.add_edge(adj, 7, 8);
B.add_edge(adj, 1, 10);
B.add_edge(adj, 10, 9);
B.add_edge(adj, 4, 11);
B.add_edge(adj, 11, 12);
B.add_edge(adj, 5, 12);
B.add_edge(adj, 8, 13);
B.add_edge(adj, 13, 14);
B.add_edge(adj, 10, 15);
B.add_edge(adj, 15, 16);
B.add_edge(adj, 16, 17);
B.add_edge(adj, 17, 18);
B.add_edge(adj, 18, 19);
B.add_edge(adj, 19, 20);
B.add_edge(adj, 20, 21);
B.add_edge(adj, 20, 27);
B.add_edge(adj, 21, 28);
B.add_edge(adj, 15, 24);
B.add_edge(adj, 16, 25);
B.add_edge(adj, 24, 25);
B.add_edge(adj, 17, 26);
B.add_edge(adj, 25, 26);
B.add_edge(adj, 20, 27);
B.add_edge(adj, 21, 28);
B.add_edge(adj, 22, 29);
B.add_edge(adj, 27, 28);
B.add_edge(adj, 28, 29);
B.add_edge(adj, 29, 30);
B.add_edge(adj, 23, 31);
B.add_edge(adj, 24, 32);
B.add_edge(adj, 25, 33);
B.add_edge(adj, 26, 34);
B.add_edge(adj, 27, 37);
B.add_edge(adj, 28, 38);
B.add_edge(adj, 29, 39);
B.add_edge(adj, 30, 40);
B.add_edge(adj, 31, 32);
B.add_edge(adj, 33, 34);
B.add_edge(adj, 34, 35);
B.add_edge(adj, 35, 36);
B.add_edge(adj, 36, 37);
B.add_edge(adj, 37, 38);
B.add_edge(adj, 38, 39);
B.add_edge(adj, 39, 40);
B.add_edge(adj, 31, 41);
B.add_edge(adj, 35, 43);
B.add_edge(adj, 36, 44);
B.add_edge(adj, 40, 45);
B.add_edge(adj, 41, 46);
B.add_edge(adj, 43, 50);
B.add_edge(adj, 44, 51);
B.add_edge(adj, 45, 55);
B.add_edge(adj, 46, 47);
B.add_edge(adj, 47, 48);
B.add_edge(adj, 48, 49);
B.add_edge(adj, 49, 50);
B.add_edge(adj, 50, 51);
B.add_edge(adj, 51, 52);
B.add_edge(adj, 52, 53);
B.add_edge(adj, 53, 54);
B.add_edge(adj, 54, 55);
B.add_edge(adj, 46, 56);
B.add_edge(adj, 47, 57);
B.add_edge(adj, 48, 58);
B.add_edge(adj, 51, 59);
B.add_edge(adj, 53, 60);
B.add_edge(adj, 56, 57);
B.add_edge(adj, 57, 58);
B.add_edge(adj, 58, 61);
B.add_edge(adj, 59, 64);
B.add_edge(adj, 60, 65);
B.add_edge(adj, 61, 62);
B.add_edge(adj, 62, 63);
B.add_edge(adj, 63, 64);
B.add_edge(adj, 65, 66);
B.add_edge(adj, 66, 67);
B.add_edge(adj, 61, 70);
B.add_edge(adj, 63, 71);
B.add_edge(adj, 64, 72);
B.add_edge(adj, 65, 74);
B.add_edge(adj, 67, 75);
B.add_edge(adj, 68, 69);
B.add_edge(adj, 69, 70);
B.add_edge(adj, 71, 72);
B.add_edge(adj, 72, 73);
B.add_edge(adj, 73, 74);

loc findEnemyVertex;
findEnemyVertex.x=E[i].getEnemyLoc().x;
findEnemyVertex.y=E[i].getEnemyLoc().y;
int source=getVertex(verticesLoc,findEnemyVertex);
loc findPlayerVertex;
cout<<endl<<"getPlayerLoc().x;"<<P->getPlayerLoc().x<<"getPlayerLoc().y;"<<P->getPlayerLoc().y<<endl;
findPlayerVertex.x=P->getPlayerLoc().x;
findPlayerVertex.y=P->getPlayerLoc().y;
int dest=getVertex(verticesLoc,findPlayerVertex);

//int source = 0, dest = 7;
//printShortestDistance(adj, source, dest, v);

cout<<endl<<"source is "<<source<<" dest is"<<dest<<endl;
if(source==dest)
{
cout<<"\n"
            " #####     #    #     # ####### ####### #     # ####### ######\n"
            "#     #   # #   ##   ## #       #     # #     # #       #     #\n"
            "#        #   #  # # # # #       #     # #     # #       #     #\n"
            "#  #### #     # #  #  # #####   #     # #     # #####   ######\n"
            "#     # ####### #     # #       #     #  #   #  #       #   #\n"
            "#     # #     # #     # #       #     #   # #   #       #    #\n"
            " #####  #     # #     # ####### #######    #    ####### #     #\n";

}
else if(source<dest && source<=75 && dest<=75)
dist=B.printShortestDistance(adj, source, dest, 75);
else if(source>dest && source<=75 && dest<=75)
dist=B.printShortestDistance(adj, dest, source, 75);
else
E[i].ecollision="false";
cout<<endl<<"the found distance for "<<i<<"is "<<dist;
return dist;
}


/*int getShortestPath(int i)
{
   int dist=distance(E[i].getEnemyLoc().x,E[i].getEnemyLoc().y,P->getPlayerLoc().x,P->getPlayerLoc().y);

/*string node[10][10]={{"n68","n69","n70","na","n71","n72","n73","n74","na","n75"},
                     {"na","na","n61","n62","n63","n64","na","n65","n66","n67"},
                     {"n56","n57","n58","na","na","n59","na","n60","na","na"},
                     {"n46","n47","n48","n49","n50","n51","n52","n53","n54","n55"},
                     {"n41","na","na","na","n43","n44","na","na","na","n45"},
                     {"n31","n32","n33","n34","n35","n36","n37","n38","n39","n40"},
                     {"n23","n24","n25","n26","na","na","n27","n28","n29","n30"},
                     {"na","n15","n16","n17","n18","n19","n20","n21","n22","na"},
                     {"n9","n10","na","na","n11","n12","na","na","n13","n14"},
                     {"na","n1","n2","n3","n4","n5","n6","n7","n8","na"}
					 };

loc n1=find_position(node,"n6");
cout<<"row is "<<n1.x<<"and column is "<<n1.y;
n1.x=0,n1.y=6,n2.x=0,n2.y=4,n3.x=4,n3.y=6,n4.x=4,n4.y=4,n5.x=6,n5.y=6,n6.x=6,n6.y=4;
int w1=distance(E[i].getEnemyLoc().x,E[i].getEnemyLoc().y,(int)n1.x,(int)n1.y);
int w2=distance(E[i].getEnemyLoc().x,E[i].getEnemyLoc().y,(int)n2.x,(int)n2.y);
int w3=distance((int)n1.x,(int)n1.y,(int)n2.x,(int)n2.y);
int w4=distance((int)n1.x,(int)n1.y,(int)n3.x,(int)n3.y);
int w5=distance((int)n2.x,(int)n2.y,(int)n4.x,(int)n4.y);
int w6=distance((int)n3.x,(int)n3.y,(int)n4.x,(int)n4.y);
int w7=distance((int)n3.x,(int)n3.y,(int)n5.x,(int)n5.y);
int w8=distance((int)n3.x,(int)n3.y,(int)n6.x,(int)n6.y);
int w9=distance((int)n4.x,(int)n4.y,(int)n5.x,(int)n5.y);
int w10=distance((int)n4.x,(int)n4.y,(int)n6.x,(int)n6.y);
int w11=distance((int)n5.x,(int)n5.y,(int)n6.x,(int)n6.y);
int w12=distance((int)n5.x,(int)n5.y,P->getPlayerLoc().x,P->getPlayerLoc().y);
int w13=distance((int)n6.x,(int)n6.y,P->getPlayerLoc().x,P->getPlayerLoc().y);
int graph[V][V] = { { 0, w1, w2, 0, 0, 0, 0, 0 },
                     { w1, 0, w3, w4, 0, 0, 0, 0 },
                     { w2, w3, 0, 0, w5, 0, 0, 0 },
                     { 0, w4, 0, 0, w6, w7, w8, 0 },
                     { 0, 0, w5, w6, 0, w9, w10, 0 },
                     { 0, 0, 0, w7, w9, 0, w11, w12},
                     { 0, 0, 0, w8, w10, w11, 0, w13},
                     { 0, 0, 0, 0, 0, w12, w13, 0}};

int dist=path->dijkstra(graph,0);*/
/*return dist;
}*/

int getMin(map<int, int> dist)
{
  pair<int, int> min= *min_element(dist.begin(), dist.end(), CompareSecond());
  return min.first;
}

void Specialkeys(int key, int x, int y)
{
	map<int,int> shortest_dist;
	for(i=0;i<4;i++)
{
    shortest_dist.insert(pair<int, int>(i,getBFSShortest(i)));
    cout<<"\n E"<<i<<" shortest path to player "<<getBFSShortest(i)<<endl;
}
int closest_enemy=getMin(shortest_dist);

cout<<"\n the closest enemy to the player is "<<closest_enemy;
    //bool stop = stopPlayer();
    // Your Code here
    bool killed = false;

    for(int i=0; i<10; i++){
        if(E[i].getEnemyLoc().x == P->getPlayerLoc().x && E[i].getEnemyLoc().y == P->getPlayerLoc().y){
            cout<<"E[i].getEnemyLoc().x: "<<E[i].getEnemyLoc().x<<"E[i].getEnemyLoc().y:  "<<E[i].getEnemyLoc().x<<endl;
            cout<<"P->getPlayerLoc().x: "<<P->getPlayerLoc().x<<"P->getPlayerLoc().y:  "<<P->getPlayerLoc().x<<endl;
            killed = true;
            int enemyN = i;
            cout<<"enemy killing player: "<<i<<endl;
            //E[i].checkEnemyPresent(E[i],E[i+1]);
            continue;
        }
    }

    cout<<"\nenemy x loc"<<E[closest_enemy].getEnemyLoc().x<<"enemy y loc"<<E[closest_enemy].getEnemyLoc().y<<endl;

   cout<<"\nbush x loc"<<M->GetBushLoc().x<<"bush y loc"<<M->GetBushLoc().y<<endl;
           if(E[closest_enemy].getEnemyLoc().x>=(M->GetBushLoc().x-1.2) && E[closest_enemy].getEnemyLoc().x<=(M->GetBushLoc().x+1) && E[closest_enemy].getEnemyLoc().y>=M->GetBushLoc().y && E[closest_enemy].getEnemyLoc().y<=(M->GetBushLoc().y+1))
          {
              cout<<"inside bush";
              block=true;
               //E[closest_enemy].enemyBushCollision("right",M->bushLoc,E[closest_enemy]);
          }


    if(P->getPlayerLoc().x == M->GetChestLoc().x && P->getPlayerLoc().y == M->GetChestLoc().y)
    {
        M->liveChest = false;
              cout<<"\n"
            " #       # ####### #       #        #        #        # ##### #      #\n"
            "  #     #  #     # #       #         #      # #      #    #   # #    #\n"
            "   #   #   #     # #       #          #    #   #    #     #   #  #   #\n"
            "     #     #     # #       #           #  #     #  #      #   #   #  #\n"
            "     #     #     # #       #            ##       ##       #   #     ##\n"
            "     #     ####### #########            #         #     ##### #      #\n";

         exit(0);
    }
    else if(killed)
    {

        P->livePlayer = false;
        cout<<"\n"
            " #####     #    #     # ####### ####### #     # ####### ######\n"
            "#     #   # #   ##   ## #       #     # #     # #       #     #\n"
            "#        #   #  # # # # #       #     # #     # #       #     #\n"
            "#  #### #     # #  #  # #####   #     # #     # #####   ######\n"
            "#     # ####### #     # #       #     #  #   #  #       #   #\n"
            "#     # #     # #     # #       #     #   # #   #       #    #\n"
            " #####  #     # #     # ####### #######    #    ####### #     #\n";
    exit(0);
    }
    int dist = distance(P->getPlayerLoc().x,P->getPlayerLoc().y,E[0].getEnemyLoc().x,E[0].getEnemyLoc().y);
    switch(key)
    {
    case GLUT_KEY_UP:
         cout<< P->getPlayerLoc().x<< "    "<<P->getPlayerLoc().y<<endl;
         //if(!stopPlayer(GLUT_KEY_UP))
         //{
            P->movePlayer("up");
            P->checkCollision(W);
            P->CheckFireCollision(W);
         //}
         //if(dist > 5){
         E[closest_enemy].checkEnemyCollision("up",W,E[closest_enemy],closest_enemy);
         //E[closest_enemy].checkEnemyPresent("up",E[closest_enemy],E[closest_enemy+1],closest_enemy);
         E[closest_enemy].enemyBushCollision("up",M->bushLoc,E[closest_enemy]);
         if(!E[closest_enemy].enemycollision && !E[closest_enemy].ecollision && !E[closest_enemy].bushcollision){
            E[closest_enemy].moveEnemy("up");
         }


         cout<<"\nE"<<closest_enemy<<"moving up";

         //}

         //E[1].moveEnemy("up");
         //E[2].moveEnemy("up");
    break;

    case GLUT_KEY_DOWN:
         cout<< P->getPlayerLoc().x<< "    "<<P->getPlayerLoc().y<<endl;
         //if(!stopPlayer(GLUT_KEY_DOWN))
         //{
            P->movePlayer("down");
            P->checkCollision(W);
         //}
         E[closest_enemy].checkEnemyCollision("down", W ,E[closest_enemy],closest_enemy);
          //E[closest_enemy].checkEnemyPresent("down",E[closest_enemy],E[closest_enemy+1],closest_enemy);
          E[closest_enemy].enemyBushCollision("down",M->bushLoc,E[closest_enemy]);
         if(!E[closest_enemy].enemycollision && !E[closest_enemy].ecollision){
          E[closest_enemy].moveEnemy("down");
         }

         cout<<"\nE"<<closest_enemy<<"moving down";

    break;

    case GLUT_KEY_LEFT:
         cout<< P->getPlayerLoc().x<< "    "<<P->getPlayerLoc().y<<endl;
         //if(!stopPlayer(GLUT_KEY_LEFT))
         //{
            P->movePlayer("left");
            P->checkCollision(W);
         //}
         E[closest_enemy].checkEnemyCollision("left", W ,E[closest_enemy],closest_enemy);
          //E[closest_enemy].checkEnemyPresent("left",E[closest_enemy],E[closest_enemy+1],closest_enemy);
          E[closest_enemy].enemyBushCollision("left",M->bushLoc,E[closest_enemy]);

         if(!E[closest_enemy].enemycollision && !E[closest_enemy].ecollision){
            E[closest_enemy].moveEnemy("left");
         }

         cout<<"\nE"<<closest_enemy<<"moving left";

    break;

    case GLUT_KEY_RIGHT:
        if(!block)
        {
         cout<< P->getPlayerLoc().x<< "    "<<P->getPlayerLoc().y<<endl;
         //if(!stopPlayer(GLUT_KEY_RIGHT))
         //{
            P->movePlayer("right");
            P->checkCollision(W);
         //}
          E[closest_enemy].checkEnemyCollision("right", W ,E[closest_enemy],closest_enemy);
          //E[closest_enemy].checkEnemyPresent("right",E[closest_enemy],E[closest_enemy+1],closest_enemy);
        E[closest_enemy].enemyBushCollision("right",M->bushLoc,E[closest_enemy]);
         if(!E[closest_enemy].enemycollision && !E[closest_enemy].ecollision  && !E[closest_enemy].bushcollision){
            E[closest_enemy].moveEnemy("right");
         }

         cout<<"\nE"<<closest_enemy<<"moving right";
        }
    break;

   }
   block=false;
  glutPostRedisplay();
}

/*void checkEnemyAtLoc(int e)
{
    for(int i = 0; i<4; i++)
    {
        if( i != e)
        {
            if((E[e].getEnemyLoc.x = E[i].getEnemyLoc().x + 1) || ((E[e].getEnemyLoc.x = E[i].getEnemyLoc().x - 1) ||(E[e].getEnemyLoc.y = E[i].getEnemyLoc().y + 1)||(E[e].getEnemyLoc.y = E[i].getEnemyLoc().y + 1))
        }

    }
}*/

/* Program entry point */

int main(int argc, char *argv[])
{

   glutInit(&argc, argv);

   glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
   glutInitWindowSize (800, 800);                //window screen
   glutInitWindowPosition (100, 100);            //window position
   glutCreateWindow ("Maze");                    //program title
   init();
/* cout<<"ABCD"<<endl;
 cout<<"M->GetChestLoc().x: "<<M->GetChestLoc().x<<endl;
 cout<<"M->GetChestLoc().y: "<<M->GetChestLoc().y<<endl;*/

   glutDisplayFunc(display);                     //callback function for display
   glutReshapeFunc(resize);                      //callback for reshape
   glutKeyboardFunc(key);                        //callback function for keyboard
   glutSpecialFunc(Specialkeys);
   glutMouseFunc(mouse);
   glutIdleFunc(idle);
   glutMainLoop();

    	//dijkstra(graph, 0); //testing

   return EXIT_SUCCESS;
}



