#include "graphic.h"
int left(int x){
	return x+10;
}
int center(int x, int length, int lentext, int size){
	return x + (length - (size-sizeM+lth_sizeM)*lentext)/2;
}
void set_exit(BUTTON &exit,char* text,int x,int y,int color){
	AREA buff;
	set_area(buff,x-strlen(text)*lth_sizeM,y,strlen(text)*lth_sizeM,30);
	set_button(exit,buff,text,sizeM,color,CENTER,cyan,cyan);
	draw_button(exit);
	line(x-strlen(text)*lth_sizeM,y+27,x,y+27);
}
void out_text_xy( int x, int y, char* text, int bk_color, int text_color){
	setcolor( text_color);
	setbkcolor( bk_color);
	outtextxy( x, y, text);
}
void print_text_bar(int x,int y, char* text,int n, int bk_color,int text_color){
    settextstyle(font_text,0,sizeS);
	if(strlen(text)<n) {
		out_text_xy(x,y,text,bk_color,text_color);
	}
	else{
		char ch = text[n];
		text[n]='\0';
		out_text_xy(x,y,text,bk_color,text_color);
 		text[n] = ch;	
	}
}
void out_text_bar(int x,int y, char* text,int n, int bk_color,int text_color,int size){
	settextstyle(font_text,0,size);
	if(strlen(text)<n) {
		out_text_xy(x,y,text,bk_color,text_color);
	}
	else{
		char ch = text[n];
		text[n]='\0';
		out_text_xy(x,y,text,bk_color,text_color);
 		text[n] = ch;	
	}
}
void create_1_bar( int x, int y, int length, int width, int bk_color, int bdr_color){
	setfillstyle( 1, bk_color);
	bar( x, y, x+length, y+width);
   	setcolor( bdr_color);
	rectangle( x, y, x+length, y+width);
}
void create_1_bar_text( int x, int y, int length, int width, int bk_color, int bdr_color, char text[], int sizechr,int text_color,int align) {
	settextstyle(font_text,0,sizechr);
    create_1_bar( x, y, length, width, bk_color, bdr_color);
	if(align==CENTER) out_text_xy(center(x,length,strlen(text),sizechr), y+3, text, bk_color, text_color);      
	else out_text_bar(left(x), y+3, text, (length-20)/(lth_sizeM-2*(sizeM-sizechr)), bk_color, text_color,sizechr);                  	
}
void create_1_bar_text2( int x, int y, int length, int width, int bk_color, int bdr_color, char text[], int sizechr,int text_color,int align) {
	settextstyle(font_text,0,sizechr);
   	setcolor( bdr_color);
	rectangle( x, y, x+length, y+width);
	if(align==CENTER) out_text_xy(center(x,length,strlen(text),sizechr), y+3, text, bk_color, text_color);                
	else out_text_bar(left(x), y+3, text, (length-20)/(lth_sizeM-2*(sizeM-sizechr)), bk_color, text_color,sizechr);               	
}
void create_1_row_of_table( int x, int y, int lengths[], int width, int nColumn,int bk_color,int bdr_color){
	for(int column=0; column<nColumn; column++){ 
    	create_1_bar(x ,y, lengths[column], width, bk_color, bdr_color);
    	x += lengths[column];
	}
}
void create_1_row_of_table_text(int x, int y, int lengths[], int width, int nColumn,int bk_color,int bdr_color,char titles[][max_lentitle],int sizechr,int text_color){
    for(int column=0; column<nColumn; column++){ 
    	create_1_bar_text(x ,y, lengths[column], width, bk_color, bdr_color, titles[column],sizechr, text_color, CENTER);
    	x += lengths[column];
    }
}
void create_table( int x, int y, int lengths[], int width, int nColumn, int nRow, char titles[][max_lentitle],int sizechr,int text_color,int color_row1, int bdr_color){
    char buff[ max_tt+1];
	for( int row=0; row<nRow; row++){
		if(row==0)	create_1_row_of_table_text( x, y+width*row, lengths, width, nColumn, color_row1, bdr_color, titles,sizechr, text_color);              								   	
		else create_1_row_of_table( x, y+width*row, lengths, width, nColumn, white, bdr_color);   
    }
}
void draw_circle(int x,int y,int R,int color){
	setcolor(color);
	circle(x,y,R);
	setfillstyle(1,color);
    floodfill(x,y,color);
}
void append_tt_stime(char* str_time,int tt){
	char buff[max_tt+1];
	if(tt<10) strcat( str_time, "0");
	strcat( str_time, itoa( tt, buff, decimal));
}
void create_solid_polygon(int x_y[],int n_xy,int bk_color){
	setfillstyle(1,bk_color);
	fillpoly(n_xy,x_y);
}
void create_1_bar_opt( int x, int y, int length, int width, int bk_color,int bdr_color,int text_color){
	create_1_bar( x, y, length, width, bk_color, bdr_color);
	int _x = x + length;
	create_1_bar( _x, y, width, len_optbar, bk_color, bdr_color);
	int x_y[]={_x+5,y+8,_x+25,y+8,_x+15,y+23,_x+5,y+8};
	create_solid_polygon( x_y, 4, text_color);
}
void set_time(int seconds,int& hh,int& mm,int& ss){
	hh = seconds/3600;
	mm = (seconds%3600)/60;
	ss = (seconds%3600)%60;
}
void print_time( int x, int y, int seconds){
    int hh, mm, ss;
	set_time(seconds,hh,mm,ss);
	char str_time[max_str_time+1]; 
	append_tt_stime(str_time,hh);
	strcat( str_time, ":");
	append_tt_stime(str_time,mm);
	strcat( str_time, ":");
	append_tt_stime(str_time,ss);
	if(seconds<31) setcolor(red);
	else setcolor(black);
	settextstyle(font_text,0,sizeM);
	setbkcolor(white);
	outtextxy( x, y, str_time);
}
void login_interface(){
	setbkcolor(cyan);
	cleardevice();
	settextstyle(font_text,0,sizeL);
	out_text_xy(l_win/3+10,w_win/8,(char*)"THI TRAC NGHIEM",cyan,black);
	rectangle(l_win/2-350,w_win/4,l_win/2+350,w_win/4+400);
	settextstyle(font_text,0,sizeM+1);
	outtextxy(l_win/2-100,w_win/3-20,(const char*)"DANG NHAP");
	settextstyle(font_text,0,sizeM);
	outtextxy(l_win/3,w_win/3+70,(const char*)"TAI KHOAN: ");
	outtextxy(l_win/3,w_win/3+140,(const char*)"MAT KHAU: ");
	create_1_bar(l_win/2-50,w_win/3+68,250,30,white,white);
	create_1_bar(l_win/2-50,w_win/3+138,250,30,white,white);
}
void draw_cursor(int x,int y,int color){
	setcolor(color);
	line(x,y,x,y+20);
}
void print_cursor(int x,int y, int &n){
	n--;
	if(n==T_cursor) draw_cursor(x, y,black);
	else if(n==T_cursor/2) draw_cursor(x,y,white);
	else if(n==0)  n=T_cursor+1;
}

