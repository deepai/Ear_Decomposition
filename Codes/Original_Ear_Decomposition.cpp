
#include <stdio.h>
#include <time.h>
#include <omp.h>
#include <cassert>
#include <iostream>

int len_row,len_column;
int *dfs_visited,*Visited,*row_offset,*column_offset; 

int *parent,*Time,count=1,*value,*Chains; 


void dfs(int v) 
{
	int i,end;
	dfs_visited[v]=1;
	Time[count]=v;
	value[v]=count;
	count++;
	if(v+1<=len_row)
		end=row_offset[v+1];
	else
		end=len_column+1;
	for(i=row_offset[v];i<end;i++)
	{
		if(dfs_visited[column_offset[i]]==0)
		{
			parent[column_offset[i]]=v;
			dfs(column_offset[i]);
		}
	}
}

//int ind=0;
void traverse(int s,int d)
{
	int pointer=s;
	#ifdef VERIFY
		printf("%d ", s); //
	#endif
	//Chains[ind]=s;
	Visited[pointer]=1;
	//ind++;
	pointer=d;
	while(1)
	{
		if (Visited[pointer]==1)
		{
			//Chains[ind]=pointer;
			//ind++;
			#ifdef VERIFY
				printf("%d ", pointer); //
			#endif
			break;
		}
		if (pointer==s)
		{
			//Chains[ind]=pointer;
			//ind++;
			#ifdef VERIFY
				printf("%d ", pointer);//
			#endif
			break;
		}
		Visited[pointer]=1;
		//Chains[ind]=pointer;
		//ind++;
		#ifdef VERIFY
			printf("%d ", pointer);//
		#endif
		pointer=parent[pointer];
	}
	//Chains[ind]=0;
	//ind++;
}
int no_chain=0;
void ear_decomposition()
{
	int i,j,end;
	for(i = 1; i <=len_row; i++)
	{
		if(Time[i]+1<=len_row)
			end=row_offset[Time[i]+1];
		else
			end=len_column+1;
		for(j=row_offset[Time[i]];j<end;j++)
		{
			if (value[Time[i]] < value[column_offset[j]] && Time[i]!=parent[column_offset[j]] )  //The second condition is for tree edges.
			{
				no_chain++;
				traverse(Time[i],column_offset[j]);
				#ifdef VERIFY			
					printf("\n");//
				#endif
			}
		}
	}
}

int main()
{
	scanf("%d",&len_row);
	scanf("%d",&len_column);

	column_offset = new int[len_column + 1];
	dfs_visited = new int[len_row + 1];
	Visited = new int[len_row + 1];
	row_offset = new int[len_row + 1];
	parent = new int[len_row + 1];
	Time = new int[len_row + 1];
	value = new int[len_row + 1];
	Chains = new int[len_column + 1];



	int i;
	for (i = 1; i <=len_row; i++)
	{
		scanf("%d",&row_offset[i]);
		//std::cout << row_offset[i] << " " << i << std::endl;
		assert(row_offset[i] <= len_column);

		dfs_visited[i]=0;
	}
	for (i = 1; i <=len_column; i++)
	{
		scanf("%d",&column_offset[i]);
		//std::cout << column_offset[i] << std::endl;
		assert(column_offset[i] <= len_row);
	}																																																													

	parent[1]=0,value[1]=0,value[0]=0;
	double start_dfs,end_dfs,dfs_time;
	double start_ear,end_ear,ear_time;
	
	start_dfs=omp_get_wtime();
	dfs(1);
	end_dfs=omp_get_wtime();
	dfs_time=end_dfs - start_dfs;
	dfs_time *= 1000;

	start_ear=omp_get_wtime();
	ear_decomposition();
	end_ear=omp_get_wtime();
	ear_time=end_ear - start_ear;
	ear_time *= 1000;
/*		printf("\n**************Original_Ear_Decomposition*****************\n\n");
    	printf("Time taken for Ear Decompostion: %lf seconds\n", ear_time+dfs_time);
		printf("              (i)  DFS Tree: %lf seconds\n", dfs_time);
		//printf("                   row:%d     column_offset:%d\n\n",len_row,len_column );
		printf("              (ii) Traversing: %lf seconds\n", ear_time);

		printf("\n******************************************\n");*/																																						

	#ifndef VERIFY
		printf("%lf,%lf,%lf\n",ear_time+dfs_time,dfs_time,ear_time);
	#endif
    return 0;
}
