/*
Dylan Resha
csc 315 Assignment 1
Fall 2018
Tessallation on simple Polygons, no holes or intersections
*/
// An OpenGL Keyboard and Mouse Interaction Program

#include <GL/glut.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

// These are defined in a global scope

GLubyte red, green, blue;
int COLORS_DEFINED;

// Specity the values to place and size the window on the screen

const int WINDOW_POSITION_X = 100;
const int WINDOW_POSITION_Y = 100;
const int WINDOW_MAX_X = 800;
const int WINDOW_MAX_Y = 800;

// Specify the coordinate ranges for the world coordinates in the 2D Frame

const float WORLD_COORDINATE_MIN_X = 0.0;
const float WORLD_COORDINATE_MAX_X = 800.0;
const float WORLD_COORDINATE_MIN_Y = 0.0;
const float WORLD_COORDINATE_MAX_Y = 800.0;


//structs to be used for points lines and triangles
//////////////////////////////////////////////////////////////////
//struct that holds the x and y values of a point as floats
struct point{
	float x,y;
};

//////////////////////////////////////////////////////////////////
//struct that holds two points to creat a line
struct line{
	point a,b;

};
//////////////////////////////////////////////////////////////////
//struct that holds 3 points to make a triangle
struct triangle{
	point v1,v2,v3;
};

//vectors to hold my lists in
vector<point> coords;
vector<line> lineList;
vector<triangle> triList;
//////////////////////////////////////////////////////////////////
void myglutInit( int argc, char** argv )
{
    glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); /* default, not needed */
    glutInitWindowSize(WINDOW_MAX_X,WINDOW_MAX_Y); /* set pixel window */
    glutInitWindowPosition(WINDOW_POSITION_X, WINDOW_POSITION_Y); /* place window top left on display */
    glutCreateWindow("Mouse and Keyboard Interaction"); /* window title */
}

//////////////////////////////////////////////////////////////////
void myInit(void)
{
 
/* standard OpenGL attributes */

      glClearColor(1.0, 1.0, 1.0, 1.0); /* white background */
      glColor3ub(150, 0, 255); /* draw in purple */
      glPointSize(1.0);

      COLORS_DEFINED = 0;

/* set up viewing window with origin lower left */

      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluOrtho2D(WORLD_COORDINATE_MIN_X, WORLD_COORDINATE_MAX_X,
                 WORLD_COORDINATE_MIN_Y, WORLD_COORDINATE_MAX_Y);
      glMatrixMode(GL_MODELVIEW);
}

//////////////////////////////////////////////////////////////////
void display( void )
{

/* define a point data type */

    typedef GLfloat point[2];     

    point p; /* A point in 2-D space */

    glClear(GL_COLOR_BUFFER_BIT);  /*clear the window */

    if (!COLORS_DEFINED) {
       red   = 200;
       green = 0; 
       blue  = 255;
    }

    glColor3ub( red, green, blue ); 

    /* define point */

   /* p[0] = 100; 
    p[1] = 100;
   
    /* plot new point */

      /*  glBegin(GL_POINTS);
            glVertex2fv(p); 
        glEnd();*/
  
     
     glFlush(); /* clear buffers */

 }

//////////////////////////////////////////////////////////////////
void drawBox( float x, float y )
{
    typedef GLfloat point[2];     
    point p;
 
    glColor3ub( red, green, blue );
   
    p[0] = x;
    p[1] = y;  
    
        glBegin(GL_POINTS);
            glVertex2fv(p); 
        glEnd();
        glFlush();
}

//////////////////////////////////////////////////////////////////
void eraseBox( float x, float y )
{
    typedef GLfloat point[2];     
    point p;

    glColor3f( 1.0, 1.0, 1.0 );

    p[0] = x;
    p[1] = y;  

    glBegin(GL_POINTS);
      glVertex2fv(p); 
    glEnd();
    glFlush();
}

