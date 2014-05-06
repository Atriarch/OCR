//Nathan McGaughy
//Optical Character Recognition
//ONLY WORKS WITH TIMES NEW ROMAN, ALL CAPITALS.

#include "EasyBMP.h"
#include "EasyBMP.cpp"
#include <cmath>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

void label(); //Draws the box around the char.
int color(int x, int y); //Finds the maxx, minx, miny, maxy and colors the char. green.
int bluecolor(int x, int y); //Makes the background blue.
void letter(); //Finds out what the letter is (Capitals only).

int minx, maxx, miny, maxy;
bool lock[5000][5000]; //Checks to see if the pixel has already been checked.
BMP text;


int main(){
  string inputstring;
  string outputstring;
  string check;
  int i = 0;

  while (i!=1){

  cout << "Which file would you like to scan?: ";
  cin >> inputstring;
  
  cout << "What would you like the output file to be called?: ";
  cin >> outputstring;

  cout << "The files text: ";

  char *inputfile=new char[inputstring.size()+1];
  inputfile[inputstring.size()]=0;
  memcpy(inputfile,inputstring.c_str(),inputstring.size());

  char *outputfile=new char[outputstring.size()+1];
  outputfile[outputstring.size()]=0;
  memcpy(outputfile,outputstring.c_str(),outputstring.size());

  text.ReadFromFile(inputfile);
  label();

  text.WriteToFile(outputfile);

  cout << "Would you like to scan another file? (yes/no): ";
  cin >> check;
  if (check == "no"){
	  i = 1;
  }
  }

  return 0;
}

int color(int x, int y){
  lock[x][y] = true;
  text(x, y)->Green = 255;
  if (x > maxx){
    maxx = x;
  }
  if (x < minx){
    minx = x;
  }
  if (y > maxy){
    maxy = y;
  }
  if (y < miny){
    miny = y;
  }

  if(text(x,y+1)->Red < 20 && text(x,y+1)->Blue < 20 && text(x,y+1)->Green < 20 && lock[x][y+1] != true){           //Top
    color( x, y+1);
  }
  if(text(x+1,y+1)->Red < 20 && text(x+1,y+1)->Blue < 20 && text(x+1,y+1)->Green < 20 && lock[x+1][y+1] != true){   //Top Right
    color( x+1, y+1);
  }
  if(text(x+1,y)->Red < 20 && text(x+1,y)->Blue < 20 && text(x+1,y)->Green < 20 && lock[x+1][y] != true){           //Right
    color( x+1, y);
  }
  if(text(x+1,y-1)->Red < 20 && text(x+1,y-1)->Blue < 20 && text(x+1,y-1)->Green < 20 && lock[x+1][y-1] != true){   //Bottom Right
    color( x+1, y-1);
  }
  if(text(x,y-1)->Red < 20 && text(x,y-1)->Blue < 20 && text(x,y-1)->Green < 20 && lock[x][y-1] != true){           //Bottom
    color( x, y-1);
  }
  if(text(x-1,y-1)->Red < 20 && text(x-1,y-1)->Blue < 20 && text(x-1,y-1)->Green < 20 && lock[x-1][y-1] != true){   //Bottom Left
    color( x-1, y-1);
  }
  if(text(x-1,y)->Red < 20 && text(x-1,y)->Blue < 20 && text(x-1,y)->Green < 20 && lock[x-1][y] != true){           //Left
    color( x-1, y);
  }
  if(text(x-1,y+1)->Red < 20 && text(x-1,y+1)->Blue < 20 && text(x-1,y+1)->Green < 20 && lock[x-1][y+1] != true){   //Top Left
    color( x-1, y+1); 
  }
  return 0;
}

