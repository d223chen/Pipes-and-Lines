/*
CODE PAGE 437: PIPES AND LINES!!!
*/


#include <iostream>
#include <windows.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <vector>
#include <fstream>
#include <string>


#include <mmsystem.h>

//define some shortcut strings to represent the box-builder codes.
#define blp 200 //bottom left pipe
#define trp 187 //top right pipe
#define brp 188 //bottom right pipe
#define tlp 201 //top left pipe
#define hp 205 //horizontal pipe
#define vp 186 //vertical pipe

#define tp 203 //T pipe
#define btp 202 //Bottom T pipe (an upside down "T")
#define ltp 204 //Left T pipe (T rotated left 90 degrees)
#define rtp 185 //Right T pipe (T rotated right 90 degrees)

#define cp 206 //cross pipe

using namespace std;


//elementof:: int, int, int[] -> bool
//checks if value i is in the array[] of length length
int elementof(int i, int length, int array[]){
	for(int j = 0; j < length; j++){
		if(i == array[j])
		{
			return 1;
		}
	}
	return 0;
}

//rando:: int, int -> int
//returns a random integer in the interval [min,max]
int rando(int min, int max)
{
	
	return rand() * (max - min + 1) + min;
}


//pickrand:: int, int[] -> int
//randomly choose and return an element of an array[] of length length
int pickrand(int length, int array[]){
	int random = rando(0,length - 1);
	int result = array[random];
	return result;
}

//title:: ->
//Prints the title page!! :)
void title(){
		//////////////////////////////////////////
	  string line;
 	 	ifstream myfile ("pipesandlinestitle.txt");
  	if (myfile.is_open())
  	{
   	 while ( getline (myfile,line) ){
      	cout << line << '\n';
    	}
    	myfile.close();
  	}
  	
  	cout << "by Daniel Chen. April 16, 2017. \n";
  	getchar();
/////////////////////////////////////////////////

}

//Special pipes, defined by their ability to be connected to later pipes.
int rightpipe[7] = { tlp, blp, hp, cp, tp, btp, ltp}; //Any pipe that can be connected at the right.
int downpipe[7] = {tlp,trp,vp,cp,tp,ltp,rtp}; //Any pipe that can be connected from below.


//connectabove:: int, vector -> bool
//check if your current position can be connected from above. Returns 1 for true and 0 for false.
int connectabove(int j, vector < vector <int> > &map){
	if( elementof(map[j][0], 7, downpipe) )
	{
		return 1;
	}
	else{
		return 0;
	}
}

//connectleft:: int, vector -> bool
//check if your current position can be connected from the left. Returns 1 for true and 0 for false.
//Note that we assert that j > 0.
int connectleft(int j, vector < vector <int> > &map){
	if( elementof(map[j - 1][1], 7, rightpipe) )
	{
		return 1;
	}
	else{
		return 0;
	}
}

