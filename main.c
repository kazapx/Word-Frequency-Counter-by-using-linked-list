#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
struct kelime
{
int repeat; //txt de kac kez tekrar ettigi
int start;  //txt de kelimenin baslangic indexi
int end;    //txt de kelimenin bitis indexi
int uzunluk;//kelimenin uzunlugu
struct kelime *sonraki;
struct kelime *onceki;
};
struct kelime2
{
int repeat; //txt de kac kez tekrar ettigi
int start;  //txt de kelimenin baslangic indexi
int end;    //txt de kelimenin bitis indexi
struct kelime *sonraki;
};


///////////////////////////////////////////////////////////////////////////////

void sona_ekle(struct kelime2** yeni_ref, int yeni_end, int yeni_repeat, int yeni_start)
{   // yeni_dugum en sona eklenecek olan dugum
    struct kelime2* yeni_dugum = (struct kelime2*) malloc(sizeof(struct kelime2));
    // sonuncu ise listenin en sonundaki dugum
    struct kelime2 *sonuncu = *yeni_ref;

    //dugume bilgiler yerlesiyor
    yeni_dugum->start = yeni_start;
    yeni_dugum->repeat = yeni_repeat;
    yeni_dugum->end = yeni_end;

//gelen dugum null ise listede herhangi bir sey yoktur.
if (*yeni_ref == NULL)
{
*yeni_ref = yeni_dugum;
return;
}

    //sonuncu en sona gidiyor
    while(sonuncu->sonraki!=NULL)
        sonuncu = sonuncu->sonraki;

    //listenin sonuna yeni_dugum ekleniyor
    sonuncu->sonraki = yeni_dugum;
    //dogal olarak yeni_dugum listenin sonuncu dugumu oldugundan sonrasý nulldur
    yeni_dugum->sonraki = NULL;
    return;
}

///////////////////////////////////////////////////////////////////////////////
void basa_ekle(struct kelime2** birinci_ref, int yeni_end, int yeni_repeat, int yeni_start)
{
// yeni_dugum en basa eklenecek olan dugum
 struct kelime2* yeni_dugum = (struct kelime2*) malloc(sizeof(struct kelime2));
    //dugume bilgiler yerlesiyor
    yeni_dugum->start = yeni_start;
    yeni_dugum->repeat = yeni_repeat;
    yeni_dugum->end = yeni_end;
//birinci_ref listenin basindaki dugumdur.
yeni_dugum->sonraki = (*birinci_ref);
//artýk listenin basini yeni_dugum gostermelidir
(*birinci_ref) = yeni_dugum;
}
///////////////////////////////////////////////////////////////////////////////
void araya_ekle(struct kelime2** ilk_dugum, int yeni_end, int yeni_repeat, int yeni_start)
{

struct kelime2* yeni_dugum =(struct kelime2*) malloc(sizeof(struct kelime2));
struct kelime2 *onceki_dugum = *ilk_dugum;
//dugume bilgiler yerlesiyor
yeni_dugum->start = yeni_start;
yeni_dugum->repeat = yeni_repeat;
yeni_dugum->end = yeni_end;

while(onceki_dugum!=NULL)
{//kendi repeat sayisindan kucuk ilk repeat sayisini buldugunda araya yerlestir.
if(onceki_dugum->sonraki->repeat < yeni_dugum->repeat)
{
yeni_dugum->sonraki = onceki_dugum->sonraki;
onceki_dugum->sonraki = yeni_dugum;
break;
}
    onceki_dugum = onceki_dugum->sonraki;

}


}
///////////////////////////////////////////////////////////////////////////////






void sil(struct kelime **iterr)
{
struct kelime* iter2 = (struct kelime*) malloc(sizeof(struct kelime));
iter2 = (*iterr);
//aradaysa
if((iter2->sonraki!=NULL && iter2->onceki!=NULL)){
iter2->onceki->sonraki = iter2->sonraki;
iter2->sonraki->onceki = iter2->onceki;
}
//sondaysa
else if(iter2->sonraki==NULL){
        iter2 = iter2->onceki;
        iter2->sonraki = NULL;
}
}

