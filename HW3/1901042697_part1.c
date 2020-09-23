#include <stdio.h>

long int sum(long int n,int);
long int mult(long int n,int);

int main(){

	long int N;
	int flag,operation_flag;

	printf("Enter an integer : ");
	scanf("%ld",&N);

	printf("Please enter '0' for sum, '1' for multiplication \n");
	scanf("%d",&operation_flag);	

	printf("Please enter '0' to work on even numbers, '1' to work on odd numbers \n");
	scanf("%d",&flag);

	if(flag != 1 && flag != 0){
		printf("Invalid value for odd/even selection\n");
		return 0;
	}
	
	switch(operation_flag){		//According to the operation_flag chooseing case

		case 0:
			N = sum(N,flag);
			printf("= %ld\n",N);	//write the turning value from sum func 
			break;

		case 1:
			N = mult(N,flag);	//write the turning value from mult func	
			printf("= %ld\n",N);
			break;

		default:
			printf("Unsported operation\n");	//if the user enter different from 1,0 this is working	
	}
	return 0;
}
///*===================================================================================*/
long int sum(long int n,int flag){		
								//Result has to be 0 because 0 is inefective eleman in sum
	long int result=0;				//Flag already choose if even flag=0 then i=flag   and i=i+2 so numbers increasind two more each time until number  
	int i;		
													//if odd flag=1 then i=flag   and i=i+2 so numbers increasind two more each time until number
	for(i=flag;i<=n;i+=2){		
		printf("%d + ",i);		//write each time
		result +=i;	
	}
	return result;
}
///*===================================================================================*/
long int mult(long int n,int flag){

	long int result=1;			//Result has to be 1 because 1 is inefective eleman in multiplication
	int i;

	if(flag==0)				//If flag=0 flag must be 2 increase because 0 is yutan eleman
		flag+=2;			

	for(i=flag;i<=n;i+=2){		//Flag already choose if even flag=2 then i=flag   and i=i+2 so numbers increasind two more each time until number	
		printf("%d * ",i);	//write each time		  if odd flag=1 then i=flag   and i=i+2 so numbers increasind two more each time until number
		result *=i;	
	}
	return result;
}
///*===================================================================================*/
