#include "HeaderGame.h"
#include "array.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void SaveFile(ListPetak Board, ListPemain Player, TabInt Off, char nf[10])
/*menyimpan game ke file eksternal sehingga dapat dilanjutkan

    input command :
    >save <nama file>
*/
{
    /* Kamus Lokal */
    FILE *fc, *fk, *fo, *fp, *fb, *fj;
    AddressP A;
    AddressT B;
    char yha[5], letak[2], nmfl[10], jml;
    int i, j;

    /* Algoritma */
    /* Jumlah Pemain */
    A = FirstP(Player); i = 0;
    do
    {
        i++;
        A = NextP(A);
    } while (A != FirstP(Player));
    jml = IntegerToChar(i);
    strcpy(nmfl, nf);
    strcat(nmfl, "_jmlpemain.txt");
    fj = fopen(nmfl, "w");
    fputc(jml, fj);
    fclose(fj);

    /* Kota yang di-offer */
    strcpy(nmfl, nf);
    strcat(nmfl, "_offer.txt");
    fo = fopen(nmfl, "w");
    i = 1; j = 1;
    while (i <= Off.NbElInt)
    {
        if (Off.TI[j] != ValUndefInt)
        {
            sprintf(yha,"%d",Off.TI[j]);
            fputs(yha, fo);
            fputs(" | ", fo);
            i++;
        }
        j++;
    }
    fclose(fo);


    /* Player */
    strcpy(nmfl, nf);
    strcat(nmfl, "_player.txt");
    fp = fopen(nmfl, "w");
    A = FirstP(Player);
    if (A != Nil)
    {
        do
        {
            fputc(NamaPlyr(A), fp);
            fputs(" | ", fp);
            sprintf(yha,"%d",NoPlyr(A));
            fputs(yha, fp);
            fputs(" | ", fp);
            sprintf(yha,"%d",UangPlyr(A));
            fputs(yha, fp);
            fputs(" | ", fp);
            fputc(IntegerToChar(GiliranPlyr(A)), fp);
            fputs(" | ", fp);
            fputc(IntegerToChar(StatPlyr(A)), fp);
            fputs(" | ", fp);
            fputc(IntegerToChar(IsPenjara(A)), fp);
            fputs(" | ", fp);
            sprintf(letak,"%d",IdxPlyr(A));
            fputs(letak, fp);

            fputc('\n', fp);
            A = NextP(A);
        } while (A != FirstP(Player));
    }
    fclose(fp);


    /* Kartu Chance Player */
    strcpy(nmfl, nf);
    strcat(nmfl, "_chance.txt");
    fc = fopen(nmfl, "w");
    A = FirstP(Player);
    if (A != Nil)
    {
        do
        {
            i = 1; j = 1;
            fputc(NamaPlyr(A), fc);
            fputs(" | ", fc);
            while (i <= KartuPlyr(A).NbElInt)
            {
                if (KartuPlyr(A).TI[j] != ValUndefInt)
                {
                    sprintf(yha,"%d",KartuPlyr(A).TI[j]);
                    fputs(yha, fc);
                    if (i < KartuPlyr(A).NbElInt)
                    {
                        fputs(" | ", fc);
                    }
                    i++;
                }
                j++;
            }
            fputc('\n', fc);
            A = NextP(A);
        } while (A != FirstP(Player));
    }
    fclose(fc);


    /* Kepemilikan Player */
    strcpy(nmfl, nf);
    strcat(nmfl, "_kepemilikan.txt");
    fk = fopen(nmfl, "w");
    A = FirstP(Player);
    if (A != Nil)
    {
        do
        {
            fputc(NamaPlyr(A), fk);
            fputs(" | ", fk);
            for (i = IdxMinInt; i <= PropPlyr(A).NbElInt; i++)
            {
                sprintf(yha,"%d",PropPlyr(A).TI[i]);
                fputs(yha, fk);
                fputs(" | ", fk);
            }
            fputc('\n', fk);
            A = NextP(A);
        } while (A != FirstP(Player));
    }
    fclose(fk);


    /* Board */
    strcpy(nmfl, nf);
    strcat(nmfl, "_board.txt");
    fb = fopen(nmfl, "w");
    B = FirstT(Board);
    if (B != Nil)
    {
        do
        {
            sprintf(yha,"%d",IdxPtk(B));
            fputs(yha, fb);
            fputs(" | ", fb);
            sprintf(yha,"%d",TipePtk(B));
            fputs(yha, fb);
            fputs(" | ", fb);
            sprintf(yha,"%d",HBeliPtk(B));
            fputs(yha, fb);
            fputs(" | ", fb);
            sprintf(yha,"%d",HSewaPtk(B));
            fputs(yha, fb);
            fputs(" | ", fb);
            sprintf(yha,"%d",HJualPtk(B));
            fputs(yha, fb);
            fputs(" | ", fb);
            fputc(IntegerToChar(LvPtk(B)), fb);
            fputs(" | ", fb);
            fputc(IntegerToChar(EfekPtk(B)), fb);
            fputs(" | ", fb);
            fputc(PemilikPtk(B), fb);

            fputc('\n', fb);
            B = NextT(B);
        } while (B != FirstT(Board));
    }
    fclose(fb);

    printf("  Proses selesai.\n\n");
}

