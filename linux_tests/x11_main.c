#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xresource.h>

#include "../libs/conf.h"
#include "../libs/log.h"

static void drawTest(Display* display, Window win, int screenNum);

int main(int argc, char* argv[]) {

    char* file = "../conf/my_tools.conf";
    conf_load(file);

    Display* display = XOpenDisplay(":0");
    if (display == NULL) {
        fprintf(stderr, "Cannot connect to X server %s\n", "simey:0");
        exit (-1);
    }


    int screenNum = DefaultScreen(display);
    int screenWidth = DisplayWidth(display, screenNum);
    int screenHeight = DisplayHeight(display, screenNum);
    printf("screenNum:%d, screenWidth:%d, screenHeight:%d \n", screenNum, screenWidth, screenHeight);

    int winWidth = screenWidth /3;
    int winHeight = screenHeight /3;

    int winX = 0;
    int winY = 0;

    long backgroundColor = BlackPixel(display, screenNum);//BlackPixel
    long borderColor = WhitePixel(display, screenNum);//WhitePixel

    int winBorderWidth = 10;

    Window win = XCreateSimpleWindow(display,
                                    RootWindow(display, screenNum),
                                    winX, winY,
                                    winWidth, winHeight,
                                    winBorderWidth,
                                    borderColor,
                                    backgroundColor);

    XSelectInput(display, win, ButtonPressMask|StructureNotifyMask|ExposureMask );

    XMapWindow(display, win);

    XFlush(display);
    XSync(display, 1);

    XEvent event;
    while(1){
        XNextEvent(display, &event);
        switch(event.type){
            case Expose:
                drawTest(display, win, screenNum);
                break;
            case ConfigureNotify:
                if (winWidth != event.xconfigure.width
                            || winHeight != event.xconfigure.height) {
                    winWidth = event.xconfigure.width;
                    winHeight = event.xconfigure.height;
                    printf("Size changed to: %d by %d \n", winWidth, winHeight);
                }
                break;
            case ButtonPress:
                XCloseDisplay(display);
                return 0;
        }
    }

    return 0;
}

static void drawTest(Display* display, Window win, int screenNum) {

    XGCValues values;
    values.cap_style = CapButt;
    values.join_style = JoinBevel;
    values.foreground = WhitePixel(display, screenNum);
    values.line_width = 1;
    values.line_style = LineSolid;

    unsigned long valueMask = GCCapStyle|GCJoinStyle|GCForeground|GCLineWidth|GCLineStyle;

    GC gc = XCreateGC(display, win, valueMask, &values);
    if (gc < 0) {
        fprintf(stderr, "XCreateGC: \n");
    }


//    XSetBackground(display, gc, BlackPixel(display, screenNum));

    XSetFillStyle(display, gc, FillSolid);

    XSetLineAttributes(display, gc, 2, LineSolid, CapRound, JoinRound);


/* draw a pixel at position '5,60' (line 5, column 60) of the given window. */
//    XDrawPoint(display, win, gc, 5, 5);

/* draw a line between point '20,20' and point '40,100' of the window. */
    XDrawLine(display, win, gc, 20, 20, 40, 100);

/* draw an arc whose center is at position 'x,y', its width (if it was a     */
/* full ellipse) is 'w', and height is 'h'. Start the arc at angle 'angle1'  */
/* (angle 0 is the hour '3' on a clock, and positive numbers go              */
/* counter-clockwise. the angles are in units of 1/64 of a degree (so 360*64 */
/* is 360 degrees).                                                          */
    int x = 30, y = 40;
    int h = 15, w = 45;
    int angle1 = 0, angle2 = 2.109;
//    XDrawArc(display, win, gc, x-(w/2), y-(h/2), w, h, angle1, angle2);

/* now use the XDrawArc() function to draw a circle whose diameter */
/* is 15 pixels, and whose center is at location '50,100'.         */
    XDrawArc(display, win, gc, 50-(15/2), 100-(15/2), 15, 15, 0, 360*64);

/* the XDrawLines() function draws a set of consecutive lines, whose     */
/* edges are given in an array of XPoint structures.                     */
/* The following block will draw a triangle. We use a block here, since  */
/* the C language allows defining new variables only in the beginning of */
/* a block.                                                              */
    {
        /* this array contains the pixels to be used as the line's end-points. */
        XPoint points[] = {
                {0, 0},
                {15, 15},
                {0, 15},
                {0, 0}
        };
        /* and this is the number of pixels in the array. The number of drawn */
        /* lines will be 'npoints - 1'.                                       */
        int npoints = sizeof(points)/sizeof(XPoint);

        /* draw a small triangle at the top-left corner of the window. */
        /* the triangle is made of a set of consecutive lines, whose   */
        /* end-point pixels are specified in the 'points' array.       */
        XDrawLines(display, win, gc, points, npoints, CoordModeOrigin);
    }

/* draw a rectangle whose top-left corner is at '120,150', its width is */
/* 50 pixels, and height is 60 pixels.                                  */
    XDrawRectangle(display, win, gc, 120, 150, 50, 60);

/* draw a filled rectangle of the same size as above, to the left of the  */
/* previous rectangle. note that this rectangle is one pixel smaller than */
/* the previous line, since 'XFillRectangle()' assumes it is filling up   */
/* an already drawn rectangle. This may be used to draw a rectangle using */
/* one color, and later to fill it using another color.                   */
    XFillRectangle(display, win, gc, 60, 150, 50, 60);
}