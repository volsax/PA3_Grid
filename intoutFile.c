#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "pa3.h"
short r, c; //global r and c
void text_grid(char *filename, GRID **Graph);

GRID **grid_read_from_file(char *filename, char *outfile){
    FILE *fp = NULL;
    int count = 0;
    short fileSize, i, j;
    
    fp = fopen(filename,"rb");
    if (fp == NULL) {
        return NULL;
    }

    //calculate the grid size
    fseek(fp, 0, SEEK_END);    //move to the end of the file
    fileSize = ftell(fp);      //return end postion
    rewind(fp);

    //read row and column from the input file
    fread(&r, sizeof(short), 1, fp);
    fread(&c, sizeof(short), 1, fp);

    //create a 2D array and store the grid in it
    GRID **graph = (GRID**)malloc(r * sizeof(GRID*));
    for(i=0; i<r; i++){
        graph[i] = (GRID*)malloc(c * sizeof(GRID));
    }

    for(i=0; i<r; i++){
        for(j=0; j<c; j++){
            fread(&(graph[i][j].key), sizeof(short), 1, fp);
            graph[i][j].index = count;
            count++;
            //printf("%hd ", grid[i][j]);
        }
    }

    text_grid(outfile, graph);
    fclose(fp);
    return graph;
}

void text_grid(char *filename, GRID **Graph){
    FILE *fp = NULL;

    //open file
    fp = fopen(filename, "w");

    //start writing to text file
    fprintf(fp, "%hd %hd\n", r, c);

    int i, j;
    for(i=0; i<r; i++){
        for(j=0; j<c; j++){
            if(j<c-1){
                fprintf(fp, "%hd ", Graph[i][j].key);
            }
            else{
                fprintf(fp, "%hd", Graph[i][j].key);
            }
        }
        fprintf(fp, "\n");;
    }
    fclose(fp);
}

void shortest_save_to_file(int *shortest, char *filename){
    FILE *fp = NULL;
    fp = fopen(filename, "wb");

    fwrite(&c, sizeof(short), 1, fp);
    fwrite(shortest, sizeof(int), c, fp);
    fclose(fp);
}