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





## Guide

* h - **move the ball to the left**
* l - **move the ball to the right**
* j - **move down**
* k - **move up**
* p - **enlarge the ball, increase scale**
* q - **make the ball smaller, decrease scale**
