/* Nama/ NIM		: Kelompok Tubes 1-7
 * Nama file		: Petak.c
 * Topik		    : Monopoly, Let's Get Wealthy
 * Tanggal		    : 23 November 2015
 * Deskripsi		: phase 3, ADT berhubung dengan board game
*/

#include "HeaderGame.h"
#include "HeaderPemain.h"
#include "HeaderPetak.h"

AddressT AlokasiPetak (Petak X)
/*	Mengirimkan Address hasil alokasi sebuah elemen
	Jika alokasi berhasil, maka Address tidak Nil, dan misalnya menghasilkan P, maka
	Info(P) = X, Next(P) = Nil
	Jika alokasi gagal, mengirimkan Nil
*/
{
	/*Kamus Lokal*/
	AddressT P;

	/*Algoritma*/
	P = (AddressT) malloc(sizeof(ElmtListPetak));
	if (P != Nil)
	{
		InfoT(P)=X;
		NextT(P)=Nil;
	}
	else
		P = Nil;
	return P;
}

void DealokasiPetak (AddressT *T)
/*	I.S. P terdefinisi
	F.S. P dikembalikan ke sistem
	Melakukan dealokasi/pengembalian Address P
*/
{
	free(*T);
}


//----------------------------------------------------------------
boolean IsListEmptyT (ListPetak Board)
/* Mengirim true jika list kosong */
{
	if (FirstT(Board)==Nil)
		return true;
	else
		return false;
}

void InsertFirstT (ListPetak *Board, AddressT T)
/*	I.S. Sembarang, P sudah dialokasi
	F.S. Menambahkan elemen ber-Address P sebagai elemen pertama
*/
{
	NextT(T) = FirstT(*Board);
	FirstT(*Board) = T;
}

void InsertAfterT (ListPetak *Board, AddressT T, AddressT Trec)
/*	I.S. Prec pastilah elemen list dan bukan elemen terakhir,
	P sudah dialokasi
	F.S. Insert P sebagai elemen sesudah elemen beralamat Prec
*/
{
	NextT(T) = NextT (Trec);
	NextT(Trec) = T;
}

void InsertLastT (ListPetak *Board, AddressT T)
/*	I.S. Sembarang, P sudah dialokasi
	F.S. P ditambahkan sebagai elemen terakhir yang baru
*/
{
	/*Kamus Lokal*/
	AddressT Last;

	/*Algoritma*/
	if (IsListEmptyT(*Board)==true)
		InsertFirstT(Board,T);
	else
	{
		Last = FirstT(*Board);
		do
			Last = NextT(Last);
		while ((NextT(Last)!=FirstT(*Board))&&(NextT(Last)!=Nil));
		InsertAfterT(Board,T,Last);
	}
	NextT(T) = FirstT(*Board);

}

//----------------------------------------------------------------------
Petak IsiPetak (char nama[10], int idx,int tipe,int HBeli,int HSewa,int Lv,int Efek, char owner)
{
	/*Kamus*/
	Petak Kota;

	/*Algoritma*/
	strcpy (Kota.namaPetak,nama);
	Kota.idxPetak = idx;
	Kota.tipePetak = tipe;
	Kota.hargaBeliP = HBeli;
	Kota.hargaSewaP = HSewa;
	Kota.hargaJualP = HBeli*0.9;
	Kota.levelPetak = Lv;
	Kota.efekPetak = Efek;
	Kota.pemilik = owner;

return Kota;
}

void MasukkanPetak (ListPetak *Board, char nama[10], int idx,int tipe,int HBeli,int HSewa,int Lv,int Efek, char owner, AddressT *T)
{
	/*Kamus Lokal*/
	Petak X;

	/*Algoritma*/
	X = IsiPetak(nama,idx,tipe,HBeli,HSewa,Lv,Efek,owner);
	*T = AlokasiPetak (X);
	if ((*T)!=Nil)
	{
		InsertLastT(Board,*T);
	}

}

