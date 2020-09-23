#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define max_char_num 256
#define max_tree_lenght 50

typedef struct node{
	char symbol;
	int freq;
	struct node *left,*right;
}node;

typedef struct list{
	int size;
	int capacity;
	node **array;		
}list;

void fill_datas(char *filename, char ch_arr[], int freq_arr[], int *size);
int ret_char_index(char ch, char ch_arr[],int size); 

void Huffman_Codes(char ch_arr[],int freq_arr[],int size);
node *Create_Huffman_Tree(char ch_arr[],int freq_arr[],int size);
list *create_heap(char ch_arr[],int freq_arr[],int size);
list *creat_listh(int capacity);
node *make_node(char charecter, int freq);
void build_heap(list *heap);
void mheapfy(list *heap,int k);
void swap_node(node **x,node **y);
node *ext_heap(list *heap);
int check_is_Leaf(node *root);
void print_Huff_char_keys_recursive(node *root, int arr[], int top);
void add_top_of_tree(list *heap,node *root);
void writefile_encoded_dat_message_txt(char *filename_keys);
int return_char_tree_way_index(char char_keys[][max_tree_lenght],char wanted_chrctr,int size);
void encode_message_txt(char *filename,char keys_char[max_char_num][max_tree_lenght],
							char keys_ways[max_char_num][max_tree_lenght],int size);
void decode_encoded_bat(char *filename);
char return_char_in_key(char wanted[20],char keys_char[max_char_num][max_tree_lenght],
							char keys_ways[max_char_num][max_tree_lenght],int size);

void calculate_different_size_byte(char *filekey,char *filemessage);

