#include <stdio.h>
#include <stdlib.h>

char GlobalUsername[32];

typedef struct book
{
    int book_id[4];
    char book_name[32];
    char writer[32];
    char publisher[32];
    int number_of_borrowing;
    int status;
}book_t;

typedef struct student
{
    int stu_id[6];
    char stu_name[32];
    int total_book_barrowed;
    char password[8];
    book_t *book;
}student_t;

typedef struct librarian
{
    int lib_id[6];
    char librarian_name[32];
    char password[8];
}librarian_t;

book_t TheBook;
struct book *savebook;

int login();
void library();
void StuLogin();
void ListBook();
void BarrowBook();
void returnBook();
int SaveBorrowBook(int okunanBookId2,char okunanBookName2[32] ,char okunanWriter2[32],char okunanPublisher2[32],int okunanNOB2,int okunanStatus2);

void LbrLogin();
void ListBookLbr();
void bookSearch();
void updateBook();
void addBook();
void dellBook();

int main()
{
    printf("\n**** KUTUPHANE OTOMASYONUNA HOSGELDINIZ ****\n");
    printf("---------------------------------------------\n\n");
    printf("Devam etmek icin lutfen giris yapin\n\n");

    int x = login();

    if (x==1)
    {
        StuLogin();
    }
    else if (x==2)
    {
        LbrLogin();
    }
    else if(x==0)
    {
        while(x==0)
        {
            printf("\n*** Kullanici adi veya sifre hatali, Lutfen tekrar deneyin ***\n\n");
            x = login();
            if(x==1)
            {
                StuLogin();
            }
            else if(x==2)
            {
                LbrLogin();
            }
        }
    }

    return 0;
}

int login()
{
    char kullanici_adi[32];
    char b[32];
    char sifre[8];
    char a[8];
    int check;
    printf("ad soyad:");
    scanf("%s",&kullanici_adi);
    printf("sifre:");
    scanf("%s",&sifre);

    FILE *fPtr;
    if( (fPtr = fopen("student.bin", "rb")) == NULL)
    {
        printf("dosya olusturulamadi...");
        return -1;
    }
    else
    {
        int okunan_Id;
        char okunan_name[32];
        char okunan_password[8];
        int okunan_toplam_kira;
        char okunan_adress[8];

        fseek(fPtr, 0, SEEK_SET);
        fscanf(fPtr,"%d",&okunan_Id);
        fscanf(fPtr,"%s",&okunan_name);
        fscanf(fPtr,"%s",&okunan_password);
        fscanf(fPtr,"%d",&okunan_toplam_kira);
        fscanf(fPtr,"%s",&okunan_adress);


        if(strcmp(kullanici_adi,okunan_name) == 0 && strcmp(sifre,okunan_password) == 0)
        {
            GlobalUsername[32]="";
            strcpy(GlobalUsername,okunan_name);
            printf("\n*** Hosgeldin %s, Giris Basarili ***\n",kullanici_adi);
            return 1;
        }
        else if(strcmp(kullanici_adi,okunan_name) != 0 && strcmp(sifre,okunan_password) != 0 && !feof(fPtr))
        {

            while(strcmp(kullanici_adi,okunan_name) != 0 && strcmp(sifre,okunan_password) != 0 && feof(fPtr)==0)
            {

                fscanf(fPtr,"%d",&okunan_Id);
                fscanf(fPtr,"%s",&okunan_name);
                fscanf(fPtr,"%s",&okunan_password);
                fscanf(fPtr,"%d",&okunan_toplam_kira);
                fscanf(fPtr,"%s",&okunan_adress);

                if(strcmp(kullanici_adi,okunan_name) == 0 && strcmp(sifre,okunan_password) == 0)
                {
                    GlobalUsername[32]="";
                    strcpy(GlobalUsername,okunan_name);
                    printf("\n*** Hosgeldin %s,  Giris Basarili ***\n",kullanici_adi);
                    return 1;
                }
            }
        }
    }
    fclose(fPtr);

    /*------------------------------------------------------------------------------------------------------------------------*/

    FILE *fPtr2;
    if( (fPtr2 = fopen("librarian.bin", "rb")) == NULL)
    {
        printf("dosya olusturulamadi...");
        return -1;
    }
    else
    {
        int okunan_Id;
        char okunan_name[32];
        char okunan_password[8];

        fseek(fPtr2, 0, SEEK_SET);
        fscanf(fPtr2,"%d",&okunan_Id);
        fscanf(fPtr2,"%s",&okunan_name);
        fscanf(fPtr2,"%s",&okunan_password);

        if(strcmp(kullanici_adi,okunan_name) == 0 && strcmp(sifre,okunan_password) == 0)
        {
            printf("\n*** Hosgeldin %s,  Giris Basarili ***\n",kullanici_adi);
            return 2;
        }
        else if(strcmp(kullanici_adi,okunan_name) != 0 && strcmp(sifre,okunan_password) != 0 && !feof(fPtr2))
        {

            while(strcmp(kullanici_adi,okunan_name) != 0 && strcmp(sifre,okunan_password) != 0 && feof(fPtr2)==0)
            {
                fscanf(fPtr2,"%d",&okunan_Id);
                fscanf(fPtr2,"%s",&okunan_name);
                fscanf(fPtr2,"%s",&okunan_password);

                if(strcmp(kullanici_adi,okunan_name) == 0 && strcmp(sifre,okunan_password) == 0)
                {
                    printf("\n*** Hosgeldin %s,  Giris Basarili ***\n",kullanici_adi);
                    return 2;
                }
            }
        }
    }
    fclose(fPtr2);
}

