#include <stdio.h>
#include <stdlib.h>

void menu();
void read_news(char buffer[500] ,char file_path[10] ,int is_Only_Title);
void append_file(char* file_path, char c);
void print_title();
void read_magic_numbers(char buffer_magic[10],char buffer_news[500]);
double f_func(int x);
double g_func(double f(int x), int a);

void main(){
	menu();
}
/*==============================================================================================================*/
void menu(){

	double magic_sum = 0;
	char operation,
		 choose_a,
	     choose_b,
	     choose_c;
	char buffer_news[500] = {0};
	char buffer_magic[10] = {0};     

	print_title();									// Basliklari yazdiriyor aciklama fonksiyon iscerisnde

	while(1){
		printf("What do you want to do?\n");
		printf("a.Read a new\n");
		printf("b.List the readed news\n");
		printf("c.Get decrypted information from the news\n");
		scanf(" %c",&operation);

		switch(operation){		
		/**/case 'a':
				printf("Which do you want to read : ");
				scanf(" %c",&choose_a);

				while(choose_a != '1' && choose_a != '2' && choose_a != '3' && choose_a != '4' ){
					printf("-----------Invalid character \nPlase enter a valid character :  ");		//Kullanici gecerli bir karakter girene kadar 
					scanf(" %c",&choose_a);															//kullanicidan sayi istiyor
				}	
				append_file("readed_news_id.txt", choose_a);										//A secenegi icin gereken paremetreler	1.Dosyanin okunup okunmadigi
				break;																													//  2.Istenilen dosya

		/**/case 'b':
				append_file("readed_news_id.txt",operation);										//Okunan dosyalarin fonksiyonu
				printf("Do you want to continue? Yes(y)/No(n) :");	
				scanf(" %c",&choose_b);
				
				if(choose_b == 'n'){
					printf("Good Bye!!\n");								//eger kullanici cikmak isterse program sonlaniyor
					exit(0);
				}
				else if(choose_b == 'y');											//Devam etmek isterse 
				else printf("---------------------Invalid character\n");			//Gecersiz karakter girerse ekrana yazdiriliyor program devam ediyor			
				break;

		/**/case 'c':
				printf("Which new would you like to decrypted : ");
				scanf(" %c",&choose_c);

				while(choose_c != '1' && choose_c != '2' && choose_c != '3' && choose_c != '4' ){		//Kullanici hatali bir input girerse dogru olana kadar  	
					printf("-----------Invalid character \nPlase enter a valid character :  ");			//kullanici uyarip input aliyor
					scanf(" %c",&choose_c);
				}	
				switch(choose_c){	
					case '1':	read_news(buffer_news,"news/1.txt",0);				// Cozulmek istenen metine gore buffer_news metin ile dolduruluyor
							break;													//Bu metin sonradan read_magic_numbers fonksiyonuna gonderilecek
					case '2': 	read_news(buffer_news,"news/2.txt",0);
							break;
					case '3': 	read_news(buffer_news,"news/3.txt",0);
							break;
					case '4': 	read_news(buffer_news,"news/4.txt",0);
				}

				read_magic_numbers(buffer_magic,buffer_news);						//buffer_news icerisindeki sihirli sayilar buffer_magic dizine koyuluyor 

				for(int i=0;i<10 && buffer_magic[i] != '\0';i++)					//buffer_magic sonuna kadar o sayiyla ilgili fonksiyonel islemler icin 
					magic_sum += g_func(f_func,buffer_magic[i] - '0');				//sayilar sirasiyla fonksiyona gonderiliyor

				switch(choose_c){	
					case '1':	printf("The number of test performed = ");			//Secilen metine gore yazi yazdirilip ardindan metinde sakli 
							break;
					case '2': 	printf("The number of sick people = ");
							break;
					case '3': 	printf("The number of deaths = ");
							break;
					case '4': 	printf("The expected number of sivk people = ");
				}
				printf("%.2lf\n",magic_sum);										//sayi yazdiriliyor
				magic_sum = 0;														//Toplam her seferinde yazdirildiktan sonra sifir olamli yoksa onceki ile toplar yanlis sonuc cikar
				break;
			default:
				printf("---------------------------Invalid character !!!\n");		//Kullanici yanlis karakter girerse uyarir
				printf("--------------Please enter a valid character !!!\n");
		}	
	}	
}
/*=================================================================================================================*/
void print_title(){

	char krktr;
	char files[4][11] = {"news/1.txt","news/2.txt","news/3.txt","news/4.txt"};		//Dosya dizinleri 2 boyutlu diziye aktarilip daha efektif kullanmak isteniyor

	FILE *read_titles;

	printf("*****************Daily Press*****************\n");
	printf("Today's news are listed dor you : \n");

	for(int i=0;i<4;i++){

		printf("Title of %d. news :",i+1);				//Metin numarasina gore sirasiyla acilip	
		read_titles = fopen(files[i],"r");	

		while(1){

			fscanf(read_titles,"%c",&krktr);
			if(krktr == '\n')							//Ilk satir bitene kadar yani newline'a kadar karakter karakter okunup yazdiriliyor her metin sirasiyla
				break;
			printf("%c",krktr);
		}
		printf("\n");						//Her baslik arasi yeni satira geciliyor
	}
	fclose(read_titles);
}
/*====================================================================================================================*/
void append_file(char* file_path,const char c){
	int i = 0, j,
		flag = 1;
	char id[8] = {0}, 				 //Okunan dosya nolarini tutuyor
		 buffer[500] = {0};
	char or = '0';	 

	FILE *read_before;
	read_before = fopen(file_path,"r");

	fscanf(read_before," %c",&id[i]);

	while(!feof(read_before)){
		
		if(c == 'b') 
			printf("%c. new is readed\n",id[i] );		//Kullani sadece b secenigini sectiginde kullaniliyor
		
		i++;											//Ama her halukarda metinden sayilar okunup diziye aktariliyor 	
		fscanf(read_before," %c",&id[i]);				//daha ilerde eger secenek a ise dosyanin istenilen dosyanin okunup okunmadigi kontrol ediliyor
	}
	fclose(read_before);								//Dosya okunmayan haberleri eklemek icin yeni mod ile acmak gerekecegi icin kapatiliyor		

	read_before = fopen(file_path,"a");					//Dosya add modunda aciliyor

	for(j=0;j<i;j++){
		if(c == id[j]){
			flag = 0;									//Eger c yani istenilen metin readed_news.txt icerisindeki herhangi bir karaktere denk ise 
			break;										//flag 1 oluyor buda bize bu sayi ile ilgili iki bilgi veriyor
		}												//1. Bunu yani istenilen news i readed_news.txt eklemeye gerek yok
	}													//2. Kullaniciya soracagimiz tekrar okumak istermisinz sorusunu yoneltmeyi sagliyor
		
	if(c != 'b'){		//Yeni haber okunmak istendiginde giriyor yani secenek a ise 
		if(flag){
			fputc(c,read_before);				//Eger istenilen metin daha onceden okunmamis ise readed_news.txt e metin numarasi ekleniliyor
			fclose(read_before);
		}
		else{
			printf("This new is readed.\nDo you want to read again? Yes(1) / No (0) : ");		//Okunma durumunda ise tekrardan okumak istiyormu diye soruluyor
			scanf(" %c",&or);
		}
		if(or == '1' || flag ){				//Eger tekrardan okumak istiyorsa veya daha onceden hic okunmadiysa giriliyor

			switch(c){	
				case '1':	read_news(buffer,"news/1.txt",or);			// eger tekrardan okunuyorsa yani or 1 ise sadece icerik eger ilk okuma ise baslik dahil
							break;										// istenilen metin buffer a konuluyor	
				case '2': 	read_news(buffer,"news/2.txt",or);
							break;
				case '3': 	read_news(buffer,"news/3.txt",or);
							break;
				case '4': 	read_news(buffer,"news/4.txt",or);
			}
			printf("%s\n\n",buffer);									// HABER YAZDIRILIYOR
		}
		else if(or == '0')										//Kullanici tekrardan okumak istemediginde cikiliyor
				printf("Exiting from chosse a...\n\n");
		else	printf("Invalid character\n\n");
	}
}
/*==============================================================================================================*/
void read_news(char buffer[500] ,char file_path[10] ,int is_Only_Title){

	int i=0;
	char *new;
	char as;
	
	FILE *fptr;
	new = buffer;		//buffer pointer a atanip menu fonksiyonu icersine etki etmemize olanak sagliyor

	if((fptr = fopen(file_path,"r")) == NULL)
		printf("%s cannot open plase check the file\n",file_path);

	if(is_Only_Title){
		fscanf(fptr,"%c",&as);				//Eger is_Only_title 1 ise ilk satiri yani basligi yazdirmadan okuyor
		while(as != '\n'){
			fscanf(fptr,"%c",&as);
		}									
	}
													
	fscanf(fptr,"%c",&new[i]);				//Eger 0 ise tum dosyayi sonuna kadar okuyup yazdiriyor

	while(!feof(fptr)){
		i++;	
		fscanf(fptr,"%c",&new[i]);
	}
}
/*=====================================================================================================================*/
void read_magic_numbers(char buffer_magic[10],char buffer_news[500]){

	int m_count=0,i;
	char *ptr_magic;

	ptr_magic = buffer_magic;			//Menu icerisinde etki etmemizi sagliyor

	printf("%s\n",buffer_news );		//Ilk olarak menuden alinan metin yazdiriliyor

	for(i=0;i<500;i++){
		if(buffer_news[i] == '#'){			//Eger # karakteriyle karsilasildiysa bir sonraki karakter pointer dizisine aktariliyor
			ptr_magic[m_count] = buffer_news[i+1];
			m_count++;
		}
	}
	printf("\n");
}
/*=====================================================================================================================*/
double f_func(int x){
	double result = x*x*x - x*x + 2;			//f fonksiyonu kurali
	return result;
}
/*=====================================================================================================================*/
double g_func(double f(int x), int a){	
	double result = f(a)*f(a);				//g fonksiyonu kurali
	return result;
}