int bluecolor(int x, int y){
  text(x, y)->Blue = 255;
  text(x, y)->Green = 0;
  text(x, y)->Red = 0;

  if(text(x,y+1)->Red == 255 && text(x,y+1)->Blue == 80 && text(x,y+1)->Green == 120){           //Top
    bluecolor( x, y+1);
  }
  if(text(x+1,y+1)->Red == 255 && text(x+1,y+1)->Blue == 80 && text(x+1,y+1)->Green == 120){   //Top Right
    bluecolor( x+1, y+1);
  }
  if(text(x+1,y)->Red == 255 && text(x+1,y)->Blue == 80 && text(x+1,y)->Green == 120){           //Right
    bluecolor( x+1, y);
  }
  if(text(x+1,y-1)->Red == 255 && text(x+1,y-1)->Blue == 80 && text(x+1,y-1)->Green == 120){   //Bottom Right
    bluecolor( x+1, y-1);
  }
  if(text(x,y-1)->Red == 255 && text(x,y-1)->Blue == 80 && text(x,y-1)->Green == 120){           //Bottom
    bluecolor( x, y-1);
  }
  if(text(x-1,y-1)->Red == 255 && text(x-1,y-1)->Blue == 80 && text(x-1,y-1)->Green == 120){   //Bottom Left
    bluecolor( x-1, y-1);
  }
  if(text(x-1,y)->Red == 255 && text(x-1,y)->Blue == 80 && text(x-1,y)->Green == 120){           //Left
    bluecolor( x-1, y);
  }
  if(text(x-1,y+1)->Red == 255 && text(x-1,y+1)->Blue == 80 && text(x-1,y+1)->Green == 120){   //Top Left
    bluecolor( x-1, y+1);
  }
  return 0;
}

