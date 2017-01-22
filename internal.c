/* Nama/ NIM		: Kelompok Tubes 1-7
 * Nama file		: Internal.c
 * Topik		    : Monopoly, Let's Get Wealthy
 * Tanggal		    : 23 November 2015
 * Deskripsi		: phase 3, ADT berhubung dengan mekanisme umum permainan
*/
#include "HeaderGame.h"


void RollDice(AddressP P, AddressT *T, ListPetak Board, ListPemain Player, boolean *ulang)
/*Melempar Dadu -- sekaligus double roll

	input command :
	>roll dice
*/

{
	/*Kamus*/
	int r,s,t,n,i;
    boolean LewatWC;
    boolean LewatS;


	/*Algoritma*/
    *ulang = false;

	*T = PetakPlyr(P);
	n=1;
    LewatS = false;
    LewatWC = false;
	srand(time(NULL));
	r = rand() % 6 + 1;
	s = rand() % 6 + 1;
    t = r+s;
    printf("  Dadu : %d + %d = %d\n\n",r,s,t);

	for (i=1;i<=t;i++)
    {
		*T = NextT(*T);
        if (IdxPtk(*T)==1)
            LewatS = true;
        if (IdxPtk(*T)==17)
            LewatWC = true;
    }
    if (LewatS == true)
    {
        UangPlyr(P) = UangPlyr(P) + 200;
        printf("  Anda melewati Start, uang Anda bertambah 200K\n");
        printf("  Uang Anda sekarang : "); WriteMoney(UangPlyr(P));
        printf("\n");
        CekOff (P,Board);
    }

    if (LewatWC == true)
    {
        CekHost (P, Board);
    }

	PetakPlyr(P) = *T;
    IdxPlyr(P) = IdxPtk(*T);
    printf("  Anda sekarang berada di %s\n", NamaPtk(*T));
    if (NamaPlyr(P)==PemilikPtk(*T))
        printf("  %s merupakan petak Anda sendiri, silahkan upgrade tile atau end turn.\n", NamaPtk(*T));
        printf("  WARNING!! Kota Pariwisata tidak dapat di-upgrade.\n\n");

	n=n+1;

    if (r==s)
    {
        printf("  Anda mendapatkan dadu double!\n");
        printf("  Anda dapat memutar dadu kembali setelah end turn\n");
        printf("\n\n");
        *ulang = true;
    }

}


void SeePrice(ListPetak Board, Name Kota)
/*Melihat harga jual petak:
	Biaya Sewa, Biaya Ambil Alih, Biaya Upgrade Bangunan

	Prekondisi : sudah dimiliki oleh pemain (siapapun)

	input command :
	>info <nama petak>

	Board adalah list petak, Kota adalah nama petak yang dimaksud
*/
{
    /*Kamus*/
    AddressT T;
    int BeliPaksa, Jual, Upgrade, Sewa;

    /*Algoritma*/
    BeliPaksa = 0;
    Jual = 0;
    Upgrade = 0;
    Sewa = 0;
    SearchKota(Kota,Board,&T);

    if (T!=Nil)
    {
        if (PemilikPtk(T)!='X')
        {
            HitungHarga (T, &BeliPaksa, &Jual, &Upgrade, &Sewa);
            printf("  Biaya sewa = "); WriteMoney (Sewa);
            printf("\n");
            printf("  Biaya ambil alih = "); WriteMoney (BeliPaksa);
            printf("\n");
            printf("  Biaya upgrade = "); WriteMoney (Upgrade);
            printf("\n\n");

        }
        else
        {
            printf("  Petak ini belum dimiliki siapapun\n\n");
        }
    }
    else
    {
        printf("  Kota salah, silahkan diperiksa kembali!\n\n");
    }
}

