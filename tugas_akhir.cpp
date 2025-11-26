#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
using namespace std;

struct DataAir {
    float pH, suhu, TDS, DO, kekeruhan;
    float indeksPencemar;
    string kategori;
};

string tentukanKategori(float ip) {
    if (ip <= 1) return "Memenuhi Baku Mutu";
    if (ip <= 5) return "Tercemar Ringan";
    if (ip <= 10) return "Tercemar Sedang";
    return "Tercemar Berat";
}

float hitungIP(float pH, float suhu, float TDS, float DO, float kekeruhan) {
    float ip = ((abs(pH - 7) / 7) +
                (abs(suhu - 25) / 25) +
                (TDS / 1000) +
                ((8 - DO) / 8) +
                (kekeruhan / 100)) / 5;
    return ip;
}


string risikoKesehatan(float ip) {
    if (ip <= 1) return "Risiko Rendah";
    if (ip <= 5) return "Risiko Sedang";
    if (ip <= 10) return "Risiko Tinggi";
    return "Risiko Sangat Tinggi";
}


float prediksiBesok(const vector<DataAir>& data) {
    if (data.size() < 2) return data.back().indeksPencemar;
    float diff = data.back().indeksPencemar - data[data.size()-2].indeksPencemar;
    return data.back().indeksPencemar + diff * 0.5;  // pergerakan setengah tren
}

int main() {
    vector<DataAir> histori;
    int pilihan;

    do {
        system("cls"); // jika error, ganti "clear" untuk Linux/Mac
        cout << "============================================\n";
        cout << "   PROGRAM PEMANTAUAN KUALITAS AIR SUNGAI\n";
        cout << "============================================\n";
        cout << "1. Input Data Harian\n";
        cout << "2. Lihat Histori Data\n";
        cout << "3. Analisis Tren\n";
        cout << "4. Prediksi Besok\n";
        cout << "5. Keluar\n";
        cout << "============================================\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
        case 1: {
            DataAir d;
            cout << "\n=== Input Data Hari Ini ===\n";
            cout << "Masukkan pH                 : "; cin >> d.pH;
            cout << "Masukkan Suhu (C)           : "; cin >> d.suhu;
            cout << "Masukkan TDS (mg/L)         : "; cin >> d.TDS;
            cout << "Masukkan DO (mg/L)          : "; cin >> d.DO;
            cout << "Masukkan Kekeruhan (NTU)    : "; cin >> d.kekeruhan;

            d.indeksPencemar = hitungIP(d.pH, d.suhu, d.TDS, d.DO, d.kekeruhan);
            d.kategori = tentukanKategori(d.indeksPencemar);

            histori.push_back(d);

            cout << "\n=== Hasil Perhitungan Hari Ini ===\n";
            cout << "Indeks Pencemar (IP) : " << d.indeksPencemar << endl;
            cout << "Kategori Mutu         : " << d.kategori << endl;
            cout << "Risiko Kesehatan      : " << risikoKesehatan(d.indeksPencemar) << endl;

            system("pause");
            break;
        }

        case 2: {
            cout << "\n========= HISTORI DATA =========\n";
            if (histori.empty()) {
                cout << "Belum ada data.\n";
            } else {
                for (int i=0; i<histori.size(); i++) {
                    cout << "\nHari ke-" << i+1 << endl;
                    cout << "pH          : " << histori[i].pH << endl;
                    cout << "Suhu        : " << histori[i].suhu << endl;
                    cout << "TDS         : " << histori[i].TDS << endl;
                    cout << "DO          : " << histori[i].DO << endl;
                    cout << "Kekeruhan   : " << histori[i].kekeruhan << endl;
                    cout << "IP          : " << histori[i].indeksPencemar << endl;
                    cout << "Kategori    : " << histori[i].kategori << endl;
                }
            }
            system("pause");
            break;
        }

        case 3: {
            cout << "\n====== ANALISIS TREN ======\n";
            if (histori.size() < 2) {
                cout << "Data kurang untuk analisis tren.\n";
            } else {
                float perubahan = histori.back().indeksPencemar - histori.front().indeksPencemar;
                cout << "Perubahan IP dari hari 1 ke hari terakhir: " 
                     << perubahan << " ("
                     << (perubahan > 0 ? "Memburuk" : "Membaik") << ")\n";
            }
            system("pause");
            break;
        }

        case 4: {
            cout << "\n====== PREDIKSI BESOK ======\n";
            if (histori.empty()) {
                cout << "Belum ada data.\n";
            } else {
                float pred = prediksiBesok(histori);
                cout << "Prediksi IP Besok : " << pred << endl;
                cout << "Kategori          : " << tentukanKategori(pred) << endl;
            }
            system("pause");
            break;
        }

        case 5:
            cout << "Program selesai.\n";
            break;

        default:
            cout << "Pilihan tidak valid.\n";
            system("pause");
        }

    } while (pilihan != 5);

    return 0;
}
