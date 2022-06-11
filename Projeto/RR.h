#ifndef __Round__ROBIN__
#define __Round__ROBIN__


#include "./Process.h"
#include "./SortingFunction.h"
#include "./PrintTable.h"


void rr_calculate_waiting_time(Process *p, int len, Quantum q)
{
	int i;

	int curr_time = 0;



	int *remain_burst_time = (int *)malloc(sizeof(int) * len);

	int *calc_response_time = (int *)malloc(sizeof(int) * len);


	for (i = 0; i < len; i++)
	{
		remain_burst_time[i] = p[i].burst;

		calc_response_time[i] = FALSE;

	}


	while (TRUE)
	{
		int check = TRUE;


		for (i = 0; i < len; i++)
		{

			if (remain_burst_time[i] > 0)
			{
				check = FALSE;

				if (calc_response_time[i] == FALSE)
				{
					p[i].response_time = curr_time - p[i].arrive_time;

					calc_response_time[i] = TRUE;

				}


				if (remain_burst_time[i] > q)
				{
					curr_time += q;

					remain_burst_time[i] -= q;

				}


				else
				{
					curr_time += remain_burst_time[i];

					p[i].waiting_time = curr_time - p[i].burst;

					remain_burst_time[i] = 0;

				}
			}
		}


		if (check == TRUE)
			break;

	}

	free(remain_burst_time);

}


void rr_calculate_turnaround_time(Process *p, int len)
{
	int i;



	for (i = 0; i < len; i++)
		p[i].turnaround_time = p[i].burst + p[i].waiting_time - p[i].arrive_time;

}


void rr_print_gantt_chart(Process *p, int len, Quantum q)
{
	int i, j;

	int curr_time = 0, total_burst_time = 0;

	int temp_total_burst_time = 0;


	int *remain_burst_time = (int *)malloc(sizeof(int) * len);


	for (i = 0; i < len; i++)
	{
		remain_burst_time[i] = p[i].burst;

		total_burst_time += p[i].burst;

	}

	printf("\t");


	while (TRUE)
	{
		int check = TRUE;

		for (i = 0; i < len; i++)
		{
			if (remain_burst_time[i] > 0)
			{
				check = FALSE;

				if (remain_burst_time[i] < q)
				{
					printf(" ");
					for (j = 0; j < remain_burst_time[i]; j++)
						printf("--");
				}

				else
				{
					printf(" ");
					for (j = 0; j <= q; j++)
						printf("--");
				}

				if (remain_burst_time[i] > q)
				{
					curr_time += q;
					remain_burst_time[i] -= q;
				}

				else
				{
					curr_time += remain_burst_time[i];
					p[i].waiting_time = curr_time - p[i].burst;
					remain_burst_time[i] = 0;
				}


			}
		}

		if (check == TRUE)
			break;
	}

	printf(" \n\t");

	for (i = 0; i < len; i++)
	{
		remain_burst_time[i] = p[i].burst;
	}


	while (TRUE)
	{
		int check = TRUE;

		for (i = 0; i < len; i++)
		{
			if (remain_burst_time[i] > 0)
			{
				check = FALSE;

				if (remain_burst_time[i] < q)
				{
					printf("|");

					if (remain_burst_time[i] != 1)
					{
						for (j = 0; j <= remain_burst_time[i] / 2; j++)
							printf(" ");

						printf("%2s", p[i].id);

						for (j = 0; j <= remain_burst_time[i] / 2; j++)
							printf(" ");
					}

					else
						printf("%2s", p[i].id);
				}

				else
				{
					printf("|");

					for (j = 0; j < q; j++)
						printf(" ");

					printf("%2s", p[i].id);

					for (j = 0; j < q; j++)
						printf(" ");
				}

				if (remain_burst_time[i] > q)
				{
					curr_time += q;
					remain_burst_time[i] -= q;
				}

				else
				{
					curr_time += remain_burst_time[i];
					p[i].waiting_time = curr_time - p[i].burst;
					remain_burst_time[i] = 0;
				}


			}
		}

		if (check == TRUE)
			break;
	}

	printf("|\n\t");

	for (i = 0; i < len; i++)
	{
		remain_burst_time[i] = p[i].burst;
	}


	while (TRUE)
	{
		int check = TRUE;

		for (i = 0; i < len; i++)
		{
			if (remain_burst_time[i] > 0)
			{
				check = FALSE;

				if (remain_burst_time[i] < q)
				{
					printf(" ");
					for (j = 0; j < remain_burst_time[i]; j++)
						printf("--");
				}

				else
				{
					printf(" ");
					for (j = 0; j <= q; j++)
						printf("--");
				}

				if (remain_burst_time[i] > q)
				{
					curr_time += q;
					remain_burst_time[i] -= q;
				}

				else
				{
					curr_time += remain_burst_time[i];
					p[i].waiting_time = curr_time - p[i].burst;
					remain_burst_time[i] = 0;
				}


			}
		}

		if (check == TRUE)
			break;
	}

	printf("\n\t");

	for (i = 0; i < len; i++)
		remain_burst_time[i] = p[i].burst;

	curr_time = 0;


	while (TRUE)
	{
		int check = TRUE;

		for (i = 0; i < len; i++)
		{
			if (remain_burst_time[i] > 0)
			{
				check = FALSE;

				if (remain_burst_time[i] < q)
				{
					printf("%-2d", curr_time);

					for (j = 0; j < remain_burst_time[i] - 1; j++)
						printf("  ");

					printf(" ");
				}

				else
				{
					printf("%-2d", curr_time);

					for (j = 0; j < q; j++)
						printf("  ");

					printf(" ");
				}

				if (remain_burst_time[i] > q)
				{
					curr_time += q;
					remain_burst_time[i] -= q;
				}

				else
				{
					curr_time += remain_burst_time[i];
					p[i].waiting_time = curr_time - p[i].burst;
					remain_burst_time[i] = 0;
				}
			}
		}

		if (check == TRUE)
			break;
	}

	printf("%-3d\n", total_burst_time);

	printf("\n");

	free(remain_burst_time);

}


