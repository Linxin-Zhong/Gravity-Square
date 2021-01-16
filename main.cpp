
//#include <windows.h>
#include <iostream>
#include <fstream>
#include <GLUT/glut.h>
#include <math.h>

using namespace std;


int leftt=0, rightt=500, bottom=400, top=0;
float sy=0.0;
float difficulty=0.15;//the scrolling speed of the whole screen
float xboy=61;
float yboy=181;
float fallspeed=0.8;//change for windows 0.5
int mode=2;// mode 1 means walking, 2 means falling, 3 represents swimming
float jump=0.0;
int jumpdir=0; //one means jumo to the right, two means jump to the left
bool pressUp=false;
bool pressLeft=false;
bool pressRight=false;
float xbeforej=0;
float ybeforej=0;
bool Exit=false;
int hitwall=-1;


float quadx1[26];
float quadx2[26];
float quady1[26];
float quady2[26];
int quadcount=0;

//bool values to record if the player character is on the ladders
bool ladder1= false;
bool ladder2= false;
bool ladder3=false;

//the bool value to record if the player lose or not
bool lose=false;

//vrables to record the gemstones got
int score=0;
int gemcount=0;
bool gem[10]= {true,true,true,true,true,true,true,true,true,true};
float gemx[10];
float gemy[10];

void drawGem(GLfloat x, GLfloat y);


void drawQuad(GLfloat x,GLfloat y,GLfloat l,GLfloat w);//the function to draw walls and floors

void drawCircle(GLfloat x,GLfloat y,GLfloat r,GLfloat nos);

void display()

{
    if (yboy+sy>=400){
        lose=true;
    }
    glClearColor(0.9,0.9,0.9,1.0); // black background
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity ();
    glOrtho( leftt, rightt, bottom, top,-1,1);
    glLineWidth(1);
    glEnable(GL_LINE_SMOOTH);


    glColor3f(0.7,0.7,0.7);
    drawCircle(250, 200, 100, 50);

    glColor3f(1.0,0.0,0.0);
    glPushMatrix();
    glBegin(GL_LINES);
    glVertex2f(250,200);
    glVertex2f(330,200);
    glEnd();
    glPopMatrix();


    if (lose){
        sy=0.0;
        difficulty=0.006;//the scrolling speed of the whole screen
        xboy=61;
        yboy=181;
        fallspeed=0.8;//change for windows
        mode=2;// mode 1 means walking, 2 means falling, 3 represents swimming
        jump=0.0;
        jumpdir=0; //one means jumo to the right, two means jump to the left
        pressUp=false;
        pressLeft=false;
        pressRight=false;
        xbeforej=0;
        ybeforej=0;
        Exit=false;
        hitwall=-1;
        quadcount=0;
        ladder1= false;
        ladder2= false;
        ladder3=false;

        lose=false;
        for(int i=0;i<10;i++){
            gem[i]=true;
        }
        gemcount=0;
        score=0;


    }
   //Speed changing buttons and texts:
    glColor3f(0.0,0.0,0.0);
    glRasterPos3f(450,40,0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,115);//s
    glRasterPos3f(457,40,0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,112);//p
    glRasterPos3f(464,40,0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,101);//e
    glRasterPos3f(471,40,0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,101);//e
    glRasterPos3f(478,40,0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,100);//d

    //draw the destination door:
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_QUADS);
    glVertex2f(346,-543+sy);
    glVertex2f(368,-543+sy);
    glVertex2f(368,-500+sy);
    glVertex2f(346,-500+sy);
    glEnd();

    //Newgame button and texts:
    //Button
    glColor3f(0.8,0.0,0.0);
    glBegin(GL_QUADS);
    glVertex2f(8,7);
    glVertex2f(55,7);
    glVertex2f(55,19);
    glVertex2f(8,19);
    glEnd();

    glColor3f(0.0,0.0,0.0);
    glRasterPos3f(11,16,0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,78);//N
    glRasterPos3f(18,16,0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,101);//e
    glRasterPos3f(23,16,0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,119);//w
    glRasterPos3f(32,16,0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,103);//g
    glRasterPos3f(37,16,0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,97);//a
    glRasterPos3f(42,16,0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,109);//m
    glRasterPos3f(48,16,0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,101);//e


    //Accelerate button
    glBegin(GL_TRIANGLES);
    glVertex2f(464,12);
    glVertex2f(476,30);
    glVertex2f(452,30);
    glEnd();

    //Decelerate button
    glBegin(GL_TRIANGLES);
    glVertex2f(464,66);
    glVertex2f(476,48);
    glVertex2f(452,48);
    glEnd();




    //Drawing floors:
    glColor3f(0.0,0.0,0.0);
    drawQuad(21,201+sy,19,277);//1
    drawQuad(332,176+sy,16,19);//2
    drawQuad(365,157+sy,21,87);//3
    drawQuad(247,117+sy,19,86);//4
    drawQuad(123,80+sy,17,85);//5
    drawQuad(92,-83+sy,19,20);//6
    drawQuad(137,-78+sy,7,64);//7
    drawQuad(215,-78+sy,7,54);//8
    drawQuad(228,-73+sy,102,6);//wall 9
    drawQuad(231,17+sy,10,125);//10
    drawQuad(347,2+sy,26,11);//10
    drawQuad(302,-96+sy,76,7);//wall 12
    drawQuad(261,-29+sy,9,48);//13
    drawQuad(378,-23+sy,16,28);//14
    drawQuad(416,-52+sy,16,28);//15
    drawQuad(458,-77+sy,16,28);//16
    drawQuad(388,-115+sy,15,40);//17
    drawQuad(425,-270+sy,20,36);//18
    drawQuad(371,-272+sy,108,22);//19
    drawQuad(83,-173+sy,6,309);//20
    drawQuad(83,-277+sy,111,22);//21
    drawQuad(22,-293+sy,4,44);//22
    drawQuad(78,-345+sy,4,46);//23
    drawQuad(159,-364+sy,10,78);//24
    drawQuad(270,-364+sy,9,82);//25
    drawQuad(334,-499+sy,9,50);//26


