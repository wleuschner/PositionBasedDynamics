# README #

[![PBD](http://img.youtube.com/vi/N3WlHEbX9K8/0.jpg)](https://www.youtube.com/watch?v=N3WlHEbX9K8 "PBD")

The code in this repository implements the Position Based Dynamics algorithm from Matthias Müller et. al. using Qt, OpenGL 3.3. To run the application, an OpenGL 3.3 capable graphics card is needed.
Further the following packages need to be installed:

  * Qt (>=4.5)
  * OpenGL (>=3.3)
  * GLM 
  
The repository is build by issuing qmake inside of the root of the repository followed by a make. Make sure the Shaders directory is in the same directory as the executable to get a rendering.
To move in the scene, the WASD keys are used. To rotate the camera, the arrow keys are used. Three scenes are available. The first scene allows the user to shoot spheres onto a soft-body by using the 'E' key.
The second scene shows a softbody falling onto the ground without self collision and the third scene allows the user to play with the pressure constraint. Have fun and playwith the options given by the GUI.

A video of the application can be found at https://www.youtube.com/watch?v=N3WlHEbX9K8
