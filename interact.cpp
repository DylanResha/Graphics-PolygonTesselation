

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
struct line{
	point a,b;

};
vector<line> lineList;
//////////////////////////////////////////////////////////////////
struct triangle{
	point v1,v2,v3;
};
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
      glColor3ub(200, 0, 255); /* draw in red */
      glPointSize(5.0);

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

	if((ua<1&&ua>0)&&(ub<1&&ub>0)){return true;}
	
return false;
}
//////////////////////////////////////////////////////////////////
bool polyIntersect(){


	cout<<lineList.size()<<endl;
	for(int i=0; i<lineList.size()-1; i++){
	   int j = (i+1);	
	 for(int k=0; k<coords.size()-3; k++){
		
		if(checkIntersect(i,j%lineList.size())){return true;}
		j++;
 	  }
	 }
	

return false;
}
//////////////////////////////////////////////////////////////////
void drawNoTess(){

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
bool concave(int v1, int v2, int v3, vector<point>& temp){
cout<<"in concave bool"<<endl;


int L1x = (temp.at(v1%temp.size()).x)-(temp.at(v2%temp.size()).x);
int L1y = (temp.at(v1%temp.size()).y)-(temp.at(v2%temp.size()).y);
int L2x = (temp.at(v3%temp.size()).x)-(temp.at(v2%temp.size()).x);
int L2y = (temp.at(v3%temp.size()).y)-(temp.at(v2%temp.size()).y);
cout<<L1x<<","<<L1y<<","<<L2x<<","<<L2y<<endl;
float cross = (L1x*L2y)-(L2x*L1y);

if(cross<0){return true;}
if(cross==0){temp.erase(temp.begin()+v2);}//removes midpoint if a straight line would be created

return false;
}
//////////////////////////////////////////////////////////////////
bool insidePoly(int v0, int v1, int v2, int v3,vector<point>& temp){
	

   if((temp.at(v2).y) > ((temp.at(v3).y))){
	cout<<"in poly if"<<endl;	
	//angle alpha
	int aLength = sqrt((pow(temp.at(v2).x-temp.at(v1).x,2)+(pow(temp.at(v2).y-temp.at(v1).y,2))));
	cout<<aLength<<endl;
	int bLength = sqrt((pow(temp.at(v0).x-temp.at(v2).x,2)+(pow(temp.at(v0).y-temp.at(v2).y,2))));
	cout<<bLength<<endl;
	int cLength = sqrt((pow(temp.at(v1).x-temp.at(v0).x,2)+(pow(temp.at(v1).y-temp.at(v0).y,2))));
	cout<<cLength<<endl;
	
		float alpha = (float) acos(((pow(aLength,2))+(pow(bLength,2))-(pow(cLength,2)))/(2*aLength*bLength));
			cout<<alpha<<endl;


	//angle beta
	int dLength = sqrt((pow(temp.at(v2).x-temp.at(v1).x,2)+(pow(temp.at(v2).y-temp.at(v1).y,2))));
	cout<<dLength<<endl;
	int eLength = sqrt((pow(temp.at(v3).x-temp.at(v2).x,2)+(pow(temp.at(v3).y-temp.at(v2).y,2))));
	cout<<eLength<<endl;
	int fLength = sqrt((pow(temp.at(v1).x-temp.at(v3).x,2)+(pow(temp.at(v1).y-temp.at(v3).y,2))));
	cout<<fLength<<endl;
		
		float beta = (float) acos(((pow(dLength,2))+(pow(eLength,2))-(pow(fLength,2)))/(2*dLength*eLength));
			cout<<beta<<endl;

	 	if(alpha<beta){return true;}
	}
   else{
	cout<<"in poly else"<<endl;	
	//angle alpha
	int aLength = sqrt((pow(temp.at(v2).x-temp.at(v1).x,2)+(pow(temp.at(v2).y-temp.at(v1).y,2))));
	cout<<aLength<<endl;
	int bLength = sqrt((pow(temp.at(v0).x-temp.at(v2).x,2)+(pow(temp.at(v0).y-temp.at(v2).y,2))));
	cout<<bLength<<endl;
	int cLength = sqrt((pow(temp.at(v1).x-temp.at(v0).x,2)+(pow(temp.at(v1).y-temp.at(v0).y,2))));
	cout<<cLength<<endl;
	
		float alpha = (float) acos(((pow(aLength,2))+(pow(bLength,2))-(pow(cLength,2)))/(2*aLength*bLength));
			cout<<alpha<<endl;


	//angle beta
	int dLength = sqrt((pow(temp.at(v2).x-temp.at(v1).x,2)+(pow(temp.at(v2).y-temp.at(v1).y,2))));
	cout<<dLength<<endl;
	int eLength = sqrt((pow(temp.at(v3).x-temp.at(v2).x,2)+(pow(temp.at(v3).y-temp.at(v2).y,2))));
	cout<<eLength<<endl;
	int fLength = sqrt((pow(temp.at(v0).x-temp.at(v3).x,2)+(pow(temp.at(v0).y-temp.at(v3).y,2))));
	cout<<fLength<<endl;
		
		float beta = (float) acos(((pow(dLength,2))+(pow(eLength,2))-(pow(fLength,2)))/(2*dLength*eLength));
			cout<<beta<<endl;

	 	if(alpha<beta){return true;}
 }
 return false;
}
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
void tessalate(){

// filling up a temp list
vector<point> temp;
for(int i=0; i<coords.size()-1; i++){
	temp.push_back(coords.at(i));
}	
  
  //looping through the temp list of points and checking in groups of 3 to see if they are concave
  //if concave seeing if the line that would be created is inside the polygon
  //if it is inside the polygon then we check to see if the line intersects with any line in the polygon
  //if we have no intersections then we add the vertices to the list of triangles, delete the middle verticies from the temp list, and draw the line

  for(int i=0; i<temp.size()-1; i++){
	cout<<"in for"<<endl;
   if(concave(i,(i+1)%temp.size(),(i+2)%temp.size(),temp)){
	cout<<"in concave if"<<endl;
	
	if(insidePoly(i%temp.size(),(i+1)%temp.size(),(i+2)%temp.size(),(i+3)%temp.size(),temp)){
		line newLine;
		newLine.a=coords.at(i);
		newLine.b=coords.at((i+2)%coords.size());
		lineList.push_back(newLine);
		if(polyIntersect()){
			cout<<"intersect"<<endl;
		lineList.pop_back();
		
		}//end if polyIntersect
		else if(!polyIntersect()){
			cout<<" no intersect"<<endl;
		   //draw new line
		   glBegin(GL_LINES);
			cout<<temp.at(i%temp.size()).x<<"  "<<temp.at(i%temp.size()).y<<endl;
	 	    glVertex2i(temp.at(i%temp.size()).x,temp.at(i%temp.size()).y);
			cout<<(i+2)%temp.size()<<"  "<<temp.at((i+2)%temp.size()).x<<"  "<<temp.at((i+2)%temp.size()).y<<endl;
		    glVertex2i(temp.at((i+2)%temp.size()).x,temp.at((i+2)%temp.size()).y);
	           glEnd();
		   	cout<<"c1"<<endl;	    
		   //add triangle
		   triangle tempTri;
cout<<"c2"<<endl;
		   tempTri.v1 = temp.at(i%temp.size());
cout<<"c3"<<endl;
		   tempTri.v2 = temp.at((i+1)%temp.size());
cout<<"c4"<<endl;
                   tempTri.v3 = temp.at((i+2)%temp.size());
cout<<"c5"<<endl;
			
		   triList.push_back(tempTri);
		   //remove mid point
		   temp.erase(temp.begin()+i+1);

			i=-1;	
                 }//end else if	
     	}//end if insidePoly
	
    }//end if concave
   }//end for
glFlush();

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
	point temp;
	temp.x=x;
	temp.y=WINDOW_MAX_Y-y;
	coords.push_back(temp); 
        drawBox( x, WINDOW_MAX_Y-y );
	drawLines();
	
	//fill lineList
 	 for(int i=0; i<coords.size()-1; i++){
	line tempLine;	
	tempLine.a=coords.at(i);
	tempLine.b=coords.at(i+1%coords.size());	
	lineList.push_back(tempLine);
  	 }
	 if(polyIntersect()){
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
  if ( key == 't' || key == 'T') tessalate();
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