//////////////////////////////////////////////////////////////////
void clearBox()
{
       glClear(GL_COLOR_BUFFER_BIT); 
       glFlush();
}
//////////////////////////////////////////////////////////////////
void drawLines(){
//loop to draw all of my lines
  for(int i=0; i<coords.size()-1; i++){	
	glBegin(GL_LINES);
	 glVertex2i(coords.at(i).x,coords.at(i).y);
	 glVertex2i(coords.at(i+1).x,coords.at(i+1).y);
	glEnd();
  }
//drawing the last line that is from my last vertex to my first firtex
	glBegin(GL_LINES);
	 glVertex2i(coords.front().x,coords.front().y);
	 glVertex2i(coords.back().x,coords.back().y);
	glEnd();
	glFlush();
}
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//method to empty out my list of triangles
void triEmpty(){
triList.clear();
}
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//method to clear the screen and redraw my polygon without tessallation
void resetPoly()
{
 glClearColor(1.0,1.0,1.0,1.0);
 glClear(GL_COLOR_BUFFER_BIT);
 drawLines();
 triEmpty();
}
//////////////////////////////////////////////////////////////////
//method to check if two lines intersect
bool checkIntersect(int m, int l){
              //all x's and y's
		float x1 = (lineList.at(m).a.x);
		float x2 = (lineList.at(m).b.x);
		float x3 = (lineList.at(l).a.x);
		float x4 = (lineList.at(l).b.x);
		float y1 = (WINDOW_MAX_Y-(lineList.at(m).a.y));
		float y2 = (WINDOW_MAX_Y-(lineList.at(m).b.y));
		float y3 = (WINDOW_MAX_Y-(lineList.at(l).a.y));
		float y4 = (WINDOW_MAX_Y-(lineList.at(l).b.y));
		
		//parts of the matrix needed to find determinate
		float p1= (x3-x1);
		float p2= -(y4-y3);
		float p3= (y3-y1);
		float p4= -(x4-x3);
		float p5= (x2-x1);
		float p6= (y2-y1);
		
		//find nomenator determinate and denominator determinate
		float uaNomDet= ((p1*p2)-(p3*p4));
		float ubNomDet= ((p5*p3)-(p6*p1));
		float denomDet= ((p5*p2)-(p6*p4));
		
	  // finds ua from two determinates		
	  float ua = (uaNomDet/denomDet);	
	  float ub = (ubNomDet/denomDet);
	//if statement to see if the values of ua and ub are between 0 and 1
	if((ua<1&&ua>0)&&(ub<1&&ub>0)){return true;}
	
return false;
}
//////////////////////////////////////////////////////////////////
bool polyIntersect(){

//simple double for loop to check all lines in the list
	for(int i=0; i<lineList.size()-1; i++){
	   int j = (i+1);	
	 for(int k=0; k<lineList.size()-3; k++){
		
		if(checkIntersect(i,j%lineList.size())){return true;}
		j++;
 	  }
	 }
	

return false;
}
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
void drawNoTess(){

//simple double for loops to fill polygon useing the verticies
for(int i=0; i<coords.size()-1; i++){
 for(int j=1; j<coords.size()-1; j++){     
	glBegin(GL_POLYGON);
	 glVertex2i(coords.at(i).x,coords.at(i).y);
	 glVertex2i(coords.at(i+1).x,coords.at(i+1).y);
	 glVertex2i(coords.at(j%coords.size()).x,coords.at(j%coords.size()).y);
	 glVertex2i(coords.at(j+1%coords.size()).x,coords.at(j+1%coords.size()).y);
    	glEnd();

  }
 }
glFlush();
}
//////////////////////////////////////////////////////////////////
void drawTess(){

//fills in polygon by filling each triangle in the list of triangles
	for(int i=0; i<triList.size(); i++){
	glBegin(GL_POLYGON);
	 glVertex2i(triList.at(i).v1.x,triList.at(i).v1.y);
	 glVertex2i(triList.at(i).v2.x,triList.at(i).v2.y);
	 glVertex2i(triList.at(i).v3.x,triList.at(i).v3.y);
	 glVertex2i(triList.at(i).v1.x,triList.at(i).v1.y);
    	glEnd();
  }
 glFlush();
}
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
bool concave(int v1, int v2, int v3, vector<point>& temp){
//checks the concavity of the current 3 vertices

int L1x = (temp.at(v1%temp.size()).x)-(temp.at(v2%temp.size()).x);
int L1y = (temp.at(v1%temp.size()).y)-(temp.at(v2%temp.size()).y);
int L2x = (temp.at(v3%temp.size()).x)-(temp.at(v2%temp.size()).x);
int L2y = (temp.at(v3%temp.size()).y)-(temp.at(v2%temp.size()).y);
//cross product of lines that creat current angle
float cross = (L1x*L2y)-(L2x*L1y);

if(cross<0){return true;}
if(cross==0){temp.erase(temp.begin()+v2);}//removes midpoint if a straight line would be created

return false;
}
//////////////////////////////////////////////////////////////////
//method that checks to see if the new line to be created is inside of the polygon
bool insidePoly(int v0, int v1, int v2, int v3,vector<point>& temp){
	
//creating lines for cross and dot products
int L1x = (temp.at(v1%temp.size()).x)-(temp.at(v2%temp.size()).x);
int L1y = (temp.at(v1%temp.size()).y)-(temp.at(v2%temp.size()).y);
int L2x = (temp.at(v3%temp.size()).x)-(temp.at(v2%temp.size()).x);
int L2y = (temp.at(v3%temp.size()).y)-(temp.at(v2%temp.size()).y);
int L3x = (temp.at(v0%temp.size()).x)-(temp.at(v2%temp.size()).x);
int L3y = (temp.at(v0%temp.size()).y)-(temp.at(v2%temp.size()).y);

//cross product of the next angle to see if it is concave
float cross = (L1x*L2y)-(L2x*L1y);

     if(cross>=0){return true;}
     if(cross<0){	
	float numerA = (L1x*L3x)+(L1y*L3y);
	float denomA = sqrt(pow(L1x,2)+pow(L1y,2))*sqrt(pow(L3x,2)+pow(L3y,2));
	float angleA = acos(numerA/denomA);
		
	float numerB = (L1x*L2x)+(L1y*L2y);
	float denomB = sqrt(pow(L1x,2)+pow(L1y,2))*sqrt(pow(L2x,2)+pow(L2y,2));
	float angleB = acos(numerB/denomB);
		
	if(angleA<angleB){return true;}
	
	}
 
 return false;
}
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//method that finds the area of each triangle that is made, and the total area of the polygon
void triAreas(){
cout<<"Area of all Triangles in Pixels"<<endl;
cout<<"-------------------------------"<<endl;
float totalA=0;
 for(int i=0; i<triList.size();i++){
	float area,Ax,Ay,Bx,By,Cx,Cy;
	Ax= triList.at(i).v1.x;
	Ay= triList.at(i).v1.y;
	Bx= triList.at(i).v2.x;
	By= triList.at(i).v2.y;
	Cx= triList.at(i).v3.x;
	Cy= triList.at(i).v3.y;
	
	area = fabs(((Ax*(By-Cy))+(Bx*(Cy-Ay))+(Cx*(Ay-By)))/2);
	totalA += area;
	cout<<area<<endl;

 }
cout<<"Total Area of Polygon = "<<totalA<<endl;

}
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
// this method goes through the entire polygon and tessalates by the ear clipping method
void tessalate(){

// filling up a temp list
vector<point> temp;
for(int i=0; i<coords.size(); i++){
	temp.push_back(coords.at(i));
}	
  
  //looping through the temp list of points and checking in groups of 3 to see if they are concave
  //seeing if the line that would be created is inside the polygon
  //if it is inside the polygon then we check to see if the line intersects with any line in the polygon
  //if we have no intersections then we add the vertices to the list of triangles, delete the middle verticies from the temp list, and draw the line

  for(int i=0; i<temp.size()-1; i++){
   if(concave(i,(i+1)%temp.size(),(i+2)%temp.size(),temp)){
	if(insidePoly(i,(i+1)%temp.size(),(i+2)%temp.size(),(i+3)%temp.size(),temp)){
				
		line newLine;
		newLine.a=temp.at(i);
		newLine.b=temp.at((i+2)%temp.size());
		lineList.push_back(newLine);

	      if(polyIntersect()){
		 lineList.pop_back();
		
		}//end if polyIntersect
		else if(!polyIntersect()){
		   glBegin(GL_LINES);
	 	    glVertex2i(lineList.back().a.x,lineList.back().a.y);
		    glVertex2i(lineList.back().b.x,lineList.back().b.y);
	           glEnd();
		   glFlush();
		   		    
		   //add triangle
		   triangle tempTri;
		   tempTri.v1 = temp.at(i%temp.size());
		   tempTri.v2 = temp.at((i+1)%temp.size());
                   tempTri.v3 = temp.at((i+2)%temp.size());

			
		   triList.push_back(tempTri);
		   //remove mid point	
		   temp.erase(temp.begin()+i+1);
			i=-1;
			
                 }//end else if	
     	}//end if insidePoly
	
    }//end if concave
   }//end for
//setup to add the last triangle to the list of triangles
triangle lastTri;
lastTri.v1=temp.at(0);
lastTri.v2=temp.at(1);
lastTri.v3=temp.at(2);
triList.push_back(lastTri);
//gives the area of the triangles and the total area
triAreas();
}
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
void mouse( int button, int state, int x, int y)
{ 



  if ( button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN )
     {
        printf ("%d   %d\n", x, y);
	point temp;
	temp.x=x;
	temp.y=WINDOW_MAX_Y-y;
	coords.push_back(temp); 
        drawBox( x, WINDOW_MAX_Y-y );
     }

  if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN )
     {
	printf ("%d   %d\n", x, y);
	//temporary point used to store values in our list	
	point temp;
	temp.x=x;
	temp.y=WINDOW_MAX_Y-y;
	coords.push_back(temp); 
        drawBox( x, WINDOW_MAX_Y-y );
	drawLines();
	//fill lineList using a temp line holder
	line tempLine;
 	 for(int i=0; i<coords.size()-1; i++){	
	tempLine.a=coords.at(i);
	tempLine.b=coords.at(i+1%coords.size());	
	lineList.push_back(tempLine);

  	 }
	tempLine.a=coords.front();
	tempLine.b=coords.back();	
	lineList.push_back(tempLine);
	//checks if the polygon that is created has any intersections
	 if(polyIntersect()){
	  cout<<"The polygon created by these points is invalid due to two lines intersecting."<<endl;
	  	
	  }
	 else{
	   cout<<"no intersections"<<endl;
	  }
	
     }
  
  if ( button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN )
     {
	//compleatly resets the graphics window to be used for new polygons
        printf ("%d   %d\n", x,y);
	coords.clear();
	lineList.clear();
	triList.clear();
        clearBox();
     }
}
//////////////////////////////////////////////////////////////////
void keyboard( unsigned char key, int x, int y )
{ 
  if ( key == 'q' || key == 'Q') exit(0);
  if ( key == 'f' || key == 'F') drawNoTess();
  if ( key == 't' || key == 'T') {resetPoly();tessalate();}
  if ( key == 'i' || key == 'I') resetPoly();
  if ( key == 'p' || key == 'P') {resetPoly();tessalate();drawTess();}
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    
    myglutInit(argc,argv); /* Set up Window */
    myInit(); /* set attributes */

    // Now start the standard OpenGL glut callbacks //
    
    glutMouseFunc(mouse);  /* Define Mouse Handler */
    glutKeyboardFunc(keyboard); /* Define Keyboard Handler */
    glutDisplayFunc(display); /* Display callback invoked when window opened */
    glutMainLoop(); /* enter event loop */
}

