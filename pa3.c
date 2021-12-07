#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>
#include "pa3.h"

int k=1;
void get_shortest_path(int *parent, int j, int *path_idx){
    if(parent[j] == -1){
        return;
    }
    get_shortest_path(parent, parent[j], path_idx);
    
    path_idx[k] = j;
    k++;
}

void path_save_to_file(char *filename, int *idx, int min, GRID **Ingrid){
    FILE *fp = NULL;
    short i, j, g;
    int number = sizeof(idx)/4; //number of the path passing

    fp = fopen(filename, "wb");

    fwrite(&min, sizeof(int), 1, fp);
    fwrite(&k, sizeof(int), 1, fp);

    for(g=0; g<k; g++){ //k is a global variable that is the count of element 
        i = idx[g]/c; //i=index/c
        j = idx[g]%c; //i=index%c due to the 2D matrix property
        fwrite(&i, sizeof(short), 1, fp);
        fwrite(&j, sizeof(short), 1, fp);
        //printf("%d %d\n", i, j);
    }
    fclose(fp);
}

int *adjust_distance(GRID **input, int *dist){
    int size = r*c, i, count=1;

    //adjust the distance from back
    //Just adjust for the last row
    for(i=c; i>0; i--){
        dist[size-count] = dist[size-count] + input[r-1][i-1].key;
        count++;
    }
    return dist;
}

int main(int argc, char *argv[]){
    GRID **ingrid = NULL;
    short **adj_matrix = NULL;
    int minTop, minBottom;
    int i, min = INT_MAX;
    

    //call grid load from file and output text file in the mean time
    ingrid = grid_read_from_file(argv[1], argv[2]);
    if(ingrid == NULL){
        return EXIT_FAILURE;
    } 

    //Find the shortest time
    int size = r*c;
    int *dist = (int *)malloc(size * sizeof(int));
    int *shortest_time = (int *)malloc(c * sizeof(int)); //array to store the time
    int *parent = (int *)malloc(size * sizeof(int)); //array to store the path
    adj_matrix = create_adajency_matrix(ingrid);
    for(i=0; i<c; i++){
        dist = dijkstra(adj_matrix, i, parent, dist);  //put the top row into account
        dist = adjust_distance(ingrid, dist);
        shortest_time[i] = find_fastest(dist); //store the result to array
        if(shortest_time[i] < min) {
            min = shortest_time[i]; //get the shortest path's index
            minTop = i;
        }
        //printf("%d ",shortest_time[i]);
    }
    //printf("\n%d\n", minTop);
    shortest_save_to_file(shortest_time, argv[3]);


    //Find the shortest path
    //we already have minDist that contains the shortest time index
    int *shortest_path_idx = (int *)malloc(size *sizeof(int));
    dist = dijkstra(adj_matrix, minTop, parent, dist); //mindest is the src
    dist = adjust_distance(ingrid, dist);
    
    minBottom = find_bottom(dist);
    shortest_path_idx[0] = minTop;
    //printf("%d ", shortest_path_idx[0]);
    get_shortest_path(parent, minBottom, shortest_path_idx);
    path_save_to_file(argv[4], shortest_path_idx, min, ingrid);

    //free the memory
    for(i=0; i<size; i++){   //free 2D array
        free(adj_matrix[i]);
    }
    for(i=0; i<r; i++){     //free 2D array
        free(ingrid[i]);
    }
    free(shortest_time);
    free(parent);
    free(adj_matrix);
    free(dist);
    free(ingrid);
    free(shortest_path_idx);
    return EXIT_SUCCESS;    
}