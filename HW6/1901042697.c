#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define SIZE_COL 20	
#define SIZE_ROW 20
#define mx_word_leng 15
#define num_of_word 10
#define num_of_r_num 10
#define num_of_keys 10
#define x_y_position 2

int my_strlen(char *s);
char get_random_character();
int get_direction();
int get_position();
void get_10random_numbers(int randoms[num_of_r_num]);
void get_10random_words(char ran_word[mx_word_leng],int ran_num);

int check_can_put(int dr,int lenght,int x,int y, char tablo[SIZE_ROW][SIZE_COL]);
int check_lenght(int dr,int lenght,int x,int y);
int check_free_box(int dr,int lenght,int x,int y, char tablo[SIZE_ROW][SIZE_COL]);
void fill_free(char (*tablo)[SIZE_COL]);	

void print_grid(char tablo[SIZE_ROW][SIZE_COL]);
void put_grid(char words[mx_word_leng],char (*tablo)[SIZE_COL],int dr,int x,int y,int len,int deger);

void play_game(char (*tab)[SIZE_COL],char (*word)[mx_word_leng],char key_ch[num_of_keys],int key_nu[num_of_keys],int key_dr[num_of_keys],int key_ln[num_of_keys]);
int check_correttion(char get_str[mx_word_leng],char corret_str[mx_word_leng]);
void key_word_correction(char word[num_of_word][mx_word_leng]);

