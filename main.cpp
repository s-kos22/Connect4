#include <iostream>
#include<graphics.h>
using namespace std;
int x_left_board=260,x_right_board=750,y_top_board=130,y_bottom_board=550;
int MATRIX[6][7];
void draw_circle( int x,int y, int color, int r)
{
    setcolor(color);
    for(int ii=r ; ii>=0; ii--)
        circle(x,y,ii);
}
void draw_circles_in_board ( int color)
{
    setcolor(color);
    for (int i=165; i<=550; i+=70)
        for (int j=x_left_board+35; j<=x_right_board; j+=70)
            draw_circle(j,i,color,25);
}
int col_mouse_hover( int x,int y)
{
    if(y>=y_top_board && y<=y_bottom_board && x>=x_left_board &&x<=x_right_board)
    {
        if(x>=x_left_board+0*70 && x<=x_left_board+1*70)
            return 0;
        else if(x>=x_left_board+1*70 && x<=x_left_board+2*70)
            return 1;
        else if(x>=x_left_board+2*70 && x<=x_left_board+3*70)
            return 2;
        else if(x>=x_left_board+3*70 && x<=x_left_board+4*70)
            return 3;
        else if(x>=x_left_board+4*70 && x<=x_left_board+5*70)
            return 4;
        else if(x>=x_left_board+5*70 && x<=x_left_board+6*70)
            return 5;
        else if(x>=x_left_board+6*70 && x<=x_left_board+7*70)
            return 6;
    }
    return -1;
}
bool possible_insert_circle( int col)
{
    if(MATRIX[0][col]==2 || MATRIX[0][col]==14)//there has already been inserted a circle there
        return false;
    return true;

}
void insert_circle (int col, int color_player)
{
    int i;

    for (i=5; MATRIX[i][col]!=0; i--);

    MATRIX[i][col]=color_player;
    draw_circle(x_left_board+70*col+35,y_top_board+70*i+35,color_player,27);
}
bool verify_if_win (int player)
{
    bool win=false;
    int i,j;
    int cross_color=14;
    if(player==14)
        cross_color=2;


    //orizontala
    for (i=0; i<6 && !win; i++)
        for (j=0; j<4 && !win; j++)
            if(MATRIX[i][j]==player && MATRIX[i][j]==MATRIX[i][j+1]&&MATRIX[i][j]==MATRIX[i][j+2]&&MATRIX[i][j]==MATRIX[i][j+3])
                win=true;
    if(win)
    {
        setfillstyle(1,cross_color);
        bar(x_left_board+70*(j-1)+5,y_top_board+70*(i-1)+30,x_left_board+70*(j+3)-5,y_top_board+70*(i-1)+40);
        return win;
    }

    //verticala
    for (j=0; j<7 && !win; j++)
        for(i=0; i<3 && !win; i++)
            if(MATRIX[i][j]==player &&MATRIX[i][j]==MATRIX[i+1][j]&&MATRIX[i][j]==MATRIX[i+2][j]&&MATRIX[i][j]==MATRIX[i+3][j])
                win=true;
    if(win)
    {
        setfillstyle(1,cross_color);
        bar(x_left_board+70*(j-1)+30,y_top_board+70*(i-1)+5,x_left_board+70*(j-1)+40,y_top_board+70*(i+3)-5);
        return win;
    }

    //diagonala stanga |-> dreapta
    for( i=0; i<3 && !win; i++)
        for( j=0; j<4 &&!win; j++)
            if(MATRIX[i][j]==player &&MATRIX[i][j]==MATRIX[i+1][j+1]&&MATRIX[i][j]==MATRIX[i+2][j+2]&&MATRIX[i][j]==MATRIX[i+3][j+3])
                win=true;
    if(win)
    {
        setcolor(cross_color);
        line(x_left_board+70*(j-1)+10,y_top_board+70*(i-1)+10,x_left_board+70*(j+2)+60,y_top_board+70*(i+2)+60);
        return win;
    }

    //diagonala dreapte |-> stanga
    for(i=0; i<3 && !win; i++)
        for( j=6; j>=3 && !win; j--)
            if(MATRIX[i][j]==player &&MATRIX[i][j]==MATRIX[i+1][j-1]&&MATRIX[i][j]==MATRIX[i+2][j-2]&&MATRIX[i][j]==MATRIX[i+3][j-3])
                win=true;
    if(win)
    {
        setcolor(cross_color);
        line(x_left_board+70*(j+1)+60,y_top_board+70*(i-1)+10,x_left_board+70*(j-2)+10,y_top_board+70*(i+2)+60);
        return win;
    }


    return win;

}
void print_player_win ( int color_player, bool delete_text)
{
    settextstyle(1,0,5);
    if(!delete_text)
    {
        setcolor(color_player);
        if(color_player==2)
            outtextxy(x_left_board,y_top_board-25, "Player Green Won");
        else
            outtextxy(x_left_board-20,y_top_board-25, "Player Yellow Won");
    }
    else
    {
        setcolor(5);
        outtextxy(x_left_board,y_top_board-25, "Player Yellow Won");
        outtextxy(x_left_board-20,y_top_board-25, "Player Green Won");
    }
}
bool este_selectat_exit( int x, int y)
{
    if(x>=10 && x<=70 && y>=y_top_board+100 && y<=y_top_board+120)
        return true;
    setcolor(15);

    return false;
}
bool este_selectat_newgame ( int x, int y)
{
    if(x>=10 && x<=25+textwidth("Newgame") && y>=y_top_board+30 && y<=y_top_board+30+textheight("Exit"))
        return true;
    return false;
}

