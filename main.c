#include <stdio.h>
#include <time.h>
#include <string.h>

// Tarih ve saat bilgilerini saklamak için struct ve union tanımı
struct TarihSaat {
    int yil;
    int ay;
    int gun;
    int saat;
    int dakika;
    int saniye;
};

union TarihSaatBirlik {
    struct TarihSaat ts;
    time_t epoch_zamani;
};

// Tarih ve saat bilgisini epoch zamanına dönüştüren fonksiyon
time_t epochZamaninaCevir(struct TarihSaat ts) {
    struct tm zamanBilgisi;
    memset(&zamanBilgisi, 0, sizeof(zamanBilgisi));
    zamanBilgisi.tm_year = ts.yil - 1900; // Yıl farkı
    zamanBilgisi.tm_mon = ts.ay - 1; // Ay farkı
    zamanBilgisi.tm_mday = ts.gun;
    zamanBilgisi.tm_hour = ts.saat;
    zamanBilgisi.tm_min = ts.dakika;
    zamanBilgisi.tm_sec = ts.saniye;
    return mktime(&zamanBilgisi);
}

int main() {
    union TarihSaatBirlik ts1, ts2;

    // Kullanıcıdan ilk tarih ve saati alma
    printf("İlk tarih ve saati girin (YYYY MM DD HH MM SS): ");
    scanf("%d %d %d %d %d %d", &ts1.ts.yil, &ts1.ts.ay, &ts1.ts.gun, &ts1.ts.saat, &ts1.ts.dakika, &ts1.ts.saniye);

    // Kullanıcıdan ikinci tarih ve saati alma
    printf("İkinci tarih ve saati girin (YYYY MM DD HH MM SS): ");
    scanf("%d %d %d %d %d %d", &ts2.ts.yil, &ts2.ts.ay, &ts2.ts.gun, &ts2.ts.saat, &ts2.ts.dakika, &ts2.ts.saniye);

    // Tarih ve saat bilgilerini epoch zamanına dönüştürme
    ts1.epoch_zamani = epochZamaninaCevir(ts1.ts);
    ts2.epoch_zamani = epochZamaninaCevir(ts2.ts);

    // Zaman farkını hesaplama
    double fark = difftime(ts2.epoch_zamani, ts1.epoch_zamani);

    // Sonuçları ekrana yazdırma
    printf("İlk tarih ve saat (epoch): %ld\n", ts1.epoch_zamani);
    printf("İkinci tarih ve saat (epoch): %ld\n", ts2.epoch_zamani);
    printf("İki tarih arasındaki zaman farkı (saniye): %.f\n", fark);

    return 0;
}