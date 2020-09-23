#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define sizeof_array 501
#define N 8
#define str_lenght 200

void menu();

void Execute_1();
void list_1a();
void generate_hofstadters_sequence (int *arr, int n);
int find_max (int arr[], int index, int max_value);
int sum_array (int arr[]);
double std_array (int arr[], double *mean, int n, int index);

void Execute_2();
void install_pipes (int visited[N][N], int x, int y,int orientation);
void Execute_3();
char* remove_duplicates (char* str);

int main(){
	menu();
	return 0;
}
/*======================================================================================================*/
void menu(){

	int execute=0;
	char enter;

	while(execute != 4){
		printf("================================================================\n");
		printf("Welcome to Homework 8,please choose one of the parts to continue\n");
		printf("----------------------------------------------------------------\n");
		printf("1-) Execute Part 1\n");
		printf("2-) Execute Part 2\n");
		printf("3-) Execute Part 3\n");
		printf("4-) Exit\n");
		scanf("%d",&execute);

		switch(execute){
			case 1:
				Execute_1();			//Turn on 1. part	
				break;
			case 2:
				Execute_2();			//Turn on 2. part
				break;
			case 3:
				scanf("%c",&enter);		//To read enter '\n'
				Execute_3();			//Turn on 3. part
				break;
			case 4:
				printf("Program Closed\n");
				break;
			default :
				printf("Undefined execute number\n");
		}
	}
}
/*======================================================================================================*/
void Execute_1(){

	int arr[sizeof_array] = {0};
	int ope1=0, g_num,sum,
		max_value, flag=1;
	double 	mean ,S;

	arr[0] = 1;				//Placed known value
	arr[1] = 1;

	while(ope1 != 5){

		list_1a();
		scanf("%d",&ope1);
		while(flag && ope1 != 1 ){			//If the user want to do any operation before fill array we want to first fill array from user
			printf("Please, Firstly fill array, enter '1' :  ");
			scanf("%d",&ope1);
		}
		if(flag == 0 && ope1 ==1){			//If the user want to fill array again explain the result of this	
				printf("If you want to create new array please start again Execute 1\n");
				printf("Other wise you don`t get correct answer \n");	
		}
		switch(ope1){

			case 1 :
				flag=0;									//Doldurulmadan bir islem yapilmamasi icin konuldu
				printf("Please enter a number\n");
				scanf("%d",&g_num);
				generate_hofstadters_sequence(arr,g_num-1);		// Array 0 dan basladigi icin alinan sayinin bir eksigini gonderiyorum
				printf("---------= Array filled =---------\n");
				break;
			case 2 : 
				max_value = find_max(arr,g_num-1,arr[0]);		//Determine the first value as max_val 
				printf("Max value of array : %d\n",max_value);
				break;
			case 3 :
				sum = sum_array (arr);							//Sum function		
				printf("The sum of array = %d\n",sum);
				break;
			case 4 : 		
				S = std_array (arr, &mean, -g_num, g_num);	//Standart sapma fonksiyonu toplam degerini donduruyor
				S = sqrt(S/(g_num-1));						//Islemler yapiliyor ve yazdiriliyor	
				printf("Mean of array = %lf\n",mean);	
				printf("Standart Deviation of array = %lf \n",S);//Toplam fonksiyonu kullanidim ama dogru sonuc veriyor									
				break;
			case 5 :
				printf("Execute_1 has Closed\n");
				break;	
			default :
				printf("Undefined character\n");	
		}
	}	
}
/*======================================================================================================*/
void list_1a(){
	printf("Please make your choice : \n");
	printf("-------------------------\n");
	printf("1-) Fill Array\n");
	printf("2-) Find the biggest number\n");
	printf("3-) Calculate sum\n");
	printf("4-) Calculate standart devistation\n");
	printf("5-) Exit\n");
}
/*======================================================================================================*/
void generate_hofstadters_sequence (int *arr, int n){

	if(n == 1)
		return;
	if(arr[n] == 0)
		generate_hofstadters_sequence(arr,n-1);				//her index icin ilk bastaki yere kadar gidip toplayip hesapliyor
	arr[n] = arr[n - arr[n-1]] + arr[n - arr[n-2]];			//Sonra array icerisine hesaplanalar dolduruluyor	
}
/*======================================================================================================*/
int find_max (int arr[], int index, int max_value){

	if(index == 1)										//To finish recursive
		return max_value;

	if(arr[index] > max_value)							//Sirasiyla bakilan indexlerden herhangi biri max_valueden buyuk ise artik o max deger oluyor
		max_value = arr[index];
	
	find_max(arr,index-1,max_value);		//we send the next index
}
/*======================================================================================================*/
int sum_array (int arr[]){

	if(arr[0] == 0)							//arrayin sonunun 0 oldugunu biliyoruz ve recursive bitirme fonksiyonu olarak kullaniyoruz
		return 0;
	else	
		return arr[0]+sum_array(arr+1);		//Arrayin bir sonraki elemani surekli ilk eleman olup toplaniyor
}
/*======================================================================================================*/
double std_array (int arr[], double *mean, int n, int index){
	
	if(n < 0){							//ilk n i negatif index olarak gonredirip toplamlari bu sayde 0 dan baslayacak ve arttirdigimiz icin
		*mean += arr[index+n];			//sirasiyla 0,1,2... index sayisini gecince yani n negatif olamayana kadar ilerliyor 0 oldugunda terim sayisina boluyoruz
		n++;			//Siraki elemana bakmak icin artiriliyor
		if(n == 0){
			*mean = *mean/index;
			std_array(arr,mean,n,index);		//Siradaki adima gidyoruz n=0 olarak siradaki recursive isleme gidiyor
		}
		else
			std_array(arr,mean,n,index);		//Elemanlar bitene kadar buradan gonderiyor 
	}
	if(n == 0){		//	pozitif oldugunda index olrak kullaniyoruz
		if(arr[0] == 0)
			return 0;
		else
			return (((arr[0] - *mean) * (arr[0] - *mean))+ std_array(arr+1,mean,n,index)) ;	//Her terimden ortalamyi cikarip karesini aliyoruz taki sona kadar
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void Execute_2(){
	int tablo[N][N] = {0};
	install_pipes(tablo,0,0,1);
}
/*======================================================================================================*/
void install_pipes (int visited[N][N], int x, int y, int orientation){


	if(orientation == 64 && visited[x][y] == 0){
		visited[x][y] = orientation;						//We put the n.th place in visited
		for(int i=0; i<N; i++){
			for(int j=0; j<N; j++)
				printf("%4d",visited[i][j]);			//Print tablo
			printf("\n");
		}
		printf("\n");
		visited[x][y] = 0;									//We delete the last character in visited
	}

	else if(visited[x][y] == 0){
		visited[x][y] = orientation;						//We arrange the clock way

		if(x>=2 && y<=6){
			install_pipes(visited,x-2,y+1,orientation+1);	//If the O8 as pdf is available the put it
		}
		if(y<=5 && x>=1){
			install_pipes(visited,x-1,y+2,orientation+1);	//O4
		}
		if(y<=5 && x<=6){
			install_pipes(visited,x+1,y+2,orientation+1);	//O5
		}
		if(y<=6 && x<=5){
			install_pipes(visited,x+2,y+1,orientation+1);	//O1
		}
		if(x<=5 && y>=1){
			install_pipes(visited,x+2,y-1,orientation+1);	//O6
		}
		if(x<=6 && y>=2){	
			install_pipes(visited,x+1,y-2,orientation+1);	//O2
		}
		if(x>=1 && y>=2){
			install_pipes(visited,x-1,y-2,orientation+1);	//O7
		}
		if(x>=2 && y>=1){
			install_pipes(visited,x-2,y-1,orientation+1);	//O3
		}
		visited[x][y] = 0;				//We going back until find a valid position	
	}
																	
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void Execute_3(){

	char str[str_lenght];

	printf("Please enter a string : \n");
	scanf("%[^\n]s",str);  						//We get string
	remove_duplicates(str);						//Set string
	printf("%s\n",str );						//Print string
}
/*======================================================================================================*/
char* remove_duplicates (char* str){

	if(str[0] == 0)
		return 0;		
	else if(str[0] == str[1]){		//If next two char is same we enter in if
		int j=1;
		while(str[j+1] != 0){		//We shift the string until end of the string
			str[j] = str[j+1];	
			j++;
		}
		str[j] = 0;						//Determine the end of the string
		remove_duplicates(str);			//To don`t miss more then two character ex :aaa
	}
	else
		remove_duplicates(str+1);		//We are send next character to function
	return str;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////