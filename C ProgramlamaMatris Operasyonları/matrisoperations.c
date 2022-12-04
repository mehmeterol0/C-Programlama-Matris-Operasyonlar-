#include <stdio.h>
#include <stdlib.h>
#include "matrisoperations.h"


int **matris1olustur(int satir, int sutun) //matris1 olusturmak icin kullanilan fonksiyon
{

    int i;
    int **dizi = malloc(satir * sizeof(int *));
    for (i = 0; i < satir; i++)
    {
        dizi[i] = malloc(sutun * sizeof(int));
    }
    return dizi;
}

int **matris2olustur(int satir, int sutun)//matris2 olusturmak icin kullanilan fonksiyon
{

    int i;
    int **dizi = malloc(satir * sizeof(int *));
    for (i = 0; i < satir; i++)
    {
        dizi[i] = malloc(sutun * sizeof(int));
    }
    return dizi;
}

int **operasyon1(int **matris1, int **matris2, int islemTipi, int matris1SatirSayisi, int Matris2SatirSayisi)//operasyon fonksiyonu baslangic
{

    int G, F, sonuc;// G= matris1 satir sayisi. F= matris2 Satir sayisi. sonuc=Formul=((G-F+2D)/1)+1
    int D;
    G = matris1SatirSayisi;
    F = Matris2SatirSayisi;
    if (islemTipi==1)
    {
        D = (Matris2SatirSayisi - 1) / 2;
    }
    if (islemTipi==0)
    {
        D=0;
    }
    
    

    // islem 1 icin parametreler
    if (islemTipi == 0)//iki farklı islem tipimiz vardı 1 ve 0. 0 icin olan kod blogu baslangici
    {
        

        int sayac = 0; //gezinme isleminin kac kere oldugunu kontrol etmem icin gereken degisken.
        int durum = 1; //olusturdugum while dongusunu kontrol etmem icin gerekli olan degiskenim.
        int sayac2 = 0; //gezinme isleminin kac kere oldugunu kontrol etmem icin gereken degisken.

        int mat1satirtut = 0; //matris1 satirlarinda padding islemi icin rahatlıkla gezebilmem icin olusturdugum degisken.
        int mat1sutuntut = 0;//matris1 sutunlarinda padding islemi icin rahatlıkla gezebilmem icin olusturdugum degisken.

        int i, j;
        sonuc = (((G - F) + (2 * D)) / 1) + 1;// formulumun sonucu
        printf("Cikti Matris Boyutu: %d\n", sonuc); //cikti matrisimin dogrulugunu kullaniciya bastirdim.

        int padMatrisSize; //padMatris adinda bir degisken. bu degisken padMatrisimin uzunlugunu belirler
        padMatrisSize = Matris2SatirSayisi; //bu uzunluk matris2satirsayisi ile esit olmalidir.
        /*
        matris2 aslinda benim kernelim olarak gorev gormektedir. kernelimi matris1 uzerinde hareket ettirdikce,
        padMatris üzerine atıyorum. daha sonra da gerekli islemi atayip, sonuc matrisimi tek tek dolduruyorum.
        */
        int **padMatris = (int **)malloc(Matris2SatirSayisi * sizeof(int *)); //padMatrisimi olusturuyorum.
        for (i = 0; i < Matris2SatirSayisi; i++)
        {
            padMatris[i] = (int *)malloc(Matris2SatirSayisi * sizeof(int));
        }

        int **sonucMatris = (int **)malloc(sonuc * sizeof(int *)); //sonucMatris boyu yukardaki ciktinin boyunu vermelidir.
        for (i = 0; i < sonuc; i++)
        {
            sonucMatris[i] = (int *)malloc(sonuc * sizeof(int));
        }

        int islem = 0; //islemi hesaplayip tutmama yarayan degisken.

        int k = 0; //sonuc matris satir indis
        int m = 0; //sonuc matris sutun indis

        while (durum == 1) //yukarda tanimladigim durum degiskenim 0 olana kadar while icinden cikmaz.
        {

            for (i = 0; i < padMatrisSize; i++)
            {
                for (j = 0; j < padMatrisSize; j++)
                {
                    padMatris[i][j] = matris1[i + mat1satirtut][j + mat1sutuntut];
                    //mat1satirtut ve mat1sutun tut degiskenlerim ile matris1 uzerinde gezinip padMatrise atıyorum.
                    //printf("sayac =%d sayac2=%d mat1satirtut=%d mat1sutuntut=%d padMatris[i][j]= %d, %d  matris1[i+satut][j+sutut]= %d, %d \n",sayac,sayac2,mat1satirtut,mat1sutuntut,i,j,(i+mat1satirtut),(j+mat1sutuntut));
                }
            }
            /* 
            //padding islemini yourum satirindan cikartarak, tek tek burda görebilirsiniz. 

            printf("------------PAD----------- \n");
            for (i = 0; i < padMatrisSize; i++)
            {
                for (j = 0; j < padMatrisSize; j++)
                {
                    printf("%d  ", padMatris[i][j]);
                }
                printf("\n");
            }
            */
            

            for (i = 0; i < Matris2SatirSayisi; i++)
            {
                for (j = 0; j < Matris2SatirSayisi; j++)
                {
                    islem += padMatris[i][j] * matris2[i][j];
                    //padleme sonucu cikan islemi foye uygun sekilde carpip toplayıp islem degiskenine atiyorum.
                }
            }

            //printf("islem = %d",islem);
            mat1sutuntut++;
            //aslinda padding islemi yaparak sadece sutunlar tek tek arttirarak sutunları kontrol ediyorum.

            sayac2++; //sutun sonucu tutan sutun padding
            if (sayac2 == sonuc) //sayac2, matrisin size'na geldigi zaman bir sonraki satira atlatiyorum.
            {
                mat1sutuntut = 0; //yine padding islemine baslarken en bastan baslamasi icin sifirliyorum.
                mat1satirtut++; //padding isleminde ilgili satir bittigi icin bir sonraki satira geciyorum.
                sayac2 = 0; //yine islemler silsilesinin devami icin sayac2'yi sifirliyorum.
            }

            sayac++; //sutun sonuc*sonuc

            sonucMatris[k][m] = islem; // sonucMatrisimin indislerine islemi atıyorum.
            m++; //kaldıgı sutunu ilerletiyorum.
            if (m == sonuc) //sutun sonuna(sonuca) geldigi takdirde bir sonraki satira gecmesi icin 
            {
                m = 0; //sutunu sifirliyorum
                k++; //satiri arttiriyorum.
            }

            islem = 0; //bir sonraki islem icin, islemimi sifirliyorum

            if (sayac == sonuc * sonuc)
            {
                mat1satirtut = 0;
                printf("------------CIKTI MATRISI----------- \n"); //dogrulugunu kontrol etmem icin yazdiriyorum.
                for (i = 0; i < sonuc; i++)
                {
                    for (j = 0; j < sonuc; j++)
                    {
                        printf("%d  ", sonucMatris[i][j]);
                    }
                    printf("\n");
                }
                durum = 0;
            }
        }
        return sonucMatris; //fonksiyonun donus parametresi.
    }

    if (islemTipi == 1) //iki farklı islem tipimiz vardı 1 ve 0. 0 icin olan kod blogu baslangici
    {
        // islem 1 icin parametreler


        int sayac = 0; //gezinme isleminin kac kere oldugunu kontrol etmem icin gereken degisken.

        int durum = 1; //olusturdugum while dongusunu kontrol etmem icin gerekli olan degiskenim.
        int sayac2 = 0; //gezinme isleminin kac kere oldugunu kontrol etmem icin gereken degisken.

        int dolgulusatirtut = 0;
        int dolgulusutuntut = 0;

        int dolgusatir = 0;
        int dolgusutun = 0;

        int islem = 0; //islemi hesaplayip tutmama yarayan degisken.

        int i, j;
        sonuc = (((G - F) + (2 * D)) / 1) + 1;
        printf("Cikti Matris Boyutu: %d\n", sonuc);

        int k = 0;
        int m = 0;

        int padMatrisSize; //padding islemini yapacak matrisin size'ını tutan degisken
        padMatrisSize = Matris2SatirSayisi; //matrisin boyu matris2 kadar olmali. padding matrisim zaten matris2.
        int dolguluMatrisSize; //dolgu degerine gore olusacak matrisin yeni size'ı.

        //iki durum ele alinacak foyde de belirtildigi uzere.
        if(D==1){//matris2 sadece 3x3 ve 5x5 icin gecerli 3x3 ise m1+2
            dolguluMatrisSize=matris1SatirSayisi+2;  //matris2 boyu 5 ise D=1 cikar ve dolgulu matris boyu 7 olmalidir.
        }
        if(D==2){//5x5 ise m1+4
            dolguluMatrisSize=matris1SatirSayisi+4; //matris boyu 3 ise D=2 cikar ve dolgulu matris boyu 9 olmalidir.
        }

        int **dolguluMatris = (int **)malloc(dolguluMatrisSize * sizeof(int *));  //yukarda hesaplanan dolguluMatrisSize'ina gore matris olusturdum.
        for (i = 0; i < dolguluMatrisSize; i++)
        {
            dolguluMatris[i] = (int *)malloc(dolguluMatrisSize * sizeof(int));
        }

        int **padMatris = (int **)malloc(Matris2SatirSayisi * sizeof(int *)); //paddlenecek matris'i olusturdum. 
        for (i = 0; i < Matris2SatirSayisi; i++)
        {
            padMatris[i] = (int *)malloc(Matris2SatirSayisi * sizeof(int)); 
        }

        int **sonucMatris = (int **)malloc(sonuc * sizeof(int *)); //islemleri atacagim matris'i olusturdum.
        for (i = 0; i < sonuc; i++)
        {
            sonucMatris[i] = (int *)malloc(sonuc * sizeof(int));
        }
        printf("Dolgulumatris Size = %d \n",dolguluMatrisSize);
        for (i = 0; i < dolguluMatrisSize; i++)
        {
            for (j = 0; j < dolguluMatrisSize; j++) 
            {
                /*
                Dolgulu matrisin ilk once dolgu olacak elemanlarina sifir islemi atamaktayim.
                matris2 5x5 oldugu takdirde; dolgu yapilacak alan 2 kat olacak.
                haliyle gerekli olusturmus oldugum algoritma asagidaki gibidir.
                matris2 3x3 oldugu takdirde; dolgu yapilacak alan 1 kat olacak.
                */
                if (Matris2SatirSayisi == 5)
                {

                    if (i > matris1SatirSayisi + 1)
                    {
                        dolguluMatris[i][j] = 0;
                    }
                    if (j > matris1SatirSayisi + 1)
                    {
                        dolguluMatris[i][j] = 0;
                    }

                    if (i < D)
                    {
                        dolguluMatris[i][j] = 0;
                    }
                    if (j < D)
                    {
                        dolguluMatris[i][j] = 0;
                    }
                }

                if (Matris2SatirSayisi == 3)
                {
                    if (i > matris1SatirSayisi)
                    {
                        dolguluMatris[i][j] = 0;
                    }
                    if (j > matris1SatirSayisi)
                    {
                        dolguluMatris[i][j] = 0;
                    }

                    if (i < D)
                    {
                        dolguluMatris[i][j] = 0;
                    }
                    if (j < D)
                    {
                        dolguluMatris[i][j] = 0;
                    }
                }
            }
        }

        /*
        Dolgu islemini olusturdum Matrisim bu sekil olabilir; 

        0      0      0       0   0
        0   -1234   -1234   -1234 0  
        0   -1234   -1234   -123  0
        0   -1234   -1234   -123  0
        0   -1234   -1234   -123  0
        0     0       0        0  0
        */

        for (i = 0; i < dolguluMatrisSize; i++)
        {
            for (j = 0; j < dolguluMatrisSize; j++)
            {
                /*
                yukardaki ornek gibi olan matrisin indislerindeki deger 0 olmayanlari bulup;
                matris1'deki elemanlari teker teker sirayla atama islemi yapmaktayim.
                */
                if (dolguluMatris[i][j] != 0)
                {
                    dolguluMatris[i][j] = matris1[dolgusatir][dolgusutun];
                    dolgusutun++; //sutunlari hareket ettiriyorum sadece
                    if (dolgusutun == matris1SatirSayisi)
                    {
                        dolgusatir++; //matris1 sutun sayisina geldiginde satiri bir arttiririm.
                        dolgusutun = 0; //sutunu tekrar sifirlarim.
                    }
                }
            }

        } 
        //başarıyla dolgu yapıldı.
        //dolgulu matrisi kullaniciya bastirdim.
        printf("----------DOLGU ISLEMI-------------\n");
        for (i = 0; i < dolguluMatrisSize; i++)
        {
            for (j = 0; j < dolguluMatrisSize; j++)
            {
                printf("%d ",dolguluMatris[i][j]);
            }
            printf("\n");
        }

        while (durum == 1)
        {
            //artik islem 0 da da yaptigim gibi padding islemlerini teker teker yaptirip matrisime atiyorum.
            for (i = 0; i < padMatrisSize; i++)
            {
                for (j = 0; j < padMatrisSize; j++)
                {
                    padMatris[i][j] = dolguluMatris[i + dolgulusatirtut][j + dolgulusutuntut];
                    //printf("sayac =%d sayac2=%d mat1satirtut=%d mat1sutuntut=%d padMatris[i][j]= %d, %d  matris1[i+satut][j+sutut]= %d, %d \n",sayac,sayac2,mat1satirtut,mat1sutuntut,i,j,(i+mat1satirtut),(j+mat1sutuntut));
                }
            }
            /*
            printf("------------PAD----------- \n");
            for (i = 0; i < padMatrisSize; i++)
            {
                for (j = 0; j < padMatrisSize; j++)
                {
                    printf("%d  ", padMatris[i][j]);
                }
                printf("\n");
            }
            */

            for (i = 0; i < Matris2SatirSayisi; i++)
            {
                for (j = 0; j < Matris2SatirSayisi; j++)
                {
                    islem += padMatris[i][j] * matris2[i][j];
                }
            }

            //printf("islem = %d",islem);
            dolgulusutuntut++;
            sayac2++; //sutun sonucu tutan sutun padding
            if (sayac2 == sonuc)
            {
                dolgulusutuntut = 0;
                dolgulusatirtut++;
                sayac2 = 0;
            }

            sayac++; //sutun sonuc*sonuc

            sonucMatris[k][m] = islem;
            m++;
            if (m == sonuc)
            {
                m = 0;
                k++;
            }

            islem = 0;

            if (sayac == sonuc * sonuc)
            {
                dolgulusatirtut = 0;
                printf("------------CIKTI MATRISI----------- \n");
                for (i = 0; i < sonuc; i++)
                {
                    for (j = 0; j < sonuc; j++)
                    {
                        printf("%d  ", sonucMatris[i][j]);
                    }
                    printf("\n");
                }
                durum = 0;

            }

        }
        return sonucMatris; //en son cikan matrisi dondurmekteyim.
    }


}