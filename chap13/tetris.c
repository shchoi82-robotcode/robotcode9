/***********************************************************/
/*
tetris
shchoi82@gmail.com

update : 2010/4/01
version : 1.0
*/
/***********************************************************/

#include<stdlib.h>
#include<unistd.h>
#include<ncurses.h>
#include<signal.h>
#include<sys/time.h>

#define BOARD_WIDTH		12
#define BOARD_HEIGHT	20
//   ***   // 
//	 *     //
char block1[4][3][3]={{{1,1,1},
				       {1,0,0},
				       {0,0,0}},

					  {{1,0,0},
					   {1,0,0},
					   {1,1,0}},
 
					  {{0,0,1},
					   {1,1,1},
					   {0,0,0}},
 
					  {{1,1,0},
					   {0,1,0},
					   {0,1,0}}};

//   ***   // 
//	   *   //
char block2[4][3][3]={{{1,1,1},
				       {0,0,1},
				       {0,0,0}},

					  {{1,1,0},
					   {1,0,0},
					   {1,0,0}},
 
					  {{1,0,0},
					   {1,1,1},
					   {0,0,0}},

					  {{0,1,0},
					   {0,1,0},
					   {1,1,0}}};

//    *    // 
//	 ***   //
char block3[4][3][3]={{{0,1,0},
				       {1,1,1},
				       {0,0,0}},

					  {{0,1,0},
					   {1,1,0},
					   {0,1,0}},

					  {{1,1,1},
					   {0,1,0},
					   {0,0,0}},
 
					  {{1,0,0},
					   {1,1,0},
					   {1,0,0}}};

//   **    // 
//	 **    //
char block4[2][2]={{1,1},
			       {1,1}};


//   **    // 
//	  **   //
char block5[2][3][3]={{{1,1,0},
				       {0,1,1},
				       {0,0,0}},

					  {{0,1,0},
					   {1,1,0},
					   {1,0,0}}};
//    **   // 
//	 **    //
char block6[2][3][3]={{{0,1,1},
				       {1,1,0},
				       {0,0,0}},

					  {{1,0,0},
					   {1,1,0},
					   {0,1,0}}};

//    ****    // 
char block7[2][4][4]={{{1,1,1,1},
				       {0,0,0,0},
				       {0,0,0,0},
				       {0,0,0,0}},

					  {{1,0,0,0},
					   {1,0,0,0},
				       {1,0,0,0},
					   {1,0,0,0}}};

struct block_info
{
	void *block;
	int shape;		// ¿¿¿¿ ¿¿¿¿¿ ¿¿ ¿¿¿
	int cols;
	int rows;
}block[7]={{(void*)block1,4,3,3},
		   {(void*)block2,4,3,3},
		   {(void*)block3,4,3,3},
		   {(void*)block4,1,2,2},
		   {(void*)block5,2,3,3},
		   {(void*)block6,2,3,3},
		   {(void*)block7,2,4,4}};

//board¿ ¿¿
struct slocation{
	unsigned int x;
	unsigned int y;
}bloc={2,1};

//¿¿¿¿
struct location{
	unsigned int x;
	unsigned int y;
}loc;

int block_no;
int block_shape;
char board[BOARD_HEIGHT][BOARD_WIDTH];
char tmpboard[BOARD_HEIGHT][BOARD_WIDTH];		// ¿¿¿ ¿¿ ¿¿¿¿

void move_block(int key);
int check(int dir);			// ¿¿¿ ¿¿¿ ¿¿¿ ¿¿¿¿.
void next_block(void);
void draw_tmpboard(void);	//¿¿¿¿¿ ¿¿ board+block(¿¿¿¿)
void draw_board(void);		//¿¿¿ ¿¿
void heap(void);
void line_clear(void);
void init(void);
void action(void);
void timer(void);
void print_context(void);