void ShowLeaderBoard(ListPetak Board, ListPemain Player, int nplayer)
/*menampilkan peringkat pemain
    berdasarkan uang dan nilai jual asset

    input command :
     leaderboard
*/
{
    /*Kamus*/
    AddressP P;
    int Assest[nplayer + 1];
    char idpemain[nplayer + 1];
    int temp, i, j;
    char tempi;

    /*Algoritma*/
    P = FirstP(Player);
    i = 1;
    do
    {
        Assest[i] = HitungAset(Board, P)+UangPlyr(P);
        idpemain[i] = NamaPlyr(P);
        P = NextP(P);
        i++;
    } while (P != FirstP(Player));

    for (i = 1; i <= nplayer; i++)
    {
        for (j = 1; j <= (nplayer - i); j++)
        {
            if (Assest[j] < Assest[j + 1])
            {
                temp = Assest[j];
                tempi = idpemain[j];
                Assest[j] = Assest[j + 1];
                idpemain[j] = idpemain[j + 1];
                Assest[j + 1] = temp;
                idpemain[j + 1] = tempi;
            }
        }
    }

    printf("---------------------------------------------------------------------------\n\n");
    printf("                             LEADERBOARD\n\n");
    printf("---------------------------------------------------------------------------\n\n");
    for (i = 1; i <= nplayer; i++)
    {
        tempi = idpemain[i];
        printf ("            Ke-%d : Player %c dengan aset ", i, tempi);
        temp = Assest[i];
        WriteMoney(temp); printf("\n");
    }
    printf("\n");
}

void GetChance(AddressP P, ListPetak Board, ListPemain Player)
/*mengambil kartu kesempatan, kartu yang didapat random
	WARNING : otomatis saat prekondisi terpenuhi
	Prekondisi : berada di petak 'chance'

	A adalah address pemain yang sedang aktif dan pada gilirannya
*/
{
/*Kamus Lokal*/
    int chance, i;
    AddressT T;
    AddressP P2;
    char namaKota[11];
    boolean berhasil;

/*Algoritma*/
    chance = (rand() % 5) + 1;
    switch (chance){
        case 1 : printf("  Anda mendapatkan kartu bebas dari penjara. Simpan kartu ini untuk penggunaan selanjutnya.\n");
                 printf("\n");
                break;
        case 2 : printf("  Anda mendapatkan kartu bebas pajak. Simpan kartu ini untuk penggunaan selanjutnya.\n");
                 printf("\n");
                break;
        case 3 : printf("  Anda mendapatkan kartu masuk penjara. Silakan masuk penjara.\n");
                strcpy(namaKota,"Dst Island");
                SearchKota(namaKota, Board, &T);
                PetakPlyr(P) = T;
                IsPenjara(P) = true;
                freeme (P,Player);
                printf("\n");
                break;
        case 4 :
                printf("  Anda mendapatkan kartu mati lampu. Tulis nama kota yang akan diserang.\n\n");
                berhasil = true;

                T = FirstT(Board);
                do {
                        if (PemilikPtk(T)!='X' && PemilikPtk(T)!= NamaPlyr(P))
                            berhasil = false;
                        else
                            T = NextT(T);
                } while (T!= FirstT(Board) && berhasil);

                if (berhasil)
                    printf("  Tidak ada kota yang dapat diserang!\n\n");

                while (!berhasil)
                {
                    printf("> ");
                    gets(namaKota);
                    SearchKota(namaKota, Board,&T);

                    if (T != Nil && PemilikPtk(T) != 'X' && PemilikPtk(T) != NamaPlyr(P))
                    {
                        EfekPtk(T) = 0;
                        P2 = SearchPlayerName (PemilikPtk(T),Player);
                        UseProtect (P2,T);
                        printf("  Selamat! Anda berhasil menyerang kota!\n");
                        berhasil = true;
                    }
                    else if (T!=Nil && (PemilikPtk(T) == 'X' || PemilikPtk(T) == NamaPlyr(P)))
                    {
                        if (PemilikPtk(T)=='X')
                            printf("  Kota tersebut belum dimiliki.\n");
                        if (PemilikPtk(T)==NamaPlyr(P))
                            printf("  Kota ini milik Anda!\n");
                    }
                    else
                        printf("  Nama kota tidak valid! Silahkan diperiksa kembali!\n");
                    printf("\n");
                }
                break;
        case 5 : printf("  Anda mendapatkan kartu perlindungan. Simpan kartu ini untuk penggunaan selanjutnya.\n");
                 printf("\n");
                break;
    }
    if ((chance != 3) && (chance != 4))
    {
        i = 1;
        if (KartuPlyr(P).NbElInt == 0)
        {
            KartuPlyr(P).TI[i] = chance;
        }
        else
        {
            while (KartuPlyr(P).TI[i] != ValUndefInt)
            {
                i++;
            }
            KartuPlyr(P).TI[i] = chance;
        }
        KartuPlyr(P).NbElInt = KartuPlyr(P).NbElInt + 1;
    }
}

