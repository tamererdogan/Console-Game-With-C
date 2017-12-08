#ifndef GAME_H
#define GAME_H

	struct karakter{
	    int x,y,last_X,last_Y,hak,puan;
	    char ikon;
	};

	struct dusman{
	    int x,y,hasar;
	    char ikon;
	};

	struct patlayici{
	    int x,y,puan_degeri;
	    char ikon;
	};

	struct konum{
	    int x,y;
	};

	void ekrani_temizle(void);		//Ekranı temizleme işi yapan fonksiyon
	void ekrana_yazdir(struct karakter,char bolum[][50]);  //Karakter puan bilgilerini ve bölüm grafiklerini ekrana yazma işi yapan fonksiyon
	void karakteri_yerlestir(struct karakter,char [][50]); //Bölüm içerisinde karakterin şuanki konumuna karakter ikonunu,önceki konumuna ise boşluk ifadesini yerleştirir
	void patlayicii_yerlestir(struct patlayici,char [][50]); //Bölüm içerisinde patlayıcının şuanki konumuna patlayıcı ikonunu yerleştirir
	void dusman_yerlestir(struct dusman,char [][50]);	//Bölüm içerisinde düşmanın şuanki konumuna düşman ikonunu yerleştirir
	bool durum_kontrol(struct karakter *karakter,struct patlayici *patlayici,struct dusman *dusman,int *);	//Karakterin; düşman veya bomba ile temas durumu,hak bitimi veya bitiş puanına ulaşma kontrolünü yapar
	void yer_ata(struct patlayici*,struct dusman*,int);	//Verilen 0 değerine karşılık patlayıcı,1 değerine karşılık düşman için random konum belirler
	void hakkimda(void);	//Hakkımda kısmını yazdıran fonksiyon
	void oynanis(void);		//Oynanış kısmını yazdıran fonksiyon
	int oyna(void);		//Oyun döngüsünün işletildiği fonksiyon
	void bekle(clock_t wt);	//Bekleme fonksiyonu

#endif