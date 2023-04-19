#ifndef _MY_GRAPHIC
#define _MY_GRAPHIC
#define l_win 1250
#define w_win 650
#define decimal 10
#define height_bar 30
#define max_tt 2
#define max_str_time 8
#define max_lentitle 50
#define black			0
#define darkBlue		1
#define darkGreen		2
#define darkCyan		3
#define darkRed		    4
#define darkPink		5
#define darkYellow	 	6
#define darkWhite		7
#define grey			8
#define blue			9
#define green			10
#define cyan			11
#define red				12
#define pink			13
#define yellow			14
#define white			15
#define no_text         NULL
#define font_text       8
#define sizeL           5
#define sizeM           3
#define lth_sizeM       14
#define sizeS           2
#define wth_rw_table    30
#define len_optbar      30
#define MAX_TEXT   50
#define nostyle    0
#define LEFT       1
#define CENTER     0
//#define RIGHT      1
#define bothCaH    2  
#define T_cursor   80 
#define MAX_BUTTON  6 
#include <winbgim.h>
#include <cstdlib>
struct AREA{
	int x;
	int y;
	int length;
	int width;
}; 
struct BUTTON{
	AREA area;
	char text[MAX_TEXT+1];
	int sizechr;
	int text_color;
	int align;
	int bdr_color;
	int bk_color;
};
struct rowTable{
	int nbutton;
	BUTTON buttons[MAX_BUTTON];
};
struct CTick{
	int x;
	int y;
	int R;
};
bool is_area_CTick(CTick& Tick,int x,int y);
void set_CTick(CTick& Tick,int x,int y,int R);
void draw_CTick(CTick& Tick);
void Tick_CTick(CTick& Tick,int color);
void delete_CTick(CTick& Tick,int color);
void set_rowTable(rowTable &rowTB, BUTTON* buttons, int nButton);
bool is_rowTable(rowTable &rowTable,int x,int y);
void draw_rowTable(rowTable &rowTable);
void draw_rowTable2(rowTable &rowTable);
void highlight_rowTable(rowTable &rowTable,int bk_color, int bdr_color, int text_color);
void highlight_rowTable2(rowTable &rowTable,int bk_color, int bdr_color, int text_color);
void highlight_button2(BUTTON &BT, int bk_color, int bdr_color, int text_color);
void set_area(AREA &area,int x,int y,int lth,int wth);
bool is_area(AREA &area,int x,int y);
void highlight_button(BUTTON &BT, int bk_color, int bdr_color,int text_color);
void set_button(BUTTON &BT, AREA &area, char* text,int sizechr,int text_color, int align, int bdr_color, int bk_color);
void draw_button(BUTTON &BT);
void draw_button2(BUTTON &BT);
void delete_button(BUTTON &BT, int color);
int left(int x);
int center(int x, int length, int lentext,int lenchr);
void append_tt_stime(char* str_time,int tt);
void set_time(int seconds,int& hh,int& mm,int& ss);
void out_text_xy( int x, int y, char* text, int bk_color, int text_color);
void create_1_bar( int x, int y, int length, int width, int bk_color, int bdr_color);
void create_1_bar_text( int x, int y, int length, int width, int bk_color, int bdr_color, char text[], int sizechr, int text_color, int isCenter);
void create_1_bar_text2( int x, int y, int length, int width, int bk_color, int bdr_color, char text[], int sizechr, int text_color, int isCenter);
void create_1_row_of_table( int x, int y, int lengths[], int width, int nColumn,int bk_color,int bdr_color);
void create_1_row_of_table_text(int x, int y, int lengths[], int width, int nColumn,int bk_color,int bdr_color,char titles[][max_lentitle],int sizechr, int text_color);
void create_table( int x, int y, int lengths[], int width, int nColumn, int nRow, char titles[][max_lentitle],int lenchr,int text_color,int color_row1, int bdr_color);
void print_time( int x, int y, int time);	
void draw_circle(int x,int y,int R,int color);
void create_solid_polygon(int x_y[],int n_xy,int bk_color);
void create_1_bar_opt( int x, int y, int length, int width, int bk_color,int bdr_color);
void draw_button_opt(BUTTON &BT);
void login_interface();
void draw_cursor(int x,int y,int color);	
void print_cursor(int x,int y, int &n);	
bool is_area_opt(BUTTON& BT,int x,int y);
void highlight_button_opt(BUTTON &BT,int bk_color,int bdr_color,int text_color);
void print_text_bar(int x,int y, char* start,int n, int bk_color,int text_color);	
void set_exit(BUTTON &exit,char* text,int x,int y,int color);	                  
#endif

