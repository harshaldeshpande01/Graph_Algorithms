/*
	Implemented graph DS using adjcency list

	You can have multiple graphs at a time, Each with a unique name.
	Initially there are no graphs, you can create graphs using array of Edges {src, target, weight} which can be modified in main function
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100 										// Define maximum number of vertices in the graph
#define INF 999999      							// Infinity                     
#define GRAPH_NAME 20								// Max graph name length

typedef struct Node 								
{
	int dest, weight;
	struct Node* next;
} Node;												// Element of Adjacency List


typedef struct Graph 
{
    char name[GRAPH_NAME];
	Node* head[N];
	int isVertex[N];
	int isDirected;
	struct Graph *next;
} Graph;                                           // Graph DS


typedef struct Edge 
{
	int src, dest, weight;
} Edge;


Graph *all_graphs_ptr;							   // All graphs are stored in a linklist


Graph* getGraphPtr(char name[])									// Returns ptr of Graph given graph name
{
	Graph *ptr = all_graphs_ptr;

	while(ptr != NULL)
	{
		if(!strcmp(name, ptr->name)) 
		{
			break;
		}
		ptr=ptr->next;
	}

	return ptr;
}

void printGraph(char name[])									// Function to print adjacency list representation of graph
{
	int i;
	Graph *graph = getGraphPtr(name);
	if(graph == NULL)
	{
		printf("\n\tGraph dosen't exist !\n");
	}
	else 
	{
		for (i = 0; i < N; i++)
		{
			if(graph->isVertex[i] == 1)
			{
				Node* ptr = graph->head[i];
				if(ptr == NULL)
				{
					printf("%d -> NULL\t", i);
				}
				else
				{
					while (ptr != NULL)
					{
						printf("%d -> %d (%d)\t", i, ptr->dest, ptr->weight);
						ptr = ptr->next;
					}
					printf("\n");
				}
			}
		}
	}
}


void createUndirectedGraph(Edge edges[], int n)							// Creates undirected graph
{
	char name[GRAPH_NAME];
	printf("\nEnter graph name : ");
	scanf("%s", name);

	unsigned i;

	Graph* graph = (Graph*)malloc(sizeof(Graph));
	strcpy(graph->name, name);
	graph->isDirected = 0;
	for (i = 0; i < N; i++)
	{
		graph->head[i] = NULL;
		graph->isVertex[i] = 0;
	}

	if(all_graphs_ptr == NULL)
	{
		all_graphs_ptr = graph;
		graph->next = NULL;
	}
	else 
	{
		graph->next = all_graphs_ptr->next;
		all_graphs_ptr->next = graph;
	}

	for (i = 0; i < n; i++)
	{
		int src = edges[i].src;
		int dest = edges[i].dest;
		graph->isVertex[src] = 1;
		graph->isVertex[dest] = 1;
		int weight = edges[i].weight;

		// 1. allocate new node of Adjacency List from src to dest

		Node* newNode = (Node*)malloc(sizeof(Node));
		newNode->dest = dest;
		newNode->weight = weight;

		newNode->next = graph->head[src];
		graph->head[src] = newNode;

		// 2. allocate new node of Adjacency List from dest to src

		newNode = (Node*)malloc(sizeof(Node));
		newNode->dest = src;
		newNode->weight = weight;

		newNode->next = graph->head[dest];
		graph->head[dest] = newNode;
	}
	printf("\nGraph created successfully !!\n");
}

void createDirectedGraph(Edge edges[], int n)									// Creates directed graph
{
	char name[GRAPH_NAME];
	printf("\nEnter graph name : ");
	scanf("%s", name);

	unsigned i;

	Graph* graph = (Graph*)malloc(sizeof(Graph));
	strcpy(graph->name, name);
	graph->isDirected = 1;
	for (i = 0; i < N; i++)
	{
		graph->head[i] = NULL;
		graph->isVertex[i] = 0;
	}
	if(all_graphs_ptr == NULL)
	{
		all_graphs_ptr = graph;
		graph->next = NULL;
	}
	else 
	{
		graph->next = all_graphs_ptr->next;
		all_graphs_ptr->next = graph;
	}

	for (i = 0; i < n; i++)
	{
		int src = edges[i].src;
		int dest = edges[i].dest;
		graph->isVertex[src] = 1;
		graph->isVertex[dest] = 1;
		int weight = edges[i].weight;

		Node* newNode = (Node*)malloc(sizeof(Node));
		newNode->dest = dest;
		newNode->weight = weight;
		newNode->next = graph->head[src];

		graph->head[src] = newNode;
	}
	printf("\nGraph created successfully !!\n");
}

void addNode(char name[])												// Adds a node in graph if dosen't already exist												
{
	int v;
	Graph* graph = getGraphPtr(name);
	if(graph == NULL)
	{
		printf("\n\tGraph does not exist !!\n");
	}
	else
	{
		printf("\nEnter vertex number to be added : ");
		scanf("%d", &v);
		if(graph->isVertex[v] == 1)
		{
			printf("\n\tVertex already exists !!\n");
		}
		else
		{
			graph->isVertex[v] = 1;
			printf("\n\tNode added succesfully !!\n");
		}	
	}
}

int deleteLL(Node **head_ref, int key)								// Deletes all edges linked to deleted node
{
    Node* temp = *head_ref, *prev; 
    if (temp != NULL && temp->dest == key) 
    { 
        *head_ref = temp->next;   // Changed head 
        free(temp);               // free old head 
        return 1; 
    } 
    while (temp != NULL && temp->dest != key) 
    { 
        prev = temp; 
        temp = temp->next; 
    } 
    if (temp == NULL) return 0; 
  
    prev->next = temp->next; 
    free(temp);
	return 1; 
}


void deleteNode(char name[])										// Deletes node from graph if present
{
	int v;
	Graph* graph = getGraphPtr(name);
	if(graph == NULL)
	{
		printf("\n\tGraph does not exist !!\n");
	}
	else
	{
		printf("\nEnter vertex number to be deleted : ");
		scanf("%d", &v);
		if(graph->isVertex[v] == 0)
		{
			printf("\n\tVertex dosent exists !!\n");
		}
		else
		{
			Node *ptr = graph->head[v], *temp;
			for(int i=0;i<N;i++)
			{
				if((i != v) && (graph->head[i] != NULL))
				{
					deleteLL(&(graph->head[i]), v);
				}
			}
			while(ptr->next != NULL)
			{
				temp = ptr;
				ptr=ptr->next;
				free(temp);
			}
			free(ptr);
			graph->head[v] = NULL;
			graph->isVertex[v] = 0;

			printf("\n\tNode deleted succesfully !!\n");
		}	
	}
}

void addEdge(char name[])												// Add edge src -> target if dosen't already exits
{
	int src, dest, weight;
	Graph* graph = getGraphPtr(name);
	if(graph == NULL)
	{
		printf("\n\tGraph does not exist !!\n");
	}
	else
	{
		printf("\nEnter src : ");
		scanf("%d", &src);
		printf("Enter dest : ");
		scanf("%d", &dest);
		printf("Edge weight(Enter 1 if unweighted graph) : ");
		scanf("%d", &weight);
		if(graph->isVertex[src] == 0)
		{
			printf("\n\tSource node dosen't exist !!\n");
		}
		else if(graph->isVertex[dest] == 0)
		{
			printf("\n\tDest node dosen't exist !!\n");
		}
		else 
		{
			int exists = 0;
			Node *ptr = graph->head[src];
			while(ptr != NULL)
			{
				if(ptr->dest == dest)
				{
					printf("\n\tEdge already exists !!\n");
					exists = 1;
					break;
				}
				ptr=ptr->next;
			}
			if(exists == 0)
			{
				Node* newNode = (Node*)malloc(sizeof(Node));
				newNode->dest = dest;
				newNode->weight = weight;
				newNode->next = graph->head[src];

				graph->head[src] = newNode;
				printf("\n\tEdge added successfully !!\n");
			}
		}	
	}
}

void deleteEdge(char name[])												// Deletes edge src -> target if exists
{
	int src, dest, weight;
	Graph* graph = getGraphPtr(name);
	if(graph == NULL)
	{
		printf("\n\tGraph does not exist !!\n");
	}
	else
	{
		printf("\nEnter src : ");
		scanf("%d", &src);
		printf("Enter dest : ");
		scanf("%d", &dest);
		if(graph->isVertex[src] == 0)
		{
			printf("\n\tSource node dosen't exist !!\n");
		}
		else if(graph->isVertex[dest] == 0)
		{
			printf("\n\tDest node dosen't exist !!\n");
		}
		else 
		{
			int deleted = deleteLL(&(graph->head[src]), dest);	
			if(deleted == 0)
				printf("\n\tEdge doesn't exist\n");
			else
				printf("\n\tEdge deleted successfully !!\n");
		}	
	}	
}

int visited_dfs[N];

void traverse(Graph* graph, int i)									// Utility function
{
		printf("\n\tVisited Node : %d",i);
		visited_dfs[i] = 1;
		Node *edge;
		edge = graph->head[i];
		while(edge != NULL)
		{
			if(visited_dfs[edge->dest] == 0)
				traverse(graph, edge->dest);
			edge = edge->next;
		}
}

void display_dft(char name[])										// Displays graph using depth first traversal
{
	int i;
	Graph *graph = getGraphPtr(name);
	printf("\nDisplaying depth first traversal : \n");
	for(i=0;i < N ; i++)
		visited_dfs[i] = 0;
	for(i=0;i<N;i++)
	{
		if(graph->isVertex[i] && visited_dfs[i]==0)
			traverse(graph, i);
	}
	printf("\n");
}

typedef struct queue												// For breadth first traversal
{
	int data;
	struct queue *next;
}queue;

queue* createQueueNode(int data)
{
	queue *retval;
	retval = (queue*)malloc(sizeof(queue));
	retval->next = NULL;
	retval->data = data;
	return retval;
}

queue* insert_queue(queue *q ,int data)
{
	queue *current;
	current = q;
	if(q == NULL)
		return createQueueNode(data);
	else
	{
		while(current->next != NULL )
			current = current->next;
		current->next = createQueueNode(data);
		return q;
	}
}

queue* pop_queue(queue *q)
{
	queue *temp;
	temp = q;
	if(q == NULL)
		return q;
	else
	{
		temp = q->next;
		free(q);
		return temp;
	}
}

void display_bft(char name[])											// Displays graph using depth first traversal
{
	Graph *graph = getGraphPtr(name);
	printf("\nDisplaying Bredth first Traversal : \n\n");
	int visited_bft[N];
	int i=0;
	queue *q;
	q = NULL;
	Node* current;
	while(q == NULL)
	{
		if(graph->isVertex[i]== 1 && graph->head[i] != NULL)
			q = insert_queue(q,i);
		i++;
	}
	for(i=0;i<N;i++)
		visited_bft[i] = 0;

	while(q != NULL)
	{
		if(visited_bft[q->data] == 0)
			printf("\n\tVisited node : %d",q->data);
		visited_bft[q->data] = 1;
		current = graph->head[q->data];
		q = pop_queue(q);
		while(current != NULL)
		{
			if(visited_bft[current->dest] == 0 )
			{
				q = insert_queue(q,current->dest);
			}
			current = current->next;
		}
	}
	printf("\n");
}

void topological_sort(char name[])
{
	Graph *graph = getGraphPtr(name);
	printf("\nDisplaying topological sort : \n\n");
	int i, count =0;
	Node *current;
	int num_pred[N];
	//initialising number of predecessors
	for(i = 0; i < N ; i++)
	{
		if(graph->isVertex[i])
			num_pred[i] = 0;
		else
			num_pred[i] = -1;
	}
	//assigning number of predecessors
	for(i = 0; i < N && count < N; i++)
	{
		if(graph->isVertex[i])
		{
			count++;
			current = graph->head[i];
			while(current != NULL)
			{
				num_pred[current->dest]++;
				current = current->next;
			}
		}
	}
	int found=1;			//to check if there exists a node with 0 predecessors
	while(found != 0)
	{
		found = -1;			//-1 means no node remaining
		i = -1;
		while(i < N-1 && (found==-1 || found == 0))		// 0 means found node
		{												//with positive parents
			i++;
			if(num_pred[i]  == 0)
				found = 1;
			else if(num_pred[i] > 0)
				found = 0;
			else if(num_pred[i] == -1 && found != 0)
				found = -1;
		}
		if(found == 0)
			printf("\n\tCycle found & topological sort failed\n");
		else if(found == -1)	//all nodes visited condition
			found = 0;
		else
		{
			printf("\n\tVisited node : %d",i);
			num_pred[i]--;
			current = graph->head[i];
			while(current != NULL)
			{
				num_pred[current->dest]--;
				current = current->next;
			}
		}
	}
	printf("\n");
}

void traverse_is_connected(int arbitary_node ,int A[][N], int visited[]) // Helper function
{
	int i;
	visited[arbitary_node] = 1;
	for(i = 0 ; i<N ; i++)
	{
		if(A[arbitary_node][i] == 1 && visited[i]==0)
			traverse_is_connected(i , A , visited);	
	}
}

void is_connected(char name[])											 // Checks if graph is connected using adjacency matrix
{
	Graph *graph = getGraphPtr(name);
	int visited[N] , visited_reversed[N];
	int A[N][N] , A_T[N][N]; 	// Transpose matrix
	Node* current;
	int arbitary_node , i , j , count;
	//initialization
	for(i=0 ; i <N ; i++)
	{
		for (j = 0; j < N; j++)
		{
			A[i][j] = 0;
			A_T[i][j] = 0;
		}
	}
	for(i=0 ; i<N ; i++)
	{
		if(graph->isVertex[i])
		{
			A[i][i] = 1;
			A_T[i][i] = 1;
			arbitary_node = i;
			visited[i] = 0;
			visited_reversed[i] = 0;
			current = graph->head[i];
			while(current != NULL)
			{
				A_T[current->dest][i] = 1;
				A[i][current->dest] = 1;
				current = current->next;
			}
		}
		else
		{
			visited[i] = -1;
			visited_reversed[i] = -1;
		}
	}
	int found = 0;
	traverse_is_connected(arbitary_node , A , visited);
	traverse_is_connected(arbitary_node , A_T , visited_reversed);
	for(i = 0 ; i<N && found == 0;i++)
	{
		if(visited[i]==0 && visited_reversed[i]==0)
			found = 1;
	}
	if(found == 1)
		printf("\n\tGraph is disconnected !!\n");
	else
		printf("\n\tGraph is connected !!\n");
}

int travere_search_dfs(Graph *graph, int node ,int i)
{
	int result = 0;
	visited_dfs[i] = 1;
	Node *current;
	if(node == i)
		result = 1;
	else
	{
		current = graph->head[i];
		while(result == 0 && current != NULL)
		{
			if(visited_dfs[current->dest] == 0);
				result = travere_search_dfs(graph, node , current->dest);
			current =  current->next;
		}
	}
	return result;
}

int search_dfs(char name[], int node)								// Search graph using depth first search
{
	Graph *graph = getGraphPtr(name);
	int i;
	for(i = 0;i<N ; i++)
		visited_dfs[i] = 0;
	for(i = 0 ; i < N ; i++)
	{
		if(graph->isVertex[i] && visited_dfs[i] == 0)
			 return travere_search_dfs(graph, node , i);
	}
	return 0;
}

int search_bfs(char name[], int node)								// Search graph using breadth first search
{
	Graph *graph = getGraphPtr(name);
	int visited_bft[N] ;
	int i=0;
	queue *q;
	q = NULL;
	Node* current;
	while(q == NULL)
	{
		if(graph->isVertex[i]== 1 && graph->head[i] != NULL)
			q = insert_queue(q,i);
		i++;
	}
	for(i=0;i<N;i++)
		visited_bft[i] = 0;

	int found=0;
	while(q != NULL && found == 0)
	{
		visited_bft[q->data] = 1;
		current = graph->head[q->data];
		q = pop_queue(q);
		while(current != NULL && found == 0)
		{
			if(visited_bft[current->dest] == 0 )
			{
				q = insert_queue(q,current->dest);
				if(current->dest == node)
					found = 1;
			}
			current = current->next;
		}
	}
	return found;
}

int traverse_is_cyclic(Graph *graph, int node ,int came_from , int visited[])
{
	Node *current;
	int result = 0;
	visited[node] = 1;
	current = graph->head[node];
	while(current != NULL && result == 0)
	{
		if(current->dest != came_from)
		{
			if(visited[current->dest] == 1)
				result = 1;
			else
				result = traverse_is_cyclic(graph, current->dest , node , visited);
		}
		current = current->next;
	}
	return result;
}

int is_cyclic(char name[])									
{
	Graph *graph = getGraphPtr(name);
	int node, i, count = 0 , visited[N];
	for(i = 0 ; i < N  ; i++)
	{
		if(graph->isVertex[i] && count == 0)
		{
			count++;
			node = i;
		}
		visited[i] = 0;
	}
	return traverse_is_cyclic(graph, node , -1 , visited);
}

int in_SV(int node , int SV[])
{
	int i , found = 0;
	for(i = 0 ; i<N && found ==0; i++)
	{
		if(SV[i] == node)
			found = 1;
	}
	return found;
}

void display_mst(char name[])										// Prim's algorithm
{
	Graph *graph = getGraphPtr(name);
	int i , count = 0;
	int S[2*(N -1)];   //adding edges in pair
	int cost[N - 1];   //stores cost for each edge
	int SV[N];
	//initialization
	for(i=0;i<N - 1;i++)
	{
		cost[i] = INF;
		S[2*i] = -1;
		S[2*i+1] = -1;
		SV[i+1] = -1;
	}
	//setting arbitary node in SV
	i=0;
	while(count == 0)
	{
		if(graph->isVertex[i])
		{
			count++;
			SV[0] = i;
		}
		i++;
	}
	int pointer_edge=0 , u , v  , pointer_vertex=1;
	int min , flag = 0;
	Node *current;
	while(pointer_edge <= 2*(N - 2) && flag == 0)
	{
		min = INF;
		for(i = 0 ; SV[i] != -1 ; i++)
		{
			current = graph->head[SV[i]];
			while(current != NULL)
			{
				if(!in_SV(current->dest , SV))
				{
					if(current->weight < min)
					{
						u = SV[i];
						v = current->dest;
						min = current->weight;
					}
				}
				current = current->next;
			}
		}
		if(min == INF)
			flag = 1;
		else
		{
			SV[pointer_vertex] = v;
			pointer_vertex++;
			S[pointer_edge] = u;
			S[pointer_edge + 1] = v;
			cost[pointer_edge / 2] = min;
			pointer_edge += 2;
		}
	}
	int total_cost = 0;
	// if(flag == 1)
	// 	printf("\n\nno spanning tree\n\n");
	// else
	// {
		printf("\n\nDisplaying minimum spanning tree\n\n");
		for(i = 0 ; i < N - 1 ; i++)
		{
			if(cost[i] < 999999)
				printf("edge from : %d -> %d \t cost = %d\n",S[2*i] , S[2*i +1] , cost[i]);
		}
		for(i = 0 ; i < N -1 ; i++)
		{
			if(cost[i] < 999999)
				total_cost += cost[i];
		}
		printf("\nMST total cost = %d\n\n",total_cost);
	// }
}

// Structure to represent a min heap node 
struct MinHeapNode 
{ 
	int v; 
	int dist; 
}; 

// Structure to represent a min heap 
struct MinHeap 
{ 
	int size;	
	int capacity; 
	int *pos;	 // This is needed for decreaseKey() 
	struct MinHeapNode **array; 
}; 

struct MinHeapNode* newMinHeapNode(int v, int dist) 
{ 
	struct MinHeapNode* minHeapNode = 
		(struct MinHeapNode*) malloc(sizeof(struct MinHeapNode)); 
	minHeapNode->v = v; 
	minHeapNode->dist = dist; 
	return minHeapNode; 
} 

struct MinHeap* createMinHeap(int capacity) 
{ 
	struct MinHeap* minHeap = 
		(struct MinHeap*) malloc(sizeof(struct MinHeap)); 
	minHeap->pos = (int *)malloc(capacity * sizeof(int)); 
	minHeap->size = 0; 
	minHeap->capacity = capacity; 
	minHeap->array = 
		(struct MinHeapNode**) malloc(capacity * sizeof(struct MinHeapNode*)); 
	return minHeap; 
} 

void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) 
{ 
	struct MinHeapNode* t = *a; 
	*a = *b; 
	*b = t; 
} 

// A standard function to heapify at given idx 
// This function also updates position of nodes when they are swapped. 
// Position is needed for decreaseKey() 
void minHeapify(struct MinHeap* minHeap, int idx) 
{ 
	int smallest, left, right; 
	smallest = idx; 
	left = 2 * idx + 1; 
	right = 2 * idx + 2; 

	if (left < minHeap->size && 
		minHeap->array[left]->dist < minHeap->array[smallest]->dist ) 
	smallest = left; 

	if (right < minHeap->size && 
		minHeap->array[right]->dist < minHeap->array[smallest]->dist ) 
	smallest = right; 

	if (smallest != idx) 
	{ 
		// The nodes to be swapped in min heap 
		struct MinHeapNode *smallestNode = minHeap->array[smallest]; 
		struct MinHeapNode *idxNode = minHeap->array[idx]; 

		// Swap positions 
		minHeap->pos[smallestNode->v] = idx; 
		minHeap->pos[idxNode->v] = smallest; 

		// Swap nodes 
		swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]); 

		minHeapify(minHeap, smallest); 
	} 
} 

int isEmpty(struct MinHeap* minHeap) 
{ 
	return minHeap->size == 0; 
} 

struct MinHeapNode* extractMin(struct MinHeap* minHeap) 
{ 
	if (isEmpty(minHeap)) 
		return NULL; 

	// Store the root node 
	struct MinHeapNode* root = minHeap->array[0]; 

	// Replace root node with last node 
	struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1]; 
	minHeap->array[0] = lastNode; 

	// Update position of last node 
	minHeap->pos[root->v] = minHeap->size-1; 
	minHeap->pos[lastNode->v] = 0; 

	// Reduce heap size and heapify root 
	--minHeap->size; 
	minHeapify(minHeap, 0); 

	return root; 
} 

// Function to decreasy dist value of a given vertex v. This function 
// uses pos[] of min heap to get the current index of node in min heap 
void decreaseKey(struct MinHeap* minHeap, int v, int dist) 
{ 
	// Get the index of v in heap array 
	int i = minHeap->pos[v]; 

	// Get the node and update its dist value 
	minHeap->array[i]->dist = dist; 

	// Travel up while the complete tree is not hepified. 
	// This is a O(Logn) loop 
	while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist) 
	{ 
		// Swap this node with its parent 
		minHeap->pos[minHeap->array[i]->v] = (i-1)/2; 
		minHeap->pos[minHeap->array[(i-1)/2]->v] = i; 
		swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]); 

		// move to parent index 
		i = (i - 1) / 2; 
	} 
} 

int isInMinHeap(struct MinHeap *minHeap, int v) 
{ 
if (minHeap->pos[v] < minHeap->size) 
	return 1; 
return 0; 
} 


void dijkstra(Graph* graph, int src, int target) 							// Display shortest path src ->target
{ 
	int V = N;
	int dist[V];	 // dist values used to pick minimum weight edge in cut 
	int parent[V];

	struct MinHeap* minHeap = createMinHeap(V); 

	// Initialize min heap with all vertices. dist value of all vertices 
	for (int v = 0; v < V; ++v) 
	{ 
		dist[v] = INF; 
		minHeap->array[v] = newMinHeapNode(v, dist[v]); 
		minHeap->pos[v] = v; 
	} 

	// Make dist value of src vertex as 0 so that it is extracted first 
	minHeap->array[src] = newMinHeapNode(src, dist[src]); 
	minHeap->pos[src] = src; 
	dist[src] = 0; 
	decreaseKey(minHeap, src, dist[src]); 

	// Initially size of min heap is equal to V 
	minHeap->size = V; 

	// In the followin loop, min heap contains all nodes 
	// whose shortest distance is not yet finalized. 
	while (!isEmpty(minHeap)) 
	{ 
		// Extract the vertex with minimum distance value 
		struct MinHeapNode* minHeapNode = extractMin(minHeap); 
		int u = minHeapNode->v; // Store the extracted vertex number 
		if(u == target)
			break;

		// Traverse through all adjacent vertices of u (the extracted 
		// vertex) and update their distance values 
		Node* pCrawl = graph->head[u]; 
		while (pCrawl != NULL) 
		{ 
			int v = pCrawl->dest; 

			// If shortest distance to v is not finalized yet, and distance to v 
			// through u is less than its previously calculated distance 
			if (isInMinHeap(minHeap, v) && dist[u] != INF && 
										pCrawl->weight + dist[u] < dist[v]) 
			{ 
				parent[v] = u;
				dist[v] = dist[u] + pCrawl->weight; 

				// update distance value in min heap also 
				decreaseKey(minHeap, v, dist[v]); 
			} 
			pCrawl = pCrawl->next; 
		} 
	} 
	printf("\n%d\t%d\t", src, target);

	if(dist[target] < INF)
	{
		printf("%d\t%d",dist[target], target);
		int i=target;
		while(i != src)
		{
			printf(" -> %d", parent[i]);
			i=parent[i];
		}
		printf("\n\n");
	}
	else
	{
		printf("INF\t");
		printf("Path not found\n\n");
	}
}

typedef struct q_of_q
{
	queue *q;
	struct q_of_q *next;
}q_of_q;

q_of_q* create_q_of_q(queue *q)
{
	q_of_q *result;
	result = (q_of_q*)malloc(sizeof(q_of_q));
	result->q = q;
	result->next = NULL;
	return result;
}

q_of_q *insert_q_of_q(q_of_q *set , queue *q)
{
	q_of_q *temp;
	if(set == NULL)
		return create_q_of_q(q);
	else
	{
		temp = set;
		while(temp->next != NULL)
			temp = temp->next;
		temp->next = create_q_of_q(q);
		return set;
	}
}

q_of_q *pop_q_of_q(q_of_q *set)
{
	q_of_q *temp;
	if(set == NULL)
		return NULL;
	else
	{
		temp = set->next;
		free(set);
		return temp;
	}
}

queue* copy_q(queue *q)
{
	queue *result;
	result = NULL;
	while(q != NULL)
	{
		result = insert_queue(result , q->data);
		q = q->next;
	}
	return result;
}

void display_q(queue *q)
{
	printf("PATH :\t");
	while(q->next != NULL)
	{
		printf("%d->",q->data);
		q = q->next;
	}
	printf("%d\n",q->data);
}

void all_possible_paths(int source , int dest)								// Valid ONLY for DAG
{
	Graph *graph = getGraphPtr("g");
	q_of_q *set;  
	queue *q , *temp , *new_q , *iter;
	Node *current;
	q = NULL;
	set = NULL;
	q = insert_queue(q , source);
	set = insert_q_of_q(set , q);
	while(set != NULL)
	{
		temp = set->q;
		set = pop_q_of_q(set);
		iter = temp;
		while(iter->next != NULL)
			iter = iter->next;
		current = graph->head[iter->data];
		while(current != NULL)
		{
			new_q = copy_q(temp);
			new_q = insert_queue(new_q , current->dest);
			if(current->dest == dest)
				display_q(new_q);
			else
				set = insert_q_of_q(set , new_q);
			current = current->next;
		}
	}
}

int main(void)
{
    all_graphs_ptr = NULL;
	Edge edgesUnweighted[] = 
	{ 
		{ 0, 1, 1 }, { 0, 2, 1 }, { 1, 3, 1 }, { 2, 4, 1 },			
		{ 3, 5, 1 }, { 4, 5, 1 }, { 1, 4, 1 }, {3, 4, 1}
	}; 

	Edge edgesWeighted[] = 
	{ 
		{ 0, 1, 5 }, { 0, 2, 3 }, { 1, 3, 2 }, { 2, 4, 1 },			
		{ 3, 5, 10 }, { 4, 5, 3 }, { 1, 4, 1 }, {3, 4, 7}
	}; 

	// Edge edgesWeighted[] =
	// {
	// 	{ 0, 1, 10 }, {0, 3, 7}, { 1, 2, 1 }, { 2, 3, 4 }, { 3, 4, 2},         // For topolocigal sort + DFS_serach + acyclic
	// 	{ 4, 5, 7 }
	// };
    
	int n, source;
    int choice = 1, ch2, ch3;
	char name[GRAPH_NAME];

    while(choice) 
	{
		printf("\n\t-----------------------------");
        printf("\n\tEnter Choice (Integer only)\n");

		printf("\t-----------------------------\n\n");
		printf(" 0 : Exit\n");
        printf(" 1 : Create directed graph\n");
        printf(" 2 : Create undirected graph\n");
		printf(" 3 : Print graph\n");
		printf(" 4 : Node Operations\n");
		printf(" 5 : Edge Operations\n");
		printf(" 6 : Traverse using DFS\n");
		printf(" 7 : Traverse using BFS\n");
		printf(" 8 : Traverse using Topological sort\n");
		printf(" 9 : Search for a node using DFS\n");
		printf("10 : Search for a node using BFS\n");
		printf("11 : Check if connected?\n");
		printf("12 : Check if Cyclic\n");
		printf("13 : Find MST (minimum spanning tree) of graph\n");
		printf("14 : Shortest Path src->target (Dijkstra's)\n");
		printf("15 : Shortest Path src->all (Dijkstra's)\n");
		printf("16 : All possible paths src->target\n\n");
        printf("\tChoice : ");
        scanf("%d",&choice);

		switch (choice)
		{
			case 0:
				printf("\n\tExiting Program...\n");
				break;
			
			case 1:
				printf("\n\n1 : Weighted graph\n");
				printf("2 : Unweighted graph\n");
				printf("\n\tSelect : ");
				scanf("%d",&ch2);
				// printf("\n\n1 : Default entries\n");
				// printf("2 : Custom entries\n");
				// printf("\n\tSelect : ");
				// scanf("%d",&ch3);
				if(ch2 == 1)
				{
					n = sizeof(edgesWeighted)/sizeof(edgesWeighted[0]);
					createDirectedGraph(edgesWeighted, n);	
				}
				else if(ch2 == 2) 
				{
					n = sizeof(edgesUnweighted)/sizeof(edgesUnweighted[0]);
					createDirectedGraph(edgesUnweighted, n);
				}
				break;
			
			case 2:
				printf("\n\n1 : Weighted graph\n");
				printf("2 : Unweighted graph\n");
				printf("\n\tSelect : ");
				scanf("%d",&ch2);
				// printf("\n\n1 : Default entries\n");
				// printf("2 : Custom entries\n");
				// printf("\n\tSelect : ");
				// scanf("%d",&ch3);
				if(ch2 == 1)
				{
					n = sizeof(edgesWeighted)/sizeof(edgesWeighted[0]);
					createUndirectedGraph(edgesWeighted, n);	
				}
				else if(ch2 == 2) 
				{
					n = sizeof(edgesUnweighted)/sizeof(edgesUnweighted[0]);
					createUndirectedGraph(edgesUnweighted, n);
				}
				break;

			case 3:
				printf("\nEnter graph name : ");
				scanf("%s", name);
				printGraph(name);
				break;

			case 4:
				printf("\n\n1 : Add a Node\n");
				printf("2 : Delete a Node\n");
				printf("\n\tSelect : ");
				scanf("%d",&ch2);
				printf("\nEnter graph name : ");
				scanf("%s", name);
				if(ch2 == 1)
				{
					addNode(name);
				}
				else if(ch2 == 2)
				{
					deleteNode(name);
				}
				break;

			case 5:
				printf("\n\n1 : Add an Edge\n");
				printf("2 : Delete an Edge\n");
				printf("\n\tSelect : ");
				scanf("%d",&ch2);
				printf("\nEnter graph name : ");
				scanf("%s", name);
				if(ch2 == 1)
				{
					addEdge(name);
				}
				else if(ch2 == 2)
				{
					deleteEdge(name);
				}
				break;

			case 6:
				printf("\nEnter graph name : ");
				scanf("%s", name);
				display_dft(name);
				break;

			case 7:
				printf("\nEnter graph name : ");
				scanf("%s", name);
				display_bft(name);
				break;

			case 8:
				printf("\nEnter graph name : ");
				scanf("%s", name);
				if((getGraphPtr(name))->isDirected)
				{
					topological_sort(name);
				}
				else
					printf("\n\tGraph is not directed !!\n");
				break;

			case 9:
				printf("\nEnter graph name : ");
				scanf("%s",name);
				if(getGraphPtr(name) == NULL)
				{
					printf("\nGraph dosen't exist !!\n");
				}
				else
				{
					printf("Enter node to be searched : ");
					scanf("%d",&source);
					if(search_dfs(name, source))
						printf("\nYES, %d is present in the graph\n",source);
					else
						printf("\nNO, %d is not present in the graph\n",source);	
				}
				break;

			case 10:
				printf("\nEnter graph name : ");
				scanf("%s",name);
				if(getGraphPtr(name) == NULL)
				{
					printf("\nGraph dosen't exist !!\n");
				}
				else
				{
					printf("Enter node number to be searched : ");
					scanf("%d",&source);
					if(search_bfs(name, source))
						printf("\nYES, %d is present in the graph\n",source);
					else
						printf("\nNO, %d is not present in the graph\n",source);	
				}
				break;

			case 11:
				printf("\nEnter graph name : ");
				scanf("%s", name);
				is_connected(name);
				break;

			case 12:
				printf("\nEnter graph name : ");
				scanf("%s", name);
				if(getGraphPtr(name)->isDirected)
				{
					topological_sort(name);
					printf("\n\nAs topological sort works, hence graph is NOT cyclic\n");
				}
				else
				{
					if(is_cyclic(name))
						printf("\n\tYES, graph is cyclic");
					else
						printf("\n\tNO, graph is not cyclic");
				}
				break;

			case 13:
				printf("\nEnter graph name : ");
				scanf("%s", name);
				if(!getGraphPtr(name)->isDirected)
					display_mst(name);
				else
					printf("\n\tGraph %s is directed , hence no mst !!",name);
				break;

			case 14:
				printf("\nEnter graph name : ");
				scanf("%s", name);
				Graph *graph = getGraphPtr(name);
				if(graph == NULL)
				{
					printf("\n\tGraph dosen't exist !!\n");
				}
				else
				{
					printf("Enter source vertex : ");
					scanf("%d", &source);
					int target;
					printf("Enter target vertex : ");
					scanf("%d", &target);
					printf("\nSource\tTarget\tCost\tPath\n");
					printf("----------------------------------");
					dijkstra(getGraphPtr(name), source, target);	
				}
				break;
			
			case 15:
				printf("\nEnter graph name : ");
				scanf("%s", name);
				graph = getGraphPtr(name);
				if(graph == NULL)
				{
					printf("\n\tGraph dosen't exist !!\n");
				}
				else
				{
					printf("Enter source vertex : ");
					scanf("%d", &source);
					printf("\nSource\tTarget\tCost\tPath\n");
					printf("----------------------------------");
					for(int i=0;i<N;i++)
					{
						if(graph->isVertex[i])
							dijkstra(graph, source, i);
					}	
				}
				break;

			case 16:
				printf("Enter source vertex : ");
				scanf("%d", &source);
				printf("Enter target vertex : ");
				int targetVertex;
				scanf("%d", &targetVertex);
				printf("\n");
				all_possible_paths(source , targetVertex);
				break;

			default:
				printf("\n\tInvalid Choice");
				break;
		}
	}
	return 0;
}