//birinci liste icin
void yazdir(struct kelime **iterr,struct kelime **wordd)
{
    FILE* f;
f = fopen("metin.txt", "r");

struct kelime* iter = (struct kelime*) malloc(sizeof(struct kelime));
struct kelime* word = (struct kelime*) malloc(sizeof(struct kelime));
 word = (*wordd);
 iter = (*iterr);
 printf("\nLink listler:\n");
iter = word;
while(iter != NULL){
        printf("| Tekrar sayisi:%3d   ",iter->repeat);
        printf("| KELIME:   ");
    for(int j = 0; ((iter->end)-(iter->start)+1)>j ; j++){

        fseek(f, ((iter->start)+j), SEEK_SET);

        printf("%c",tolower(fgetc(f)));


}

printf("\n_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n");
 iter= iter->sonraki;
}


}



//kullanilmasi gereken yazdirma metotu (liste2 icin)
void yazdir2(struct kelime2 **iterr)
{
    FILE* f;
f = fopen("metin.txt", "r");

struct kelime2* iter = (struct kelime2*) malloc(sizeof(struct kelime2));
 iter = (*iterr);
 printf("\nLink listler:\n");
 int no = 0;
while(iter != NULL){
        printf("| %2d: ",no);
        printf("| Tekrar sayisi:%3d   ",iter->repeat);
        printf("| KELIME:   ");
no++;
    for(int j = 0; ((iter->end)-(iter->start)+1)>j ; j++){
        fseek(f, ((iter->start)+j), SEEK_SET);
        printf("%c",tolower(fgetc(f)));
}

printf("\n_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ \n");
 iter= iter->sonraki;
}

}






