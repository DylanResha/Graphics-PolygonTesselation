

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
	   
	   if(i==j){j++;}
	   if(j!=coords.size()-1){
		//all x's and y's
		float x1 = (coords.at(i).x);
		float x2 = (coords.at(i+1).x);
		float x3 = (coords.at(j).x);
		float x4 = (coords.at(j+1).x);
		float y1 = (WINDOW_MAX_Y-(coords.at(i).y));
		float y2 = (WINDOW_MAX_Y-(coords.at(i+1).y));
		float y3 = (WINDOW_MAX_Y-(coords.at(j).y));
		float y4 = (WINDOW_MAX_Y-(coords.at(j+1).y));
		//cout<<x1<<" "<<x2<<" "<<x3<<" "<<x4<<" "<<y1<<" "<<y2<<" "<<y3<<" "<<y4<<endl;
		//parts of the matrix needed to find determinate
		float p1= (x3-x1);
		float p2= -(y4-y3);
		float p3= (y3-y1);
		float p4= -(x4-x3);
		float p5= (x2-x1);
		float p6= (y2-y1);
		//cout<<p1<<" "<<p2<<" "<<p3<<" "<<p4<<" "<<p5<<" "<<p6<<endl;
		//find nomenator determinate and denominator determinate
		float uaNomDet= ((p1*p2)-(p3*p4));
		float ubNomDet= ((p5*p3)-(p6*p1));
		float denomDet= ((p5*p2)-(p6*p4));
		//cout<<uaNomDet<<" "<<ubNomDet<<" "<<denomDet<<" in if"<<endl;
	  // finds ua from two determinates		
	  float ua = (uaNomDet/denomDet);	
	  float ub = (ubNomDet/denomDet);	 		
		//cout<<ua<<" "<<ub<<endl;
		
	  if((fabs(ua)<1 && fabs(ub)<1)&&(fabs(ua)>0 && fabs(ub)>0)){interCount++;}
	  	
	  }
	  else{
	   //all x's and y's
		int k = 0;
		float x1 = (coords.at(k).x);
		float x2 = (coords.at(k+1).x);
		float x3 = (coords.at(j).x);
		float x4 = (coords.at(k).x);
		float y1 = (WINDOW_MAX_Y-(coords.at(k).y));
		float y2 = (WINDOW_MAX_Y-(coords.at(k+1).y));
		float y3 = (WINDOW_MAX_Y-(coords.at(j).y));
		float y4 = (WINDOW_MAX_Y-(coords.at(k).y));
		//cout<<x1<<" "<<x2<<" "<<x3<<" "<<x4<<" "<<y1<<" "<<y2<<" "<<y3<<" "<<y4<<endl;
		//parts of the matrix needed to find determinate
		float p1= (x3-x1);
		float p2= -(y4-y3);
		float p3= (y3-y1);
		float p4= -(x4-x3);
		float p5= (x2-x1);
		float p6= (y2-y1);
		//cout<<p1<<" "<<p2<<" "<<p3<<" "<<p4<<" "<<p5<<" "<<p6<<endl;
		//find nomenator determinate and denominator determinate
		float uaNomDet= ((p1*p2)-(p3*p4));
		float ubNomDet= ((p5*p3)-(p6*p1));
		float denomDet= ((p5*p2)-(p6*p4));
		//cout<<uaNomDet<<" "<<ubNomDet<<" "<<denomDet<<" in else"<<endl;
	  // finds ua from two determinates		
	  float ua = (uaNomDet/denomDet);	
	  float ub = (ubNomDet/denomDet);	 		
		//cout<<ua<<" "<<ub<<endl;
	   if((fabs(ua)<1 && fabs(ub)<1)&&(fabs(ua)>0 && fabs(ub)>0)){interCount++;}
		
	  }
	 }
	}
  if(interCount>0)
	return true;

  else
	return false;
}
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
void drawNoTess(){

for(int i=0; i<coords.size()-1; i++){
     if(coords.size()>=4 && (i+3)<=(coords.size()-1)){	
	glBegin(GL_POLYGON);
	 glVertex2i(coords.at(i).x,coords.at(i).y);
	 glVertex2i(coords.at(i+1).x,coords.at(i+1).y);
	 glVertex2i(coords.at(i+2).x,coords.at(i+2).y);
	 glVertex2i(coords.at(i+3).x,coords.at(i+3).y);
    	glEnd();
      }
     else if(coords.size()==3){
	glBegin(GL_POLYGON);
	 glVertex2i(coords.at(i).x,coords.at(i).y);
	 glVertex2i(coords.at(i+1).x,coords.at(i+1).y);
	 glVertex2i(coords.at(i+2).x,coords.at(i+2).y);
	 glVertex2i(coords.at(i).x,coords.at(i).y);
    	glEnd();
      }	

}
	int k=0;
	int l= ((coords.size()-1)*(1/4));
	int m= ((coords.size()-1)*(3/4));
/////////////////////////////////////////////////////////////////
	glBegin(GL_POLYGON);
	 glVertex2i(coords.front().x,coords.front().y);
	 glVertex2i(coords.at(k+1).x,coords.at(k+1).y);
	 glVertex2i(coords.at(k+2).x,coords.at(k+2).y);
	 glVertex2i(coords.back().x,coords.back().y);
    	glEnd();
/////////////////////////////////////////////////////////////////
	glBegin(GL_POLYGON);
	 glVertex2i(coords.front().x,coords.front().y);
	 glVertex2i(coords.at(l).x,coords.at(l).y);
	 glVertex2i(coords.at(m).x,coords.at(m).y);
	 glVertex2i(coords.back().x,coords.back().y);
    	glEnd();


	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);
	glFlush();


}
//////////////////////////////////////////////////////////////////
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
  if ( key == 'f' || key == 'F') drawNoTess();
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

