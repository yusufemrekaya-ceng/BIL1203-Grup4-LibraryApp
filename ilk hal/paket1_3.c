#include <stdio.h>
#include <string.h>

#define MAX_KULLANICI 100
#define MAX_KITAP 200
#define KULLANICI_DOSYA "kullanicilar.txt"
#define KITAP_DOSYA "veri.txt"

/*
    Is paketleri:
    1) Kullanici girisi ve yetkilendirme
    3) Kullanici hesabi yonetimi

    Kullanici dosya formati:
    id-kullaniciAdi-sifre-rol

    Roller:
    1 = admin
    2 = personel
    3 = kullanici

    Admin hesabi programdan olusturulmaz.
    Adminler sadece kullanicilar.txt dosyasina developerlar tarafindan eklenir.

    Ornek admin satiri:
    1-admin-1234-1
*/

struct Kullanici {
    int id;
    char ad[30];
    char sifre[30];
    int rol;
};

struct Kitap {
    char isim[60];
    char yazar[60];
    char isbn[20];
    int stok;
};

struct Kullanici kullanicilar[MAX_KULLANICI];
struct Kitap kitaplar[MAX_KITAP];

int kullaniciSayisi = 0;
int kitapSayisi = 0;

void satirSonuSil(char metin[]) {
    int uzunluk = strlen(metin);

    if (uzunluk > 0 && metin[uzunluk - 1] == '\n') {
        metin[uzunluk - 1] = '\0';
    }
}

void rolYazdir(int rol) {
    if (rol == 1) {
        printf("Admin");
    } else if (rol == 2) {
        printf("Personel");
    } else if (rol == 3) {
        printf("Kullanici");
    } else {
        printf("Bilinmeyen");
    }
}

void kullanicilariOku() {
    FILE *dosya;
    char satir[150];

    kullaniciSayisi = 0;
    dosya = fopen(KULLANICI_DOSYA, "r");

    if (dosya == NULL) {
        return;
    }

    while (fgets(satir, sizeof(satir), dosya) != NULL && kullaniciSayisi < MAX_KULLANICI) {
        satirSonuSil(satir);

        if (sscanf(satir, "%d-%29[^-]-%29[^-]-%d",
                   &kullanicilar[kullaniciSayisi].id,
                   kullanicilar[kullaniciSayisi].ad,
                   kullanicilar[kullaniciSayisi].sifre,
                   &kullanicilar[kullaniciSayisi].rol) == 4) {
            kullaniciSayisi++;
        }
    }

    fclose(dosya);
}

void kullanicilariYaz() {
    FILE *dosya;
    int i;

    dosya = fopen(KULLANICI_DOSYA, "w");

    if (dosya == NULL) {
        printf("Kullanici dosyasi yazilamadi!\n");
        return;
    }

    for (i = 0; i < kullaniciSayisi; i++) {
        fprintf(dosya, "%d-%s-%s-%d\n",
                kullanicilar[i].id,
                kullanicilar[i].ad,
                kullanicilar[i].sifre,
                kullanicilar[i].rol);
    }

    fclose(dosya);
}

void kitaplariOku() {
    FILE *dosya;
    char satir[250];

    kitapSayisi = 0;
    dosya = fopen(KITAP_DOSYA, "r");

    if (dosya == NULL) {
        return;
    }

    while (fgets(satir, sizeof(satir), dosya) != NULL && kitapSayisi < MAX_KITAP) {
        satirSonuSil(satir);

        if (sscanf(satir, "%59[^-]-%59[^-]-%19[^-]-%d",
                   kitaplar[kitapSayisi].isim,
                   kitaplar[kitapSayisi].yazar,
                   kitaplar[kitapSayisi].isbn,
                   &kitaplar[kitapSayisi].stok) == 4) {
            kitapSayisi++;
        }
    }

    fclose(dosya);
}