void PayTax(ListPetak Board, AddressP A)
/*membayar pajak
	WARNING : otomatis saat prekondisi terpenuhi
	Prekondisi : berada di petak 'tax'

	A adalah address pemain yang sedang aktif dan pada gilirannya
*/
{
/*Kamus Lokal*/
    int tax, aset;

/*Algoritma*/
    aset = HitungAset(Board, A);
    tax = (aset * 0.1);
    if (UangPlyr(A) < tax)
    {
        printf("  Uang Anda tidak cukup untuk membayar pajak! Sayang sekali, Anda bangkrut!\n\n");
        StatPlyr(A) = true;
    }
    else
    {
        UangPlyr(A) = UangPlyr(A) - tax;
        printf("  Pajak Bumi dan Bangunan, uang Anda berkurang ");
        WriteMoney(tax); printf("\n");
        printf("  Sisa uang Anda : ");
        WriteMoney(UangPlyr(A)); printf("\n\n");
    }
}

void GetBonus(AddressP A)
/*mendapat uang bonus, uang yang didapat random
	WARNING : otomatis saat prekondisi terpenuhi
	Prekondisi : berada di petak 'bonus'

	A adalah address pemain yang sedang aktif dan pada gilirannya
*/
{
/*Kamus Lokal*/
    int bonus;

/*Algoritma*/
     bonus = ((rand() % (500 + 1 - 100))  + 100);
     printf("  Selamat, Anda mendapatkan ");
     WriteMoney(bonus);
     printf("!\n");
     printf("  Uang Anda sekarang ");
     UangPlyr(A) = UangPlyr(A) + bonus;
     WriteMoney(UangPlyr(A));
     printf("\n\n");
}


void WorldCupTime(ListPetak *Board, ListPemain L, AddressP P)
/*memilih tile untuk world cup mengganti efek petak yang dipilih
    WARNING : Efek world cup akan berhenti ketika pemain tersebut melewati petak world cup
    Prekondisi : Berada di petak 'World Cup'

    input command :
     host <nama kota>
*/
{
    char host[5];
    char kota[10];
    int i;
    AddressT T;
    boolean input = false;

    if (PropPlyr(P).TI[1] != ValUndefInt)
    {
        printf("  Anda dapat menjadikan kota-kota di bawah ini sebagai host World Cup :\n");
        printf("  ");
        for (i = 1; i < PropPlyr(P).NbElInt; i++)
        {
            printf("%s, ", NamaPtk(SearchKotaId(PropPlyr(P).TI[i],*Board)));
        }
        printf("%s\n\n",NamaPtk(SearchKotaId(PropPlyr(P).TI[PropPlyr(P).NbElInt],*Board)));

        do
        {
            printf("> ");
            scanf("%s",&host);
            getchar();
            gets(kota);
            if (strcmp(host,"host")==0)
            {
                SearchKota(kota,*Board,&T);
                if(T!=Nil)
                {
                    if (PemilikPtk(T) == NamaPlyr(P))
                    {
                        EfekPtk(T)  = EfekPtk(T)*2;
                        input = true;
                    }
                    else
                        printf("  Kota tersebut bukan milik Anda, silahkan pilih kota yang lain.\n\n");
                }
                else
                {
                    printf("  Nama kota tidak ditemukan, silahkan pilih kota lain.\n\n");
                }
            }
            else
            {
                printf("  Instruksi salah! Silakhkan coba lagi.\n\n");
                input = false;
            }
        } while (input==false);
        printf("  Selamat, %s telah menjadi host dari World Cup!\n\n",kota);
    }
    else
    {
        printf("  Anda tidak memiliki aset sama sekali. Tidak bisa memilih host.\n\n");
    }
}