void MakeInitialMap (ListPetak *Board)
/*	I.S. sembarang
	F.S. Terbentuk map kosong */
{
	/*Kamus*/
	AddressT T;

	/*Algoritma*/
	FirstT(*Board) = Nil;

	MasukkanPetak (Board,"Start", 1, PetakStart, HAwal[1],0,0,1,'X',&T);
	FirstT(*Board) = T;
	MasukkanPetak (Board,"Beijing", 2, BlockA, HAwal[2],60,0,1,'X',&T);
	MasukkanPetak (Board,"Bonus", 3, PetakBonus, HAwal[3],0,0,1,'X',&T);
	MasukkanPetak (Board,"Jakarta", 4, BlockA, HAwal[4],50,0,1,'X',&T);
	MasukkanPetak (Board,"Ancol", 5, BlockP, HAwal[5],80,0,1,'X',&T);
	MasukkanPetak (Board,"Taipei", 6, BlockB, HAwal[6],45,0,1,'X',&T);
	MasukkanPetak (Board,"New Delhi", 7, BlockB, HAwal[7],50,0,1,'X',&T);
	MasukkanPetak (Board,"Seoul", 8, BlockB, HAwal[8],50,0,1,'X',&T);
	MasukkanPetak (Board,"Dst Island", 9, PetakDIsland, HAwal[9],0,0,1,'X',&T);
	MasukkanPetak (Board,"Hawaii", 10, BlockP, HAwal[10],100,0,1,'X',&T);
	MasukkanPetak (Board,"Tokyo", 11, BlockC, HAwal[11],100,0,1,'X',&T);
	MasukkanPetak (Board,"Sydney", 12, BlockC, HAwal[12],100,0,1,'X',&T);
	MasukkanPetak (Board,"Chance", 13, PetakChance, HAwal[13],0,0,1,'X',&T);
	MasukkanPetak (Board,"Singapura", 14, BlockD, HAwal[14],50,0,1,'X',&T);
	MasukkanPetak (Board,"Senggigi", 15, BlockD, HAwal[15],80,0,1,'X',&T);
	MasukkanPetak (Board,"Sao Paolo", 16, BlockD, HAwal[16],100,0,1,'X',&T);
	MasukkanPetak (Board,"World Cup", 17, PetakWorldCup, HAwal[17],0,0,1,'X',&T);
	MasukkanPetak (Board,"Denmark", 18, BlockE, HAwal[18],100,0,1,'X',&T);
	MasukkanPetak (Board,"Bintan", 19, BlockP, HAwal[19],75,0,1,'X',&T);
	MasukkanPetak (Board,"Berlin", 20, BlockE, HAwal[20],110,0,1,'X',&T);
	MasukkanPetak (Board,"Chance", 21, PetakChance, HAwal[21],0,0,1,'X',&T);
	MasukkanPetak (Board,"Geneva", 22, BlockF, HAwal[22],75,0,1,'X',&T);
	MasukkanPetak (Board,"Moscow", 23, BlockF, HAwal[23],75,0,1,'X',&T);
	MasukkanPetak (Board,"Rome", 24, BlockF, HAwal[24],100,0,1,'X',&T);
	MasukkanPetak (Board,"Wrld Trvl", 25, PetakWorldTravel, HAwal[25],0,0,1,'X',&T);
	MasukkanPetak (Board,"Kuta", 26, BlockP, HAwal[26],100,0,1,'X',&T);
	MasukkanPetak (Board,"London", 27, BlockG, HAwal[27],105,0,1,'X',&T);
	MasukkanPetak (Board,"Paris", 28, BlockG, HAwal[28],75,0,1,'X',&T);
	MasukkanPetak (Board,"Chance", 29, PetakChance, HAwal[29],0,0,1,'X',&T);
	MasukkanPetak (Board,"New York", 30, BlockH, HAwal[30],150,0,1,'X',&T);
	MasukkanPetak (Board,"Tax", 31, PetakTax, HAwal[31],0,0,1,'X',&T);
	MasukkanPetak (Board,"Bangkok", 32, BlockH, HAwal[32],100,0,1,'X',&T);

}

