#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lcgrand.h"

#define Idle 0
#define Busy 1

void depature (double *Sim_Time,double *next_dept_time,double *Time_since_Last_Event, double *Last_Event_Time, double *C_Area_Under_Q, double *E_Area_Under_Q,int *C_Num_In_Queue, int *E_Num_In_Queue,int *Server_Status, double *C_qDelay, double *E_qDelay,double *C_Time_Arrival,
               double *E_Time_Arrival, double *C_Total_qDelay, double *E_Total_qDelay,int *Num_Custs_Delayed, float *mean_service_time,double *C_sys_delay, double *E_sys_delay,double *C_total_sys_delay,double *E_total_sys_delay);

void C_arrival(double *Sim_Time,double *C_next_arr_time,float *C_mean_interarrival_time,double *Time_since_Last_Event, double *Last_Event_Time,double *C_Area_Under_Q, int *C_Num_In_Queue, int *Server_Status, double *C_qDelay, double *E_qDelay, double *C_Total_qDelay, double *E_Total_qDelay, int *E_Num_In_Queue,
               int *C_Q_limit, double *next_dept_time, float *mean_service_time,double *C_Time_Arrival, int *Num_Custs_Delayed, double *num_of_C_full,double *E_Time_Arrival );

void E_arrival(double *Sim_Time,double *E_next_arr_time,float *E_mean_interarrival_time,double *Time_since_Last_Event, double *Last_Event_Time,double *E_Area_Under_Q, int *E_Num_In_Queue, int *Server_Status, double *C_qDelay, double *E_qDelay, double *C_Total_qDelay, double *E_Total_qDelay, int *C_Num_In_Queue,
               int *E_Q_limit, double *next_dept_time, float *mean_service_time,double *E_Time_Arrival, int *Num_Custs_Delayed, double*num_of_E_full,double *C_Time_Arrival);


