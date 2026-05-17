#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
FILE *dos;
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
        printf("Aramak istediginiz kelimeyi girin\n");
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
            printf("Eslesen bir sonuc bulunamadi\n\n");
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
                    printf("Kitap Adi :%s\nYazar Adi :%s\nKitap No :%s\nStok :%s\n\nYapilacak islemin yanindaki sayiyi girin\n\n1-Kiralama  2-Iade Etme  3-Geri\n",duzenli2[uyusanlar[islem-1]][0],duzenli2[uyusanlar[islem-1]][1],duzenli2[uyusanlar[islem-1]][2],duzenli2[uyusanlar[islem-1]][3]);
                    scanf("%d",&kislem);
                }
                
                
            }
            

        }
    }
    
}
    


int main()
{
    
    arama();
}
