/****************************************************************************************************/
/*Date:21st August 2016*/
/*Description: 1.Modified Ear Decomposition (with rearrangement of  trivial ears)
			   2.Giving Ear numbers to Trivial Ears wich are left in main CSR after rearrangement.

			   3. row_offset_start[u] and row_offset_end[u] Arrays are starting and ending indices of vertex "u"
			      in column_offset[] Array (which are neighbours of vertx "u")
			   4. new_offset_end[] and column_offset_new[] Arrays are for new (TUF - CSR) 
	
			   5. For checking time comment printf statements in traverse() and Ear_Decomposition
			   6. For checking exact-output comment last line(which prints time)*/
/****************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <queue>
using namespace std;

#define No_nodes 1000000 //Number of Nodes
#define No_edges 100000000 //2*Number of Edges(length of column offset)

int row_offset_start[No_nodes],row_offset_end[No_nodes];
int column_offset[No_edges];

int i,len_row,len_column;
int parent[No_nodes],Time[No_nodes],value[No_nodes],count=1;
int parent_new[No_nodes];
int store_count[No_nodes];

int Chains[No_edges],chain_index=0;
int visited_bfs[No_nodes];
int visited_dfs[No_nodes];
int visited_traverse[No_nodes];
int reverse_offset[No_edges];
/*-----------------------------------------*/
/*******************************************/
int	temp_offset_end[No_nodes],column_offset_new[No_edges];

void Store_Tree_U_Forest_New(int u , int v) /*Creating TUF graph in CSR format*/
{
		column_offset_new[temp_offset_end[u]]=v;
		temp_offset_end[u]++;
		column_offset_new[temp_offset_end[v]]=u;
		temp_offset_end[v]++;
}

void bfs() /*Selecting Tree edges*/
{
	int s=1;
	queue <int> bfs_queue,index_queue;
	int value[No_nodes],count=0;
	bfs_queue.push(s);
	index_queue.push(1);
	value[s]=count;
	count++;
	visited_bfs[s]=1;
	int end;
	parent_new[1]=1;
	while (!bfs_queue.empty())
	{
		int v,w,i,j,end1;
		v = bfs_queue.front();
		int index_u=index_queue.front();
		Time[v]=count;
		count++;
		bfs_queue.pop();
		index_queue.pop();
		for(i=row_offset_start[v];i<row_offset_end[v];i++)
		{
			w=column_offset[i];
			if(visited_bfs[w]==0)
			{
				visited_bfs[w]=1;
				bfs_queue.push(w);
				index_queue.push(i);
				Store_Tree_U_Forest_New(v,w);
						
					column_offset[i]=column_offset[row_offset_end[v]];
					
					column_offset[reverse_offset[i]]=column_offset[row_offset_end[column_offset [i]]];	

					reverse_offset[reverse_offset[row_offset_end[column_offset[i]]]]=reverse_offset[i];
					
					reverse_offset[reverse_offset[i]]=reverse_offset[row_offset_end[column_offset[i]]];
					
					reverse_offset[i]=reverse_offset[row_offset_end[v]];

					reverse_offset[reverse_offset[row_offset_end[v]]]=i;


					row_offset_end[v]--;
					row_offset_end[w]--;



				parent_new[w]=v;
				store_count[v]++;
				store_count[w]++;				
			}
		}
	}
}

int random_edges() /*Selecting log(n)-1 edges from each node*/
{
	int  threshold= log(No_nodes)/log(2);
	srand(time(NULL));
	for(int u = 1; u <= len_row; u++)
	{
		int v;		
		if(threshold < (row_offset_end[u] - row_offset_start[u]))
		{
			while(store_count[u] < threshold)
			{

				store_count[u]++;
				v = row_offset_start[u] + (rand()%( row_offset_end[u] - row_offset_start[u]));
				/*if(v > row_offset_end[u])
					v=row_offset_end[u];*/
				if(u<column_offset[v])
				{
					store_count[u]++;
					store_count[column_offset[v]]++;
					Store_Tree_U_Forest_New(u,column_offset[v]);
				
					column_offset[v]=column_offset[row_offset_end[u]];
					
					column_offset[reverse_offset[v]]=column_offset[row_offset_end[column_offset [v]]];	

					reverse_offset[reverse_offset[row_offset_end[column_offset[v]]]]=reverse_offset[v];
					
					reverse_offset[reverse_offset[v]]=reverse_offset[row_offset_end[column_offset[v]]];
					
					reverse_offset[v]=reverse_offset[row_offset_end[u]];

					reverse_offset[reverse_offset[row_offset_end[u]]]=v;


					row_offset_end[u]--;
					row_offset_end[column_offset[v]]--;
				}
						
			}
		}
		else
		{
			for (v = row_offset_start[u] ; v < row_offset_end[u]; v++)
			{
				if(u<column_offset[v])
				{
					Store_Tree_U_Forest_New(u,column_offset[v]);
					
				column_offset[v]=column_offset[row_offset_end[u]];
					
					column_offset[reverse_offset[v]]=column_offset[row_offset_end[column_offset [v]]];	

					reverse_offset[reverse_offset[row_offset_end[column_offset[v]]]]=reverse_offset[v];
					
					reverse_offset[reverse_offset[v]]=reverse_offset[row_offset_end[column_offset[v]]];
					
					reverse_offset[v]=reverse_offset[row_offset_end[u]];

					reverse_offset[reverse_offset[row_offset_end[u]]]=v;


					row_offset_end[u]--;
					row_offset_end[column_offset[v]]--;
				}
			}		
		}
	}
}