void ShowBoard(ListPetak Board, ListPemain Player)
{
	/*Kamus*/
	AddressT T, PT[4+1];
	AddressP P;
	int i,j, npemain;
	int CityCost[32+1];
	char CityOwner[32+1];
	char Player1[32+1];
	char Player2[32+1];
	char Player3[32+1];
	char Player4[32+1];

	/*Algoritma*/
	T = FirstT(Board);
	P = FirstP(Player);
	i=1;
	npemain = 1;
	do
	{
		if (StatPlyr(P)==false)
		{
			PT[i] = PetakPlyr(P);
			npemain = npemain +1;
		}

		P = NextP(P);
		i = i+1;
	} while (P != FirstP(Player));



	i=1;
	T = FirstT(Board);

	do
	{

		CityCost[i] = HBeliPtk(T);

		if (PemilikPtk(T)=='X')
			CityOwner[i] = '-';
		else
			CityOwner[i] = PemilikPtk(T);

		Player1[i] = ' ';
		Player2[i] = ' ';
		Player3[i] = ' ';
		Player4[i] = ' ';
		for (j=1;j<=npemain;j++)
		{
			if (PT[j]==T)
			{
				if (j==1)
					Player1[i] = 'A';
				if (j==2)
					Player2[i] = 'B';
				if (j==3)
					Player3[i] = 'C';
				if (j==4)
					Player4[i] = 'D';
			}
		}

		i=i+1;
		T = NextT(T);
	} while (T!=FirstT(Board));

	/* GAMBAR BOARD */

	printf("\n");
	printf("______________________________________________________________________________________________________________________________\n");
	printf("|    Start    |   Beijing   |    Bonus    |   Jakarta   |    Ancol    |   Taipei    |  New Delhi  |    Seoul    |  Dst Island |\n");
	printf("|             | %5d       |             | %5d       | %5d       | %5d       | %5d       | %5d       |             |\n",CityCost[2],CityCost[4],CityCost[5],CityCost[6],CityCost[7],CityCost[8]);
	printf("|             |      %c      |             |      %c      |      %c      |      %c      |      %c      |      %c      |             |\n",CityOwner[2],CityOwner[4],CityOwner[5],CityOwner[6],CityOwner[7],CityOwner[8]);
	printf("|  %c  %c  %c  %c |  %c  %c  %c  %c |  %c  %c  %c  %c |  %c  %c  %c  %c |  %c  %c  %c  %c |  %c  %c  %c  %c |  %c  %c  %c  %c |  %c  %c  %c  %c |  %c  %c  %c  %c |\n",
		Player1[1],Player2[1],Player3[1],Player4[1],Player1[2],Player2[2],Player3[2],Player4[2],Player1[3],Player2[3],Player3[3],Player4[3],
		Player1[4],Player2[4],Player3[4],Player4[4],Player1[5],Player2[5],Player3[5],Player4[5],Player1[6],Player2[6],Player3[6],Player4[6],
		Player1[7],Player2[7],Player3[7],Player4[7],Player1[8],Player2[8],Player3[8],Player4[8],Player1[9],Player2[9],Player3[9],Player4[9]);
	printf("|_____________|_____________|_____________|_____________|_____________|_____________|_____________|_____________|_____________|\n");
	printf("|   Bangkok   |                                                                                                 |    Hawai    |\n");
	printf("| %5d       |                                                                                                 | %5d       |\n",CityCost[32],CityCost[10]);
	printf("|      %c      |                                                                                                 |     %c       |\n",CityOwner[32],CityOwner[10]);
	printf("|  %c  %c  %c  %c |                                                                                                 |  %c  %c  %c  %c |\n",Player1[32],Player2[32],Player3[32],Player4[32],Player1[10],Player2[10],Player3[10],Player4[10]);
	printf("|_____________|                                                                                                 |_____________|\n");
	printf("|     Tax     |                                                                                                 |    Tokyo    |\n");
	printf("|             |                                                                                                 | %5d       |\n",CityCost[11]);
	printf("|             |                                                                                                 |     %c       |\n",CityOwner[11]);
	printf("|  %c  %c  %c  %c |                                                                                                 |  %c  %c  %c  %c |\n",Player1[31],Player2[31],Player3[31],Player4[31],Player1[11],Player2[11],Player3[11],Player4[11]);
	printf("|_____________|                                                                                                 |_____________|\n");
	printf("|  New York   |                                                                                                 |    Sydney   |\n");
	printf("| %5d       |                                                                                                 | %5d       |\n",CityCost[30],CityCost[12]);
	printf("|      %c      |                                                                                                 |     %c       |\n",CityOwner[30],CityOwner[12]);
	printf("|  %c  %c  %c  %c |                                                                                                 |  %c  %c  %c  %c |\n",Player1[30],Player2[30],Player3[30],Player4[30],Player1[12],Player2[12],Player3[12],Player4[12]);
	printf("|_____________|                                                                                                 |_____________|\n");
	printf("|    Chance   |                                                                                                 |    Chance   |\n");
	printf("|             |                                                                                                 |             |\n");
	printf("|             |                                                                                                 |             |\n");
	printf("|  %c  %c  %c  %c |                                                                                                 |  %c  %c  %c  %c |\n",Player1[29],Player2[29],Player3[29],Player4[29],Player1[13],Player2[13],Player3[13],Player4[13]);
	printf("|_____________|                                                                                                 |_____________|\n");
	printf("|    Paris    |                                                                                                 |  Singapura  |\n");
	printf("| %5d       |                                                                                                 | %5d       |\n",CityCost[28], CityCost[14]);
	printf("|      %c      |                                                                                                 |     %c       |\n",CityOwner[28], CityOwner[14]);
	printf("|  %c  %c  %c  %c |                                                                                                 |  %c  %c  %c  %c |\n",Player1[28],Player2[28],Player3[28],Player4[28],Player1[14],Player2[14],Player3[14],Player4[14]);
	printf("|_____________|                                                                                                 |_____________|\n");
	printf("|   London    |                                                                                                 |   Senggigi  |\n");
	printf("| %5d       |                                                                                                 | %5d       |\n",CityCost[27],CityCost[15]);
	printf("|      %c      |                                                                                                 |     %c       |\n",CityOwner[27],CityOwner[15]);
	printf("|  %c  %c  %c  %c |                                                                                                 |  %c  %c  %c  %c |\n",Player1[27],Player2[27],Player3[27],Player4[27],Player1[15],Player2[15],Player3[15],Player4[15]);
	printf("|_____________|                                                                                                 |_____________|\n");
	printf("|    Kuta     |                                                                                                 |  Sao Paolo  |\n");
	printf("| %5d       |                                                                                                 | %5d       |\n",CityCost[26],CityCost[16]);
	printf("|      %c      |                                                                                                 |     %c       |\n",CityOwner[26],CityOwner[16]);
	printf("|  %c  %c  %c  %c |                                                                                                 |  %c  %c  %c  %c |\n",Player1[26],Player2[26],Player3[26],Player4[26],Player1[16],Player2[16],Player3[16],Player4[16]);
	printf("|_____________|_________________________________________________________________________________________________|_____________|\n");
	printf("| Wrld Travel |    Rome     |   Moscow    |   Geneva    |   Chance    |   Berlin    |    Bintan   |   Denmark   |  World Cup  |\n");
	printf("|             | %5d       | %5d       | %5d       |             | %5d       | %5d       | %5d       |             |\n",CityCost[24],CityCost[23],CityCost[22],CityCost[20],CityCost[19],CityCost[18]);
	printf("|             |      %c      |      %c      |      %c      |             |      %c      |      %c      |      %c      |             |\n",CityOwner[24],CityOwner[23],CityOwner[22],CityOwner[20],CityOwner[19],CityOwner[18]);
	printf("|  %c  %c  %c  %c |  %c  %c  %c  %c |  %c  %c  %c  %c |  %c  %c  %c  %c |  %c  %c  %c  %c |  %c  %c  %c  %c |  %c  %c  %c  %c |  %c  %c  %c  %c |  %c  %c  %c  %c |\n",
		Player1[25],Player2[25],Player3[25],Player4[25],Player1[24],Player2[24],Player3[24],Player4[24],Player1[23],Player2[23],Player3[23],Player4[23],
		Player1[22],Player2[22],Player3[22],Player4[22],Player1[21],Player2[21],Player3[21],Player4[21],Player1[20],Player2[20],Player3[20],Player4[20],
		Player1[19],Player2[19],Player3[19],Player4[19],Player1[18],Player2[18],Player3[18],Player4[18],Player1[17],Player2[17],Player3[17],Player4[17]);
	printf("|_____________|_____________|_____________|_____________|_____________|_____________|_____________|_____________|_____________|\n");

}

/*Subprogram Perhitungan & Update Board*/

void HitungHarga (AddressT T, int *HargaBeliPaksa, int *HargaJual, int *HargaUpgrade, int *HargaSewa)
{
    /*Kamus*/
    int i;

    /*Algortima*/
    i = IdxPtk(T);

    *HargaJual = HAwal[i]*(LvPtk(T)+1);

    *HargaBeliPaksa = (*HargaJual)*2;

    *HargaUpgrade = HAwal[i]*(LvPtk(T)+1);

    *HargaSewa = (*HargaJual)*0.1*EfekPtk(T);
}

void UpdateHargaPetak (ListPetak Board)
{
    /*Kamus*/
    AddressT T;
    int BeliPaksa, Jual, Upgrade,Sewa;

    /*Algoritma*/
    T = FirstT(Board);
    do
    {
        HitungHarga(T,&BeliPaksa,&Jual,&Upgrade,&Sewa);
        HSewaPtk(T) = Sewa;
        HJualPtk(T) = Jual;

        T = NextT(T);

    } while (T!=FirstT(Board));
}
