

// An OpenGL Keyboard and Mouse Interaction Program

#include <GL/glut.h>
#include <stdio.h>
#include <vector>
#include <iostream>

using namespace std;

// These are defined in a global scope

GLubyte red, green, blue;
int COLORS_DEFINED;

// Specity the values to place and size the window on the screen

const int WINDOW_POSITION_X = 100;
const int WINDOW_POSITION_Y = 100;
const int WINDOW_MAX_X = 700;
const int WINDOW_MAX_Y = 700;

// Specify the coordinate ranges for the world coordinates in the 2D Frame

const float WORLD_COORDINATE_MIN_X = 0.0;
const float WORLD_COORDINATE_MAX_X = 700.0;
const float WORLD_COORDINATE_MIN_Y = 0.0;
const float WORLD_COORDINATE_MAX_Y = 700.0;



//////////////////////////////////////////////////////////////////
struct point{
	float x,y;
};

vector<point> coords;
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
      glColor3ub(200, 0, 255); /* draw in red */
      glPointSize(10.0);

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
void drawBox( int x, int y )
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
void eraseBox( int x, int y )
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

  for(int i=0; i<coords.size()-1; i++){	
	glBegin(GL_LINES);
	 glVertex2i(coords.at(i).x,coords.at(i).y);
	 glVertex2i(coords.at(i+1).x,coords.at(i+1).y);
	glEnd();
  }
	glBegin(GL_LINES);
	 glVertex2i(coords.front().x,coords.front().y);
	 glVertex2i(coords.back().x,coords.back().y);
	glEnd();
	glFlush();
}
//////////////////////////////////////////////////////////////////
bool checkIntersect(){

//counts if any intersections occur
 int interCount = 0;	

	for(int i=0; i<coords.size()-1; i++){	
	 for(int j=1; j<coords.size()-1; j++){
	   
	   if(j!=coords.size()-1){
		//all x's and y's
		int x1 = (coords.at(i).x);
		int x2 = (coords.at(i+1).x);
		int x3 = (coords.at(j).x);
		int x4 = (coords.at(j+1).x);
		int y1 = (WINDOW_MAX_Y-(coords.at(i).y));
		int y2 = (WINDOW_MAX_Y-(coords.at(i+1).y));
		int y3 = (WINDOW_MAX_Y-(coords.at(j).y));
		int y4 = (WINDOW_MAX_Y-(coords.at(j+1).y));
		cout<<x1<<" "<<x2<<" "<<x3<<" "<<x4<<" "<<y1<<" "<<y2<<" "<<y3<<" "<<y4<<endl;
		//parts of the matrix needed to find determinate
		int p1= (x3-x1);
		int p2= -(y4-y3);
		int p3= (y3-y1);
		int p4= -(x4-x3);
		int p5= (x2-x1);
		int p6= (y2-y1);
		cout<<p1<<" "<<p2<<" "<<p3<<" "<<p4<<" "<<p5<<" "<<p6<<endl;
		//find nomenator determinate and denominator determinate
		int uaNomDet= ((p1*p2)-(p3*p4));
		int ubNomDet= ((p5*p3)-(p6*p1));
		int denomDet= ((p5*p2)-(p6*p4));
		cout<<uaNomDet<<" "<<ubNomDet<<" "<<denomDet<<endl;
	  // finds ua from two determinates		
	  float ua = (float)(uaNomDet/denomDet);	
	  float ub = (float)(ubNomDet/denomDet);	 		
		cout<<ua<<" "<<ub<<endl;
	  if((ua>1)&&(ub>1)){interCount++;}
	  	
	  }
	  /*else{
	   //all x's and y's
		int x1 = (coords.at(i).x);
		int x2 = (coords.at(i+1).x);
		int x3 = (coords.at(i).x);
		int x4 = (coords.at(j).x);
		int y1 = (WINDOW_MAX_Y-(coords.at(i).y));
		int y2 = (WINDOW_MAX_Y-(coords.at(i+1).y));
		int y3 = (WINDOW_MAX_Y-(coords.at(i).y));
		int y4 = (WINDOW_MAX_Y-(coords.at(j).y));
		cout<<x1<<" "<<x2<<" "<<x3<<" "<<x4<<" "<<y1<<" "<<y2<<" "<<y3<<" "<<y4<<endl;
		//parts of the matrix needed to find determinate
		int p1= (x3-x1);
		int p2= -(y4-y3);
		int p3= (y3-y1);
		int p4= -(x4-x3);
		int p5= (x2-x1);
		int p6= (y2-y1);
		cout<<p1<<" "<<p2<<" "<<p3<<" "<<p4<<" "<<p5<<" "<<p6<<endl;
		//find nomenator determinate and denominator determinate
		int uaNomDet= ((p1*p2)-(p3*p4));
		int ubNomDet= ((p5*p3)-(p6*p1));
		int denomDet= ((p5*p2)-(p6*p4));
		cout<<uaNomDet<<" "<<ubNomDet<<" "<<denomDet<<endl;
	  // finds ua from two determinates		
	  float ua = (float)(uaNomDet/denomDet);	
	  float ub = (float)(ubNomDet/denomDet);	 		
		cout<<ua<<" "<<ub<<endl;
	   if((ua>1)&&(ub>1)){interCount++;}
		
	  }*/
	 }
	}
  if(interCount>0)
	return true;

  else
	return false;
}
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
	point temp;
	temp.x=x;
	temp.y=WINDOW_MAX_Y-y;
	coords.push_back(temp); 
        drawBox( x, WINDOW_MAX_Y-y );
	drawLines();
	 if(checkIntersect()){
	  cout<<"The polygon created by these points is invalid due to two lines intersecting."<<endl;
	  //clearBox();	
	  }
	 else{
	   cout<<"no intersections"<<endl;
	  }
	
     }
  
 /* if ( button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN )
     {
        printf ("%d   %d\n", x,y);
        clearBox();
     }*/
}

//////////////////////////////////////////////////////////////////
void keyboard( unsigned char key, int x, int y )
{ 
  if ( key == 'q' || key == 'Q') exit(0);
  if ( key == 'f' || key == 'F')        ;
  if ( key == 't' || key == 'T')        ;
  if ( key == 'i' || key == 'I')        ;
  if ( key == 'p' || key == 'P')        ;
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

