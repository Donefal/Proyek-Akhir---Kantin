## Update Kamis, 28 November 2024 (08:41 WIB)

Tujuan update ini adalah untuk memangkas fungsi-fungsi yang terlalu kompleks dan menyisakan yang benar-benar butuh.
Program awalnya hendak memiliki database 3 lapis yaitu kantin >> toko >> menu.
Database kantin & toko dihapus dan hanya menyisakan database menu.
Kuasa mode admin dalam program ini juga dikurangi untuk menjaga program tetap simpel.

### Fitur yang dikurangi:
- Database toko 
- Segala fungsi admin yang berhubungan dengan toko
- Database kantin
- Fungsi admin untuk edit menu

### Fitur yang ditambahkan:
- Database menu
- Persiapan program dalam menyimpan database menu ke dalam vektor
- Start program dalam mode admin
- Start program dalam mode pembeli
- Fungsi output menu
- Fungsi admin: login sebagai admin
- Fungsi admin: menambahkan menu
- Fungsi admin: menghapus menu tertentu
- Menetapkan nilai harga maksimal
- Fungsi pembeli: memilih menu untuk dibeli
- Pilihan untuk kembali di sebagian besar fungsi

### Fitur yang disempurnakan:
- Meng-hardcode nama, id, dan password kantin pada fungsi siapkanDataKantin()
- Meringkas fungsi pembacaan file csv jadi hanya untuk database menu
- Fungsi main() dirapihkan
- Fungsi input bertipe integer: Menambahkan parameter nilai maksimal untuk bisa diinput

### Fitur yang dikerjakan:
- Fungsi untuk output struk belanja
- Fungsi untuk save perubahan menu yang dilakukan oleh admin, dari vektor ke file csv
- Fungsi input bertipe integer: error handling apabila input memiliki angka didepan. Misal: 123ap
- Merapihkan & memperindah tampilan output