int kullaniciAdiVarMi(char ad[]) {
    int i;

    for (i = 0; i < kullaniciSayisi; i++) {
        if (strcmp(kullanicilar[i].ad, ad) == 0) {
            return 1;
        }
    }

    return 0;
}

int kullaniciIndexBul(int id) {
    int i;

    for (i = 0; i < kullaniciSayisi; i++) {
        if (kullanicilar[i].id == id) {
            return i;
        }
    }

    return -1;
}

int yeniIdBul() {
    int i;
    int enBuyuk = 0;

    for (i = 0; i < kullaniciSayisi; i++) {
        if (kullanicilar[i].id > enBuyuk) {
            enBuyuk = kullanicilar[i].id;
        }
    }

    return enBuyuk + 1;
}

int girisYap(int secilenRol) {
    char ad[30];
    char sifre[30];
    int i;

    kullanicilariOku();

    printf("Kullanici adi: ");
    scanf("%29s", ad);

    printf("Sifre: ");
    scanf("%29s", sifre);

    for (i = 0; i < kullaniciSayisi; i++) {
        if (strcmp(kullanicilar[i].ad, ad) == 0 &&
            strcmp(kullanicilar[i].sifre, sifre) == 0 &&
            kullanicilar[i].rol == secilenRol) {
            return i;
        }
    }

    printf("Giris bilgileri veya secilen giris turu hatali!\n");
    return -1;
}

int sifreKontrolEt(int aktifIndex) {
    char girilenSifre[30];

    while (1) {
        printf("Guncel sifrenizi giriniz (iptal icin 0): ");
        scanf("%29s", girilenSifre);

        if (strcmp(girilenSifre, "0") == 0) {
            return 0;
        }

        if (strcmp(kullanicilar[aktifIndex].sifre, girilenSifre) == 0) {
            return 1;
        }

        printf("Sifre hatali! Tekrar deneyiniz.\n");
    }
}

void kendiSifresiniDegistir(int aktifIndex) {
    char yeniSifre[30];

    kullanicilariOku();

    if (!sifreKontrolEt(aktifIndex)) {
        printf("Sifre degistirme iptal edildi.\n");
        return;
    }

    printf("Yeni sifre: ");
    scanf("%29s", yeniSifre);

    strcpy(kullanicilar[aktifIndex].sifre, yeniSifre);
    kullanicilariYaz();

    printf("Sifre degistirildi.\n");
}

void kendiAdiniDegistir(int aktifIndex) {
    char yeniAd[30];

    kullanicilariOku();

    if (!sifreKontrolEt(aktifIndex)) {
        printf("Kullanici adi degistirme iptal edildi.\n");
        return;
    }

    while (1) {
        printf("Yeni kullanici adi: ");
        scanf("%29s", yeniAd);

        if (strcmp(kullanicilar[aktifIndex].ad, yeniAd) == 0) {
            printf("Bu zaten sizin kullanici adiniz.\n");
            return;
        }

        if (kullaniciAdiVarMi(yeniAd)) {
            printf("Bu isimde kullanici var! Baska isim giriniz.\n");
        } else {
            strcpy(kullanicilar[aktifIndex].ad, yeniAd);
            kullanicilariYaz();
            printf("Kullanici adi degistirildi.\n");
            return;
        }
    }
}

void kullaniciListele() {
    int i;

    kullanicilariOku();

    printf("\n--- Kullanicilar ---\n");

    if (kullaniciSayisi == 0) {
        printf("Kayitli kullanici yok.\n");
        return;
    }

    for (i = 0; i < kullaniciSayisi; i++) {
        printf("ID: %d | Ad: %s | Rol: ", kullanicilar[i].id, kullanicilar[i].ad);
        rolYazdir(kullanicilar[i].rol);
        printf("\n");
    }
}

