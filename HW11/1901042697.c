#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define lenght_text 1000000

typedef struct ll_list{
	int n;
	struct ll_list *next;
}ll_list;

typedef struct dif_nums{
	int n_1,n_2;
}dif_nums;

void Execute_1();
int* read_array(char *filename,long int *size);
float * stats_array(int *d_nums,long int size);
ll_list* read_linkedlist(char *filename);
float * stats_linkedlist(ll_list *ll,long int size);

void Execute_2();
dif_nums * find_dif_num_in_same_index(ll_list * root,int *d_list,int size,int *dif_s);

int main(){ 

	printf("%ld  \n",sizeof(ll_list) );

	int op;
	while(op != 0){
		printf("==========================================\n");
		printf("0. Close the program\n");	
		printf("1. Part 1\n");
		printf("2. Part 2\n");
		printf("Choose execute part which you want?\n");
		scanf("%d",&op);
		printf("==========================================\n");
		if(op == 1)
			Execute_1();
		else if(op == 2)
			Execute_2();
		else if(op != 0)
			printf("Unknown operation\n");
	}
	return 0;
}
/*==================================================*/
void Execute_1(){
	int *d_list;
	long int size,byte_1=0,byte_2=0;
	float *d_datas,*l_datas;
	ll_list *root,*iter;
	clock_t start_0,stop_0,start_1,stop_1,
			start_2,stop_2,start_3,stop_3;
	double time_0,time_1,
		   time_2,time_3;						//Sirasiyla fonksiyonlar icin gecen zamanlar hesaplaniyor

	d_datas = malloc(sizeof(float)*4); 			//Min, max, mean, std icin yer ayiriyoruz
	l_datas = malloc(sizeof(float)*4); 

	start_0 = clock();
/**/d_list = read_array("list.txt",&size);
	stop_0 = clock();
	time_0 = (double)(stop_0-start_0) /CLOCKS_PER_SEC;
	for(int i=0; d_list[i] != -1; i++)			//Dinamik arrayin boyutu hesaplaniyor
		byte_1 += sizeof(d_list[i]);	
	
	start_1 = clock();
/**/d_datas = stats_array(d_list,size);
	stop_1 = clock();
	time_1 = (double)(stop_1-start_1) /CLOCKS_PER_SEC;
	
	printf("\n(#read_array#) required time = %lf s\n",time_0 );
	printf("(#stats_array#)required time = %lf s\n",time_1 );
	printf("(#read_array#) using byte is for = %ld\n\n",byte_1 );
	printf("Min num  = %f\nMaks num = %f\n",d_datas[0],d_datas[1] );	
	printf("Mean num = %f\nSTD  dev = %f\n\n",d_datas[2],d_datas[3] );
	printf("----------------------------------------------\n\n");
		
	start_2 = clock();
/**/root = read_linkedlist("list.txt");
	stop_2 = clock();
	time_2 = (double)(stop_2-start_2) /CLOCKS_PER_SEC;
	iter = root;
	for (int i = 0; iter!=NULL ;i++){
		byte_2 += sizeof(ll_list);
		iter = iter ->next;
	}
	start_3 = clock();
/**/l_datas = stats_linkedlist(root,size);
	stop_3 = clock();
	time_3 = (double)(stop_3-start_3) /CLOCKS_PER_SEC;
	printf("(#read_linkedlist#) required time = %lf s\n",time_2 );
	printf("(#stats_linkedlist#)required time = %lf s\n",time_3 );
	printf("(#read_linkedlist#) using byte = %ld \n\n",byte_2 );
	printf("Min num  = %f\nMaks num = %f\n",l_datas[0],l_datas[1] );	
	printf("Mean num = %f\nSTD  dev = %f\n\n",l_datas[2],l_datas[3] );

	free(d_list);		//Alinan ram yerleri geri veriliyor
	free(root);
	free(l_datas);
	free(d_datas);
}
/*==================================================*/
int* read_array(char *filename,long int *size){

	int *d_list = NULL;
	int  s_n;
	long int conuter=0;
	char text[lenght_text], 
		 *no_need;
	char *number = (char*)malloc(sizeof(char)*7);	//string numara
	
	FILE *fptr;
	fptr = fopen(filename,"r");
	fgets(text,lenght_text,fptr);

	d_list = (int*)malloc(sizeof(int));		//dinamik array icin ilk yer ayitiliyor
	number = strtok(text,",");
	s_n = strtol(number, &no_need,10);
	d_list[conuter] = s_n;
	conuter++;

	d_list = (int*)realloc(d_list,sizeof(int)*(conuter+1));	//dinamik arrayde boyut buyutuluyor
	number = strtok(NULL,",");
	s_n = strtol(number, &no_need,10);
	d_list[conuter] = s_n;
	conuter++;

	while((number = strtok(NULL,",")) != NULL){		//Alinana satir arrayi sonuna gelene kadar 
													//virgulle alinan sayilari ayiriyor
		d_list = (int*)realloc(d_list,sizeof(int)*(conuter+1));	//Array boyutu artiriliyor
		s_n = strtol(number, &no_need,10);		//string integera ceviriliyor
		d_list[conuter] = s_n;				//Acilana yere cevirilen degerler sirasiyla yazdiriliyor
		conuter++;					//boyut artirmak icin counter kullaniyoruz 
	}
	d_list[conuter] = -1;		//Son elemana -1 ataniyor
	*size = conuter;			//Kac adet sayi oldugu tutuluyor

	fclose(fptr);			//Dosya kapaniyor
	return d_list;
}
/*==================================================*/
ll_list* read_linkedlist(char *filename){

	int num;
	char text[lenght_text], 
		 *no_need;
	char *number = (char*)malloc(sizeof(char)*7);
	
	ll_list *root,*iter;

	FILE *fptr;
	fptr = fopen(filename,"r");		
	fgets(text,lenght_text,fptr);		//Text icindeki satir string olarak aliniyot

	root = (ll_list*)malloc(sizeof(ll_list));		//Link list icin ilk yer aciliyot
	iter = root;		//Daha hizli olmasi icin iter kullaniliyor
	iter->next = NULL;

	number = strtok(text,",");		//Text virgullere parcalaniyor
	num = strtol(number, &no_need,10);		//str to int
	iter -> n = num;	//Listeye sayi ekleniyor
	iter -> next = (ll_list*)malloc(sizeof(ll_list));	//Bir yer daha aciliyor
	iter = iter -> next;
	number = strtok(NULL,",");
	num = strtol(number, &no_need,10);
	iter ->  n  = num ;					//Ikinci sayida elle konuluyor
	iter ->  next = NULL;

	while((number = strtok(NULL,",")) != NULL){	//Alinan string bitene kadar devam ediyor

		iter -> next = (ll_list*)malloc(sizeof(ll_list));	//Yer aciliyor
		iter -> next ->next = NULL;			
		num = strtol(number, &no_need,10);	//str to int 
		iter ->next -> n = num;			//sayi listeye ekleniyor
		iter = iter->next;		//Iter ilerletiliyor
	}
	return root;
}
/*==================================================*/
float *stats_array(int *d_nums,long int size){

	float *datas;
	long long int sum= 0,std_sum=0;
	long int fark_kare, i;
	datas =malloc(sizeof(int)*4);

	int max = d_nums[0];
	int min = d_nums[0];

	for(i=0; d_nums[i] != -1; i++){	//Max, min ve toplam bulunuyor
		sum += d_nums[i];	//Toplam	
		if(d_nums[i] > max)	//Max
			max = d_nums[i];
		if(d_nums[i] < min)	//Min
			min = d_nums[i];
	}

	datas[0] = min;
	datas[1] = max;
	datas[2] = (float) (sum/size);		//Ortalama hesaplaniyor

	for(i=0; d_nums[i] != -1; i++)		//Her eleman ortalamadan cikarilip karesini aliyoruz
		std_sum += (d_nums[i] - datas[2]) * (d_nums[i] - datas[2]);

	datas[3] = (float) sqrt(std_sum/(i-1));		//Son islem yapiliyor

	return datas;
}
/*==================================================*/
float * stats_linkedlist(ll_list *ll,long int size){

	ll_list *iter;			
	long long int sum = 0,sum_std=0;
	long int i;
	float *datas;
	datas =malloc(sizeof(int)*4);

	iter = ll;

	int max = ll->n;		//Ilk eleman en buyuk ve en kucuk olarak bulunuyor
	int min = ll->n;
	
	for(i=0;iter!=NULL; i++){	//Toplam min ve max hesaplaniyor
		sum += iter->n;	//Toplam
		if(iter->n > max)	//Max	
			max = iter->n;
		if(iter->n < min)	//Min
			min = iter->n;
		iter = iter->next;	//Iter ilerletiliyor
	}

	datas[0] = min;
	datas[1] = max;
	datas[2] = (float)(sum/size);	//Ortalama

	iter = ll;
	for(i=0;iter!=NULL; i++){
		sum_std += ((iter->n)-datas[2])*((iter->n)-datas[2]);	//STD icin her eleman ortalamadan cikarip 
		iter = iter->next;										//Karesini aliyoruz			
	}
	datas[3] = (float) sqrt(sum_std/(i-1));		//STD icin son islem yapiliyor
	return datas;
}
/*==================================================*/
void Execute_2(){

	int *d_list = NULL;
	ll_list *root,*iter; 
	dif_nums *dif_num_arr =NULL; //Dinamik struct array
	int n=0, less_one, count_dif,
		cont_1 = 0,	cont_2 = 0;

	root = (ll_list*)malloc(sizeof(ll_list));
	root->next = NULL;
	iter = root;

	printf("\nFill Dynamic Array until enter '-1'\n");
	scanf("%d",&n);
	while(n!=-1){	//Dinamik array dolduruluyor
		cont_1++;
		d_list = (int*)realloc(d_list,sizeof(int)*cont_1);
		d_list[cont_1-1] = n;
		scanf("%d",&n);
	}

	printf("\nFill Linked List until enter '-1'\n");
	scanf("%d",&n);
	while(1){				//Link list dolduruluyor
		iter->n = n;
		scanf("%d",&n);
		if(n == -1)
			break;
		iter->next = (ll_list*)malloc(sizeof(ll_list));
		iter->next->next = NULL;
		iter = iter->next;
		cont_2++;
	}
	if(cont_1 != cont_2+1){
		printf("Entered numbers are not equal in Linked list and Dinamic Array\n");
		printf("The operation will be done according to the small size\n");	
		if(cont_1 > cont_2)  //Girilen sayilarin adetlerini karsilastirip kucuk olana gore islem yapacagiz
			less_one = cont_2;
		if(cont_2 > cont_1)
			less_one = cont_1;
	}
	else	
		less_one = cont_1;		//Eger adet ayni ise adet less_one a ataniyor

	dif_num_arr = find_dif_num_in_same_index(root,&d_list[0],less_one,&count_dif);

	if(count_dif != 0){	//Dondurulen struct arrayi bulunan miktar kadar sirasiyla yazdiriliyor
		printf("\nThere are %d diffrent numbers \n",count_dif );
		for (int i = 0; i < count_dif; ++i){
			printf("%d => (%d) & (%d)\n",i+1,dif_num_arr[i].n_1,dif_num_arr[i].n_2);
		}
	}
	else
		printf("There is no diffrent numbers\n");
	printf("\n");
	
	free(d_list);		//Alinan yerler geri veriliyor
	free(root);
	free(dif_num_arr);
}
/*==================================================*/
dif_nums * find_dif_num_in_same_index(ll_list * root,int *d_list,int size,int *dif_s){

	int dif_size = 0;
	dif_nums *dif_arr = NULL;
	for(int i=0; i<size; i++){
		if(root->n != d_list[i]){		//Indexler karsilastiriliyor eger farkli ise struct arraya de 
			++dif_size;					//Uygun indexe dolduruluyor
			dif_arr = (dif_nums*)realloc(dif_arr,sizeof(dif_nums)*(dif_size));
			dif_arr[dif_size-1].n_1 = root->n;
			dif_arr[dif_size-1].n_2 = d_list[i];
		}
		root = root->next;		//Link list index artiriliyor
	}
	*dif_s = dif_size;	//Farkli sayi adedi
	return dif_arr;
}