float expon(float mean);
double minimum(double *next_dept_time, double  *C_next_arr_time, double *E_next_arr_time);
int main()
{
// Initialize

    double Sim_Time = 0;

    int Server_Status = Idle;

    int C_Num_In_Queue = 0;
    int E_Num_In_Queue = 0;

    int Num_Custs_Delayed = 0;

    double C_avg_qdelay = 0;
    double E_avg_qdelay = 0;

    float C_avg_num_in_queue = 0;
    float E_avg_num_in_queue = 0;

    float C_mean_interarrival_time = 0;
    float E_mean_interarrival_time = 0;

    double next_dept_time = pow(10,30);
    float mean_service_time = 0;

    double C_next_arr_time = 0;
    double E_next_arr_time = 0;

    int Num_Delays_Required = 0;

    int C_Q_limit = 0;
    int E_Q_limit = 0;

    int C_K = 0;
    int E_K = 0;

    double C_Area_Under_Q = 0;
    double E_Area_Under_Q = 0;

    double Last_Event_Time=0;

    double C_Total_qDelay = 0;
    double E_Total_qDelay = 0;

    double C_qDelay = 0;
    double E_qDelay = 0;

    double Time_since_Last_Event = 0;

    double min_time = 0;

    double num_of_C_arr = 0;
    double num_of_E_arr = 0;

    double num_of_C_full = 0;
    double num_of_E_full = 0;

    float C_Pk = 0;
    float E_Pk = 0;

    double C_sys_delay = 0;
    double E_sys_delay = 0;

    double C_total_sys_delay = 0;
    double E_total_sys_delay = 0;

    float C_avg_sys_delay =0;
    float E_avg_sys_delay =0;

    printf("Enter customer mean_interarrival_time\n");
	scanf("%f", &C_mean_interarrival_time);
    C_next_arr_time=expon(C_mean_interarrival_time);

    printf("Enter energy mean_interarrival_time\n");
	scanf("%f", &E_mean_interarrival_time);
    E_next_arr_time=expon(E_mean_interarrival_time);

    printf("Enter mean_service_time\n");
	scanf("%f", &mean_service_time);

	printf("Enter num_delays_required\n");
	scanf ("%d", &Num_Delays_Required);

    printf("Enter Customer_K\n");
    scanf ("%d", &C_K);

    C_Q_limit = C_K -1;

    double C_Time_Arrival[C_Q_limit+1];

    for (int i=0; i<C_Q_limit+1;i++){
        C_Time_Arrival[i]=0;
    }

    printf("Enter Energy_K\n");
    scanf ("%d", &E_K);

    E_Q_limit = E_K-1;

    double E_Time_Arrival[E_Q_limit+1];

    for (int i=0; i<E_Q_limit+1;i++){
        E_Time_Arrival[i]=0;
    }

//Initialize end

while (Num_Custs_Delayed<Num_Delays_Required){
    min_time = minimum(&next_dept_time, &C_next_arr_time, &E_next_arr_time);

    if (min_time == next_dept_time){
        depature ( &Sim_Time, &next_dept_time, &Time_since_Last_Event,  &Last_Event_Time, &C_Area_Under_Q, &E_Area_Under_Q, &C_Num_In_Queue, &E_Num_In_Queue, &Server_Status, &C_qDelay, &E_qDelay, C_Time_Arrival,
                E_Time_Arrival, &C_Total_qDelay, &E_Total_qDelay, &Num_Custs_Delayed, &mean_service_time, &C_sys_delay,  &E_sys_delay, &C_total_sys_delay, &E_total_sys_delay);

    }
    else if (min_time == C_next_arr_time){
         C_arrival(&Sim_Time, &C_next_arr_time, &C_mean_interarrival_time, &Time_since_Last_Event,  &Last_Event_Time, &C_Area_Under_Q,  &C_Num_In_Queue,  &Server_Status,  &C_qDelay, &E_qDelay, &C_Total_qDelay, &E_Total_qDelay, &E_Num_In_Queue,
                &C_Q_limit,  &next_dept_time,  &mean_service_time, C_Time_Arrival, &Num_Custs_Delayed,&num_of_C_full, E_Time_Arrival);
        num_of_C_arr++;
    }

    else{
         E_arrival( &Sim_Time, &E_next_arr_time, &E_mean_interarrival_time, &Time_since_Last_Event,  &Last_Event_Time, &E_Area_Under_Q,  &E_Num_In_Queue,  &Server_Status,  &C_qDelay,  &E_qDelay,   &C_Total_qDelay, &E_Total_qDelay, &C_Num_In_Queue,
                &E_Q_limit,  &next_dept_time,  &mean_service_time, E_Time_Arrival, &Num_Custs_Delayed,&num_of_E_full,C_Time_Arrival );

                num_of_E_arr++;
    }
}

printf("\n");
printf("sim_time= %.8f \n",Sim_Time);
printf("num_custs_delayed= %d \n",Num_Custs_Delayed);

C_avg_qdelay = C_Total_qDelay/Num_Custs_Delayed;
printf("C_avg_q_delay= %.8f \n",C_avg_qdelay);
E_avg_qdelay = E_Total_qDelay/Num_Custs_Delayed;
printf("E_avg_q_delay= %.8f \n",E_avg_qdelay);

C_avg_num_in_queue = C_Area_Under_Q/Sim_Time;
printf("C_avg_num_in_queue= %.8f \n",C_avg_num_in_queue);
E_avg_num_in_queue = E_Area_Under_Q/Sim_Time;
printf("E_avg_num_in_queue= %.8f \n",E_avg_num_in_queue);

C_avg_sys_delay = C_total_sys_delay/Sim_Time;
printf("C_avg_system_delay= %.8f \n",C_avg_sys_delay);

E_avg_sys_delay = E_total_sys_delay/Sim_Time;
printf("E_avg_system_delay= %.8f \n",E_avg_sys_delay);

C_Pk = num_of_C_full/num_of_C_arr;
printf("C_Pk = %f \n", C_Pk);
E_Pk = num_of_E_full/num_of_E_arr;
printf("E_Pk = %f \n", E_Pk);


    return 0;
}