void StuLogin()
{
    printf("\nLuften bekleyin...");
    sleep(1);
    system("cls");

    printf("\n**** KUTUPHANE OTOMASYONUNA HOSGELDINIZ ****\n");
    printf("---------------------------------------------\n\n");

    printf("1-) Kitaplara Goz At \n2-) Odunc Kitap Al\n3-) Kitap Iade Et\n4-) Cikis\n\n");

    int deger;
    printf("Lutfen Ne Yapmak Istediginizi Secin : ");
    scanf("%d",&deger);

    switch(deger)
    {
        case 1:
            system("cls");
            ListBook();
            break;
        case 2:
            system("cls");
            BarrowBook();
            break;
        case 3:
            system("cls");
            returnBook();
            break;
        case 4:
            return 0;
            break;
        default:
            printf("\n*** Gecersiz Bir Deger Girildi, Lutfen Tekrar Deneyin ***\n");
            StuLogin();
    }
}

void library()
{
    FILE *fPtr;
    if( (fPtr = fopen("book.bin", "rb")) == NULL)
    {
        printf("dosya olusturulamadi...");
        return -1;
    }
    else
    {
        int okunanStatus;
        char status1[15]="Odunc Verildi";
        char status2[15]="Musait";
        int okunanBookId;
        int eskiokunanBookId;
        char okunanBookName[32];
        char okunanWriter[32];
        char okunanPublisher[32];
        int okunanNOB;
        int sayac=0;

        printf("\n %15s | %4s | %32s | %32s | %32s | %7s\n","Durumu","ID","Kitap Adi","Kitabin Yazari","Kitabin Yayinevi","Kiralanma sayisi");
        printf("------------------------------------------------------------------------------------------------------------------------------------------------------\n");

        fseek(fPtr, 0, SEEK_SET);
        do
        {
            fscanf(fPtr,"%d%s%s%s%d%d",&okunanBookId,okunanBookName,okunanWriter,okunanPublisher,&okunanNOB,&okunanStatus);

                if(okunanBookId==0)
                {
                    eskiokunanBookId = okunanBookId;
                    sayac+=1;
                    continue;
                }


                if(eskiokunanBookId!=okunanBookId && okunanBookId!=0)
                {
                        eskiokunanBookId = okunanBookId;
                        sayac+=1;
                        if(okunanStatus==1)
                        {
                            printf(" %15s |",status2);
                        }
                        else if(okunanStatus==0)
                        {
                            printf(" %15s |",status1);
                        }
                        printf(" %d | %32s | %32s | %32s | %d\n",
                                okunanBookId,
                                okunanBookName,
                                okunanWriter,
                                okunanPublisher,
                                okunanNOB
                                );
                }

        }while(!feof(fPtr));
    }
    fclose(fPtr);
}

void ListBook()
{
    library();

    printf("\n\n1-) Odunc Kitap Al\n2-) Kitap Iade Et\n3-) Anasayfaya Don\n4-) Cikis\n\n");

    int deger;
    printf("Lutfen Ne Yapmak Istediginizi Secin : ");
    scanf("%d",&deger);

    switch(deger)
    {
        case 1:
            BarrowBook();
            break;
        case 2:
            returnBook();
            break;
        case 3:
            system("cls");
            StuLogin();
            break;
        case 4:
            return 0;
        default:
            system("cls");
            printf("\n*** Gecersiz Bir Deger Girildi, Lutfen Tekrar Deneyin ***\n\n");
            ListBook();
    }
}

