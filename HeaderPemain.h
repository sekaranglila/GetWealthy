/* Nama/ NIM		: Kelompok Tubes 1-7
 * Nama file		: HeaderPemain.h
 * Topik		    : Monopoly, Let's Get Wealthy
 * Tanggal		    : 23 November 2015
 * Deskripsi		: phase 3, header Pemain
*/
#ifndef HEADERPEMAIN_H
#define HEADERPEMAIN_H

#include "HeaderPetak.h"
#include "boolean.h"
#include "array.h"



/*List untuk pemain, ditujukan supaya mudah jika pindah giliran tinggal nextH(X)*/

typedef struct {
	TabInt 		kartu;
	TabInt		kepemilikan;
	AddressT	posisiX;                 //pointer ke element petak, supaya mudah jika ingin mengubah yang ada di petak
	boolean		statGiliran;
	boolean		statBangkrut;
	boolean     statPenjara;
	int			id;                       //index petak dimana player ada
	int         uang;                     //uang yang dimiliki pemain
	int 		xPemain;                  //nomor urutan pemain
	char		namaPemain;
} Pemain;

typedef struct TElmtListPemain *AddressP;

typedef struct TElmtListPemain {
	Pemain  	infoP;
	AddressP	nextP;
} ElmtListPemain;

typedef struct {
	AddressP	firstP;
} ListPemain;

/*---------------------------------------------------------------------------------------------------------*/

#define FirstP(L) (L).firstP
#define NextP(P) (P)->nextP
#define InfoP(P) (P)->infoP

#define KartuPlyr(T) InfoP(T).kartu
#define PropPlyr(T) InfoP(T).kepemilikan
#define PetakPlyr(T) InfoP(T).posisiX
#define IsPenjara(T) InfoP(T).statPenjara
#define StatPlyr(T) InfoP(T).statBangkrut
#define GiliranPlyr(T) InfoP(T).statGiliran
#define IdxPlyr(T) InfoP(T).id
#define UangPlyr(T) InfoP(T).uang
#define NoPlyr(T) InfoP(T).xPemain
#define NamaPlyr(T) InfoP(T).namaPemain


AddressP AlokasiPemain (Pemain X);
/*	Mengirimkan Address hasil alokasi sebuah elemen
	Jika alokasi berhasil, maka Address tidak Nil, dan misalnya menghasilkan P, maka
	Info(P) = X, Next(P) = Nil
	Jika alokasi gagal, mengirimkan Nil
*/

void DealokasiPemain (AddressP *P);
/*	I.S. P terdefinisi
	F.S. P dikembalikan ke sistem
	Melakukan dealokasi/pengembalian Address P
*/

boolean IsListEmptyP (ListPemain Player);
/* Mengirim true jika list kosong */

void InsertFirstP (ListPemain *Player, AddressP P);
/*	I.S. Sembarang, P sudah dialokasi
	F.S. Menambahkan elemen ber-Address P sebagai elemen pertama
*/

void InsertAfterP (ListPemain *Player, AddressP P, AddressP Prec);
/*	I.S. Prec pastilah elemen list dan bukan elemen terakhir,
	P sudah dialokasi
	F.S. Insert P sebagai elemen sesudah elemen beralamat Prec
*/

void InsertLastP (ListPemain *Player, AddressP P);
/*	I.S. Sembarang, P sudah dialokasi
	F.S. P ditambahkan sebagai elemen terakhir yang baru
*/


//----------------------------------------------------------------------------

Pemain IsiPemain (
	char		nama,
	int 		urutan,
	boolean		giliran,
	boolean		bangkrut,
	boolean		dipenjara,
	int			indeks,
	AddressT	posisi	);

void MasukkanPemain (ListPemain *Player, char nama, int urutan,boolean giliran,boolean bangkrut,boolean dipenjara,int indeks, AddressT posisi, AddressP *P);

void AddPlayer (ListPemain *Player, ListPetak Board, int N);

void InisialisasiArrayInt (TabInt *T);
/* Mengisi elemen array dengan ValUndefInt dan indeks IdxUndef */


//----------------------------------------------------------------

void UpgradeTile(AddressP P);
/*mengupgrade level bangunan yang sedang ditempati, update board jika berhasil
	Prekondisi : petak dimiliki sendiri

	input command :
	>upgrade

	A adalah address pemain yang sedang aktif dan pada gilirannya
*/


void ShowLeaderBoard(ListPetak Board,ListPemain Player,int nplayer);
/*menampilkan peringkat pemain
	berdasarkan uang dan nilai jual asset

	input command :
	>leaderboard
*/


void EndTurn(ListPemain Player, AddressP *A);
/*megakhiri giliran, berlanjut ke pemain lain yang belum bangkrut
	Prekondisi : Berada di petak 'World Travel'

	input command :
	>end turn

	I.S. A adalah address pemain yang sedang aktif dan pada gilirannya
	F.S. A diganti dengan address pemain berikutnya
*/



//---------------------------------------------------------


#endif