void WorldTravelTime(ListPetak Board, AddressP A, ListPemain Player)
/*memilih tile yang dituju, pemain bergerak maju menuju petak itu
	Prekondisi : Berada di petak 'World Travel'

	input command :
	>travel <nama kota>
*/
{
    char travel[10];
    char kota[10];
    boolean input = false;
    AddressT T;

    ShowBoard(Board,Player);
    do
    {
        printf("> ");
        scanf("%s",travel);
        getchar();
        gets(kota);
        if (strcmp(travel,"travel")==0)
        {
            SearchKota(kota,Board,&T);
            if(T != Nil)
            {
                PetakPlyr(A) = T;
                printf("  Selamat, Anda berada di %s!\n\n",kota);
                input = true;
            }
            else
                printf("  Kota tersebut tidak ada pada board! Silakhkan coba lagi.\n\n");
        }
        else
            printf("  Input salah! Silakhkan coba lagi.\n Contoh input : travel <nama kota>\n\n");
    } while (input==false);
}


//---------------------------------------------------------------------------------------------------------
/*===============================Fungsi Tambahan===================================*/


/*Fungsi Tamabahan Search*/
void SearchKota(Name kota, ListPetak Board, AddressT *T)
{
    *T =  FirstT(Board);
    boolean found = false;

    do
    {
        if (strcmp(NamaPtk(*T),kota)==0)
        {
            found = true;
        }
        else
        {
            *T = NextT(*T);
        }
    } while (*T != FirstT(Board) && !found);

    if (found==false)
        *T = Nil;
}

AddressT SearchKotaId(int id, ListPetak Board)
{
    /*Kamus*/
    AddressT T;

    /*Algoritma*/
    T = FirstT(Board);
    while ((IdxPtk(T)!=id)&&(NextT(T)!=FirstT(Board)))
        T = NextT(T);

    return T;
}

AddressP SearchPlayerId (int id, ListPemain Player)
{
    /*Kamus*/
    AddressP P;

    /*Algoritma*/
    P = FirstP(Player);
    while ((NoPlyr(P)!=id)&&(NextP(P)!=FirstP(Player)))
        P = NextP(P);

    return P;
}

AddressP SearchPlayerName (char c,ListPemain Player)
{
    /*Kamus*/
    int i;
    AddressP P;

    /*Algoritma*/

    i=1;
    P = FirstP(Player);

    while ((NamaPlyr(P)!=c)&&(i<=4))
    {
        P = NextP(P);
        i = i+1;
    }

    if (NamaPlyr(P)!=c)
        return Nil;
    else
        return P;

}

int HitungAset (ListPetak L, AddressP P)
{
/*Kamus Lokal*/
    int aset, count, i, j;
    AddressT T;

/*Algoritma*/
    T = FirstT(L);
    i = 1; j = 1;
    aset = 0;
    while (PropPlyr(P).TI[i] != ValUndefInt)
    {
        T = FirstT(L);
        count = PropPlyr(P).TI[i];
        while (j < count)
        {
            T = NextT(T);
            j++;
        }
        aset = aset + HJualPtk(T);
        i++;
    }
    return aset;
}

//Kartu chances
boolean SearchKartu (AddressP P, int N)
/*Mencari apakah pemain memiliki kartu chance tertentu dan mengembalikan true atau false*/
{
/*Kamus Lokal*/
    int i;
    boolean found;

/*Algoritma*/
    //Search Kartu
    found = false;
    i = 1;
    while ((found == false) && (i <= KartuPlyr(P).NbElInt))
    {
        if (KartuPlyr(P).TI[i] == N)
        {
            found = true;
        }
        else
        {
            i++;
        }
    }
    return found;
}

