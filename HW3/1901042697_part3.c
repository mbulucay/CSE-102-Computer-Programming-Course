#include <stdio.h>

int andop(int,int);  //And operasyonu sonucu sayiyi dondurmek
int lengt(int);		 //Bir sayinin uzunlugunu hesaplamak	
int check_all_digit(int);	//Sayidaki rakamlarin 1 veya 0 dan farkli olup olmadigini kontrol etmek
int return_digit(int,int);	//Her basamagi teker teker dondurmeyi dusunuyorum

int main(){
	
	int first_int,second_int,result;
	int lengt_1,lengt_2,value_a,value_b;

	while(1){

		printf("First integer : ");
		scanf("%d",&first_int);
		printf("Second integer: ");
		scanf("%d",&second_int);

		lengt_1 = lengt(first_int);		//1. binary sayinin uzunluk degerini sayi aliyor
		lengt_2 = lengt(second_int);	//2. binary sayinin uznuluk degerini sayi aliyor

		value_a = check_all_digit(first_int);	// Girilen sayi binary ise 0 degilse 1 donduryor
		value_b = check_all_digit(second_int);	// Binary kontrolu yapan fonksiyon

		if(  lengt_2 != lengt_1 )	//Uzunluklar esit olmadiginda
			printf("Integer should the same lenght,please enter 2 new integers.\n");
		else if(value_a || value_b)	//Sayi binary olmadiginda	
			printf("Integer should be binary, please enter 2 new integer\n");
		else{	//Bir sikinti yoksa islem yapiliyor
			result = andop(first_int,second_int);	//AND isleminin sonucunu aliyoruz
			printf("%d AND %d = %d\n",first_int,second_int,result ); //Istenilen formda yazdiriyoruz
			break;
		}
	}		
	return 0;
}
///*=======================================================================================================================*/
int andop(int a,int b){

	int number=0,pow=1;
	int digit;

	while(1){		//Dongu sayi bitimine kadar devam ediyor alt tarafta kosul saglaniyor

		digit = return_digit(a,b);
		a/=10;						//Gonderilen sayi her seferinde ona bolunup alinan birler basamagindan alinan digit bir daha alinmasin	
		b/=10;						//Yani alinan birler basamagi sayidan kaydirilip goturuluyor
		
		if(digit == 0)				//Digit 0 geldiginde us bir artirilmali cunku sonradan gelecek
			pow*=10;				//1 ler bu sifirlarin yerini almasin 	
		else{
			number += pow*digit;	//Denklem alinan digitlerle bir tam sayi oluturuyor
			pow*=10;
		}
	
		if(a==0)
			break;		//Sayi butun basamaklarina bakidiktan sonra sonsuz donguden cikartiliyor
	}
	
	return number;
}
///*=======================================================================================================================*/
int lengt(int num){			//Calculate the lengt of number

	if(num==0)				//When the number is equal to zero means that 
		return 0;			//all digit has calculated then finish the recursive func.
	else 
		return 1+lengt(num/10);	//if number still can divide 10 the value of lenght() func. is increasing +1 
}
///*=======================================================================================================================*/
int check_all_digit(int number){

	int digit;				
	int result=0;				//Digitlerin basamak basamak bakilip atilacagi yer

	while(1){

		digit = number%10;					//Birler basamaginin degerini aliyor

		if(digit != 0 && digit != 1){		// Basamak degeri 1 veya 0 dan farkliysa 
			result=1;						//Dondurulecek degeri 1 yapip ana fonksiyonda 
			break;							//gerekli kosulun icerisine girmesini sagliyor
		}
		number /= 10;						//Siradaki alinacak basamak degerini birler basamagina kaydiriyor

		if(number==0)						//Eger hicbir basamakta sikinti cikamazsa tum sayiyi kontrol ettikten 
			break;							//sonra donguden cikmamizi sagliyors
	}
	return result;
}	
///*=======================================================================================================================*/
int return_digit(int num_1,int num_2){

	int digit_1,digit_2,ret_digit=1;

	digit_1 = num_1%10;		//fonksiyon sayiyi her aldiginda 1 onceki halinin 10 a bolunmus halini aliyor
	digit_2 = num_2%10;		//ve her seferinde 1 ler basamagini alip

	if(digit_1 == 0 || digit_2 == 0)	//and kosuluna uyuyorsa 0 uymuyorsa 1 donduruyor
		ret_digit=0;

	return ret_digit;
}
///*=======================================================================================================================*/