void dfs(int v) /*Making DFS tree on TUF graph*/
{
	
	int i,end;
	visited_dfs[v]=1;
	Time[count]=v;
	value[v]=count;
	count++;
	for(i=row_offset_start[v];i<temp_offset_end[v];i++)
	{
		if(!visited_dfs[column_offset_new[i]])
		{
			parent[column_offset_new[i]]=v;
			dfs(column_offset_new[i]);
		}

	}
}

void traverse(int s,int d) /*Printing All ear's*/
{
	int pointer=s;
//		printf("%d ", s);
	Chains[chain_index]=s;
	visited_traverse[pointer]=1;
	chain_index++;
	pointer=d;
	while(1)
	{
		if (visited_traverse[pointer])
		{
			Chains[chain_index]=pointer;
			chain_index++;
//				printf("%d ", pointer);
			break;
		}
		if (pointer==s )
		{
			Chains[chain_index]=pointer;
			chain_index++;
//				printf("%d ", pointer);
			break;
		}
		visited_traverse[pointer] = 1;
		Chains[chain_index]=pointer;
		chain_index++;
///			printf("%d ", pointer);
		pointer=parent[pointer];
	}
	Chains[chain_index]=0;
	chain_index++;
}

void Ear_Decompostion() /*Selecting non tree edges from TUF to print ear's*/
{
	int i,j,end;
	for(i = 1; i <=len_row; i++)
	{
		for(j=row_offset_start[Time[i]];j<temp_offset_end[Time[i]];j++)
		{
			if (value[Time[i]] < value[column_offset_new[j]] && Time[i]!=parent[column_offset_new[j]] )  //The second condition is for tree edges.
			{
				traverse(Time[i],column_offset_new[j]);			
//				printf("\n");
			}
		}
	}
}

int main()
{
		
		scanf("%d %d",&len_row,&len_column);
		for (i = 1; i <=len_row; i++)
		{
			scanf("%d",&row_offset_start[i]);	
		
			visited_dfs[i]=0;
			visited_bfs[i]=0;
			visited_traverse[i]=0;
			temp_offset_end[i]=row_offset_start[i];
		
		}
		for (i = 1; i <=len_column; i++)
		{
			scanf("%d",&column_offset[i]);
		}
		
		for (i = 1; i <=len_row; i++)
		{
			if(i==len_row)
			{
				row_offset_end[i] = len_column;
			}
			else
			{
				row_offset_end[i]=row_offset_start[i+1]-1;
			}
		}

			 int k=1,it,j;
		    for(i = 1; i <=len_row; i++)
		    {
		        for(j=row_offset_start[i];j<row_offset_end[i];j++)
		        {
		            for(it=row_offset_start[column_offset[j]];it<row_offset_end[column_offset[j]];it++)
		            {
		                if(column_offset[it]==i)
		                    reverse_offset[k]=it;
		            }
		            k++;
		        }
		    }
		

		double start_time,end_time,bfs_time,random_edges_time,dfs_time,ear_decomp_time;
		
		start_time=omp_get_wtime();
		bfs();
		end_time=omp_get_wtime();
		bfs_time= end_time - start_time;


		start_time=omp_get_wtime();
		random_edges();
		end_time=omp_get_wtime();
		random_edges_time = end_time- start_time;

		start_time=omp_get_wtime();
		dfs(1);
		end_time=omp_get_wtime();
		dfs_time=end_time - start_time;

		
		start_time=omp_get_wtime();
		Ear_Decompostion();
		for(i=0;i<len_row;i++)
		{
			for(j=row_offset_start[i];j<row_offset_end[i];j++)
			{
	//			printf("%d %d\n",i,column_offset[j]);			
			}

		}
		end_time=omp_get_wtime();
		ear_decomp_time=end_time- start_time;

		printf("Time for Modified approach Version-2:%lf sec\n",bfs_time + dfs_time + ear_decomp_time );

		
	return 0;


}