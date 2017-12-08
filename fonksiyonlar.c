#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <conio.h>
#include "fonksiyonlar.h"

void karakteri_yerlestir(struct karakter karakter, char bolum[][50])
{
    bolum[karakter.last_Y][karakter.last_X] = ' ';
    bolum[karakter.y][karakter.x] = karakter.ikon;

}

void patlayicii_yerlestir(struct patlayici patlayici,char bolum[][50])
{
    bolum[patlayici.y][patlayici.x] = patlayici.ikon;
}

void dusman_yerlestir(struct dusman dusman,char bolum[][50])
{
    bolum[dusman.y][dusman.x] = dusman.ikon;
}

void yer_ata(struct patlayici *patlayici,struct dusman *dusman,int istenilen)
{

    srand(time(NULL));

    if(istenilen == 0)  //Patlayıcı konumu isteniyorsa
    {
        patlayici->x = 1 + rand()% 26; //Patlayıcının X konumuna değer ata
        patlayici->y = 1 + rand()% 18; //Patlayıcının Y konumuna değer ata

        //Eğer patlayıcı,düşmanın bulunduğu bir konuma denk gelirse denk gelmeyecek şekilde farklı bir konum ata
        while(patlayici->x == dusman->x && patlayici->y == dusman->y)
        {
            patlayici->x = 1 + rand()% 26;
            patlayici->y = 1 + rand()% 18;
        }

    }else if(istenilen == 1)    //Düşman konumu isteniyorsa
    {
        dusman->x = 1 + rand()% 26; //Düşmanın X konumuna değer ata
        dusman->y = 1 + rand()% 18; //Düşmanın Y konumuna değer ata

        //Eğer düşman,patlayıcının bulunduğu bir konuma denk gelirse denk gelmeyecek şekilde farklı bir konum ata
        while(patlayici->x == dusman->x && patlayici->y == dusman->y)
        {
            dusman->x = 1 + rand()% 26;
            dusman->y = 1 + rand()% 18;
        }
    }

}

bool durum_kontrol(struct karakter *karakter,struct patlayici *patlayici,struct dusman *dusman,int *win)
{
    //Karakter bir patlayıcı ile aynı konumdaysa
    if( karakter->x == patlayici->x && karakter->y == patlayici->y )
    {
        karakter->puan += patlayici->puan_degeri;  //Karakterin puanını arttır
        yer_ata(patlayici,dusman,0);    //Patlayıcıya yeni bir konum ata

        //Eğer karakter 1000 puana ulaşmış ise,kazandı işareti ver
        if(karakter->puan == 1000)
        {
            *win = 1;
            return false;
        }
    }

    //Karakter bir düşman ile aynı konumdaysa
    if(karakter->x == dusman->x && karakter->y == dusman->y)
    {
        karakter->hak -= dusman->hasar; //Karakterin hakkını azalt
        yer_ata(patlayici,dusman,1);    //Düşmana yeni bir konum ata

        //Eğer karakter hakkı 0'a ulaşmış ise,kaybetti işareti ver
        if(karakter->hak == 0)
        {
            *win = 0;
            return false;
        }
    }
}

void ekrana_yazdir(struct karakter karakter,char bolum[][50])
{
    for(int i=0 ; i<=19 ; i++)
    {
        for(int j=0 ; j<=27 ;j++)
        {
            printf("%c",bolum[i][j]);
        }

        printf("\n");
    }

    printf("Puan : %d\nKalan Hak : %d\n",karakter.puan,karakter.hak);
}