int main(){

	char ch_arr[max_char_num];
	int freq_arr[max_char_num] ={0},
		size,size_1;
	
	fill_datas("reference.txt",ch_arr,freq_arr,&size_1);
	size = size_1 / sizeof(ch_arr[0]); 	//tree size	
	
	FILE *fptr;
	fptr = fopen("char_keys.txt","w");	//Eger program ikinci veya daha fazla calismak istenirse 
	fclose(fptr);						//harflerin sifrelemmis hali olan dosyayi temizliyor	

	Huffman_Codes(ch_arr,freq_arr,size);
	printf("Created Huffman_Tree\n");
	printf("Done part 1!\n\n");
	printf("char_keys.txt icerisinde karakterlerin yollari yazildi\n(\\ = \\n     $ = ' ' temsil ediyor)\n\n");
	/*
		Yukarda hufman tree yi olusturup char_keys.txt ye her harfin yolunu kaydettik
		Simdi bu yollari islemlerin daha anlasilabilir olmasi icin bir iki boyutlu 
		char arraya kayit edecegiz ve char buldukca encoded.bin icerisine yazacagiz 
	*/
	writefile_encoded_dat_message_txt("char_keys.txt");	//(encoded.bat)
	printf("Created encoded.dat file\n");
	printf("Done part 2!\n\n");

	/*
		encoded icerisine yazdik simdi encoded icerisine yazdigimizi decode etme vakti
		bunun icin yine char_keys.txt kullanacagiz ve encoded.bin kullanacagiz
		binary sayilari alip onlari karsilastirip bulunca harf karsiligini yazacagiz
	*/
	decode_encoded_bat("encoded.dat");
	printf("Created decoded.txt file\n");
	printf("Done part 3!\n\n");


	calculate_different_size_byte("char_keys.txt","message.txt");

	printf("DONE!\n");

	return 0;
}
/*=====================================================================*/
void fill_datas(char *filename, char ch_arr[], int freq_arr[], int *size){

	FILE *fp;
	char ch;
	int count = 0, index;

	if((fp = fopen(filename,"r")) == NULL)
		printf("Dosya Acilmadi\n");

	ch = fgetc(fp);
	index = ret_char_index(ch,ch_arr,count);
	while(!(feof(fp))){		//reference.txt icindeki charlar ile ch_arr ve her
							//karakterin kac tane oldugunu hesapliyoruz
		if(index == -1){	//ret_char_index = -1 dondururse bu bize yeni bir karakterle karsilastigimizi gosteriyor
			ch_arr[count] = ch;
			freq_arr[count]++;	//count yeni harf buldukca artiyor
			count++;
		}
		else
			freq_arr[index]++;//diger turlu ret_char_index = index donduruyor ve freq artiriliyor

		ch = fgetc(fp);
		index = ret_char_index(ch,ch_arr,count);//Karakterler gonderilip index bulunuyor
	}

	*size = count;
	fclose(fp);
}
/*=====================================================================*/
int ret_char_index(char ch, char ch_arr[],int size){

	int index = -1;
	for(int i=0; i<size; i++){//Eger daha onceden alinan karakter varsa onun
		if(ch == ch_arr[i]){//indexini donduruyor eger bulamassa -1 dondurup acilan yere		
			index = i;	//fill datas fonksiyonu icinde ch yi ch_arr icinde yaziyoruz
			i = size;
		}
	}
	return index;
}
/*=====================================================================*/
void Huffman_Codes(char ch_arr[],int freq_arr[],int size){

	node *root;
	root = Create_Huffman_Tree(ch_arr,freq_arr,size);

	int last_arr[max_char_num],
		str_index = 0;	//indexleri baslatma yeri

	print_Huff_char_keys_recursive(root, last_arr, str_index);	
}
/*=====================================================================*/
node *Create_Huffman_Tree(char ch_arr[],int freq_arr[],int size){

	node *left,*right,*root;
	list *heap;

	heap = create_heap(ch_arr,freq_arr,size);

	while(!(heap->size == 1)){

		right = ext_heap(heap);//Alinan degerler agaca eklenmek icin dugum geliyor
		left = ext_heap(heap);

		root = make_node('$',left->freq+right->freq);

		root->right = left;//Agacin dallarina ekleniyor
		root->left = right;
	
		add_top_of_tree(heap,root);//Agacin tepesine ekliyor
	}
	return ext_heap(heap);
}
/*=====================================================================*/
list *create_heap(char ch_arr[],int freq_arr[],int size){
	list *heap;
	heap = creat_listh(size);

	for(int i=0; i<size; i++)
		heap->array[i] = make_node(ch_arr[i],freq_arr[i]);//Her index degerini(char ve freq icin)
													//heap icerisine diziyoruz
	heap->size = size;
	build_heap(heap);	//yigin olusturuyoruz

	return heap;
}
/*=====================================================================*/
list *creat_listh(int capacity){
	list *heap = (list*)malloc(sizeof(list));
	heap->size  = 0;
	heap->capacity = capacity;//Tree nin capasitesi 
								//Yeni eleman eklendikce guncelleniyor
	heap->array = (node**)malloc(capacity * sizeof(node*));//Yer aciyoruz

	return heap;	//treenin en basini donduruyoruz
}
/*=====================================================================*/
node *make_node(char charecter, int freq){

	node *tmp = (node*)malloc(sizeof(node));	//Node icin yer aciyoruz

	tmp ->left =NULL;		//sagini ve solunu bos birakiyoruz
	tmp->right = NULL;
	tmp ->symbol = charecter;//struct icindeki char i ve freq i dolduruyoruz
	tmp ->freq = freq;

	return tmp;
}
/*=====================================================================*/
void build_heap(list *heap){

	int adet = heap->size - 1;
	for(int i=(adet-1)/2; i>-1; i--)
		mheapfy(heap,i);
}
/*=====================================================================*/
void mheapfy(list *heap,int k){
								//bulid_heap den gelen degerlere gore agac insa ediliyor
	int small = k;				//Agactaki degerlerin kucukluk buyukluk durumuna gore sekillendiriliyor
	int l_val = 2*k+1;
	int r_val = 2*k+2;

	if(l_val < heap->size && heap->array[l_val]->freq < heap->array[small]->freq)
		small = l_val;
	if(r_val < heap->size && heap->array[r_val]->freq < heap->array[small]->freq)
		small = r_val;

	if(small != k){
		swap_node(&heap->array[small],&heap->array[k]);		
		mheapfy(heap,small);
	}
}
/*=====================================================================*/
void swap_node(node **x,node **y){ 
	node *tmp = *x;		//tree icinde node degisimi yapiyoruz
	*x = *y;
	*y = tmp;
}
/*=====================================================================*/
node *ext_heap(list *heap){
	node *tmp = heap->array[0];
	int index = heap->size - 1;
	heap->array[0] = heap->array[index];
	heap->size -= 1;

	mheapfy(heap,0);

	return tmp;
}
/*=====================================================================*/
int check_is_Leaf(node *root) {
  return !(root->left) && !(root->right);
}
/*=====================================================================*/
void add_top_of_tree(list *heap,node *root){

	heap->size++;		//Tree nin tepesine node ekliyor
	int x = heap->size - 1;		

	while(x && root->freq < heap->array[(x-1) / 2] ->freq){
		heap->array[x] = heap->array[(x-1) / 2];
		x = (x-1) / 2;
	}
	heap->array[x] = root;
}
/*=====================================================================*/
void print_Huff_char_keys_recursive(node *root, int arr[], int top) {
  if (root->left) {		//eger sol tarafa giderse her char icin 1 ekleniyor
    arr[top] = 0;
    print_Huff_char_keys_recursive(root->left, arr, top + 1); //top+1 eklenecek arr indexini artiriyor
  }
  if (root->right){ 
    arr[top] = 1;		////eger sag tarafa giderse her char icin 0 ekleniyor
    print_Huff_char_keys_recursive(root->right, arr, top + 1);
  }
  if (check_is_Leaf(root)) {
    
    FILE *fptr;
    fptr = fopen("char_keys.txt","a");

    if(root->symbol == '\n')
    	fprintf(fptr, "\\ ");
    else if(root->symbol == ' ')
    	fprintf(fptr, "$ ");
    else
    	fprintf(fptr,"%c ",root->symbol);
   	for(int i = 0; i<top; i++) 					//her char icin sona geldiginde biriktirilen 1 ve sifirlar yaziliyor
	   	fprintf(fptr, "%d",arr[i]);
   	fprintf(fptr, "\n");

  	fclose(fptr);
  }		
}
/*=====================================================================*/
void writefile_encoded_dat_message_txt(char *filename_keys){

	char keys_char[max_char_num][max_tree_lenght],// \n karakteri icin iki botulu olmasi gerekiyor
		 keys_ways[max_char_num][max_tree_lenght];
	FILE *fptr_key;
	int count = 0;

	if((fptr_key = fopen(filename_keys,"r")) == NULL)
		printf("Anahtar dosya acilamadi\n");

	while(!(feof(fptr_key))){
		fscanf(fptr_key,"%s%s",keys_char[count],keys_ways[count]);
		count++;
	}	

	fclose(fptr_key);
	/*
		Butun ahatarlari keysler icerisine aldik($ bosluk isaretini temosil edecek)
		Sirada message.txt den char alip keys icerisnde bulup yolunu yazdirmak olacak
	*/

	encode_message_txt("message.txt",keys_char,keys_ways,count);
}
/*=====================================================================*/
int return_char_tree_way_index(char char_keys[][max_tree_lenght],char wanted_chrctr,int size){
	int index;

	for(int i=0; i<size; i++){	//char kullanarak yolun indexini donduruyoruz
		if(char_keys[i][0] == wanted_chrctr){
			index = i;
			i = size;
		}
	}
	return index;
}
/*=====================================================================*/
void encode_message_txt(char *filename,char keys_char[max_char_num][max_tree_lenght],
							char keys_ways[max_char_num][max_tree_lenght],int size)
{
	FILE *fptr_txt,
		 *write;
	char character;
	int index;
	if((fptr_txt = fopen(filename,"r")) == NULL)
		printf("Reference cozulme yazdirilirken acilamadi\n");
	if((write = fopen("encoded.dat","w")) == NULL)
		printf("Binary yazmak icin dosya acilamadi (encoded.dat)\n");
	
	character = fgetc(fptr_txt);
	while(!(feof(fptr_txt))){

		if(character == ' ')
			character = '$';//bosluk karakteri temsil ediyor
		if(character == '\n')
			character = '\\';//new line temsil ediyor

		index = return_char_tree_way_index(keys_char,character,size);
		fprintf(write,"%s ",keys_ways[index]);
		character = fgetc(fptr_txt);
	}
	fclose(write);
	fclose(fptr_txt);
}
/*=====================================================================*/
void decode_encoded_bat(char *filename){

	char keys_char[max_char_num][max_tree_lenght],// \n karakteri icin iki botulu olmasi gerekiyor
		 keys_ways[max_char_num][max_tree_lenght];
	int count = 0;
	char ch,wanted[20],free;		 
	FILE *read_bin,*wrt_decode,*key_file;

	if((key_file = fopen("char_keys.txt","r")) == NULL)
		printf("Anahtar Dosya decode edilmeye calisilirken acilamadi\n");

	while(!(feof(key_file))){
		fscanf(key_file,"%s%s",keys_char[count],keys_ways[count]);
		count++;
	}									//Her harfin kodunu yeniden dolduruyoruz
	fclose(key_file);
	//Simdi binary dosyayi okuyup keys icerisnde karsilastiracagiz
	
	if((read_bin = fopen(filename,"r")) == NULL)
		printf("Okumak icin decode.dat binary dosyasi acilamadi\n");
	if((wrt_decode = fopen("decoded.txt","w")) == NULL)
		printf("Cozum dosyasi olusturulamadi\n");

	fscanf(read_bin,"%s%c",wanted,&free);	
	while(!feof(read_bin)){
		ch = return_char_in_key(wanted,keys_char,keys_ways,count);//Alinan chara gore decoded dosyasina metin yaziliyor
		if(ch == '\\')
			fprintf(wrt_decode ,"\n");
		else if(ch == '$')
			fprintf(wrt_decode ," ");
		else
			fprintf(wrt_decode ,"%c",ch);
		fscanf(read_bin,"%s%c",wanted,&free);	
	}
	fclose(read_bin);
	fclose(wrt_decode);
}
/*=====================================================================*/
char return_char_in_key(char wanted[20],char keys_char[max_char_num][max_tree_lenght],
							char keys_ways[max_char_num][max_tree_lenght],int size)
{
	char ch;
	for(int i=0; i<size; i++){			//Yol kullanarak karakteri donduruyor
		if((strcmp(wanted ,keys_ways[i]) == 0)){
			ch = keys_char[i][0];
			i = size;
		}
	}
	return ch;
}
/*=====================================================================*/
void calculate_different_size_byte(char *filekey,char *filemessage){

	FILE *fptr_key,*fmessage;
	int n_of_ch, count = 0,
		n_byte = 0 , index,
		huff_byte = 0, use_ea_byte = 0;
	char ch,
		 keys_char[max_char_num][max_tree_lenght],
	     keys_ways[max_char_num][max_tree_lenght];

	if((fptr_key = fopen(filekey,"r")) == NULL)
		printf("Anahtar dosya byte hesaplamasi yapilirken acilamadi\n");
	while(!(feof(fptr_key))){
		fscanf(fptr_key,"%s%s",keys_char[count],keys_ways[count]);
		count++;
	}	
	n_of_ch = count - 1;
	fclose(fptr_key);

	while(pow(2,use_ea_byte) < n_of_ch)  //Burda normal depolamada bir karakter icin kullanilacak 
		use_ea_byte++;					 //bite hesaplaniyor

	if((fmessage = fopen(filemessage,"r")) == NULL)
		printf("Message dosyasi byte hesaplaniyorken acilamadi\n");

	ch = fgetc(fmessage);
	while(!(feof(fmessage))){
		index = return_char_tree_way_index(keys_char,ch,count);	//karakter kullanilarak yol indexi bulunuyor
		huff_byte += strlen(keys_ways[index]);//Sifrelenmis string boyutu kadar artiriliyor
		n_byte += use_ea_byte;//Her karakterde 2^x>char_var  x degeri kadar artitiliyor
		ch = fgetc(fmessage);
	}

	printf("There are %d diffrent character in tree\n",n_of_ch );
	printf("Normal method for each character need 2^%d > %d bit\n",use_ea_byte,n_of_ch);
	printf("So normally we need %d bit for each letter\n",use_ea_byte );
	printf("\n");	
	printf("Used bit with Normal method = %d \n",n_byte );
	printf("Used bit with the Huffman method = %d \n",huff_byte );
	int earn_byte = n_byte - huff_byte;
	printf("Amount of bit earned = %d\n",earn_byte);
}