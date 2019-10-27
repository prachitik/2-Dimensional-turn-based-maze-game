#ifndef BUTTON_H
#define BUTTON_H

#include<CommonThings.h>
#include<string.h>
#include<gl/gl.h>
#include<GL/glut.h>
#include<SOIL.h>
#include<iostream>
#include <Timer.h>
#include <math.h>       /* ceil */

class Console_Button
{
    public:
        Console_Button()
        {

        }

        void TheButtonCallback();
        void Font(void *,char *,int,int);
        int ButtonClickTest(Console_Button*,int,int);
        void ButtonRelease(Console_Button *,int,int);
        void ButtonPress(Console_Button *,int,int);
        void ButtonPassive(Console_Button *,int,int);
        void ButtonDraw(Console_Button *);
        void Draw2D();
        void DrawButton();
        void Resize(int,int);
        void MouseButton(int,int,int,int);
        void MouseMotion(int,int);
        void MousePassiveMotion(int,int);
};

#endif
