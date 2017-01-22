/* Nama/ NIM        : Kelompok Tubes 1-7
 * Nama file        : buy.c
 * Topik            : Monopoly, Let's Get Wealthy
 * Tanggal          : 23 November 2015
 * Deskripsi        : phase 3, ADT berhubung pembelian
*/

#include "HeaderGame.h"
#include "HeaderPemain.h"
#include "HeaderPetak.h"


void BuyTile(int X, AddressP A)
/*Fungsi dasar membeli Petak, mengubah status petak yang dibeli*/
{
    /* Kamus Lokal */
    AddressT T;
    int i=1;

    /* Algoritma */
    T = PetakPlyr(A);
    UangPlyr(A) = UangPlyr(A) - X;
    PemilikPtk(T) = NamaPlyr(A);

    while (PropPlyr(A).TI[i] != ValUndefInt)
        i++;

    PropPlyr(A).TI[i] = IdxPtk(T);
    PropPlyr(A).NbElInt++;
}

void NormalBuyTile(AddressP A)
/*membeli petak yang ditempati sekarang
    Prekondisi : tidak dimiliki pemain lain

    input command :
    >buy
*/
{
    /* Kamus Lokal */
    AddressT T;

    /* Algoritma */
    T = PetakPlyr(A);
    if (BisaBeli(T))
    {
        if (HBeliPtk(T) > UangPlyr(A))
        {
            printf("  Uang Anda tidak cukup untuk membeli kota ini!\n\n");
        }
        else
        {
            /* Memindahkan kepemilikan kota */
            BuyTile(HBeliPtk(T), A);
            printf("  Selamat, kota %s kini menjadi milik Anda!\n", NamaPtk(T));
            printf("  Level bangunan %d\n", LvPtk(T));
            printf("  Sisa uang Anda : ");
            WriteMoney(UangPlyr(A));
            printf("\n\n");
        }
    }
    else
    {
        printf("  Anda tidak bisa membeli petak ini.\n\n");
    }
}

void ForceBuyTile(ListPemain Player, AddressP A)
/*membeli petak yang ditempati sekarang
    Prekondisi : petak dimiliki pemain lain

    input command :
    >buy
*/
{
    /* Kamus Lokal */
    AddressT T;
    AddressP A1;
    char PemAwal;
    int Price, IdxHapus;
    boolean found;
    int a,b,c;

    /* Algoritma */
    T = PetakPlyr(A);
    PemAwal = PemilikPtk(T);
    HitungHarga (T,&Price,&a,&b,&c);
    if (Price > UangPlyr(A))
    {
        printf("  Uang Anda tidak cukup untuk membeli kota ini!\n\n");
    }
    else if ((BisaBeli(T)==true)&&(TipePtk(T)!=BlockP) && (LvPtk(T)<5))
    {
        /* Mencari address pemilik awal kota */
        A1 = FirstP(Player);
        found = false;
        do
        {
            if (NamaPlyr(A1) == PemAwal)
            {
                found = true;
            }
            else
            {
                A1 = NextP(A1);
            }
        } while ((A1 != FirstP(Player)) && (!found));

        /* Menghapus kepemilikan kota dari pemilik awal */
        IdxHapus = SearchIdx(PropPlyr(A1), IdxPtk(T));
        PropPlyr(A1).TI[IdxHapus] = ValUndefInt;
        PropPlyr(A1).NbElInt = PropPlyr(A1).NbElInt-1;
        UangPlyr(A1) = UangPlyr(A1) + Price;

        /* Memindahkan kepemilikan kota */
        BuyTile(Price, A);
        printf("  Selamat, kota %s kini menjadi milik Anda!\n", NamaPtk(T));
        printf("  Level bangunan %d\n", LvPtk(T));
        printf("  Sisa uang Anda : ");
        WriteMoney(UangPlyr(A));
        printf("\n\n");
        printf("  Player %c mendapat hasil penjualan sebesar %dK\n\n", PemAwal, Price);
    }
    else if (TipePtk(T)==BlockP)
    {
        printf("  Anda tidak dapat membeli paksa kota pariwisata\n\n");
    }

    if (LvPtk(T)==5)
        printf("  Anda tidak dapat membeli kota yang telah memiliki Landmark!\n\n");
}

