// This code is used to check accuracy of rdtsc operation to profile a code for inel architecture. 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <math.h>

volatile int variable = 0;
unsigned long flags;

#define RDTSC_START()            \
	__asm__ volatile("CPUID\n\t" \
	                 "RDTSC\n\t" \
	                 "mov %%edx, %0\n\t" \
	                 "mov %%eax, %1\n\t" \
	                 : "=r" (start_hi), "=r" (start_lo) \
	                 :: "%rax", "%rbx", "%rcx", "%rdx");

#define RDTSC_STOP()              \
	__asm__ volatile("RDTSCP\n\t" \
	                 "mov %%edx, %0\n\t" \
	                 "mov %%eax, %1\n\t" \
	                 "CPUID\n\t" \
	                 : "=r" (end_hi), "=r" (end_lo) \
	                 :: "%rax", "%rbx", "%rcx", "%rdx");

uint64_t elapsed(uint32_t start_hi, uint32_t start_lo,
                 uint32_t end_hi,   uint32_t end_lo)
{
	uint64_t start = (((uint64_t)start_hi) << 32) | start_lo;
	uint64_t end   = (((uint64_t)end_hi)   << 32) | end_lo;
	return end-start;
}
double variance(int a[], int n)
{
    
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += a[i];
    double mean = (double)sum /
                  (double)n;
 
    
    double sqDiff = 0;
    for (int i = 0; i < n; i++)
        sqDiff += (a[i] - mean) *
                  (a[i] - mean);
    return sqDiff / n;
}

int main(void)
{
	uint32_t start_hi=0, start_lo=0; 
	uint32_t   end_hi=0,   end_lo=0;

	
	

#define REPEAT 1000
int arrprintf[1000] = {0};
int arrnothing[1000] = {0};
int arrloop[1000] = {0};
int arrprintf1[1000] = {0};
int arrnothing1[1000] = {0};
int arrloop1[1000] = {0};
uint64_t totalTime = 0;

for(int j=0;j<REPEAT;j++)
{
	for(int i=0; i<REPEAT; i++)
	 
	{
		 variable = 0;
       
		RDTSC_START();
		printf("printing!\n"); // how fast is printf()?
		RDTSC_STOP();
		uint64_t e = elapsed(start_hi, start_lo, end_hi, end_lo);
		printf("trial, %d, %ld,printf\n", i, e);
		arrprintf[i]=e;
		totalTime += e;
		
	}


	int var = variance(arrprintf,REPEAT);
    printf("trail,%d,%d,varince\n",j, var);


 
	arrprintf1[j]=var;
}
    int varofvarprintf = variance(arrprintf1,REPEAT);
    printf("%d \n", varofvarprintf);

	return 0;
}