BarrowBook()
{
    int Id;
    printf("\nOdunc almak istediginiz kitabin Id numarasini girin :");
    scanf("%d",&Id);

    FILE *fPtr;

    if( (fPtr = fopen("book.bin", "rb+")) == NULL)
    {
        printf("dosya olusturulamadi...");
        return -1;
    }
    else
    {
        int okunanStatus;
        int okunanBookId;
        char okunanBookName[32];
        char okunanWriter[32];
        char okunanPublisher[32];
        int okunanNOB;
        int sayac=0;

        fseek(fPtr, 0, SEEK_SET);

        while(!feof(fPtr))
        {
            fscanf(fPtr,"%d%s%s%s%d%d",&okunanBookId,&okunanBookName,&okunanWriter,&okunanPublisher,&okunanNOB,&okunanStatus);

            if(Id==okunanBookId)
            {
                char okunanBookName2[32];
                char okunanWriter2[32];
                char okunanPublisher2[32];

                okunanBookName2[32] =okunanBookName;
                okunanWriter2[32]=okunanWriter;
                okunanPublisher2[32]=okunanPublisher;
                int okunanBookId2 = okunanBookId;
                int okunanNOB2 = okunanNOB;
                int okunanStatus2 = okunanStatus;

                strcpy(okunanBookName2,okunanBookName);
                strcpy(okunanWriter2,okunanWriter);
                strcpy(okunanPublisher2,okunanPublisher);
                sayac+=1;

                printf("\n*** Asagida Bilgileri Bulunan Kitab Odunc Aliniyor ... ***\n\n");
                printf("%d | %s | %s | %s \n\n",
                       okunanBookId2,
                       okunanBookName2,
                       okunanWriter2,
                       okunanPublisher2
                       );

                if(okunanStatus==0)
                {
                    printf("\n*** Odunc Alma Basarisiz, Kitap Daha Once Odunc Verildigi Icin Odunc Alinamadi ***\n");
                    printf("\n*** Ana Menuye Yonlendiriliyorsunuz... ***\n\n");
                    sleep(1);
                    StuLogin();
                }
                else if(okunanStatus==1)
                {
                    int h;
                    okunanStatus2=0;
                    okunanStatus2+=1;

                    h = SaveBorrowBook(okunanBookId2,okunanBookName2,okunanWriter2,okunanPublisher2,okunanNOB2,okunanStatus2);
                    if(h==1)
                    {

                        printf("\n*** Odunc Alma Islemi Basarili , Anasayfaya Yonlendiriliyorsunuz ... ***\n");
                        sleep(3);
                        StuLogin();

                    }
                    else
                    {
                        sleep(1);
                        printf("\n*** Bilinmedik Bir Hata oldu Lutfen Daha Sonra Tekrar Deneyin ***\n");
                        printf("\n*** Anasayfaya Yonlendiriliyorsunuz ... ***\n");
                        StuLogin();

                    }
                }
                break;
            }
        }
        fclose(fPtr);
        if(sayac==0)
        {
            int t;
            do
            {
                printf("\n*** Girdiginiz Id'ye Sahip Kitap Bulunamadi ***\n");
                printf("\n1-)Odunc Kitap al\n");
                printf("2-)Anasayfa\n");
                printf("3-)Cikis\n");
                printf("\nLutfen Yapmak Istediginiz Islemi Secin :");
                scanf("%d",&t);

                switch(t)
                {
                    case 1:
                        BarrowBook();
                        break;
                    case 2:
                        StuLogin();
                        break;
                    case 3:
                        return 0;
                    default:
                        printf("\n*** Gecersiz Bir Deger Girdiniz Lutfen Tekrar Deneyin ***\n");
                        t=0;
                        break;
                }
            }while(t==0);
        }
    }
}

