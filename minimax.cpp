#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <array>
#include <stack>
#include <vector>
using namespace std;
enum SPOT_STATE {
    EMPTY = 0,
    BLACK = 1,
    WHITE = 2
};
struct node{
    int i;
    int j;
    node(int ii, int jj){
        i = ii;
        j = jj;
    }
};

int x,y;
int entoken,ustoken;
int enfives = 0,enfours = 0, enthrees = 0, entwos = 0;
int usfives = 0,usfours = 0, usthrees = 0, ustwos = 0;
int player;
const int SIZE = 15;
std::array<std::array<int, SIZE>, SIZE> board;
int mark[15][15];
stack<node> newestmark;

void read_board(std::ifstream& fin) {
    fin >> player;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            fin >> board[i][j];
        }
    }
}

void print_board(){

    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 15 ;j++){
            cout << board[i][j] << " ";

        }
        cout << "\n";
    }
    cout << "====================\n";
}
bool checkboard(int i ,int j){
    if(board[i][j] != EMPTY) return 0;

    if(i > 0) {if(board[i-1][j] != EMPTY) return 1;}
    if(i < 14) {if(board[i+1][j] != EMPTY) return 1;}
    if(j > 0) {if(board[i][j-1] != EMPTY) return 1;}
    if(j < 14){if(board[i][j+1] != EMPTY) return 1;}
    if(i > 0 && j > 0){if(board[i-1][j-1] != EMPTY) return 1;}
    if(i > 0 && j < 14){if(board[i-1][j+1] != EMPTY)return 1;}
    if(i < 14 && j < 0){if(board[i+1][j-1] != EMPTY)return 1;}
    if(i < 14 && j < 14){if(board[i+1][j+1] != EMPTY) return 1;}

    return 0;

}


