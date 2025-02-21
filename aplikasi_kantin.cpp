#include <iostream>
#include <conio.h>
#include <fstream>
#include <vector>

using namespace std;
const string NAMA_FILE = "dataMenu.csv";
const int MAX_HARGA = 1000000;
const int MAX_PANJANG_STRING = 25;

const string NAMA_KANTIN = "Kantin Daspro";
const string ID_KANTIN = "idkantin";
const string PASSWORD_KANTIN = "passkantin";

struct sMenu
{
    string nama;
    int harga;
};

struct sKantin
{
    string nama;
    string id;
    string password;
    vector<sMenu> menu;
};


//----------------------  PERSIAPAN PROGRAM-------------------------------

//Baca File menu masukkan ke vector
void bacaFileMenu(vector<sMenu> &menu){
    ifstream fileMenu(NAMA_FILE);

    if (!fileMenu.is_open())
    {
        cout << "Terdapat error dalam membuka file: " << NAMA_FILE << endl;
        return;
    }

    string namaMenu, hargaMenu;
    while (true)
    {
        getline(fileMenu, namaMenu, ',');
        if (namaMenu == "END"){
            break;
        }

        getline(fileMenu, hargaMenu, '\n');

        //stoi() String to integer
        menu.push_back({namaMenu, stoi(hargaMenu)});
    }
    
    fileMenu.close();
}

//Menyiapkan data kantin
void mulaiProgram(sKantin &kantin){
    kantin.nama = NAMA_KANTIN;
    kantin.id = ID_KANTIN;
    kantin.password = PASSWORD_KANTIN;

    bacaFileMenu(kantin.menu);
}



//----------------------  FUNGSI SAVE PROGRAM-------------------------------

//Untuk save perubahan menu
void saveDataMenu(vector<sMenu> &menu){
    cout << "Menyimpan perubahan...." << endl;

    ofstream fileMenu(NAMA_FILE);

    if (!fileMenu.is_open())
    {
        cout << "Terdapat error dalam membuka file: " << NAMA_FILE << endl;
        return;
    }

    int banyakMenu = menu.size();
    for (int i = 0; i < banyakMenu; i++)
    {
        fileMenu << menu[i].nama << "," << menu[i].harga << "\n";
    }

    fileMenu << "END";

    fileMenu.close();
}
//---------------------------------------------------------------------------


//---------------------- FUNGSI INPUT PROGRAM-------------------------------

//Untuk input bertipe int dari pengguna, sekaligus error handling
int intUserInput(int nilaiMaksimal){
    string inputStr;
    int inputInt;
    bool sudahBenar = false;
  
    /* Kondisi input yang tidak diterima:
        - Apabila terdapat spasi
        - Apabila terdapat karakter bukan angka
        - Apabila input lebih kecil dari 1
        - Apabila input lebih besar dari nilai maksimal (parameter)
    
    */

    while (!sudahBenar)
    {
        getline(cin, inputStr, '\n');
        int panjangInput = inputStr.length();

        if (panjangInput == 0)
        {
            cout << "Anda tidak memberikan input!" << endl;
            cout << "Ulangi Input: ";
            continue;
        }
        

        // Cek apakah input yang diberikan merupakan full angka
        int batasBawahAscii = 48; //Bernilai int = 0
        int batasAtasAscii = 57; //Bernilai int = 9
        bool terdapatBukanAngka = false;
        for (int i = 0; i < panjangInput; i++)
        {
            if (                                        // Kondisi gagal input:
                inputStr == " " ||                      // Apabila terdapat spasi, atau
                int(inputStr[i]) < batasBawahAscii ||   // Apabila ASCII(input) < ASCII(0), atau
                int(inputStr[i]) > batasAtasAscii       // Apabila ASCII(input) > ASCII(9)
                )
            {
                terdapatBukanAngka = true;
                break;
            }
            
        }

        if (terdapatBukanAngka)
        {
            cout << "Input harus sepenuhnya berupa angka!" << endl;
            cout << "Ulangi Input: ";
            continue;
        }
        

        inputInt = stoi(inputStr);

        // Apabila sudah aman, cek apakah sesuai range yang diingkan
        if (inputInt < 1 || inputInt > nilaiMaksimal)
        {
            cout << "Input tidak sesuai! Coba lagi" << endl;
            cout << "Ulangi Input: ";
            continue;
        } else{
            sudahBenar = true;
        }
    }

    return inputInt;
}

