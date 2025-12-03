#include <iostream>
#include <cmath>
#include <string>
using namespace std;

int MAKS_HARI = 100;

// ==========================
string tentukanKategori(float ip) {
    if (ip <= 1) return "Memenuhi Baku Mutu";
    if (ip <= 5) return "Tercemar Ringan";
    if (ip <= 10) return "Tercemar Sedang";
    return "Tercemar Berat";
}

// ==========================
float hitungIP(float pH, float suhu, float TDS, float DO, float kekeruhan) {

    float ip = ((abs(pH - 7) / 7) +
                (abs(suhu - 25) / 25) +
                (TDS / 1000) +
                ((8 - DO) / 8) +
                (kekeruhan / 100)) / 5;

    return ip;
}

// ==========================
string risikoKesehatan(float ip) {
    if (ip <= 1) return "Risiko Rendah";
    if (ip <= 5) return "Risiko Sedang";
    if (ip <= 10) return "Risiko Tinggi";
    return "Risiko Sangat Tinggi";
}

// ==========================
float prediksiBesok(float ip[], int jumlah) {
    if (jumlah < 2) return ip[jumlah - 1];

    float selisih = ip[jumlah - 1] - ip[jumlah - 2];
    return ip[jumlah - 1] + (selisih * 0.5);
}

// ==========================
int main() {

    float pH[100];
    float suhu[100];
    float TDS[100];
    float DO[100];
    float kekeruhan[100];
    float indeksPencemar[100];
    string kategori[100];

    int jumlahData = 0;
    int pilihan;

    do {
        cout << "============================================\n";
        cout << "   PROGRAM PEMANTAUAN KUALITAS AIR SUNGAI\n";
        cout << "============================================\n";
        cout << "1. Input Data Harian\n";
        cout << "2. Lihat Histori Data\n";
        cout << "3. Analisis Perubahan\n";
        cout << "4. Prediksi Besok\n";
        cout << "5. Keluar\n";
        cout << "============================================\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {

        case 1: {
            if (jumlahData >= 100) {
                cout << "Data sudah penuh.\n";
                break;
            }

            cout << "\n=== Input Data Hari Ini ===\n";
            cout << "Masukkan pH              : "; cin >> pH[jumlahData];
            cout << "Masukkan Suhu (C)        : "; cin >> suhu[jumlahData];
            cout << "Masukkan TDS (mg/L)      : "; cin >> TDS[jumlahData];
            cout << "Masukkan DO (mg/L)       : "; cin >> DO[jumlahData];
            cout << "Masukkan Kekeruhan (NTU) : "; cin >> kekeruhan[jumlahData];

            indeksPencemar[jumlahData] = hitungIP(
                pH[jumlahData], suhu[jumlahData], TDS[jumlahData],
                DO[jumlahData], kekeruhan[jumlahData]
            );

            kategori[jumlahData] = tentukanKategori(indeksPencemar[jumlahData]);

            cout << "\nIP Hari Ini : " << indeksPencemar[jumlahData] << endl;
            cout << "Kategori    : " << kategori[jumlahData] << endl;
            cout << "Risiko      : " << risikoKesehatan(indeksPencemar[jumlahData]) << endl;

            jumlahData++;
            break;
        }

        case 2: {
            cout << "\n========= HISTORI DATA =========\n";

            if (jumlahData == 0) {
                cout << "Belum ada data.\n";
            } else {
                for (int i = 0; i < jumlahData; i++) {
                    cout << "\nHari ke-" << i + 1 << endl;
                    cout << "pH          : " << pH[i] << endl;
                    cout << "Suhu        : " << suhu[i] << endl;
                    cout << "TDS         : " << TDS[i] << endl;
                    cout << "DO          : " << DO[i] << endl;
                    cout << "Kekeruhan   : " << kekeruhan[i] << endl;
                    cout << "IP          : " << indeksPencemar[i] << endl;
                    cout << "Kategori    : " << kategori[i] << endl;
                }
            }
            break;
        }

        case 3: {
            cout << "\n====== ANALISIS PERUBAHAN ======\n";

            if (jumlahData < 2) {
                cout << "Data kurang untuk analisis tren.\n";
            } else {
                float perubahan =
                    indeksPencemar[jumlahData - 1] - indeksPencemar[0];

                cout << "Perubahan IP dari hari 1 ke hari terakhir: "
                     << perubahan << " ("
                     << (perubahan > 0 ? "Memburuk" : "Membaik")
                     << ")\n";
            }
            break;
        }

        case 4: {
            cout << "\n====== PREDIKSI BESOK ======\n";

            if (jumlahData == 0) {
                cout << "Belum ada data.\n";
            } else {
                float pred = prediksiBesok(indeksPencemar, jumlahData);

                cout << "Prediksi IP Besok : " << pred << endl;
                cout << "Kategori          : " << tentukanKategori(pred) << endl;
            }

            break;
        }

        case 5:
            cout << "Program selesai.\n";
            break;

        default:
            cout << "Pilihan tidak valid.\n";
        }

    } while (pilihan != 5);


}

