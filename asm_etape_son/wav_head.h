typedef struct {
int chan;
unsigned long freq;    /* frequence d'echantillonnage */
unsigned long bpsec;   /* bytes par seconde */
int block;
int resol;             /* en bits */
unsigned long wavsize; /* longueur en echantillons (par canal) */
} wavpars;

#ifndef O_BINARY
#define O_BINARY 0
#endif

void WAVreadHeader( wavpars *s, int hand );

void WAVwriteHeader( wavpars *d, int hand );

void gasp( char *fmt, ... );  /* traitement erreur fatale */