int main(void)
{
    initscr();

    timer();
    init();
    next_block();
    while(1)
    {
        move_block(getch());
		// ¿¿¿ ¿¿
		// ¿¿¿ ¿¿¿¿ ¿¿..
	}
	endwin();

	return 1;
}

void action(void)
{
    move_block(KEY_DOWN);
}

void timer(void)
{
    struct sigaction newact;
    struct itimerval value;

    newact.sa_handler = action;
    newact.sa_flags = SA_RESTART;
    sigemptyset(&newact.sa_mask);
    sigaction(SIGALRM, &newact, NULL);

    value.it_interval.tv_sec = 1;
    value.it_interval.tv_usec = 0;
    value.it_value = value.it_interval;
    setitimer(ITIMER_REAL, &value, NULL);
}


void next_block(void)
{
	
	
	srand(time(NULL));
	block_no = rand()%7;	//¿¿ ¿¿¿
	block_shape=0;			//¿¿¿¿ ¿¿¿
	loc.x=4;				//¿¿¿¿
	loc.y=0;

	if(!check(0))
	{
		endwin();
		exit(1);
	}				// ¿¿¿ ¿¿¿

	draw_tmpboard();
	draw_board();			//¿¿¿ ¿¿ move¿ ¿¿¿ ¿¿¿¿¿.. ¿¿¿ ¿¿¿¿¿
	return;
}

int check(int key)		//¿¿¿ ¿¿¿ ¿¿¿ ¿¿¿¿.
{			
	int i,j;
	int rows=block[block_no].rows;	// ¿¿¿ ¿¿¿¿ ¿¿
	int cols=block[block_no].cols;	// ¿¿¿ ¿¿¿¿ ¿¿

	void *a=block[block_no].block;
	
	int tmpx=loc.x;
	int tmpy=loc.y;
	int tmpshape=block_shape;

	int bound = block[block_no].shape-1;		// ¿¿¿ shape

	switch(key)
	{
		case KEY_UP:
			tmpshape == bound ? tmpshape = 0 : tmpshape++ ;		// 
			break;
		case KEY_LEFT:
			tmpx--;
			break;
		case KEY_RIGHT:
			tmpx++;
			break;
		case KEY_DOWN:
			tmpy++;
			break;
	}


	for(i = 0 ; i < rows ; i++)
	{
		for(j = 0 ; j < cols ; j++)
		{
			if(*(char*)(a+(tmpshape*rows*cols)+(i*rows)+j)==1)
			{	
				if(!((tmpy+i)>=0 && (tmpy+i)<BOARD_HEIGHT && (tmpx+j)>=0 && (tmpx+j)<BOARD_WIDTH))	//1.board¿ ¿¿¿ ¿¿¿ ¿¿				
					return 0;
				if(board[tmpy+i][tmpx+j] != 0)	//2.¿¿¿ ¿¿¿ ¿¿¿ ¿¿
					return 0;
			}
		}
	}
	return 1;
}

void move_block(int key)
{
	int bound = block[block_no].shape-1;
	
	if(!check(key))		// ¿¿¿¿ ¿¿¿ ¿¿
	{
		if(key==KEY_DOWN)	// ¿¿¿¿ ¿¿ KEY_DOWN¿¿
		{
			heap();
			line_clear();
			next_block();
		}
		return;
	}

	switch(key)
	{
		case KEY_UP:
			block_shape == bound ? block_shape = 0 : block_shape++;
			break;
		case KEY_LEFT:
			loc.x--;
			break;
		case KEY_RIGHT:
			loc.x++;
			break;
		case KEY_DOWN:
			loc.y++;
			break;
		case 32:		// space key
			while(check(key))
				loc.y++;
			loc.y--;
			heap();
			line_clear();
			next_block();
			break;
	}
	draw_tmpboard();
	draw_board();
}
void draw_tmpboard(void)
{
	int i,j;
	int rows=block[block_no].rows;		//¿¿¿ size
	int cols=block[block_no].cols;
	void *a=block[block_no].block;

	// tempboard¿¿¿ ¿¿ ¿¿¿¿ ¿¿¿¿ ¿¿¿¿¿.
	for(i=0;i<20;i++)
		for(j=0;j<12;j++)
				tmpboard[i][j]=board[i][j];	

	// tempboard¿ ¿¿¿¿ ¿¿ ¿¿¿ ¿¿
	for(i = 0 ; i < rows ; i++)
		for(j = 0 ; j < cols ; j++)
			if(*(char*)(a+(block_shape*rows*cols)+(i*rows)+j)==1)	
				tmpboard[loc.y+i][loc.x+j]=block_no+1;

	return;
}


