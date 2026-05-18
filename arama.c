#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
FILE *dos;

#define ARAMA_KITAP_DOSYA "veri.txt"
#define ARAMA_KULLANICI_DOSYA "kullanicilar.txt"
#define ARAMA_ODUNC_DOSYA "oduncler.txt"
#define ARAMA_MAX 100

int aramaKullaniciVarMi(char kullaniciAdi[])
{
    FILE *dosya;
    char satir[150];
    int id;
    char ad[30];
    char sifre[30];
    int rol;

    dosya=fopen(ARAMA_KULLANICI_DOSYA,"r");

    if(dosya==NULL)
    return 0;

    while(fgets(satir,sizeof(satir),dosya)!=NULL)
    {
        if(sscanf(satir,"%d-%29[^-]-%29[^-]-%d",&id,ad,sifre,&rol)==4 && strcmp(ad,kullaniciAdi)==0)
        {
            fclose(dosya);
            return 1;
        }
    }

    fclose(dosya);
    return 0;
}

int aramaKitapStokGuncelle(char isbn[], int fark)
{
    FILE *dosya;
    char isimler[ARAMA_MAX][50];
    char yazarlar[ARAMA_MAX][50];
    char isbnler[ARAMA_MAX][50];
    int stoklar[ARAMA_MAX];
    char satir[200];
    int kitapSayisi=0;
    int bulundu=0;

    dosya=fopen(ARAMA_KITAP_DOSYA,"r");

    if(dosya==NULL)
    return 0;

    while(fgets(satir,sizeof(satir),dosya)!=NULL && kitapSayisi<ARAMA_MAX)
    {
        if(sscanf(satir,"%49[^-]-%49[^-]-%49[^-]-%d",isimler[kitapSayisi],yazarlar[kitapSayisi],isbnler[kitapSayisi],&stoklar[kitapSayisi])==4)
        kitapSayisi++;
    }

    fclose(dosya);

    for(int i=0;i<kitapSayisi;i++)
    {
        if(strcmp(isbnler[i],isbn)==0)
        {
            bulundu=1;

            if(fark<0 && stoklar[i]<=0)
            return -1;

            stoklar[i]=stoklar[i]+fark;
        }
    }

    if(!bulundu)
    return 0;

    dosya=fopen(ARAMA_KITAP_DOSYA,"w");

    if(dosya==NULL)
    return 0;

    for(int i=0;i<kitapSayisi;i++)
    {
        fprintf(dosya,"%s-%s-%s-%d\n",isimler[i],yazarlar[i],isbnler[i],stoklar[i]);
    }

    fclose(dosya);
    return 1;
}

int aramaOduncKaydiEkle(char kullaniciAdi[], char isbn[])
{
    FILE *dosya;

    dosya=fopen(ARAMA_ODUNC_DOSYA,"a");

    if(dosya==NULL)
    return 0;

    fprintf(dosya,"%s-%s-%d\n",kullaniciAdi,isbn,0);
    fclose(dosya);
    return 1;
}

int aramaOduncKaydiIadeEt(char kullaniciAdi[], char isbn[])
{
    FILE *dosya;
    char kullanicilar[ARAMA_MAX][30];
    char isbnler[ARAMA_MAX][20];
    int teslimler[ARAMA_MAX];
    int oduncSayisi=0;
    int bulundu=0;

    dosya=fopen(ARAMA_ODUNC_DOSYA,"r");

    if(dosya==NULL)
    return 0;

    while(oduncSayisi<ARAMA_MAX &&
        fscanf(dosya,"%29[^-]-%19[^-]-%d\n",kullanicilar[oduncSayisi],isbnler[oduncSayisi],&teslimler[oduncSayisi])==3)
    {
        oduncSayisi++;
    }

    fclose(dosya);

    for(int i=0;i<oduncSayisi;i++)
    {
        if(strcmp(kullanicilar[i],kullaniciAdi)==0 && strcmp(isbnler[i],isbn)==0 && teslimler[i]==0)
        {
            teslimler[i]=1;
            bulundu=1;
            break;
        }
    }

    if(!bulundu)
    return 0;

    dosya=fopen(ARAMA_ODUNC_DOSYA,"w");

    if(dosya==NULL)
    return 0;

    for(int i=0;i<oduncSayisi;i++)
    {
        fprintf(dosya,"%s-%s-%d\n",kullanicilar[i],isbnler[i],teslimler[i]);
    }

    fclose(dosya);
    return 1;
}

void aramaKitapOduncAl(char isbn[])
{
    char kullaniciAdi[30];
    int sonuc;

    printf("Kullanici adi giriniz: ");
    scanf("%29s",kullaniciAdi);

    if(!aramaKullaniciVarMi(kullaniciAdi))
    {
        printf("Kayit bulunamadi.\n");
        return;
    }

    sonuc=aramaKitapStokGuncelle(isbn,-1);

    if(sonuc==-1)
    {
        printf("Stokta kitap yok.");
        return;
    }

    if(sonuc==0)
    {
        printf("Kitap bulunamadi.\n");
        return;
    }

    if(!aramaOduncKaydiEkle(kullaniciAdi,isbn))
    {
        aramaKitapStokGuncelle(isbn,1);
        printf("Kayit bulunamadi.\n");
        return;
    }

    printf("Kitap odunc verildi.\n");
}

