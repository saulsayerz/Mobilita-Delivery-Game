# TUGAS BESAR ALSTRUKDAT
## MOBILITAAA

## Table of Contents
- [General Info](#general-information)
- [File penting](#file-penting)
- [Instalasi](#instalasi)
- [Run Program](#run-program)
- [Pembagian Tugas](#pembagian-tugas)
- [Daftar Fitur](#daftar-fitur)

### General Information
Dengan adanya pandemi COVID-19, usaha orang tua Mobita mengalami penurunan
pendapatan. Setelah diringankannya PPKM, Mobita ingin membantu orang tuanya
mendapat penghasilan menjadi seorang kurir. Tugas kalian adalah membantu Mobita
membuatkan aplikasi yang akan membantunya melacak pesanan, navigasi peta, mengambil
dan menurunkan barang.

### File penting
| Lokasi               |  Konten                                            |
|----------------------|--------------------------------------------------- |
| `/gadget`            | Modul gadget <b>(List Statis)</b>                  |
| `/inventory`         | Modul inventory <b>(List Statis)</b>               |
| `/map`               | Modul map <b>(Point, List Dinamis, Matriks)</b>    |
| `/mesin`             | Modul mesin <b>(Mesin Karakter, Mesin Kata)</b>    |
| `/mobita`            | Modul mobita <b>(ADT Bentukan)</b>                 |
| `/pesanan`           | Modul pesanan <b>(Queue, Linked List)</b>          |
| `/tas`               | Modul tas <b>(Stack)</b>                           |
| `main.c`             | Main program                                       |
| `Makefile`           | Makefile buat kompilasi program                    |
| `*.txt`              | File konfigurasi atau save file                    |

## Instalasi
#### Sebelum mulai <br><br>
Sebelum memulai, Anda harus menginstal dan menjalankan yang berikut:

- [X] gcc
- [X] make

#### Template

* Kompilasi dengan Makefile
  ```
  Pada foler utama
  $ make compileobj rmunused build clean
  ```

### Run Program

```
Pada folder utama
$ make test
```
atau
```
Pada folder utama
$ ./main
```

### Pembagian Tugas
| NIM       | Nama                     | Tugas                                                                  |
| --------- | ------------------------ | ---------------------------------------------------------------------- |
| 13520063  | Louis Yanggara           | Inprogress, dropOff, laporan bagian 1,3,4,8,9                          |
| 13520072  | Jova Andres Riski Sirait | Todolist, buy, wrap up, final debugging dan fix bug, charmachine, save, load, vip item, return to sender, laporan bagian 2 7                    |
| 13520075  | Samuel Christopher Swandi| Increment time, pickup item, display todolist dan inprogress           |
| 13520094  | Saul Sayers              | ADT map, pesanan, konfigurasi awal,help,move,displaymap, laporan bagian 5 6 7            |
| 13520100  | Averrous Saloom          | Mobita, Tas, Inventory, Manajemen Efek (gadget, reward, perishable), senter pengecil, laporan bagian 5    |

### Daftar Fitur
| Fitur         | Status Pengerjaan |
| ------------- | ----------------- |
| MOVE          | Selesai           |
| PICK_UP       | Selesai           |
| DROP_OFF      | Selesai           |
| MAP           | Selesai           |
| TO_DO         | Selesai           |
| IN_PROGRESS   | Selesai           |
| BUY           | Selesai           |
| INVENTORY     | Selesai           |
| HELP          | Selesai           |
| SAVE_GAME     | Selesai           |
| RETURN        | Selesai           |

#### Keterangan tambahan
```
Disarankan menjalankan program di Linux.
Mesin kata tidak bekerja dengan baik di Windows (unresolved bug)

Jika binary file tidak bisa di execute, bisa dilakukan compile ulang pada program
```
[Link github](https://github.com/saulsayerz/Tugas-Besar-Alstrukdat)