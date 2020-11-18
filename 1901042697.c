#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

void menu();

void decrypt_and_print(char* file_path);		//PART 1
void deep_decrypt_and_print(char* file_path);	//PART 2
char decrypt__numbers(int number);				//PART 1/2

void  encrypt_messages   (char* file_path);		//PART 4	
int   encrypted_character(char character,int num1,int num2);//PART 4

void track_machine();							//PART 3
void refresh_position(int *X,int *Y,double *D,double *R);//PART 3

int main()
{
	menu();
}
/*============================================================================================================*/
void menu(){

	int choice;

	while(1){

		printf("1-) Decrypt and print encrypted_p1.img \n");
		printf("2-) Decrypt and print encrypted_p2.img \n");
		printf("3-) Switch on the tracking machine \n");
		printf("4-) Encrypt the message \n");
		printf("5-) Switch off\n");
		printf("Please make your choice\n");
		scanf("%d",&choice);

		if(choice == 1)														//Apply to choice according to the choice
			decrypt_and_print("encrypted_p1.img");
		else if(choice == 2)
			deep_decrypt_and_print("encrypted_p2.img");
		else if(choice == 3)		
			track_machine();
		else if(choice == 4)
				encrypt_messages("decrypted_p4.img");
		else if(choice == 5)
			break;
		else
			printf("***UNDIFINED CHARACTER***\nPlease make another choice\n");
		
		printf("\n");
	}	
}	
/*================================================================================================================*/
void decrypt_and_print(char* file_path){
	
	int count=0,	
		number;
	char character;	

	FILE *read;
	read = fopen(file_path,"r");

	if(read == NULL)
		printf("There is a problem encrypted_p2.img.Check the file \n"); 	//If the file cannot open showing the user

	while(fscanf(read,"%1d",&number) != EOF){	//This is scaning the end of file of encrypted__p1.img	

		if(count%99 == 0)					//Each line of file contain 99 number so there is a counter for each loop
			printf("\n");					//When the count k*99 after that new shape print new line

		character = decrypt__numbers(number);	//We sending number from file (encrypted__p1.img) function gives us a character according to the rule	
		printf("%c",character );				//geting charecter printing	
		count++;	
	}
	printf("\n");

	fclose(read);
}
/*=================================================================================================================*/
void deep_decrypt_and_print(char* file_path){
	
	int send_number;
	char get_chracter,num1,num2,num3;			
	
	FILE *read2;
	read2 = fopen(file_path,"r");

	if(read2 == NULL)
		printf("There is a problem encrypted_p2.img.Check the file \n");  //if the file cannot open shows the user

	while(1){		//We need to do formul of part 2,each time we need 3 number with queue 

		fscanf(read2,"%c",&num1);	//first number	

			if(num1 == '\n'){					//if fisrt number == '\n' we are taking num1 again because 
				printf("\n");					//we arange the new line of first character = num1		and print new line
				fscanf(read2,"%1c",&num1);
			}

		fscanf(read2,"%c",&num2);	//seconf number
		fscanf(read2,"%c",&num3);	//third number

			if(num2 == '\n'){		//when the num2 == 0  the rule says as to don't lose data of end of line character
				num2='0';			//we are doing an arragment
				num3='0';
			}
			if(num3=='\n'){			//To dont lose data line of two character
				num3='0';			//num3=0 must be zero 
			}
			if(feof(read2))			//When the came end of the line  the loop breaking
				break;

		send_number = (num1 + num2 + num3) - (3*'0');	//When we read as character so we need to use ASCII table decimal value of numbers
		send_number%=7;									//If after the operation if send_number>7 we are doing mod as from as want
		
		get_chracter = decrypt__numbers(send_number);	//We send the number then get a character according to the rule	
		printf("%c",get_chracter);						//It is printing	

		fseek(read2,-2,SEEK_CUR);						//And we need to go back two steps for each time because we are caculating number two step back
	}	
	printf("\n");

	fclose(read2);
}
/*==================================================================================================================*/
char decrypt__numbers(int number){

	char character;
											//These are return of number as character
	switch(number){

		case 0:
			character = ' ';   break;
		case 1:
			character = '-';   break;
		case 2:
			character = '_';   break;
		case 3:
			character = '|';   break;
		case 4:
			character = '/';   break;	
		case 5:	
			character = '\\';  break;
		case 6:
			character = 'O';   break;
		default:
			printf("-------UNKNOWN NUMBER--------\n");		//If there is a mistake at file is is shows usz
	}
	return character;
}
/*===================================================================================================================*/
void track_machine(){

	char command;
	int i,j,
		x_e = 1,	//	initial position
		y_e = 1;		

	double r = 0 , d = 8.48; //fisrt values

	while(1){

		for(i=1;i<12;i++){     			//Printing map
			for(j=1;j<12;j++){

				if(x_e == i && y_e==j)	//Place of enemies
					printf("E\t");
				else if(i==6 && j==6)	//Place of us
					printf("O\t");
				else
					printf(".\t");		//Other place of map	
			}
			printf("\n");
		}

		printf("Enemies X position %d, Y position: %d, ",x_e,y_e);	
		printf("Displacement: %.2lf, Distance to our camp: %.2lf ",r,d);	
		printf("\n");
		printf("Command Waiting ...:");
		scanf(" %c",&command);

		if(command == 'R')
			refresh_position(&x_e,&y_e,&d,&r);	//We sending the adres of number because the function parameters has *ptr so we are doing  like call by adress 
		else if(command == 'E')	//Enf of the loop
			break;
		else
			printf("\n-----!!!  Unknown Chararecter Please Enter Again  !!!-------\n");

		printf("\n");
	}	
}
/*====================================================================================================================*/
void refresh_position(int *X,int *Y,double *D,double *R){

	int past_x = *X,
		past_y = *Y;

	srand(time(NULL));

	*X = rand()%10+1;			//	Random, location
	*Y = rand()%10+1;			//	in maps

	*R = sqrt( ((past_x-*X)*(past_x-*X)) + ((past_y-*Y)*(past_y-*Y)) ); //Calculete the change of enemy position diffrent
	*D = sqrt( ((*X-6)*(*X-6)) + ((*Y-6)*(*Y-6)) );						//Calculate the distance of our camp
}
/*=====================================================================================================================*/
void encrypt_messages(char* file_path){
	
	int  num1=0,num2=0,num3,flag=0;
	
	char get_character;	 

		FILE *read4,*write; 
	
		read4 = fopen(file_path,"r");				//Opening the file decrypted_p4.img
		write = fopen("encrypted_p4.img","w");		//Opening the file encrypted_p4.img

		if(read4 == NULL)
			printf("There is a problem file decrypted_p4.img\n");
		if(write == NULL)
			printf("There is a problem will make encrypted_p4.img  \n");

		while(fscanf(read4,"%c",&get_character) != EOF){

			while(get_character == '\n'){
				
				fprintf(write,"%c",get_character);		//When we came to the end of line to don't make	
				fscanf(read4,"%c",&get_character);		//mix the operations 
				
				num1=0;							//Each line num1 and num2 must be zero 			
				num2=0;							//According to the rule
				if(feof(read4)){
					break;
				}
			}	

			if(feof(read4)){					//if file end the loop is breaking
					break;
			}	

			num3 = encrypted_character(get_character,num1,num2);	//We are sending character which are getting from file then the function 	
																		//give us a number
			fprintf(write,"%d",num3);								//We print number each time execpt charecter != '\n'

			num1 = num2;											//Each time pointer move next charecter so we need to move
			num2 = num3;											//number a step because before pointer location sum of theree number % 7  
																		//(We are arrange the mod in encrypted_charecter function)
		}

		printf("\n--File Created (encrypted_p4.img) in same directory \n");		//If print file succesfully it is printing

	fclose(write);
	fclose(read4);	
}
/*=====================================================================================================================*/
int encrypted_character(char character,int num1,int num2 ){

	int sum,ret_val;

	switch(character){

		case ' ':
			sum = 0;						
			ret_val = sum - (num1 + num2);   break;		//This is formul of ex:  ' ' = 0  we know that   	
		case '_':															//--- three if the character = ' ' sum = 0
			sum = 2;														//      15-   num1 =1 	num2 =5  num=?     (num1+2+3)%7 = 0 so 
			ret_val = sum - (num1 + num2);   break;							//      so rel_val = num3    (1+5+relvat)%7=0 rel_val = -6 or 1 
		case '|':															//If the result is negative we are sum with seven until being it is positive				
			sum = 3;   														//with loop
			ret_val = sum - (num1 + num2);   break;
		case '/':
			sum = 4;   
			ret_val = sum - (num1 + num2);   break;
		case '\\':	
			sum = 5; 
			ret_val = sum - (num1 + num2);   break;
		default:
			printf("-------UNKNOWN NUMBER--------\n");
	}

	while(ret_val<0)											//This is the loop +7 until it is positive	
		ret_val+=7;

	return ret_val;
}
/*======================================================================================================================*/
