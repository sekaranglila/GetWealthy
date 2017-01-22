/* Nama/ NIM		: Kelompok Tubes 1-7
 * Nama file		: HeaderGame.h
 * Topik		    : Monopoly, Let's Get Wealthy
 * Tanggal		    : 23 November 2015
 * Deskripsi		: phase 3, header semua subprogram lain
*/

#include "HeaderPemain.h"
#include "boolean.h"
#include "array.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


#ifndef HEADERGAME_H
#define HEADERGAME_H
/*------------------------------------SELL-----------------------------------------*/

void OfferTile(ListPetak *Board, AddressP P, ListPemain Player, Name Kota, TabInt *Off);
/*menawarkan petak untuk dijual, petak dimasukkan ke list "offered"
	Prekondisi : petak dimiliki sendiri

	input command :
	>sell <nama petak>

	A adalah address pemain yang sedang aktif dan pada gilirannya
*/

void SellTile(ListPetak Board, Name Kota, ListPemain Player, AddressP P);
/*menjual petak ke bank, petak status diubah menjadi tidak berkepeilikan
	Prekondisi : petak dimiliki sendiri

	input command :
	>sell bank <nama petak>

	A adalah address pemain yang sedang aktif dan pada gilirannya
	Harga jual adalah 90% dari harga total petak (lahan + properti)
*/

void SellAll (ListPetak Board, AddressP P);



/*-------------------------------------BUY-----------------------------------------*/

void BuyTile(int X, AddressP A);
/*Fungsi dasar membeli Petak, mengubah status petak yang dibeli
    A adalah address pemain yang sedang aktif dan pada gilirannya
*/

void NormalBuyTile(AddressP A);
/*membeli petak yang ditempati sekarang
	Prekondisi : tidak dimiliki pemain lain

	input command :
	>buy

	A adalah address pemain yang sedang aktif dan pada gilirannya
*/

void ForceBuyTile(ListPemain Player, AddressP A);
/*membeli petak yang ditempati sekarang
	Prekondisi : petak dimiliki pemain lain

	input command :
	>buy

	A adalah address pemain yang sedang aktif dan pada gilirannya
*/

void OfferedBuyTile(ListPetak *Board, ListPemain Player, AddressP A, TabInt *Off, Name Kota);
/*membeli petak yang dijual ditawarkan dalam list "offered"
	Prekondisi : petak dimiliki pemain lain

	input command :
	>buy offered <nama petak>

	A adalah address pemain yang sedang aktif dan pada gilirannya
*/
//-----------------------------------

int GetEmptyIdx(TabInt Tab);
/*Mencari Idx kosong dalam array TabInt*/

int SearchIdx(TabInt Tab, int ID);
/*Mencari Idx tertentu dalam array TabInt*/

void WriteMoney (int M);
/*Menuliskan jumlah uang ke layar*/

boolean IsKepemilikan(TabInt Tab, int ID);
/*Memastikan kepemilikan pemain*/

void ShowKepemilikan(ListPetak Board, AddressP P);
/*Menampilkan aset pemain*/

boolean IsTripleMonopoly (AddressP P, ListPetak Board);
/*Memeriksa apakah ada pemain yang triple monopoly(3 blok milih 1 pemain)*/

boolean IsGameOver(ListPemain Player, AddressP P, ListPetak Board);
/*Memeriksa apakah sudah Game Over atau belum*/

boolean IsBlok (AddressT T, ListPetak Board);
/*Memeriksa apakah 1 blok milik 1 pemain*/

void CekBlock (AddressT T, ListPetak Board);
/*Memberi efek pada 1 blok milik pemain*/

/*-----------------------------------INTERNAL--------------------------------------*/
void RollDice(AddressP P, AddressT *T, ListPetak Board, ListPemain Player, boolean *ulang);
/*Melempar Dadu -- sekaligus double roll

	input command :
	>roll dice
*/

void ShowBoard(ListPetak Board, ListPemain Player);
/*menampilkan board pemain dan situasi pemain
	(posisi setiap pemain, kepemilikan, properti, dll)

	input command :
	>board
*/
/*Subprogram Perhitungan & Update Board*/


void SeePrice(ListPetak Board, Name Kota);
/*Melihat harga jual petak:
	Biaya Sewa, Biaya Ambil Alih, Biaya Upgrade Bangunan

	Prekondisi : sudah dimiliki oleh pemain (siapapun)

	input command :
	>info <nama petak>

	Board adalah list petak, Kota adalah nama petak yang dimaksud
*/