//Draw ladders:
    //ladder1:
    glColor3f(0.2,0.2,0.2);
    glLineWidth(5);
    glBegin(GL_LINES);
        glVertex2f(95,-64+sy);
        glVertex2f(95,20+sy);
        glVertex2f(112,-64+sy);
        glVertex2f(112,20+sy);
        for(int i=-50;i<=10;i+=10){
        glVertex2f(95,i+sy);
        glVertex2f(112,i+sy);
        }
    glEnd();


    //ladder2:

    glBegin(GL_LINES);
        glVertex2f(435,-247+sy);
        glVertex2f(435,-161+sy);
        glVertex2f(453,-247+sy);
        glVertex2f(453,-161+sy);
        for(int i= -235;i<-161;i+=10){
            glVertex2f(435,i+sy);
            glVertex2f(453,i+sy);
        }
    glEnd();

     //ladder3:
    glBegin(GL_LINES);
        glVertex2f(346,-491+sy);
        glVertex2f(346,-372+sy);
        glVertex2f(368,-491+sy);
        glVertex2f(368,-372+sy);
        for(int i= -480;i<=-372;i+=10){
            glVertex2f(346,i+sy);
        glVertex2f(368,i+sy);
        }
        glEnd();

//Swimming pool ladder
    glBegin(GL_LINES);
        glVertex2f(110,-276+sy);
        glVertex2f(110,-232+sy);
        glVertex2f(123,-276+sy);
        glVertex2f(123,-232+sy);
        for(int i=-270; i<-232;i+=10){
            glVertex2f(110,i+sy);
            glVertex2f(123,i+sy);
        }
        glEnd();


    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    // draw gemstones:
    drawGem(344,165);
    drawGem(285,101);
    drawGem(245,1);
    drawGem(350,-19);
    drawGem(306,-114);
    drawGem(473,-99);
    drawGem(442,-191);
    drawGem(294,-216);
    drawGem(125,-198);
    drawGem(353,-417);

    //To detect if the gemstone is got by the player
    for(int i=0;i<10;i++){
        if(xboy+7>=gemx[i]-5 && xboy+7<=gemx[i]+5 && yboy+6>=gemy[i]-5 && yboy+6<=gemy[i]+5){
            gem[i]=false;
            gemx[i]=550;
            gemy[i]=450;
            score++;
        }
    }


