#ifndef __SHORTEST__REMAINING__TIME
#define __SHORTEST__REMAINING__TIME
#include "./Process.h"
#include "./SortingFunction.h"
#include "./PrintTable.h"


void srt_calculate_time(Process *p, int len)
{
    int i;
    int current_time = 0;
    int total_burst_time = 0;
    int shortest_remain_time;
    int k = 0;
    int *remain_burst_time = (int *)malloc(sizeof(int) * len);
    int *count = (int *)malloc(sizeof(int) * len);
    for (i = 0; i < len; i++)
    {
        count[i] = 0;
        remain_burst_time[i] = p[i].burst;
        total_burst_time += p[i].burst;
    }
    while (current_time < total_burst_time)
    {
        shortest_remain_time = TMP_MAX;
        if (current_time <= p[len - 1].arrive_time)
        {
            for (i = 0; i < len; i++)
            {
                if ((p[i].completed == FALSE)
                    && (p[i].arrive_time <= current_time)
                    && (shortest_remain_time > remain_burst_time[i]))
                {
                    shortest_remain_time = remain_burst_time[i];
                    k = i;
                }
            }
        }
        else
        {
            for (i = 0; i < len; i++)
            {
                if ((p[i].completed == FALSE)
                    && (shortest_remain_time > remain_burst_time[i]))
                {
                    shortest_remain_time = remain_burst_time[i];
                    k = i;
                }
            }
        }
        if (count[k] == 0)
        {
            count[k]++;
            p[k].response_time = current_time;
        }

        remain_burst_time[k]--;
        current_time++;
        if (remain_burst_time[k] == 0)
        {
            p[k].completed = TRUE;
            p[k].waiting_time = current_time - p[k].burst - p[k].arrive_time;
            p[k].return_time = current_time;
        }
    }
    free(count);
    free(remain_burst_time);
}
void srt_print_gantt_chart(Process *p, int len)
{
    int i;
    int total_burst_time = 0;
    int current_time = 0, previous_time;
    int k, pre_k = 0;
    int shortest_remain_time, num;

    int *count = (int *)malloc(sizeof(int) * len);
    int *remain_burst_time = (int *)malloc(sizeof(int) * len);

    for (i = 0; i < len; i++)
    {
        remain_burst_time[i] = p[i].burst;
        total_burst_time += p[i].burst;
        p[i].completed = FALSE;
        count[i] = 0;
    }

    printf("\t ");
    while (current_time < total_burst_time)
    {
        shortest_remain_time = TMP_MAX;

        if (current_time <= p[len - 1].arrive_time)
        {
            for (i = 0; i < len; i++)
            {
                if ((p[i].completed == FALSE)
                    && (p[i].arrive_time <= current_time))
                {
                    if (shortest_remain_time > remain_burst_time[i])
                    {
                        shortest_remain_time = remain_burst_time[i];
                        k = i;
                    }
                }
            }
        }

        else
        {
            for (i = 0; i < len; i++)
            {
                if (p[i].completed == FALSE)
                {
                    if (shortest_remain_time > remain_burst_time[i])
                    {
                        shortest_remain_time = remain_burst_time[i];
                        k = i;
                    }
                }
            }
        }
        if (pre_k != k)
            printf(" ");

        printf("--");
        remain_burst_time[k]--;
        current_time++;
        pre_k = k;

        if (remain_burst_time[k] == 0)
            p[k].completed = TRUE;
    }

    for (i = 0; i < len; i++)
    {
        remain_burst_time[i] = p[i].burst;
        p[i].completed = FALSE;
    }

    current_time = 0;
    printf("\n\t|");
    while (current_time <= total_burst_time)
    {
        if (current_time != total_burst_time)
        {
            shortest_remain_time = TMP_MAX;

            if (current_time <= p[len - 1].arrive_time)
            {
                for (i = 0; i < len; i++)
                {
                    if ((p[i].completed == FALSE)
                        && (p[i].arrive_time <= current_time)
                        && (shortest_remain_time > remain_burst_time[i]))
                    {
                        shortest_remain_time = remain_burst_time[i];
                        k = i;
                    }
                }
            }

            else
            {
                for (i = 0; i < len; i++)
                {
                    if ((p[i].completed == FALSE)
                        && (shortest_remain_time > remain_burst_time[i]))
                    {
                        shortest_remain_time = remain_burst_time[i];
                        k = i;
                    }
                }
            }

            if (current_time == 0)
            {
                count[k]++;
                printf("  ");
            }

            else
            {
                if (pre_k != k)
                {
                    num = count[pre_k] + 1;
                    count[pre_k] = 0;
                    count[k]++;
                    for (i = 0; i < num; i++)
                        printf("\b");
                    printf("%2s", p[pre_k].id);
                    for (i = 0; i < num - 2; i++)
                        printf(" ");

                    printf("|  ");
                }
                else
                {
                    count[k]++;

                    printf("  ");
                }
            }

            pre_k = k;
            remain_burst_time[k]--;
            current_time++;

            if (remain_burst_time[k] == 0)
                p[k].completed = TRUE;
        }
        else
        {
            for (i = 0; i < count[pre_k] + 1; i++)
                printf("\b");
            printf("%2s", p[k].id);
            for (i = 0; i < count[pre_k] - 1; i++)
                printf(" ");

            break;
        }
    }

    for (i = 0; i < len; i++)
    {
        remain_burst_time[i] = p[i].burst;
        p[i].completed = FALSE;
    }

    current_time = 0;
    printf("|\n\t");
    while (current_time < total_burst_time)
    {
        shortest_remain_time = TMP_MAX;

        if (current_time <= p[len - 1].arrive_time)
        {
            for (i = 0; i < len; i++)
            {
                if ((p[i].completed == FALSE)
                    && (p[i].arrive_time <= current_time)
                    && (shortest_remain_time > remain_burst_time[i]))
                {
                    shortest_remain_time = remain_burst_time[i];
                    k = i;
                }
            }
        }

        else
        {
            for (i = 0; i < len; i++)
            {
                if ((p[i].completed == FALSE)
                    && (shortest_remain_time > remain_burst_time[i]))
                {
                    shortest_remain_time = remain_burst_time[i];
                    k = i;
                }
            }
        }

        if (pre_k != k)
            printf(" ");

        printf("--");

        remain_burst_time[k]--;
        current_time++;
        pre_k = k;

        if (remain_burst_time[k] == 0)
            p[k].completed = TRUE;
    }

    for (i = 0; i < len; i++)
    {
        remain_burst_time[i] = p[i].burst;
        p[i].completed = FALSE;
    }

    current_time = 0;
    printf("\n\t");
    while (current_time <= total_burst_time)
    {
        if (total_burst_time != current_time)
        {
            shortest_remain_time = TMP_MAX;

            if (current_time <= p[len - 1].arrive_time)
            {
                for (i = 0; i < len; i++)
                {
                    if ((p[i].completed == FALSE)
                        && (p[i].arrive_time <= current_time)
                        && (shortest_remain_time > remain_burst_time[i]))
                    {
                        shortest_remain_time = remain_burst_time[i];
                        k = i;
                    }
                }
            }

            else
            {
                for (i = 0; i < len; i++)
                {
                    if ((p[i].completed == FALSE)
                        && (shortest_remain_time > remain_burst_time[i]))
                    {
                        shortest_remain_time = remain_burst_time[i];
                        k = i;
                    }
                }
            }


            if (pre_k != k)
            {
                for (i = 0; i < num && current_time != 0; i++)
                    printf("  ");

                if (current_time != 0)
                    printf(" ");

                printf("%-2d", current_time);
                num = 0;

                previous_time = current_time;
            }

            else
                num++;

            remain_burst_time[k]--;
            current_time++;
            pre_k = k;

            if (remain_burst_time[k] == 0)
                p[k].completed = TRUE;
        }

        else
        {
            for (i = 0; i < current_time - previous_time - 1; i++)
                printf("  ");
            printf(" ");

            printf("%-2d", current_time);

            break;
        }
    }

    printf("\n");
    free(count);
    free(remain_burst_time);
}

