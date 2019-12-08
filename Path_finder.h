#ifndef PATH_FINDER_H_INCLUDED
#define PATH_FINDER_H_INCLUDED
#include <math.h>
#include <limits.h>
#include "Path.h"
#define V 26


class Path_finder{
public:

	int map[26][26];
	int timetable[32][26][26][2];
	int flight_path[100];
	int dep_time[3];
	int arr_time[3];
	int shor_path[100];
	int dist[26];
	int sptSet[V]; // �湮 �ߴ��� üũ �ϴ� int�� �迭

	Path_finder(int t[][26][26][2], int m[][26])
    {
        for(int i = 1; i<= 31; i++){
            for(int j = 0; j< 26; j++){
                for(int k = 0; k< 26; k++){
                    timetable[i][j][k][0] = t[i][j][k][0];
                    timetable[i][j][k][1] = t[i][j][k][1];
                }
            }
        }
        for(int j = 0; j< 26; j++){
                for(int k = 0; k< 26; k++){
                    map[j][k] = m[j][k];
                }
            }
    }

	Path* get_path(int date, int src, int dst){
	    memset(flight_path,-1,sizeof(flight_path));
	    memset(dep_time,0,sizeof(dep_time));
	    memset(arr_time,0,sizeof(arr_time));
	    memset(shor_path,-1,sizeof(shor_path));
	
	    Path *p = new Path;
		memset(p->flight_path,-1,sizeof(p->flight_path));
	    p->flight_time = -1;
	    p->source = src;
	    p->dest = dst;
	
	    int path_ok = ShortestPath(map, src, dst, date);
	    if(path_ok == 1){
		    p->dep_time[0] = date;
		    p->dep_time[1] = timetable[date][src][flight_path[1]][0];
		    p->dep_time[2] = timetable[date][src][flight_path[1]][1];
		    p->arr_time[0] = date + (int)dist[dst]/1440;
		    p->arr_time[1] = (int)((dist[dst]%1440)/60);
		    p->arr_time[2] = dist[dst]%60;
			p->flight_time = 0;
			printf("flight Path : ");
		    int j;
			for(j =0; flight_path[j]!=-1; j++)
		        p->flight_path[j] = flight_path[j];
		   	for(int i = 0; i<j; i++){
				printf("%c", p->flight_path[i]+'A');
				if(i != j-1)
					printf("->");
			}
			printf("\n");
		    for(int i =1; flight_path[i]!=-1;i++){
		        p->flight_time+=map[flight_path[i]][flight_path[i-1]];
		    }
		    printf("flight_time : %d\n",p->flight_time);
		    printf("departure time: %dd, %dh%dm\n", p->dep_time[0],p->dep_time[1],p->dep_time[2]);
		    printf("arrival time : %dd, %dh%dm\n", p->arr_time[0],p->arr_time[1],p->arr_time[2]);
	    }else{
			printf("There is no path between %c and %c\n", src+'A', dst+'A');
		}
	    return p;
	};

	int minDistance(int dist[V], int sptSet[V])
	{
	    int min = INT_MAX;
	    int min_index=-1;
	
	    for (int v = 0; v < V; v++)
	    {
	        if (!sptSet[v] && min > dist[v])
	        {
	            min_index = v;
	            min = dist[v];
	        }
	    }
	
	    return min_index;
	}
	void SearchPath(int from,int to){
	    int vertex = to;
	    int stack[V];
	    int Top=0;
	    int i = 0;
	    stack[Top++] = vertex;
	    while(1){
	        vertex = shor_path[vertex];
	        stack[Top++] = vertex;
	        if(vertex == from) break;
	    }
	    while(--Top >=0){
	        flight_path[i++] = stack[Top];
	    }
	}

	void dijkstra(int graph[V][V], int src, int date)
	{
	
	
	    for (int i = 0; i<V; i++)
	        dist[i] = INT_MAX, sptSet[i] = 0;
	
	    // �ʱ� ���� ����.
	    dist[src] = 0;
	
	    // V-1�� ������ �����Ѵٴ� ���� ù src��带 ������ ��� ���鿡 ������ �� ����� �Ѵٴ� �ǹ�.
	    for (int count = 0; count < V - 1; count++)
	    {
	        // �ִܰŸ� ������ �˰� �ִ� ���� �� ���� �Ÿ��� ª�� ����� �ε����� �����´�.
	        int u = minDistance(dist, sptSet);
	        if(u != -1){
	
		        // �׷��� ���� ��� ������ Ž���ϸ� u ����� �ֺ� ������ �����Ѵ�.
		        for (int v = 0; v < V; v++)
		        {
		            // 1. ���� ó���� ���� ���� ����̾�� �ϸ� (���ѷ��� ����)
		            // 2. u-v ���� edge�� �����ϰ�
		            // 3. src���� u������ ��ΰ� �����ϰ�
		            // 4. ������ v�������� �ִܰŸ� ������ ���� ���Ǵ� �ִܰŸ��� �� ª�� ���
		            if(dist[u] != INT_MAX && graph[u][v]!=0){
		                int date_1 =date + (int)(dist[u]/1440);
		                if(date_1 > 31){
		                	continue;
		                }
		                int dep = timetable[date_1][u][v][0]*60 + timetable[date_1][u][v][1];
		                int total = 0;
		                if(dep > dist[u]%1440){
		                    total = dep - (dist[u]%1440);
		                }
		                else{
		                    if(date_1 == 31)
		                        continue;
		                    else
		                       {
		                           total = (1440 - (dist[u]%1440)) + timetable[date_1+1][u][v][0]*60+timetable[date_1+1][u][v][1];
		                       }
		                }
		
		                if (!sptSet[v] && dist[v] > dist[u] + graph[u][v] + total)
		                {
		                    // �ִܰŸ��� �������ش�.
		                    dist[v] = dist[u] + graph[u][v]+total;
		                    shor_path[v] = u;
		                }
		            }
		
		        }
	        }
	
	
	        // ���� �� ���(u)�� ������ ���� ����. �÷��׸� 1�� ����.
	        sptSet[u] = 1;
	
	        // ��������� �ִ� �Ÿ��� ������ش�.
	        //printSolution(dist, V);
	    }
	}
	int ShortestPath(int graph[V][V], int from, int to,int date){
	    for(int i = 0; i< V;i++,dist[i-1] = INT_MAX, shor_path[i-1]=-1);
	    dist[from] = 0;
	    dijkstra(graph,from,date);
	
	    if(dist[to] !=INT_MAX)
	    {
	        SearchPath(from, to);
	        return 1;
	    }
	    else{
	        return 0;
	    }
	}
};


#endif // PATH_FINDER_H_INCLUDED
