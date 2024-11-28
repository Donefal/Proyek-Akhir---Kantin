#include <iostream>
#include <conio.h>
#include <fstream>
#include <vector>

using namespace std;
const int MAX_HARGA = 1000000;

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


//Untuk persiapan awal menjalankan program --> Kantin dulu baru menu
void siapkanDataMenu(vector<sMenu> &menu){
    string namaFile = "dataMenu.csv";
    ifstream fileMenu(namaFile);

    if (!fileMenu.is_open())
    {
        cout << "Terdapat error dalam membuka file: " << namaFile << endl;
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

        menu.push_back({namaMenu, stoi(hargaMenu)});
    }
    
    fileMenu.close();
}

//Untuk persiapan awal menjalankan program --> Kantin dulu baru menu
void siapkanDataKantin(sKantin &kantin){
    kantin.nama = "Kantin Firas";
    kantin.id = "idkantin";
    kantin.password = "passkantin";

    siapkanDataMenu(kantin.menu);
}

//BELUM DIMULAI | Fungsi untuk save perubahan menu
void saveDataMenu(vector<sMenu> &menu){

}


//Untuk input bertipe int dari pengguna, sekaligus error handling
int intUserInput(int pilihanMaksimal){
    int input;
    bool sudahBenar = false;
    
    while (!sudahBenar)
    {
        cin >> input;
        if (cin.fail())
        {
            cout << "Pilihan tidak sesuai! Coba lagi" << endl;
            cin.clear();
            cin.ignore(100, '\n');
        } else if (input < 1 || input > pilihanMaksimal)
        {
            cout << "Pilihan tidak sesuai! Coba lagi" << endl;
            cin.ignore(100, '\n');
        } else{
            cin.ignore(100, '\n');
            sudahBenar = true;
        }
        
    }

    return input;
}

//Untuk input bertipe string dari pengguna, sekaligus error handling
string strUserInput(){
    string input;
    while (true)
    {
        getline(cin, input);
        if (cin.fail())
        {
            cout << "Input tidak sesuai! Coba lagi" << endl;
            cin.clear();
            cin.ignore(100,'\n');
        } else {
            break;
        }
    }

    return input;
}


//Output data menu
void outputMenu(vector<sMenu> menu){
    int banyakMenu = menu.size();

    cout << "Daftar menu: " << endl;
    for (int i = 0; i < banyakMenu; i++)
    {
        cout << i+1 << ". " << menu[i].nama << "\t\t| Rp." << menu[i].harga << endl;
    }
}


//Kuasa admin --> Menambahkan menu
void tambahkanMenu(vector<sMenu> &menu){
    string namaMenu;
    int hargaMenu;

    cout << "TAMBAHKAN MENU" << endl;
    cout << "Nama menu: "; 
    namaMenu = strUserInput();

    cout << "Harga menu: ";
    hargaMenu = intUserInput(MAX_HARGA);

    menu.push_back({namaMenu, hargaMenu});
    cout << "Menu ditambahkan! " << endl;
}

//Kuasa admin --> Menghapus menu
void hapusMenu(vector<sMenu> &menu){
    int yangDihapus;

    cout << "HAPUS MENU" << endl;
    cout << "Pilih menu untuk dihapus: ";
    yangDihapus = intUserInput(menu.size()) - 1;

    cout << "---------------------------------------" << endl;
    cout << yangDihapus+1 << ". " << menu[yangDihapus].nama << " Rp." << menu[yangDihapus].harga << " dihapus!" << endl;
    cout << "---------------------------------------" << endl;

    menu.erase(menu.begin() + yangDihapus);
}


//Kuasa pembeli --> Print struk setelah pilih menu
void printStrukPembelian(vector<int> keranjang, string nama){
    int banyakItem = keranjang.size();

    cout << "Intinya mah nanti ada format struk pembeliannya" << endl;
    cout << "Index item yang dibeli: ";
    for (int i = 0; i < banyakItem; i++)
    {
        cout << keranjang[i] << " ";
    }
    cout << endl;
    
    /*
        Ini nanti pokoknya diformatin aja sebagus mungkin
    */
}

//Kuasa pembeli --> Pilih menu untuk dibeli
void beliMenu(vector<sMenu> menu, string nama){
    int yangDibeli;
    vector<int> keranjang;
    
    int banyakMenu = menu.size();
    bool berhenti = false;

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
    
        keranjang.push_back(yangDibeli-1);
    }
    
    printStrukPembelian(keranjang, nama);

}


//Jalankan program dengan mode admin
void modeAdmin(sKantin &kantin){
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
            cout << "---------------------------------------" << endl;
            cout << "Berhasil login!" << endl;
            cout << "---------------------------------------" << endl;
            cout << endl;
            berhenti = true;
        } else {
            cout << "---------------------------------------" << endl;
            cout << "ID atau Password salah!" << endl;
            cout << "---------------------------------------" << endl;
        }
    }
    
    //////////////////////////////////////////////////////////////////////
    //Menu admin
    berhenti = false;
    while (!berhenti)
    {
        cout << "Selamat Datang di " << kantin.nama << endl;
        cout << "---------------------------------------" << endl;
        outputMenu(kantin.menu);

        cout << "---------------------------------------" << endl;
        cout << "Pilih aksi:" << endl;
        cout << "(1) Tambahkan menu" << endl;
        cout << "(2) Hapus menu" << endl;
        cout << "(3) Kembali" << endl;
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

//Jalankan program dengan mode pembeli
void modePembeli(sKantin kantin){
    string nama;
    bool berhenti = false;

    cout << "Nama anda: ";
    nama = strUserInput();

    while (!berhenti)
    {
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


//Fungsi utama program
int main(){
    sKantin kantin;
    siapkanDataKantin(kantin);

    bool akhiriProgram = false;

    while (!akhiriProgram)
    {
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
            cout << "saveProgress()" << endl;
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
