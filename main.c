/* Nama/ NIM        : Kelompok Tubes 1-7
 * Nama file        : main.c
 * Topik            : Monopoly, Let's Get Wealthy
 * Tanggal          : 6 November 2015
 * Deskripsi        : phase 3, program utama
*/

#include "HeaderGame.h"


	/*Kamus*/
	ListPetak Board;
	ListPemain Player;
	AddressP P;
	AddressT T;
	boolean ulang, justbuy, GameOver, akhirulang, loads;
	char InUser[15],InUser2[15], c;
	TabInt Off;
	int nplayer, countulang, i, choice;


void AutoPlayBoard ()
{
    if (IdxPtk(T)==31) /*index 31 = Tax*/
    {
        freetax (Board, P); /*Jika ada kartu bebas Tax, bisa pakai, jika tidak wajib bayar*/
    }

    else if ((IdxPtk(T)==13)||(IdxPtk(T)==21)||(IdxPtk(T)==29)) /*Index 13,21,29 = Chance*/
    {
        GetChance(P,Board,Player);
    }

    else if (IdxPtk(T)==9) /*Index 9 = deserted Island*/
    {
        IsPenjara(P) = true;
    }

    else if (IdxPtk(T)==3) /*Index 3 = bonus*/
    {
		GetBonus(P);
    }
    else if (TipePtk(PetakPlyr(P))==207)
    {
		WorldCupTime(&Board,Player,P);
		UpdateHargaPetak (Board);
    }
	else if (TipePtk(PetakPlyr(P))==208)
	{
		WorldTravelTime(Board,P, Player);
		T = PetakPlyr(P);
		AutoPlayBoard();
	}
	else
	{
		BayarSewa (P,Player,Board);
	}
}


void Pengulangan ()
{
	/*Kamus Lokal*/
	AddressP Q;

	/*Algoritma*/

	printf("Masukkan perintah : \n");
	countulang = 1;
	do
	{
		GameOver = IsGameOver(Player,P, Board);
		if (GameOver == false)
		{
			justbuy = false;
			printf("> ");
			gets(InUser);
			printf("\n");
			if (strcmp(InUser,"roll dice")!=0)
			{
				printf("  Anda harus Roll Dice terlebih dahulu!\n\n");
			}
			else
			{
				akhirulang = false;
			    if (IsPenjara(P)==false)
	                RollDice(P,&T,Board,Player,&ulang);
	            else
	            {
	                printf("  Anda tidak bisa roll dice. Silahkan bayar atau end turn!\n\n");
	            }
				Q = P;

				printf("\n");
				justbuy = false;
				AutoPlayBoard();
				while ((GiliranPlyr(Q)==true)&&(IsPenjara(Q)==false)&&(akhirulang==false))
				{

					printf("> ");
					scanf("%s",InUser);
                    printf("\n");
	/*============================================Buy & Buy offered=====================================================*/
					if (strcmp(InUser,"buy") == 0)
					{
						scanf("%s",InUser);
						if (strcmp(InUser,"offered")==0)
						{
							getchar();
							gets (InUser);
							OfferedBuyTile(&Board,Player,P,&Off, InUser);
							GameOver = IsGameOver(Player,P, Board);
							if (GameOver==true)
								akhirulang = true;
						}
						else
						{
							if (IsKota1Kata (InUser)==false)
							{
								gets(InUser2);
								strcat(InUser,InUser2);
							}
							if (PemilikPtk(T)=='X')
							{
								if (strcmp(InUser,NamaPtk(T))==0)
								{
                                    NormalBuyTile(P);
                                    justbuy = true;
									GameOver = IsGameOver(Player,P, Board);
									if (GameOver==true)
										akhirulang = true;

								}
								else
								{
									printf("  Anda hanya dapat membeli kota tempat Anda berada!\n\n");
								}
							}
							else if (PemilikPtk(T) != NamaPlyr(P))
							{
								if (strcmp(InUser,NamaPtk(T))==0)
								{
									printf("  Petak ini dimiliki oleh %c, Anda ingin membelinya? (Y/N) ",PemilikPtk(T));
									scanf(" %c",&c); printf("\n\n");
									if (c=='Y')
									{
										ForceBuyTile(Player,P);
										justbuy = true;
									}
									else
									{
										printf("  Anda tidak jadi membelinya!\n\n");
									}
								}
								else if (TipePtk(T)==BlockP)
                                {
                                    printf("> Anda tidak dapat membeli paksa kota pariwisata!\n\n");
                                }
                                else
								{
									printf("> Anda hanya dapat membeli kota tempat Anda berada\n\n");
								}
							}
							else
							{
							    printf("  Kota ini telah menjadi milik Anda!\n\n");
							}
						}
					}

	/*================================================Sell & Offer====================================================*/

					else if (strcmp(InUser,"sell")==0)
					{
						scanf("%s",InUser);
						if (strcmp(InUser,"bank")==0)
						{
							getchar();
							gets (InUser);
							SellTile(Board,InUser,Player,P);
						}
						else
						{
							if (IsKota1Kata (InUser)==false)
							{
								scanf("%s",InUser2);
								strcat(InUser," ");
								strcat(InUser,InUser2);
							}
							OfferTile(&Board,P,Player,InUser,&Off);
						}
					}
					else if (strcmp(InUser,"show")==0)
					{
						getchar();
						gets(InUser);
						if (strcmp(InUser,"offered")==0)
						{
							ShowOffered(Off,Board);
						}
						else
						{
							printf("  Masukkan tidak valid\n\n");
						}
					}

	/*===============================Show Board, LeaderBoard, Info Harga Petak==========================================*/
					else if (strcmp(InUser,"board")==0)
					{
						ShowBoard(Board,Player);
					}
					else if (strcmp(InUser,"upgrade")==0)
					{
					    if (justbuy == false)
	                    {
	                       UpgradeTile(P);
	                       justbuy = true;
	                    }
	                    else
	                    {
	                        printf("  Anda tidak bisa mengupgrade ketika baru selesai membeli tile atau mengupgrade tile 2 kali!\n\n");
	                    }
					}
					else if (strcmp(InUser,"leaderboard")==0)
					{
						ShowLeaderBoard(Board,Player,nplayer);
					}
					else if ((strcmp(InUser,"info")==0))
					{
						getchar();
						gets(InUser);
						SeePrice(Board,InUser);
					}
	/*============================================End Turn, Save=========================================================*/
					else if (strcmp(InUser,"end")==0)
					{
						getchar();
						gets(InUser);
						if (strcmp(InUser,"turn")==0)
						{
							if (ulang == true)
							{
								if (countulang<3)
								{
									akhirulang = true;
									printf("  Player %c, Anda dapat roll dice lagi\n\n", NamaPlyr(P));
									countulang = countulang + 1;
								}
								else
								{
									printf("  Anda tidak bisa Roll Dice lebih dari 3 kali!\n\n");
								}
							}
							else
							{
								countulang = 1;
								EndTurn(Player,&P);
							}
							CekBlock(T,Board);
							UpdateHargaPetak (Board);
						}
						else
						{
							printf("  Masukan salah!\n\n");
						}
					}
					else if (strcmp(InUser,"save")==0)
					{
						getchar();
						gets(InUser);
						SaveFile(Board, Player, Off, InUser);
					}
	/*============================================Pesan Kesalahan====================================================*/
					else if (strcmp(InUser,"profile")==0)
					{
						ShowKepemilikan(Board,P);
					}
					else
					{
						printf("  Command salah\n\n");
					}
	/*------------------------------------------Test------------------------------------*/
				}
				if (IsPenjara(P)==true)
				{
					freeme(P, Player);
					if (IsPenjara(P)==true)
					{
						printf("  Player %c dipenjara!\n\n", NamaPlyr(P));
						EndTurn(Player,&P);
					}
					else
					{
						getchar();
						EndTurn(Player,&P);
					}
				}
				printf("\n");
			}
		}
	} while (GameOver == false);
    printf("---------------------------------------------------------------\n\n");
    printf("                          THE END\n\n");
    printf("---------------------------------------------------------------\n\n");
	printf("   Permainan berakhir! Selamat! Pemenangnya adalah Player %c\n\n", NamaPlyr(P));
	printf("          Terima Kasih telah memainkan Get Wealthy!\n\n");

}




