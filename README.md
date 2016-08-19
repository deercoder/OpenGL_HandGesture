README
=====

##HOW to configure in Xcode for OpenGLDemo

Check this post for detail: http://lnx.cx/docs/opengl-in-xcode/


##Tracking

### August 16th
* Compile issue under Mac: updated OpenGL/GLut.h files.
* Remove unnecessary files and components.

### August 17th
* add mouse listener, fix the issue of not responding. (must placed after display callback)
* add translation function to deal with location move/change.
* fix the issue of display, cannot refresh/re-display the ball.
* fix mouse listener's drawing, change the coordinates(ballX,ballY,ballZ), and
only draw it in the display function with the glTranslatef()
* minor/major fix for keyboard control with respect to the shape and location of ball

### August 18th
* remove shadow, change move/scale(use larger changes/scales)
* make the sphere more round(use more slices/stacks)
* set GLUT initial window position and size
* add reshape function to avoid being ellipse instead of circle(avoid losing original shape)
* add color control, use `c` to randomly change the color of sphere
* add rolling effect, when moving upside/down/left/right


## Guide

* h - **move the ball to the left**
* l - **move the ball to the right**
* j - **move down**
* k - **move up**
* p - **enlarge the ball, increase scale**
* q - **make the ball smaller, decrease scale**