int SaveBorrowBook(int okunanBookId2,char okunanBookName2[32] ,char okunanWriter2[32],char okunanPublisher2[32],int okunanNOB2,int okunanStatus2)
{
    FILE *fPtr;

    if( (fPtr = fopen("book.bin", "rb+")) == NULL)
    {
        printf("dosya olusturulamadi...");
        return -1;
    }
    else
    {
        int dosyadanOkunanStatus;
        int dosyadanOkunanBookId;
        char dosyadanOkunanBookName[32];
        char dosyadanOkunanWriter[32];
        char dosyadanOkunanPublisher[32];
        int dosyadanOkunanNOB;

        fseek(fPtr, 0, SEEK_SET);
        int sayac=0;
        while(!feof(fPtr))
        {
            sayac+=1;
            fscanf(fPtr,"%d%s%s%s%d%d",&dosyadanOkunanBookId,dosyadanOkunanBookName,dosyadanOkunanWriter,dosyadanOkunanPublisher,&dosyadanOkunanNOB,&dosyadanOkunanStatus);
            if(dosyadanOkunanBookId==okunanBookId2)
            {
                TheBook.book_id[0]=dosyadanOkunanBookId/1000;
                TheBook.book_id[1]=(dosyadanOkunanBookId-(TheBook.book_id[0]*1000))/100;
                TheBook.book_id[2]=(dosyadanOkunanBookId-(TheBook.book_id[0]*1000)-(TheBook.book_id[1]*100))/10;
                TheBook.book_id[3]=dosyadanOkunanBookId%10;
                strcpy(TheBook.book_name,dosyadanOkunanBookName);
                strcpy(TheBook.writer,dosyadanOkunanWriter);
                strcpy(TheBook.publisher,dosyadanOkunanPublisher);
                TheBook.number_of_borrowing=(dosyadanOkunanNOB+1);
                TheBook.status=0;
                break;
            }
        }

        if(sayac==1)
        {
            fseek(fPtr,0,SEEK_SET);
            fseek(fPtr,(sayac-1)*sizeof(book_t),SEEK_CUR);

            fprintf(fPtr,"%d%d%d%d\t%32s\t%32s\t%32s\t%d\t%d",TheBook.book_id[0],TheBook.book_id[1],TheBook.book_id[2],TheBook.book_id[3],TheBook.book_name,TheBook.writer,TheBook.publisher,TheBook.number_of_borrowing,TheBook.status);
        }
        else
        {
            fseek(fPtr,1-sizeof(dosyadanOkunanStatus)-sizeof(dosyadanOkunanNOB)-sizeof(dosyadanOkunanPublisher)-sizeof(dosyadanOkunanWriter)-sizeof(dosyadanOkunanBookName)-sizeof(dosyadanOkunanBookId),SEEK_CUR);
            fprintf(fPtr,"%d%d%d%d\t%32s\t%32s\t%32s\t%d\t%d",TheBook.book_id[0],TheBook.book_id[1],TheBook.book_id[2],TheBook.book_id[3],TheBook.book_name,TheBook.writer,TheBook.publisher,TheBook.number_of_borrowing,TheBook.status);
        }
    }
    fclose(fPtr);

    /* --------------------------------------------------------------------------------------------------------------------- */

    FILE *fPtr2;

    if( (fPtr2 = fopen("student.bin", "rb+")) == NULL)
    {
        printf("dosya olusturulamadi...");
        return -1;
    }
    else
    {
        int okunan_IdS;
        char okunan_nameS[32];
        char okunan_passwordS[8];
        char okunan_adressS[8];
        int okunanTotal_barrow;

        int sayac=0;

        fseek(fPtr2, 0, SEEK_SET);

        while(!feof(fPtr2))
        {
            sayac= sayac+1;
            fscanf(fPtr2,"%d%s%s%d%p",&okunan_IdS,okunan_nameS,okunan_passwordS,&okunanTotal_barrow,&savebook);

                if(strcmp(GlobalUsername,okunan_nameS)==0)
                {
                    savebook = (book_t*) malloc(sizeof(book_t));

                    savebook->book_id[0]=TheBook.book_id[0];
                    savebook->book_id[1]=TheBook.book_id[1];
                    savebook->book_id[2]=TheBook.book_id[2];
                    savebook->book_id[3]=TheBook.book_id[3];
                    strcpy(savebook->book_name,TheBook.book_name);
                    strcpy(savebook->writer,TheBook.writer);
                    strcpy(savebook->publisher,TheBook.publisher);
                    savebook->number_of_borrowing=TheBook.number_of_borrowing;
                    savebook->status=TheBook.status;


                    okunanTotal_barrow = okunanTotal_barrow + 1;
                    fseek(fPtr2,-2-sizeof(savebook)-sizeof(okunanTotal_barrow),SEEK_CUR);
                    fprintf(fPtr2,"%d\t%p",okunanTotal_barrow,savebook);

                    printf("kitabin kaydedildigi pointer'in adresi %p\nkaydedilen book id %d%d%d%d\nkaydedilen name %s\nkaydedilen writer %s\nkaydedilen publisher %s\nkaydedilen number_of_borrowing %d\nkaydedilen status %d\n-------\n",
                           savebook,
                           savebook->book_id[0],
                           savebook->book_id[1],
                           savebook->book_id[2],
                           savebook->book_id[3],
                           savebook->book_name,
                           savebook->writer,
                           savebook->publisher,
                           savebook->number_of_borrowing,
                           savebook->status);
                     break;
                }
        }
    }
    fclose(fPtr2);

    return 1;
}