int main ()
{

	GameOver = false;
	MakeInitialMap (&Board);

	/*PERLU INISIALISASI SEMUA ARRAY OFFERED*/
	InisialisasiArrayInt (&Off);

    printf("-------------------------------------------------------------------------------------------------------------------------\n");
    printf("-------------------------------------------------------------------------------------------------------------------------\n");
    printf("-------------------------------------------------------------------------------------------------------------------------\n\n\n");
    printf("                                                      GET WEALTHY\n\n\n");
    printf("-------------------------------------------------------------------------------------------------------------------------\n");
    printf("-------------------------------------------------------------------------------------------------------------------------\n");
    printf("-------------------------------------------------------------------------------------------------------------------------\n\n\n");
	printf("                                Selamat datang di game GET WEALTHY Kelompok 7 <3<3<3\n\n\n");

	/*Inisialisasi Kartu & Kepemilikan ada di pemain masing-masing*/
    do
    {
        printf("Pilih permainan :\n");
        printf("1. Memulai permainan baru\n");
        printf("2. Melanjutkan permainan yang sudah ada\n\n");
        printf("Pilihan Anda (1/2) : "); scanf("%d",&choice);
        if ((choice != 1)&&(choice !=2))
        {
            printf("\n");
            printf("Pilihan salah, ulangi!\n\n");
        }
    } while (choice!=1 && choice!=2);

    if (choice==1)
    {
        getchar();
        printf("\n");
        printf("Tentukan jumlah pemain (2-4)\n");
        do
        {
            printf("> ");
            scanf("%d",&nplayer);
            if (nplayer<2 || nplayer>4)
            {
                printf("Silahkan masukkan jumlah pemain yang valid (2-4 pemain)\n\n");
            }
        } while (nplayer<2 || nplayer>4);
        gets(InUser);
        AddPlayer (&Player, Board, nplayer);

        /*Menampilkan board awal*/
        ShowBoard(Board,Player);
        PrintPerintah();
        printf("Sekarang giliran Player A!\n\n");
        P = FirstP(Player);
        Pengulangan();
    }
    else
    {
        getchar();
        do
        {
            printf("Ketik load <nama file>\n");
            scanf("%s", InUser);
            if (strcmp(InUser,"load")==0)
            {
                getchar();
                gets(InUser2);
                LoadFile(&Board, &Player, &Off, InUser2, &loads);
                if (loads)
                {
                    AutoSyncPemain(Player,Board);
                    P = FirstP(Player);
                    while (GiliranPlyr(P)==false)
                        P = NextP(P);
                }
                else
                {
                    printf("File tidak ada atau bermasalah.\n\n");
                }
            }
            else
            {
                gets(InUser2);
                printf("Perintah salah!\n\n");
            }
        } while (!loads || (strcmp(InUser,"load")!=0));
        PrintPerintah();
        Pengulangan();
    }


return 0;
}