//draw the swimming pool water
    glColor4f(0.0,0.3,0.7,0.2);
    glBegin(GL_QUADS);
    glVertex2f(105,-265+sy);
    glVertex2f(377,-265+sy);
    glVertex2f(377,-172+sy);
    glVertex2f(105,-172+sy);

    //if the player character reaches the end of the pool, move it to the other pool side
    if(mode==3 && xboy+5>=110 && xboy+5<=123 &&yboy<=-232 && yboy>=-276){
        xboy=90;
        yboy=-305;
        mode=2;
    }
    if(xboy>=113 && xboy<=370 && yboy<=-175 &&yboy>=-260){
        mode=3;
    }

//Detect if the player character is on the ladder:
    if (mode!=3){
    mode=2;
    }
    //ladder1
    if(yboy<=25 && yboy>=-83&& xboy<=112 && xboy>=95){
        ladder1=true;
        mode=1;
        xboy=95;
    }else{
    ladder1=false;
    }
    if(yboy<=-78&& yboy>=-90&& xboy<=112 && xboy>=95){

        ladder1=false;
        yboy=-105;
        mode=2;
    }

    //ladder2
    if(yboy<=-160 && yboy>=-270 && xboy<= 455 && xboy>=436){
        ladder2=true;
        mode=1;
        xboy=438;
    }else{
    ladder2=false;
    }
    if(yboy<=-265 && yboy>=-277 &&xboy<= 455&& xboy>=436){

        ladder2=false;
        yboy=-292;
        mode=2;
    }


    //ladder3
    if(yboy<=-372 && yboy>=-489 && xboy<=368 && xboy>=346){
        ladder3=true;
        mode=1;
        xboy=350;
    }else{
    ladder3=false;
    }
    if(yboy<=-486 && yboy>=-490 &&xboy<=368&& xboy>=346){
        ladder3=false;
        yboy=-520;
        mode=2;
    }


    glColor3f(1.0,0.0,1.0);
    for(int i=0;i<26;i++){//To detect if the player character is on any of the floors
        if(xboy+14>=quadx1[i] && xboy<=quadx2[i] && (yboy+sy+21)>=quady1[i] && (yboy+sy+21)<=quady2[i]){
            if(mode!=3){
                mode=1;
            }
            hitwall=i;
        }
    }

    if(mode==1 ||mode==3){//if the character is on the floor
        fallspeed=0;// make the falling speed into 0 (stays)
    }
    else{//if it is not on any of the floors
        mode=2;//change it into falling mode
        fallspeed=0.5;//make the falling speed into normal
        hitwall=-1;
    }


    if(jump==1.0){
        xbeforej=xboy;
        ybeforej=yboy;
        if(jumpdir==1){
            xboy+=0.65;//0.05 for windows
        }
        else if(jumpdir==2){
            xboy-=0.65;//0.05 for windows
        }
        float jumph=(-55)*pow(jump-25.0,2)/625+55;
        yboy=ybeforej-jumph;
             jump+=0.65;//0.05 for windows
    }
    else if(jump<50&&jump>1){
        if(ladder1||ladder2 ||ladder3) {
            mode=1;
            jump=0;
        }

        else if (mode==1 && yboy+sy+21>=quady1[hitwall]-3.5&& yboy+sy+21<=quady1[hitwall]+3.5){
        jump=0;
        }
        else if(mode==1 ){
        if(jumpdir==1){
        xboy-=5;
        yboy+=5;
        cout<<"return"<<endl;
        }
        else{
            xboy+=5;
            yboy+=5;
        }
        jump=0;
        mode=2;
        }
        else{
        if(jumpdir==1){
            xboy+=0.65;
        }
        else if(jumpdir==2){
            xboy-=0.65;
        }
        float jumph=(-55)*pow(jump*1.0-25,2)/625+55;
        yboy=ybeforej-jumph;
            jump+=0.65;
        }

    }
    else if(jump==50){
        jump=0;
        jumpdir=0;
    }