void letter(){
 A:
  for (int x = minx; x < (minx+(maxx-minx)*.2); x++){
    if (text(x, maxy)->Green != 255){
      goto B;
    }
  }
  if (text(minx+((maxx-minx)*.5), maxy)->Blue != 255 ){
    goto B;
  }
  if (text(minx+((maxx-minx)*.5), miny+((maxy-miny)*.5))->Red != 255, 
      text(minx+((maxx-minx)*.5), miny+((maxy-miny)*.5))->Blue != 80,
      text(minx+((maxx-minx)*.5), miny+((maxy-miny)*.5))->Green != 120){
    goto B;
  }
  cout << "A";
  goto end;
  
 B:
  if (text(minx+((maxx-minx)*.5), miny+((maxy-miny)*.3))->Red != 255 ||
      text(minx+((maxx-minx)*.5), miny+((maxy-miny)*.7))->Red != 255 ||
      text(minx+((maxx-minx)*.5), miny+((maxy-miny)*.5))->Green != 255){
    goto C;
  }
  cout << "B";
  goto end;

 C:
  if (text(minx, miny)->Blue != 255 ||
      text(maxx, maxy)->Blue != 255 ||
      text(maxx, miny)->Blue != 255 ||
      text(minx+((maxx-minx)*.85), miny+((maxy-miny)*.7))->Blue != 255 ||
      text(minx+((maxx-minx)*.5), miny+((maxy-miny)*.5))->Blue != 255){
    goto D;
  }
  cout << "C";
  goto end;

 D:  
  for(int y = miny; y < maxy; y++){
    if(text(minx+((maxx-minx)*.2), y)->Green != 255){
      goto E;
    }
  }
  if(text(minx+((maxx-minx)*.5), miny+((maxy-miny)*.5))->Red != 255){
    goto E;
  }
  cout << "D";
  goto end;

 E:
  for(int y = miny; y < maxy; y++){
    if(text(minx+((maxx-minx)*.2), y)->Green != 255){
      goto F;
    }
  }
  if(text(minx+((maxx-minx)*.5), miny)->Green != 255 ||
     text(minx+((maxx-minx)*.5), maxy)->Green != 255 || 
     text(minx+((maxx-minx)*.85), miny)->Green != 255 ||
      text(minx+((maxx-minx)*.85), maxy)->Green != 255){
    goto F;
  }
  cout << "E";
  goto end;

 F:
  for(int y = miny; y < maxy; y++){
    if(text(minx+((maxx-minx)*.2), y)->Green != 255){
      goto G;
    }
  }
  if(text(minx+((maxx-minx)*.5), miny)->Green != 255 ||
     text(minx+((maxx-minx)*.4), maxy)->Green != 255 ||
     text(minx+((maxx-minx)*.85), miny)->Green != 255 ||
     text(minx+((maxx-minx)*.85), maxy)->Blue != 255){
    goto G;
  }
  cout << "F";
  goto end;

 G:
  if(text(minx+((maxx-minx)*.4), miny+((maxy-miny)*.5))->Blue != 255 ||
     text(minx+((maxx-minx)*.8),  miny+((maxy-miny)*.5))->Green != 255 ||
     text(minx+((maxx-minx)*.5), miny)->Green != 255 || 
     text(minx+((maxx-minx)*.5), maxy)->Green != 255){
    goto H;
  }
  cout << "G";
  goto end;

 H:
  for(int y = miny; y < maxy; y++){
    if(text(minx+((maxx-minx)*.2), y)->Green != 255){
      goto I;
    }
    if(text(minx+((maxx-minx)*.8), y)->Green != 255){
      goto I;
    }
  }
  cout << "H";
  goto end;

 I:
  for (int y = miny; y < maxy; y++){
    if (text((minx+((maxx - minx)/2)), y)->Green != 255){
	  goto J;
	}
  }
  for (int x = minx; x < maxx; x++){
    if (text(x, miny)->Green != 255 || text(x, maxy)->Green != 255){
      goto J;
    }
  }
  cout << "I";
  goto end;
 
 J:
  for (int y = miny; y < maxy-((maxy-miny)*.2); y++){
    if (text((minx+((maxx - minx)*.6)), y)->Green != 255){
      goto K;
    }
  }
  if(text(minx+((maxx-minx)*.5), maxy)->Blue != 255){
    goto K;
  }
  cout << "J";
  goto end;
 
 K:
  for(int y = miny; y < maxy; y++){
    if(text(minx+((maxx-minx)*.2), y)->Green != 255){
      goto L;
    }
  }
  if(text(minx+((maxx-minx)*.8), miny)->Green != 255 ||
     text(maxx, maxy)->Green != 255 ||
     text(minx+((maxx-minx)*.5), miny+((maxy-miny)*.8))->Blue != 255){
    goto L;
  }
  cout << "K";
  goto end;

 L:
  for(int y = miny; y < maxy; y++){
    if(text(minx+((maxx-minx)*.2), y)->Green != 255){
      goto M;
    }
  }
  if(text(minx+((maxx-minx)*.8), maxy)->Green != 255 ||
     text(minx+((maxx-minx)*.8), miny)->Blue != 255 ||
     text(maxx, maxy)->Blue != 255 ||
     text(minx+((maxx-minx)*.5), miny+((maxy-miny)*.5))->Blue != 255){
    goto M;
  }
  cout << "L";
  goto end;

 M:
  if(text(minx+((maxx-minx)*.85), maxy)->Green != 255 ||
     text(minx+((maxx-minx)*.85), miny)->Green != 255 ||
     text(minx+((maxx-minx)*.2), maxy)->Green != 255 ||
     text(minx+((maxx-minx)*.2), miny)->Green != 255 ||
     text(minx+((maxx-minx)*.5), miny+((maxy-miny)*.5))->Blue != 255){
    goto N;
  }
  cout << "M";
  goto end;

 N:
  if(text(minx+((maxx-minx)*.85), maxy)->Blue != 255 ||
     text(minx+((maxx-minx)*.85), miny)->Green != 255 ||
     text(minx+((maxx-minx)*.2), miny+((maxy-miny)*.95))->Green != 255 || 
     text(minx+((maxx-minx)*.2), miny)->Green != 255 || 
     text(minx+((maxx-minx)*.5), miny+((maxy-miny)*.5))->Green != 255){
    goto O;
  }
  cout << "N";
  goto end;

 O:
  if(text(minx+((maxx-minx)*.5), maxy)->Green != 255 ||
     text(minx+((maxx-minx)*.5), miny)->Green != 255 ||
     text(minx, miny+((maxy-miny)*.5))->Green != 255 ||
     text(maxx, miny+((maxy-miny)*.5))->Green != 255 ||
     text(minx+((maxx-minx)*.5), miny+((maxy-miny)*.5))->Red != 255){
    goto P;
  }
  cout << "O";
  goto end;

 P:
  if(text(minx+((maxx-minx)*.5), maxy)->Green != 255 ||
     text(minx+((maxx-minx)*.3), miny)->Green != 255 ||
     text(maxx, maxy)->Blue != 255 || 
     text(minx+((maxx-minx)*.9), miny+((maxy-miny)*.3))->Green != 255 ||
     text(maxx, miny+((maxy-miny)*.5))->Blue != 255 ||
     text(minx+((maxx-minx)*.5), miny+((maxy-miny)*.3))->Red != 255){
    goto Q;
  }
  cout << "P";
  goto end;

 Q:
  if(text(minx+((maxx-minx)*.5), maxy)->Blue != 255 ||
     text(minx+((maxx-minx)*.5), miny)->Green != 255 ||
     text(minx, miny+((maxy-miny)*.5))->Green != 255 ||
     text(maxx, miny+((maxy-miny)*.5))->Green != 255 ||
     text(minx+((maxx-minx)*.5), miny+((maxy-miny)*.5))->Red != 255){
    goto R;
  }
  cout << "Q";
  goto end;

 R:
  if(text(minx+((maxx-minx)*.3), maxy)->Green != 255 ||
     text(minx+((maxx-minx)*.3), miny)->Green != 255 ||
     text(maxx, miny+((maxy-miny)*.3))->Blue != 255 ||
     text(maxx, miny+((maxy-miny)*.5))->Blue != 255 ||
     text(maxx, maxy)->Green != 255 ||
     text(minx+((maxx-minx)*.4), miny+((maxy-miny)*.3))->Red != 255){
    goto S;
  }
  cout << "R";
  goto end;

 S:
  if(text(minx+((maxx-minx)*.5), miny)->Green != 255 ||
     text(minx+((maxx-minx)*.5), miny+((maxy-miny)*.25))->Blue != 255 ||
     text(minx+((maxx-minx)*.25), miny+((maxy-miny)*.35))->Green != 255 ||
     text(minx+((maxx-minx)*.5), miny+((maxy-miny)*.5))->Green != 255 ||
     text(minx+((maxx-minx)*.5), miny+((maxy-miny)*.75))->Blue != 255 ||
     text(minx+((maxx-minx)*.5), maxy)->Green != 255){
    goto T;
  }
  cout << "S";
  goto end;

 T:
  for (int y = miny; y < maxy; y++){
    if (text((minx+((maxx - minx)/2)), y)->Green != 255){
      goto U;
    }
  }
  for (int x = minx; x < maxx; x++){
    if (text(x, miny)->Green != 255){
      goto U;
    }
  }
  if(text(minx, maxy)->Blue != 255 ||
     text(maxx, maxy)->Blue != 255){
    goto U;
  }
  cout << "T";
  goto end;

 U:
  if(text(minx, miny)->Green != 255 ||
     text(maxx, miny)->Green != 255 ||
     text(minx+((maxx-minx)*.5), miny)->Blue != 255 ||
     text(minx+((maxx-minx)*.5), maxy)->Green != 255 ||
     text(minx, maxy)->Blue != 255 ||
     text(minx+((maxx-minx)*.2), miny+((maxy-miny)*.6))->Green != 255 ||
     text(minx+((maxx-minx)*.5), miny+((maxy-miny)*.5))->Blue != 255 ||
     text(maxx, maxy)->Blue != 255){
    goto V;
  }
  cout << "U";
  goto end;

 V:
  if(text(minx, miny)->Green != 255 ||
     text(maxx, miny)->Green != 255 ||
     text(minx+((maxx-minx)*.5), miny)->Blue != 255 ||
     text(minx+((maxx-minx)*.5), maxy)->Green != 255 ||
     text(minx, maxy)->Blue != 255 ||
     text(minx+((maxx-minx)*.2), miny+((maxy-miny)*.6))->Blue != 255 ||
     text(minx+((maxx-minx)*.5), miny+((maxy-miny)*.5))->Blue != 255 ||
     text(maxx, maxy)->Blue != 255){
    goto W;
  }
  cout << "V";
  goto end;

 W:
  if(text(minx, miny)->Green != 255 ||
     text(maxx, miny)->Green != 255 ||
     text(minx+((maxx-minx)*.5), miny)->Green != 255 ||
     text(minx+((maxx-minx)*.3), maxy)->Blue != 255 ||
     text(minx+((maxx-minx)*.6), maxy)->Blue != 255){
    goto X;
  }
  cout << "W";
  goto end;

 X:
  if(text(minx+((maxx-minx)*.2), miny)->Green != 255 ||
     text(minx+((maxx-minx)*.8), miny)->Green != 255 ||
     text(minx+((maxx-minx)*.2), maxy)->Green != 255 ||
     text(minx+((maxx-minx)*.8), maxy)->Green != 255 ||
     text(minx+((maxx-minx)*.5), miny+((maxy-miny)*.5))->Green != 255 ||
     text(minx+((maxx-minx)*.5), miny)->Blue != 255 ||
     text(minx+((maxx-minx)*.5), maxy)->Blue != 255 ||
     text(minx+((maxx-minx)*.3), miny+((maxy-miny)*.5))->Blue != 255 ||
     text(minx+((maxx-minx)*.7), miny+((maxy-miny)*.5))->Blue != 255 ){
    goto Y;
  }
  cout << "X";
  goto end;

 Y:
  if(text(minx+((maxx-minx)*.2), miny)->Green != 255 ||
     text(minx+((maxx-minx)*.8), miny)->Green != 255 ||
     text(minx+((maxx-minx)*.2), maxy)->Blue != 255 ||
     text(minx+((maxx-minx)*.8), maxy)->Blue != 255 ||
     text(minx+((maxx-minx)*.5), miny+((maxy-miny)*.5))->Green != 255 ||
     text(minx+((maxx-minx)*.5), miny)->Blue != 255 ||
     text(minx+((maxx-minx)*.5), maxy)->Green != 255 ||
     text(minx+((maxx-minx)*.3), miny+((maxy-miny)*.5))->Blue != 255 ||
     text(minx+((maxx-minx)*.7), miny+((maxy-miny)*.5))->Blue != 255 ){
    goto Z;
  }
  cout << "Y";
  goto end;

 Z:
  cout << "Z";

 end:;
}


