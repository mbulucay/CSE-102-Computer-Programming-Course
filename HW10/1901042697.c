#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define max_data 100
#define lenght_of_row 200
#define PI 3.14159265
#define name_len 10
#define file_name_len 20

typedef struct{
	char name[name_len];
	float x,y;
}point;
typedef struct{
	char name[name_len];
	point start,end;
}line;
typedef struct{
	char name[name_len];
	int size;
	point p_s[name_len];
}poly_point;
typedef struct{
	char name[name_len];
	int size;
	line l_s[name_len];
}poly_line;

void data_part_fill_all_datas(char *filepath, point *points, line *lines, poly_point *poly_p, poly_line  *poly_l);
void ayikla(char string[lenght_of_row]);
void determine_type(char string[lenght_of_row],char* type);
void count_number_element_of_polygon(char string[lenght_of_row],int *size);
void return_point_index(char string[name_len],int *index,point *points,int p_count);
void return_line_index(char string[name_len],int *index,line *lines,int l_count);
void return_polygon_point_index(char string[name_len],int *index,poly_point *poly_p,int P_count);
void return_polygon_line_index(char string[name_len],int *index,poly_line poly_l[max_data],int L_count);
void find_kind_of_polygon(char string[name_len],poly_point *poly_p,poly_line *poly_l,int size,int *kind);

void action_part(char *filepath,point *points,line *lines, poly_point *poly_p, poly_line  *poly_l);
void calculate_distance_two_point(point A,point B,float *distance);
void calculate_lenght_of_line(line A,float *lenght);
void calculate_angle_between_line(line A,line B, float *angle);
void calculate_lenght_of_polygon_using_point(poly_point A,float *lenght);
void calculate_lenght_of_polygon_using_line(poly_line A,float *lenght);
void calculate_the_area_of_polygon_using_point(poly_point A, float *area);
void calculate_the_area_of_polygon_using_lines(poly_line A,float *area);
void calculate_the_ditance_point_to_line(line A, point B,float *distance);
void make_equation(float x1,float y1,float x2,float y2,float katsayilar[]);
void distance_point_to_line(float x,float y,float katsayilar[],float *dis);