//Untuk input bertipe string dari pengguna, sekaligus error handling
string strUserInput(){
    string input;
    bool sudahBenar = false;

    while (!sudahBenar)
    {
        getline(cin, input, '\n'); 
        int panjangInput = input.length();

        // Pengecekan apakah ada koma atau tidak dalam input
        // Koma bisa merusak file .csv (penyimpanan)
        bool terdapatKoma = false;
        for (int i = 0; i < panjangInput; i++)
        {
            if (input[i] == ',')
            {
                terdapatKoma = true;
                break;
            }
        }

        if (terdapatKoma)
        {
            cout << "Input tidak boleh mengandung koma! " << endl;
            cout << "Ulangi Input: ";
            continue;
        }
        

        // Cek panjang input
        if (input.length() > MAX_PANJANG_STRING)
        {
            cout << "Input terlalu panjang! Maksimal " << MAX_PANJANG_STRING << " karakter" << endl;
            cout << "Ulangi Input: ";
            continue;
        } else {
            sudahBenar = true;
        }    
    }

    return input;
}


//---------------------- FUNGSI OUTPUT DATA-------------------------------
//Output data menu
void outputMenu(vector<sMenu> menu){
    int banyakMenu = menu.size();

    cout << "Daftar menu: " << endl;
    for (int i = 0; i < banyakMenu; i++)
    {
        cout << i+1 << ". " << menu[i].nama << "\t\t | Rp." << menu[i].harga << endl;
    }
}


//---------------------- FUNGSI-FUNGSI ADMIN-------------------------------

//Admin --> login sebagai admin
bool loginAdmin(sKantin kantin){
    bool berhenti = false;
    string id, password;

    //Protokol login
    while (!berhenti)
    {
        cout << endl;
        cout << "Login sebagai Admin: " << endl;
        cout << "ID: "; 
        id = strUserInput();

        cout << "Password: "; 
        password = strUserInput();


        if (id == kantin.id && password == kantin.password)
        {
            cout << endl;
            cout << "---------------------------------------" << endl;
            cout << "Berhasil login!" << endl;
            cout << "---------------------------------------" << endl;
            cout << endl;
            berhenti = true;
            return true;
        } else {
            cout << "---------------------------------------" << endl;
            cout << "ID atau Password salah!" << endl;
            cout << "Tekan apapun untuk coba lagi (0 untuk kembali)" << endl;

            id = getch();
            if (id == "0")
            {
                berhenti = true;
                return false;
            }

            cout << "---------------------------------------" << endl;
        }
    }

    return true;
}

//Admin --> Menambahkan menu
void tambahkanMenu(vector<sMenu> &menu){
    string namaMenu;
    int hargaMenu;
    
    cout << endl;
    cout << "TAMBAHKAN MENU" << endl;

    cout << "Nama menu: "; 
    namaMenu = strUserInput();

    cout << "Harga menu: ";
    hargaMenu = intUserInput(MAX_HARGA);

    menu.push_back({namaMenu, hargaMenu});
    cout << "Menu ditambahkan! " << endl;
}

//Admin --> Menghapus menu
void hapusMenu(vector<sMenu> &menu){
    int indexYgDihapus;

    cout << endl;
    cout << "HAPUS MENU" << endl;
    cout << "Pilih menu untuk dihapus: ";
    indexYgDihapus = intUserInput(menu.size()) - 1;

    cout << "---------------------------------------" << endl;
    cout << indexYgDihapus + 1 << ". " << menu[indexYgDihapus].nama << " Rp." << menu[indexYgDihapus].harga << " dihapus!" << endl;
    cout << "---------------------------------------" << endl;

    menu.erase(menu.begin() + indexYgDihapus);
}

//Admin --> Update menu
void updateMenu(vector<sMenu> &menu){
    int banyakMenu = menu.size();

    cout << "Pilih menu untuk diubah harganya: ";
    int pilihan = intUserInput(banyakMenu);

    cout << "Harga menu yang diubah: ";
    int hargaPengganti = intUserInput(MAX_HARGA);

    menu[pilihan - 1].harga = hargaPengganti;

    cout << "\n----------------------------" << endl;
}

//---------------------- FUNGSI-FUNGSI PEMBELI-------------------------------

//Pembeli --> Print struk setelah pilih menu
void printStrukPembelian(vector<sMenu> menu, vector<int> indexDibeli, string nama){
    int banyakItem = indexDibeli.size();
    int totalHarga = 0;
    
    cout << endl;
    cout << "---------------------------------------" << endl;
    cout <<  NAMA_KANTIN << endl;
    cout << "Pesanan atas nama " << nama << endl;
    cout << "---------------------------------------" << endl;
    for (int i = 0; i < banyakItem; i++)
    {
        int index = indexDibeli[i];
        totalHarga += menu[index].harga;

        cout << i + 1 << ". " << menu[index].nama << "\t\tRp. " << menu[index].harga << endl;
    }

    cout << "---------------------------------------" << endl;
    cout << "Total: " << "\t\t\tRp. " << totalHarga << endl;
    cout << "---------------------------------------" << endl;
    cout << endl;
    cout << "Tekan tombol apapun untuk kembali..." << endl;
    getch();

    cout << endl;
    
}

