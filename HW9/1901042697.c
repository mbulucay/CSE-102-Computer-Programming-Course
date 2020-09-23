#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define location_num 4
#define max_var_city 50
#define max_word_len 10	
#define var_face 13
#define var_suits 4
#define var_card 52

void execute_1();
int numPathsHome(int street, int avenue);
int faktor = 1, adet, pay=1,
	payda_1 =1, payda_2 = 1;

void execute_2();
struct Hospital{
	char* name;
	char citiesServed[3];
};
int canOfferCovidCoverage(char _cities[6], char _locations[4][3], int _numHospitals, struct Hospital results[4]);
int result_off_all(char arr[max_var_city],char _cities[6]);
int* chance_loc(int *new,int size);
int* look_location;					//Lokasyon indexleri icin kullaniyoruz
char city_arr[max_var_city] = {0};		//Lokasyonlardaki sehirleri tutmak icin

void execute_3();
struct card {
	const char *face;
	const char *suit;
};
void fill_deck(struct card suit_face[var_card]);
void shuffle_deck(struct card suit_face[var_card]);
void print_deck(struct card mixed_deck[var_card]);
int get_random();

int main(){
	
	int ope;
	while(ope != 4){
		printf("==============================================\n");
		printf("1-) Part 1\n");
		printf("2-) Part 2\n");
		printf("3-) Part 3\n");
		printf("4-) Exit\n");
		printf("Please select an operation\n");
		scanf("%d",&ope);
		switch(ope){
			case 1:		execute_1();
				break;
			case 2:		execute_2();
				break;
			case 3:		execute_3();
				break;
			case 4:		printf("Program Closed\n");
				break;		
			default:
				printf("Unknown operation\nPlease enter valid operation\n");	
		}
	}
	return 0;
}
/*====================================================================================================================*/
void execute_1(){
	
	int street,avenue,
		fastest_way_adet;

	printf("Enter the street number : ");
	scanf("%d",&street);
	printf("Enter the avenue number : ");
	scanf("%d",&avenue);
	adet = street+avenue;  //Faktoriyel hesabi yapacagimiz icin street ve avenue nin toplam degerine ihtiyacimiz var
	fastest_way_adet = numPathsHome(street,avenue);
	printf("Number of optimal paths to take back home: %d\n",fastest_way_adet);
	faktor = 1;		//Her islem sonrasi olmasi gereken haline geri getiriliyorlar
	pay=1;
	payda_1 =1;
	payda_2 = 1;

}
/*====================================================================================================================*/
int numPathsHome(int street, int avenue){

	if(adet == 2)
		return pay/(payda_1*payda_2);
	if(avenue > 1)
		payda_1*=faktor;	//Burada avenue nin degerinin faktoriyelini hesapliyoruz
	if(street > 1)			//1 den buyuk olduklari surece heplaniyor cunku son konum 1,1 noktasi	
		payda_2*=faktor;	//Burada street degerinin faktoriyelini hesapliyoruz

	pay*=faktor;					//Her halikarda sona kadar gidecek olan yani adet(street + avenue) kadar donduruyoruz
	faktor++;						//Her seferinde carpim degeri artiriyoruz
	adet--;							//Kac kez recursive olacagina karar veriyoruz
	numPathsHome(street-1,avenue-1);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void execute_2(){

	int num_hospital, ret_val;
	char cities[6] = {'A', 'B', 'C', 'D', 'E', 'F'};
	char location[4][3] = {{'A', 'B', 'C'},{'A', 'C', 'D'},{'B', 'F'},{'C', 'E', 'F'}};
	struct Hospital values[4] = {0};


	printf("Enter the maximum number of hospitals that can be constructed: ");
	scanf("%d",&num_hospital);
	
	look_location = (int *)malloc(sizeof(int)*num_hospital);
	for(int i=0; i<num_hospital; i++)	
		look_location[i] = 0;

	if( num_hospital > location_num || num_hospital <= 0)		//Lokasyondan fazla deger girldiyse veya 0 veya negatif deger girilirse hata veriyor
		ret_val= -1;
	else
		ret_val = canOfferCovidCoverage(cities,location,num_hospital,values);	//Denemek icin veriler lokasyona gonderiliyor

	if(ret_val < 0)
		printf("Lokasyondan fazla hastane girdiniz veya negatif sayi girdiniz \n");
	else if(ret_val == 0)
		printf("No, some cities not covered\n");
	else{ 
		for(int i=0; i<num_hospital; i++){		//Eger kaplayan olasilik varsa doldurulmus degerleri yazdiriyor
			printf(">%s\n",values[i].name);
			printf("Hospital Locations : ");
			for(int j=0; j<3; j++)
				printf("%c ",values[i].citiesServed[j]);
			printf("\n");
		}
	}
}
/*====================================================================================================================*/
int canOfferCovidCoverage(char _cities[6], char _locations[4][3], int _numHospitals, struct Hospital results[4]){

	int point_1,point_2,point_3,point_4;
	int count=0;

	for(int i=0; i<max_var_city; i++ )	//Global oldugu icin her denemede sifirlanmasi gerekiyor
		city_arr[i] = 0;

	if(look_location[0] > 3){	//Recursive durdurma kosulu butun olasiliklarin denendigini gosteriyor
		return 0;
	}

	look_location = chance_loc(look_location,_numHospitals);	//Kontrol edilecek lokasyonu degistirmi sagliyor

	if(_numHospitals == 1){

		point_1 = look_location[1];		//Lokasyonun olasilik numarasininin bulundugu numarayi atiyoruz
		
		for(int i=0; i<3; i++){
			city_arr[count] = _locations[point_1][i];	//Aldigimiz numarayi kullanip lokasyon veya lokasyonlar icinde ki butun sehirleri tanimladigimiz 	
			if(city_arr[count] != 0)	count++;		//array icerisine atiyoruz
		}
		if(result_off_all(city_arr,_cities) == 6){		//Aldigimiz sehirler ile  _cities icersindeki butun sehirler dahilse yani cities icindeki sehir sayisi kadarsa 
			results[0].name = "Hastane_1";				//Bu butun sehirleri kapsadigini gosterir ve result icerisini dolduruyoruz
			for(int i=0; i<3; i++)		
				results[0].citiesServed[i] = _locations[point_1][i];
			return 6;		//Doldurulduktan sonra uygun degeri donduruyoruz
		}	
	}
	if(_numHospitals == 2){			//Kullanici 2 hastane insa etmek istediginde kullaniliyor

		point_1 = look_location[1];		//Olasilik degerlerini kullanip lokasyondaki sehirleri alacagiz
		point_2 = look_location[2];

		for(int i=0; i<3; i++){	
			city_arr[count] = _locations[point_1][i];	//Verilen olasilik numaralarina gore sehirleri aliyoruz
			if(city_arr[count] != 0)	count++;
		}
		for(int i=0; i<3; i++){
			city_arr[count] = _locations[point_2][i];
			if(city_arr[count] != 0)	count++;
		}
		if(result_off_all(city_arr,_cities) == 6){		//Aldigimiz sehirler ile  _cities icersindeki butun sehirler dahilse yani cities icindeki sehir sayisi kadarsa
														//Bu butun sehirleri kapsadigini gosterir ve result icerisini dolduruyoruz
			results[0].name = "Hastane_1";
			for(int i=0; i<3; i++)	
				results[0].citiesServed[i] = _locations[point_1][i];
			results[1].name = "Hastane_2";
			for(int i=0; i<3; i++)	
				results[1].citiesServed[i] = _locations[point_2][i];
			return 6;			//Uygun degeri donduruyoruz
		}
	}
	if(_numHospitals == 3){

		point_1 = look_location[0];		//Olasiliklarda bulunan degerlerin oldugu lokasyonlardaki sehirlerin
		point_2 = look_location[1];		//indexlerini aliyoruz
		point_3 = look_location[2];

		for(int i=0; i<3; i++){							//O lokasyonlari sirasiyla gecici arrayimize atiyoruz
			city_arr[count] = _locations[point_1][i];
			if(city_arr[count] != 0)	count++;
		}
		for(int i=0; i<3; i++){
			city_arr[count] = _locations[point_2][i];
			if(city_arr[count] != 0)	count++;
		}
		for(int i=0; i<3; i++){
			city_arr[count] = _locations[point_3][i];
			if(city_arr[count] != 0)	count++;
		}

		if(result_off_all(city_arr,_cities) == 6 ){		//Eger kapsanan sehirler ile cities icerisndeki sehirler ayni ise 
			results[0].name = "Hastane_1";				//Lokasyonlarin sehirlerini struct icersine atiyoruz	
			for(int i=0; i<3; i++)	
				results[0].citiesServed[i] = _locations[point_1][i];
			results[1].name = "Hastane_2";
			for(int i=0; i<3; i++)	
				results[1].citiesServed[i] = _locations[point_2][i];
			results[2].name = "Hastane_3";
			for(int i=0; i<3; i++)	
				results[2].citiesServed[i] = _locations[point_3][i];
			return 6;
		}
	}
	if(_numHospitals == 4){
		
		for(int i=0; i<3; i++){					//Gecici arraylere ataniyor
			city_arr[count] = _locations[0][i];
			if(city_arr[count] != 0)	count++;
		}
		for(int i=0; i<3; i++){
			city_arr[count] = _locations[1][i];
			if(city_arr[count] != 0)	count++;
		}
		for(int i=0; i<3; i++){
			city_arr[count] = _locations[2][i];
			if(city_arr[count] != 0)	count++;
		}
		for(int i=0; i<3; i++){
			city_arr[count] = _locations[3][i];
			if(city_arr[count] != 0)	count++;
		}	

		if(result_off_all(city_arr,_cities) == 6){	//Karsilastiriliyor eger tum sehirler kapsaniyorsa
			results[0].name = "Hastane_1";			//struct icerisine ataniyor
			for(int i=0; i<3; i++)	
				results[0].citiesServed[i] = _locations[0][i];
			results[1].name = "Hastane_2";
			for(int i=0; i<3; i++)	
				results[1].citiesServed[i] = _locations[1][i];
			results[2].name = "Hastane_3";
			for(int i=0; i<3; i++)	
				results[2].citiesServed[i] = _locations[2][i];
			results[3].name = "Hastane_4";
			for(int i=0; i<3; i++)	
				results[3].citiesServed[i] = _locations[3][i];	
			return 6;		//ve uygun deger donduruluyor
		}
	}

	canOfferCovidCoverage(_cities, _locations, _numHospitals, results);
}
/*====================================================================================================================*/
int result_off_all(char arr[max_var_city],char _cities[6]){

	int sayac=0,
	index=0,i=0,j=0;

	for(i=0; i<50; i++){		//string icerisindeki ayni elemanlardan varsa ikiden fazlasini siliyor
		for(j=0; j<i; j++){		//Esit degerin indexini bulmayi sagliyor
			if(arr[i] == arr[j])
				break;
		}
		if(j==i)
			arr[index++] = arr[i];
	}

	for(int i=0; i<6; i++){				//Alinan array ayiklandiktan sonra elimizdeki sehirlerin bulundugu array ile karsilastiriyoruz
		for(int j=0; j<6; j++){			
			if(arr[i] == _cities[j])
				sayac++;				//Eger ayiklana arrayde _cities icindeki eleman kadar varsa dogru olacak sonucu donduruyor
		}								//Aksi takdirde yanlis sonuc donduruyor
	}
	
	return sayac;
}
/*====================================================================================================================*/
int* chance_loc(int *new,int size){
	new[size-1]++;		//Her seferinde son karakteri artiriyoruz

	for (int i = size-1; i >=1 ; i--){
		if (new[i] > 3){	//Eger herhangi bir karakter lokasyon indexinden fazla ise 
				new[i]-=3;	//Ondan uc cikartip siradaki dizilim icin
				new[i-1]++;	//Bir eksik indextekini bir artirip siradaki olasilik bulunuyor
		}	
	}
	for (int i = 0; i < size-1; ++i){
		if(new[i+1] < new[i])		//Kontrol edilen bir olasiligin tekrardan farkli sekilde kontrol edilmemesi icin
			new[i+1] = new[i];		//Kucuk indexteki sayi buyuk ise kucuk sayiyi buyuk indexe atiyoruz
	}								//Ex :  123  ile 132 ayni bunun bir daha kontrol edilmemesini sagliyor
	return new;	
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void execute_3(){

	srand(time(NULL));
	struct card suit_face[var_card];
	fill_deck(suit_face);				//Desteyi butun kartlarla dolduruyoruz
	for(int i=0; i<10; i++)				//Desteyi 10 kez rastgele karistiriyoruz
		shuffle_deck(suit_face);
	print_deck(suit_face);				//Karilan desteyi yazdiriyoruz
}
/*====================================================================================================================*/
void fill_deck(struct card suit_face[var_card]){

	int count =0;
	char *suits[max_word_len] = {"Hearts", "Diamonds", "Clubs", "Spades"};
	char *faces[var_face]  = {"Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"} ;

	for(int i=0; i<var_suits; i++){			//Desteyi dolduruyoruz
		for(int j=0; j<var_face; j++){
			suit_face[count].suit = suits[i];
			suit_face[count].face = faces[j];
			count++;
		}
	}
}
/*====================================================================================================================*/
void shuffle_deck(struct card suit_face[var_card]){

	struct card temp;
	int random_num;	 

	for(int i=0; i<52; i++){		//Her seferinde rastgele alinan rakamla siraki karti yer degistiriyoruz
		random_num = get_random();
		
		temp.face = suit_face[i].face;
		temp.suit = suit_face[i].suit;
		suit_face[i].face = suit_face[random_num].face;
		suit_face[i].suit = suit_face[random_num].suit;
		suit_face[random_num].face = temp.face;
		suit_face[random_num].suit = temp.suit;
	}	 
}
/*====================================================================================================================*/
void print_deck(struct card mixed_deck[var_card]){

	for(int i=0; i<var_card; i++){			//Istenilen formatta yaziyoruz
	 	printf("%5s of %-7s\t",mixed_deck[i].face,mixed_deck[i].suit);
	 	if(i%2)
	 		printf("\n");
	}
}
/*====================================================================================================================*/
int get_random(){
	return rand()%52;
}	