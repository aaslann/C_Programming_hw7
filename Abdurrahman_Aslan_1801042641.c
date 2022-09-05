#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#define MAX_SIZE 512
void read_file(int matrix[MAX_SIZE][MAX_SIZE],int *l_value); // This function reads integers from file according to MAX_SIZE
void find_islands(int matrix[MAX_SIZE][MAX_SIZE],int *l_value,int flag); // This function finds the islands first cordinate and it moves to another path vertical or horizontal line.If the flag 0 it finds the number of island write it to file.If the flag 1 it finds the islands cordinates and write them to file.
int main(){   
    int l_value;
    int matrix [MAX_SIZE][MAX_SIZE];
    read_file(matrix,&l_value);
    find_islands(matrix,&l_value,0); // I am reading file two times because when I finding the islands I am converting values to -1 avoiding to infinite loop.Than I am refreshing matrix from file.
    read_file(matrix,&l_value);    
    find_islands(matrix,&l_value,1);
    return 0;
}

void read_file(int matrix[MAX_SIZE][MAX_SIZE],int *l_value){
    FILE *fp = fopen("input.txt","r");
    int input;
    fscanf(fp,"%d",&input);
    *l_value=input;
    for (int i = 0; i < MAX_SIZE; i++){
        for (int j = 0; j < MAX_SIZE; j++){
            fscanf(fp,"%d",&matrix[i][j]);
        }
    }
    fclose(fp);
}
void find_islands(int matrix[MAX_SIZE][MAX_SIZE],int *l_value,int flag){
    int i,j,last_x,last_y,counter =0, island_counter = 1;
    FILE *fp;
    if(flag == 0){
        fp = fopen("output.txt","w");
    }
    else{
        fp = fopen("output.txt","a");
    }
    for(i =0 ;i < MAX_SIZE;i++){
        for(j =0 ; j< MAX_SIZE;j++){
            if(i < MAX_SIZE && j < MAX_SIZE && matrix[i][j] > *l_value){
                if(counter == 0){
                    last_x = i;
                    last_y = j;
                    counter++;
                }
                matrix[i][j] = -1;
                if(j +1  > 0 && j+1 < MAX_SIZE && matrix[i][j+1] > *l_value){
                    continue;
                }
                else if(i+1 > 0 && i+1 < MAX_SIZE && matrix[i+1][j] > *l_value){
                    break;
                }
                else if(j -1 > 0 && j-1 < MAX_SIZE && matrix[i][j-1] > *l_value){
                    j -=2;
                }
                else if(i -1 > 0 && i-1 < MAX_SIZE && matrix[i-1][j] > *l_value){
                    i -= 2;                
                    break;
                }
                else{
                    if (flag == 1){
                        fprintf(fp,"x_cordinate :%d y_ cordinate: %d \t#coordinate of a point which is on island %d\n",last_x,last_y,island_counter);
                    }
                    counter =0;
                    i = last_x;
                    j = last_y;
                    island_counter++;
                }
            }
        }
    }
    if(flag == 0){
        fprintf(fp,"%d\n",island_counter-1);
    }
}