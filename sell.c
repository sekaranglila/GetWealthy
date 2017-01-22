/* Nama/ NIM		: Kelompok Tubes 1-7
 * Nama file		: Sell.c
 * Topik		    : Monopoly, Let's Get Wealthy
 * Tanggal		    : 23 November 2015
 * Deskripsi		: phase 3, ADT berhubung dengan penjualan
*/
#include "HeaderGame.h"
#include "HeaderPemain.h"
#include "HeaderPetak.h"

//----------------------------------------------------------------------------------------


void OfferTile(ListPetak *Board, AddressP P, ListPemain Player, Name Kota, TabInt *Off)
/*menawarkan petak untuk dijual, petak dimasukkan ke Array "offered"
	Prekondisi : petak dimiliki sendiri

	input command :
	>sell <nama petak>
*/
{
	//Kamus Lokal
	AddressT T;
	int i;

	//Algoritma
	if (IsPenjara(P) == true)
	{
		printf("  Anda tidak bisa menjual aset karena Anda dipenjara!\n\n");
	}
	else
	{
		/*Memasukkan Kota ke dalam list yang akan dijual*/
	  	SearchKota(Kota,*Board,&T);
	  	if (T!=Nil)
	  	{
		  	if (PemilikPtk(T) != NamaPlyr(P))
		  	{
		  		printf("  Kota ini bukan milik Anda! Anda tidak berhak menjualnya!\n\n");
		  	}
		  	else
		  	{
		  		i = GetEmptyIdx(*Off);
		  		(*Off).TI[i] = IdxPtk(T);
		  		(*Off).NbElInt++;
		  		printf("  Kota %s sudah dimasukkan ke list Offered.\n\n", Kota);
		  	}
		  }
		  else
		  {
		  	printf("  Input nama kota salah!\n\n");
		  }
	}
}

void SellTile(ListPetak Board, Name Kota, ListPemain Player, AddressP P)
/*menjual petak ke bank, petak status diubah menjadi tidak berkepeilikan
	Prekondisi : petak dimiliki sendiri

	input command :
	>sell bank <nama petak>
*/
{
	 /* Kamus Lokal */
	AddressT T;
    /*AddressP A1;
    char Pemilik;
    int IdxKosong, IdxHapus;*/
    int i;

    /* Algoritma */
    //Algoritma
	if (IsPenjara(P) == true)
	{
		printf("  Kamu tidak bisa menjual aset karena Anda dipenjara!\n\n");
	}
	else
	{
		/*Memasukkan Kota ke dalam list yang akan dijual*/
	  	SearchKota(Kota,Board,&T);
	  	if (T!=Nil)
	  	{
		  	if (PemilikPtk(T) != NamaPlyr(P))
		  	{
		  		printf("  Kota ini bukan milikmu! Kamu tidak berhak menjualnya!\n\n");
		  	}
		  	else
		  	{
		  		//Menambahkan uang pemilik petak
		  		UangPlyr(P) = UangPlyr(P) + (HJualPtk(T)*0.9);

		  		//Merubah kepemilikan Petak serta data Petak
		  		PemilikPtk(T) = 'X';
		  		HSewaPtk(T) = 0;
		  		HBeliPtk(T) = HAwal[IdxPtk(T)];
		  		LvPtk(T) = 0;
		  		EfekPtk(T) = 1;
		  		HJualPtk(T) = 0;

		  		//Output Pemain
		  		printf("  Kota %s sudah dijual ke bank.\n\n", Kota);

		  		//Menghapus data kepemilikan petak tersebut dari array Kepemilikan pemain
		  		i = SearchIdx(PropPlyr(P), IdxPtk(T));
		  		while (PropPlyr(P).TI[i] != ValUndefInt)
		  		{
		  			PropPlyr(P).TI[i] = PropPlyr(P).TI[i + 1];
					i=i+1;

		  		}
		  		PropPlyr(P).NbElInt = PropPlyr(P).NbElInt - 1;
		  	}
		}
		else
		{
			printf("  Input nama kota salah\n\n");
		}

	}
}

void ShowOffered(TabInt Off, ListPetak L)
/*menampilkan petak yang ada di list "Offered"

	input command :
	>show offered
*/
{
	// Kamus Lokal
	AddressT T;
	int i;

	//Algoritma
    i = 1;
    while (Off.TI[i] != ValUndefInt)
    {
        T = SearchKotaId(Off.TI[i],L);
        printf("  %s :\n", NamaPtk(T));
        SeePrice(L, NamaPtk(T));
        printf("\n");
        i++;
    }
}



void SellAll (ListPetak Board, AddressP P)
{
	/*Kamus*/
	int i;
	AddressT T;

	/*Algoritma*/
	while (PropPlyr(P).NbElInt != 0)
	{
		T = SearchKotaId(PropPlyr(P).TI[1],Board);

		//Menambahkan uang pemilik petak
		UangPlyr(P) = UangPlyr(P) + (HJualPtk(T)*0.9);

		//Merubah kepemilikan Petak serta data Petak
		PemilikPtk(T) = 'X';
		HSewaPtk(T) = 0;
		HBeliPtk(T) = HAwal[IdxPtk(T)];
		LvPtk(T) = 0;
		EfekPtk(T) = 1;
		HJualPtk(T) = 0;

		//Menghapus data kepemilikan petak tersebut dari array Kepemilikan pemain
		i = SearchIdx(PropPlyr(P), IdxPtk(T));
		while (PropPlyr(P).TI[i] != ValUndefInt)
		{
			PropPlyr(P).TI[i] = PropPlyr(P).TI[i + 1];
			i=i+1;
		}
		PropPlyr(P).NbElInt = PropPlyr(P).NbElInt - 1;
	}
}