void returnBook()
{
        printf("\n *** PROGRAM KITAP ODUNC ALIRKEN DOGRU BIR SEKILDE KITABI PONTER'A KAYIT EDEREK, POINTER'IN ADRESINI BINARY DOSYAYA KAYIT ALIYOR ***\n");
        printf("\n *** AMA BU ADRESI KULLANARAK ODUNC ALINAN KITABIN BILGILERINE ULASAMADIM ***\n");
        printf("\n *** ODUNC ALMAYI SORUNSUZ BIR SEKILDE GERCEKLESTIRIYORUM AMA DEDIGIM GIBI IADE ETMEYI YAPAMADIM ***\n");

        int a;
        printf("\n\nAnasayfaya Donmek Icin Herhangi Bir Sayiya Basin :");
        scanf("%d",&a);

        switch(a)
        {
        case 1:
            StuLogin();
            break;
        default:
            StuLogin();
            break;
        }

}

void LbrLogin()
{
    printf("\nLuften bekleyin...");
    sleep(1);
    system("cls");
    printf("\n**** KUTUPHANE OTOMASYONUNA HOSGELDINIZ ****\n");
    printf("---------------------------------------------\n\n");
    printf(" 1-) Kitap Listesi \n 2-) Kitap Ara\n 3-) Kitap Bilgilerini Guncelle\n 4-) Yeni Kitap Ekle \n 5-) Listeden Kitap Sil\n 6-) Cikis\n\n");
    int deger;
    printf("Lutfen Ne Yapmak Istediginizi Secin : ");
    scanf("%d",&deger);
    switch(deger)
    {
        case 1:
            system("cls");
            ListBookLbr();
            break;
        case 2:
            system("cls");
            bookSearch();
            break;
        case 3:
            system("cls");
            updateBook();
            break;
        case 4:
            system("cls");
            addBook();
            break;
        case 5:
            system("cls");
            dellBook();
            break;
        case 6:
            return 0;
            break;
        default:
            printf("\n*** Gecersiz Bir Deger Girildi, Lutfen Tekrar Deneyin ***\n");
            LbrLogin();
            break;
    }
}

void ListBookLbr()
{
    library();
    printf("\n 1-) Kitap Ara\n 2-) Kitap Bilgilerini Guncelle\n 3-) Yeni Kitap Ekle \n 4-) Listeden Kitap Sil\n 5-) Anasayfaya Don\n\n");

    int deger;
    printf("Lutfen Ne Yapmak Istediginizi Secin : ");
    scanf("%d",&deger);

    switch(deger)
    {
        case 1:
            bookSearch();
            break;
        case 2:
            updateBook();
            break;
        case 3:
            addBook();
            break;
        case 4:
            dellBook();
            break;
        case 5:
            LbrLogin();
            break;
        default:
            system("cls");
            printf("\n*** Gecersiz Bir Deger Girildi, Lutfen Tekrar Deneyin ***\n\n");
            ListBook();
            break;
    }
}