void label(){
  int sizew;
  int sizeh;
  bool check;
  bool key;
  bool skip = true;
  bool rowcheck = true;
  int row = 0;
  int count = 0;
  int holes = 0;
  sizew = text.TellWidth();
  sizeh = text.TellHeight();
  
  for(int y = 0; y < sizeh; y++){
    for(int x = 0; x < sizew; x++){
      if(text(x,y)->Red < 20 && text(x,y)->Blue < 20 && text(x,y)->Green < 20 && skip == true){
	x = 0;
	y += 5;
	skip = false;
      } // By using rowcheck and skip, we can make sure that we are starting on the first letter in the row, not the largest.

      rowcheck = true;
      if(text(x,y)->Red < 20 && text(x,y)->Blue < 20 && text(x,y)->Green < 20){
	if( lock[x][y] != true){
	  minx=x;
	  miny=y;
	  maxx=x;
	  maxy=y;
	  color( x, y);

	  for(int a = minx-2; a < maxx+3; a++){
	    text(a, miny-2)->Red = 255, text(a, miny-2)->Blue = 0, text(a, miny-2)->Green = 0;
	    text(a, maxy+2)->Red = 255, text(a, maxy+2)->Blue = 0, text(a, maxy+2)->Green = 0;
	  }
	  for(int b = miny-2; b < maxy+2; b++){
	    text(minx-2, b)->Red = 255, text(minx-2, b)->Blue = 0, text(minx-2, b)->Green = 0;
	    text(maxx+2, b)->Red = 255, text(maxx+2, b)->Blue = 0, text(maxx+2, b)->Green = 0;
	  }	  
	  
	  // for(int b = miny-2; b < maxy+2; b++){
	  for(int a = minx-1; a < maxx+2; a++){
	    for(int b = miny-1; b < maxy+2; b++){
	      if(text(a, b)->Green == 255 && text(a, b)->Red == 0 && text(a, b)->Blue == 0){
	      }         
	      else{
		text(a, b)->Red = 255, text(a, b)->Blue = 80, text(a, b)->Green = 120;
	      }
	    }
	  }
	  bluecolor(minx-1, miny-1);

	  for(int y = miny-1; y < maxy+2; y++){  //Finds the number of holes.
	    check = true;
	    for(int x = minx-1; x < maxx+2; x++){
	      if(text(x,y)->Red == 255 && text(x,y)->Blue == 80 && text(x,y)->Green == 120){
		check = false;
	      }
	    }
	    if(check == true){
	      key = false;
	    }
	    if(check == false && key == false){
	      key = true;
	      holes++;
	    }
	  }
	  
	  letter();
	  count ++;  //Finds the number of char.
	  rowcheck = false;
	}
	if(rowcheck == true){
	  skip = true;
	}
      }
    }
  }
  
  for(int y = 0; y < sizeh; y++){  //Finds the number of rows.
    check = true;
    for(int x = 0; x < sizew; x++){
      if(text(x,y)->Red == 255 && text(x,y)->Blue == 0 && text(x,y)->Green == 0){
	check = false;
      }
    }
    if(check == true){
      key = false;
    }
    if(check == false && key == false){
      key = true;
      row++;
    }
  }

  cout << endl; 
  cout << "Their are " << count << " characters." << endl;
  cout << "Their are " << row << " rows." << endl;
  cout << "Their are " << holes << " holes." << endl;
}
