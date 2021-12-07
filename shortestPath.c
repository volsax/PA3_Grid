#include "pa3.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

short **create_adajency_matrix(GRID **graph){
    //create a 2D array for adajency matrix
    int i, j;
    int size = r*c;
    short** adj = (short**)malloc(size * sizeof(short*));
    for(i=0; i<size; i++){
        adj[i] = (short*)malloc(size * sizeof(short));
    }
    //initialize adj matrix
    for(i=0; i<size; i++){
        for(j=0; j<size; j++){
            adj[i][j] = -1;
        }
    }
    //Start making adj matrix
    for(i=0; i<r; i++){
        for(j=0; j<c; j++){
            //case top left
            if(i == 0 && j == 0){
                adj[graph[i][j].index][graph[i][j+1].index] = graph[i][j].key; //right
                adj[graph[i][j].index][graph[i+1][j].index] = graph[i][j].key; //down
            }

            //case top right
            else if(i==0 && j==c-1){
                adj[graph[i][j].index][graph[i+1][j].index] = graph[i][j].key; //down
                adj[graph[i][j].index][graph[i][j-1].index] = graph[i][j].key; //left
            }

            //case button left
            else if(i==r-1 && j==0){
                adj[graph[i][j].index][graph[i-1][j].index] = graph[i][j].key; //up
                adj[graph[i][j].index][graph[i][j+1].index] = graph[i][j].key; //right
            }

            //case button right
            else if(i==r-1 && j==c-1){
                adj[graph[i][j].index][graph[i][j-1].index] = graph[i][j].key; //left
                adj[graph[i][j].index][graph[i-1][j].index] = graph[i][j].key; //up
            }

            //case leftmost
            else if(i!=0 && j==0 && i!=r-1){
                adj[graph[i][j].index][graph[i-1][j].index] = graph[i][j].key; //up
                adj[graph[i][j].index][graph[i][j+1].index] = graph[i][j].key; //right
                adj[graph[i][j].index][graph[i+1][j].index] = graph[i][j].key; //down
            }

            //case upmost
            else if(i==0 && j!=0 && j!=c-1){
                adj[graph[i][j].index][graph[i][j+1].index] = graph[i][j].key; //right
                adj[graph[i][j].index][graph[i+1][j].index] = graph[i][j].key; //down
                adj[graph[i][j].index][graph[i][j-1].index] = graph[i][j].key; //left
            }

            //case rightmost
            else if(j==c-1 && i!=0 && i!=r-1){
                adj[graph[i][j].index][graph[i+1][j].index] = graph[i][j].key; //down
                adj[graph[i][j].index][graph[i][j-1].index] = graph[i][j].key; //left
                adj[graph[i][j].index][graph[i-1][j].index] = graph[i][j].key; //up
            }

            //case buttommost
            else if(i==r-1 && j!=0 && j!=c-1){
                adj[graph[i][j].index][graph[i][j-1].index] = graph[i][j].key; //left
                adj[graph[i][j].index][graph[i-1][j].index] = graph[i][j].key; //up
                adj[graph[i][j].index][graph[i][j+1].index] = graph[i][j].key; //right
            }
            
            //other
            else{
                adj[graph[i][j].index][graph[i][j-1].index] = graph[i][j].key; //left
                adj[graph[i][j].index][graph[i-1][j].index] = graph[i][j].key; //up
                adj[graph[i][j].index][graph[i][j+1].index] = graph[i][j].key; //right
                adj[graph[i][j].index][graph[i+1][j].index] = graph[i][j].key; //down
            }
        }
    }
    return adj; //return the adjency matrix
}

static int min_distance(int *dist, short *sptSet){
    int size = r*c;
    int min = INT_MAX, idx, v;
    for(v=0; v<size; v++){
        if(sptSet[v]==0 && dist[v]<=min){
            min = dist[v];
            idx = v;
        }
    }
    return idx;
}

int *dijkstra(short **grid, int src, int *parent, int *dist){
    //size = vertices of graph
    //create 3 array
    int size = r*c, i=0, count=0, v=0;
    short *sptSet = (short *)malloc(size * sizeof(short));

    //initialize
    for(i=0; i<size; i++){
        parent[src] = -1;
        dist[i] = INT_MAX;
        sptSet[i] = 0;
    }
    dist[src] = 0; //starting point distance is 0

    for(count=0; count<size-1; count++){
        int u = min_distance(dist, sptSet);
        sptSet[u] = 1;
        for(v=0; v<size; v++){
            if(!sptSet[v] && grid[u][v]!=-1 && dist[u]+grid[u][v]<dist[v] && dist[u]!=INT_MAX){
                parent[v] = u;
                dist[v] = dist[u] + grid[u][v];
            }
        }
    }
    free(sptSet);
    return dist;
}

int find_fastest(int *distance){
    int size = r*c;
    int min = INT_MAX, i;
    for(i=size-1; i>size-1-c; i--){
        if(distance[i]<min){
            min = distance[i];
        }
    }
    return min;
}

int find_bottom(int *distance){
    int size = r*c;
    int min = INT_MAX, i, idx;
    for(i=size-1; i>size-1-c; i--){
        if(distance[i]<min){
            min = distance[i];
            idx = i;
        }
    }
    return idx;
}