int assign_score(int a , int b){

    int en5 = 0, en4 = 0, en3 = 0 ,en2 = 0;
    int us5 = 0, us4 = 0, us3 = 0, us2 = 0;
   //////== EN 
    //up

    int tempa = a, tempb = b, subcount = 0, count = 1;
    tempa--;
    while(tempa >= 0){
        if(board[tempa][tempb] == entoken){count++;subcount++;}
        else break;
        tempa--;
    }
    if(subcount == 2)en2--;if(subcount == 3)en3--;if(subcount==4)en4--;
    
    //down
    tempa = a; tempb = b; subcount = 0;
    tempa++;
    while(tempa < 15){
        if(board[tempa][tempb] == entoken){count++;subcount++;}
        else break;
        tempa++;
    }
    if(subcount == 2)en2--;if(subcount == 3)en3--;if(subcount==4)en4--;
    if(count == 2)en2++;if(count == 3)en3++;if(count ==4)en4++;if(count==5)en5++;


    // left
    tempa = a; tempb = b; subcount = 0; count = 1;
    tempb--;
    while(tempb >= 0){
        if(board[tempa][tempb] == entoken){count++;subcount++;}
        else break;
        tempb--;
    }
    if(subcount == 2)en2--;if(subcount == 3)en3--;if(subcount==4)en4--;

    //right
    tempa = a; tempb = b; subcount = 0;
    tempb++;
    while(tempb < 15){
        if(board[tempa][tempb] == entoken){count++;subcount++;}
        else break;
        tempb++;
    }
    if(subcount == 2)en2--;if(subcount == 3)en3--;if(subcount==4)en4--;
    if(count == 2)en2++;if(count == 3)en3++;if(count ==4)en4++;if(count==5)en5++;

    //upleft
    tempa = a; tempb = b; subcount = 0; count = 1;
    tempb--;
    tempa--;
    while(tempb >= 0 && tempa >= 0){
        if(board[tempa][tempb] == entoken){count++;subcount++;}
        else break;
        tempb--; tempa--;
    }
    if(subcount == 2)en2--;if(subcount == 3)en3--;if(subcount==4)en4--;
    //downright
    tempa = a; tempb = b; subcount = 0;
    tempb++;
    tempa++;
    while(tempb < 15 && tempa < 15){
        if(board[tempa][tempb] == entoken){count++;subcount++;}
        else break;
        tempb++; tempa++;
    }
    if(subcount == 2)en2--;if(subcount == 3)en3--;if(subcount==4)en4--;
    if(count == 2)en2++;if(count == 3)en3++;if(count ==4)en4++;if(count==5)en5++;

    //upright
    tempa = a; tempb = b; subcount = 0; count = 1;
    tempb++;
    tempa--;
    while(tempb < 15 && tempa >= 0){
        if(board[tempa][tempb] == entoken){count++;subcount++;}
        else break;
        tempb++; tempa--;
    }
    if(subcount == 2)en2--;if(subcount == 3)en3--;if(subcount==4)en4--;
    
    //downleft
    tempa = a; tempb = b; subcount = 0; 
    tempb--;
    tempa++;
    while(tempb >= 0 && tempa < 15){
        if(board[tempa][tempb] == entoken){count++;subcount++;}
        else break;
        tempb--; tempa++;
    }
    if(subcount == 2)en2--;if(subcount == 3)en3--;if(subcount==4)en4--;
    if(count == 2)en2++;if(count == 3)en3++;if(count ==4)en4++;if(count==5)en5++;

    ///US
    /*
    //up

    tempa = a, tempb = b, subcount = 0, count = 1;
    tempa--;
    while(tempa >= 0){
        if(board[tempa][tempb] == ustoken){count++;subcount++;}
        else break;
        tempa--;
    }
    if(subcount == 2)us2--;if(subcount == 3)us3--;if(subcount==4)us4--;
    
    //down
    tempa = a; tempb = b; subcount = 0;
    tempa++;
    while(tempa < 15){
        if(board[tempa][tempb] == ustoken){count++;subcount++;}
        else break;
        tempa++;
    }
    if(subcount == 2)us2--;if(subcount == 3)us3--;if(subcount==4)us4--;
    if(count == 2)us2++;if(count == 3)us3++;if(count ==4)us4++;if(count==5)us5++;


    // left
    tempa = a; tempb = b; subcount = 0; count = 1;
    tempb--;
    while(tempb >= 0){
        if(board[tempa][tempb] == ustoken){count++;subcount++;}
        else break;
        tempb--;
    }
    if(subcount == 2)us2--;if(subcount == 3)us3--;if(subcount==4)us4--;

    //right
    tempa = a; tempb = b; subcount = 0;
    tempb++;
    while(tempb < 15){
        if(board[tempa][tempb] == ustoken){count++;subcount++;}
        else break;
        tempb++;
    }
    if(subcount == 2)us2--;if(subcount == 3)us3--;if(subcount==4)us4--;
    if(count == 2)us2++;if(count == 3)us3++;if(count ==4)us4++;if(count==5)us5++;

    //upleft
    tempa = a; tempb = b; subcount = 0; count = 1;
    tempb--;
    tempa--;
    while(tempb >= 0 && tempa >= 0){
        if(board[tempa][tempb] == ustoken){count++;subcount++;}
        else break;
        tempb--; tempa--;
    }
    if(subcount == 2)us2--;if(subcount == 3)us3--;if(subcount==4)us4--;
    //downright
    tempa = a; tempb = b; subcount = 0;
    tempb++;
    tempa++;
    while(tempb < 15 && tempa < 15){
        if(board[tempa][tempb] == ustoken){count++;subcount++;}
        else break;
        tempb++; tempa++;
    }
    if(subcount == 2)us2--;if(subcount == 3)us3--;if(subcount==4)us4--;
    if(count == 2)us2++;if(count == 3)us3++;if(count ==4)us4++;if(count==5)us5++;

    //upright
    tempa = a; tempb = b; subcount = 0; count = 1;
    tempb++;
    tempa--;
    while(tempb < 15 && tempa >= 0){
        if(board[tempa][tempb] == ustoken){count++;subcount++;}
        else break;
        tempb++; tempa--;
    }
    if(subcount == 2)us2--;if(subcount == 3)us3--;if(subcount==4)us4--;
    
    //downleft
    tempa = a; tempb = b; subcount = 0; 
    tempb--;
    tempa++;
    while(tempb >= 0 && tempa < 15){
        if(board[tempa][tempb] == ustoken){count++;subcount++;}
        else break;
        tempb--; tempa++;
    }
    if(subcount == 2)us2--;if(subcount == 3)us3--;if(subcount==4)us4--;
    if(count == 2)us2++;if(count == 3)us3++;if(count ==4)us4++;if(count==5)us5++;
    */

    enfives += en5; enfours += en4; enthrees += en3; entwos += en2;
    usfives += us5; usfours += us4; usthrees += us3; ustwos += us2;
    int currscore = 0;
    currscore = currscore - (entwos * 3);
    currscore = currscore - (enthrees * 8);
    currscore = currscore - (enfours * 30);
    currscore = currscore - (enfives * 150);
    currscore = currscore + (ustwos * 3);
    currscore = currscore + (usthrees * 8);
    currscore = currscore + (usfours * 30);
    currscore = currscore + (usfives * 3000);

    return currscore;
}
void assign_boardscore(){
    entwos = 0; enthrees = 0; enfours = 0; enfives = 0;
    ustwos = 0; usthrees = 0; usfours = 0; usfives = 0;
    for(int a = 0; a < 15; a++){
            for(int b = 0; b < 15; b++){
                    if(board[a][b] == EMPTY)continue;
                    if(board[a][b] == entoken){
                        //check down, if no up
                        int flag = 1;
                        if(a != 0){
                            if(board[a-1][b] == entoken) flag = 0;
                        }
                        if(flag){
                            int tempa = a;
                            int tempb = b;
                            int count = 1;
                            tempa++;
                            while(true){
                                if(board[tempa][tempb] == entoken){count++; }
                                else break;
                                tempa++;
                                if(tempa == 15)break;
                            }
                            if(count == 2)entwos++;
                            if(count == 3)enthrees++;
                            if(count == 4)enfours++;
                            if(count == 5)enfives++;
                        }
                        //check right, if no left
                        flag = 1;
                        if(b != 0){
                            if(board[a][b-1] == entoken) flag = 0;
                        }
                        if(flag){
                            int tempa = a;
                            int tempb = b;
                            int count = 1;
                            tempb++;
                            while(true){
                                if(board[tempa][tempb] == entoken){count++;}
                                else break;
                                tempb++;
                                if(tempa == 15)break;
                            }
                            if(count == 2)entwos++;
                            if(count == 3)enthrees++;
                            if(count == 4)enfours++;
                            if(count == 5)enfives++;
                        }
                        // check downright, if no upleft
                        flag = 1;
                        if(a != 0 && b!= 0){
                            if(board[a-1][b-1] == entoken) flag = 0;
                        }
                        if(flag){
                            int tempa = a;
                            int tempb = b;
                            int count = 1;
                            tempa++; tempb++;
                            while(true){
                                if(board[tempa][tempb] == entoken){count++;}
                                else break;
                                tempa++; tempb++;
                                if(tempa == 15 || tempb == 15)break;
                            }
                            if(count == 2)entwos++;
                            if(count == 3)enthrees++;
                            if(count == 4)enfours++;
                            if(count == 5)enfives++;
                        }
                        //check downleft, if no upright
                        flag = 1;
                        if(a != 0 && b != 14){
                            if(board[a-1][b+1] == entoken)flag = 0;
                        }
                        if(flag){
                            int tempa = a;
                            int tempb = b;
                            int count = 1;
                            tempa++; tempb--;
                            while(true){
                                if(board[tempa][tempb] == entoken){count++;}
                                else break;
                                tempa++; tempb--;
                                if(tempa == 15 || tempb == 0)break;
                            }
                            if(count == 2)entwos++;
                            if(count == 3)enthrees++;
                            if(count == 4)enfours++;
                            if(count == 5)enfives++;
                        }


                    }
                    if(board[a][b] == ustoken){
                        //check down, if no up
                        int flag = 1;
                        if(a != 0){
                            if(board[a-1][b] == ustoken) flag = 0;
                        }
                        if(flag){
                            int tempa = a;
                            int tempb = b;
                            int count = 1;
                            tempa++;
                            while(true){
                                if(board[tempa][tempb] == ustoken){count++; }
                                else break;
                                tempa++;
                                if(tempa == 15)break;
                            }
                            if(count == 2)ustwos++;
                            if(count == 3)usthrees++;
                            if(count == 4)usfours++;
                            if(count == 5)usfives++;
                        }
                        //check right, if no left
                        flag = 1;
                        if(b != 0){
                            if(board[a][b-1] == ustoken) flag = 0;
                        }
                        if(flag){
                            int tempa = a;
                            int tempb = b;
                            int count = 1;
                            tempb++;
                            while(true){
                                if(board[tempa][tempb] == ustoken){count++;}
                                else break;
                                tempb++;
                                if(tempa == 15)break;
                            }
                            if(count == 2)ustwos++;
                            if(count == 3)usthrees++;
                            if(count == 4)usfours++;
                            if(count == 5)usfives++;
                        }
                        // check downright, if no upleft
                        flag = 1;
                        if(a != 0 && b!= 0){
                            if(board[a-1][b-1] == ustoken) flag = 0;
                        }
                        if(flag){
                            int tempa = a;
                            int tempb = b;
                            int count = 1;
                            tempa++; tempb++;
                            while(true){
                                if(board[tempa][tempb] == ustoken){count++;}
                                else break;
                                tempa++; tempb++;
                                if(tempa == 15 || tempb == 15)break;
                            }
                            if(count == 2)ustwos++;
                            if(count == 3)usthrees++;
                            if(count == 4)usfours++;
                            if(count == 5)usfives++;
                        }
                        //check downleft, if no upright
                        flag = 1;
                        if(a != 0 && b != 14){
                            if(board[a-1][b+1] == ustoken)flag = 0;
                        }
                        if(flag){
                            int tempa = a;
                            int tempb = b;
                            int count = 1;
                            tempa++; tempb--;
                            while(true){
                                if(board[tempa][tempb] == ustoken){count++;}
                                else break;
                                tempa++; tempb--;
                                if(tempa == 15 || tempb == 0)break;
                            }
                            if(count == 2)ustwos++;
                            if(count == 3)usthrees++;
                            if(count == 4)usfours++;
                            if(count == 5)usfives++;
                        }


                    }

                }

            }

}
void markit(){
    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 15;j++){
            mark[i][j] = 0;
        }
    }

    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 15;j++){
            if(board[i][j] != EMPTY){
                if(i > 0 ){if(board[i-1][j] == EMPTY) mark[i-1][j] = 1;}
               // if(i > 1 ){if(board[i-2][j] == EMPTY) mark[i-2][j] = 1;}

                if(i < 14){if(board[i+1][j] == EMPTY) mark[i+1][j] = 1;}
                //if(i < 13){if(board[i+2][j] == EMPTY) mark[i+2][j] = 1;}
                
                if(j > 0){if(board[i][j-1] == EMPTY) mark[i][j-1] = 1;}
                //if(j > 1){if(board[i][j-2] == EMPTY) mark[i][j-2] = 1;}
                
                if(j < 14){if(board[i][j+1] == EMPTY)mark[i][j+1] = 1;}
                //if(j < 13){if(board[i][j+2] == EMPTY)mark[i][j+2] = 1;}
                
                if(i > 0 && j > 0){if(board[i-1][j-1] == EMPTY)mark[i-1][j-1] = 1;}
              //  if(i > 1 && j > 1){if(board[i-2][j-2] == EMPTY)mark[i-2][j-2] = 1;}
                
                if(i > 0 && j < 14){if(board[i-1][j+1] == EMPTY)mark[i-1][j+1] = 1;}
                //if(i > 1 && j < 13){if(board[i-2][j+2] == EMPTY)mark[i-2][j+2] = 1;}

                if(i < 14 && j > 0){if(board[i+1][j-1] == EMPTY)mark[i+1][j-1] = 1;}
                //if(i < 13 && j > 1){if(board[i+2][j-2] == EMPTY)mark[i+2][j-2] = 1;}

                if(i < 14 && j < 14){if(board[i+1][j+1] == EMPTY)mark[i+1][j+1] = 1;}
                //if(i < 13 && j < 13){if(board[i+2][j+2] == EMPTY)mark[i+2][j+2] = 1;}
            }

        }
    }

}
int evaluatei;
int evaluatej;
int minimax(int depth, bool maximize){
    if(depth == 0){
       // cout << evaluatei << " " << evaluatej << "\n";
        int current = assign_score(evaluatei,evaluatej);
        
        return current;
        
    }
    markit();
    if(maximize){
        int value = -2147483647;
        int tempmark[15][15];
        int temppi,temppj;
        for(int i = 0; i < 15;i++){
            for(int j = 0; j < 15;j++){
                tempmark[i][j] = mark[i][j];
            }
        }
        for(int i = 0; i < 15; i++){
            for(int j = 0; j < 15; j++){
                
                if(tempmark[i][j] == 1){
                    board[i][j] = ustoken;
                    
                  //  newestmark.push(node(i,j));
                    int theminimax = minimax(depth - 1,false);
                    board[i][j] = EMPTY;
                    //newestmark.pop();
                    if(theminimax >= value){
                        temppi = i;
                        temppj = j;
                        if(depth == 4){
                        x = i;
                        y = j;
                        }
                        value = theminimax;
                    }
                }


            }
        }
       // cout << "\n";
        //cout << "\ndepth: " << depth << " value: " << value << "\n";
        //cout << "path: " << temppi << " " << temppj << "\n\n";
        return value;

    }else{
        int value = 2147483647;
        int tempmark[15][15];
        int temppi,temppj;
        if(depth == 1) assign_boardscore();
        for(int i = 0; i < 15;i++){
            for(int j = 0; j < 15;j++){
                tempmark[i][j] = mark[i][j];
            }
        }
        for(int i = 0; i < 15; i++){
            for(int j = 0; j < 15 ;j++){
                
                if(tempmark[i][j] == 1){
                    
                    if(depth != 1)board[i][j] = entoken;
                    else{
                        evaluatej = j;
                        evaluatei = i;
                    }
                   // newestmark.push(node(i,j));
                    int theminimax = minimax(depth-1,true);
                    if(depth != 1)board[i][j] = EMPTY;
                    //newestmark.pop();
                    if(theminimax < value){
                         value = theminimax;
                    }
                }
            }

        }
        //cout << "\ndepth: " << depth << " value: " << value << "\n";
        // cout << "path: " << temppi << " " << temppj << "\n\n";
        return value;

    }


}
bool winandthreats(){
    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 15;j++){
            if(mark[i][j] == 0)continue;

            //up down
            int enemcounter =0;
            int prev = -1;
            int counter = 0;
            int itemp = i;
            int jtemp = j;
            itemp --;
            while(itemp >= 0){
                if(board[itemp][jtemp] == ustoken && (prev == -1 || prev == ustoken)){
                    counter++;
                    prev = ustoken;
                }else if(board[itemp][jtemp] == entoken && (prev == -1 || prev == entoken)){
                    enemcounter++;
                    prev = entoken;
                }else break;

                itemp--;
            }
            itemp = i;
            jtemp = j;
            itemp++;
            prev = -1;
            while(itemp < 15){
           
                if(board[itemp][jtemp] == ustoken && (prev == -1 || prev == ustoken)){
                    counter++;
                    prev = ustoken;
                }else if(board[itemp][jtemp] == entoken && (prev == -1 || prev == entoken)){
                    enemcounter++;
                    prev = entoken;
                }else break;
                itemp++;

            }
            if(counter >= 4){
                x = i;
                y = j;
                return 1;
            }
            if(enemcounter >= 4){
                x = i;
                y = j;
                return 1;
            }
            
           //left right 
            counter =0;
            itemp = i;
            enemcounter =0;
            jtemp = j;
            jtemp--;
            prev = -1;
            while(jtemp >= 0){
                if(board[itemp][jtemp] == ustoken && (prev == -1 || prev == ustoken)){
                    counter++;
                    prev = ustoken;
                }else if(board[itemp][jtemp] == entoken && (prev == -1 || prev == entoken)){
                    enemcounter++;
                    prev = entoken;
                }else break;
                jtemp--;
            }
            itemp = i;
            jtemp = j;
            jtemp++;
            prev = -1;
            while(jtemp < 15){
                if(board[itemp][jtemp] == ustoken && (prev == -1 || prev == ustoken)){
                    counter++;
                    prev = ustoken;
                }else if(board[itemp][jtemp] == entoken && (prev == -1 || prev == entoken)){
                    enemcounter++;
                    prev = entoken;
                }else break;
                jtemp++;
            }
             if(counter >= 4){
                x = i;
                y = j;
                return 1;
            }
             
            if(enemcounter >= 4){
                x = i;
                y = j;
                return 1;
            }
            //upleft downright
            enemcounter =0;
            counter =0;
            itemp = i;
            jtemp = j;
            jtemp--;
            itemp--;
            prev = -1;
            while(jtemp >= 0 && itemp >= 0){
                if(board[itemp][jtemp] == ustoken && (prev == -1 || prev == ustoken)){
                    counter++;
                    prev = ustoken;
                }else if(board[itemp][jtemp] == entoken && (prev == -1 || prev == entoken)){
                    enemcounter++;
                    prev = entoken;
                }else break;
                itemp--;
                jtemp--;
            }

            itemp = i;
            jtemp = j;
            jtemp++;
            itemp++;
            prev = -1;
            while(jtemp < 15 && itemp < 15){
                if(board[itemp][jtemp] == ustoken && (prev == -1 || prev == ustoken)){
                    counter++;
                    prev = ustoken;
                }else if(board[itemp][jtemp] == entoken && (prev == -1 || prev == entoken)){
                    enemcounter++;
                    prev = entoken;
                }else break;
                jtemp++;
                itemp++;
            }
             if(counter >= 4){
                x = i;
                y = j;
                return 1;
            }

           
            if(enemcounter >= 4){
                x = i;
                y = j;
                return 1;
            }
            //upright downleft
            enemcounter =0;
            counter =0;
            itemp = i;
            jtemp = j;
            jtemp++;
            itemp--;
            prev = -1;
            while(jtemp < 15 && itemp >= 0){
                if(board[itemp][jtemp] == ustoken && (prev == -1 || prev == ustoken)){
                    counter++;
                    prev = ustoken;
                }else if(board[itemp][jtemp] == entoken && (prev == -1 || prev == entoken)){
                    enemcounter++;
                    prev = entoken;
                }else break;
                jtemp++;
                itemp--;
            }
           
            itemp = i;
            jtemp = j;
            jtemp--;
            itemp++;
            prev = -1;
            while(jtemp >= 0 && itemp < 15){
                if(board[itemp][jtemp] == ustoken && (prev == -1 || prev == ustoken)){
                    counter++;
                    prev = ustoken;
                }else if(board[itemp][jtemp] == entoken && (prev == -1 || prev == entoken)){
                    enemcounter++;
                    prev = entoken;
                }else break;
                jtemp--;
                itemp++;
            }

             if(counter >= 4){
                x = i;
                y = j;
                return 1;
            }
        
            if(enemcounter >= 4){
                x = i;
                y = j;
                return 1;
            }
           

        }

    }
     return 0;

}

void write_valid_spot(std::ofstream& fout) {
    if(player == 1){
        ustoken = 1;
        entoken = 2;
    }else if(player == 2){
        ustoken = 2;
        entoken = 1;

    }
    markit();
    if(winandthreats()){
        fout << x << " " << y << std::endl; 
        fout.flush();
        return;
    };
    minimax(4,true);


    fout << x << " " << y << std::endl;
    //Remember to flush the output to ensure the last action is written to file.
    fout.flush();
      
}

int main(int, char** argv) {
    std::ifstream fin(argv[1]);
    std::ofstream fout(argv[2]);
    read_board(fin);
    write_valid_spot(fout);
    fin.close();
    fout.close();
    return 0;
}