void aramaKitapIadeEt(char isbn[])
{
    char kullaniciAdi[30];

    printf("Kullanici adi giriniz: ");
    scanf("%29s",kullaniciAdi);

    if(!aramaKullaniciVarMi(kullaniciAdi))
    {
        printf("Kayit bulunamadi.\n");
        return;
    }

    if(!aramaOduncKaydiIadeEt(kullaniciAdi,isbn))
    {
        printf("Kayit bulunamadi.\n");
        return;
    }

    aramaKitapStokGuncelle(isbn,1);
    printf("Kitap iade edildi.\n");
}

int arama()
{
    donus3:
    system("cls");
    int a;
    char tekrar[]="Yeni Sorgu";
    char geri[]="Geri";
    int islem=0;
    int kk=1;
    char b[50];
    printf("__________________________________________________________________________________\nLutfen hangi konu hakkinda arama yapilacagini yanindaki numarayi tuslayarak secin|\n_________________________________________________________________________________|\n\n\n1-Kitap Ismi\n2-Yazar Adi\n3-Kitap ID\n\n0-Geri\n");
    scanf("%d",&a);
    while(!(a<4&&a>=0))
    {
        printf("Lutfen dogru sayiyi girin\n");
        scanf("%d",&a);
        return 1;
    }
    if(a==0)
    return 1;

    a--;
    char alinan[50000];
    char duzenli[100][10][50];
    char duzenli2[100][10][50];
    dos=fopen("veri.txt","r");

    if(dos==NULL)
    {
        printf("hata");
        return 1;
    }
    
    for(int i=0;fscanf(dos,"%c",&alinan[i])!=EOF;i++)
    {
    }
    fclose(dos);
    
    int i,x=0,y=0,z=0;
    for(i=0;alinan[i]!='\0';i++)
    {
        if(alinan[i]!='\n'&&alinan[i]!='-')
        {
            
            duzenli2[z][y][x]=alinan[i];

            if(alinan[i]<=90&&alinan[i]>=65)
            duzenli[z][y][x]=alinan[i]+32;

            else
            duzenli[z][y][x]=alinan[i];


            x++;
        }
        else if(alinan[i]=='-')
        {
            duzenli[z][y][x]='\0';
            duzenli2[z][y][x]='\0';
            y++;
            x=0;
        }
        else if(alinan[i]=='\n')
        {
            duzenli[z][y][x]='\0';
            duzenli2[z][y][x]='\0';
            z++;
            y=0;
            x=0;
            
        }
        

    }
    while(kk)
    {
        
        kk=0;
        system("cls");
        donus:
        printf("Aramak istediginiz kitabi giriniz:\n");
        scanf("%s",&b);
        for(int zz=0;b[zz]!='\0';zz++)
        {
            if(b[zz]<=90&&b[zz]>=65)
            b[zz]=b[zz]+32;
        }
        int uyusanlar[50];
        int u=0;
        
        for(int i=0;i<z;i++)
        {
            if (strstr(duzenli[i][a], b) != NULL)
            {
                uyusanlar[u]=i;
                u++;
            }
            
        }
        system("cls");
        if(u==0)
        {
            printf("Eslesen bir sonuc bulunamadi.\n\n");
            goto donus;
        }
        else
        {
            
            int dd=1;
            while(dd>0)
            {
                system("cls");
                if(0)
                {
                    donus2:
                    system("cls");
                    printf("Lutfen dogru girdi giriniz\n");
                }
                
                printf("Eslesen sonuclar\nDetayi sonuc icin yanindaki numarayi tuslayin\nOnceki menu icin 0 i tekrar sorgu yapmak icin %d tuslayin \n\n",u+1);
                for(int p=0;p<u;p++)
                {
                    printf("%d|%40s|%40s|\n",p+1,duzenli2[uyusanlar[p]][0],duzenli2[uyusanlar[p]][1]);
                }
                printf("\n%d|%40s|\n0|%40s|\n",u+1,tekrar,geri);
                
                dd=0;
                int kislem;
                scanf("%d",&islem);
                if(islem==0)
                goto donus3;
                else if(islem==u+1)
                {
                    kk=1;
                }
                else if(islem<0||islem>u+1)
                goto donus2;
                
                else
                {
                    system("cls");
                    printf("Kitap Adi :%s\nYazar Adi :%s\nKitap No :%s\nStok :%s\n\nYapilacak islemin yanindaki sayiyi girin\n\n1-Odunc alma  2-Iade Etme  3-Geri\n",duzenli2[uyusanlar[islem-1]][0],duzenli2[uyusanlar[islem-1]][1],duzenli2[uyusanlar[islem-1]][2],duzenli2[uyusanlar[islem-1]][3]);
                    scanf("%d",&kislem);
                    if(kislem==1)
                    {
                        aramaKitapOduncAl(duzenli2[uyusanlar[islem-1]][2]);
                        goto donus3;
                    }
                    else if(kislem==2)
                    {
                        aramaKitapIadeEt(duzenli2[uyusanlar[islem-1]][2]);
                        goto donus3;
                    }
                    else if(kislem==3)
                    {
                        dd=1;
                    }
                    else
                    {
                        goto donus2;
                    }
                }
                
                
            }
            

        }
    }
    
}
    


int main()
{
    
    arama();
}