int main(){

	int i,j=0, flag=1,
		dr, len,
		pos[x_y_position],
		key_dr[num_of_keys],
		key_lenght[num_of_keys],
		keys_num[num_of_keys],
		random_numbers[num_of_r_num] = {0};

	char tab[SIZE_COL][SIZE_ROW] = {0},
		 random_words[num_of_word][mx_word_leng] = {0},
		 keys_char[num_of_keys] = {0};

	for(i=0;i<SIZE_COL;i++){									//To make easier process next steps we put '.' all place of tablo
		for(int j=0; j<SIZE_ROW;j++)
			tab[i][j] = '.';	
	}

	srand(time(NULL));

	get_10random_numbers(random_numbers);			//Get random num from func to random_numbers
	
	for(i=0; i<num_of_word; i++)
		get_10random_words(random_words[i],random_numbers[i]);		//We are getting random words according to the random numbers

	while(j<num_of_word){		//10 kelime tam anlmiyla yerlesene kadar devam ettiriyor

		dr = get_direction();	//Ex in func 				
		len = my_strlen(random_words[j]);

		for(i=0; i<2 ;i++)
			pos[i] = get_position();	//We are get two number betwen 0-19  because [x][y] determine row and cloumn		
		flag = check_can_put(dr,len,pos[0],pos[1],tab);		//Function return if the word can fit the position 
															//If it is not we are get another dr and pos 
		if(flag == 0){
			keys_char[j] = pos[1]+65;		// We are chance number to letter       0+65 = 'A'     5+65 = 'E'
			keys_num[j] = pos[0];				
			key_dr[j] = dr;					//We are keep keys  at 4  ex:{char = A  num = 12  dr = 2  len = 6 } line 
			key_lenght[j] = len;
			//printf("%s %c%d  dr>%d ln>%d\n",random_words[j],keys_char[j],keys_num[j],dr,len ); 		//If you want to see anser please turn on the line 
  			put_grid(random_words[j],tab,dr,pos[0],pos[1],len,0);
			j++;													//Counter putting words
		}
	}
	fill_free(tab);	
	play_game(tab,random_words,keys_char,keys_num,key_dr,key_lenght);
	return 0;
}
/*=======================================================================================================================*/
int get_random(){						// Give us only 1 random number
	return 1+rand()%99;
} 
/*=======================================================================================================================*/
char get_random_character(){			// after put words on tab , It gives us character for free area 
	return 97+rand()%25;
}
/*======================================================================================================================*/
void get_10random_numbers(int randoms[num_of_r_num]){

	int *new_rand = randoms;				//We collect total 10 random number to choose random words
	for(int i=0;i<num_of_r_num;i++){					//If number is 15 we get 15th word from wordlist.txt		
		new_rand [i]= get_random();
		for(int j=0;j<i;j++){
			if(new_rand[i] == new_rand[j]){			// If there is number before we got, we take another number
				while(new_rand[i] == new_rand[j]){	// to dont take same word
					new_rand[i] = get_random();		
				}
			}	
		}
	}
}
/*===================================================================================//On numlock pad======================*/
int get_direction(){			//Direction center is numlock 5    ex: if the direction is 6 the word writing 5 to 6
	int direction;															//direction is 1 the word writing 5 to 1
	direction =1+rand()%9;
		while(direction == 5)		//If the direction is equal center 					
			direction =1+rand()%9;	//we take another direction number until it is not equal center
}
/*=======================================================================================================================*/
int get_position(){			//We determine the position on tablo for word
	return rand()%19;		//We calling two time in menu function firt is x second is y
}
/*=======================================================================================================================*/
int my_strlen(char  *s){
									//The turning the lenght of the random words
	int len = 0;
	for(int i=0 ; s[i] != '\0' ;i++)		
		len++;
	return len-2;
}
/*=======================================================================================================================*/
void print_grid(char tablo[SIZE_ROW][SIZE_COL]){

	char harf=65;
									//This is printing tablo for each time 
	printf(" ");
	for(int j=0; j<SIZE_COL; j++)
		printf("%3d",j );		//Sutun rakamlarini yaziyor
	printf("\n");
	for(int i=0; i<SIZE_ROW ; i++){
		printf("%-3c",harf);	//Satir karakterlerini yaziyot
		for(int j=0 ; j<SIZE_COL ;j++)
			printf("%-3c",tablo[i][j]);
		printf("\n");
		harf++;
	}
}
/*======================================================================================================================================*/
void get_10random_words(char ran_word[mx_word_leng],int ran_num){

	int i,count=0;
	char *ran_pwords;		
	FILE *fptr;
	fptr = fopen("words.txt","r");

	ran_pwords = ran_word;		//This is effect to wrod use the menu function in menu		
	while(count < ran_num){
		fgets(ran_pwords,mx_word_leng,fptr);		//We are take random word from file according to the ran_num	
		count++;
	}
	fclose(fptr);
}
/*=========================================================================================================================================*/
void put_grid(char words[mx_word_leng],char (*tablo)[SIZE_COL],int dr,int x,int y,int len,int deger){

	//len = lenght of word    dr = direction  
	//deger = when the user is find the correct answer deger chancing to upper case 'a'-32 = 'A'
	
	int i;
	switch(dr){									//According to the direction 	
		case 1:									//Put the word on grid
			for(i=0; i<len; i++){				
				tablo[y][x] = words[i]+deger;	
				x--;	y++;					//Kelimelerin harflerini sirasiyla tabloya koyuyor 	
			}									//Yone gore degerler artiyor veya azaliyor
			break;
		case 2 :
			for(i=0; i<len; i++){
				tablo[y][x] = words[i]+deger;	//These are same process	
				y++;				
			}
			break;
		case 3:
			for(i=0; i<len; i++){
				tablo[y][x] = words[i]+deger;	
				y++;	x++;				
			}
			break;
		case 4:
			for(i=0; i<len; i++){
				tablo[y][x] = words[i]+deger;	
				x--;				
			}
			break;
		case 6:
			for(i=0; i<len; i++){
				tablo[y][x] = words[i]+deger;	
				x++;				
			}
			break;
		case 7:
			for(i=0; i<len; i++){
				tablo[y][x] = words[i]+deger;	
				x--;	y--;				
			}
			break;
		case 8:
			for(i=0; i<len; i++){
				tablo[y][x] = words[i]+deger;	
				y--;				
			}
			break;
		case 9:
			for(i=0; i<len; i++){
				tablo[y][x] = words[i]+deger;	
				x++;	y--;				
			}
	}	
}
/*==============================================================================================*/
int check_can_put(int dr,int lenght,int x,int y,char tablo[SIZE_ROW][SIZE_COL]){

	int check = 1,					//This function let us if word can suitable its place
		ch_len=1,ch_free = 1;

		ch_len = check_lenght(dr,lenght,x,y);	//Kelimenin tablodan tasmadigini dogruluyor	
		if(ch_len == 0){
			ch_free = check_free_box(dr,lenght,x,y,tablo); // Eger uzunluk uyuyorsa bu sefer tablonun
			if(ch_free == 0)							   // kelimeyi koyacagi yerinde baska kelime 	
				check = 0;								   // olup olmadigini kotrol ediyor		
		}
	return check;
}
/*===============================================================================================*/
int check_lenght(int dr,int lenght,int x,int y){

	int check_len = 1;		//x = kelimenin ilk karekterinin x posizyonu
							//y = kelimenin ilk karakterinin y pozisyonu
	switch(dr){			//Yone ve uzunlugununa gore kelimeyi koyup koyamayacagimizi donduruyor	
		case 1:
			if( ((x+2) > lenght) && ((lenght+y) < 21) )	//The rules of if dr=1  it is depend on two axis	
				check_len = 0; 
			break;
		case 2:
			if( (lenght+y) < 21 )	//The rules of if dr=2  it is depend on one axis 
				check_len = 0;
			break;
		case 3:
			if(((lenght+x) < 21) && ((lenght+y) < 21) )
				check_len = 0;
			break;						//Mesela
		case 4:							//x ilk kelimenin ilk harfinin pozisyonu
			if( (x+2) > lenght )		// eger yon 4 ise kelimeyi ters koyacagiz bu yuzden kelimenin uzunlugu
				check_len = 0;			// x+2 den kucuk olmali eger x kucuk ise kelime sigmaz 		
			break;
		case 6:
			if((lenght+x) < 21)
				check_len = 0;
			break;
		case 7:
			if( ((x+2) > lenght) && ((y+2) > lenght))			
				check_len = 0;
			break;
		case 8:
			if((y+2) > lenght)
				check_len = 0;
			break;
		case 9:
			if( ((y+2) > lenght) && ((lenght+x) < 21) )
				check_len = 0;
			break;
		default:	
			check_len = 1;
	}
	return check_len;	
}
/*===============================================================================================*/
int check_free_box(int dr,int lenght,int x,int y, char tablo[SIZE_ROW][SIZE_COL]){

	int check_free = 0,i;		// if check_free = 0  it shows us free area 
								// if check_free = 1  it shows us filled area 	
	switch(dr){
		case 1:
			for(i=0; i<lenght; i++){		//Koyulacak yeni kelimenin yerinin onceden baska bir
				if(tablo[y][x] != '.')		//kelime tarafindan alinmadigini kontrol ediyor
					check_free = 1;				
				x--;	y++;
			}								//To check every place letter of word
			break;
		case 2 :
			for(i=0; i<lenght; i++){
				if(tablo[y][x] != '.')		//These are same process
					check_free = 1;		
				y++;
			}
			break;
		case 3:
			for(i=0; i<lenght; i++){
				if(tablo[y][x] != '.')
					check_free = 1;		
				y++;	x++;
			}
			break;
		case 4:
			for(i=0; i<lenght; i++){
				if(tablo[y][x] != '.')
					check_free = 1;		
				x--;
			}
			break;
		case 6:
			for(i=0; i<lenght; i++){
				if(tablo[y][x] != '.')	
					check_free = 1;		
				x++;
			}
			break;
		case 7:
			for(i=0; i<lenght; i++){
				if(tablo[y][x] != '.')
					check_free = 1;			
				x--;	y--;
			}
			break;
		case 8:
			for(i=0; i<lenght; i++){
				if(tablo[y][x] != '.')	
					check_free = 1;		
				y--;
			}
			break;
		case 9:
			for(i=0; i<lenght; i++){
				if(tablo[y][x] != '.')	
					check_free = 1; 		
				x++;	y--;
			}
	}
	return check_free;
}
/*===============================================================================================*/
void fill_free(char (*tablo)[SIZE_COL]){

	for(int i=0; i<SIZE_ROW; i++){
		for(int j=0; j<SIZE_COL; j++){			//This func put random character on free area on tablo
			if(tablo[i][j] == '.')				//betwenn a-z	
				tablo[i][j] = get_random_character();
		}
	}
}
/*===============================================================================================*/
void play_game(char (*tab)[SIZE_COL],char (*word)[mx_word_leng],char key_ch[num_of_keys],int key_nu[num_of_keys],int key_dr[num_of_keys],int key_ln[num_of_keys]){

	int  i,j, flag=1,
		 sayi, 
		 point=0, 
		 correction;

	char get_str[30] = {0},
		 get_word[15] = {0},
		 adress;

	key_word_correction(word);									//Delete the last char '\n' en of words
	printf("If you want to exit please enter 'Exit' or 'exit' \n");
	print_grid(tab);											//print grid and all word	
	for(j=0; j<num_of_word; j++)	
		printf("%s\n",word[j] );
		
	while(flag && point != 10){ 													// if all words is found or print Exit the loop is done
		
		correction = 0;
		printf("===============================================================\n");		
		printf("Plese enter a koordinate and word = ");								//Take answer from user
		fgets(get_str,20,stdin);

		if((get_str[0] == 'E' || get_str[0] == 'e') && get_str[1] == 'x' && get_str[2] == 'i' && get_str[3] == 't' ){
			flag = 0;											 										 //If the user wants to exit flag = 0 
			printf("You have got %d points\nSee you...\n",point); 										//The number of knowed word
		}	
		else{
			printf("===============================================================\n");		
			sscanf(get_str,"%c%d%s",&adress,&sayi,get_word);											//We seperate the get_str according to the 
																										//syntax of answer  ex: "A13 allow"
			for(i=0; i<10; i++){	
				
				if(adress == key_ch[i] && sayi == key_nu[i]){									//If the matched koordinate of any koordinate	
					correction = check_correttion(get_word,word[i]);							//We check the word is true?
																								//If the word macth the coordinate correction=1
					if(correction){
						put_grid(word[i],tab,key_dr[i],sayi,adress-'A',key_ln[i],-32);					//We chance the upper case on table of the word which knowed
																										// -32 :   (a-32=='A')=1;  	
						for(j=0; j<key_ln[i]; j++)
							word[i][j] = word[i][j]-32;													//We chance the list upper case instead of low case of word
						point++;																		//incerase the point which knowed words

						printf("Welldone! You got : %d points\n",point);
						printf("===============================================================\n");		
						break;
					}
				}
			}
			if(correction == 0){																		//If the answer is not true		
				printf("Wrong answer ...\nTry again ...\n");
				printf("===============================================================\n");		
			}
		}
		if(flag){
			print_grid(tab);																			//print grid and all word	
			for(j=0; j<num_of_word; j++)	
				printf("%s\n",word[j] );
		}		
	}
	if(point == 10)
		printf("\n!!!!!  WELL DONE YOU FIND OUT ALL ANSWER   !!!!!\n");
}
/*===============================================================================================*/
int check_correttion(char get_str[mx_word_leng],char corret_str[mx_word_leng]){

	int flag=0;						//if flag = 1 corret_str same get_str
	if(strcmp(get_str,corret_str) == 0)	
		flag=1;
	return flag;
}
/*===============================================================================================*/
void key_word_correction(char word[num_of_word][mx_word_leng]){
	for(int i=0;i<num_of_word;i++)
		word[i][my_strlen(word[i])] =0;		//Delete the last char '\n' en of words
}
