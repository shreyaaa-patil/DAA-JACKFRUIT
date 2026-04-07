// tasks :to describe re- weighting edges are non negative 
// why djikstra's cant be applied directly to the graph with negative edges
// to do for reference: augmented graph construction,Bellman-Ford for potentials, re-weighting, and Dijkstra from every vertex
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100
#define INF 999999 // large number used here for infinity to avoid overflow
struct Edge //using structure to represent a directed edge
 {
    int src, dest, weight;
};
//bellmann ford algo to find potentials
//use aug matrix to calculate shortest distance from dummy vertex to all , these become the potentials for re-weighting
bool bellmanFord(int V , int R, struct Edge edges[] , int src , int h[]) {
    //initially we take all the distances from the sources as infinity and then reduce them accordingly
    for(int i=0;i<V;i++) {
        h[i]=INF;
    }
    h[src]=0; //distance from source to itself is 0
    //relaxing all edges V-1 times 
    for(int i=1;i<=V-1;i++) {
        for( int j =0;j<E;j++) {
            int u=edges[j].src;
            int v=edges[j].dest;
            int w=edges[j].weight;
            if(h[u]!=INF && h[u]+w<h[v]) {
                h[v]=h[u]+w;
            }
        }
    }
    //check for negative weight cycles, as in if we can still relax an edge after all this that means there is a negative cycle
    for (int j=0;j<E;j++) {
        int u=edges[j].src;
        int v=edges[j].dest;
        int w=edges[j].weight;
        if(h[u]!=INF && h[u]+w<h[v]) {
            return false; // to detect the negative cycle 
        }
    }
    return true; // if no negative cycle detected

}
//adding utlity function to find vertex with minimum distance
int minDistance (int dist[],bool sptSet[], int V) {
    int min=INF , min_index;
    for (int v=0;v<V;v++) {
        if(sptSet[v]==false && dist[v]<=min){
            min=dist[v];
            min_index=v;
        
        }
    }
    return min_index;
}