void kullaniciEkle(int eklenecekRol) {
    struct Kullanici yeni;

    kullanicilariOku();

    if (kullaniciSayisi >= MAX_KULLANICI) {
        printf("Kullanici kapasitesi dolu!\n");
        return;
    }

    yeni.id = yeniIdBul();
    yeni.rol = eklenecekRol;

    while (1) {
        printf("Yeni kullanici adi: ");
        scanf("%29s", yeni.ad);

        if (kullaniciAdiVarMi(yeni.ad)) {
            printf("Bu isimde kullanici var! Tekrar isim giriniz.\n");
        } else {
            break;
        }
    }

    printf("Sifre: ");
    scanf("%29s", yeni.sifre);

    kullanicilar[kullaniciSayisi] = yeni;
    kullaniciSayisi++;

    kullanicilariYaz();

    printf("Kullanici eklendi. Rol: ");
    rolYazdir(eklenecekRol);
    printf("\n");
}

void kullaniciSil(int silinebilecekRol1, int silinebilecekRol2) {
    int id;
    int index;
    int i;

    kullanicilariOku();
    kullaniciListele();

    printf("Silinecek kullanici ID: ");
    scanf("%d", &id);

    index = kullaniciIndexBul(id);

    if (index == -1) {
        printf("Kullanici bulunamadi.\n");
        return;
    }

    if (kullanicilar[index].rol != silinebilecekRol1 &&
        kullanicilar[index].rol != silinebilecekRol2) {
        printf("Bu roldeki kullaniciyi silme yetkiniz yok.\n");
        return;
    }

    for (i = index; i < kullaniciSayisi - 1; i++) {
        kullanicilar[i] = kullanicilar[i + 1];
    }

    kullaniciSayisi--;
    kullanicilariYaz();

    printf("Kullanici silindi.\n");
}

void kitapListele() {
    int i;

    kitaplariOku();

    printf("\n--- Kitap Listesi ---\n");

    if (kitapSayisi == 0) {
        printf("Kitap dosyasi bulunamadi veya kitap yok.\n");
        return;
    }

    for (i = 0; i < kitapSayisi; i++) {
        printf("%d) %s | %s | ISBN: %s | Stok: %d\n",
               i + 1,
               kitaplar[i].isim,
               kitaplar[i].yazar,
               kitaplar[i].isbn,
               kitaplar[i].stok);
    }
}

void kitapSorgula() {
    char aranan[60];
    int i;
    int bulundu = 0;

    kitaplariOku();

    if (kitapSayisi == 0) {
        printf("Kitap dosyasi bulunamadi veya kitap yok.\n");
        return;
    }

    printf("Kitap adi, yazar veya ISBN giriniz: ");
    scanf(" %59[^\n]", aranan);

    printf("\n--- Arama Sonuclari ---\n");

    for (i = 0; i < kitapSayisi; i++) {
        if (strstr(kitaplar[i].isim, aranan) != NULL ||
            strstr(kitaplar[i].yazar, aranan) != NULL ||
            strstr(kitaplar[i].isbn, aranan) != NULL) {
            printf("%s | %s | ISBN: %s | Stok: %d\n",
                   kitaplar[i].isim,
                   kitaplar[i].yazar,
                   kitaplar[i].isbn,
                   kitaplar[i].stok);
            bulundu = 1;
        }
    }

    if (!bulundu) {
        printf("Sonuc bulunamadi.\n");
    }
}

