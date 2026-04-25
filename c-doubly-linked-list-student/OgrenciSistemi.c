#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Ogrenci
{
    int numara;
    char tc[12];
    char ad[30];
    char soyad[30];
    char bolum[50];
    char dersler[100];

    struct Ogrenci* next; // önceki öğrenci
    struct Ogrenci* prev; // sonraki öğrenci
};

struct Ogrenci* head = NULL; // liste başı (ilk eleman) boş olarak belirledik yani liste boş.

// Öğrenci ekleme
void ogrenciEkle(int numara, char tc[], char ad[], char soyad[], char bolum[], char dersler[])
{
    struct Ogrenci* yeni = (struct Ogrenci*)malloc(sizeof(struct Ogrenci));

    yeni->numara = numara;

    strcpy(yeni->tc, tc);
    strcpy(yeni->ad, ad);
    strcpy(yeni->soyad, soyad);
    strcpy(yeni->bolum, bolum);
    strcpy(yeni->dersler, dersler);

    yeni->next = NULL;
    yeni->prev = NULL;

        if(head == NULL)
    {
        head = yeni;
    }
        else
    {
        struct Ogrenci* temp = head;

        while(temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = yeni;
        yeni->prev = temp;
    }
}

// Öğrenci silme
void listele()
{
    struct Ogrenci* temp = head;

    while(temp != NULL)
    {
        printf("No: %d\n", temp->numara);
        printf("Ad: %s\n", temp->ad);
        printf("Soyad: %s\n", temp->soyad);
        printf("Bolum: %s\n", temp->bolum);
        printf("Dersler: %s\n", temp->dersler);

        printf("-------------------\n");

        temp = temp->next;
    }
}

// Veri yapıları ve algoritmalar dersi alanlar
void veriYapilariListele()
{
    struct Ogrenci* temp = head;

    while(temp != NULL)
    {
        if(strstr(temp->dersler, "Veri Yapilari") != NULL)
        {
            printf("%s %s\n", temp->ad, temp->soyad);
        }

        temp = temp->next;
    }
}

// ada göre sıralama
void adaGoreSirala()
{
    struct Ogrenci *i, *j;

    for(i = head; i != NULL; i = i->next)
    {
        for(j = i->next; j != NULL; j = j->next)
        {
            if(strcmp(i->ad, j->ad) > 0)
            {
                struct Ogrenci temp = *i;
                
                struct Ogrenci* i_next = i->next;
                struct Ogrenci* i_prev = i->prev;
                *i = *j;
                i->next = i_next;
                i->prev = i_prev;

                struct Ogrenci* j_next = j->next;
                struct Ogrenci* j_prev = j->prev;
                *j = temp;
                j->next = j_next;
                j->prev = j_prev;
            }
        }
    }
}

/* Quick Sort ()hızlı sıralama algoritması), parçala yönet prensibiyle çalışır.
Çalışma mantığı:
1.Pivot seçimi: Listedden bir eleman eleman seçilir. (buna pivot denir)
2.Bölümleme: Listedeki diğer elemanlar pivot ile karşılaştırılır. 
    - Pivot'tan küçük olanlar pivotun soluna, 
    -büyük olanlar ise sağına yerleştirilir.
3.Özyineleme: Sol ve sağ alt listeler için aynı işlemler tekrarlanır. 
    -Bu işlem, alt listeler tek eleman kalana kadar devam eder.

Bu çalışmada da tüm listeyi değil sadece veri yapıları ve algoritmalar dersini alan öğrencileri sıralayacağız.
*/

// karşılaştırma yapabilmek için öğrencileri diziye aktarıyoruz çünkü linked listte elemanlara indeksle erişim yoktur.
// linked list -> diziye çevirme

int partition(struct Ogrenci* arr[], int low, int high)
{
    int pivot = arr[high]->numara;
    int i = low - 1;

    for(int j = low; j < high; j++)
    {
        if(arr[j]->numara < pivot)
        {
            i++;
            struct Ogrenci* temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    struct Ogrenci* temp = arr[i+1];
    arr[i+1] = arr[high];
    arr[high] = temp;

    return i+1;
}

void quickSort(struct Ogrenci* arr[], int low, int high)
{
    if(low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void quickSortListele()
{
    struct Ogrenci *dizi[50]; // maksimum 50 öğrenci olduğunu varsayıyoruz
    int ogrenciSayisi = 0; // öğrenci sayısını takip etmek için

    struct Ogrenci *temp = head; // geçici pointer, liste içinde gezmek için
    while(temp != NULL)
    {
        if(strstr(temp->dersler, "Veri Yapilari") != NULL) // eğer öğrenci veri yapıları dersini alıyorsa
        {
            dizi[ogrenciSayisi] = temp; // öğrenciyi diziye ekle
            ogrenciSayisi++; // öğrenci sayısını artır
        }
        temp = temp->next;
    }

    if(ogrenciSayisi > 0)
    {
        quickSort(dizi, 0, ogrenciSayisi - 1);
        
        for(int i = 0; i < ogrenciSayisi; i++)
        {
            printf("%d %s %s\n", dizi[i]->numara, dizi[i]->ad, dizi[i]->soyad);
        }
    }
}


int main()
{
    ogrenciEkle(1001, "12345678901", "Alparslan", "Yilmaz", "Bilgisayar Mühendisliği", "Veri Yapilari ve Algoritmalar");
    ogrenciEkle(1002, "45678912345", "Evrim", "Demir", "Yazılım Mühendisliği", "Matematik");
    ogrenciEkle(1003, "78945612378", "Metehan", "Kaya", "Bilgisayar Mühendisliği", "Veri Yapilari ve Algoritmalar");
    ogrenciEkle(1004, "65432198745", "Mine", "Tas", "Bilgisayar Mühendisliği", "Fizik");

    printf("\nTum Ogrenciler:\n");
    listele();

    printf("\nVeri Yapilari ve Algoritmalar Dersi Alanlar:\n");
    veriYapilariListele();

    adaGoreSirala();

    printf("\nAda Gore Siralanmis Liste:\n");
    listele();

    quickSortListele();

    return 0;
}