/* Nama/ NIM		: Kelompok Tubes 1-7
 * Nama file		: HeaderPetak.h
 * Topik		    : Monopoly, Let's Get Wealthy
 * Tanggal		    : 23 November 2015
 * Deskripsi		: phase 3, header Petak
*/
#ifndef HEADERPETAK_H
#define HEADERPETAK_H
#include "boolean.h"
#include "array.h"

#define Nil NULL
/*Untuk Tipe Petak*/
#define BlockA 101
#define BlockB 102
#define BlockC 103
#define BlockD 104
#define BlockE 105
#define BlockF 106
#define BlockG 107 //tipe kota dibagi per blok
#define BlockH 108 //dibagi per blok
#define BlockP 301 //pariwisata
#define PetakChance 202
#define PetakBonus 203
#define PetakTax 204
#define PetakStart 205
#define PetakDIsland 206
#define PetakWorldCup 207
#define PetakWorldTravel 208

typedef struct {
	Name		namaPetak;
	int 		idxPetak;
	int 		tipePetak; //direpresentasikan sebagai angka saja
	int 		hargaBeliP;
	int 		hargaSewaP;
	int 		hargaJualP;
	int 		levelPetak;
	int			efekPetak;
	char		pemilik;
} Petak;


typedef struct TElmtListPetak *AddressT;

typedef struct TElmtListPetak {
	Petak 	 	infoT;
	AddressT	nextT;
} ElmtListPetak;

typedef struct {
	AddressT	firstT;
} ListPetak;


/*------------------------------------------------------*/

#define FirstT(L) (L).firstT
#define NextT(P) (P)->nextT
#define InfoT(P) (P)->infoT

#define NamaPtk(T) InfoT(T).namaPetak
#define IdxPtk(T) InfoT(T).idxPetak
#define TipePtk(T) InfoT(T).tipePetak
#define HBeliPtk(T) InfoT(T).hargaBeliP
#define HSewaPtk(T) InfoT(T).hargaSewaP
#define HJualPtk(T) InfoT(T).hargaJualP
#define LvPtk(T) InfoT(T).levelPetak
#define EfekPtk(T) InfoT(T).efekPetak
#define PemilikPtk(T) InfoT(T).pemilik

AddressT AlokasiPetak (Petak X);
/*	Mengirimkan Address hasil alokasi sebuah elemen
	Jika alokasi berhasil, maka Address tidak Nil, dan misalnya menghasilkan P, maka
	Info(P) = X, Next(P) = Nil
	Jika alokasi gagal, mengirimkan Nil
*/


void DealokasiPetak (AddressT *T);
/*	I.S. P terdefinisi
	F.S. P dikembalikan ke sistem
	Melakukan dealokasi/pengembalian Address P
*/

//----------------------------------------------------------------
boolean IsListEmptyT (ListPetak Board);
/* Mengirim true jika list kosong */

void InsertFirstT (ListPetak *Board, AddressT T);
/*	I.S. Sembarang, P sudah dialokasi
	F.S. Menambahkan elemen ber-Address P sebagai elemen pertama
*/


void InsertAfterT (ListPetak *Board, AddressT T, AddressT Trec);
/*	I.S. Prec pastilah elemen list dan bukan elemen terakhir,
	P sudah dialokasi
	F.S. Insert P sebagai elemen sesudah elemen beralamat Prec
*/

void InsertLastT (ListPetak *Board, AddressT T);
/*	I.S. Sembarang, P sudah dialokasi
	F.S. P ditambahkan sebagai elemen terakhir yang baru
*/

//----------------------------------------------------------------------
Petak IsiPetak (char nama[10], int idx,int tipe,int HBeli,int HSewa,int Lv,int Efek, char owner);
/*Mengisi data petak*/

void MasukkanPetak (ListPetak *Board, char nama[10], int idx,int tipe,int HBeli,int HSewa,int Lv,int Efek, char owner, AddressT *T);
/*Memasukkan petak kedalam list beserta datanya*/

void MakeInitialMap (ListPetak *Board);
/*Membuat peta awal*/

void HitungHarga (AddressT T, int *HargaBeliPaksa, int *HargaJual, int *HargaUpgrade, int *HargaSewa);
/*Menghitung harga-harga petak*/

void UpdateHargaPetak (ListPetak Board);
/*Mengupdate harga petak setiap berubah*/

static const int HAwal[33] =
{
	0, 0, 120, 0, 100, 160, 90, 100, 150, 0,
	200, 200, 200, 0, 100, 160, 200, 0, 200,
	150, 220, 0, 150, 150, 200, 0, 200, 210,
	190, 0, 300, 0, 200
};


#endif