void depature (double *Sim_Time,double *next_dept_time,double *Time_since_Last_Event, double *Last_Event_Time, double *C_Area_Under_Q, double *E_Area_Under_Q,int *C_Num_In_Queue, int *E_Num_In_Queue,int *Server_Status, double *C_qDelay, double *E_qDelay,double *C_Time_Arrival,
               double *E_Time_Arrival, double *C_Total_qDelay, double *E_Total_qDelay,int *Num_Custs_Delayed, float *mean_service_time, double *C_sys_delay, double *E_sys_delay,double *C_total_sys_delay,double *E_total_sys_delay){

        *Sim_Time = *next_dept_time;
        *Time_since_Last_Event = *Sim_Time - *Last_Event_Time;
        *Last_Event_Time = *Sim_Time;

        *C_Area_Under_Q += (*C_Num_In_Queue) * (*Time_since_Last_Event);
        *E_Area_Under_Q += (*E_Num_In_Queue) * (*Time_since_Last_Event);


        if (*C_Num_In_Queue==0){
            *Server_Status = Idle;
            *next_dept_time = pow(10,30);

            *C_sys_delay = *Sim_Time - C_Time_Arrival[0];
            *C_total_sys_delay += *C_sys_delay;

            *E_sys_delay = *Sim_Time - E_Time_Arrival[0];
            *E_total_sys_delay +=*E_sys_delay;


        }
        else if (*E_Num_In_Queue==0){
            *Server_Status = Idle;
            *next_dept_time = pow(10,30);

            *C_sys_delay =*Sim_Time - C_Time_Arrival[0];
            *C_total_sys_delay += *C_sys_delay;

            *E_sys_delay = *Sim_Time - E_Time_Arrival[0];
            *E_total_sys_delay += *E_sys_delay;

        }
        else{
            (*C_Num_In_Queue)--;
            (*E_Num_In_Queue)--;
            *C_qDelay = *Sim_Time - C_Time_Arrival[1];
            *C_Total_qDelay += *C_qDelay;

            *E_qDelay = *Sim_Time - E_Time_Arrival[1];
            *E_Total_qDelay += *E_qDelay;

            *C_sys_delay = *Sim_Time - C_Time_Arrival[0];
            *C_total_sys_delay += *C_sys_delay;

            *E_sys_delay = *Sim_Time - E_Time_Arrival[0];
            *E_total_sys_delay += *E_sys_delay;


            (*Num_Custs_Delayed)++;

            *next_dept_time = *Sim_Time + expon(*mean_service_time);

            for (int i=0; i<=*C_Num_In_Queue;i++){
                C_Time_Arrival[i]=C_Time_Arrival[i+1];
            }

            for (int i=0; i<=*E_Num_In_Queue;i++){
                E_Time_Arrival[i]=E_Time_Arrival[i+1];
            }

        }

}