void DeleteCard(AddressP P, int N)
/*Menghapus kartu chance yang dimiliki pemain jika dipakai*/
{
/*Kamus Lokal*/
    int i;
    boolean found;

/*Algoritma*/
    //Mencari id kartu
    found = false;
    i = 1;
    while ((found == false) && (i <= KartuPlyr(P).NbElInt))
    {
        if (KartuPlyr(P).TI[i] == N)
        {
            found = true;
        }
        else
        {
            i++;
        }
    }
    //Menghapus Kepemilikan kartu
    while (i <= KartuPlyr(P).NbElInt)
    {
        KartuPlyr(P).TI[i] = KartuPlyr(P).TI[i+1];
        i++;
    }
    KartuPlyr(P).NbElInt = KartuPlyr(P).NbElInt - 1;
}

void freeme (AddressP P, ListPemain Player)
/*Membebaskan player dari penjara ketika dia punya kartu chance free me*/
{
/*Kamus Lokal*/
    char *InputUser;
    boolean found;
    AddressT T;
    char ans;

/*Algoritma*/
    T = PetakPlyr(P);
    printf("  PERINGATAN!\n");
    printf("  Jika hanya ada 1 player yang tidak dipenjara, maka player tersebut dinyatakan menang\n\n");
    if ((SearchKartu (P,1)==true)&&(IdxPtk(T)==9))
    {
        printf("  Anda mempunyai kartu bebas penjara\n");
        printf("  untuk menggunakan ketik 'free me'\n\n");
        printf("> ");
        gets (InputUser);
        if (strcmp(InputUser,"free me")==0)
        {
            DeleteCard(P,1);
            IsPenjara(P) = false;
            printf("Anda bebas dari penjara, silakan mengakhiri giliran\n\n");
        }
        else
        {
            printf("Silakan menikmati waktu Anda dalam penjara\n\n");
        }
    }
    else
    {
        printf("Anda tidak memiliki kartu bebas penjara\n");
        printf("Apakah Anda ingin membayar 100K untuk keluar dari penjara? [Y/N]\n\n");
        do
        {
            printf("> "); scanf(" %c",&ans);
            printf("\n");
            if (ans != 'Y' && ans != 'N')
            {
                printf("Masukan tidak valid\n\n");
            }
        }
        while (ans != 'Y' && ans != 'N');

        if (ans == 'Y')
        {
            if (UangPlyr(P) < 100)
            {
                printf("  Uang Anda tidak cukup untuk keluar dari penjara!\n\n");
            }
            else
            {
                UangPlyr(P) = UangPlyr(P) - 100;
                IsPenjara(P) = false;
                printf("  Anda bebas dari penjara, silakan mengakhiri giliran\n");
                printf("  Uang Player %c sekarang : ",NamaPlyr(P)); WriteMoney(UangPlyr(P)); printf("\n\n");
            }
        }
        else
        {
            printf("  Anda harus dipenjara, giliran Anda habis!\n\n");
            getchar();
        }
    }
}

void freetax (ListPetak Board, AddressP P)
/*Membebaskan pemain dari pajak jika memang punya kartu bebas pajak*/
{
/*Kamus Lokal*/
    char *InputUser;
    AddressT T;

/*Algoritma*/
    T = PetakPlyr(P);
    if ((SearchKartu (P,2)==true)&&(IdxPtk(T)==31))
    {
        printf("  Anda mempunyai kartu bebas pajak\n");
        printf("  untuk menggunakan ketik 'free tax'\n\n");
        printf("> ");
        gets (InputUser);
        if (strcmp(InputUser,"free tax")==0)
        {
            DeleteCard(P,2);
            printf("Anda telah terbebas dari pajak!\n");
        }
        else
        {
            printf("Anda memilih untuk tetap membayar.\n");
            PayTax(Board,P);
        }
    }
    else
    {
        printf("Anda tidak punya kartu bebas pajak...\n");
        printf("  Anda harus membayar pajak\n");
        PayTax(Board,P);
    }
    printf("\n");
}

void UseProtect (AddressP P, AddressT T)
{
    /*Kamus*/
    char *InputUser, *InputUser2;

    /*Algoritma*/
    if (SearchKartu (P,5)==true)
    {
        printf("  Anda dapat menggunakan kartu 'Protect', untuk menggunakan ketik protect <nama tempat>\n");
        printf("> ");
        scanf("%s",InputUser);
        fgets (InputUser2, 15, stdin);
        if ((strcmp(InputUser,"protect")==0)&&(strcmp(InputUser2,NamaPtk(T))==0))
        {
            EfekPtk(T) = 1;
            DeleteCard(P,5);
            printf("Anda berhasil melindungi Kota %s, harga sewa di kota %s kembali normal\n\n",NamaPtk(T),NamaPtk(T));
        }
    }
}

