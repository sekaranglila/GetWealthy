/* Nama/ NIM        : Kelompok Tubes 1-7
 * Nama file        : Pemain.c
 * Topik            : Monopoly, Let's Get Wealthy
 * Tanggal          : 23 November 2015
 * Deskripsi        : phase 3, ADT berhubung dengan player
*/

#include "HeaderGame.h"
#include "HeaderPemain.h"
#include "HeaderPetak.h"



AddressP AlokasiPemain (Pemain X)
/*	Mengirimkan Address hasil alokasi sebuah elemen
	Jika alokasi berhasil, maka Address tidak Nil, dan misalnya menghasilkan P, maka
	Info(P) = X, Next(P) = Nil
	Jika alokasi gagal, mengirimkan Nil
*/
{
	/*Kamus Lokal*/
	AddressP P;

	/*Algoritma*/
	P = (AddressP) malloc(sizeof(ElmtListPemain));
	if (P != Nil)
	{
		InfoP(P)=X;
		NextP(P)=Nil;
	}
	else
		P = Nil;
	return P;
}

void DealokasiPemain (AddressP *P)
/*	I.S. P terdefinisi
	F.S. P dikembalikan ke sistem
	Melakukan dealokasi/pengembalian Address P
*/
{
	free(*P);
}

boolean IsListEmptyP (ListPemain Player)
/* Mengirim true jika list kosong */
{
	if (FirstP(Player)==Nil)
		return true;
	else
		return false;
}

void InsertFirstP (ListPemain *Player, AddressP P)
/*	I.S. Sembarang, P sudah dialokasi
	F.S. Menambahkan elemen ber-Address P sebagai elemen pertama
*/
{
	NextP(P) = FirstP(*Player);
	FirstP(*Player) = P;
}

void InsertAfterP (ListPemain *Player, AddressP P, AddressP Prec)
/*	I.S. Prec pastilah elemen list dan bukan elemen terakhir,
	P sudah dialokasi
	F.S. Insert P sebagai elemen sesudah elemen beralamat Prec
*/
{
	NextP(P) = NextP (Prec);
	NextP(Prec) = P;
}

void InsertLastP (ListPemain *Player, AddressP P)
/*	I.S. Sembarang, P sudah dialokasi
	F.S. P ditambahkan sebagai elemen terakhir yang baru
*/
{
	/*Kamus Lokal*/
	AddressP Last;

	/*Algoritma*/
	if (IsListEmptyP(*Player)==true)
		InsertFirstP(Player,P);
	else
	{
		Last = FirstP(*Player);
		do
			Last = NextP(Last);
		while ((NextP(Last)!=FirstP(*Player))&&(NextP(Last)!=Nil));
		InsertAfterP(Player,P,Last);
	}
	NextP(P) = FirstP(*Player);
}

//----------------------------------------------------------------------------

Pemain IsiPemain (
	char		nama,
	int 		urutan,
	boolean		giliran,
	boolean		bangkrut,
	boolean		dipenjara,
	int			indeks,
	AddressT	posisi	)

{
	Pemain Player;

	Player.namaPemain = nama;
	Player.xPemain = urutan;
	Player.statGiliran = giliran;
	Player.statBangkrut = bangkrut;
	Player.statPenjara = dipenjara;
	Player.id = indeks;
	Player.posisiX = posisi;


return Player;
}

void MasukkanPemain (ListPemain *Player, char nama, int urutan,boolean giliran,boolean bangkrut,boolean dipenjara,int indeks, AddressT posisi, AddressP *P)
{
	/*Kamus Lokal*/
	Pemain X;

	/*Algoritma*/
	X = IsiPemain(nama,urutan,giliran,bangkrut,dipenjara,indeks,posisi);
	InisialisasiArrayInt(&(X.kartu));
	InisialisasiArrayInt(&(X.kepemilikan));

	X.uang = 1000;
	*P = AlokasiPemain (X);
	if ((*P)!=Nil)
	{
		InsertLastP(Player,*P);
	}


}