int oyna(void)
{

    bool oyunDurumu = true;  //Oyun döngüsü değişkeni

    int winnumber,*win;      //Kazanma-kaybetme durum değişkeni 

    win = &winnumber;

    char tus,tus2 = 'b';

    struct karakter karakter; //Karakter tanımlama
    struct patlayici bomba;   //Patlayıcı tanımlama
    struct dusman asker = {17,6,1,'A'};  //Asker tanımlaması ve yyapılandırması

    struct karakter     *oyuncu     = &karakter;
    struct dusman       *dusman     = &asker;
    struct patlayici    *patlayici  = &bomba;

    //Karakter yapılandırma
    karakter.hak  = 3;
    karakter.puan = 0;
    karakter.ikon = '*';
    karakter.x    = 5;
    karakter.y    = 5;

    //Bomba yapılandırma
    bomba.puan_degeri = 100;
    bomba.ikon        = 'P';
    bomba.x =13;
    bomba.y =8;

    //Bölüm tanımlaması
    char bolum1[50][50] =
    {

        {'|','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','|'},
        {'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
        {'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
        {'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
        {'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
        {'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
        {'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
        {'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
        {'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
        {'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
        {'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
        {'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
        {'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
        {'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
        {'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
        {'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
        {'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
        {'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
        {'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
        {'|','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','|'},

    };

    //Oyun döngüsü
    while(oyunDurumu)
    {
        //Karakter konumunu bir önceki konum değişkenine atama
        karakter.last_X = karakter.x;
        karakter.last_Y = karakter.y;

        //Tuş kontrolleri yapılıyor
        if((tus == 'd' || tus == 77) && karakter.x != 26)  //ASCII tablosunda 77 = sağ ok tuşu
        {
            karakter.x += 1; //Karakterin X konumu 1 arttırılıyor

        }else if((tus == 'a' || tus == 75) && karakter.x != 1)  //ASCII tablosunda 75 = sol ok tuşu
        {
            karakter.x -= 1; //Karakterin X konumu 1 azaltılıyor

        }else if((tus == 'w' || tus == 72) && karakter.y != 1)  //ASCII tablosunda 72 = üst ok tuşu
        {
            karakter.y -= 1; //Karakterin Y konumu 1 azaltılıyor

        }else if((tus == 's' || tus == 80) && karakter.y != 18) //ASCII tablosunda 80 = alt ok tuşu
        {
            karakter.y += 1; //Karakterin Y konumu 1 arttırılıyor

        }else if(tus == 27) //ASCII tablosunda 27 = ESC tuşu
        {
            return 1;
        }

        karakteri_yerlestir(karakter,bolum1);   //Karakter ikonunu bölüm içerisinde konumuna yerleştirme
        oyunDurumu = durum_kontrol(oyuncu,patlayici,dusman,win);    //Karakterin düşman veya bomba ile temas durumunun kontrolünü yapılması
        
        //Kontrol sonucu istenilen yönde ise(Karakter hakkı bitmemiş yada bitiş puanına ulaşılmamış ise)
        if(oyunDurumu)
        {
            patlayicii_yerlestir(bomba,bolum1); //Konumu belirlenmiş bombayı bölüm içerisine yerleştirme
            dusman_yerlestir(asker,bolum1);     //Konumu belirlenmiş düşmanı bölüm içerisine yerleştirme
            ekrana_yazdir(karakter,bolum1);     //Bölümü ekrana yazdırma
            tus = getch();                      //Tuş kontrolü için tuşa basılmasını bekleme
        }

        ekrani_temizle();
    }

    if(winnumber == 1)  //Bitiş puanına ulaşıldı ise
    {
        printf("Oyun bitti,kazandiniz !!\n");

    }else if(winnumber == 0)  //Karakter hakkı bitti ise
    {
        printf("Oyun bitti,kaybettiniz !!\n");

    }
}

void bekle(clock_t wt)           
{
   clock_t t1, t2;

   t1 = clock();
   t2 = clock();

   while (t2 - t1 <= wt)
   {
   		t2 = clock();

   }
}

void hakkimda(void)
{
    printf("Merhabalar ben Tamer Erdogan,Nigde Universitesi Mekatronik Muhendisligi 1. Sinif ogrencisiyim\n"
           "Bu yazmis oldugum bir nevi tamamlanmamis bir oyun olan yazilimi kendimi C dilinde gelistirmek\n"
           "fonksiyonlar,yapilar,isaretciler gibi konularda pratik yapmak ve oyun programlama isine ufaktan\n"
           "baslamak icin yazdim.Kaynak kodlarini istediginiz gibi incelemekte ve gelistirmekte ozgursunuz\n"
           "umarim programi yazarken bana kazandirdigi deneyimler kadar sizide deneyim kazandirir.Iyi kodlamalar!");
}

void oynanis(void)
{
    printf("                  Menu hareketleri\n"
           "--------------------------------------------------------\n"
           "Yukari dogru hareket icin \'W\' veya \'Ust Ok Tusu\'\n"
           "Asagi dogru hareket icin  \'S\' veya \'Alt Ok Tusu\'\n"
           "Giris yapmak icin         \'Enter\'\n"
           "Cikis yapmak icin         \'Esc\'\n\n"
           "                  Oyun Ici Hareketler\n"
           "--------------------------------------------------------\n"
           "Yukari dogru hareket icin \'W\' veya \'Ust Ok Tusu\'\n"
           "Asagi dogru hareket icin  \'S\' veya \'Alt Ok Tusu\'\n"
           "Sola dogru hareket icin   \'A\' veya \'Sol Ok Tusu\'\n"
           "Saga dogru hareket icin   \'D\' veya \'Sag Ok Tusu\'\n"
           "Cikis yapmak icin         \'Esc\'\n"
           "                  Oynanis\n"
           "--------------------------------------------------------\n"
           "\'*\' isareti bizim kontrol ettigimiz karakterimizdir.Gerekli yon tuslarini\n"
           "kullanarak askerlere \(\'A\'\) yakalanmadan patlayicilari \(\'P\'\) toplamalisiniz.\n"
           "1000 puan yapinca oyunu kazanir,3 kez askerlere yakalanirsaniz kaybedersiniz.\nIyi oyunlar.."
           );
}

void ekrani_temizle(void)
{
    system("CLS");
}