int main()
{
//////////////////////////////////////////////////////////////
	FILE* f;
	f = fopen("metin.txt", "r");
	if (f == NULL) { // dosyaya erisilemiyorsa NULL olur
		printf("Dosya acilamadi.\n");
		exit(1);
	}
//////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////
struct kelime* word = NULL;
word = (struct kelime*)malloc(sizeof(struct kelime));
struct kelime *iter;
iter = word;
//////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////
	int kelime_sayisi = 0;
	int karakter_sayisi = 0;
	char c;
//////////////////////////////////////////////////////////////




//KELIME SAYISI VE KARAKTER SAYISINI BUL
//////////////////////////////////////////////////////////////
    if((c = fgetc(f))!= EOF)
        kelime_sayisi++;
    fclose(f);
f = fopen("metin.txt", "r");
    while((c = fgetc(f))!= EOF)
    {karakter_sayisi++;
        if(c==' '){
            kelime_sayisi++;}
    }
printf("Kelime sayisi: %d ",kelime_sayisi);
printf("Karakter sayisi: %d",karakter_sayisi);
//////////////////////////////////////////////////////////////




//TXT DE EN BASA GELMEK ICIN DOSYAYI KAPATIP ACIYORUZ (FSEEK KULLANILABILIRDI)
//////////////////////////////////////////////////////////////
fclose(f);
f = fopen("metin.txt", "r");
//////////////////////////////////////////////////////////////








//TUM KELIMELERI LISTEYE AT
//////////////////////////////////////////////////////////////
int ayar =0;


for(int i = 0; karakter_sayisi>i ; i++)
{char x;
x = fgetc(f);
    if(x != ' ')
    {
        if(ayar == 1)
        {//if(x == '.' || x == ',')
         //  continue;

            iter->end = i;

        }
        if(ayar == 0)//kelimenin metin icerisinde ilk yani baslangic indexi
        {  iter->end = i;
          iter->start = i;
            ayar =1;
        }

    }
    else
    {
        iter->sonraki=(struct kelime*)malloc(sizeof(struct kelime));
        iter = iter->sonraki;
        ayar = 0;

    }

iter->uzunluk = (iter->end)-(iter->start)+1;
iter->repeat = 1;
}


iter->sonraki = NULL;

//////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////
printf("\n");

//onceki ekleme
struct kelime *iter2;
iter2 = word->sonraki;
iter = word;
iter->onceki=NULL;
while(iter2!=NULL)
{
    iter2->onceki = iter;

    iter = iter->sonraki;
    iter2 = iter2->sonraki;
}
//////////////////////////////////////////////////////////////





//KELIMELERIN KAC DEFA GECTIGINI YANI REPEAT SAYISINI BULUYORUZ VE LISTEDEKI AYNI KELIMELERI SILIYORUZ.
//////////////////////////////////////////////////////////////
int count = 0;
char a_1;
char a_2;

if(word->sonraki == NULL)
{

}
else{
iter2 = word->sonraki;
iter = word;
fclose(f);
f = fopen("metin.txt", "r");
while(iter!=NULL)
{
    while(iter2!=NULL)
    {
        if(iter2==iter){
        iter2=iter2->sonraki;
        continue;
        }
        //KELIMELERIN UZUNLUKLARI AYNIYSA KARSILASTIR. UZUNLUKLARI FARKLIYSA ZATEN FARKLI KELIMELERDIR
        if(iter2->uzunluk==iter->uzunluk){
        for(int k = 0; iter2->uzunluk>k; k++)
        {
        fseek(f, ((iter->start)+k), SEEK_SET);
        a_1 = fgetc(f);
        fseek(f, ((iter2->start)+k), SEEK_SET);
        a_2 = fgetc(f);

        if(tolower(a_1)!=tolower(a_2))
            break;//DIREK FARKLI KARAKTER GORURSEN FARKLI KELIMEDIR. DIREK CIKAR
        else{

            count++;
            if(count == iter->uzunluk){
sil(&iter2);
iter->repeat++;
              }
            }
        }
        count = 0;
       }


     iter2=iter2->sonraki;
    }

    count = 0;
    iter=iter->sonraki;
    iter2 = iter;
}



}
//////////////////////////////////////////////////////////////



//LISTE 1 DEN LISTE 2 YE EKLIYORUZ.
//////////////////////////////////////////////////////////////
iter = word;
 struct kelime2* yeni_dugum = NULL;
int aaaa =0;
while(iter!=NULL)
{

    if(aaaa == 0) //LISTE 2'YE ILK EKLENECEK DUGUM
    {
     yeni_dugum  = (struct kelime2*) malloc(sizeof(struct kelime2));
     yeni_dugum->end = iter->end;
     yeni_dugum->repeat = iter->repeat;
     yeni_dugum->start = iter->start;
     iter = iter->sonraki;
     aaaa++;
     continue;
    }
                                    //yeni_dugum  LISTE2 NIN ILK DUGUMU (BASA_EKLE() METOTU ICIN)
    struct kelime2* sonuncu_dugum; //sonuncu_dugum LISTE2 NIN SONUNCU DUGUMU (SONA_EKLE() METOTU ICIN)
    sonuncu_dugum = yeni_dugum;
    while(sonuncu_dugum->sonraki!=NULL)
    {
        sonuncu_dugum = sonuncu_dugum->sonraki;
    }

    if(yeni_dugum->repeat<=iter->repeat)
    {basa_ekle(&yeni_dugum,iter->end,iter->repeat,iter->start);
     iter = iter->sonraki;
    continue;
    }



    if(sonuncu_dugum->repeat>=iter->repeat)
    {sona_ekle(&yeni_dugum,iter->end,iter->repeat,iter->start);
    iter = iter->sonraki;
    continue;
    }

    //ARAYA EKLE, EN YUKSEK REPEAT SAYISI VE EN KUCUK REPEAT SAYISININ SAYISAL OLARAK ORTASINDA YER ALIYORSA ARAYA EKLE
    if(sonuncu_dugum->repeat  < iter->repeat   &&   yeni_dugum->repeat  >  iter->repeat)
    {
    araya_ekle(&yeni_dugum,iter->end,iter->repeat,iter->start);
    iter = iter->sonraki;
     continue;
    }




}
//////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////
//yazdir(&iter,&word); //LISTE 1 ICIN YAZDIRMA
yazdir2(&yeni_dugum); //LISTE 2 ICIN YAZDIRMA (en son hal ve kullanilmasi gereken)




    return 0;
}
