/* programme pour experimenter le decoupage en bandes sur fichier WAVE */
/*   */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <math.h>

#include "wav_head.h"


void usage()
{
fprintf( stderr, "\nUsage : wav2asm source.wav dest.s\n\n");
exit(1);
}

int main( int argc, char ** argv )
{
int shand; wavpars s;
char snam[256];
char dnam[256];
FILE * dfil;

if ( argc != 3 ) usage();

sprintf( snam, "%s", argv[1] );
sprintf( dnam, "%s", argv[2] );

printf("ouverture %s en lecture\n", snam );
shand = open( snam, O_RDONLY | O_BINARY );
if ( shand == -1 ) gasp("not found");

WAVreadHeader( &s, shand );
if	(
	( s.chan != 1 )   ||
	( s.resol != 16 )
	)
	gasp("programme seulement pour fichiers mono 16 bits");
printf("%d echantillons par canal, duree %gs\n", (int)s.wavsize, (double)s.wavsize / (double)s.freq );

printf("ouverture %s en ecriture\n", dnam );
dfil = fopen( dnam, "w" );
if ( dfil == NULL ) gasp("pb ouverture pour ecrire");

fprintf( dfil, "\tAREA DonneeSon, CODE, READONLY\n");
fprintf( dfil, "\texport LongueurSon\n");
fprintf( dfil, "\texport PeriodeSonMicroSec\n");
fprintf( dfil, "\texport Son\n");

fprintf( dfil, "LongueurSon\tDCD\t%lu\n", s.wavsize );
fprintf( dfil, "PeriodeSonMicroSec\tDCD\t%d\n", (int)( floor( 1000000.0/(double)s.freq + 0.5 ) ) );

fprintf( dfil, "Son "); 

#define FRAMLEN 512

unsigned char sbuf[FRAMLEN];	// source
int  sind;			// index courant dans sbuf[]
int rdcont;
int sbufcont;			// contenu de sbuf[] */
long qbytes;
int bpsam; 
short int val16;

bpsam = s.chan * ((s.resol)>>3);
qbytes = s.wavsize * bpsam;

while	( qbytes > 0L )   /* qbytes = nombre de bytes restant a traiter */
	{
	if	( qbytes < (long)FRAMLEN )
		rdcont = (int)qbytes;
	else	rdcont = FRAMLEN;
	sbufcont = read( shand, sbuf, rdcont );
	if	( sbufcont < rdcont )
		gasp("fin inattendue fichier source %d vs %d", sbufcont, rdcont );
	qbytes -= (long)rdcont;
	// ici on a sbufcont bytes dans sbuf, prets a traiter
	for	( sind = 0; sind < sbufcont; sind += 2 )
		{
		val16 = ( sbuf[sind+1] << 8 ) + sbuf[sind];
		fprintf( dfil, "\tdcw\t%d\n", (int)val16 );
		}
	}
fprintf( dfil, "\tend\n"); 
fclose( dfil );
close( shand );
return 0;
}

