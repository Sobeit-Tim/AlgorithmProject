#ifndef PATH_FINDER_H_INCLUDED
#define PATH_FINDER_H_INCLUDED
#include <math.h>
#include "Path.h"
#include "list.h"
#define Large 100000
#define V 26
#define SEAT 20

//extern int map[26][26];
extern List map[26];
extern int timetable[32][26][26][23];

class Path_finder{
public:

	int flight_path[100];
	int flight_date[100];
	int dep_time[3];
	int arr_time[3];

	int shor_path[100];
	int sp_date[100];
	int dist[27];
	int sptSet[V]; // 방문 했는지 체크 하는 int형 배열

	void printPath(Path* p){	 
		printf("flight Path[dep date, seat] : ");
		int j;
		for(j =0; p->flight_path[j]!=-1; j++);
		
		for(int i = 0; i<j; i++){
			printf("%c", p->flight_path[i]+'A');
			if(i != j-1)
				printf("[date:%d|seat:%d]->",p->flight_date[i+1],p->flight_seat[i+1]);
		}
		printf("\n");
		printf("flight_time : %d minutes\n",p->flight_time);
		printf("departure time: %dd, %dh%dm\n", p->dep_time[0],p->dep_time[1],p->dep_time[2]);
	 	printf("arrival time : %dd, %dh%dm\n", p->arr_time[0],p->arr_time[1],p->arr_time[2]);
	}

	Path* get_path(int date, int src, int dst){
	    memset(flight_path,-1,sizeof(flight_path));
		memset(flight_date,-1,sizeof(flight_date));
	    memset(dep_time,0,sizeof(dep_time));
	    memset(arr_time,0,sizeof(arr_time));
	    memset(shor_path,-1,sizeof(shor_path));
		memset(sp_date,-1,sizeof(sp_date));

	    Path *p = new Path;
		memset(p->flight_path,-1,sizeof(p->flight_path));
	    p->flight_time = -1;
	    p->source = src;
	    p->dest = dst;

	    int path_ok = ShortestPath(src, dst, date);
	    if(/*((date+(int)dist[dst]/1440) <32 )&&*/path_ok == 1){
		    p->dep_time[0] = date;
		    p->dep_time[1] = timetable[date][src][flight_path[1]][0];
		    p->dep_time[2] = timetable[date][src][flight_path[1]][1];
		    p->arr_time[0] = date + (int)dist[dst]/1440;
		    p->arr_time[1] = (int)((dist[dst]%1440)/60);
		    p->arr_time[2] = dist[dst]%60;
			p->flight_time = 0;
			int j;
			for(j =0; flight_path[j]!=-1; j++){
		        p->flight_path[j] = flight_path[j];
			}
			for(int i = 1; i<j; i++){
				p->flight_date[i] = flight_date[i];
				for(int k = 1; k<=SEAT; k++){
					if(timetable[flight_date[i]][flight_path[i-1]][flight_path[i]][2+k] == 0){
						timetable[flight_date[i]][flight_path[i-1]][flight_path[i]][2+k] = 1;
						timetable[flight_date[i]][flight_path[i-1]][flight_path[i]][2]++;
						p->flight_seat[i] = k;
						break;
					}
				}

			}
		    for(int i =1; flight_path[i]!=-1;i++){
		        //p->flight_time+=map[flight_path[i]][flight_path[i-1]];
		        p->flight_time+=map[flight_path[i]].find(flight_path[i-1]);
			}
		    printPath(p);
			if(p->arr_time[0] < p->dep_time[0])
                printf("???");
            else{
                if( (p->arr_time[0] == p->dep_time[0])&& (p->arr_time[1] < p->dep_time[1]))
                    printf("????");
                else
                {
                    if((p->arr_time[0] == p->dep_time[0]) && (p->arr_time[1] == p->dep_time[1]) &&(p->arr_time[2] < p->dep_time[2]))
                        printf("?????");
                }
            }

	    }else{
			printf("There is no path between %c and %c\n", src+'A', dst+'A');
		}
	    return p;
	};

	int minDistance(int dist[V], int sptSet[V])
	{
	    int min = Large;
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
			if(stack[Top] != from)
				flight_date[i] = sp_date[stack[Top]];
	        flight_path[i++] = stack[Top];
	    }
	}

	void dijkstra(int src, int date)
	{


	    for (int i = 0; i<V; i++)
	        dist[i] = Large, sptSet[i] = 0;

	    // 초기 조건 설정.
	    dist[src] = 0;

	    // V-1번 루프를 수행한다는 것은 첫 src노드를 제외한 모든 노드들에 접근을 해 계산을 한다는 의미.
	    for (int count = 0; count < V - 1; count++)
	    {
	        // 최단거리 정보를 알고 있는 노드들 중 가장 거리가 짧은 노드의 인덱스를 가져온다.
	        int u = minDistance(dist, sptSet);
	        if(u != -1){

		        // 그래프 상의 모든 노드들을 탐색하며 u 노드의 주변 정보를 갱신한다.
		        for (int v = 0; v < V; v++)
		        {
		            // 1. 아직 처리가 되지 않은 노드이어야 하며 (무한루프 방지)
		            // 2. u-v 간에 edge가 존재하고
		            // 3. src부터 u까지의 경로가 존재하고
		            // 4. 기존의 v노드까지의 최단거리 값보다 새로 계산되는 최단거리가 더 짧을 경우
		            if(!sptSet[v] && dist[u] != Large && map[u].find(v) != -1){
		                int date_1 =date + (int)(dist[u]/1440);
		                if(date_1 > 31){
		                	break;
		                }
		                int dep = timetable[date_1][u][v][0]*60 + timetable[date_1][u][v][1];
		                int total = 0;

						int set_date = date_1;
		                
						if(dep > (dist[u]%1440)){
		                    total = dep - (dist[u]%1440);
		                }
		                else{
		                    if(date_1 == 31)
		                        continue;
		                    else
		                       {
		                           total = (1440 - (dist[u]%1440)) + timetable[date_1+1][u][v][0]*60+timetable[date_1+1][u][v][1];
		                           set_date = date_1+1;
							   }
		                }
						if (timetable[set_date][u][v][2] >= SEAT)
							continue;
		                if ( dist[v] > dist[u] + map[u].find(v) + total)
		                {
		                    // 최단거리를 갱신해준다.
		                    dist[v] = dist[u] + map[u].find(v) +total;
		                    shor_path[v] = u;
							sp_date[v] = set_date;
		                }
		            }

		        }
	        }


	        // 이제 이 노드(u)는 접근할 일이 없다. 플래그를 1로 설정.
	        sptSet[u] = 1;

	        // 현재까지의 최단 거리를 출력해준다.
	        //printSolution(dist, V);
	    }
	    for(int i = 0; i<V; i++){
	    }
	}
	int ShortestPath(int from, int to,int date){
	    for(int i = 0; i< V;i++,dist[i-1] = Large, shor_path[i-1]=-1);
	    dist[from] = 0;
	    dijkstra(from,date);

	    if(dist[to] !=Large)
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