//draws the player character
     glBegin(GL_QUADS);
     glVertex2f(xboy,yboy+sy);
     glVertex2f(xboy+15,yboy+sy);
     glVertex2f(xboy+15,yboy+sy+20);
     glVertex2f(xboy,yboy+sy+20);
     glEnd();
     glColor3f(0.0,0.0,0.0);
     //draw the eyes to show the walking/jumping direction
     if(jumpdir==1){
     drawCircle(xboy+12,yboy+sy+5,1.5,15);//to the right
     }
     else if(jumpdir==2){//to the left
    drawCircle(xboy+2,yboy+sy+5,1.5,15);
     }else{//showing both eyes
     drawCircle(xboy+5,yboy+sy+5,1.5,15);
     drawCircle(xboy+10,yboy+sy+5,1.5,15);
     }

//The starting flag:
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(39,168+sy);
    glVertex2f(55,178+sy);
    glVertex2f(39,181+sy);
    glEnd();
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_LINES);
    glVertex2f(39,168+sy);
    glVertex2f(39,203+sy);
    glEnd();


  //winning situation:
    if(xboy+7>=346 && xboy+7<=368 && yboy-10>=-543 && yboy-10<=-500){
        difficulty=0;//stop the screen rolling
        glColor3f(1.0,1.0,0.5);
        glBegin(GL_QUADS);
        glVertex2f(150,120);
        glVertex2f(350,120);
        glVertex2f(350,180);
        glVertex2f(150,180);
        glEnd();


        glLineWidth(2);



     glPushMatrix();
    glColor3f(0.6,0.6,1.0);
    glTranslatef(160,170,0);
    glScalef(0.13,-0.13,0);
    for (const char *s="Your score is :"; *s != NULL; s++)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *s);
    glPopMatrix();

     if(score!=10){

        glPushMatrix();
        glColor3f(0.6,0.6,1.0);
        glTranslatef(160,150,0);
        glScalef(0.13,-0.13,0);
        for (const char *s="YOU WIN !!"; *s != NULL; s++)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *s);
        glPopMatrix();


        glPushMatrix();
        glTranslatef(300,170,0);
        glScalef(0.13,-0.13,0);
        int nn=score+48;
        glutStrokeCharacter(GLUT_STROKE_ROMAN, nn);
        glPopMatrix();

    }else{
        glPushMatrix();
        glColor3f(0.6,0.6,1.0);
        glTranslatef(160,150,0);
        glScalef(0.13,-0.13,0);
        for (const char *s="Perfect !!"; *s != NULL; s++)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *s);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(300,170,0);
        glScalef(0.13,-0.13,0);
        glutStrokeCharacter(GLUT_STROKE_ROMAN, 49);
        glTranslatef(10,0,0);
        glutStrokeCharacter(GLUT_STROKE_ROMAN, 48);
        glPopMatrix();
    }

    }



    yboy+=fallspeed;
    sy+=difficulty;//0.01 for windows, 0.2 for mac
    glutPostRedisplay();
    glFlush();
}


static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;
    }
    display();
}

//function to detect mouse events
void mouse(int button, int state, int xm, int ym){

    if(state==GLUT_DOWN &&xm<=108 &&xm >=16 && ym <=36 &&ym>=15){
        lose=true;
    }
    //if the mouse clicked the accelerate button
    if(state==GLUT_DOWN && xm>=904 && xm<=952 && ym>=26 && ym<=60){
        difficulty+=0.05;//change the speed by 0.01
    }
    //if the mouse clicked the deccelerate button
    if(difficulty>0.01 && state==GLUT_DOWN && xm>=904 && xm<=952 && ym>=98 && ym<=131){
        difficulty-=0.05;//change the speed by o.o1
    }
    display();
}