void E_arrival(double *Sim_Time,double *E_next_arr_time,float *E_mean_interarrival_time,double *Time_since_Last_Event, double *Last_Event_Time,double *E_Area_Under_Q, int *E_Num_In_Queue, int *Server_Status,  double *C_qDelay, double *E_qDelay, double *C_Total_qDelay, double *E_Total_qDelay, int *C_Num_In_Queue,
               int *E_Q_limit, double *next_dept_time, float *mean_service_time,double *E_Time_Arrival, int *Num_Custs_Delayed, double*num_of_E_full,double *C_Time_Arrival){

    *Sim_Time = *E_next_arr_time;
    *E_next_arr_time = *Sim_Time + expon(*E_mean_interarrival_time);
    *Time_since_Last_Event = *Sim_Time - *Last_Event_Time;
    *Last_Event_Time = *Sim_Time;
    *E_Area_Under_Q +=(*E_Num_In_Queue) * (*Time_since_Last_Event);

    if (*Server_Status == Idle){
        if (*C_Num_In_Queue != 0){
            (*Num_Custs_Delayed)++;
            *Server_Status= Busy;
            *C_qDelay = *Sim_Time - C_Time_Arrival[1];
            *C_Total_qDelay += *C_qDelay;
            *next_dept_time = *Sim_Time + expon(*mean_service_time);
            (*C_Num_In_Queue)--;
            E_Time_Arrival[0]= *Sim_Time;

            for (int i=0; i<=*C_Num_In_Queue;i++){
                C_Time_Arrival[i]=C_Time_Arrival[i+1];
            }


        }


        else{
        (*E_Num_In_Queue)++;

        if (*E_Num_In_Queue > *E_Q_limit){

         (*E_Num_In_Queue)--;
         (*num_of_E_full)++;

        }

        else {

        E_Time_Arrival[*E_Num_In_Queue] = *Sim_Time;

        }
    }

    }
    else{
        (*E_Num_In_Queue)++;

        if (*E_Num_In_Queue > *E_Q_limit){

         (*E_Num_In_Queue)--;
         (*num_of_E_full)++;

        }

        else {

        E_Time_Arrival[*E_Num_In_Queue] = *Sim_Time;

        }
    }


}




void C_arrival(double *Sim_Time,double *C_next_arr_time,float *C_mean_interarrival_time,double *Time_since_Last_Event, double *Last_Event_Time,double *C_Area_Under_Q, int *C_Num_In_Queue, int *Server_Status, double *C_qDelay, double *E_qDelay,double *C_Total_qDelay, double *E_Total_qDelay,  int *E_Num_In_Queue,
               int *C_Q_limit, double *next_dept_time, float *mean_service_time,double *C_Time_Arrival,int *Num_Custs_Delayed, double *num_of_C_full,double *E_Time_Arrival){

    *Sim_Time = *C_next_arr_time;
    *C_next_arr_time = *Sim_Time + expon(*C_mean_interarrival_time);
    *Time_since_Last_Event = *Sim_Time - *Last_Event_Time;
    *Last_Event_Time = *Sim_Time;
    *C_Area_Under_Q +=(*C_Num_In_Queue) * (*Time_since_Last_Event);

    if (*Server_Status == Idle){
        if (*E_Num_In_Queue != 0){
            (*Num_Custs_Delayed)++;
            *Server_Status= Busy;
            *E_qDelay = *Sim_Time - E_Time_Arrival[1];
            *E_Total_qDelay += *E_qDelay;
            *next_dept_time = *Sim_Time + expon(*mean_service_time);
            (*E_Num_In_Queue)--;
            C_Time_Arrival[0] = *Sim_Time;
             for (int i=0; i<=*E_Num_In_Queue;i++){
                E_Time_Arrival[i]=E_Time_Arrival[i+1];
            }

        }
         else{

        (*C_Num_In_Queue)++;

        if (*C_Num_In_Queue > *C_Q_limit){

         (*C_Num_In_Queue)--;
        (*num_of_C_full)++;
        }

        else {

        C_Time_Arrival[*C_Num_In_Queue] = *Sim_Time;

        }
        }
    }
    else{
        (*C_Num_In_Queue)++;

        if (*C_Num_In_Queue > *C_Q_limit){

         (*C_Num_In_Queue)--;
        (*num_of_C_full)++;
        }

        else {

        C_Time_Arrival[*C_Num_In_Queue] = *Sim_Time;

        }
    }


}


float expon(float mean){
    return -mean*log(lcgrand(1));
}


double minimum(double *next_dept_time, double  *C_next_arr_time, double *E_next_arr_time){
    double min;
    min = *next_dept_time;
    if (min>*C_next_arr_time){
        min = *C_next_arr_time;
    }
    if (min>*E_next_arr_time){
        min = *E_next_arr_time;
    }

    return min;

}