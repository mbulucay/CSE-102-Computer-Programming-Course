/* ------------------------ */	
//	Muhammed Bedir ULUCAY 	*/
//	1901042697				*/
//	CSE 102        HW1		*/
/* ------------------------ */
#include <stdio.h>
#include <math.h>

void find_root();
void find_newtonian_root();
int find_multible_closest(int number_1,int number_2);

int main(){

	printf("===========PART 1============\n");	
		find_root();
	
//=================================================
	printf("===========PART 2============\n");

	printf("Your equation ");	
	find_newtonian_root();

//==================================================
	printf("===========PART 3============\n");

	int number_1,number_2,closest;

	printf("Enter the first integer : ");
	scanf("%d",&number_1);
	printf("Enter the first integer : ");
	scanf("%d",&number_2);

	closest = find_multible_closest(number_1,number_2);
	
	if(closest == number_1)							//Gerceklesebilecek olasiliklara gore ikiye ayiriyoruz
		printf("Closest number to %d that is multiple of %d is itself\n",number_1,number_2);	//Number_1 Number_2 nin kati olabilir bu yuzden kendisi cikacak
	else
		printf("Closest number to %d that is multiple %d is %d\n",number_1,number_2,closest);	//Diger secenekler icin closeset zaten en yakin degeri aliyor fonksiyondan			

	return 0;
}
//========================================================================================

void find_root(){

	float x_1,x_2,delta;
	int a,b,c;

	printf("Please, Enter the first coefficient : ");
	scanf("%d",&a);	
	printf("Please, Enter the second coefficient : ");
	scanf("%d",&b);
	printf("Please, Enter the third coefficient : ");
	scanf("%d",&c);

	printf("Your equation ");
	
	if(b>=0 && c>=0)						//
		printf("%dx^2+%dx+%d ",a,b,c);		//	
											//
	else if(b<=0 && c>=0)					//
		printf("%dx^2%dx+%d ",a,b,c);		//	
											//	Sayilarin isaretlerine gore uygun denklem yaziliyor
	else if(b>=0 && c<=0)					//
		printf("%dx^2+%dx%d ",a,b,c);		//	
											//		
	else if(b<=0 && c<=0)					//
		printf("%dx^2%dx%d ",a,b,c );		//	

										//Matematik formulleri
	
	delta = (b*b)-(4*a*c);              //Formulden delta hesaplanip
										
	if(delta < 0){
		printf("does not have any real roots\n"); 	//negatif ise kok bulunmadi 
	}
	else{
		delta = sqrt(delta);						//pozitif ise yine matematik islemleri yapilip
		x_1 = (-b + delta)/(2*a);					//Yazdiriliyor
		x_2 = (-b - delta)/(2*a);
		printf("have real roots{%.1f,%.1f}\n",x_1,x_2);
	}
}
//========================================================================================

