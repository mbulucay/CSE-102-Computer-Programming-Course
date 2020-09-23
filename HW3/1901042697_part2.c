#include <stdio.h>
#include <math.h>

int isprime(int a);
	
int main(){
		
	int N,check,i;

	printf("Please enter an integer : ");
	scanf("%d",&N);

	for(i=2;i<N;i++){		//This is checking for all numbers until reach the number which enter user

		printf("\n");
		check = isprime(i);		//this function return small value if there is
								//is not function return 0 so it show us the number is prime
		if(check == 0)
			printf("%d is a prime number\n",i);	//When func is return 0
		else 
			printf("%d is not a prime number, it is dividible by %d\n",i,check);//When the function any value exept 0	
	}																			//it is the smallest prime smallest divider
	return 0;
}
///*===================================================================================*/
int isprime(int a){

	int i=0,small_divide=0;
	float root;
	
	root=sqrt(a);		//This is the formul

	for(i=2;i<=root;i++){
		if(a%i == 0){			
			small_divide = i;//if number can divide the a it is the smallest divider 
			break;
		}						//becasue loop start from 2	
	}	
	return small_divide;
}
