#include <stdio.h>
#include <math.h>

int draw_triangle(int side1,int side2,int side3);
void type_triangle(int side1,int side2,int side3);
int perimeter_triangle(int side1,int side2,int side3);
double area_triangle(int side1,int side2,int side3,int perimeter);

int number_lenght(int number);
int find_digits(int number,int index);

int main()
{
	//=============================== PART 1 =============================================
	printf("=======================   PART 1   =============================\n");
	
	int side_1,side_2,side_3;
	int status,perimeter;
	double area;
	
	printf("Please enter the sides of triangle(three integer) : ");
	scanf(" %d%d%d",&side_1,&side_2,&side_3);

	status = draw_triangle(side_1,side_2,side_3);

	if(status == 0){
		printf("-According to the triangle theorem, this trianle cannot be drawn.\n");
	}
	else if (status ==1){ //if triangle can draw these steps work, else not

		printf("-According to the triangle theorem, this triangle can be drawn.\n");
		type_triangle(side_1,side_2,side_3);

		perimeter = perimeter_triangle(side_1,side_2,side_3);
		printf("-The perimeter of the triangle : %d \n",perimeter);

		area = area_triangle(side_1,side_2,side_3,perimeter);
		printf("-The area of the tringle : %lf\n",area);
	}

	//=============================== PART 2 =============================================
	printf("=======================   PART 2   =============================\n");

	int number,lnght_num,index;

	printf("Enter a number (maximum 6 digits)\n");
	scanf("%d",&number);

	lnght_num = number_lenght(number);
	printf("Your number has %d digits\n",lnght_num);
	
	printf("When your number is written 100 times next to each other,\n");
	printf("Which digit of this number would you like to see? :  ");
	scanf("%d",&index);

	number = find_digits(number,index);

	printf("%d.th digit of the big number sequence %d \n",index,number );

	//=============================== PART 3 ==============================================
	printf("=======================   PART 3   =============================\n");

	double amount;
	char type_has_chance,type_chance;
	double tl=1.0,euro=6.69,dollar=6.14,money;


	printf("*****Welcome to ABC Exchange Office***** \n");

	printf("Enter your amount :\n");
	scanf("%lf",&amount);
	printf("\n");

	printf("Please select your currency :\n");
	printf("1. Turkish Lira\n");
	printf("2. Euro\n");
	printf("3. Dollar\n");

	scanf(" %c",&type_has_chance);

	switch(type_has_chance){

		case '1' : printf("You have %lf Turkish Liras\n",amount);
					break;
		case '2' : printf("You have %lf Euros\n",amount); 	 	//Check the type of money is true	
					break;										//and give the information about that
		case '3' : printf("You have %lf Dollars\n",amount); 			
					break;
		default : 	
			printf("Your selection is invalid\n");	
			return 0;
	}

	printf("Choose which currnecy you want to convert\n");
	scanf(" %c",&type_chance);		

	switch(type_has_chance){			//firstly we usin swicth case for what type money we have
										//Then go to case about what we have		
		case '1':

			switch(type_chance){			//if we select turkish lira we can convert to euro or dollar there is no one another option except invalid
											//this switch case about convert type of money
				case '2' :
					money =  amount/euro;						//Converting money
					printf("You have %lf Euros\n",money);		//Then show the user
					break;
				case '3' :	
					money = amount/dollar;
					printf("You have %lf Dollar\n",money);
					break;
				default : 
					printf("Your selection is invalid\n");
			}
			break;

		case '2':										//These are working same as first one

			switch(type_chance){

				case '1' :
					money = amount*euro;
					printf("You have %lf Turkish Liras\n",money);
					break;
				case '3' :
					money = amount*(euro/dollar);
					printf("You have %lf Dollar\n",money);
					break;
				default : 
					printf("Your selection is invalid\n");
			}
			break;

		case '3':								////These are working same as first one

			switch(type_chance){

				case '1' :
					money = amount*dollar;
					printf("You have %lf Turkish Liras\n",money);
					break;
				case '2' :
					money = amount*(dollar/euro);
					printf("You have %lf Euros\n",money);
					break;
				default : 
					printf("Your selection is invalid\n");
			}
			break;
	}


	return 0;
}
//########################################################################################

int draw_triangle(int side1,int side2,int side3){

	int status=0;
											//it is the rules of triangle inequality theorem 
	if(side1>=side2 && side1>=side3)		//determine the big side of trinagle
		if(side2+side3 > side1)				//the sum of the 2 side must be greater than 1 side
			status = 1;

	if(side2>=side1 && side2>=side3)		//We check all possibility if could be then return 1 in stasus
		if(side1+side3 > side2)
			status = 1;
		
	if(side3>=side1 && side3>=side2)
		if(side1+side2 > side3)
			status = 1;	

	return status;
}
//*=======================================================================================*/
void type_triangle(int side1,int side2,int side3){
															//There are three types triagle
	if(side1 == side2 && side1 == side3)					//Determine the equilateral triangle
		printf("-It is a equilateral triangle.\n");	
	else if(side1==side2 || side1==side3 || side2==side3)	//Determine the isosceles trinagle
		printf("-It is a isosceles triangle\n");
	else													//Not both of the above
		printf("-It is a scalene triangle\n");				//It must be scalene triangle 
}
//*=======================================================================================*/
int perimeter_triangle(int side1,int side2,int side3){

	int perimeter = side1+side2+side3;        //It is calculate the perimeter of triangle 
	return perimeter;	
}
//*=======================================================================================*/
double area_triangle(int side1,int side2,int side3,int perimeter){

	double area,p;

	p = (double) perimeter/2;							//We are using formul(side, perimeter) to calculete the area
	area = sqrt(p*(p-side1)*(p-side2)*(p-side3));		

	return area;
}
//########################################################################################

int number_lenght(int number){

	if(number==0)							//It is calculated how many digits are entered
		return 1;
	number = floor(log10(number)+1);
	return number;
}
//*=======================================================================================*/

int find_digits(int number,int index){

	int lnght_num,digit,solution,kalan;

	lnght_num = number_lenght(number);

	if(lnght_num == 1)		//this is special situation for number which has one digit
		return number;

	kalan = index % lnght_num;					//Bizden girilen sayinin hangi basamagini istegini bulmak icin kalani bulmak gerekiyor
															//Yukaridaki ve asagidaki islemden kazanmak icin
	if(kalan==0){								//Kalan sifir oldugunda birler basamagini donduruyor
		return number%10;
	}											
												//mod islemi yapip kalani buluyoruz kalan sayisi bizim soldan kacinci basamagin 
												//istendigini belirtiyor
	solution = pow(10,lnght_num-kalan+1); 	 	//Istenilen basamaktan onceki basamaklari goturmek icin uzunluktan
												//kalanin bir fazlasini cikarip 10 un ussu yapiyoruz  
	solution = number % solution;				//Burdada bi onceki buldumuz sayiya gore modunu alip gereken basamagin
												//onundeki sayilardan kurtuluyoruz 
 												//soldan ilk basamagi bizden dondurmemiz istenin basamak oluyor
	digit = solution / pow(10,lnght_num-kalan);	//Burada sayiyi sayinin basamak degerine bolerek kac adet o basamak degerine 
												//sahip oldugunu ogreniyoruz bu da bizden istenilen sayi oluyor
	return digit;
}
//*=======================================================================================*/