//mapout:: int, int, int, int->
//The main process function. Takes input for width and height from the user, and then generates a random map in those boundaries.
void mapout(int width, int height, int sound, int delay){
   
    //

    
    
	// 
	//Now that we've got the desired map dimensions, lets initialize an array. It will contain the Code Page 437 value for each character to be drawn to the screen.
	//We make map a two dimensional vector (i.e. a vector of vectors), that way we can do dynamic memory allocation at runtime.
	vector < vector <int> >  map (width, vector<int> (2));
    
	/*
    Setup the map with values between 179 and 218, inclusive. These are the *Box-drawing Characters* from Code Page 437.
	The number in the array corresponds to the box-drawing character to be drawn there.
    */
    //Loop across the map. Start at the left of the current height (j), initialize map[j,i], then move over right one.
    for(int i = 0; i < height; i++)
    {
    	for(int j = 0; j < width; j ++)
    	{
    		int *x = &map[j][1];//point to the current position of the map. We will decide what this is now.
    		
    		//Top left corner of map?
    		if ((i == 0) &&(j == 0)){
    			*x = tlp;  //make the top left corner of the map a top-left pipe, 'cause. 
			}
			
			else if ((i == 0 ) && (j == width - 1)){
				if (elementof(map[j -1][1], 7, rightpipe)){
				*x = trp;}
				else *x = 32;
			}
			else if ((i == height - 1) && (j == 0)){
				if (elementof(map[j][0], 7, downpipe)){
				*x = blp;}
				else *x = 32;
			}
			else if ((i == height - 1 ) && (j == width - 1)){
				if ( connectleft(j,map) && connectabove(j,map) ){
					*x = brp;
				}
				else if (connectleft(j,map)){
					*x = hp;
				}
				else if  (connectabove(j,map)) {
					*x = vp;
				}
				else {
					*x = 32;
				}
			}
			
			//if we are at the top of the map
			else if (i == 0){ 
				if ( connectleft(j,map)){ //if the piece to the left can be connected at the right, choose a piece to connect.
					int array[3] = {trp,hp,tp};
					*x = array[rand()%3];
				}
				else{
					int array[2] = {tlp, 32}; //32 = whitespace as per the space bar.
					*x = array[rand()%2];
				}
			}
			
			//if we are at the leftmost of the map
			else if (j == 0){ 
				if( connectabove(j,map)) { //if it can be connected at from above
					int array[3] = {vp,ltp, blp};
					*x = array[rand()%3];
				}
				else{
					int array[2] = {tlp, 32}; //32 = whitespace as per the space bar.
					*x = array[rand()%2];
				}
			}
			
			
			//if we are at the rightmost of the map
			else if (j == width - 1){
				if ( connectleft(j,map) && connectabove(j,map) ){ //if it can be connected to the left and above
					int array[2] = {rtp,brp};
					*x = array[rand()%2];
				}
				else if( connectleft(j,map) ) { //if it can only be connected at the left
					*x = trp;
				}
				else if( connectabove(j,map) ) { //if it can only be connected at from above
					*x = vp;
				}
				else{	 //32 = whitespace as per the space bar.
					*x = 32;
				}
			}
			
			
			//if we are at the bottom of the map
			else if (i == height - 1){
				if ( connectleft(j,map) && connectabove(j,map) )
				{
					int array[2] = {brp,btp};
					*x = array[rand() % 2];
				}
				else if (connectleft(j,map)  ){
					*x = hp;
				}
				else if (connectabove(j,map) ){
					*x = blp;
				}
				else{
					*x = 32;
				}
				
			}
			
			
				
			//somewhere in the middle of all of this nonsense.
			else{
				if ( connectleft(j,map)  && connectabove(j,map) ){ //if it can be connected to the left and above
					int array[3] = {rtp,cp,brp};
					*x = array[rand()%3];
				}
				else if( connectleft(j,map) ) { //if it can only be connected at the left
					int array[3] = {hp,trp,tp};
					*x = array[rand()%3];
				}
				else if( connectabove(j,map) ) { //if it can only be connected at from above
					int array[3] = {vp,ltp,blp};
					*x = array[rand()%3];
				}
				else{
					int array[2] = {tlp, 32}; //32 = whitespace as per the space bar.
					*x = array[rand()%2];
				}
			}
			//Now that we've decided what goes here, lets print it!	
			
    		cout << (char) map[j][1]; //print what we just decided for the current coordinate.
    		
			map[j][0] = map[j][1]; //push this value up into the buffer.
			
			
			//If we asked for sound, bleep!!
			if (sound == 1){
				Beep(rand()%3000 + 200,500);  
			}
			Sleep (delay); //delay for the amount specified by the user.
			
		}
		
		cout << endl; //we reached the end of our line, so move to the next one.
		
	}
}


int main()
{
	//Set the console to Code Page 437!! Standard Windows ALT + number pad combination characters...
	//Note, native to windows OS (requires windows.h library which is obviously not available in Linux or Mac, unless you do some serious digging around).
    SetConsoleCP(437);
    SetConsoleOutputCP(437);
    
    //////////////////////////////////////////////////////////////////
	srand(time(NULL));//random time seed.
	int width = 200, height = 30; //width and height variables for later use.
	int delay = 0; //delay variable for speed of printing.
	int sound = 0; //a boolean indicating whether we desire random sounds.
	int choice = 0; //menu choice value.
	//////////////////////////////////////////////////////////////////

    
    title(); //print the title
    
	
    while(0 < 1 + 2 + 3 + 4  + 5){
    	
    	cout << "MENU" << endl;
    	cout << "1. Generate Random Map" << endl << "2. Settings" << endl;
    	
    	cout << "What would you like to do? [1,2]:";
    	cin >> choice;
    	
    	switch(choice){
			case 1:   
	    		cout << "Hello, enter your width:";
    			cin >> width;
    			cout << "Now enter your height:";
    			cin >> height;
    	
				mapout(width,height,sound,delay); // given the map dimensions, print a random map and keep doing the doggy game...or whatever.
			break;
			
			
			case 2:
				cout << "SETTINGS" << endl;
				cout << "1. Print Speed" << endl << "2. Sound FX" << endl;
				cout << "What would you like to do? [1,2]:";
    			cin >> choice;	
    			
    			switch(choice){
    				case 1:
    					
    					cout << "Enter your new print delay in milliseconds(ms). [Enter 0 for no delay]: ";
    					cin >> delay;
    				break;
    				case 2:
    				
						cout << "Enter whether you would like annoying random sounds in between printing. [1 = yes, 0 = no]";
						cin >> sound;
					break;
					default:
						cout << "Wrong button!" << endl;
						
				}
			break;
			default:
				cout << "Are you some sort of...!!? Try again! " << endl;
		}
	}	
	
    return 0;
}
