Ron Stuchevsky | 101188412
COMP 4900 A3


========================================================
Code Breakdown
========================================================

ofApp - Responsible for setting up the image dimension, camera view, doing the raycasting algorithm, as well as calculating the 
3 point lighting and shadow test, then coloring each pixel in the image accordingly.

Ray - a helper class useful for defining a ray object that will be intersecting with the world objects.

Sphere - defines how a sphere object is represented in the world and how to calculate if the sphere is hit, 
	also holds the definition for a helper HitRecord class which holds the relevant info from a registered hit about the sphere
	that is used later to compute its color.

LightSource - a helper class that defines a light source in the world, and holds useful info like its position that is used later 
to calculate the spheres color if it is able to "see" the light source (passes raycast shadow test)

 

========================================================
How to Run
========================================================
* Make a new oF project with the builder and pray it actually generates.

* Drag the src folder from the zip here into the new project you generated to replace the empty src folder there.

* Open visual studio and right click the src folder -> add -> existing item -> And select all the other files in the folder 
to be added to the .vcxproj file of the solution (needs to be linked for the entire thing to build properly).

* Build oFLib and then the project in debug/release x64 and hit the green run button in visual studio.
(raycast image will be displayed or you can find it saved in the /bin/data folder of the project)