/*Fungsi tambahan untuk mempermudah peroseean main*/
void PrintPerintah ()
{
    printf("\n");
    printf("-------------------------------------------------------------------\n\n");
    printf("                        DAFTAR PERINTAH \n\n");
    printf("-------------------------------------------------------------------\n\n");
    printf(" <> roll dice\n");
    printf(" <> board\n");
    printf(" <> leaderboard\n");
    printf(" <> end turn\n");
    printf(" <> info <nama petak>\n");
    printf(" <> profile\n");
    printf(" <> buy\n");
    printf(" <> upgrade\n");
    printf(" <> sell <nama petak>\n");
    printf(" <> sell bank <nama petak>\n");
    printf(" <> show offered\n");
    printf(" <> buy offered <nama petak>\n");
    printf(" <> free me\n");
    printf(" <> free tax\n");
    printf(" <> off <nama kota/tempat rekreasi>\n");
    printf(" <> protect <nama kota/tempat rekreasi>\n");
    printf(" <> host <nama kota>\n");
    printf(" <> travel <nama kota>\n");
    printf(" <> save <nama file>\n");
    printf(" <> load <nama file>\n\n");

}

boolean IsKota1Kata (char *s)
{
    if ((strcmp(s,"New")==0)||(strcmp(s,"Dst")==0)||(strcmp(s,"Sao")==0)||
            (strcmp(s,"World")==0)||(strcmp(s,"Wrld")==0))
        return false;
    else
        return true;

}


/*Fungsi Tambahan Autoplay di Roll Dice*/
void CekHost (AddressP P, ListPetak Board)
{
	AddressT T;

	T = FirstT(Board);

	do
	{
		if (PemilikPtk(T) == NamaPlyr(P))
		{
			if (EfekPtk(T)==2)
            {
                if (!IsBlok(T,Board))
                    EfekPtk(T) = 1;
            }
            else if (EfekPtk(T)==4)
                EfekPtk(T)=2;
		}
		T = NextT(T);
	} while (T != FirstT(Board));
}

void CekOff (AddressP P, ListPetak Board)
{
	AddressT T;

	T = FirstT(Board);

	do
	{
		if (PemilikPtk(T) == NamaPlyr(P))
		{
			if (EfekPtk(T)==0)
				EfekPtk(T) = 1;
		}
	} while (T != FirstT(Board));
}



void BayarSewa (AddressP P, ListPemain LP, ListPetak Board)
//Player P harus membayar sewa ke pemilik kota T
{
/*Kamus Lokal*/
    AddressT T;
    AddressP Pem;
    boolean found;
    boolean GameOver;
    Name Kota;

/*Algoritma*/
    T = PetakPlyr(P);
    found = false;
    if ((PemilikPtk(T) != 'X') && (PemilikPtk(T) != NamaPlyr(P)))
    {
        if (UangPlyr(P) >= HSewaPtk(T))
        {
            UangPlyr(P) = UangPlyr(P) - HSewaPtk(T);
            Pem = FirstP(LP);
            while ((NextP(Pem) != FirstP(LP)) && (!(found)))
            {
                if (NamaPlyr(Pem) == PemilikPtk(T))
                {
                    found = true;
                }
                else
                {
                    Pem = NextP(Pem);
                }
            }
            UangPlyr(Pem) = UangPlyr(Pem) + HSewaPtk(T);
            printf("  Anda berada di petak milik %c \n",PemilikPtk(T));
            printf("  Anda harus membayar : "); WriteMoney(HSewaPtk(T)); printf("\n");
            printf("  Uang Anda sekarang "); WriteMoney(UangPlyr(P)); printf("\n\n");
        }
        else
        {
            printf("  Anda berada di petak milik %c \n",PemilikPtk(T));
            printf("  Uang Anda tidak cukup untuk membayar sewa sebanyak : ");
            WriteMoney(HSewaPtk(T));
            printf("\n\n");

            if ((UangPlyr(P)+HitungAset(Board,P))<HSewaPtk(T))
            {
                printf("  Aset Anda tidak cukup untuk membayar sewa!\n\n");
                printf("  Sayang sekali, Anda bangkrut!\n\n");
                StatPlyr(P) = true;
				SellAll (Board,P);
                EndTurn(LP,&P);
            }
            else
            {
                printf("  Anda dapat menjual aset\n");
                while (UangPlyr(P)<HSewaPtk(T))
                {
					ShowKepemilikan(Board, P);
					printf("  Tulis nama kota yang ingin Anda jual\n");
					gets(Kota);
					SellTile(Board,Kota,LP,P);
                }
	            UangPlyr(P) = UangPlyr(P) - HSewaPtk(T);
            }
        }
    }
    else if (PemilikPtk(T) == NamaPlyr(P))
    {
    	printf("  Anda berada di petak Anda sendiri!\n\n");
    }
}
AddressT SearchTipe (int tipe, ListPetak Board)
{
    /*Kamus Lokal*/
    AddressT T;
    boolean found;

    /*Algoritma*/
    found = false;
    T = FirstT(Board);
    do {
        if (TipePtk(T)==tipe)
            found = true;
        else
            T = NextT(T);
    } while (T != FirstT(Board) && !found);

    return T;
}

