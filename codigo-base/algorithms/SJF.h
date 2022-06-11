#ifndef __SHORTEST__JOB__FIRST__
#define __SHORTEST__JOB__FIRST__


#include "./Process.h"
#include "./SortingFunction.h"
#include "./PrintTable.h"


void sjf_calculate_time(Process *p, int len)
{
	int i, j;

	int curr_time = 0;

	int min = 0;



	p[0].completed = TRUE;
	p[0].return_time = p[0].burst;
	p[0].turnaround_time = p[0].burst - p[0].arrive_time;
	p[0].waiting_time = 0;
	
	curr_time = p[0].burst;



	for(i = 1; i < len; i++)
	{

		for (j = 1; j < len; j++)
		{

			if (p[j].completed == TRUE)
				continue;

			else
			{
				min = j;

				break;

			}
		}


		for (j = 1; j < len; j++)
		{

			if ((p[j].completed == FALSE)
					&& (p[j].arrive_time <= curr_time)
						&& (p[j].burst < p[min].burst))
			{
				min = j;

			}
		}

		p[min].waiting_time = curr_time - p[min].arrive_time;

		p[min].completed = TRUE;


		curr_time += p[min].burst;


		p[min].return_time = curr_time;

		p[min].turnaround_time = p[min].return_time - p[min].arrive_time;

	}
}


void sjf_print_gantt_chart(Process *p, int len)
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

		if (p[i].turnaround_time > 9)
			printf("\b");

		printf("%d", p[i].return_time);
	}

	printf("\n");
}


void SJF(Process *p, int len){
	
	int i,j,time = 0;
	Process pAux;
	float total_waiting_time = 0, total_turnaround_time = 0, total_response_time = 0;
	merge_sort_by_arrive_time(p, 0, len-1);
	for(i=0; i<len; i++){           //Loop para pegar o processo com menor burst dentro do time.
		for(j=i; j<len; j++){
			if(p[i].burst > p[j].burst && p[j].arrive_time <= time){   //Checar qual dos processos dentro do tempo tem o burst menor.
				pAux = p[i];
				p[i] = p[j];
				p[j] = pAux;
			}
		}
		time+=p[i].burst;
		if(p[i].arrive_time > time) time = p[i].arrive_time;
	}
	
	
	time = 0;
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
	printf("\tShortest Job First\n\n");
	sjf_print_gantt_chart(p, len);
    printf("\n\tAverage Waiting Time     : %-2.2lf\n", (double)total_waiting_time / (double)len);
    printf("\tAverage Turnaround Time  : %-2.2lf\n", (double)total_turnaround_time / (double)len);
    printf("\tAverage Response Time    : %-2.2lf\n\n", (double)total_response_time / (double)len);

    print_table(p, len);

}

#endif