void draw_board(void)
{
	int i,j;
//	init_color(COLOR_RED, 700, 0, 0);
    /* param 1     : color name
     * param 2, 3, 4 : rgb content min = 0, max = 1000 */	

	for(i = 0 ; i < 20 ; i++)
		for(j = 0 ; j < 12 ; j++)
			if(tmpboard[i][j]!=0)	
			{
				attron(/*A_REVERSE*/COLOR_PAIR(tmpboard[i][j]));
				mvaddstr(bloc.y+i,bloc.x+(j*2),"**");				
				attroff(/*A_REVERSE*/COLOR_PAIR(tmpboard[i][j]));
			}
			else
			{
				mvaddstr(bloc.y+i,bloc.x+(j*2),"--");				
			}
	refresh();
}


void heap(void)
{
	int i,j;
	int rows=block[block_no].rows;
	int cols=block[block_no].cols;
	
	void *a=block[block_no].block;

	for(i = 0 ; i < rows ; i++)
		for(j = 0 ; j < cols ; j++)
			if(*(char*)(a+(block_shape*rows*cols)+(i*rows)+j)==1)
				board[loc.y+i][loc.x+j] = block_no+1+10;
	

}



void print_context(void)
{
	int x=0;
	int y=30;

	mvprintw(y,x,"block_no=%d",block_no);
	mvprintw(y+1,x,"block_shape=%d",block_shape);
	mvprintw(y+2,x,"loc=(%d,%d)",loc.x,loc.y);
	
}
void line_clear(void)
{
	int flag;
	int i,j,ii,jj;

	for(i = 19 ; i >=0 ; i--)
	{
		flag=0;		// ¿¿ ¿¿ flag = 0 ¿¿
		for(j = 0 ; j < 12 ; j++)
			if(board[i][j]==0)	
				flag=1;
		if(flag==0)
		{
			for(ii = i ; ii >= 1 ; ii--)
				for(jj = 0 ; jj < 12 ; jj++)
					board[ii][jj] = board[ii-1][jj];
			i++;
		}
		
	}
}

void init(void)
{
	curs_set(0); 		// 0:invisible 1:normal 2:very visible
	noecho();			// echo¿¿
	cbreak();
	start_color();
	keypad(stdscr,TRUE);
// ¿¿¿¿ ¿¿ ¿¿
	init_pair(1,COLOR_RED,COLOR_RED);
	init_pair(2,COLOR_GREEN,COLOR_GREEN);
	init_pair(3,COLOR_YELLOW,COLOR_YELLOW);
	init_pair(4,COLOR_BLUE,COLOR_BLUE);
	init_pair(5,COLOR_MAGENTA,COLOR_MAGENTA);
	init_pair(6,COLOR_WHITE,COLOR_WHITE);
	init_pair(7,COLOR_CYAN,COLOR_CYAN);
	init_pair(11,COLOR_BLACK,COLOR_RED);
// ¿¿ ¿¿
	init_pair(12,COLOR_BLACK,COLOR_GREEN);
	init_pair(13,COLOR_BLACK,COLOR_YELLOW);
	init_pair(14,COLOR_BLACK,COLOR_BLUE);
	init_pair(15,COLOR_BLACK,COLOR_MAGENTA);
	init_pair(16,COLOR_BLACK,COLOR_WHITE);
	init_pair(17,COLOR_BLACK,COLOR_CYAN);

}