//Pembeli --> Pilih menu untuk dibeli
void beliMenu(vector<sMenu> menu, string nama){
    int yangDibeli;
    vector<int> indexDibeli;
    
    int banyakMenu = menu.size();
    bool berhenti = false;

    cout << endl;
    cout << "BELI MENU" << endl;
    while (!berhenti)
    {
        cout << "Pilih menu untuk dibeli (" << banyakMenu+1 << " untuk berhenti): ";
        yangDibeli = intUserInput(banyakMenu+1);
        if (yangDibeli == banyakMenu+1)
        {
            berhenti = false;
            break;
        }

        indexDibeli.push_back(yangDibeli-1);

        cout << "Menu yang dipilih: ";
        for (int i = 0; i < indexDibeli.size(); i++)
        {
            cout << "(" << indexDibeli[i] + 1 << ") ";
        }
        cout << endl;
    }
    
    printStrukPembelian(menu, indexDibeli, nama);

}


//---------------------- FUNGSI MODE PROGRAM-------------------------------

//Jalankan program dengan mode admin
void modeAdmin(sKantin &kantin){
    bool berhenti = false;
    
    cout << endl;
    // Login dulu sebagai admin
    if (!loginAdmin(kantin)){
        return;
    }
    
    // Loop admin
    while (!berhenti)
    {
        cout << endl;
        cout << "---------------------------------------" << endl;
        cout << "Selamat Datang di " << kantin.nama << endl;
        cout << "---------------------------------------" << endl;
        outputMenu(kantin.menu);

        cout << "---------------------------------------" << endl;
        cout << "Pilih aksi:" << endl;
        cout << "(1) Tambahkan menu" << endl;
        cout << "(2) Hapus menu" << endl;
        cout << "(3) Ubah harga" << endl;
        cout << "(4) Kembali & simpan perubahan" << endl;
        cout << "---------------------------------------" << endl;
        cout << "Pilihan anda: ";

        switch (intUserInput(3))
        {
        case 1:
            tambahkanMenu(kantin.menu);
            break;
        case 2:
            hapusMenu(kantin.menu);
            break;
        case 3:
            updateMenu(kantin.menu);
            break;
        case 4:
            cout << endl;
            cout << "---------------------------------------" << endl;
            saveDataMenu(kantin.menu);
            cout << "Kembali ke menu awal..." << endl;
            cout << "---------------------------------------" << endl;
            berhenti = true;
            break;
        default:
            break;
        }
        

    }
}

//Jalankan program dengan mode pembeli
void modePembeli(sKantin kantin){
    string nama;
    bool berhenti = false;

    cout << endl;
    cout << "Nama anda: ";
    nama = strUserInput();

    while (!berhenti)
    {
        cout << endl;
        cout << "---------------------------------------" << endl;
        cout << "\nSelamat Datang " << nama << " di " << kantin.nama << endl;
        cout << "---------------------------------------" << endl;
        outputMenu(kantin.menu);

        cout << "---------------------------------------" << endl;
        cout << "Pilih aksi: " << endl;
        cout << "(1) Beli menu" << endl;
        cout << "(2) Kembali" << endl;
        cout << "---------------------------------------" << endl;
        cout << "Pilihan anda: ";

        switch (intUserInput(2))
        {
        case 1:
            beliMenu(kantin.menu, nama);
            break;
        case 2:
            cout << endl;
            cout << "---------------------------------------" << endl;
            cout << "Kembali ke menu awal..." << endl;
            cout << "---------------------------------------" << endl;
            berhenti = true;
            break;
        default:
            break;
        }
    }
}



//---------------------- FUNGSI UTAMA PROGRAM-------------------------------
int main(){
    sKantin kantin;
    mulaiProgram(kantin);

    bool akhiriProgram = false;

    while (!akhiriProgram)
    {
        cout << endl;
        cout << "\nSelamat Datang di " << kantin.nama << endl;
        cout << "---------------------------------------" << endl;
        cout << "Pilih Mode Akun: " << endl;
        cout << "(1) Mode Admin" << endl;
        cout << "(2) Mode Pembeli" << endl;
        cout << "(3) Akhiri program"  << endl;
        cout << "---------------------------------------" << endl;
        cout << "Pilihan anda: ";        


        switch (intUserInput(3))
        {
        case 1:
            modeAdmin(kantin);
            break;
        case 2:
            modePembeli(kantin);
            break;
        case 3:
            cout << "---------------------------------------" << endl;
            cout << "Menutup program..." << endl;
            cout << "---------------------------------------" << endl;
            akhiriProgram = true;
        default:
            break;
        }
    }

    getch();
}