//function to detect the arrow keys events
static void arrows(int key, int x, int y)
{
    /*If the upeer arrow key is pressed, and the player character is not on ladders or falling or swimming*/
        if(key== GLUT_KEY_UP && jumpdir!=0 && mode==1 && !ladder1 && !ladder2 &&! ladder3){
            jump=1;//let the player character jump
        }
        //upper arrow key is used for moving while on ladders
        if(key== GLUT_KEY_UP && (ladder1||ladder2 ||ladder3) && mode!=3){
            yboy-=10;//make the coordinates down
        }
        //down arrrow key is only used when the player character is on ladderf
        if(key==GLUT_KEY_DOWN && (ladder1||ladder2 ||ladder3) &&mode!=3){
            yboy+=10;

        }

        //if the right arrow key is pressed and it's not on ladders or falling
        if(key== GLUT_KEY_RIGHT && mode==1 && !ladder1&& !ladder2 &&!ladder3){
            bool rightwall=false;
            for(int i=0;i<26;i++){
                if(xboy+15<=quadx1[i] && xboy+15+10>=quadx1[i] && yboy+sy>=quady1[i] &&yboy+sy<=quady2[i]){
                    rightwall=true;
                }
            }

            if(!rightwall){
            jumpdir=1;//change the direction of the player character to the right
            xboy+=10;//move it to the right
            }
        }


        if(key== GLUT_KEY_LEFT &&mode==1 && !ladder1 && !ladder2 &&!ladder3){
            bool leftwall=false;
            for (int i=0;i<26;i++){
                if(xboy>=quadx2[i] && xboy-10<=quadx2[i] && yboy+sy>=quady1[i] &&yboy+sy<=quady2[i]){
                    leftwall=true;
                }
            }
            if(!leftwall){
            jumpdir=2;//change the direction of the player character to the right
            xboy-=10; //move it to the left
            }
        }



        if(key== GLUT_KEY_UP && mode==3 && (yboy-10)>=-270){
            yboy-=10;//let the player character jump
        }


        if(key==GLUT_KEY_DOWN && mode==3 && (yboy+10)<=-185){
            yboy+=10;

        }


          if(key== GLUT_KEY_RIGHT && mode==3 && (xboy+10)<=358){
            xboy+=10;
          }

          if(key== GLUT_KEY_LEFT && mode==3 && (xboy-10)>=101){
            xboy-=10;
          }

}

int main( int argc, char **argv )

{
    glutInit( &argc, argv );
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize( 1000,800 );
    glutCreateWindow( "SummativeTask" );

    glutKeyboardFunc(key);
    glutSpecialFunc(arrows);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);

    glutMainLoop();

    return 0;
}

//function to draw floors and store their coordinates into the array
void drawQuad(GLfloat x,GLfloat y,GLfloat l,GLfloat w){
    //Draw the floors using GL_QUADS
    glBegin(GL_QUADS);
    glVertex2f(x,y);
    glVertex2f(x+w,y);
    glVertex2f(x+w,y+l);
    glVertex2f(x,y+l);
    glEnd();

    /*Store the coordinates into an array of 26, which means every time when the screen flushes,
    the index of the array would started again from 0 and rewrite the coordinates to get the
    latest data*/
    int k=quadcount%26;
    quadx1[k]=x;
    quadx2[k]=x+w;
    quady1[k]=y;
    quady2[k]=y+l;
    quadcount++;
}


void drawCircle(GLfloat x,GLfloat y,GLfloat r,GLfloat nos){
    GLint nov=nos+2;
    GLfloat doublePI=2.0f*M_PI;
    GLfloat VerticesX [nov];
    GLfloat VerticesY [nov];
    GLfloat VerticesZ [nov];
    VerticesX [0]=x;
    VerticesY [0]=y;

    for(int i=1;i<nov;i++){
        VerticesX[i]=x+(r*cos(i*doublePI/nos));
        VerticesY[i]=y+(r*sin(i*doublePI/nos));
    }

    glBegin(GL_TRIANGLE_FAN);
    for(int i=0;i<nov;i++){
        glVertex2f(VerticesX[i],VerticesY[i]);
    }
    glEnd();
}

//The function to draw the gemstones and store the coordinates of them

void drawGem(GLfloat x, GLfloat y){

    int counter=gemcount%10;
    if(gem[counter]){
        glColor3f(0.0,1.0,0.0);
    glBegin(GL_QUADS);
    glVertex2f(x, y-7+sy);
    glVertex2f(x+5,y+sy);
    glVertex2f(x, y+7+sy);
    glVertex2f(x-5,y+sy);
    glEnd();
    gemx[counter]=x;
    gemy[counter]=y;
    }
    gemcount++;
}

