#ifndef __PA3_H__
#define __PA3_H__

typedef struct _grid{
    short key;
    short index;
}GRID;

extern short r, c;
GRID **grid_read_from_file(char *filename, char *outfile);
short **create_adajency_matrix(GRID **graph);
int *dijkstra(short **grid, int src, int *parent, int *dist);
int find_fastest(int *distance);
void shortest_save_to_file(int *shortest, char *filename);
int find_bottom(int *distance);
#endif