/*
LAB 5.c
Jorge Jesus Jurado-Garcia
Purpose to use timers, monitors for real-time events, and write functions

Hardware required:
 *Launchpad with LM34

Modified 01/19/2020 by Jorge Jurado to use MSP432 Register operations
Modified 01/30/2020 by Jorge Jurado to run in Code composer studio
 */

/*  Basic LAB
 */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "msp432.h"
#include "ee1910delay.h"
#include "stdio.h"
#include "ee1910analog.h"
#include "ee1910millis.h"
#include "math.h"
void lights(int bacon, int wait_time);
void player_2(int bacon, int wait_time2);
void score(int p1, int p2);
//PROTOTYPE(s)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//main function being conducted
void main(void){
    printf("Player 1 & Player 2\n");
    ///////////////////////////////////////////////////////////////////////////////
    //variables being used
    int ted = 0;
    static int wait_time= 1000;
    int p1;
    int p2;
    ///////////////////////////////////////////////////////////////////////////////////
    //Start up, activating LED lights from two ports adn button
    P9->DIR |= 0xFF;
    P4->DIR |= 0X03;
    P9->OUT &= ~0XFF;
    P4->OUT &= ~0X03;
    P1->DIR &= ~0x12;
    P1->REN |= 0x12;
    P1->OUT |= 0x12;
    P2->DIR |= 0x03;
    P2->OUT &= ~(0x03);
    //////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////
    while(1){
        static int reaction_time;///for loop player 1
        for(ted=0;ted<=9;ted=ted+1){
            lights(ted, wait_time);               ////function used for player 1
        }
        while((P1->IN & 0x10)!=0){
            if( millis() >= wait_time){
                P2->OUT |= 0x01;
                printf("Button not pressed, too late Player 2 scores\n");
                p2++;
                delay(1000);
                P2->OUT &= ~0x01;
                score(p1,p2);
            break;
            }
        }
        if((P1->IN & 0x10) ==0){
            reaction_time = millis();
            wait_time = 2.0 * reaction_time;
            P4->OUT &= ~0x02;
        }

        ///////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////////
        for(ted=8;ted>0;ted=ted-1){                       ////////for loop player 2
            player_2(ted, wait_time);             //////////function used for player 2
        }

        while( (P1->IN & 0x02)!=0){
            if( millis() >= wait_time){
                P2->OUT |= 0x01;
                /////////////if I just put in the while loop it will disseaper I have to make sure that I define it before hand
                printf("Button not pressed, too late Player 1 scores\n");
                p1++;
                delay(1000);
                P2->OUT &= ~0x01;
                score(p1,p2);
            break;
            }
        }
        if( (P1->IN & 0x02) ==0){
            reaction_time = millis();
            wait_time = reaction_time * 2.0;
            P9->OUT &= ~(0x01);
        }


    }
}
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
//function for this code is for player 1
void lights(int bacon, int wait_time){
    start_timer();
    if( bacon<8 ){
        P9->OUT |= (1<<bacon);                         //this if statement turn on the LED and turns them off
        delay(wait_time);                              //in acending order from port 9
        P9->OUT &= ~(1<<bacon);
        while((P1->IN & 0x10)==0){        //If left button is pushed turn on LED green and print command
            P2->OUT |= 0x02;
            printf("Button pressed to early\n");
            delay(1000);
            P2->OUT &= ~0x02;
            break;
        }
    }
    else{
        if( bacon==8){
            P4->OUT |= 0x01;
            delay(wait_time);
            P4->OUT &= ~(0x01);}

        else{
            P4->OUT |= 0X02;
        }
    }
    reset_timer();
}

////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
//////Function for this code is for player 2
void player_2(int bacon,int wait_time){
    start_timer();
    if( bacon == 8){
        P4->OUT &= ~0x02;
        P4->OUT |= 0x01;
        delay(wait_time);
        P4->OUT &= ~0x01;
    }
    else if( bacon >0){
        P9->OUT |= (1<<bacon);                         //this if statement turn on the LED and turns them off
        delay(wait_time);                              //in acending order from port 9
        P9->OUT &= ~(1<<bacon);
        while( (P1->IN & 0x02)==0){        //If right button is pushed turn on LED green and print command
            P2->OUT |= 0x02;
            printf("Button pressed to early\n");
            delay(1000);
            P2->OUT &= ~0x02;
            break;
        }
    }
    else{
        P4->OUT |= 0X01;
    }
    reset_timer();

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void score(int p1, int p2){
    switch(p1){
    case 0:
        printf("Player 1 score: 0\n");
        break;
    case 1:
        printf("Player 1 score: 15\n");
        break;
    case 2:
        printf("Player 1 score: 30\n");
        break;
    case 3:
        printf("Player 1 score: 45\n");
        printf("Player 1 Wins\n");
        while(1){}
        break;

    }
    switch(p2){
    case 0:
        printf("Player 2 score: 0\n");
        break;
    case 1:
        printf("Player 2 score: 15\n");
        break;
    case 2:
        printf("Player 2 score: 30\n");
        break;
    case 3:
        printf("Player 2 score: 45\n");
        printf("Player 2 wins\n");
        while(1){}
        break;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