void OfferedBuyTile(ListPetak *Board, ListPemain Player, AddressP A, TabInt *Off, Name Kota)

/*membeli petak yang dijual ditawarkan dalam list "offered"
    Prekondisi : petak sudah di-offered

    input command :
    >buy offered <nama petak>
*/
{
    /* Kamus Lokal */
    AddressT T;
    AddressP A1;
    char PemAwal;
    int IdxKosong, IdxHapus, i;
    boolean found;

    /* Algoritma */
    SearchKota(Kota,*Board,&T);
    if (T!=Nil)
    {
        PemAwal = PemilikPtk(T);
        if (HJualPtk(T) > UangPlyr(A))
        {
            printf("  Uang Anda tidak cukup untuk membeli kota ini!\n\n");
        }
        else
        {
            /* Mencari address pemilik awal kota */
            A1 = SearchPlayerName (PemAwal,Player);
            if (A1 != Nil)
            {
                /* Menghapus kepemilikan kota dari pemilik awal */
                IdxHapus = SearchIdx(PropPlyr(A1), IdxPtk(T));
                while (PropPlyr(A1).TI[IdxHapus] != ValUndefInt)
                {
                    PropPlyr(A1).TI[IdxHapus] = PropPlyr(A1).TI[IdxHapus+1];
                    IdxHapus = IdxHapus + 1;
                }
                PropPlyr(A1).NbElInt = PropPlyr(A1).NbElInt - 1;


                /* Menghapus kota dari array offer */
                IdxHapus = SearchIdx(*Off, IdxPtk(T));
                while ((*Off).TI[IdxHapus+1] != ValUndefInt)
                {
                    (*Off).TI[IdxHapus] = (*Off).TI[IdxHapus+1];
                    IdxHapus = IdxHapus +1;
                }
                (*Off).NbElInt = (*Off).NbElInt - 1;

                /* Memindahkan kepemilikan kota */
                UangPlyr(A) = UangPlyr(A) - HJualPtk(T);
                PemilikPtk(T) = NamaPlyr(A);

                i=1;
                while (PropPlyr(A).TI[i] != ValUndefInt)
                    i++;

                PropPlyr(A).TI[i] = IdxPtk(T);
                PropPlyr(A).NbElInt++;

                printf("  %s menjadi milik Anda!\n", NamaPtk(T));
                printf("  Sisa uang Anda : ");
                WriteMoney(UangPlyr(A));
                printf("\n\n");
            }
            else
            {
                printf("  Kota yang Anda pilih tidak valid! Silakan diperiksa kembali.\n\n");
            }
        }
    }
    else
    {
        printf("  Input nama kota salah\n\n");
    }
}


//----------------------------------------------------------------------------------------------------------------
int GetEmptyIdx(TabInt Tab)
/* Menghasilkan indeks yang pertama kali ditemukan yang elemennya kosong */
{
    /* Kamus Lokal */
    int i;
    /* Algoritma */
    i = 1;
    while ((i <= IdxMaxInt) && (Tab.TI[i] != ValUndefInt))
    {
        i++;
    }
    return i;
}

int SearchIdx(TabInt Tab, int ID)
/* Menghasikan indeks yang nilai elemennya sama dengan ID. Array P dijamin unik */
{
    /* Kamus Lokal */
    int i;
    /* Algoritma */
    i = 1;
    while ((i <= IdxMaxInt) && (Tab.TI[i] != ID))
    {
        i++;
    }
    return i;
}

void WriteMoney (int M)
{
    /* Kamus Lokal */
    int Tulis, Tulis1;
    /* Algoritma */
    if (M % 1000 == 0)
    {
        Tulis = M / 1000;
        printf("%dM", Tulis);
    }
    else
    {
        if (M > 1000)
        {
            Tulis = M / 1000;
            Tulis1 = M % 1000;
            printf("%dM %dK", Tulis, Tulis1);
        }
        else
        {
            printf("%dK", M);
        }
    }
}