void ShowOffered(TabInt Off, ListPetak L);
/*menampilkan petak yang ada di list "Offered"

	input command :
	>show offered
*/

void GetChance(AddressP P, ListPetak Board, ListPemain Player);
/*mengambil kartu kesempatan, kartu yang didapat random
	WARNING : otomatis saat prekondisi terpenuhi
	Prekondisi : berada di petak 'chance'

	A adalah address pemain yang sedang aktif dan pada gilirannya
*/

void PayTax(ListPetak Board, AddressP A);
/*membayar pajak
	WARNING : otomatis saat prekondisi terpenuhi
	Prekondisi : berada di petak 'tax'

	A adalah address pemain yang sedang aktif dan pada gilirannya
*/

void GetBonus(AddressP A);
/*mendapat uang bonus, uang yang didapat random
	WARNING : otomatis saat prekondisi terpenuhi
	Prekondisi : berada di petak 'bonus'

	A adalah address pemain yang sedang aktif dan pada gilirannya
*/

void WorldCupTime(ListPetak *Board, ListPemain L, AddressP P);
/*memilih tile untuk world cup mengganti efek petak yang dipilih
	WARNING : Efek world cup akan berhenti ketika pemain tersebut melewati petak world cup
	Prekondisi : Berada di petak 'World Cup'

	input command :
	>host <nama kota>
*/

void WorldTravelTime(ListPetak Board, AddressP A, ListPemain Player);
/*memilih tile yang dituju, pemain bergerak maju menuju petak itu
	Jika melewati start akan mendapat uang
	Prekondisi : Berada di petak 'World Travel'

	input command :
	>travel <nama kota>

	A adalah address pemain yang sedang aktif dan pada gilirannya
*/


void SaveFile(ListPetak Board, ListPemain Player, TabInt Off, char nf[10]);
/*menyimpan game ke file eksternal sehingga dapat dilanjutkan

	input command :
	>save <nama file>
*/

void LoadFile(ListPetak *Board, ListPemain *Player, TabInt *Off, char nf[10], boolean *loading);
/*memulai permainan dari save file

	input command :
	>load <nama file>

*/
char IntegerToChar (int X);
/*Merubah integer ke char*/

/*Check efek & matikan*/
void CekHost (AddressP P,ListPetak Board);
/*Mengecek apakah host dari suatu petak adalah P*/

void CekOff (AddressP P, ListPetak Board);
/*Mengecek status mati lampu*/


/*Subprogram untuk kartu*/

int HitungAset (ListPetak L, AddressP P);
/*Menghitung aset milik pemain P*/

void SearchKota(Name kota, ListPetak Board, AddressT *T);
/*Mencari kota tertentu dalam board sesuai dengan namanya*/

AddressT SearchKotaId(int id, ListPetak Board);
/* Mengembalikan address suatu kota sesuai dengan ID nya*/

AddressP SearchPlayerId (int id, ListPemain Player);
/*Mengembalikan address player sesuai dengan Id nya*/

AddressP SearchPlayerName (char c,ListPemain Player);
/*Mengembalikan address player seusai dengan namanya*/


//Kartu Chance
boolean SearchKartu (AddressP P, int N);
/*Memastikan bahwa player P memiliki kartu tertentu*/

void DeleteCard(AddressP P, int N);
/*Menghapus kartu yang telah dipakai dari array kartu pemain yang memakainya*/

void freeme (AddressP P, ListPemain Player);
/*Membebaskan pemain dari penjara jika punya kartu bebas penjara dan memperbolehkannya untuk
membayar keluar penjara*/

void freetax (ListPetak Board, AddressP P);
/*Membebaskan pemain dari pajak jika punya kartu bebas pajak dan memperbolehkannya menjual aset*/

void UseProtect (AddressP P, AddressT T);
/*Melindungi kota yang dimiliki pemain P menggunakan kartu protect jika punya*/


/*Main*/
void PrintPerintah ();
/*Menampilkan perintah game ke layar*/

void BayarSewa (AddressP P, ListPemain LP, ListPetak Board);
/*Membuat player yang singgah di petak milik player lain untuk membayar sewanya*/

boolean isOffempty (TabInt Off);
/*Memeriksa apakah array offered kosong atau tidak*/

boolean BisaBeli (AddressT T);
/*Menentukan apakah player dalam kondisi boleh membeli petak T atau tidak*/

#endif
