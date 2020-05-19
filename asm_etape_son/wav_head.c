/* -------------------- WAV specific stuff --------------------------- */

/* wav est un cas de fichier RIFF.
 * le fichier RIFF commence par "RIFF" (4 caracteres) suivi de la longueur
 * du reste du fichier en long (4 bytes ordre Intel)
 * puis on trouve "WAVE" suivi de chucks.
 * chaque chuck commence par 4 caracteres (minuscules) suivis de la longueur
 * du reste du chuck en long (4 bytes ordre Intel)
 * le chuck "fmt " contient les parametres, sa longueur n'est pas tres fixe,
 * il peut y avoir un chuck "fact" contenant le nombre de samples
 * le chuck "data" contient les samples,
 * tout autre doit etre ignore.

 header mini :
 RIFF      4  ]
 filesize  4  ] == 12 bytes de pre-header
 WAVE      4  ]
 fmt       4     le chuck fmt coute  au moins 24 bytes en tout
 chucksize 4     == 16 bytes utile
 type      2  ]
 chan      2  ]
 freq      4  ] == 16 bytes
 bps       4  ]
 block     2  ]
 resol     2  ]
 data      4
 chucksize 4    == 8 bytes de post-header
 --------------
          44 au total
 real filesize = chucksize + 44
 RIFF filesize = chucksize + 36

 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>

#include "wav_head.h"


unsigned long readlong( unsigned char *buf )
{
unsigned long l;
l  = (unsigned long)buf[3] << 24 ;
l += (unsigned long)buf[2] << 16 ;
l += (unsigned long)buf[1] << 8 ;
l += buf[0];
return(l);
}
unsigned int readshort( unsigned char *buf )
{
unsigned int s;
s = buf[0] + ( buf[1] << 8 );
return(s);
}

void WAVreadHeader( wavpars *s, int hand )
{
unsigned char buf[256]; unsigned long filesize, chucksize, factsize;
read( hand, buf, 4 );
if ( strncmp( (char *)buf, "RIFF", 4 ) != 0 ) gasp("manque en-tete RIFF");
read( hand, buf, 4 ); filesize = readlong( buf );
read( hand, buf, 4 );
if ( strncmp( (char *)buf, "WAVE", 4 ) != 0 ) gasp("manque en-tete WAVE");

read( hand, buf, 4 );
if ( strncmp( (char *)buf, "fmt ", 4 ) != 0 ) gasp("manque chuck fmt");
read( hand, buf, 4 ); chucksize = readlong( buf );
if ( chucksize > (long)256 ) gasp("chuck fmt trop gros");
read( hand, buf, (int)chucksize );
if ( readshort(buf) != 1 ) gasp("fichier wave non PCM");
s->chan = readshort( buf + 2 );
s->freq = readlong( buf + 4 );
s->bpsec = readlong( buf + 8 );
s->block = readshort( buf + 12 );
s->resol = readshort( buf + 14 );
s->wavsize = 0L;
factsize = 0L;

read( hand, buf, 4 );
if   ( strncmp( (char *)buf, "fact", 4 ) == 0 )
     {
     read( hand, buf, 4 ); chucksize = readlong( buf );
     if ( chucksize > (long)256 ) gasp("chuck fmt trop gros");
     read( hand, buf, (int)chucksize );
     factsize = readlong( buf );
     read( hand, buf, 4 );
     }
if   ( strncmp( (char *)buf, "data", 4 ) != 0 ) gasp("pas de chuck data");
read( hand, buf, 4 ); chucksize = readlong( buf );

s->wavsize = chucksize / ( s->chan * ((s->resol)>>3) );

printf("%d canaux, %lu Hz, %lu bytes/s, %d bits\n",
       s->chan, s->freq, s->bpsec, s->resol );
printf("%lu echantillons selon data chuck\n", s->wavsize );
if ( factsize != 0L )
   {
   printf("%lu echantillons selon fact chuck\n", factsize );
   if ( s->wavsize != factsize )
      gasp("longueurs incoherentes");
   }
printf("fichier %lu bytes, chuck data %lu bytes\n",
           filesize, chucksize );
  {
  double durs, dmn, ds; int mn;
  durs = s->wavsize;  durs /= s->freq;
  dmn = durs / 60.0;  mn = (int)dmn; ds = durs - 60.0 * mn;
  printf("duree %.3f s soit %d mn %.3f s\n", durs, mn, ds );
  }
}

void writelong( unsigned char *buf, unsigned long l )
{
buf[0] = (unsigned char)l; l >>= 8;
buf[1] = (unsigned char)l; l >>= 8;
buf[2] = (unsigned char)l; l >>= 8;
buf[3] = (unsigned char)l;
}
void writeshort( unsigned char *buf, unsigned int s )
{
buf[0] = (unsigned char)s; s >>= 8;
buf[1] = (unsigned char)s;
}
void gulp()
{ gasp("erreur ecriture fichier");
}

void WAVwriteHeader( wavpars *d, int hand )
{
unsigned char buf[16]; long filesize, chucksize;

d->bpsec = d->freq * d->chan * ((d->resol)>>3);
d->block = d->chan * ((d->resol)>>3);
chucksize = d->wavsize * d->chan * ((d->resol)>>3);
filesize = chucksize + 36;

if ( write( hand, "RIFF", 4 ) != 4 ) gulp();
writelong( buf, filesize );
if ( write( hand, buf, 4 ) != 4 ) gulp();

if ( write( hand, "WAVE", 4 ) != 4 ) gulp();
if ( write( hand, "fmt ", 4 ) != 4 ) gulp();
writelong( buf, 16L );
if ( write( hand, buf, 4 ) != 4 ) gulp();

writeshort( buf,      1        ); /* PCM type id */
writeshort( buf + 2,  d->chan  );
writelong(  buf + 4,  d->freq  );
writelong(  buf + 8,  d->bpsec );
writeshort( buf + 12, d->block );
writeshort( buf + 14, d->resol );
if ( write( hand, buf, 16 ) != 16 ) gulp();

if ( write( hand, "data", 4 ) != 4 ) gulp();
writelong( buf, chucksize );
if ( write( hand, buf, 4 ) != 4 ) gulp();
}

/* --------------------------------------- traitement erreur fatale */

void gasp( char *fmt, ... )
{
  char lbuf[2048];
  va_list  argptr;
  va_start( argptr, fmt );
  vsprintf( lbuf, fmt, argptr );
  va_end( argptr );
  printf("STOP : %s\n", lbuf ); exit(1);
}