void bookSearch()
{
    char arananDeger[32];
    int w=0;

    printf("\nAramak Istediginiz Kitabin ismini Giriniz : ");
    scanf("%32s",&arananDeger);
    printf("\n");

    FILE *fPtr;
    if( (fPtr = fopen("book.bin", "rb")) == NULL)
    {
        printf("dosya olusturulamadi...");
        return -1;
    }
    else
    {
        int okunanStatus;
        char status1[15]="Odunc Verildi";
        char status2[15]="Musait";
        int okunanBookId;
        int eskiokunanBookId;
        char okunanBookName[32];
        char okunanWriter[32];
        char okunanPublisher[32];
        int okunanNOB;

        fseek(fPtr, 0, SEEK_SET);
        do
        {
            fscanf(fPtr,"%d%s%s%s%d%d",&okunanBookId,&okunanBookName,&okunanWriter,&okunanPublisher,&okunanNOB,&okunanStatus);

            if(eskiokunanBookId!=okunanBookId)
            {
                eskiokunanBookId = okunanBookId;
                if(strcmp(arananDeger,okunanBookName)==0)
                {
                    if(okunanStatus==1)
                    {
                        printf(" %15s |",status2);
                    }
                    else if(okunanStatus==0)
                    {
                        printf(" %15s |",status1);
                    }
                    printf(" %4d | %32s | %32s | %32s | %4d\n",
                           okunanBookId,
                           okunanBookName,
                           okunanWriter,
                           okunanPublisher,
                           okunanNOB
                           );
                    w+=1;
                    break;
                }
            }
        }while(!feof(fPtr));
    }
    fclose(fPtr);
    if(w==0)
    {
        printf("\n*** Aradiginiz Isimde Kitap Bulunamadi!! ***\n");
    }
    printf("\n 1-) Yeniden Arama Yap \n 2-) Kitap Listesine Goz At \n 3-) Anasayfaya Don \n 4-)Cikis\n\n");
    int x;
    printf("Lutfen Ne Yapmak Istediginizi Secin : ");
    scanf("%d",&x);

    switch(x)
    {
        case 1:
        system("cls");
        bookSearch();
        break;
        case 2:
            system("cls");
            ListBookLbr();
            break;
        case 3:
            system("cls");
            LbrLogin();
            break;
        case 4:
            return 0;
            break;
        default:
            printf("\n*** Gecersiz Bir Deger Girildi, Anasayfaya Yonlendiriliyorsunuz... ***\n\n");
            LbrLogin();
            break;
    }
}

void updateBook()
{
    int arananDeger;
    int y;
    int t= 0;
    printf("\nGuncellemek Istediginiz Kitabin Id Numarasini Giriniz : ");
    scanf("%d",&arananDeger);

    FILE *fPtr;
    if( (fPtr = fopen("book.bin", "rb+")) == NULL)
    {
        printf("dosya olusturulamadi...");
        return -1;
    }
    else
    {
        int okunanStatus;
        char status1[15]="Odunc Verildi";
        char status2[15]="Musait";
        int okunanBookId;
        int eskiokunanBookId=0;
        char okunanBookName[32];
        char okunanWriter[32];
        char okunanPublisher[32];
        int okunanNOB;
        int t=0;

        fseek(fPtr, 0, SEEK_SET);
        do
        {
            fscanf(fPtr,"%d%s%s%s%d%d",&okunanBookId,okunanBookName,okunanWriter,okunanPublisher,&okunanNOB,&okunanStatus);

            if(eskiokunanBookId!=okunanBookId)
            {
                eskiokunanBookId = okunanBookId;
                if(arananDeger==okunanBookId)
                {
                    printf("\n");
                    if(okunanStatus==1)
                    {
                        printf(" %15s |",status2);
                    }
                    else if(okunanStatus==0)
                    {
                        printf(" %15s |",status1);
                    }

                    printf(" %4d | %32s | %32s | %32s | %4d\n",
                           okunanBookId,
                           okunanBookName,
                           okunanWriter,
                           okunanPublisher,
                           okunanNOB
                           );
                    t+=1;
                    break;
                }
            }
        }while(!feof(fPtr));

        if(t==0)
        {
            printf("\n***  Girilen Id Numarasina Ait Kitap Bulunamadi!! ***\n");
            printf("\n 1-) Anasayfaya Don \n 2-) Baska Bir Arama Yap\n\n");
            printf("Lutfen Ne Yapmak Istediginizi Secin : ");
        }

        if(t>0)
        {
            printf("\n 1-) Anasayfaya Don \n 2-) Baska Bir Arama Yap\n");
            printf(" 3-) %d Id Numarali Kitabi Guncelle\n\n",okunanBookId);
            printf("Lutfen Ne Yapmak Istediginizi Secin : ");
        }
        scanf("%d",&y);

        switch(y)
        {
            case 2:
                updateBook();
                break;
            case 1:
                LbrLogin();
                break;
            case 3:
                break;
            default:
                printf("\n*** Gecersiz Bir Deger Girildi , Anasayfaya Yonlendiriliyorsunuz... ***\n");
                LbrLogin();
                break;
        }
        int a;
        int newId;
        char newName[32];
        char newWriter[32];
        char newPublisher[32];
        int newNob;

        printf("\nKitabin Yeni Id Numarasi : ");
        scanf("%d",&newId);
        printf("Kitabin Yeni Adi : ");
        scanf("%s",newName);
        printf("Kitabin Yeni Yazari : ");
        scanf("%s",newWriter);
        printf("Kitabin Yeni Yayinevi : ");
        scanf("%s",newPublisher);
        printf("Kitabin Yeni Kiralanma Sayisi : ");
        scanf("%d",&newNob);


        fseek(fPtr,-3-sizeof(okunanBookId)-sizeof(okunanBookName)-sizeof(okunanWriter)-sizeof(okunanPublisher)-sizeof(okunanNOB),SEEK_CUR);
        fprintf(fPtr,"%4d\t%32s\t%32s\t%32s\t%d\t",newId,newName,newWriter,newPublisher,newNob);

        fclose(fPtr);

        sleep(1);
        printf("\n*** Bilgiler Basarili Bir Sekilde Guncellendi!! ***\n\n");

        printf("*** Anasayfaya Yonlendiriliyorsunuz... ***\n");
        LbrLogin();
    }
}

