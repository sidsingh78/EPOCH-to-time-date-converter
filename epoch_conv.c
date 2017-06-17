/*
EPOCH to human readable time and date converter for microcontrollers (PIC, AVR, Arduino, STM32)
Current EPOCH time can be found at https://www.epochconverter.com/
The code can be suitably modified to suit your requirements. I have extensively
tested this code with valid inputs. If you have any questions or if you find a bug, please contact me. 
Author: Siddharth Singh <sidsingh78@gmail.com>
Ver:1.0
Date: June 15, 2017 
*/


#include <stdio.h>
#include <stdlib.h>

static unsigned char month_days[12]={31,28,31,30,31,30,31,31,30,31,30,31};
static unsigned char week_days[7] = {4,5,6,0,1,2,3};
//Thu=4, Fri=5, Sat=6, Sun=0, Mon=1, Tue=2, Wed=3

unsigned char
ntp_hour, ntp_minute, ntp_second, ntp_week_day, ntp_date, ntp_month, leap_days, leap_year_ind ;

unsigned short temp_days;

unsigned int
epoch, ntp_year, days_since_epoch, day_of_year; 

char key;


int main()
{
   //---------------------------- Input and Calculations -------------------------------------
start: 
    leap_days=0; 
    leap_year_ind=0;
    printf("-------------------------------------------\n");    
    printf("Enter EPOCH => ");
    scanf ("%d",&epoch);
    
    // Add or substract time zone here. 
    epoch+=19800 ; //GMT +5:30 = +19800 seconds 
    
      ntp_second = epoch%60;
      epoch /= 60;
      ntp_minute = epoch%60;
      epoch /= 60;
      ntp_hour  = epoch%24;
      epoch /= 24;
        
      days_since_epoch = epoch;      //number of days since epoch
      ntp_week_day = week_days[days_since_epoch%7];  //Calculating WeekDay
      
      ntp_year = 1970+(days_since_epoch/365); // ball parking year, may not be accurate!
 
      int i;
      for (i=1972; i<ntp_year; i+=4)      // Calculating number of leap days since epoch/1970
         if(((i%4==0) && (i%100!=0)) || (i%400==0)) leap_days++;
            
      ntp_year = 1970+((days_since_epoch - leap_days)/365); // Calculating accurate current year by (days_since_epoch - extra leap days)
      day_of_year = ((days_since_epoch - leap_days)%365)+1;
  
   
      if(((ntp_year%4==0) && (ntp_year%100!=0)) || (ntp_year%400==0))  
       {
         month_days[1]=29;     //February = 29 days for leap years
         leap_year_ind = 1;    //if current year is leap, set indicator to 1 
        }
            else month_days[1]=28; //February = 28 days for non-leap years 
   
            temp_days=0;
   
    for (ntp_month=0 ; ntp_month <= 11 ; ntp_month++) //calculating current Month
       {
           if (day_of_year <= temp_days) break; 
           temp_days = temp_days + month_days[ntp_month];
        }
    
    temp_days = temp_days - month_days[ntp_month-1]; //calculating current Date
    ntp_date = day_of_year - temp_days;
    
   // -------------------- Printing Results ------------------------------------- 
    
    switch(ntp_week_day) {
                         
                         case 0: printf("\nSunday");
                                 break;
                         case 1: printf("\nMonday");
                                 break;
                         case 2: printf("\nTuesday");
                                 break;
                         case 3: printf("\nWednesday");
                                 break;
                         case 4: printf("\nThursday");
                                 break;
                         case 5: printf("\nFriday");
                                 break;
                         case 6: printf("\nSaturday");
                                 break;
                         default: break;        
                         }
  printf(", "); 
  
  switch(ntp_month) {
                         
                         case 1: printf("January");
                                 break;
                         case 2: printf("February");
                                 break;
                         case 3: printf("March");
                                 break;
                         case 4: printf("April");
                                 break;
                         case 5: printf("May");
                                 break;
                         case 6: printf("June");
                                 break;
                         case 7: printf("July");
                                 break;
                         case 8: printf("August");
                                 break;
                         case 9: printf("September");
                                 break;
                         case 10: printf("October");
                                 break;
                         case 11: printf("November");
                                 break;
                         case 12: printf("December");       
                         default: break;        
                         }
  
  printf(" %2d",ntp_date);
  printf(", %d\n",ntp_year);
  printf("TIME = %2d : %2d : %2d\n\n", ntp_hour,ntp_minute,ntp_second)  ;
  printf("Days since Epoch: %d\n",days_since_epoch);
  printf("Number of Leap days since EPOCH: %d\n",leap_days);
  printf("Day of year = %d\n", day_of_year);
  printf("Is Year Leap? %d\n",leap_year_ind);
  printf("===============================================\n");
  printf(" Press e to EXIT, or any other key to repeat...\n\n");
  key=getch();
  if (key!='e') goto start; 
  return 0;
}
