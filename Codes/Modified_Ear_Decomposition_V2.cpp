
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <queue>
using namespace std;

int count_dfs_tree = 1;

int i,len_row,len_column;
int count=1;
int chain_index=0;
int single_len_column=0;

int *row_offset_start;
int *row_offset_end;
int *parent;
int *Time;
int *value;
int *parent_new;
int *store_count;
int *visited_bfs;
int *visited_dfs;
int *visited_traverse;
int *single_row_offset_start;
int *single_row_offset_end;
int	*temp_offset_end;

int *Chains;
int *column_offset;
int *single_column_offset;
int *column_offset_new;

#ifdef STATS
	int T;
	int TUF;
#endif

int threshold_offset = 1;

inline void Store_Tree_U_Forest_New(int u , int v) /*Creating TUF graph in CSR format*/
{
		
		column_offset_new[temp_offset_end[u]]=v;
		temp_offset_end[u]++;
		column_offset_new[temp_offset_end[v]]=u;
		temp_offset_end[v]++;

		#ifdef STATS
			TUF += 2;
		#endif
}

void bfs() /*Selecting Tree edges*/
{
	int s=1;
	queue <int> bfs_queue;
	int count=0;
	bfs_queue.push(s);
	count++;
	visited_bfs[s]=1;
	int end;
	parent_new[1]=1;
	int v,w,i,j,end1,index_u,tmp;
	while (!bfs_queue.empty())
	{
		
		v = bfs_queue.front();
		Time[v]=count;
		count++;
		bfs_queue.pop();
		for(i=row_offset_start[v];i<row_offset_end[v];i++)
		{
			w=column_offset[i];
			//intf("%d %d\n",row_offset_start[v],row_offset_end[v]);
			if(visited_bfs[w]==0)
			{
				#ifdef STATS
					T++;
				#endif
				visited_bfs[w]=1;
				bfs_queue.push(w);
				Store_Tree_U_Forest_New(v,w);
				parent_new[w]=v;
				if(v>w)
					store_count[w]++;
				else
					store_count[v]++;	
							
			}
		}
	}
}
// void dfs_bfs(int s)
// {
// 	Time[s] = count++;
// 	int end = row_offset_end[s];
// 	for(int i=row_offset_start[s];i<end;i++)
// 	{
// 		int w = column_offset[i];
// 		if(visited_bfs[w] == 0)
// 		{
// 			visited_bfs[w] = 1;
// 			Store_Tree_U_Forest_New(s,w);
// 			parent_new[w] = s;
// 			if(s>w)
// 				store_count[w]++;
// 			else
// 				store_count[s]++;
// 			dfs_bfs(w);
// 		}
// 	}
// }

int random_edges() /*Selecting log(n)-1 edges from each node*/
{
	int  threshold = threshold_offset * log(len_row)/log(2);
	srand(time(NULL));
	int v;
	for(int u = 2; u <= len_row; u++)
	{
			
		if(threshold < ((single_row_offset_end[u] - single_row_offset_start[u])-1))
		{
			while(store_count[u] < threshold)
			{
				v = single_row_offset_start[u] + (rand()%(( single_row_offset_end[u] - single_row_offset_start[u] -1)));
				if(parent_new[u]!= single_column_offset[v] && parent_new[single_column_offset[v]] != u)
				{
					store_count[u]++;
					Store_Tree_U_Forest_New(u,single_column_offset[v]);
					single_column_offset[v]=single_column_offset[single_row_offset_end[u]];
					single_row_offset_end[u]--;
				}		
			}
		}
		else
		{
			for (v = single_row_offset_start[u] ; v < single_row_offset_end[u]; v++)
			{
				if(parent_new[u]!=single_column_offset[v] && parent_new[single_column_offset[v]]!=u )
				{
					Store_Tree_U_Forest_New(u,single_column_offset[v]);
				}
			}	
			single_row_offset_end[u]=single_row_offset_start[u];
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
	#ifdef VERIFY
		printf("%d ", s);
	#endif
	//Chains[chain_index]=s;
	visited_traverse[pointer]=1;
	//chain_index++;
	pointer=d;
	while(1)
	{
		if (visited_traverse[pointer])
		{
			//Chains[chain_index]=pointer;
			//chain_index++;
			#ifdef VERIFY
				printf("%d ", pointer);
			#endif
			break;
		}
		if (pointer==s )
		{
			//Chains[chain_index]=pointer;
			//chain_index++;
			#ifdef VERIFY
				printf("%d ", pointer);
			#endif
			break;
		}
		visited_traverse[pointer] = 1;
		//Chains[chain_index]=pointer;
		//chain_index++;
		#ifdef VERIFY
			printf("%d ", pointer);
		#endif
		pointer=parent[pointer];
	}
	//Chains[chain_index]=0;
	//chain_index++;
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
				#ifdef VERIFY
					printf("\n");
				#endif
			}
		}
	}
}