int exit_game=0,newgame;
//---Sorodoc Tudor Cosmin---
void draw_hover ()
{
    clearmouseclick(WM_LBUTTONDOWN);
    int color_player=2;
    int ok=true;
    while(!newgame)
    {
        int mouse_x=mousex(), mouse_y=mousey();
        int col=col_mouse_hover(mouse_x,mouse_y);
        if(este_selectat_exit(mouse_x,mouse_y))
        {
            settextjustify(0,0);
            settextstyle(6,0,3);
            setcolor(15);
            outtextxy(10,y_top_board+100+textheight("New Game"),"Exit");
            while(!ismouseclick(WM_LBUTTONDOWN) && este_selectat_exit(mouse_x,mouse_y))
            {
                mouse_x=mousex(), mouse_y=mousey();
            }
            setcolor(13);
            outtextxy(10,y_top_board+100+textheight("New Game"),"Exit");

        }
        if(este_selectat_newgame(mouse_x,mouse_y))
        {
            settextjustify(0,0);
            settextstyle(6,0,3);
            setcolor(15);
            outtextxy(10,y_top_board+50,"New Game");
            while(!ismouseclick(WM_LBUTTONDOWN) && este_selectat_newgame(mouse_x,mouse_y))
            {
                mouse_x=mousex(), mouse_y=mousey();
            }
            setcolor(13);
            outtextxy(10,y_top_board+50,"New Game");

        }
        if(ismouseclick(WM_LBUTTONDOWN) && este_selectat_exit(mouse_x,mouse_y))
            exit_game=1;
        else if (ismouseclick(WM_LBUTTONDOWN) && este_selectat_newgame(mouse_x,mouse_y))
            newgame=1;
        if(exit_game)
            return;
        clearmouseclick(WM_LBUTTONDOWN);
        while(col!=-1 && ok)
        {
            if(col==0)
            {
                draw_circle(x_left_board+col*70+35,y_top_board-35,color_player,25);
                while(col_mouse_hover(mouse_x,mouse_y)==0 && ok)
                {
                    mouse_x=mousex(), mouse_y=mouse_y;
                    if(ismouseclick(WM_LBUTTONDOWN) && possible_insert_circle(col))
                    {
                        clearmouseclick(WM_LBUTTONDOWN);
                        insert_circle(col, color_player);

                        if(verify_if_win(color_player))
                        {
                            ok=false;
                            draw_circle(x_left_board+col*70+35,y_top_board-35,0,25);
                            print_player_win(color_player,0);
                        }
                        if(color_player==2)
                            color_player=14;
                        else
                            color_player=2;
                        if(ok)
                            draw_circle(x_left_board+col*70+35,y_top_board-35,color_player,25);
                    }
                }
                if(ok)
                    draw_circle(x_left_board+col*70+35,y_top_board-35,0,25);
            }
            else if(col==1)
            {
                draw_circle(x_left_board+col*70+35,y_top_board-35,color_player,25);
                while(col_mouse_hover(mouse_x,mouse_y)==1 && ok)
                {
                    mouse_x=mousex(), mouse_y=mouse_y;
                    if(ismouseclick(WM_LBUTTONDOWN) && possible_insert_circle(col))
                    {
                        clearmouseclick(WM_LBUTTONDOWN);
                        insert_circle(col, color_player);
                        if(verify_if_win(color_player))
                        {
                            ok=false;
                            draw_circle(x_left_board+col*70+35,y_top_board-35,0,25);
                            print_player_win(color_player,0);
                        }
                        if(color_player==2)
                            color_player=14;
                        else
                            color_player=2;
                        if(ok)
                            draw_circle(x_left_board+col*70+35,y_top_board-35,color_player,25);
                    }
                }
                if(ok)
                    draw_circle(x_left_board+col*70+35,y_top_board-35,0,25);
            }
            else if(col==2)
            {
                draw_circle(x_left_board+col*70+35,y_top_board-35,color_player,25);
                while(col_mouse_hover(mouse_x,mouse_y)==2 && ok)
                {
                    mouse_x=mousex(), mouse_y=mouse_y;
                    if(ismouseclick(WM_LBUTTONDOWN) && possible_insert_circle(col))
                    {
                        clearmouseclick(WM_LBUTTONDOWN);
                        insert_circle(col, color_player);
                        if(verify_if_win(color_player))
                        {
                            ok=false;
                            draw_circle(x_left_board+col*70+35,y_top_board-35,0,27);
                            print_player_win(color_player,0);
                        }
                        if(color_player==2)
                            color_player=14;
                        else
                            color_player=2;
                        if(ok)
                            draw_circle(x_left_board+col*70+35,y_top_board-35,color_player,25);
                    }
                }
                if(ok)
                    draw_circle(x_left_board+col*70+35,y_top_board-35,0,25);
            }
            else if(col==3)
            {
                draw_circle(x_left_board+col*70+35,y_top_board-35,color_player,25);
                while(col_mouse_hover(mouse_x,mouse_y)==3 && ok)
                {
                    mouse_x=mousex(), mouse_y=mouse_y;
                    if(ismouseclick(WM_LBUTTONDOWN) && possible_insert_circle(col))
                    {
                        clearmouseclick(WM_LBUTTONDOWN);
                        insert_circle(col, color_player);
                        if(verify_if_win(color_player))
                        {
                            ok=false;
                            draw_circle(x_left_board+col*70+35,y_top_board-35,0,25);
                            print_player_win(color_player,0);
                        }
                        if(color_player==2)
                            color_player=14;
                        else
                            color_player=2;
                        if(ok)
                            draw_circle(x_left_board+col*70+35,y_top_board-35,color_player,25);
                    }
                }
                if(ok)
                    draw_circle(x_left_board+col*70+35,y_top_board-35,0,25);
            }
            else if(col==4)
            {
                draw_circle(x_left_board+col*70+35,y_top_board-35,color_player,25);
                while(col_mouse_hover(mouse_x,mouse_y)==4 && ok)
                {
                    mouse_x=mousex(), mouse_y=mouse_y;
                    if(ismouseclick(WM_LBUTTONDOWN) && possible_insert_circle(col))
                    {
                        clearmouseclick(WM_LBUTTONDOWN);
                        insert_circle(col, color_player);
                        if(verify_if_win(color_player))
                        {
                            ok=false;
                            draw_circle(x_left_board+col*70+35,y_top_board-35,0,25);
                            print_player_win(color_player,0);
                        }
                        if(color_player==2)
                            color_player=14;
                        else
                            color_player=2;
                        if(ok)
                            draw_circle(x_left_board+col*70+35,y_top_board-35,color_player,25);
                    }
                }
                if(ok)
                    draw_circle(x_left_board+col*70+35,y_top_board-35,0,25);
            }
            else if(col==5)
            {
                draw_circle(x_left_board+col*70+35,y_top_board-35,color_player,25);
                while(col_mouse_hover(mouse_x,mouse_y)==5 && ok)
                {
                    mouse_x=mousex(), mouse_y=mouse_y;
                    if(ismouseclick(WM_LBUTTONDOWN) && possible_insert_circle(col))
                    {
                        clearmouseclick(WM_LBUTTONDOWN);
                        insert_circle(col, color_player);
                        if(verify_if_win(color_player))
                        {
                            ok=false;
                            draw_circle(x_left_board+col*70+35,y_top_board-35,0,25);
                            print_player_win(color_player,0);
                        }
                        if(color_player==2)
                            color_player=14;
                        else
                            color_player=2;
                        if(ok)
                            draw_circle(x_left_board+col*70+35,y_top_board-35,color_player,25);
                    }
                }
                if(ok)
                    draw_circle(x_left_board+col*70+35,y_top_board-35,0,25);
            }
            else if(col==6)
            {
                draw_circle(x_left_board+col*70+35,y_top_board-35,color_player,25);
                while(col_mouse_hover(mouse_x,mouse_y)==6 && ok)
                {
                    mouse_x=mousex(), mouse_y=mouse_y;
                    if(ismouseclick(WM_LBUTTONDOWN) && possible_insert_circle(col))
                    {
                        clearmouseclick(WM_LBUTTONDOWN);
                        insert_circle(col, color_player);
                        if(verify_if_win(color_player))
                        {
                            ok=false;
                            draw_circle(x_left_board+col*70+35,y_top_board-35,0,25);
                            print_player_win(color_player,0);
                        }
                        if(color_player==2)
                            color_player=14;
                        else
                            color_player=2;
                        if(ok)
                            draw_circle(x_left_board+col*70+35,y_top_board-35,color_player,25);
                    }
                }
                if(ok)
                    draw_circle(x_left_board+col*70+35,y_top_board-35,0,25);
            }


            mouse_x=mousex(), mouse_y=mouse_y;
            col=col_mouse_hover(mouse_x,mouse_y);
            clearmouseclick(WM_LBUTTONDOWN);

        }


    }

}
void draw_board ()
{
    setcolor(4);
    setfillstyle(1,9);
    bar(x_left_board,y_top_board,x_right_board,y_bottom_board);
    settextstyle(10,1,8);
    setcolor(12);
    outtextxy(x_left_board-10,y_top_board+400,"CONNECT4");
    setlinestyle(1,1,5);
    draw_circles_in_board(0);
    setcolor(0);
    for( int i=x_left_board; i<x_right_board; i+=70)
        rectangle(i,y_top_board,i+70,y_bottom_board);
    for( int i=y_top_board; i<y_bottom_board; i+=70)
        rectangle(x_left_board,i,x_right_board,i+70);
}
void draw_buttons()
{
    settextjustify(0,0);
    settextstyle(6,0,3);
    setcolor(13);
    outtextxy(10,y_top_board+50,"New Game");
    outtextxy(10,y_top_board+100+textheight("New Game"),"Exit");
}
void delete_all ()
{
    setfillstyle(1,0);
    bar(0,0,800,600);
    for( int i=0; i<6; i++)
        for( int j=0; j<7; j++)
            MATRIX[i][j]=0;
}
void menu()
{
    while(!exit_game)
    {
        newgame=0;
        draw_buttons();
        draw_board();
        draw_hover();
        delete_all();
    }
}
int main()
{
    initwindow(800,600,"Connect4");
    menu();

    closegraph();
    return 0;
}
/*

Name	Value
BLACK	0
BLUE	1
GREEN	2
CYAN	3
RED	4
MAGENTA	5
BROWN	6
LIGHTGRAY	7
DARKGRAY	8
LIGHTBLUE	9
LIGHTGREEN	10
LIGHTCYAN	11
LIGHTRED	12
LIGHTMAGENTA	13
YELLOW	14
WHITE	15
*/