void find_newtonian_root(){

	int i=1,a,b,c;						//Katsayilar ve sayac
	float f_x,tf_x,different,initial;	//Matematiksel islemler icin gerekli degiskenler
	float x_1,x_2,lnght_1,lnght_2;      //Kokler ve initial arasi mesafe degiskenleri
	float delta,close;					//close yakin kok

	printf("Please, Enter the first coefficient : ");
	scanf("%d",&a);	
	printf("Please, Enter the second coefficient : ");
	scanf("%d",&b);
	printf("Please, Enter the third coefficient : ");
	scanf("%d",&c);
	printf("Please,Enter the initial : ");
	scanf("%f",&initial); 

	if(b>=0 && c>=0)						//
		printf("%dx^2+%dx+%d ",a,b,c);		//
											//
	else if(b<=0 && c>=0)					//
		printf("%dx^2%dx+%d ",a,b,c);		//
											//	Sayilarin isaretlerine gore denklem yaziliyor
	else if(b>=0 && c<=0)					//
		printf("%dx^2+%dx%d ",a,b,c);		//
											//
	else if(b<=0 && c<=0)					//
		printf("%dx^2%dx%d ",a,b,c );		//

	printf("and iterations are\n\n");

	delta = (b*b)-(4*a*c);

	x_1 = (-b + (sqrt(delta))) /(2*a);
	x_2 = (-b - (sqrt(delta))) /(2*a);

	lnght_1 = initial - x_1;		//Koklerin initiale olan uzakligi hesaplaniyor
	lnght_2 = initial - x_2;

	if(lnght_1<0)
		lnght_1 = lnght_1*-1;	//
	if(lnght_2<0)				//Koklerin initiale olan uzakligi daha saglikli olsun diye
		lnght_2 = lnght_2*-1;	//negatif varsa pozitife ceviriliyor	

	if(lnght_2 > lnght_1)
		close = x_1;			//
	else 						//Different islemi icin initial'e yakin olan kok aliniyor
		close = x_2;			//	

		
	printf("Step    x\t  f(x)\t\tDifference\t\n");
	printf("--------------------------------------------\n");

	f_x = (a*initial*initial) + (b*initial) +c; 		
	tf_x = (2*a*initial ) + b;													//Newton_root formulune gore matemetiksel islemler yapiliyor
	initial = initial - (f_x/tf_x);												//initiale ilk alinan sayinin getirdigi sonuc tekrar initiale
																				//gonderiliyor   islem 5 kez tekrar ediyor
	f_x = (a*initial*initial) + (b*initial) +c;
	different = initial-close;	
	printf("x%d     %06.4f\t  %06.5f\t %06.4f\t\n",i,initial,f_x,different );	
	
	i++;
	f_x = (a*initial*initial) + (b*initial) +c; 		
	tf_x = (2*a*initial ) + b;
	initial = initial - (f_x/tf_x);
	f_x = (a*initial*initial) + (b*initial) +c;
	different = initial-close;	
	printf("x%d     %06.4f\t  %06.5f\t %06.4f\t\n",i,initial,f_x,different );	
	
	i++;
	f_x = (a*initial*initial) + (b*initial) +c; 		
	tf_x = (2*a*initial ) + b;
	initial = initial - (f_x/tf_x);
	f_x = (a*initial*initial) + (b*initial) +c;
	different = initial-close;	
	printf("x%d     %06.4f\t  %06.5f\t %06.4f\t\n",i,initial,f_x,different );	
	
	i++;
	f_x = (a*initial*initial) + (b*initial) +c; 		
	tf_x = (2*a*initial ) + b;
	initial = initial - (f_x/tf_x);
	f_x = (a*initial*initial) + (b*initial) +c;
	different = initial-close;	
	printf("x%d     %06.4f\t  %06.5f\t %06.4f\t\n",i,initial,f_x,different );	
	
	i++;
	f_x = (a*initial*initial) + (b*initial) +c; 		
	tf_x = (2*a*initial ) + b;
	initial = initial - (f_x/tf_x);
	f_x = (a*initial*initial) + (b*initial) +c;
	different = initial-close;	
	printf("x%d     %06.4f\t  %06.5f\t %06.4f\t\n",i,initial,f_x,different );	
}
//=========================================================================================

int	find_multible_closest(int number_1,int number_2){

	int div,close;
	int result_1,result_2;
	
	div = number_1 / number_2;	//Sayilari bolerek en yakin kucuk katsayiyi integer 
								//cinsinden buluyoruz yani div bize number_2 nin number_1 icerisinde 
								//Tam olarak kac tane oldgunu veriyor 
										
	result_1 = div *number_2;		//Bunu da div ve div+1 ile carparak number_1 i 
	result_2 = (div+1) *number_2;	//Number_2 nin katsayisi olarak result_1 ve result_2 
									//arasina aliyoruz

	//Bu islemlerden sonra kesin olarak bildigimiz sey  result_2 > number_1 > result_2

	if(result_2-number_1 == number_1-result_1)
		close = result_2;
	else if(result_2-number_1>number_1-result_1) //3 sayi arasindaki uzakliklari karsilastirarak
		close = result_1;						 //Number_1 e yakin olan sayiyi geri gondermek icin
	else										 //close un icine atiyoruz	ve main fonksiyonuna gonderiyoruz			
		close = result_2;

	return close;							
}
//===============================================================================================================
