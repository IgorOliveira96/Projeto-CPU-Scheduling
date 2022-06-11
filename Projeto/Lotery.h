#ifndef __Lotery__
#define __Lotery__


#include "./Process.h"
#include "./SortingFunction.h"
#include "./PrintTable.h"
#include <time.h>

void lotery_print_gantt_chart(Process *p, int len) {
    int i, j;
    printf("\t ");
    for (i = 0; i < len; i++)
    {
        for (j = 0; j < p[i].burst; j++)
            printf("--");

        printf(" ");
    }

    printf("\n\t|");


    for (i = 0; i < len; i++)
    {
        for (j = 0; j < p[i].burst - 1; j++)
            printf(" ");

        printf("%s", p[i].id);

        for (j = 0; j < p[i].burst - 1; j++)
            printf(" ");

        printf("|");
    }

    printf("\n\t ");

    for (i = 0; i < len; i++)
    {
        for (j = 0; j < p[i].burst; j++)
            printf("--");

        printf(" ");
    }

    printf("\n\t");


    printf("0");

    for (i = 0; i < len; i++)
    {
        for (j = 0; j < p[i].burst; j++)
            printf("  ");

        if (p[i].return_time > 9)
            printf("\b");

        printf("%d", p[i].return_time);

    }

    printf("\n");
}

void Lotery(Process *p, int len) {
	
	int i,j,k,processTime = 0,minArriveTime=0,tickets=0,sorteado,ticket;
	Process pAux;
	float total_waiting_time = 0, total_turnaround_time = 0, total_response_time = 0;
	merge_sort_by_arrive_time(p, 0, len-1);
	for(i=0; i<len; i++){
		tickets+=p[i].priority;
	}
	for(i=0; i<len; i++){
		for(k=i; k<len; k++){
			if(p[k].arrive_time<minArriveTime) minArriveTime= p[k].arrive_time;
		}
		if(processTime<minArriveTime) processTime = minArriveTime;
		do{
			srand(time(NULL));
			sorteado = rand()%tickets;
			ticket = 0;
			for(j=i; j<len; j++){
				ticket+=p[j].priority;
				if(ticket>sorteado){
					pAux = p[j];
					break;
				}
			}
			
		}while(pAux.arrive_time > processTime);
		p[j]=p[i];
		p[i]=pAux;
		tickets-=p[i].priority;
		processTime+=p[i].burst;
	}
	
	
	processTime = 0;
	for(i=0;i<len;i++){
		if(p[i].arrive_time>processTime) processTime = p[i].arrive_time;	//comando para tratar se não tem processos executando;
		p[i].response_time = processTime - p[i].arrive_time;
		p[i].return_time = processTime+ p[i].burst;
		p[i].waiting_time = processTime -p[i].arrive_time;
		p[i].turnaround_time = processTime+ p[i].burst-p[i].arrive_time;
		p[i].completed = 1;
		total_waiting_time += p[i].waiting_time;
		total_turnaround_time += p[i].turnaround_time;
		total_response_time += p[i].response_time;
		processTime+=p[i].burst;
		
	}
	printf("\tLotery\n\n");
	lotery_print_gantt_chart(p, len);
    printf("\n\tAverage Waiting Time     : %-2.2lf\n", (double)total_waiting_time / (double)len);
    printf("\tAverage Turnaround Time  : %-2.2lf\n", (double)total_turnaround_time / (double)len);
    printf("\tAverage Response Time    : %-2.2lf\n\n", (double)total_response_time / (double)len);

    print_table(p, len);


}

#endif