void AddPlayer (ListPemain *Player, ListPetak Board, int N)
{
	/*Kamus*/
	AddressP P;

	/*Algpritma*/
	FirstP(*Player) = Nil;
	MasukkanPemain (Player,'A',1,true,false,false,1,FirstT(Board),&P);
	FirstP(*Player) = P;
	MasukkanPemain (Player,'B',2,false,false,false,1,FirstT(Board),&P);

	if (N==3)
	{
		MasukkanPemain (Player,'C',3,false,false,false,1,FirstT(Board),&P);
	}

	if (N==4)
	{
		MasukkanPemain (Player,'C',3,false,false,false,1,FirstT(Board),&P);
		MasukkanPemain (Player,'D',4,false,false,false,1,FirstT(Board),&P);
	}
}

void InisialisasiArrayInt (TabInt *T)
/* Mengisi elemen array dengan ValUndefInt dan indeks IdxUndef */
{
	/* Kamus Lokal */
	int i;

	/* ALgoritma */
	(*T).NbElInt = IdxUndef;
	for (i = IdxMinInt; i <= IdxMaxInt; i++)
	{
		(*T).TI[i] = ValUndefInt;
	}
	(*T).NbElInt = 0;
}


//---------------------------------------------------------------------------------------------

void UpgradeTile(AddressP P)
/*mengupgrade level bangunan yang sedang ditempati, update board jika berhasil
	Prekondisi : petak dimiliki sendiri

	input command :
	>upgrade

	A adalah address pemain yang sedang aktif dan pada gilirannya
*/
{
/*Kamus Lokal*/
    AddressT T;
    int a,b,c,Upgrade;

/*Algoritma*/
    T = PetakPlyr(P);
    if (PemilikPtk(T) == NamaPlyr(P))
    {
        if (LvPtk(T)<5)
        {
            if ((TipePtk(T) >= 101) && (TipePtk(T) <= 108))
            {
                HitungHarga (T,&a,&b,&Upgrade,&c);
                if (UangPlyr(P) >= Upgrade)
                {
                    printf("  Selamat bangunan Anda di kota %s memiliki Level %d\n", NamaPtk(T), (LvPtk(T) + 1));
                    LvPtk(T) = LvPtk(T) + 1;
                    UangPlyr(P) = UangPlyr(P) - Upgrade;
                    HitungHarga (T,&a,&HJualPtk(T),&b,&HSewaPtk(T));
                    if (LvPtk(T) == 5)
                    {
                        printf("  Selamat, %s telah memiliki Landmark!\n", NamaPtk(T));
                    }
                    printf("  Sisa Uang Anda : ");
                    WriteMoney(UangPlyr(P));
                    printf("\n\n");
                }
                else
                {
                   printf("  Uang Anda tidak cukup untuk melakukan upgrade bangunan\n\n");
                }
            }
            else
            {
            	printf("  Petak ini tidak dapat diupgrade\n\n");
            }
        }
        else
        {
			printf("  Bangunan Anda sudah mencapai Landmark. Sudah tidak dapat di upgrade lagi!\n\n");
        }
    }
    else
    {
        printf("  Petak ini bukan milik Anda\n\n");
    }
}


void EndTurn(ListPemain Player, AddressP *A)
/*megakhiri giliran, berlanjut ke pemain lain yang belum bangkrut

    input command :
    >end turn
*/
{
	/*Kamus*/
	AddressP P;

	/*Algoritma*/
    printf("  Player %c mengakhiri giliran.\n",NamaPlyr(*A));

    P = *A;
    do
    {
    	*A = NextP(*A);
    }
    while ((StatPlyr(*A)==true)&&(*A!=P));

    if (*A == P)
    {
    	printf("  Player %c telah memenangkan permainan\n\n", NamaPlyr(P));
    }
    else
    {
	    GiliranPlyr(P) = false;
	    GiliranPlyr(*A) = true;
	    printf("  Giliran player %c!\n\n", NamaPlyr(*A));
    }

}


void AutoSyncPemain (ListPemain Player, ListPetak Board)
{
	/*Kamus*/
	AddressP P;
	int i;
	/*Algoritma*/
	P = FirstP (Player);

	for (i=1;i<=4;i++)
	{
		if (IdxPlyr(P)!=0)
		{
			PetakPlyr(P) = SearchKotaId(IdxPlyr(P),Board);
		}
	}
}