void organizar(Process* p, int ini, int len){
	int i,j;
	Process pAux;
	for(i=ini; i<len; i++){
		for(j=i; j<len; j++){
			if(p[i].burst > p[j].burst){
				pAux = p[i];
				p[i] = p[j];
				p[j] = pAux;
			}
		}
	}
}


void SRT(Process *p, int len)
{
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
		
		if(p[j].arrive_time <= time){
			newPLen+=1;
			newP = (Process *) realloc(newP,sizeof(Process) *newPLen);
			newP[newPLen-1] = p[j];
			j+=1;
			organizar(newP,i+1,newPLen);
			if(newP[i].burst>newP[newPLen-1].burst){
				newPLen+=1;
				newP = (Process *) realloc(newP,sizeof(Process) *newPLen);
				newP[newPLen-1] = newP[i];
				newP[newPLen-1].burst-=exec;
				newP[i].burst = exec;
				exec = 0;
				i++;
				organizar(newP,i,newPLen);
			}
			
		}
		if(exec>=newP[i].burst){
			exec=0;
			i++;
			time++;
			organizar(newP,i,newPLen);
			continue;
		}
		
		time++;
		if(i>=newPLen){
			break;
		}
		
	}
	
	time = 0;
	
	
	
	
	
	
	for(i=0;i<newPLen;i++){
		if(newP[i].arrive_time>time) time = newP[i].arrive_time;	//comando para tratar se n�o tem processos executando;
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
	printf("\tShortest Remaining Time\n\n");
	srt_print_gantt_chart(p, len);
    printf("\n\tAverage Waiting Time     : %-2.2lf\n", (double)total_waiting_time / (double)newPLen);
    printf("\tAverage Turnaround Time  : %-2.2lf\n", (double)total_turnaround_time / (double)newPLen);
    printf("\tAverage Response Time    : %-2.2lf\n\n", (double)total_response_time / (double)newPLen);

    print_table(newP, newPLen);
    free(newP);
}

#endif