void addBook()
{
    int newId;
    char newName[32];
    char newWriter[32];
    char newPublisher[32];
    int newNOB =0;
    int newStatus=1;
    int w=0;

    printf("\n*** Kutuphaneye Eklenecek Yeni Kitap Icin Asagidaki Bilgileri Doldurunuz ***\n\n");

    printf("Book Id Numarasi :");
    scanf("%d",&newId);

    FILE *fPtr;
    if( (fPtr = fopen("book.bin", "rb+")) == NULL)
    {
        printf("dosya olusturulamadi...");
        return -1;
    }
    else
    {
        int okunanStatus;
        int okunanBookId;
        char okunanBookName[32];
        char okunanWriter[32];
        char okunanPublisher[32];
        int okunanNOB;

        fseek(fPtr, 0, SEEK_SET);
        do
        {
            fscanf(fPtr,"%d%s%s%s%d%d",&okunanBookId,&okunanBookName,&okunanWriter,&okunanPublisher,&okunanNOB,&okunanStatus);
            if(okunanBookId==newId)
            {
                w+=1;
                break;
            }

        }while(!feof(fPtr));
    }

    int u;
    if(w!=0)
    {
        printf("\n*** Girilen Id Degeri Daha Once Kullanilmis ***\n\n");
        printf(" 1-) Anasayfaya Don\n 2-) Yeni Kitap Ekle\n\n");
        printf("Lutfen Ne Yapmak Istediginizi Secin : ");
        scanf("%d",&u);

        switch(u)
        {
            case 1:
                LbrLogin();
                break;
            case 2:
                system("cls");
                addBook();
        }
    }

    else
    {
        printf("Kitabin Adi :");
        scanf("%s",newName);
        printf("Kitabin Yazari :");
        scanf("%s",newWriter);
        printf("Kitabin Yayinevi :");
        scanf("%s",newPublisher);

        printf("\n %d | %s | %s | %s | %d\n",
                               newId,
                               newName,
                               newWriter,
                               newPublisher,
                               newNOB
                               );

        printf("\n*** Yukarida Belirtilen Kitap Kutuphaneye Ekleniyor... ***\n\n");
        sleep(1);
        fseek(fPtr,0,SEEK_END);
        fprintf(fPtr,"\n%4d\t%32s\t%32s\t%32s\t%d\t%d",
                        newId,
                        newName,
                        newWriter,
                        newPublisher,
                        newNOB,
                        newStatus);
        fclose(fPtr);
        printf("*** Yukleme Basarili!! ***\n\n");
        printf(" 1-) Anasayfaya Don\n 2-) Yeni Kitap Ekle\n 3-) Cikis\n\n");
        printf("Lutfen Ne Yapmak Istediginizi Secin : ");
        scanf("%d",&u);

        switch(u)
        {
            case 1:
                LbrLogin();
                break;
            case 2:
                system("cls");
                addBook();
            case 3:
                return 0;
        }
    }
}

