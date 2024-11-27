/*
    SEDANG DIKERJAKAN: siapkanDataMenu();
*/


#include <iostream>
#include <conio.h>
#include <fstream>
#include <sstream>

using namespace std;
const int JUMLAH_SLOT_TOKO = 5;
const int JUMLAH_SLOT_MENU = 5;
int jumlahToko;

struct sMenu
{
    string nama;
    int harga;
};

struct sToko
{
    string nama;
    string id;
    string password;
    bool isAktif = true;
    sMenu menu[JUMLAH_SLOT_MENU];
};

struct sKantin
{
    string nama;
    string password;
    sToko toko[JUMLAH_SLOT_TOKO];
};

void bukaFileError(string namaFile){
    cout << "Terdapat error dalam membuka file: " << namaFile << endl;
    return;
}


//Untuk persiapan awal menjalankan program
void siapkanDataMenu(sMenu menu[], string namaToko){
    /* Catatan kebingungan
        Untuk menyimpan menu agak tricky di bagian penamaan filenya
        Ada 2 pilihan:
            menuToko + i + .csv
            menuToko_namaToko + ".csv"
        Kyknya lebih bagus semisal pakai i, agar file dapat berulang kali dipakai
    */

    for (int i = 0; i < jumlahToko; i++)
    {
        string namaFile = "menuToko_" + namaToko + ".csv";
        ifstream listMenu(namaFile);

        if (!listMenu)
        {
            bukaFileError(namaFile);
            return;
        }
        
    }
    

}

void siapkanDataToko(sToko toko[]){
    string namaFile = "listToko.csv";
    ifstream listToko(namaFile);

    if (!listToko.is_open())
    {
        bukaFileError(namaFile);
        return;
    }

    int i; 
    for (i = 0; i < jumlahToko; i++)
    {
        string namaToko, idToko, passwordToko;

        getline(listToko, namaToko, ',');
        getline(listToko, idToko, ',');
        getline(listToko, passwordToko, '\n');

        toko[i].nama = namaToko;
        toko[i].id = idToko;
        toko[i].password = passwordToko;

        //siapkanDataMenu(toko[i].menu, toko[i].nama);
    }

    while (i < JUMLAH_SLOT_TOKO)
    {
       toko[i].isAktif = false;
       i++;
    }

    listToko.close();
}

void siapkanDataKantin(sKantin &kantin){
    string namaFile = "dataKantin.csv";
    ifstream fileKantin(namaFile);

    if (!fileKantin.is_open())
    {
        bukaFileError(namaFile);
        return;
    }

    string namaKantin, passwordKantin, jumlahTokoKantin;

    getline(fileKantin, namaKantin, ',');
    getline(fileKantin, passwordKantin, ',');
    getline(fileKantin, jumlahTokoKantin, '\n');

    kantin.nama = namaKantin;
    kantin.password = passwordKantin;
    jumlahToko = stoi(jumlahTokoKantin);

    siapkanDataToko(kantin.toko);
}


//Untuk input dari pengguna, sekaligus error handling
int intUserInput(){
    int input;
    while (true)
    {
        cin >> input;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(100, '\n');
        } else {
            cin.ignore(100, '\n');
            break;
        }
        
    }

    return input;
}

string strUserInput(){
    string input;
    while (true)
    {
        getline(cin, input);
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(100,'\n');
        } else {
            break;
        }
    }

    return input;
}


void outputDataToko(sToko toko[]){
    for (int i = 0; i < JUMLAH_SLOT_TOKO; i++)
    {
        if (!toko[i].isAktif)
        {
            cout << "Slot Toko Kosong" << endl;
            continue;
        }
        
        cout << "Nama Toko: " << toko[i].nama << endl;
    }
    
}

void gunakanModeAdmin(sKantin &kantin){
    bool berhenti = false;
    while (!berhenti)
    {
        cout << "\nSelamat Datang di " << kantin.nama << endl;
        cout << "---------------------------------------" << endl;
        cout << "Pilih toko: " << endl;
        getch();
    }
}

int main(){
    sKantin kantin;
    siapkanDataKantin(kantin);

    bool aksesAdmin = false;
    int intInput = -1;
    string strInput = "";

    
    cout << "\nSelamat Datang di " << kantin.nama << endl;
    /*
    cout << "---------------------------------------" << endl;
    cout << "Pilih Mode Akun: " << endl;
    cout << "(1) Mode Admin" << endl;
    cout << "(2) Mode Pembeli" << endl;

    do
    {
        intInput = intUserInput();
        if (intInput == 1)
        {
            aksesAdmin = true;
        } else if (intInput == 2)
        {
            aksesAdmin = false;
        }
    } while (intInput < 1 || intInput > 2);
    */

    outputDataToko(kantin.toko);

    getch();
}