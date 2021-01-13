//============================================================================
// Name        : game.cpp
// Author      : Hassan Mustafa
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Dodge 'Em...
//============================================================================

//MUHAMMAD ABDULLAH AKRAM
//19I-0513
//CS-H

#ifndef DODGE_CPP_
#define DODGE_CPP_
#include "util.h"
#include <iostream>
#include<string>
#include<cmath> // for basic math functions such as cos, sin, sqrt
#include <fstream>


using namespace std;
      


//declaration and initialization
	int level=1; 
        int actlevel=1;//actual level that is displayed
	float xopp =90; //opponent x coordinates
	float yopp = 500;//opponent y coordinates
        float xmine = 395; //my x coordinates
        float ymine = 670;//my y coordinates
        float score=0;//score
	int lives=3;//no of lives
        int plot;//to see if my car is in which arena
        int mode=0;//for different windows
        int speed=6;//my speed
        float ts=0;//actual score that even increments after level up
        int oppspeed=3;//opponent speed
        int opp2speed=3;//opponent speed
        int xopp2=90;//second car x coordinates
        int yopp2=100;//second car y coordinates
	string strscore;
	static int counter=0;
	int high_scores[12];//for storing highscores


// seed the random numbers generator by current time (see the documentation of srand for further help)...






//HIGHSCORE STORING & DISPLAYING

void HSW()//to write them in txt file
{
	//writing to a file
	ofstream fout;
	fout.open ("highscores.txt"); //this function takes the name of the file that you are writing to
	
	for (int i = 0; i < 10; i++){
		fout << high_scores[i] << endl;
	}
		
	fout.close();


}


void BubbleSort()//to set them in ascending order
{
	
	ifstream fin ("highscores.txt"); //name of the file it is supposed to read
	if (fin.is_open())
	{ 
		int i=0;
		while ( getline (fin, strscore) ) //this loop will run depending on the number of lines in the file
		{
		 high_scores[i]=atoi(strscore.c_str());  i++;//i have used atoi bcuz stoi wasn't working for me
		}
		fin.close();
	}

high_scores[10]=ts;
     int tvar=0;
	for (int n = 0; n < 11; n++)
	{
	   tvar=high_scores[n];
	
	   for (int m=n+1; m<11; m++)
	   {
		if (tvar<high_scores[m])
		  { 
			high_scores[n]=high_scores[m];
			high_scores[m]=tvar;
			tvar=high_scores[n];
		  }
	   }
			
	}
HSW();


}



void HSShower()//to show the high score called when mode == 2
{

	//reading from a file
	ifstream fin ("highscores.txt"); //name of the file it is supposed to read
	if (fin.is_open())
	{ 
		int yaxes=560;//to show proper arrangement
		 
		DrawString( 300, 640,  "HIGH SCORES", colors[AQUA]);
		while ( getline (fin, strscore) ) //this loop will run depending on the number of lines in the file
		{
		  DrawString( 350, yaxes,  strscore , colors[AQUA]);
		  yaxes=yaxes-40;
		  
		  
		}
		fin.close();
	}
	
}



/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}


/*
 * Main Canvas drawing function.
 * */
