#ifndef __FIRST__COME__FIRST__SERVED__
#define __FIRST__COME__FIRST__SERVED__


#include "./Process.h"
#include "./SortingFunction.h"
#include "./PrintTable.h"


void fcfs_print_gantt_chart(Process *p, int len)
{
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
int Pertence(int * pO,int len, int i){
	int j;
	for(j=0;j<=len;j++){
		printf("erro\n");
		if(pO[j]==i)
			return 1;
	}
	printf("acerto\n");
	return 0;
}

void FCFS(Process *p, int len)
{
	int i,time = 0;
	float total_waiting_time = 0, total_turnaround_time = 0, total_response_time = 0;
	merge_sort_by_arrive_time(p, 0, len-1);
	
	for(i=0;i<len;i++){
		if(p[i].arrive_time>time) time = p[i].arrive_time;	//comando para tratar se não tem processos executando;
		p[i].response_time = time - p[i].arrive_time;
		p[i].return_time = time+ p[i].burst;
		p[i].waiting_time = time -p[i].arrive_time;
		p[i].turnaround_time = time+ p[i].burst-p[i].arrive_time;
		p[i].completed = 1;
		total_waiting_time += p[i].waiting_time;
		total_turnaround_time += p[i].turnaround_time;
		total_response_time += p[i].response_time;
		time+=p[i].burst;
		
	}
	printf("\tFirst Come First Served\n\n");
	fcfs_print_gantt_chart(p, len);
    printf("\n\tAverage Waiting Time     : %-2.2lf\n", (double)total_waiting_time / (double)len);
    printf("\tAverage Turnaround Time  : %-2.2lf\n", (double)total_turnaround_time / (double)len);
    printf("\tAverage Response Time    : %-2.2lf\n\n", (double)total_response_time / (double)len);

    print_table(p, len);
	
	
}


#endif
