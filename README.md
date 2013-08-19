Code Reuse:

TA Code to get started
Marke Kolezar
http://pages.cpsc.ucalgary.ca/~mtkolesz/index.php?n=Teaching.IntroductionToComputerGraphics-CPSC453

Ta Code for virtual Trackball
Erica Harrison
http://pages.cpsc.ucalgary.ca/~eharris/cpsc453/tut09/

Compliling:
-navigate to director this README is in.
-Ensure that you are using the latest version of QT on the lab machines
-run qmake
-run make
-./MD2Viewer

Data Structures/Algorithms
-Used the provided md2.h file.  It had its own data structure to hold the md2 file and the mappings to place
the texture on the model.
-Used the generic algorithm to calculate the cross product for face normals and the algorithm described
in the lecture notes to determine the vertex normals

User manual
The application should be quite easy to use as the UI is quite self explanatory.
There are 4 Tabs: Models and Textures, Rendering, Transformations, Views.

Models and Textures:
   -There are 4 buttons here, each one opens a file browser to pick either a model or a texture.
   -After selection the name of the file opened will be listed below the button

Rendering:
   -There are 2 sections here, Display mode and Optional Display items

      Display Mode:
      -Select either wireframe, flat shading, or smooth shading.

      Optional Display Items:
      -Allows you to hide/show the groundsheet, vertex normals, and face normals.

Transformations:
   -4 sliders for each transformation(translation and scaling), x,y,z,all
   -scaling can also be done by the roll ball on the mouse
   -Rotation done via trackball rotation
   -Reset all button resets all transformations.

Views:
   -3 view changes posssible, Location, Direction, Orientation, 3 sliders for each, x,y,z
   -Reset all button resets all view changes.

Bonus's:
-To much other work to do bonus's at this time, might do animation before demoing just to see how it works.
