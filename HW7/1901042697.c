#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxline 2000
#define max_game_name 200
#define LONGROW 200
#define maxvar_gen_plat 15
#define maxlen_gen_plat 20

void menu();
void list_operations();
void fill_all_info(char (*names)[max_game_name],char (*genres)[maxlen_gen_plat],char (*platforms)[maxlen_gen_plat], float datas[7][maxline]);
int check_is_same(char (*var)[20],char get[15]);
float ret_index(char (*var)[20],char get[15],int num);
void list_according_to_year(char (*names)[max_game_name] , float date[maxline]);
void game_info(char (*names)[max_game_name],char (*genres)[maxlen_gen_plat],char (*platforms)[maxlen_gen_plat],float datas[7][maxline]);
int ret_name_index(char (*names)[max_game_name],char get[max_game_name]);
int ret_genre_plat_index(float g_p_data[maxline],int index);
void compare_na_eu(char (*names)[max_game_name],float eu[maxline],float na[maxline]);
void frequency_genre_plat(char (*varierity)[maxlen_gen_plat],float data[maxline]);

int main(){
	menu();
	return 0;
}
/*====================================================================1========================================================*/
void menu(){

	char game_name[maxline][max_game_name],				//Arrays to put reading data from the file
		 genres[maxvar_gen_plat][maxlen_gen_plat],
		 platforms[maxvar_gen_plat][maxlen_gen_plat];
	float datas[7][maxline] = {0},
		  sum_of_scores=0; 	 
	int operations ,i;

	fill_all_info(game_name,genres,platforms,datas);	//This is fill information in arrays

	while(operations != 8){								//Loop is continue until operations==8
		
		list_operations();								//Printing all we can do
		printf("Please select an operations : ");
		scanf("%d",&operations);
		printf("\n");

		switch(operations){								

			case 0:
				for(i=0; genres[i][0] != '\0' ; i++)	//If user choose 0 operations 
					printf("%s\n",genres[i] );			//printing all variable genres
				break;
			case 1:
				for(i=0; platforms[i][0] != '\0'; i++)	//If user choose 1 operations
					printf("%s\n",platforms[i] );		//printing all variable platforms 
				break;
			case 2:
				list_according_to_year(game_name,datas[2]);		//datas[2] keep years						
				break;	
			case 3:
				game_info(game_name,genres,platforms,datas);	//Explain in function
				break;
			case 4:
				for(i=0;i<maxline;i++)
					sum_of_scores+=datas[6][i];				//We sum all numbers then divede it line number
				float avg = sum_of_scores/i;				
				printf("Avarage : %f\n",avg);
				break;
			case 5:	
				compare_na_eu(game_name,datas[4],datas[3]);	//datas[4] keep eu   datas[3] keep na 
				break;
			case 6:
				frequency_genre_plat(genres,datas[0]);	//datas[0] keep genres float info
				break;	
			case 7:
				frequency_genre_plat(platforms,datas[1]);	//datas[1] keep platforms float info
				break;	
			case 8:
				printf("Program Closed...\n");	
				break;
			default : 
				printf("TRY AGAIN\n" );	
		}
		printf("\n\n");
	}	
}
/*============================================================================================================================*/
void list_operations(){
	printf("0: List of the Genres\n");
	printf("1: List of the Platforms\n");
	printf("2: List of the Games Through the Years\n");
	printf("3: All Information of a Single Game\n");
	printf("4: Average of the User Scores\n");
	printf("5: Georographical Information of a Single Game\n");
	printf("6: Frequence of the Genres\n");
	printf("7: Frequence of the Platforms\n");
	printf("8: Exit\n\n");
}
/*============================================================================================================================*/
void fill_all_info(char (*names)[max_game_name],char (*genres)[maxlen_gen_plat],char (*platforms)[maxlen_gen_plat],float datas[7][maxline]){

	FILE *fptr;

	char *take = (char*)malloc(sizeof(char)*LONGROW),
		 line[maxline],
		 *str;
	int satir=0,
		count_genre=0,flag_genre,
		count_plat= 0,flag_plat;	

	if((fptr = fopen("Video_Games.txt","r")) == NULL)
		printf("DOSYA ACILAMADI\n");

	fgets(line,maxline,fptr); 										//Degersiz satir

	while(!feof(fptr)){

		fgets(line,maxline,fptr);

		take = strtok(line,",");										//Take name of the game
		strcpy(names[satir],take);

		take = strtok(NULL,",");				
		flag_genre = check_is_same(genres,take);	//Eger take yani aldigimiz genre daha onceden genres dizisine kaydedilmemis ise
		if(flag_genre == 0){						//fonksiyon 0 dondurup onu genres icerisine ekliyoruz
			strcpy(genres[count_genre],take);
			count_genre++;
		}
		datas[0][satir] = ret_index(genres,take,count_genre); 		// This is keep genres format float

		take = strtok(NULL,",");			
		flag_plat = check_is_same(platforms,take);	//Eger take yani aldigimiz platforms daha onceden alinmamis ise 0  
		if(flag_plat == 0){							//dondurup platforms icerisine ekliyoruz
			strcpy(platforms[count_plat],take);
			count_plat++;
		}
		datas[1][satir] = ret_index(platforms,take,count_plat);		//This is keep platforms format float	 

		take = strtok(NULL,",");
		datas[2][satir] = strtod(take,&str);						//This is keep date 		

		take = strtok(NULL,",");	
		datas[3][satir] = strtod(take,&str);						//This is keep na_sales

		take = strtok(NULL,",");		
		datas[4][satir] = strtod(take,&str);						//This is keep eu_sales

		take = strtok(NULL,",");										//This keep global_sales
		if(strcmp(take,"not_available") == 0)							//If gl_sales not available we make him negative number	
			datas[5][satir] = -1.0;									//To use forward process
		else 																
			datas[5][satir] = strtod(take,&str); 					//If there is any data this time we put it direct
		
		take = strtok(NULL,",");										//This keep user scores
		datas[6][satir] = strtod(take,&str);

		satir++;				//Icrease first place of all arrays
	}
}
/*============================================================================================================================*/
int check_is_same(char var[maxvar_gen_plat][20],char get[15]){

	int ret=0;
	for(int i=0; i<maxvar_gen_plat; i++){
		if(strcmp(var[i],get) == 0){	//Eger daha onceden alinan bir string varsa 1 donduruyor
			ret = 1;					//Ve dondurulen deger 1 ise alinan bir daha yazilmiyor
			break;
		}
	}
	return ret;							//Eger yoksa 0 dondurup string arraya ekliyor ve yaziyor
}
/*============================================================================================================================*/
float ret_index(char (*var)[20],char get[100],int num){

	float idx;
	for(int i=0; i<num; i++){
		if(strcmp(var[i],get) == 0)		//Get kelimesi var icerisinde hangi siradaki kelimeye esit ise 
			idx =(float) i;					//Onun bulundugu indeksi donduruyoruz
	}
	return idx;	
}	
/*============================================================================================================================*/
void list_according_to_year(char (*names)[max_game_name] , float date[maxline]){

	float get_year;
	int u_or_s, i=0;

	printf("Enter a year:\n");
	scanf("%f",&get_year);
	printf("Until (0) or Since (1) 2000: ");		//We get info according to games which want 
	scanf("%d",&u_or_s);

	while(get_year > 2005 || get_year < 1985){				//If year is not between valid year we want again 
		printf("TRY AGAIN  \nPlease enter a valid year : \n");
		scanf("%f",&get_year);
		printf("Until (0) or Since (1) 2000: ");
		scanf("%d",&u_or_s);
	}
	if(u_or_s!=1 && u_or_s != 0)		//Check u_or_s true entered
		printf("\nNot correct until or since value\nReturning to main menu");

	i=0;
	while(names[i][0] != '\0'){
		if(i==maxline)					//This is help to finish loop we can kown all line checked
			break;		
		if(u_or_s == 1 && date[i] > get_year)	//According to the input we list name of hames
			printf("%s\n",names[i]);
		if(u_or_s == 0 && get_year > date[i])	
			printf("%s\n",names[i]);
		i++;
	}
}
/*============================================================================================================================*/
void game_info(char (*names)[max_game_name],char (*genres)[maxlen_gen_plat],char (*platforms)[maxlen_gen_plat],float datas[7][maxline]){

	int index,
		index2,
		index3;
	char name[max_game_name];

	printf("Please enter the name of the game : \n");
	scanf("%s",name);

	index = ret_name_index(names,name);			//We get index until find the game
	while(index == -1){							//If it cannot find we want it until find	
		printf("The written name cannot found\nPlease enter a valid game name : \n");
		scanf("%s",name);
		index = ret_name_index(names,name);
	}
	
	index2 = ret_genre_plat_index(datas[0],index);		//This is returning genre of choosen game index 
	index3 = ret_genre_plat_index(datas[1],index);		//This is returning platforms of choosen game index 

	printf("Name: 	  \t%s\n",names[index]);			//Priting all info about game
	printf("Genre:	\t%s\n",genres[index2]);	
	printf("Platforms:\t%s\n",platforms[index3]);
	printf("Year:	\t%.f\n",datas[2][index]);
	printf("Sales In NA:\t%f\n",datas[3][index]);
	printf("Sales In EU:\t%f\n",datas[4][index]);
	if(datas[5][index] == -1)							//If global_sales not available we give him -1 in fill function
		printf("Total Sales:\tNot Available\n");		//and so we can check it easily here if it is equal -1 we understand that 
	else 												//	There is no data about choosen game
		printf("Total Sales:\t%f\n",datas[5][index]);	//If it is not -1 so there is data then we print it

	printf("User Score: \t%f\n",datas[6][index]);		
}
/*============================================================================================================================*/
int ret_name_index(char (*names)[max_game_name],char get[max_game_name]){

	int idx=-1;
	for(int i=0; i<maxline; i++){
		if(strcmp(names[i],get) == 0){		//Get stringi names icerisinde hangi siradaki stringe esit ise 
			idx = i;						//Onun bulundugu indeksi donduruyoruz
			break;
		}	
	}
	return idx;	
}
/*============================================================================================================================*/
int ret_genre_plat_index(float g_p_data[maxline],int index){
	index = g_p_data[index];	//This is returning games genres or platforms index using float genre and platforms arrays	
	return index;
}
/*============================================================================================================================*/
void compare_na_eu(char (*names)[max_game_name],float eu[maxline],float na[maxline]){

	char name[max_game_name];
	int index;

	printf("Please enter the name of the game : \n");
	scanf("%s",name);

	index = ret_name_index(names,name);												 //We are take index of name so we can find using this eu and na values
	while(index == -1){																 //If name not equal in names array then function return -1 so 
		printf("The written name cannot found\nPlease enter a valid game name : \n");//We understand that there is no game input name we want it again
		scanf("%s",name);
		index = ret_name_index(names,name);											 //Until find the game name	
	}

	if(eu[index] == na[index])									//We compare here using index
		printf("Games has equal popularity both places\n");
	else if(eu[index] > na[index])								//Then print result 
		printf("This game was more popular in Europe\n");
	else
		printf("This game was more popular in North America\n");
}
/*============================================================================================================================*/
void frequency_genre_plat(char (*varierity)[maxlen_gen_plat],float data[maxline]){

	int frequency[maxvar_gen_plat]={0};
	int gg;
													//We are calculate the datas how many 0,1,2 ... until varierity genre or platform	
	for(int i=0; i<maxline; i++){					//We increase the frequncy according to queue index
		gg= data[i];	
		frequency[gg]++;
	}
	for(int i=0; varierity[i][0] != '\0';i++){		//Print it the result name and frequency with queue
		if(strlen(varierity[i]) > 7)
			printf("%s\t%d\n",varierity[i],frequency[i]);
		else
			printf("%s\t\t%d\n",varierity[i],frequency[i]);
	}
}