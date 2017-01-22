/* Nama/ NIM		: Kelompok Tubes 1-7
 * Nama file		: HeaderPemain.h
 * Topik		    : Monopoly, Let's Get Wealthy
 * Tanggal		    : 23 November 2015
 * Deskripsi		: phase 3, header array

*/
#ifndef ARRAY_H
#define ARRAY_H

/* Indeks untuk array integer */
#define IdxMinInt 1
#define IdxMaxInt 30

/* Indeks untuk string nama kota */
#define IdxMinChar 1
#define IdxMaxChar 10

#define IdxUndef -999 //Indeks tak terdefinisi
#define ValUndefInt -9999 //Value tak terdefinisi untuk tipe elemen integer
#define ValUndefChar '?' //Value tak terdefinisi untuk tipe elemen char

typedef struct
{
    int TI[IdxMaxInt+1];
    int NbElInt;
} TabInt; //Array integer

typedef char Name[IdxMaxChar+1]; //Nama kota

#endif
