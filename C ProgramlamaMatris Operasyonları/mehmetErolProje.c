/*
* @file mehmetErolProje
* @description Bu Odev, parametre olarak kullanici tarafindan girilen,
               Matris1 ve Matris2'nin sizelarına gore padding islemi ve 
               ve cikti matrisini gostermektedir. Daha cok goruntu
               isleme uygulamalari gibi uygulamalarda kullanilabilir.
* @assignment 1. Odev
* @date 14.12.2021
* @author Mehmet Erol | mehmet.erol@stu.fsm.edu.tr
*/
#include "matrisoperations.h"
#include <stdio.h>
#include <stdlib.h>



int main()
{

    int islemtipi;  //kullanicidan 0 ve ya 1 islem secmesini saglayacak degiskenim.
    int m1boy, m2boy; //matris1 ve matris2'nin boylarini tutan degiskenler


    printf("Matris1 Boy Girin: ");
    scanf("%d", &m1boy);
    if (m1boy % 2 == 0)//matris1 boyu tekxtek degilse program sonlanır.
    {
        printf("Matris1 Boyunu Tek Sayı Girmediniz Program Sonlanıyor..");
        return 0;
    }
    if (m1boy % 2 == 1)//matris1 boyu tekxtek ise programa devam edilir.
    {
        printf("Matris2 Boy Girin: ");
        scanf("%d", &m2boy);
        if (m2boy>m1boy)
        {
            return 0;
        }
        
        if (m2boy % 2 == 0)//matris1 boyu tekxtek degilse program sonlanır.
        {
            printf("Matris2 Boyunu Tek Sayı Girmediniz Program Sonlanıyor..");
            return 0;
        }
        if (m2boy % 2 == 1)//matris1 boyu tekxtek ise programa devam edilir.
        {
            if (m2boy == 5 || m2boy == 3)// foyde belirtildigi gibi matris2 boyu 3x3 ve ya 5x5 olmalıdır.
            {
                printf("Islem Tipini Seciniz: ");
                scanf("%d", &islemtipi);

                if(islemtipi==1 ||islemtipi==0){
                int seed;
                printf("Seed Degeri Giriniz: ");
                scanf("%d", &seed);
                int **matris1;
                matris1 = matris1olustur(m1boy, m1boy);
                int **matris2;
                matris2 = matris2olustur(m2boy, m2boy);
                int i, j;
                int k = 1; //matrislere deger atamasi yapmasi icin olusturulan degisken.
                srand(seed);
                printf("------------MATRIS 1-----------\n");
                for (i = 0; i < m1boy; i++)
                {
                    for (j = 0; j < m1boy; j++)
                    {
                        matris1[i][j] = 1+rand() % 10;
                        printf("%d  ", matris1[i][j]);
                    }
                    printf("\n");
                }

                printf("------------MATRIS 2-----------\n");
                for (i = 0; i < m2boy; i++)
                {
                    for (j = 0; j < m2boy; j++)
                    {
                        matris2[i][j] = 1+rand() % 10;
                        printf("%d  ", matris2[i][j]);
                    }
                    printf("\n");
                }
                operasyon1(matris1,matris2,islemtipi,m1boy,m2boy);
                }
                else{
                    printf("Islem Tipi 1 ve 0 olmalidir. Program Sonlaniyor..");
                    return 0;
                }

            }
            else{
                printf("Matris2 boyutu sadece 3x3 ve 5x5'lik olmalıdır. Program sonlanıyor..");
                return 0;
            }
        }
    }

    return 0;
}