void LoadFile(ListPetak *Board, ListPemain *Player, TabInt *Off, char nf[10], boolean *loading)
/*memulai permainan dari save file

    input command :
    >load <nama file>
*/
{
    /* Kamus Lokal */
    FILE *fc, *fk, *fo, *fp, *fb, *fj;
    AddressP A;
    AddressT B;
    int c;
    int conv, jmlhpemain;
    char uang[7], yha[5], letak[2], /*namkot[10],*/ nmfl[10], LagiMain;
    int i, j, k, l, counter, total;

    /* Algoritma */
    /* Load jumlah pemain */
    strcpy(nmfl, nf);
    strcat(nmfl, "_jmlpemain.txt");
    fj = fopen(nmfl, "r");
    if (fj)
    {
        *loading = true;
        while ((c = fgetc(fj)) != EOF)
        {
            jmlhpemain = c - '0';
        }
    }
    else
    {
        printf("  Ada kesalahan dalam loading jumlah pemain.\n\n");
        *loading = false;
    }
    fclose(fj);
    AddPlayer(Player, *Board, jmlhpemain);

    /* Kota yang di-offer */
    strcpy(nmfl, nf);
    strcat(nmfl, "_offer.txt");
    fo = fopen(nmfl, "r");
    if (fo)
    {
        i = 0;
        j = 0;
        while ((c = fgetc(fo)) != EOF)
        {
            if ((c != ' ') && (c != '|') && (c != '\0') && (c != '\n'))
            {
                yha[j] = c;
                j++;
            }
            else if (c == '|')
            {
                total = 0;
                for (k = 0; k < j; k++)
                {
                    if (k > 0)
                    {
                        total = total * 10;
                    }
                    total = total + (yha[k] - '0');
                }
                i++;
                (*Off).TI[i] = total;
                j = 0;
            }
        }
        (*Off).NbElInt = i;
    }
    else
    {
        printf("  Ada kesalahan dalam loading daftar kota yang di-offer.\n\n");
    }
    fclose(fo);

    /* Player */
    strcpy(nmfl, nf);
    strcat(nmfl, "_player.txt");
    fp = fopen(nmfl, "r");
    if (fp)
    {
        A = FirstP(*Player);
        counter = 1;
        j = 0; l = 0;
        while (((c = fgetc(fp)) != EOF) && (A != Nil))
        {
            if ((c != ' ') && (c != '\0') && (c != '\n') && (c != '|'))
            {
                switch (counter)
                {
                    case 1:
                        NamaPlyr(A) = c;
                        break;
                    case 2:
                        conv = c - '0';
                        GiliranPlyr(A) = conv;
                        break;
                    case 3:
                        uang[j] = c;
                        //printf("uang %c[%d]: %c\n", NamaPlyr(A), j, uang[j]);
                        j++;
                        break;
                    case 4:
                        conv = c - '0';
                        GiliranPlyr(A) = conv;
                        if (conv == 1)
                        {
                            LagiMain = NamaPlyr(A);
                        }
                        break;
                    case 5:
                        conv = c - '0';
                        StatPlyr(A) = conv;
                        break;
                    case 6:
                        conv = c - '0';
                        IsPenjara(A) = conv;
                        break;
                    case 7:
                        letak[l] = c;
                        //printf("letak %c[%d]: %c\n", NamaPlyr(A), l, letak[l]);
                        l++;
                        break;
                }
            }
            else if (c == '|')
            {
                if (counter == 3)
                {
                    total = 0;
                    for (k = 0; k < j; k++)
                    {
                        if (k > 0)
                        {
                            total = total * 10;
                        }
                        //printf("tesuang[%d] : %c\n", k, uang[k]);
                        total = total + (uang[k] - '0');
                        //printf("totaluang%d: %d\n", k, total);
                    }
                    UangPlyr(A) = total;
                    j = 0;
                }
                counter++;
            }
            else if (c == '\n')
            {
                total = 0;
                for (k = 0; k < l; k++)
                {
                    if (k > 0)
                    {
                        total = total * 10;
                    }
                    //printf("tesletak[%d] : %c\n", k, letak[k]);
                    total = total + (letak[k] - '0');
                    //printf("totalletak%d: %d\n", k, total);
                }
                IdxPlyr(A) = total;
                l = 0;
                counter = 1;
                A = NextP(A);
            }
        }
    }
    else
    {
        printf("  Ada kesalahan dalam loading data pemain.\n\n");
    }
    fclose(fp);
    /*A = FirstP(*Player);
    do
    {
        printf("%c\n", NamaPlyr(A));
        printf("%d\n", NoPlyr(A));
        printf("%d\n", UangPlyr(A));
        printf("%d\n", GiliranPlyr(A));
        printf("%d\n", StatPlyr(A));
        printf("%d\n", IsPenjara(A));
        printf("%d\n", IdxPlyr(A));
        A = NextP(A);
    } while (A != FirstP(*Player));*/

    /* Kepemilikan Player */
    strcpy(nmfl, nf);
    strcat(nmfl, "_kepemilikan.txt");
    fk = fopen(nmfl, "r");
    if (fk)
    {
        A = FirstP(*Player);
        i = 0; j = 0;
        while (((c = fgetc(fk)) != EOF) && (A != Nil))
        {
            if ((c != ' ') && (c != '|') && (c != '\0') && (c != '\n') && ((c < 'A') || (c > 'z')))
            {
                letak[j] = c;
                j++;
            }
            else if (c == '|')
            {
                if (j > 0)
                {
                    total = 0;
                    for (k = 0; k < j; k++)
                    {
                        if (k > 0)
                        {
                            total = total * 10;
                        }
                        total = total + (letak[k] - '0');
                    }
                    i++;
                    PropPlyr(A).TI[i] = total;
                }
                j = 0;
            }
            else if (c == '\n')
            {
                if (i > 0)
                {
                    PropPlyr(A).NbElInt = i;
                }
                A = NextP(A);
                i = 0;
            }
        }
    }
    else
    {
        printf("  Ada kesalahan dalam loading kepemilikan pemain.\n\n");
    }
    fclose(fk);

    /* Kartu Chance Player */
    strcpy(nmfl, nf);
    strcat(nmfl, "_chance.txt");
    fc = fopen(nmfl, "r");
    if (fc)
    {
        A = FirstP(*Player);
        i = 0; counter = 0;
        while (((c = fgetc(fc)) != EOF) && (A != Nil))
        {
            if ((c != ' ') && (c != '|') && (c != '\0') && (c != '\n') && ((c < 'A') || (c > 'z')))
            {
                conv = c - '0';
                KartuPlyr(A).TI[i] = conv;
                counter++;
            }
            else if (c == '|')
            {
                i++;
                //printf("i : %d\n", i);
            }
            else if (c == '\n')
            {
                if (counter > 0)
                {
                    KartuPlyr(A).NbElInt = i;
                    //printf("NbElChance : %d\n", i);
                }
                A = NextP(A);
                i = 0;
            }
        }
    }
    else
    {
        printf("  Ada kesalahan dalam loading kartu chance pemain.\n\n");
    }
    fclose(fc);
    /*A = FirstP(*Player);
    do
    {
        if (KartuPlyr(A).NbElInt > 0)
        {
            for (i = 1; i <= KartuPlyr(A).NbElInt; i++)
            {
                printf("chance%c[%d] : %d\n", NamaPlyr(A), i, KartuPlyr(A).TI[i]);
            }
        }
        A = NextP(A);
    } while (A != FirstP(*Player));*/


    /* Board */
    strcpy(nmfl, nf);
    strcat(nmfl, "_board.txt");
    fb = fopen(nmfl, "r");
    if (fb)
    {
        B = FirstT(*Board);
        counter = 2;
        j = IdxMinChar; l = 0;
        while (((c = fgetc(fb)) != EOF) && (B != Nil))
        {
            if ((c != ' ') && (c != '|') && (c != '\0') && (c != '\n'))
            {
                switch (counter)
                {
                    /*case 1:
                        if (c == '_')
                        {
                            c = ' ';
                        }
                        NamaPtk(B)[j] = c;
                        j++;
                        break;*/
                    case 2: //indeks petak
                    case 3: //jenis petak
                    case 4: //harga beli
                    case 5: //harga sewa
                    case 6: //harga jual
                        yha[l] = c;
                        l++;
                        break;
                    case 7: //level petak
                        conv = c - '0';
                        LvPtk(B) = conv;
                        break;
                    case 8: //efek petak
                        conv = c - '0';
                        EfekPtk(B) = conv;
                        break;
                    case 9:
                        PemilikPtk(B) = c;
                        break;
                }
            }
            else if (c == '|')
            {
                /*if (counter == 1)
                {
                    j = IdxMinChar;
                }
                else */if ((counter >= 2) && (counter <= 6))
                {
                    total = 0;
                    for (k = 0; k < l; k++)
                    {
                        if (k > 0)
                        {
                            total = total * 10;
                        }
                        total = total + (yha[k] - '0');
                    }
                    if (counter == 2)
                        IdxPtk(B) = total;
                    else if (counter == 3)
                        TipePtk(B) = total;
                    else if (counter == 4)
                        HBeliPtk(B) = total;
                    else if (counter == 5)
                        HSewaPtk(B) = total;
                    else
                        HJualPtk(B) = total;
                    l = 0;
                }
                counter++;
            }
            else if (c == '\n')
            {
                counter = 2;
                B = NextT(B);
            }
        }
    }
    else
    {
        printf("  Ada kesalahan dalam loading board\n\n");
    }
    fclose(fb);
    /*B = FirstT(*Board);
    do
    {
        printf("%d\n", IdxPtk(B));
        printf("%d\n", TipePtk(B));
        printf("%d\n", HBeliPtk(B));
        printf("%d\n", HSewaPtk(B));
        printf("%d\n", HJualPtk(B));
        printf("%d\n", LvPtk(B));
        printf("%d\n", EfekPtk(B));
        printf("%c\n", PemilikPtk(B));
        B = NextT(B);
    } while (B != FirstT(*Board));*/


    printf("  Proses selesai.\n\n");
    if (*loading)
        printf("  Sekarang giliran Player %c.\n\n", LagiMain);
}

char IntegerToChar (int X)
/* Mengubah satu digit integer menjadi char */
{
    /* Algoritma */
    if (X == 0)
    {
        return '0';
    }
    else if (X == 1)
    {
        return '1';
    }
    else if (X == 2)
    {
        return '2';
    }
    else if (X == 3)
    {
        return '3';
    }
    else if (X == 4)
    {
        return '4';
    }
    else if (X == 5)
    {
        return '5';
    }
    else if (X == 6)
    {
        return '1';
    }
    else if (X == 7)
    {
        return '7';
    }
    else if (X == 8)
    {
        return '8';
    }
    else if (X == 9)
    {
        return '9';
    }
}