boolean IsTripleMonopoly (AddressP P, ListPetak Board)
{
    /* Kamus Lokal */
    int counter, i;

    /* Algoritma */
    i = 1; counter = 0;

    for (i= 101; i<=108; i++)
    {
        if ((IsBlok(SearchTipe(i,Board),Board)) && (PemilikPtk(SearchTipe(i,Board)) == NamaPlyr(P)))
            counter++;
    }

    if (counter < 3)
    {
        return false;
    }
    else
    {
        return true;
    }
}

boolean IsGameOver(ListPemain Player, AddressP P, ListPetak Board)
{
    /*Kamus*/
    AddressP Q;
    boolean GameOver;

    /*Algoritma*/

    GameOver = false;
    Q = P;
    do
    {
        Q = NextP(Q);
    }
    while (((StatPlyr(Q)==true)||(IsPenjara(Q)==true))&&(Q!=P));

    if (Q == P)
    {
        printf("  Hanya ada satu pemain yang tidak dipenjara.\n\n");
        GameOver =  true;
    }

    if ((IsKepemilikan(PropPlyr(P),5)==true)&&(IsKepemilikan(PropPlyr(P),10)==true)&&(IsKepemilikan(PropPlyr(P),19)==true)&&(IsKepemilikan(PropPlyr(P),26)==true))
    {
        printf("  Player %c telah memenangkan permainan dengan Tourism Monopoly!\n\n", NamaPlyr(P));
		GameOver = true;
    }

    if (IsTripleMonopoly(P,Board))
    {
        printf("  Player %c telah memenangkan permainan dengan Triple Monoply!\n\n", NamaPlyr(P));
        GameOver = true;
    }

	return GameOver;

}

boolean BisaBeli (AddressT T)
{
    if (TipePtk(T)>=202 && TipePtk(T)<=208)
        return false;
    else
        return true;
}

void ShowKepemilikan(ListPetak Board, AddressP P)
{
	/*Kamus*/
	int i;
	AddressT T;

	/*Algoritma*/
	i=1;
	printf("  Uang Player %c = ",NamaPlyr(P));
	WriteMoney(UangPlyr(P)); printf("\n");

	for (i=1; i<=PropPlyr(P).NbElInt; i++)
    {
        T = SearchKotaId(PropPlyr(P).TI[i],Board);
        printf("  %s\n",NamaPtk(T));
        SeePrice(Board, NamaPtk(T));
    }
    printf("\n");
}


boolean IsKepemilikan(TabInt Tab, int ID)
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
    if (Tab.TI[i]==ID)
	    return true;
	else
		return false;
}

