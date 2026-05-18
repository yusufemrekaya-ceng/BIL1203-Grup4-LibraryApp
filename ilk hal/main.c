#include <stdio.h>

#define main paket1_3_main
#include "paket1_3.c"
#undef main

#define main arama_main
#include "arama.c"
#undef main

#define Kitap Kitap_App2
#define kitaplar kitaplar_app2
#define kitapSayisi kitapSayisi_app2
#define kitapListele kitapListele_app2
#define main library_app2_main
#include "library app 2"
#undef main
#undef kitapListele
#undef kitapSayisi
#undef kitaplar
#undef Kitap
#undef MAX

#define Kitap Kitap_App4
#define Odunc Odunc_App4
#define kitaplar kitaplar_app4
#define oduncler oduncler_app4
#define kitapSayisi kitapSayisi_app4
#define oduncSayisi oduncSayisi_app4
#define main library_app4_main
#include "library app 4"
#undef main
#undef oduncSayisi
#undef kitapSayisi
#undef oduncler
#undef kitaplar
#undef Odunc
#undef Kitap
#undef MAX

void profilYonetimi(int aktifIndex) {
    int secim;

    do {
        printf("\n--- Profil Yonetimi ---\n");
        printf("1- Kendi sifremi degistir\n");
        printf("2- Kendi kullanici adimi degistir\n");
        printf("0- Geri\n");
        printf("Secim: ");
        scanf("%d", &secim);

        if (secim == 1) {
            kendiSifresiniDegistir(aktifIndex);
        } else if (secim == 2) {
            kendiAdiniDegistir(aktifIndex);
        } else if (secim == 0) {
            printf("Geri donuluyor.\n");
        } else {
            printf("Hatali secim!\n");
        }
    } while (secim != 0);
}

void adminKullaniciYonetimi() {
    int secim;

    do {
        printf("\n--- Admin Kullanici Yonetimi ---\n");
        printf("1- Personel ekle\n");
        printf("2- Kullanici ekle\n");
        printf("3- Personel sil\n");
        printf("4- Kullanici sil\n");
        printf("5- Kullanicilari listele\n");
        printf("0- Geri\n");
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
        } else if (secim == 0) {
            printf("Geri donuluyor.\n");
        } else {
            printf("Hatali secim!\n");
        }
    } while (secim != 0);
}

void personelKullaniciYonetimi() {
    int secim;

    do {
        printf("\n--- Personel Kullanici Yonetimi ---\n");
        printf("1- Kullanici ekle\n");
        printf("2- Kullanici sil\n");
        printf("3- Kullanicilari listele\n");
        printf("0- Geri\n");
        printf("Secim: ");
        scanf("%d", &secim);

        if (secim == 1) {
            kullaniciEkle(3);
        } else if (secim == 2) {
            kullaniciSil(3, 3);
        } else if (secim == 3) {
            kullaniciListele();
        } else if (secim == 0) {
            printf("Geri donuluyor.\n");
        } else {
            printf("Hatali secim!\n");
        }
    } while (secim != 0);
}

void adminAnaMenu(int aktifIndex) {
    int secim;

    do {
        printf("\n--- Admin Ana Menusu ---\n");
        printf("1- Personel ve kullanici yonetimi\n");
        printf("2- Profil yonetimi\n");
        printf("3- Kitap arama\n");
        printf("4- Kitap odunc ve iade\n");
        printf("5- Kitap islemleri\n");
        printf("0- Cikis\n");
        printf("Secim: ");
        scanf("%d", &secim);

        if (secim == 1) {
            adminKullaniciYonetimi();
        } else if (secim == 2) {
            profilYonetimi(aktifIndex);
        } else if (secim == 3) {
            arama();
        } else if (secim == 4) {
            library_app4_main();
        } else if (secim == 5) {
            library_app2_main();
        } else if (secim == 0) {
            printf("Cikis yapiliyor.\n");
        } else {
            printf("Hatali secim!\n");
        }
    } while (secim != 0);
}

void personelAnaMenu(int aktifIndex) {
    int secim;

    do {
        printf("\n--- Personel Ana Menusu ---\n");
        printf("1- Kullanici yonetimi\n");
        printf("2- Profil yonetimi\n");
        printf("3- Kitap arama\n");
        printf("4- Kitap odunc ve iade\n");
        printf("5- Kitap islemleri\n");
        printf("0- Cikis\n");
        printf("Secim: ");
        scanf("%d", &secim);

        if (secim == 1) {
            personelKullaniciYonetimi();
        } else if (secim == 2) {
            profilYonetimi(aktifIndex);
        } else if (secim == 3) {
            arama();
        } else if (secim == 4) {
            library_app4_main();
        } else if (secim == 5) {
            library_app2_main();
        } else if (secim == 0) {
            printf("Cikis yapiliyor.\n");
        } else {
            printf("Hatali secim!\n");
        }
    } while (secim != 0);
}

void kullaniciAnaMenu(int aktifIndex) {
    int secim;

    do {
        printf("\n--- Kullanici Ana Menusu ---\n");
        printf("1- Profil yonetimi\n");
        printf("2- Kitap arama\n");
        printf("3- Kitap odunc ve iade\n");
        printf("0- Cikis\n");
        printf("Secim: ");
        scanf("%d", &secim);

        if (secim == 1) {
            profilYonetimi(aktifIndex);
        } else if (secim == 2) {
            arama();
        } else if (secim == 3) {
            library_app4_main();
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
        adminAnaMenu(aktifIndex);
    } else if (girisTuru == 2) {
        personelAnaMenu(aktifIndex);
    } else if (girisTuru == 3) {
        kullaniciAnaMenu(aktifIndex);
    }

    return 0;
}