void dellBook()
{
    int okunanStatus;
    char status1[15]="Odunc Verildi";
    char status2[15]="Musait";
    char okunanBookName[32];
    char okunanWriter[32];
    char okunanPublisher[32];
    int okunanNOB;
    int okunanBookId;

    int arananDeger;
    int w=0;
    int u;
    int kontrolstatus = 1;

    printf("\nSilmek Istediginiz Kitabin Id Numarasini Giriniz : ");
    scanf("%d",&arananDeger);
    printf("\n");

    FILE *fPtr;
    if( (fPtr = fopen("book.bin", "rb+")) == NULL)
    {
        printf("dosya olusturulamadi...");
        return -1;
    }
    else
    {
        fseek(fPtr, 0, SEEK_SET);
        do
        {
            fscanf(fPtr,"%d%s%s%s%d%d",&okunanBookId,&okunanBookName,&okunanWriter,&okunanPublisher,&okunanNOB,&okunanStatus);

                if(arananDeger==okunanBookId)
                {
                    printf("*** %d Id Numarali Kitap Bulundu!! ***\n\n",arananDeger);

                    if(okunanStatus==1)
                    {
                        printf(" %15s |",status2);
                    }
                    else if(okunanStatus==0)
                    {
                        printf(" %15s |",status1);
                        kontrolstatus=0;
                    }
                    printf(" %d | %s | %s | %s | %d\n",
                           okunanBookId,
                           okunanBookName,
                           okunanWriter,
                           okunanPublisher,
                           okunanNOB
                           );
                    w+=1;
                    break;
                }

        }while(!feof(fPtr));
    }

    if(w==0)
    {
        printf("\n*** %d Id Numarali Kitap Bulunamadi!! ***\n",arananDeger);

        printf("\n 1-) Listeden Kitap Sil \n 2-) Kitap Listesine Goz At \n 3-) Anasayfaya Don \n 4-)Cikis\n\n");
        int x;
        printf("Lutfen Ne Yapmak Istediginizi Secin : ");
        scanf("%d",&x);

        switch(x)
        {
            case 1:
            system("cls");
            dellBook();
            break;
            case 2:
                system("cls");
                ListBookLbr();
                break;
            case 3:
                system("cls");
                LbrLogin();
                break;
            case 4:
                return 0;
                break;
            default:
                printf("\n*** Gecersiz Bir Deger Girildi, Anasayfaya Yonlendiriliyorsunuz... ***\n\n");
                LbrLogin();
                break;
        }
    }
    else
    {
        if(kontrolstatus==0)
        {
            printf("\n*** %d  Id Numarali Kitap Suan Odunc Verildigi Icin Silinemiyor!! ***\n",arananDeger);

            printf("\n 1-) Listeden Kitap Sil \n 2-) Kitap Listesine Goz At \n 3-) Anasayfaya Don \n 4-)Cikis\n\n");
            int x;
            printf("Lutfen Ne Yapmak Istediginizi Secin : ");
            scanf("%d",&x);

            switch(x)
            {
                case 1:
                system("cls");
                dellBook();
                break;
                case 2:
                    system("cls");
                    ListBookLbr();
                    break;
                case 3:
                    system("cls");
                    LbrLogin();
                    break;
                case 4:
                    return 0;
                    break;
                default:
                    printf("\n*** Gecersiz Bir Deger Girildi, Anasayfaya Yonlendiriliyorsunuz... ***\n\n");
                    LbrLogin();
                    break;
            }
        }
        else
        {
            fseek(fPtr,-3-sizeof(okunanBookId)-sizeof(okunanBookName)-sizeof(okunanWriter)-sizeof(okunanPublisher)-sizeof(okunanNOB),SEEK_CUR);
            char a[32]="-";
            fprintf(fPtr,"0000\t%32s\t%32s\t%32s\t0\t0",a,a,a);
            fclose(fPtr);
            printf("\n*** Silme Islemi Basarili!! ***\n\n");
            printf(" 1-) Anasayfaya Don\n 2-) Kitap Sil\n 3-) Cikis\n\n");
            printf("Lutfen Ne Yapmak Istediginizi Secin : ");
            scanf("%d",&u);

            switch(u)
            {
                case 1:
                    LbrLogin();
                    break;
                case 2:
                    system("cls");
                    dellBook();
                case 3:
                    return 0;
            }
        }
    }
}