boolean IsBlok (AddressT T, ListPetak Board)
{
    if (TipePtk(T) == 101)
    {
        if (PemilikPtk(SearchKotaId(2,Board))==PemilikPtk(SearchKotaId(4,Board)) && PemilikPtk(SearchKotaId(2,Board)) != 'X')
            return true;
        else
            return false;
    }
    else if (TipePtk(T) == 102)
    {
        if (PemilikPtk(SearchKotaId(6,Board))==PemilikPtk(SearchKotaId(7,Board))==PemilikPtk(SearchKotaId(8,Board)) && PemilikPtk(SearchKotaId(6,Board)) != 'X')
            return true;
        else
            return false;
    }
    else if (TipePtk(T) == 103)
    {
        if (PemilikPtk(SearchKotaId(11,Board))==PemilikPtk(SearchKotaId(12,Board)) && PemilikPtk(SearchKotaId(12,Board)) != 'X')
            return true;
        else
            return false;
    }
    else if (TipePtk(T) == 104)
    {
        if (PemilikPtk(SearchKotaId(14,Board))==PemilikPtk(SearchKotaId(15,Board))==PemilikPtk(SearchKotaId(16,Board)) && PemilikPtk(SearchKotaId(16,Board)) != 'X')
            return true;
        else
            return false;
    }
    else if (TipePtk(T) == 105)
    {
        if (PemilikPtk(SearchKotaId(18,Board))==PemilikPtk(SearchKotaId(20,Board)) && PemilikPtk(SearchKotaId(18,Board)) != 'X')
            return true;
        else
            return false;
    }
    else if (TipePtk(T) == 106)
    {
        if (PemilikPtk(SearchKotaId(23,Board))==PemilikPtk(SearchKotaId(24,Board)) && PemilikPtk(SearchKotaId(23,Board)) != 'X')
            return true;
        else
            return false;
    }
    else if (TipePtk(T) == 107)
    {
        if (PemilikPtk(SearchKotaId(27,Board))==PemilikPtk(SearchKotaId(28,Board)) && PemilikPtk(SearchKotaId(27,Board)) != 'X')
            return true;
        else
            return false;
    }
    else if (TipePtk(T) == 108)
    {
        if (PemilikPtk(SearchKotaId(30,Board))==PemilikPtk(SearchKotaId(32,Board)) && PemilikPtk(SearchKotaId(30,Board)) != 'X')
            return true;
        else
            return false;
    }
    else
        return false;
}

void CekBlock (AddressT T, ListPetak Board)
{
    /* Algoritma */
    if (IsBlok(T,Board))
    {
        if (TipePtk(T) == 101)
        {
            EfekPtk(SearchKotaId(2,Board)) = 2;
            EfekPtk(SearchKotaId(4,Board)) = 2;
        }
        else if (TipePtk(T) == 102)
        {
            EfekPtk(SearchKotaId(6,Board)) = 2;
            EfekPtk(SearchKotaId(7,Board)) = 2;
            EfekPtk(SearchKotaId(8,Board)) = 2;
        }
        else if (TipePtk(T) == 103)
        {
            EfekPtk(SearchKotaId(11,Board)) = 2;
            EfekPtk(SearchKotaId(12,Board)) = 2;
        }
        else if (TipePtk(T) == 104)
        {
            EfekPtk(SearchKotaId(14,Board)) = 2;
            EfekPtk(SearchKotaId(15,Board)) = 2;
            EfekPtk(SearchKotaId(16,Board)) = 2;
        }
        else if (TipePtk(T) == 105)
        {
            EfekPtk(SearchKotaId(18,Board)) = 2;
            EfekPtk(SearchKotaId(20,Board)) = 2;
        }
        else if (TipePtk(T) == 106)
        {
            EfekPtk(SearchKotaId(23,Board)) = 2;
            EfekPtk(SearchKotaId(24,Board)) = 2;
        }
        else if (TipePtk(T) == 107)
        {
            EfekPtk(SearchKotaId(27,Board)) = 2;
            EfekPtk(SearchKotaId(28,Board)) = 2;
        }
        else if (TipePtk(T) == 108)
        {
            EfekPtk(SearchKotaId(30,Board)) = 2;
            EfekPtk(SearchKotaId(32,Board)) = 2;
        }
    }

}
