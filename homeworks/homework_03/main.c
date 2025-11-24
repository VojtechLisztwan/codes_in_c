#include "drawing.h"


/*colors
0..red
1..green
2..blue
3..white
4..yellow
5..black
*/

typedef enum{
    RED,
    GREEN,
    BLUE,
    WHITE,
    YELLOW,
    BLACK
}Color;

typedef enum{
    RIGHT,
    LEFT,
    DOWN,
    UP
}Direction;

void printLine(int length, Color color, Direction direction);
void printDashedLine(int length, Color color, Direction direction);
void setColor(Color color);
void moveDirection(Direction direction);
void move(Direction direction, int length);
void printStairs(int width_of_stair, int length, Color color);
void printFlower(int width, int height);
void printMeadow(int columns, int rows);
void animatedName();

int main() {
  // Keep this line here
  clear_screen();

  // Load the input - what should be drawn.
  int drawing = 0;
  scanf("%d", &drawing);

    switch (drawing){
    case 0:
        printDashedLine(5,RED, DOWN);
        move_to(5,5);
        printDashedLine(2, BLUE, UP);
        move_to(10,15);
        printDashedLine(12, GREEN, RIGHT);
        break;
    case 1:
        move_to(3,10);
        printStairs(4,4, YELLOW);
        break;
    case 2:
        move_to(5,5);
        printFlower(7,6);
        break;
    case 3:
        printMeadow(4,2);
        break;
    case 4:
        animatedName();
        break;
    default:
        break;
    }



  end_drawing();

  return 0;
}

void printLine(int length, Color color, Direction direction){
    setColor(color);
    for(int i=0;i<length;i++){
        draw_pixel();
        moveDirection(direction);
    }
}

void printDashedLine(int length, Color color, Direction direction){
    setColor(color);
    for(int i=0;i<length;i++){
        draw_pixel();
        moveDirection(direction);
        moveDirection(direction);
    }
}

void setColor(Color color){
    switch (color){
    case RED:
        set_red_color();
        break;
    case GREEN:
        set_green_color();
        break;
    case BLUE:
        set_blue_color();
        break;
    case WHITE:
        set_white_color();
        break;
    case YELLOW:
        set_yellow_color();
        break;
    case BLACK:
        set_black_color();
        break;
    default:
        break;
    }
}

void moveDirection(Direction direction){
    switch (direction){
    case RIGHT:
        move_right();
        break;
    case LEFT:
        move_left();
        break;
    case UP:
        move_up();
        break;
    case DOWN:
        move_down();
        break;
    
    default:
        break;
    }
}

void printStairs(int width_of_stair, int length, Color color){
    setColor(color);
    for(int i=0;i<length;i++){
        printLine(width_of_stair, color, RIGHT);
        move_left();
        printLine(width_of_stair, color, DOWN);
        move_up();
    }
}

void move(Direction direction, int length){
    for(int i=0;i<length;i++){
        moveDirection(direction);
    }
}

void printFlower(int width, int height){
    //minimum dimensions are 3*3
    if(width<3)width=3;
    if(height<3)height=3;


    setColor(RED);
    draw_pixel();
    if(width%2){
        move(RIGHT, width/2);
        draw_pixel();
        move(RIGHT, width/2);
    }else{
        move(RIGHT, width-1);
    }
    draw_pixel();
    move_down();
    move(LEFT, width-1);
    printLine(width,RED, RIGHT);
    move(LEFT, width);
    move(RIGHT, width/2);
    move_down();
    printLine(height-2, GREEN, DOWN);
    if((width%2)==0){
        move_left();
        move(UP,height-2);
        printLine(height-2, GREEN, DOWN);
    }
}


void printMeadow(int columns, int rows){
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            move_to(i*6+1, j*6+1);
            printFlower(5,5);
        }
    }
}
void animatedName(){
    for (int k = 0; k < 30; k++) {
        clear_screen();
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 7; j++) {
                
                move_to(i*2+1, j*8+1+k);
                setColor((j+i)%6);
                printf("UPR");
            }
        }
        animate_ms(30);
    }

    for (int k = 30; k > 0; k--) {
        clear_screen();
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 7; j++) {
                move_to(i*2+1, j*8+1+k);
                setColor((j+i)%6);
                printf("UPR");
            }
        }
        animate_ms(30);
    }

}