int main(){
		
	point 	points[max_data];		//Ihtiyacimiz olacak kadar maksimum duzeyde her bir struct icin yer ayiriyoruz
	line 	lines[max_data];		
	poly_point	poly_p[max_data];
	poly_line 	poly_l[max_data];

	data_part_fill_all_datas("commands.txt",points, lines, poly_p, poly_l);	//Bilgileri doldurdugumuz yer 
	action_part("commands.txt",points, lines, poly_p, poly_l);	//Bilgileri kullandigimiz yer
	return 0;
}
/*======================================================================*/
void data_part_fill_all_datas(char *filepath, point *points, line *lines, poly_point *poly_p, poly_line  *poly_l){

	char p_name[name_len],p2_name[name_len],l_name[name_len],
		 satir[lenght_of_row], type, 
		 *take = (char*)malloc(sizeof(char)*name_len);
	int data_num, p_count=0,l_count=0,
		P_count=0,L_count=0, size=0;
	int index;

	float x, y;	
	FILE *read;
	if((read = fopen(filepath,"r")) == NULL)
		printf("Dosya Acilamadi\n");	

	while(!(strstr(satir,"data"))){		//"data " kelimesini bulana kadar dosyayi satir satir okuyor
		fgets(satir,lenght_of_row,read);
	}	
	fscanf(read,"%d",&data_num);		//data kelimesinin altindaki data sayisini aliyoruz
	fgets(satir,lenght_of_row,read);	//Sayi satirindan kurtuluyoruz

	for(int i=0 ;i<data_num; i++){		//Dosyadan data sayisi kadar bilgi icin o kadar satir okuyoruz

		fgets(satir,lenght_of_row,read);
		ayikla(satir);		//eger satir yorum veya new line karakteri iceriyorsa okunan stringi duzenliyor
		determine_type(satir,&type);	//Alinan datanin hangi struct icin oldugunu ayirt ediyor

		if(type == 'p'){	//point icin
			sscanf(satir,"%f%f%s",&x,&y,p_name);	//Satiri parcaliyor kordinatlari ve point name aliyor	
			strcpy(points[p_count].name, p_name);
			points[p_count].x = x;					//Alinan degerleri struct icerisindeki uygun yerlere yerlestiriyoruz
			points[p_count].y = y;
			p_count++;				//Bir sonraki icin array indexi artiriyoruz
		}	
		else if(type == 'l'){	// line icin
			sscanf(satir,"%s%s%s",p_name,p2_name,l_name);	
			strcpy(lines[l_count].name,l_name);

			for(int i=0; i<p_count; i++){	//Satirdan alinacak olan points isimleri 
				if((strcmp(p_name,points[i].name)) == 0)	//Tum pointlerle karsilastirilip uygun point 
					lines[l_count].start = points[i];		//Line icindeki uygun struct pointlerine atiyoruz
				if((strcmp(p2_name,points[i].name)) == 0)
					lines[l_count].end = points[i];
			}
			l_count++;	//index arttiriyoruz
		}
		else if(type == 'P'){	//Poligon point icin
			count_number_element_of_polygon(satir,&size);//Poligonun kacgen oldugunu buluyoruz
			poly_p[P_count].size = size;				 //struct icerisindeki size a atiyoruz
			take = strtok(satir," ");					//Ilk point adini aliyoruz
			return_point_index(take,&index,points,p_count);	//uygun pointer indexi donduruyoruz
			poly_p[P_count].p_s[0] =  points[index];	// ilk pointi atiyoruz
			for(int i=1; i<size; i++){
				take = strtok(NULL," ");
				return_point_index(take,&index,points,p_count);	//Sonra alinan butun pointleri 
				poly_p[P_count].p_s[i] = points[index];			//indexleri bulunup poligon icindeki point structina atiyoruz
			}
			take = strtok(NULL," ");		//Poligonun adini alip atiyoruz
			strcpy(poly_p[P_count].name,take);
			P_count++;					//index artiriyoruz
		}
		else if(type == 'L'){	//Poligon line icin
			count_number_element_of_polygon(satir,&size);	//Ustteki adimlar aynen poligon lina icin uygulaniyor
			poly_l[L_count].size = size;
			take = strtok(satir," ");
			return_line_index(take,&index,lines,l_count);
			poly_l[L_count].l_s[0] = lines[index];
			for(int i=1; i<size; i++){
				take = strtok(NULL," ");
				return_line_index(take,&index,lines,l_count);
				poly_l[L_count].l_s[i] = lines[index];
			}
			take = strtok(NULL," ");
			strcpy(poly_l[L_count].name,take);
			L_count++;				//index artiriyoruz
		}
		else
			printf("Tanimlanamayan satir var lutfen satirlarin uygun formatta yazildigindan emin olun\n");
	}
}
/*======================================================================*/
void ayikla(char string[lenght_of_row]){
	int a=0;

	while(string[a] != '\n'){
		a++;
		if( string[a] =='/' )
			break;
	}
	for(int i=a ;i<lenght_of_row;i++)
		string[i] = 0;
}
/*======================================================================*/
void determine_type(char string[lenght_of_row],char* type){

	for(int i=strlen(string); i>=0; i--){	//satirlari geriden okuyup bulunan ilk karakter
		if(string[i] == 'P'){				//satirin tipini berlirliyor
			*type = 'p';
			i=-1;
		}
		else if(string[i] == 'L'){
			*type = 'l';
			i=-1;
		}
		else if(string[i] == 'G'){
			if(string[0] == 'P')
				*type = 'P';
			else if(string[0] == 'L')
				*type = 'L';	
			i=-1;
		}
	}
}
/*======================================================================*/
void count_number_element_of_polygon(char string[lenght_of_row],int *size){
	int count = 0;

	for(int i=0; i<strlen(string); i++){		//Poligonun kacgen oldugunu buluyoruz
		if(string[i] == 'P')
			count++;
		if(string[i] == 'L')
			count++;
	}
	*size = count-1;
}
/*======================================================================*/
void return_point_index(char string[name_len],int *index,point *points,int p_count){
	int flag = 1;
	for(int i=0; i<p_count; i++){
		if((strcmp(string,points[i].name)) == 0){
			*index = i;
			i = p_count;			//Stringin points struclari icindeki isimleri ile
			flag = 0;				//karsilastirilip index donduruyoruz
		}
	}
	if(flag)
		*index = -1;
}
/*======================================================================*/
void return_line_index(char string[name_len],int *index,line *lines,int l_count){
	int flag = 1;
	for(int i=0; i<l_count; i++){
		if((strcmp(string,lines[i].name)) == 0){
			*index = i;
			i = l_count;		//Stringin line struclari icindeki isimleri ile
			flag = 0;			//karsilastirilip index donduruyoruz
		}
	}
	if(flag)
		*index = -1;
}
/*======================================================================*/
void return_polygon_point_index(char string[name_len],int *index,poly_point *poly_p,int P_count){
	int flag = 1;
	for(int i=0; i<P_count; i++){
		if((strcmp(string,poly_p[i].name)) == 0){
			*index = i;
			i = P_count; 	//Stringin poligon point struclari icindeki isimleri ile
			flag = 0;		//karsilastirilip index donduruyoruz
		}
	}
	if(flag)
		*index = -1;
}
/*======================================================================*/
void return_polygon_line_index(char string[name_len],int *index,poly_line *poly_l,int L_count){
	int flag = 1;
	for(int i=0; i<L_count; i++){
		if((strcmp(string,poly_l[i].name)) == 0){
			*index = i;
			i = L_count;	//Stringin poligon line struclari icindeki isimleri ile
			flag = 0;		//karsilastirilip index donduruyoruz
		}		
	}
	if (flag)
		*index = -1;
}
/*======================================================================*/
void action_part(char *filepath,point *points,line *lines, poly_point *poly_p, poly_line  *poly_l){

	char satir[lenght_of_row], *file_name,
		 islem[name_len],parameter_1[name_len],parameter_2[name_len];
	int action_num,flag = 1,index,
		index_1,index_2,kind;
	float distance, angle, area,lenght;

	FILE *read,*write;
	read = fopen(filepath,"r");
	file_name = (char *)malloc(sizeof(char) * file_name_len);	

	fgets(satir,lenght_of_row,read);	
	while((strstr(satir,"actions")) == 0){	//Action kelimesini bulana kadar dosyayi okuyoruz
		fgets(satir,lenght_of_row,read);
		if(feof(read))
			printf("actions cannot found\n");
	}
	fgets(satir,lenght_of_row,read);
	satir[strlen(satir) - 1] = '\0';	//new line siliniyor
	strcpy(file_name,satir);
	write = fopen(file_name,"w"); 

	fscanf(read,"%d",&action_num);
	fgets(satir,lenght_of_row,read);

	for(int sayac=0; sayac<action_num; sayac++){
		flag = 1;
		fgets(satir,lenght_of_row,read);
		sscanf(satir,"%s%s%s",islem,parameter_1,parameter_2);

		if(strstr(satir,"Distance")){
		
			if(parameter_2[0] == 'P'){										//Mesafesi olculecek	
				return_point_index(parameter_1,&index_1,points,max_data);	//Noktalarin bulundugu indexler aliniyor			
				return_point_index(parameter_2,&index_2,points,max_data);
				calculate_distance_two_point(points[index_1],points[index_2],&distance);  //Fonksiyonda mesafe hesaplanip yazdiriliyor
				if(index_1 ==-1 || index_2 == -1)
					fprintf(write,"Distance(%s,%s) = NOT_IMPLEMENTED \n",points[index_1].name,points[index_2].name);
				else	
					fprintf(write,"Distance(%s,%s) = %.1f \n",points[index_1].name,points[index_2].name,distance );
			}
			if(parameter_2[0] == 'L'){
				return_point_index(parameter_1,&index_1,points,max_data);	//Pointin indexi bulunuyor
				calculate_the_ditance_point_to_line(lines[index_2],points[index_1],&distance);

				if(index_1 ==-1 || index_2 == -1)
					fprintf(write,"Distance(%s,%s) = NOT_IMPLEMENTED\n",parameter_1,parameter_2 );
				else
					fprintf(write,"Distance(%s,%s) = %.1f\n",parameter_1,parameter_2,distance );	
			}
		}
		else if(strstr(satir,"Angle")){
			return_line_index(parameter_1,&index_1,lines,max_data);	//Linelerin indexleri aliniyot
			return_line_index(parameter_2,&index_2,lines,max_data);
			calculate_angle_between_line(lines[index_1],lines[index_2],&angle);		//Formule gore aci hesaplaniyor
			if(index_1 ==-1 || index_2 == -1)			
				fprintf(write, "Angle(%s,%s) = NOT_IMPLEMENTED\n",lines[index_1].name,lines[index_2].name);
			else
				fprintf(write, "Angle(%s,%s) = %.1f\n",lines[index_1].name,lines[index_2].name,angle );
		}
		else if((strstr(satir,"Length"))){

				if(parameter_1[0] == 'P'){
					find_kind_of_polygon(parameter_1,poly_p,poly_l,max_data,&kind); //Polygonun pointlerden mi yoksa linelardan mi olustugunu kontrol ediliyor
					if(kind == 0){//Point type
						return_polygon_point_index(parameter_1,&index,poly_p,max_data);	//Eger pointlerden olusmussa indexi bulunuyor
						calculate_lenght_of_polygon_using_point(poly_p[index],&lenght );	//Uzunluk hesaplaniyor
						if(index == -1)
							fprintf(write,"Length(%s) = NOT_IMPLEMENTED\n",poly_p[index].name);
						else
							fprintf(write,"Length(%s) = %.1f\n",poly_p[index].name,lenght);
					}
					else if(kind == 1){
						return_polygon_line_index(parameter_1,&index,poly_l,max_data);	//Linelardan olusmussa indexi aliniyor 
						calculate_lenght_of_polygon_using_line(poly_l[index],&lenght);	//Uzunluk hesaplaniyor
						if(index == -1)
							fprintf(write,"Length(%s) = NOT_IMPLEMENTED\n",poly_l[index].name);
						else
							fprintf(write,"Length(%s) = %.1f\n",poly_l[index].name,lenght);
					}
				}
				else if(parameter_1[0] == 'L'){
					return_line_index(parameter_1,&index,lines,max_data);	//Ayni islemler sirasiyla yapiliyor
					calculate_lenght_of_line(lines[index],&lenght);
					if(index == -1)
						fprintf(write, "Length(%s) = NOT_IMPLEMENTED\n",lines[index].name );
					else
						fprintf(write, "Length(%s) = %.1f\n",lines[index].name,lenght );
				}	
		}
		else if((strstr(satir,"Area"))){
			find_kind_of_polygon(parameter_1,poly_p,poly_l,max_data,&kind);	//Ayni islemler sirasiyla yapiliyor

			if(kind == 0){
				return_polygon_point_index(parameter_1,&index,poly_p,max_data);		//index aliniyor
				calculate_the_area_of_polygon_using_point(poly_p[index],&area);		//Islem hesaplaniyor
				if(index == -1)
					fprintf(write,"Area(%s) = NOT_IMPLEMENTED\n",poly_p[index].name );
				else
					fprintf(write,"Area(%s) = %.1f\n",poly_p[index].name, area );
			}
			else if(kind == 1){
				return_polygon_line_index(parameter_1,&index,poly_l,max_data);
				calculate_the_area_of_polygon_using_lines(poly_l[index],&area);
				if(index == -1)
					fprintf(write,"Area(%s) = NOT_IMPLEMENTED\n",poly_p[index].name );
				else
					fprintf(write,"Area(%s) = %.1f\n",poly_p[index].name, area );
			}
		}
	}

	fclose(read);
	fclose(write);
}
/*======================================================================*/
void calculate_distance_two_point(point A,point B,float *distances){
	float x = A.x - B.x;
	float y = A.y - B.y;
	float result = x*x + y*y;		// a^2 = b^2+c^2  pisagor
	if(result<0)
		result*=-1;
	*distances = sqrt(result);
}
/*======================================================================*/
void calculate_lenght_of_line(line A,float *lenght){
	float result;
	calculate_distance_two_point(A.start,A.end,&result);	//Linein baslangic ve bitis noktalari gonderiliyor
	*lenght = result;
}
/*======================================================================*/
void calculate_the_ditance_point_to_line(line A, point B,float *distance){
	float dis;
	float katsayilar[3];

	if(A.start.x - A.end.x == 0)		//Tanimsizlik oldugu durumlar icin
		*distance = fabsf(B.x - A.start.x); 
	else{
		make_equation(A.start.x,A.start.y,A.end.x,A.end.y,katsayilar);
		distance_point_to_line(B.x,B.y,katsayilar,&dis);
		*distance = dis;
	}
}
/*======================================================================*/
void make_equation(float x1,float y1,float x2,float y2,float katsayilar[]){

	float slope =  (y2-y1) / (x2-x1);
	katsayilar[0] = slope;			//Egimi hesaplayip denklem katsayilarini buluyoruz
	katsayilar[1] = -1;
	katsayilar[2] = +y1 - slope*x1;
}
/*======================================================================*/
void distance_point_to_line(float x,float y,float katsayilar[],float *dis){
	float pay = fabsf(katsayilar[0]*x + katsayilar[1]*y + katsayilar[2]);	// Noktanin dogruya uzakligini buluyoruz
	float payda = sqrt(pow(katsayilar[0], 2) + pow(katsayilar[1], 2));
	*dis = pay / payda;
}
/*======================================================================*/
void calculate_angle_between_line(line A,line B, float *angle){

	float result,
		  mag_A ,mag_B,
		  dif_a_x,dif_a_y,
		  dif_b_x,dif_b_y;

	dif_a_x = (A.start.x - A.end.x);		//Cos teoreminden aci hesaplaniyor
	dif_a_y = (A.start.y - A.end.y);
	dif_b_x = (B.start.x - B.end.x);
	dif_b_y = (B.start.y - B.end.y);
	calculate_distance_two_point(A.start,A.end,&mag_A);
	calculate_distance_two_point(B.start,B.end,&mag_B);
	
	result = (dif_a_x*dif_b_x + dif_a_y*dif_b_y) / (mag_A * mag_B);
	result = acos(result);
	result = result * 180.0 / PI;
	if(result>=90)
		result-=180;
	if(result<0)
		result*=-1;
	*angle = result;
}
/*======================================================================*/
void find_kind_of_polygon(char string[5],poly_point *poly_p,poly_line *poly_l,int size,int *kind){

	for(int i=0;i<size; i++){	//Poligonun noktalardan mi linelardan mi olustugunu buluyoruz

		if((strcmp(string,poly_p[i].name)) == 0){
			*kind = 0;
			i = size;
		}
		if((strcmp(string,poly_l[i].name)) == 0){
			*kind = 1;
			i = size;
		}
	}
}
/*======================================================================*/
void calculate_lenght_of_polygon_using_point(poly_point A,float *lenght){

	float sum = 0,dis;		

	for(int i=0; i<A.size-1; i++){
		calculate_distance_two_point(A.p_s[i],A.p_s[i+1],&dis);	//Poligonun sirayi takip ederek her iki nokta arasi 
		sum += dis;												//uzaliklari topluyor		
	}
	calculate_distance_two_point(A.p_s[A.size-1],A.p_s[0],&dis);
	sum+=dis;
	*lenght = sum;
}
/*======================================================================*/
void calculate_lenght_of_polygon_using_line(poly_line A,float *lenght){

	float sum = 0,dis;

	for(int i=0; i<A.size; i++){
		calculate_lenght_of_line(A.l_s[i],&dis);	//Poligonu olusturan linelarin uzunluklari
		sum+=dis;									//toplanip bulunuyor
	}
	*lenght = sum;
}
/*======================================================================*/
void calculate_the_area_of_polygon_using_point(poly_point A, float *area){

	float sum_of_multiple_right = 0.0;			//Formule gore alan hesaplaniyor
	float sum_of_multiple_left  = 0.0;

	for(int i=0; i<A.size-1; i++)
		sum_of_multiple_right += (A.p_s[i].x) * (A.p_s[i+1].y);		//Sagalt capraza dogru carpimlar toplami
	sum_of_multiple_right += (A.p_s[A.size-1].x) * (A.p_s[0].y);

	for(int i=0; i<A.size-1; i++)
		sum_of_multiple_left  += (A.p_s[i].y) * (A.p_s[i+1].x);		//Sol alt capraza dogru carpimlar toplami
	sum_of_multiple_left += (A.p_s[A.size-1].y) * (A.p_s[0].x);

	*area = (sum_of_multiple_right - sum_of_multiple_left)/2;
}
/*======================================================================*/
void calculate_the_area_of_polygon_using_lines(poly_line A,float *area){

	poly_point temp;
	float result;
	for(int i=0; i<A.size; i++ )
		temp.p_s[i]= A.l_s[i].start;
	temp.size = A.size;	
	calculate_the_area_of_polygon_using_point(temp,&result);	//Linelari olusturan noktalar gonderilip
	*area = result;												//formule gore alan hesaplaniyor
}
/*======================================================================*/