//Board *b;
void GameDisplay()/**/{
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

	
	// calling some functions from util.cpp file to help students

	//Square at 400,20 position
	//DrawSquare( 400 , 20 ,40,colors[RED]); 
	//Square at 250,250 position
	//DrawSquare( 250 , 250 ,20,colors[GREEN]); 
	//Display Score
	//DrawString( 50, 800, "Score=0", colors[RED]);
	//Triangle at 300, 450 position
	//DrawTriangle( 300, 450 , 340, 450 , 320 , 490, colors[MISTY_ROSE] ); 
	// Trianlge Vertices v1(300,50) , v2(500,50) , v3(400,250)
	//Circle at 50, 670 position
	//DrawCircle(50,670,10,colors[RED]);
	//Line from 550,50 to 550,480 with width 10
        // DrawLine(int x1, int y1, int x2, int y2, int lwidth, float *color)
	


if (mode==0)//display menu initially(when mode==0)
{
glClearColor(0/*Red Component*/, .2,	//148.0/255/*Green Component*/,
			0.4/*Blue Component*/, 1 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors

DrawCircle(420,450,300,colors[INDIGO]);
DrawString(380,650,"MENU",colors[LAVENDER_BLUSH]) ;
DrawString(300,550,"1).Start new Game",colors[LAVENDER_BLUSH]) ;
DrawString(300,450,"2).See highscores",colors[LAVENDER_BLUSH]) ;
DrawString(300,350,"3).Help",colors[LAVENDER_BLUSH]) ;
DrawString(300,250,"4).Exit",colors[LAVENDER_BLUSH]) ;
}






if (mode==2)//Highscores
{
glClearColor(0/*Red Component*/, .2,	//148.0/255/*Green Component*/,
			0.4/*Blue Component*/, 1 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors

HSShower();//DISPLAYS HIGHSCORES 


}

if(mode==3)//display help
{
glClearColor(0/*Red Component*/, 0.2,	//148.0/255/*Green Component*/,
			0.4/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors

DrawString(380,750,"HELP",colors[SKY_BLUE]) ;
DrawString(50,600,"press up arrow key to move up",colors[SKY_BLUE]) ;
DrawString(50,500,"press down arrow key to move down",colors[SKY_BLUE]) ;
DrawString(50,400,"press right arrow key to move right",colors[SKY_BLUE]) ;
DrawString(50,300,"press left arrow key to move left",colors[SKY_BLUE]) ;
DrawString(50,200,"Collect all points to move onto the next level",colors[SKY_BLUE]) ;
DrawString(50,100,"There are four levels and you have 3 lives to get all 400 points",colors[SKY_BLUE]) ;



}

if(mode==4)//exit the program
{
exit(1);
}


if (mode==5)//display pause menu
{
glClearColor(0/*Red Component*/, .2,	//148.0/255/*Green Component*/,
			0.4/*Blue Component*/, 1 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors
DrawString(380,650,"MENU",colors[LAVENDER_BLUSH]) ;
DrawString(300,550,"1).continue Game",colors[LAVENDER_BLUSH]) ;
DrawString(300,450,"2).See highscores",colors[LAVENDER_BLUSH]) ;
DrawString(300,350,"3).Help",colors[LAVENDER_BLUSH]) ;
DrawString(300,250,"4).Exit",colors[LAVENDER_BLUSH]) ;




}




if(mode==1)//display game	
{


glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
			0.1/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors

//DrawString(2000,38000,100,100,"score :  "+ to_string(score),colors[RED]);
DrawString(100,750,"Score :  "+ Num2Str(ts),colors[SKY_BLUE]) ;

DrawString(380,750,"Lives :  "+ Num2Str(lives),colors[SKY_BLUE]) ;


DrawString(600,750,"Level :  "+ Num2Str(actlevel),colors[SKY_BLUE]) ;



	// Drawing opponent car

	float width = 6; 
	float height = 5;
	float* color = colors[LAWN_GREEN]; 
	float radius = 4.0;
	DrawRoundRect(xopp,yopp,width,height,color,radius); // bottom left tyre
	DrawRoundRect(xopp+width*3,yopp,width,height,color,radius); // bottom right tyre
	DrawRoundRect(xopp+width*3,yopp+height*4,width,height,color,radius); // top right tyre
	DrawRoundRect(xopp,yopp+height*4,width,height,color,radius); // top left tyre
	DrawRoundRect(xopp, yopp+height*2, width, height, color, radius/2); // body left rect
	DrawRoundRect(xopp+width, yopp+height, width*2, height*3, color, radius/2); // body center rect
	DrawRoundRect(xopp+width*3, yopp+height*2, width, height, color, radius/2); // body right rect
{

        //Drawing my car
 
	width = 6; 
	height = 5;
	color = colors[ORCHID]; 
         radius = 4.0;
	DrawRoundRect(xmine,ymine,width,height,color,radius); // bottom left tyre
	DrawRoundRect(xmine+width*3,ymine,width,height,color,radius); // bottom right tyre
	DrawRoundRect(xmine+width*3,ymine+height*4,width,height,color,radius); // top right tyre
	DrawRoundRect(xmine,ymine+height*4,width,height,color,radius); // top left tyre
	DrawRoundRect(xmine, ymine+height*2, width, height, color, radius/2); // body left rect
	DrawRoundRect(xmine+width, ymine+height, width*2, height*3, color, radius/2); // body center rect
	DrawRoundRect(xmine+width*3, ymine+height*2, width, height, color, radius/2); // body right rect
}

  
    if(actlevel==4)
     {
          //at level 4 another car enters
         //drawing car2
	float width = 6; 
	float height = 5;
	float* color = colors[RED]; 
	float radius = 4.0;
	DrawRoundRect(xopp2,yopp2,width,height,color,radius); // bottom left tyre
	DrawRoundRect(xopp2+width*3,yopp2,width,height,color,radius); // bottom right tyre
	DrawRoundRect(xopp2+width*3,yopp2+height*4,width,height,color,radius); // top right tyre
	DrawRoundRect(xopp2,yopp2+height*4,width,height,color,radius); // top left tyre
	DrawRoundRect(xopp2, yopp2+height*2, width, height, color, radius/2); // body left rect
	DrawRoundRect(xopp2+width, yopp2+height, width*2, height*3, color, radius/2); // body center rect
	DrawRoundRect(xopp2+width*3, yopp2+height*2, width, height, color, radius/2); // body right rect



    }




	// Drawing Arena
	int gap_turn = 80;
	int sx = 70;
	int sy = 10;
	int swidth = 700/2 - gap_turn/2; // half width
	int sheight = 7;
	float *scolor = colors[BLUE];
	DrawRectangle(sx, sy, swidth, sheight, scolor); // bottom left
	DrawRectangle(sx + swidth + gap_turn, sy, swidth, sheight, scolor); // bottom right
	DrawRectangle(sx+swidth*2+gap_turn, sy+sheight, sheight*2, swidth, scolor); // right down
	DrawRectangle(sx+swidth*2+gap_turn, sy+sheight+swidth+gap_turn, sheight*2, swidth, scolor); // right up
	DrawRectangle(sx + swidth + gap_turn, sy+710, swidth, sheight, scolor); // top left
	DrawRectangle(sx, sy+710, swidth, sheight, scolor); // top right
        DrawRectangle(sx-sheight*2, sy+sheight+swidth+gap_turn, sheight*2, swidth, scolor); // left up
	DrawRectangle(sx-sheight*2, sy+sheight, sheight*2, swidth, scolor); // left down


{
	// Drawing Arena 2
	int gap_turn = 80;
	int sx = 145;
	int sy = 80;
	int swidth = 550/2 - gap_turn/2; // half width
	int sheight = 7;
	float *scolor = colors[LIGHT_SKY_BLUE];
	DrawRectangle(sx, sy, swidth, sheight, scolor); // bottom left
	DrawRectangle(sx + swidth + gap_turn, sy, swidth, sheight, scolor); // bottom right
	DrawRectangle(sx+swidth*2+gap_turn, sy+sheight, sheight*2, swidth, scolor); // right down
	DrawRectangle(sx+swidth*2+gap_turn, sy+sheight+swidth+gap_turn, sheight*2, swidth, scolor); // right up
	DrawRectangle(sx + swidth + gap_turn, sy+560, swidth, sheight, scolor); // top left
	DrawRectangle(sx, sy+560, swidth, sheight, scolor); // top right
        DrawRectangle(sx-sheight*2, sy+sheight+swidth+gap_turn, sheight*2, swidth, scolor); // left up
	DrawRectangle(sx-sheight*2, sy+sheight, sheight*2, swidth, scolor); // left down	
}


{
	// Drawing Arena 3
	int gap_turn = 80;
	int sx = 220;
	int sy = 150;
	int swidth = 400/2 - gap_turn/2; // half width
	int sheight = 7;
	float *scolor = colors[BLUE];
	DrawRectangle(sx, sy, swidth, sheight, scolor); // bottom left
	DrawRectangle(sx + swidth + gap_turn, sy, swidth, sheight, scolor); // bottom right
	DrawRectangle(sx+swidth*2+gap_turn, sy+sheight, sheight*2, swidth, scolor); // right down
	DrawRectangle(sx+swidth*2+gap_turn, sy+sheight+swidth+gap_turn, sheight*2, swidth, scolor); // right up
	DrawRectangle(sx + swidth + gap_turn, sy+410, swidth, sheight, scolor); // top left
	DrawRectangle(sx, sy+410, swidth, sheight, scolor); // top right
        DrawRectangle(sx-sheight*2, sy+sheight+swidth+gap_turn, sheight*2, swidth, scolor); // left up
	DrawRectangle(sx-sheight*2, sy+sheight, sheight*2, swidth, scolor); // left down	
}



{
	// Drawing Arena 4
	int gap_turn = 80;
	int sx = 295;
	int sy = 220;
	int swidth = 250/2 - gap_turn/2; // half width
	int sheight = 7;
	float *scolor = colors[LIGHT_SKY_BLUE];
	DrawRectangle(sx, sy, swidth, sheight, scolor); // bottom left
	DrawRectangle(sx + swidth + gap_turn, sy, swidth, sheight, scolor); // bottom right
	DrawRectangle(sx+swidth*2+gap_turn, sy+sheight, sheight*2, swidth, scolor); // right down
	DrawRectangle(sx+swidth*2+gap_turn, sy+sheight+swidth+gap_turn, sheight*2, swidth, scolor); // right up
	DrawRectangle(sx + swidth + gap_turn, sy+260, swidth, sheight, scolor); // top left
	DrawRectangle(sx, sy+260, swidth, sheight, scolor); // top right
        DrawRectangle(sx-sheight*2, sy+sheight+swidth+gap_turn, sheight*2, swidth, scolor); // left up
	DrawRectangle(sx-sheight*2, sy+sheight, sheight*2, swidth, scolor); // left down	
}


{
	// Drawing Arena 5
	int gap_turn = 0;
	int sx = 370;
	int sy = 290;
	int swidth = 100/2 - gap_turn/2; // half width
	int sheight = 7;
	float *scolor = colors[BLUE];
	DrawRectangle(sx, sy, swidth, sheight, scolor); // bottom left
	DrawRectangle(sx + swidth + gap_turn, sy, swidth, sheight, scolor); // bottom right
	DrawRectangle(sx+swidth*2+gap_turn, sy+sheight, sheight*2, swidth, scolor); // right down
	DrawRectangle(sx+swidth*2+gap_turn, sy+sheight+swidth+gap_turn, sheight*2, swidth, scolor); // right up
	DrawRectangle(sx + swidth + gap_turn, sy+110, swidth, sheight, scolor); // top left
	DrawRectangle(sx, sy+110, swidth, sheight, scolor); // top right
        DrawRectangle(sx-sheight*2, sy+sheight+swidth+gap_turn, sheight*2, swidth, scolor); // left up
	DrawRectangle(sx-sheight*2, sy+sheight, sheight*2, swidth, scolor); // left down	
}



//drawing points and incrementing score
static int arr[5][5];
int a=0,b=0;
for(int i=100;i<=740;i+=70)
 {
  a+=1;
   for(int j=40;j<=720;j+=69)
       {
        b+=1;
         if((xmine-i>=-30&&xmine-i<=30)&&(ymine-j>=-35&&ymine-j<=35))//when car and box meet
           {
             if (arr[a][b]==0&&(j>400||j<310)&&(i<355||i>460))
              {score+=1.5625;ts+=1.5625;}//1 box= 1.5625 points
           arr[a][b]=1;//GIFT BOXES DISAPPER AFTER COLLISION AND SCORE IS INCREMENTED

            }        
         if((j>400 || j<310) && (i<355 || i>460))
            {
            if (arr[a][b]==0)
                DrawSquare( i , j ,10,colors[AQUA]);//to draw boxes at equal intervals following the given conditions       
        //WHEN arr[a][b]==0 boxes are displayed else not
            }
 
       }
           //incrementing and decrementing levelS according to specific conditions
		if (score==100)
		{ 
		xopp=460;xmine=320;yopp=20;ymine=20;score=0;//initializing after level up
                 for(int v=0;v<45;v++)
		{
			for(int c=0;c<45;c++)
			{

                                    arr[c][v]={0};

			}
      
         level++;
        
   } 

actlevel++;//this is actual level displayed


}


}

speed=5;//after pressing spacebar, to reduce its speed



}

if( mode==7)//displaying congrats if score ==400
{
if (counter==0) {BubbleSort();counter++;}

glClearColor(0/*Red Component*/, .2,	//148.0/255/*Green Component*/,
			0.4/*Blue Component*/, 1 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors
DrawString(340,450,"congrats!!!... YOU WON!!!",colors[LAVENDER_BLUSH]) ;


}

if (mode==8)//displaying this if all lives are lost
{
if (counter==0) {BubbleSort();counter++;}

glClearColor(0/*Red Component*/, .2,	//148.0/255/*Green Component*/,
			0.4/*Blue Component*/, 1 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors
DrawString(340,450,"Hard Luck...):",colors[LAVENDER_BLUSH]) ;
DrawString(340,350,"Your score is "+Num2Str(ts),colors[LAVENDER_BLUSH]) ;
DrawString(320,250,"PRESS ESC TO EXIT",colors[LAVENDER_BLUSH]) ;
}







	glutSwapBuffers(); // do not modify this line.. or draw anything below this line
}





/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) {
	if (key
			== GLUT_KEY_LEFT/*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
		 if(((xmine>100&&xmine<=400)||(xmine>=520 &&xmine<=725))&&(ymine>=310&&ymine<=365))//||(yopp>=320&&yopp<=365)))
		    {xmine-=70;}//LEFT
		  } 
	 
         else if (key
			== GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {
		if(((xmine>=85&&xmine<=300)  || (xmine>510 &&xmine<715))&&(ymine>=310&&ymine<=365))
               { xmine+=70;}	//RIGHT
		   } 
	 
       
         else if (key
			== GLUT_KEY_UP/*&&(xopp>=380&&xopp<=450)&&(yopp>=20&&yopp<=30)*/ /*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {
                
		
		if(((ymine>=35&&ymine<235)||(ymine>=280&&ymine<650))&&(xmine>360&&xmine<430))
                {ymine+=70;}//UP
		
	}

	  

         else if (key
			== GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {

		if(((ymine>40&&ymine<375)||(ymine>=430 &&ymine<=685))&&(xmine>=360&&xmine<=430))
		{ymine-=70;}//DOWN
		
		}

	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/

	glutPostRedisplay();

}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
	if (key == 27/* Escape key ASCII*/) {
		exit(1); // exit the program when escape key is pressed.
	}

	if (key == 49 || key == '1')//press 1 to start game
			{
		
		mode=1;counter=0;lives=3;level=1;
		

			
	}
       if (key == 50 || key == '2')//press 2 to enter highscores
			{
		
		mode=2;

}

if (key == 51 || key == '3')//press 3 to enter help
			{
		
		mode=3;

}


if (key == 112||key==80||key==8)//press p or backspace to pause game or go back
			{
		
		mode=5;
              
}

if (key == 52 || key == '4')//press 4 to exit
			{

		mode=4;
              
                 
}

if (key==32 || key==' ')//press space to increment speed
{

speed+=5;


}


	glutPostRedisplay();
}



/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
void Timer(int m) {

if (ts==400)
       {mode=7;}//if score = 400 , end game by printing congrats!!!
//if (lives==0){mode=8;}




if (actlevel==3)
        {oppspeed=5;}//after first level speed doubles


//AI movement of opponent car relative to mine   
    if(mode==1)

    {
        	  if(xmine>=90 && xmine <=725 && ymine>=35&&ymine<=690 )//arena 1
		{plot=1;}


 		  if(xmine>=150 && xmine <=650 && ymine>=105 && ymine<=595 )//arena 2
		{plot=2;}

 		   if(xmine>=230 && xmine <=580 && ymine>=175&&ymine<=500 )//arena 3
		{plot=3;}

 		   if(xmine>=300 && xmine <=515 && ymine>=245&&ymine<=430 )//arena 4
	  	{plot=4;}


/*

	
//movement of opponent car in arenas

  
*/

//To go inside

	  if(plot>1)//2,3,4
		    {
     	          	if((yopp>=20  && yopp<=40 ) && (xopp>380 && xopp<430)){yopp+=70;}// down
		        if((yopp>=660 && yopp<=690) && (xopp>380 && xopp<430)){yopp-=80;}// up

			if (level>1)//if level is above 1, opponent can move right and left
			{

  			if((yopp>=310&&yopp<=365) && (xopp>710 && xopp<740)){xopp-=72;}//condition on right
	           else if((yopp>=310&&yopp<=365) && (xopp>=90 && xopp<=110)){xopp+=72;}//condition on left

			}
	             }
 

	  if(plot>2)//3,4
	       	  {
		      if((yopp>85&&yopp<=120) && (xopp>380 && xopp<430)){yopp+=80;}//down
	 	      if((yopp>575&&yopp<635) && (xopp>380 && xopp<430)){yopp-=80;}//up

		        if (level>1)//if level is above 1, opponent can move right and left
			     {
			 if((yopp>310&&yopp<=365) && (xopp>=630 && xopp<660)){xopp-=72;}//condition on right
		         else if((yopp>=310&&yopp<=365) && (xopp>=100 && xopp<=170)){xopp+=72;}//condition on left

			}
		   }
	
	


 	 if(plot>3)//4
           {
                     if(yopp>=160&&yopp<=190 && xopp>380 && xopp<430){yopp+=65;}//down
 		     if(yopp>=485&&yopp<=515 && xopp>380 && xopp<430){yopp-=80;}//up

		   if (level>1)//if level is above 1, opponent can move right and left
			{

 			if(yopp>=310&&yopp<=365 && xopp>=560 && xopp<630){xopp-=72;}//condition on right
			else if(yopp>=310&&yopp<=365 && xopp>=225 && xopp<=250){xopp+=72;}//condition on left
			}
	   }



//to go outside



	 else if(plot<4)//3,2,1
        {
   	    if((yopp>=220  &&yopp<= 255) && (xopp>380 && xopp<=440)){yopp-=80;}//down
 	     if((yopp>=420  &&yopp<=445)  && (xopp>380 && xopp<=425)){yopp+=80;}//up

     		 if (level>1)//if level is above 1, opponent can move right and left
		    {
 			if((yopp>=310&&yopp<=365) && (xopp>=500  && xopp<520 ) ){xopp+=72;}//condition on right
			else if((yopp>=310&&yopp<=365) && (xopp>=300  && xopp<=320) ){xopp-=72;}//condition on left
		    }
	}



	 if(plot<3)//2,1
	{
      		if((yopp>=160  &&yopp<= 180) && (xopp>380 && xopp<430)){yopp-=80;}//down
 	        if((yopp>=485  &&yopp<=515)  && (xopp>380 && xopp<=430)){yopp+=80;}//up
 
	 if (level>1)//if level is above 1, opponent can move right and left
		{
 		if((yopp>=310&&yopp<=365) && (xopp>=560  && xopp<630 )){xopp+=72;}//condition on right
		else if((yopp>310&&yopp<365) && (xopp>225  && xopp<250 )){xopp-=72;}//condition on left
		}
	}



	 if(plot<2)//1
	{
      		     if((yopp> 90  && yopp< 120) && (xopp>380 && xopp<430)){yopp-=80;}//down
  		 if((yopp>=590 && yopp<=625) && (xopp>380 && xopp<430)){yopp+=80;}//up

	    if (level>1)//if level is above 1, opponent can move right and left
		{

		     if((yopp>=310&&yopp<=365) &&  (xopp>=630 && xopp<660 )){xopp+=72;}//condition on right
		else if((yopp> 310&&yopp<=365) &&  (xopp> 150 && xopp<170 )){xopp-=72;}//condition on left
		}
	}










/*

	
//movement of opponent 2nd car in arenas

  
*/

//To go inside


{

	  if(plot>1)//2,3,4
		    {
     	          	if((yopp2>=20  && yopp2<=40 ) && (xopp2>380 && xopp2<430)){yopp2+=70;}// down
		        if((yopp2>=660 && yopp2<=690) && (xopp2>380 && xopp2<430)){yopp2-=80;}// up

			if (level>1)//if level is above 1, opponent can move right and left
			{

  			if((yopp2>=310&&yopp2<=365) && (xopp2>710 && xopp2<740)){xopp2-=72;}//condition on right
	           else if((yopp2>=310&&yopp2<=365) && (xopp2>=90 && xopp2<=110)){xopp2+=72;}//condition on left

			}
	             }
 

	  if(plot>2)//3,4
	       	  {
		      if((yopp2>85&&yopp2<=120) && (xopp2>380 && xopp2<430)){yopp2+=80;}//down
	 	      if((yopp2>575&&yopp2<635) && (xopp2>380 && xopp2<430)){yopp2-=80;}//up

		        if (level>1)//if level is above 1, opponent can move right and left
			     {
			 if((yopp2>310&&yopp2<=365) && (xopp2>=630 && xopp2<660)){xopp2-=72;}//condition on right
		         else if((yopp2>=310&&yopp2<=365) && (xopp2>=100 && xopp2<=170)){xopp2+=72;}//condition on left

			}
		   }
	
	


 	 if(plot>3)//4
           {
                     if(yopp2>=160&&yopp2<=190 && xopp2>380 && xopp2<430){yopp2+=65;}//down
 		     if(yopp2>=485&&yopp2<=515 && xopp2>380 && xopp2<430){yopp2-=80;}//up

		   if (level>1)//if level is above 1, opponent can move right and left
			{

 			if(yopp2>=310&&yopp2<=365 && xopp2>=560 && xopp2<630){xopp2-=72;}//condition on right
			else if(yopp2>=310&&yopp2<=365 && xopp2>=225 && xopp2<=250){xopp2+=72;}//condition on left
			}
	   }



//to go outside



	 else if(plot<4)//3,2,1
        {
   	    if((yopp2>=220  &&yopp2<= 255) && (xopp2>380 && xopp2<=440)){yopp2-=80;}//down
 	     if((yopp2>=420  &&yopp2<=445)  && (xopp2>380 && xopp2<=425)){yopp2+=80;}//up

     		 if (level>1)//if level is above 1, opponent can move right and left
		    {
 			if((yopp2>=310&&yopp2<=365) && (xopp2>=500  && xopp2<520 ) ){xopp2+=72;}//condition on right
			else if((yopp2>=310&&yopp2<=365) && (xopp2>=300  && xopp2<=320) ){xopp2-=72;}//condition on left
		    }
	}



	 if(plot<3)//2,1
	{
      		if((yopp2>=160  &&yopp2<= 180) && (xopp2>380 && xopp2<430)){yopp2-=80;}//down
 	        if((yopp2>=485  &&yopp2<=515)  && (xopp2>380 && xopp2<=430)){yopp2+=80;}//up
 
	 if (level>1)//if level is above 1, opponent can move right and left
		{
 		if((yopp2>=310&&yopp2<=365) && (xopp2>=560  && xopp2<630 )){xopp2+=72;}//condition on right
		else if((yopp2>310&&yopp2<365) && (xopp2>225  && xopp2<250 )){xopp2-=72;}//condition on left
		}
	}



	 if(plot<2)//1
	{
      		     if((yopp2> 90  && yopp2< 120) && (xopp2>380 && xopp2<430)){yopp2-=80;}//down
  		 if((yopp2>=590 && yopp2<=625) && (xopp2>380 && xopp2<430)){yopp2+=80;}//up

	    if (level>1)//if level is above 1, opponent can move right and left
		{

		     if((yopp2>=310&&yopp2<=365) &&  (xopp2>=630 && xopp2<660 )){xopp2+=72;}//condition on right
		else if((yopp2> 310&&yopp2<=365) &&  (xopp2> 150 && xopp2<170 )){xopp2-=72;}//condition on left
		}
	}





}





/*

MOVEMENT OF OPPONENT CAR

*/

      //movement of opponent car in first arena
       if((yopp>=20&&yopp<=40)&&xopp<=720){xopp+=oppspeed;}//for left bottom
  else if((xopp>=710&&xopp<=740)&&yopp<=670){yopp+=oppspeed;}//for right bottom
  else if((yopp>=660&&yopp<=690)&&xopp>=95){xopp-=oppspeed;}//for right top 
  else if((xopp>=80&&xopp<=100)&&yopp>=20){yopp-=oppspeed;} //for left top  
        
    //movement of opponent car in second arena
  else if((yopp>=75&&yopp<=115)&&xopp<=650){xopp+=oppspeed;}//for left bottom
  else if((xopp>=630&&xopp<=660)&&yopp<=590){yopp+=oppspeed;}//for right bottom
  else if((yopp>=570&&yopp<=600)&&xopp>=160){xopp-=oppspeed;}//for right top 
  else if((xopp>=150&&xopp<=170)&&yopp>=90){yopp-=oppspeed;} //for left top  

//movement of opponent car in third arena
  else if((yopp>=145&&yopp<=190)&&xopp<=580){xopp+=oppspeed;}//for left bottom
  else if((xopp>=560&&xopp<=600)&&yopp<=500){yopp+=oppspeed;}//for right bottom
  else if((yopp>=485&&yopp<=525)&&xopp>=240){xopp-=oppspeed;}//for right top 
  else if((xopp>=220&&xopp<=250)&&yopp>=150){yopp-=oppspeed;} //for left top  


//movement of opponent car in fourth arena
  else if((yopp>=220&&yopp<=255)&&xopp<=500){xopp+=oppspeed;}//for left bottom
  else if((xopp>=485&&xopp<=515)&&yopp<=425){yopp+=oppspeed;}//for right bottom
  else if((yopp>=420&&yopp<=435)&&xopp>=310){xopp-=oppspeed;}//for right top 
  else if((xopp>=300&&xopp<=325)&&yopp>=235){yopp-=oppspeed;} //for left top  


/*

MOVEMENT OF MY CAR

*/



   //movement of my car in first arena
          if((ymine>=20&&ymine<=42)&&xmine>=95){xmine-=speed;}//for right bottom     
    else if((xmine>=85&&xmine<=105)&&ymine<=670){ymine+=speed;}//for left bottom
   else if((ymine>=660&&ymine<=690)&&xmine<=720){xmine+=speed;} //for left top     
   else if((xmine>=710&&xmine<=740)&&ymine>=25){ymine-=speed;}//for right top 
 


   //movement of my car in second arena
  else if((ymine>=75&&ymine<=110)&&xmine>=160){xmine-=speed;}//for right bottom     
     else if((xmine>=150&&xmine<=170)&&ymine<=590){ymine+=speed;}//for left bottom
   else if((ymine>=575&&ymine<=605)&&xmine<=650){xmine+=speed;} //for left top     
   else if((xmine>=630&&xmine<=660)&&ymine>=90){ymine-=speed;}//for right top 

//movement of my car in third arena
  else if((ymine>=145&&ymine<=180)&&xmine>=240){xmine-=speed;}//for right bottom     
     else if((xmine>=220&&xmine<=260)&&ymine<=500){ymine+=speed;}//for left bottom
  else if((ymine>=485&&ymine<=540)&&xmine<=580){xmine+=speed;} //for left top     
   else if((xmine>=560&&xmine<=585)&&ymine>=150){ymine-=speed;}//for right top 


//movement of my car in fourth arena
   else if((ymine>=220&&ymine<=250)&&xmine>=310){xmine-=speed;}//for right bottom     
   else if((xmine>=300&&xmine<=325)&&ymine<=423){ymine+=speed;}//for left bottom
   else if((ymine>=415&&ymine<=440)&&xmine<=500){xmine+=speed;} //for left top     
   else if((xmine>=480&&xmine<=515)&&ymine>=235){ymine-=speed;}//for right top 






//movement of new opponent car in level 4
   

    //movement of opponent car in first arena
       if((yopp2>=20&&yopp2<=45)&&xopp2<=720){xopp2+=opp2speed;}//for left bottom
  else if((xopp2>=710&&xopp2<=740)&&yopp2<=660){yopp2+=opp2speed;}//for right bottom
  else if((yopp2>=650&&yopp2<=680)&&xopp2>=90){xopp2-=opp2speed;}//for right top 
  else if((xopp2>=80&&xopp2<=100)&&yopp2>=30){yopp2-=opp2speed;} //for left top  
        
    //movement of opponent car in second arena
  else if((yopp2>=75&&yopp2<=115)&&xopp2<=650){xopp2+=opp2speed;}//for left bottom
  else if((xopp2>=630&&xopp2<=660)&&yopp2<=590){yopp2+=opp2speed;}//for right bottom
  else if((yopp2>=570&&yopp2<=600)&&xopp2>=160){xopp2-=opp2speed;}//for right top 
  else if((xopp2>=150&&xopp2<=170)&&yopp2>=85){yopp2-=opp2speed;} //for left top  

//movement of opponent car in third arena
  else if((yopp2>=145&&yopp2<=180)&&xopp2<=580){xopp2+=opp2speed;}//for left bottom
  else if((xopp2>=560&&xopp2<=600)&&yopp2<=500){yopp2+=opp2speed;}//for right bottom
  else if((yopp2>=485&&yopp2<=525)&&xopp2>=240){xopp2-=opp2speed;}//for right top 
  else if((xopp2>=220&&xopp2<=250)&&yopp2>=150){yopp2-=opp2speed;} //for left top  


//movement of opponent car in fourth arena
  else if((yopp2>=220&&yopp2<=255)&&xopp2<=500){xopp2+=opp2speed;}//for left bottom
  else if((xopp2>=485&&xopp2<=515)&&yopp2<=423){yopp2+=opp2speed;}//for right bottom
  else if((yopp2>=415&&yopp2<=430)&&xopp2>=310){xopp2-=opp2speed;}//for right top 
  else if((xopp2>=300&&xopp2<=325)&&yopp2>=235){yopp2-=opp2speed;} //for left top  




//CRASH 

if((yopp-ymine>=-10 && yopp-ymine<=30 && xopp-xmine>=-10 && xopp-xmine<=30)||(ymine-yopp>=-10 && ymine-yopp<=30 && xmine-xopp>=-10 && xmine-xopp<=30)  )//  ||   (yopp2-ymine>=-10 && yopp2-ymine<=30 && xopp2-xmine>=-10 && xopp2-xmine<=30)||(ymine-yopp2>=-10 && ymine-yopp2<=30 && xmine-xopp2>=-10 && xmine-xopp2<=30)   )
{

 
   
   lives--;//life is lost
   xmine =395;
   ymine = 660;
   xopp =95;
   yopp=400;
  if(lives==0)
	{mode=8;}//display window if all lives are lost


}

if(actlevel==4){


if ((yopp2-ymine>=-10 && yopp2-ymine<=30 && xopp2-xmine>=-10 && xopp2-xmine<=30)||(ymine-yopp2>=-10 && ymine-yopp2<=30 && xmine-xopp2>=-10 && xmine-xopp2<=30))
{
 
   lives--;//life is lost
   xmine =395;
   ymine = 660;
   xopp2 =95;
   yopp2 =100;
  if(lives==0)
	{mode=8;}



}




}



 }    

	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(100.0/(FPS+10), Timer, 0);

   	

	glutPostRedisplay();
  
 
}



//HAVENT USED THIS FUNCTION
/*This function is called (automatically) whenever your mouse moves witin inside the game window
 *
 * You will have to add the necessary code here for finding the direction of shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 *
 * */
void MousePressedAndMoved(int x, int y) {
	cout << x << " " << y << endl;
	glutPostRedisplay();
}
void MouseMoved(int x, int y) {

	glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */
void MouseClicked(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON) // dealing only with left button
			{ cout << "";

	} else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
			{

	}
	glutPostRedisplay();
}




/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {

	//b = new Board(60, 60); // create a new board object to use in the Display Function ...

	int width = 840, height = 840; // i have set my window size to be 800 x 600
	//b->InitalizeBoard(width, height);
	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("DODGE_EM by ABDULLAH AKRAM"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...

	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.

	
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0/(FPS+10), Timer, 0);

	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse

      //   glutDisplayFunc(gamedisplay2);
       // glutGameDisplay();	
	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();


 

     

	return 1;
}
#endif /* AsteroidS_CPP_ */
