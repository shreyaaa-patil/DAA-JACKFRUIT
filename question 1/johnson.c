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
bool bellmanFord(int V , int E, struct Edge edges[] , int src , int h[]) {
    //initially we take all the distances from the sources as infinity and then reduce them accordingly
    for(int i=0;i<V;i++) {
        h[i]=INF;
    }
    h[src]=0; //distance from source to itself is 0
    //relaxing all edges V-1 times 
    for(int i=0;i<V-1;i++) {
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
    int min=INF , min_index=-1;
    for (int v=0;v<V;v++) {
        if(sptSet[v]==false && dist[v]<min){
            min=dist[v];
            min_index=v;
        
        }
    }
    return min_index;
}

//djikstra's algo to find shortest path 
void djikstra(int V, int graph[MAX_VERTICES][MAX_VERTICES],int src, int dist[]){ //initialized graph to hold max value at first
    bool sptSet[MAX_VERTICES]; // to keep track of the vertices going to the shortest path tree set
    //initially all distances are inf and then reduced to a constant value and sptSet[] is false
    for(int i=0;i<V;i++) {
        dist[i]=INF;
        sptSet[i]=false;
    }
dist[src]=0; //distance from source to itself is 0
//to find shortest path for all the vertices
for(int count=0;count<V-1;count++) {
    int u=minDistance(dist,sptSet,V);
    //if u is -1 then all remaining vertices are unreachable
    if(u==-1) break;
    sptSet[u]=true; // this is to add the vertex to the shortest path tree set
    //updating the dis calue of the adj vertices
    for(int v=0;v<V;v++) {
        if(!sptSet[v]&& graph[u][v]!=INF && dist[u]!=INF && dist[u]+graph[u][v]<dist[v]) {
            dist[v]=dist[u]+graph[u][v];
        }
    }
}
}
//johnson's algorithm to find all pairs shortest path
void johnsonAlgorithm(int V,int E, struct Edge edges[]) {
    //augmenting the graph by adding a dummy vertex and connecting it to all other vertices with 0 weight edges
    int augmentedV=V+1;
    int augmentedE=E+V;
    struct Edge augmentedEdges[MAX_VERTICES*MAX_VERTICES];
    //copying the original edges to the augmented graph
    for(int i=0;i<E;i++){
        augmentedEdges[i]=edges[i];
    }
    //adding edges from dummy vertex V to all other vertices (0 to V-1)
    for (int i=0;i<V;i++){
        augmentedEdges[E+i].src=V; //dummy vertex
        augmentedEdges[E+i].dest=i; //connecting to all other vertices
        augmentedEdges[E+i].weight=0; //weight of these edges is 0
    }
    //running bellmanford from dummy vertex to get potentials
    int h[MAX_VERTICES]; //to store the potentials
    if(!bellmanFord(augmentedV, augmentedE,augmentedEdges,V,h)){
        printf("graph contains a negative cycle . johnson's algo cannot proceed further\n");
        return;
    }
    //reweighting the original edges
    int reweightedGraph[MAX_VERTICES][MAX_VERTICES];
    for(int i=0;i<V;i++){
        for(int j=0;j<V;j++){
            reweightedGraph[i][j]=INF; //initially all edges are set to inf as usual
        }
    }
    //applying re weighting formula
    for(int i=0;i<E;i++){
        int u=edges[i].src;
        int v=edges[i].dest;
        int w=edges[i].weight;
        reweightedGraph[u][v]=w+h[u]-h[v]; //reweighting the edge weight
    }
    //similarly running it for djikstra's algo from every original vertex
    int finalDistances[MAX_VERTICES][MAX_VERTICES];
    for(int u=0;u<V;u++){
        int dist[MAX_VERTICES];
        djikstra(V,reweightedGraph,u,dist);
        //undoing the re weighting 
        for(int v=0;v<V;v++){
            if(dist[v]!=INF) {
                finalDistances[u][v]=dist[v]+h[v]-h[u]; //undoing the reweighting to get the original distances
            } else {
                finalDistances[u][v]=INF; //if unreachable
            }
        } 
    }
    //printing the final all pairs shortest path matrix
    printf("all pairs shortest path matrix:\n");
    for(int i=0;i<V;i++){
        for(int j=0;j<V;j++){
            if(finalDistances[i][j]==INF) {
                printf("INF\t");
            } else {
                printf("%d\t",finalDistances[i][j]);
            }
        }
        printf("\n");
    }
}
//final driver code:
int main()
{
    //testcase 1: simple graph with negative edges but no negative cycles
    int V=4;
    int E=5;
    struct Edge edges[]={
        {0, 1, -1},
        {0, 3, 4},
        {1, 2, 3},
        {2, 3, 2},
        {1, 3, 2}
    };
    johnsonAlgorithm(V,E,edges); 
    //testcase 2: graph with negative edges
    int V2 = 4;
    int E2 = 5;
    struct Edge edges2[] = {
        {0, 1, 1}, 
        {0, 2, 4}, 
        {1, 2, 2}, 
        {2, 3, 2}, 
        {1, 3, -3} // Negative edge
    };
    johnsonAlgorithm(V2, E2, edges2);
    // testcase 3: graph with a negative cycle to test the detection mechanism of the algorithm
    // This test case will purposefully trigger the Bellman-Ford negative cycle warning
    // The cycle 0 -> 1 -> 2 -> 0 has a total weight of 1 - 5 + 2 = -2
    int V3 = 3;
    int E3 = 3;
    struct Edge edges3[] = {
        {0, 1, 1}, 
        {1, 2, -5}, 
        {2, 0, 2} 
    };
    johnsonAlgorithm(V3, E3, edges3);
    return 0;

}

 