int main()
{
		
		scanf("%d %d",&len_row,&len_column);


		row_offset_start=new int[len_row + 1];
		row_offset_end=new int[len_row + 1];
		parent=new int[len_row + 1];
		Time=new int[len_row + 1];
		value=new int[len_row + 1];
		parent_new=new int[len_row + 1];
		store_count=new int[len_row + 1];
		visited_bfs=new int[len_row + 1];
		visited_dfs=new int[len_row + 1];
		visited_traverse=new int[len_row + 1];
		single_row_offset_start=new int[len_row + 1];
		single_row_offset_end=new int[len_row + 1];
		temp_offset_end=new int[len_row + 1];

		Chains=new int[len_column + 1];
		column_offset=new int[len_column + 1];
		single_column_offset=new int[len_column + 1];
		column_offset_new=new int[len_column + 1];

		
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
				row_offset_end[i]=row_offset_start[i+1]; 
			}

			//intf("%d %d\n",row_offset_start[i],row_offset_end[i]);
		}
		/*Generator Single CSR*/
		int k=1,it,j;
		for(i = 1; i <=len_row; i++)
		{
		    	single_row_offset_start[i]=single_len_column;
		        for(j=row_offset_start[i];j<row_offset_end[i];j++)
		        {
		        	if(column_offset[j]>i)
					{
						//printf("%s\n", );
						single_column_offset[single_len_column]=column_offset[j];
						single_len_column++;
					}
		        }
		        single_row_offset_end[i]=single_len_column;
		}
		/*End of Single CSR*/

		double start_time,end_time,bfs_time,random_edges_time,dfs_time,ear_decomp_time;
		
		visited_bfs[1] = 1;
		parent_new[1] = 1;

		start_time=omp_get_wtime();
		bfs();
		end_time=omp_get_wtime();
		bfs_time= end_time - start_time;
		bfs_time *= 1000;


		start_time=omp_get_wtime();
		random_edges();
		end_time=omp_get_wtime();
		random_edges_time = end_time- start_time;
		random_edges_time *= 1000;

		start_time=omp_get_wtime();
		dfs(1);
		end_time=omp_get_wtime();
		dfs_time=end_time - start_time;
		dfs_time *= 1000;

		
		start_time=omp_get_wtime();
		Ear_Decompostion();

		/*		
		for(i=1;i<=len_row;i++)
		{
			for(j=single_row_offset_start[i];j<single_row_offset_end[i];j++)
			{
				if(parent_new[i]!=single_column_offset[j] && parent_new[single_column_offset[j]]!=i)
				{
					//printf("%d %d\n",i,single_column_offset[j]);			
				}
			}

		}
		*/
		end_time=omp_get_wtime();
		ear_decomp_time=end_time- start_time;
		ear_decomp_time *= 1000;

		#ifndef VERIFY

			#ifndef STATS
			printf("%lf,%lf,%lf,%lf,%lf\n",bfs_time + dfs_time + ear_decomp_time + random_edges_time,
						       bfs_time,
						       dfs_time,
						       ear_decomp_time,
						       random_edges_time);
			#endif

			#ifdef STATS
			printf("%lf,%lf,%lf,%lf,%lf,%d,%d\n",bfs_time + dfs_time + ear_decomp_time + random_edges_time,
						       bfs_time,
						       dfs_time,
						       ear_decomp_time,
						       random_edges_time,
						       T,
						       TUF);
			#endif
		#endif
		
	return 0;


}