void RR(Process *p, int len, Quantum quantum) {
    
	int i,j,time = 1,exec=0,newPLen=1;
	Process * newP;
	float total_waiting_time = 0, total_turnaround_time = 0, total_response_time = 0;
	merge_sort_by_arrive_time(p, 0, len-1);
	newP = (Process *) malloc(sizeof(Process) * 1);
	newP[0]=p[0];
	i=0;
	j=1;
	while(1==1){
		exec++;
		if(exec>=newP[i].burst||exec>=quantum){
			if(newP[i].burst>quantum){
				newPLen+=1;
				newP = (Process *) realloc(newP,sizeof(Process) *newPLen);
				newP[newPLen-1] = newP[i];
				newP[newPLen-1].burst-=exec;
				newP[i].burst = exec;
			}
			exec=0;
			i++;
			time++;
		}
		if(p[j].arrive_time <= time){
			newPLen+=1;
			newP = (Process *) realloc(newP,sizeof(Process) *newPLen);
			newP[newPLen-1] = p[j];
			j+=1;
		}
		
		
		time++;
		if(i>=newPLen){
			break;
		}
		
	}
	
	time = 0;
	
	
	
	
	
	
	for(i=0;i<newPLen;i++){
		if(newP[i].arrive_time>time) time = newP[i].arrive_time;	//comando para tratar se não tem processos executando;
		newP[i].response_time = time - newP[i].arrive_time;
		newP[i].return_time = time+ newP[i].burst;
		newP[i].waiting_time = time -newP[i].arrive_time;
		newP[i].turnaround_time = time+ newP[i].burst-newP[i].arrive_time;
		newP[i].completed = 1;
		total_waiting_time += newP[i].waiting_time;
		total_turnaround_time += newP[i].turnaround_time;
		total_response_time += newP[i].response_time;
		time+=newP[i].burst;
		
	}
	printf("\tRound Robin\n\n");
	rr_print_gantt_chart(newP, newPLen,quantum);
    printf("\n\tAverage Waiting Time     : %-2.2lf\n", (double)total_waiting_time / (double)newPLen);
    printf("\tAverage Turnaround Time  : %-2.2lf\n", (double)total_turnaround_time / (double)newPLen);
    printf("\tAverage Response Time    : %-2.2lf\n\n", (double)total_response_time / (double)newPLen);

    print_table(newP, newPLen);
    free(newP);
}

#endif