void set_area(AREA &area,int x1,int y1,int lth,int wth){
	area.x=x1;
	area.y=y1;
	area.length=lth;
	area.width=wth;
}
void set_button(BUTTON &BT, AREA &area, char* text,int sizechr,int text_color, int align, int bdr_color, int bk_color){
	BT.area = area;
	strncpy(BT.text,text,MAX_TEXT);
	BT.text[MAX_TEXT] = '\0';
	BT.sizechr = sizechr;
	BT.text_color = text_color;
	BT.align = align;
	BT.bdr_color = bdr_color;
	BT.bk_color = bk_color;
}
void draw_button(BUTTON &BT){
	create_1_bar_text(BT.area.x, BT.area.y, BT.area.length, BT.area.width, BT.bk_color, BT.bdr_color,BT.text,BT.sizechr,BT.text_color,BT.align);
}
void draw_button2(BUTTON &BT){
	create_1_bar_text2(BT.area.x, BT.area.y, BT.area.length, BT.area.width, BT.bk_color, BT.bdr_color,BT.text,BT.sizechr,BT.text_color,BT.align);
}
bool is_area(AREA &area,int x,int y){
	return (area.x<=x)&&(x<=area.x+area.length)&&(area.y<=y)&&(y<=area.y+area.width);
}
void highlight_button(BUTTON &BT, int bk_color, int bdr_color, int text_color){
	create_1_bar_text(BT.area.x, BT.area.y, BT.area.length, BT.area.width, bk_color, bdr_color,BT.text,BT.sizechr,text_color,BT.align);	
}
void highlight_button2(BUTTON &BT, int bk_color, int bdr_color, int text_color){
	create_1_bar_text2(BT.area.x, BT.area.y, BT.area.length, BT.area.width, bk_color, bdr_color,BT.text,BT.sizechr,text_color,BT.align);	
}
void delete_button(BUTTON &BT, int color){
	create_1_bar(BT.area.x,BT.area.y,BT.area.length,BT.area.width,color,color);
}
void set_rowTable(rowTable &rowTB, BUTTON* buttons, int nButton){
	for(int i=0;i<nButton;i++) rowTB.buttons[i] = buttons[i];
	rowTB.nbutton = nButton;
}
bool is_rowTable(rowTable &rowTable,int x,int y){
	AREA areaFirst = rowTable.buttons[0].area;
	AREA areaLast = rowTable.buttons[rowTable.nbutton-1].area;
	return areaFirst.x<x&&areaFirst.y<y&&(areaLast.x+areaLast.length)>x&&(areaLast.y+areaLast.width)>y;
}
void draw_rowTable(rowTable &rowTable){
	for(int i=0;i<rowTable.nbutton;i++) draw_button(rowTable.buttons[i]);
}
void draw_rowTable2(rowTable &rowTable){
	for(int i=0;i<rowTable.nbutton;i++) draw_button2(rowTable.buttons[i]);
}
void highlight_rowTable(rowTable &rowTable,int bk_color, int bdr_color, int text_color){
	for(int i=0;i<rowTable.nbutton;i++) highlight_button(rowTable.buttons[i],bk_color,bdr_color,text_color);
}
void highlight_rowTable2(rowTable &rowTable,int bk_color, int bdr_color, int text_color){
    for(int i=0;i<rowTable.nbutton;i++) highlight_button2(rowTable.buttons[i],bk_color,bdr_color,text_color);
}
void draw_CTick(CTick& Tick){
	draw_circle(Tick.x,Tick.y,Tick.R,white);
}
void Tick_CTick(CTick& Tick,int color){
	draw_circle(Tick.x,Tick.y,Tick.R-3,color);
}
void delete_CTick(CTick& Tick,int color){
	draw_circle(Tick.x,Tick.y,Tick.R,color);
}
void set_CTick(CTick& Tick,int x,int y,int R){
	Tick.x=x;
	Tick.y=y;
	Tick.R=R;
}
bool is_area_CTick(CTick& Tick,int x,int y){
	return (Tick.x-Tick.R<=x)&&(Tick.y-Tick.R<=y)&&(Tick.x+Tick.R>=x)&&(Tick.y+Tick.R>=y);
}
void draw_button_opt(BUTTON &BT){
	create_1_bar_opt(BT.area.x, BT.area.y, BT.area.length, BT.area.width, BT.bk_color, BT.bdr_color,grey);
	settextstyle(font_text,0,BT.sizechr);
    out_text_xy(BT.area.x+7, BT.area.y+3, BT.text, BT.bk_color, BT.text_color);   
}
void highlight_button_opt(BUTTON &BT,int bk_color,int bdr_color,int text_color){
	create_1_bar_opt(BT.area.x, BT.area.y, BT.area.length, BT.area.width, bk_color, bdr_color,text_color);
	settextstyle(font_text,0,BT.sizechr);
    out_text_xy(BT.area.x+10, BT.area.y+3, BT.text, bk_color, text_color);  
}
bool is_area_opt(BUTTON& BT,int x,int y){
	return BT.area.x+BT.area.length<=x&&BT.area.x+BT.area.length+30>=x&&BT.area.y<=y&&BT.area.y+BT.area.width>=y;
}






