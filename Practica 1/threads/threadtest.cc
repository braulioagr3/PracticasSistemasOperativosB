// threadtest.cc 
//	Simple test case for the threads assignment.
//
//	Create two threads, and have them context switch
//	back and forth between themselves by calling Thread::Yield, 
//	to illustratethe inner workings of the thread system.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include <stdio.h>
int arr[6];
//----------------------------------------------------------------------
// SimpleThread
// 	Loop 5 times, yielding the CPU to another ready thread 
//	each iteration.
//
//	"which" is simply a number identifying the thread, for debugging
//	purposes.
//----------------------------------------------------------------------

void
SimpleThread(int which)
{
    int num;
    
    for (num = 0; num < 5; num++) {
	printf("*** thread %d looped %d times\n", which, num);
        currentThread->Yield();
    }
}

void calculaFactorial(int which)
{
	int mayor=0;
	int i;
	int factorial =1;
	currentThread->Yield();
	printf("Hilo %d: \n",which);
	for(i=0 ;i<6 ; i++)
	{
		if(arr[i] > mayor)
		{
			mayor = arr[i];
		}
	}
	for(i = mayor ; i > 1 ; i--)
	{
		factorial *= i;
	}
	printf("El Factorial es: %d \n",factorial);
	currentThread->Yield();
}

void calculaPromedio(int which)
{
	int i;
	float prom;
	currentThread->Yield();
	printf("Hilo %d: \n",which);
	for(i = 0; i < 6 ; i++)
	{ 
		prom += arr[i];
	}
	prom /= 6;
	printf("El promedio de los numeros del arreglo es: %.2f \n",prom);
	currentThread->Yield();
}

void capturaDatos(int which)
{
	int i;
	printf("Hilo %d: \n",which);
	for(i = 0; i < 6 ; i++)
	{
		printf("Introduce el dato %d: ",i);
		scanf("%d",&arr[i]);
	}
}

void ordenaDatos(int which)
{
	int i,j,temp;
	currentThread->Yield();
	printf("Hilo %d: \n",which);
	for(i = 0 ; i < 6 ; i++)
	{
		for(j=i+1 ; j<6 ; j++)
		{
			if(arr[j] >  arr[i])
			{
				temp = arr[j];
				arr[j] = arr[i];
				arr[i] = temp;
			}
		}
	}
	for(i = 0; i < 6 ; i++)
	{
		printf("%d ",arr[i]);
	}
	printf("\n");
	currentThread->Yield();
}

//----------------------------------------------------------------------
// ThreadTest
// 	Set up a ping-pong between two threads, by forking a thread 
//	to call SimpleThread, and then calling SimpleThread ourselves.
//----------------------------------------------------------------------

void
ThreadTest()
{
	DEBUG('t', "Entering SimpleTest");
	int op;
	printf("1.- Simple Thread \n");
	printf("2.- Ejemplo hilos (FCFS) \n");
	printf("3.- Salir \n");
	scanf("%d",&op);
	if(op==1)
	{
		Thread *t = new Thread("forked thread");
		t->Fork(SimpleThread, 1);
		SimpleThread(0);
	}
	if(op==2)
	{
		Thread *t1 = new Thread("forked thread");
		Thread *t2 = new Thread("forked thread");
		Thread *t3 = new Thread("forked thread");
		capturaDatos(0);		
		t1->Fork(ordenaDatos,1);
		t2->Fork(calculaFactorial,2);
		t3->Fork(calculaPromedio, 3);
	}
	if(op==3)
	{
		printf("Adios\n");
	}	
}