void adminMenu(int aktifIndex) {
    int secim;
    int altSecim;

    do {
        printf("\n--- Admin Menusu ---\n");
        printf("1- Personel ekle\n");
        printf("2- Kullanici ekle\n");
        printf("3- Personel sil\n");
        printf("4- Kullanici sil\n");
        printf("5- Kullanicilari listele\n");
        printf("6- Kendi sifremi degistir\n");
        printf("7- Kendi kullanici adimi degistir\n");
        printf("8- Kitap listele\n");
        printf("9- Kitap sorgula\n");
        printf("0- Cikis\n");
        printf("Secim: ");
        scanf("%d", &secim);

        if (secim == 1) {
            kullaniciEkle(2);
        } else if (secim == 2) {
            kullaniciEkle(3);
        } else if (secim == 3) {
            kullaniciSil(2, 2);
        } else if (secim == 4) {
            kullaniciSil(3, 3);
        } else if (secim == 5) {
            kullaniciListele();
        } else if (secim == 6) {
            kendiSifresiniDegistir(aktifIndex);
        } else if (secim == 7) {
            kendiAdiniDegistir(aktifIndex);
        } else if (secim == 8) {
            kitapListele();
        } else if (secim == 9) {
            kitapSorgula();
        } else if (secim == 0) {
            printf("Cikis yapiliyor.\n");
        } else {
            printf("Hatali secim!\n");
        }

        altSecim = 0;
    } while (secim != 0 && altSecim == 0);
}

void personelMenu(int aktifIndex) {
    int secim;

    do {
        printf("\n--- Personel Menusu ---\n");
        printf("1- Kullanici ekle\n");
        printf("2- Kullanici sil\n");
        printf("3- Kullanicilari listele\n");
        printf("4- Kendi sifremi degistir\n");
        printf("5- Kendi kullanici adimi degistir\n");
        printf("6- Kitap listele\n");
        printf("7- Kitap sorgula\n");
        printf("0- Cikis\n");
        printf("Secim: ");
        scanf("%d", &secim);

        if (secim == 1) {
            kullaniciEkle(3);
        } else if (secim == 2) {
            kullaniciSil(3, 3);
        } else if (secim == 3) {
            kullaniciListele();
        } else if (secim == 4) {
            kendiSifresiniDegistir(aktifIndex);
        } else if (secim == 5) {
            kendiAdiniDegistir(aktifIndex);
        } else if (secim == 6) {
            kitapListele();
        } else if (secim == 7) {
            kitapSorgula();
        } else if (secim == 0) {
            printf("Cikis yapiliyor.\n");
        } else {
            printf("Hatali secim!\n");
        }
    } while (secim != 0);
}

void kullaniciMenu(int aktifIndex) {
    int secim;

    do {
        printf("\n--- Kullanici Menusu ---\n");
        printf("1- Kitap listele\n");
        printf("2- Kitap sorgula\n");
        printf("3- Kendi sifremi degistir\n");
        printf("4- Kendi kullanici adimi degistir\n");
        printf("0- Cikis\n");
        printf("Secim: ");
        scanf("%d", &secim);

        if (secim == 1) {
            kitapListele();
        } else if (secim == 2) {
            kitapSorgula();
        } else if (secim == 3) {
            kendiSifresiniDegistir(aktifIndex);
        } else if (secim == 4) {
            kendiAdiniDegistir(aktifIndex);
        } else if (secim == 0) {
            printf("Cikis yapiliyor.\n");
        } else {
            printf("Hatali secim!\n");
        }
    } while (secim != 0);
}

int main() {
    int girisTuru;
    int aktifIndex;

    printf("Kutuphaneye Hos Geldiniz\n");
    printf("Giris turu seciniz:\n");
    printf("1- Admin girisi\n");
    printf("2- Personel girisi\n");
    printf("3- Kullanici girisi\n");
    printf("Secim: ");
    scanf("%d", &girisTuru);

    if (girisTuru < 1 || girisTuru > 3) {
        printf("Hatali giris turu!\n");
        return 0;
    }

    aktifIndex = girisYap(girisTuru);

    if (aktifIndex == -1) {
        return 0;
    }

    printf("Giris basarili. Rol: ");
    rolYazdir(kullanicilar[aktifIndex].rol);
    printf("\n");

    if (girisTuru == 1) {
        adminMenu(aktifIndex);
    } else if (girisTuru == 2) {
        personelMenu(aktifIndex);
    } else if (girisTuru == 3) {
        kullaniciMenu(aktifIndex);
    }

    return 0;
}
