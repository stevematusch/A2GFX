/*****************************************/
/* This file includes bunch of asm lang  */
/* graphics routines, and associated     */
/* c language interface headers			 */
/*****************************************/

#include "TYPES.H"
#include "GRAF.H"


#asm

YAXIS    EQU $E0		; first chunk of 29 bytes on zero page
XAXIS    EQU $E1
BASE     EQU $E3
DISP     EQU $E5
BITNUM   EQU $E6
FROM     EQU BITNUM+$1
TO       EQU FROM+$2
AT       EQU TO+$2
COLOR    EQU AT+$2
HLEN     EQU COLOR+$1
WIDTH    EQU HLEN+$2
HEIGHT   EQU WIDTH+$1
DATA     EQU HEIGHT+$1
BITCNT   EQU DATA+$2
TEMPW    EQU BITCNT+$1
TEMPX    EQU TEMPW+$1
SHIFTR   EQU TEMPX+$1
PNTR     EQU SHIFTR+$1
BYTCNT   EQU PNTR+$2
LENGTH   EQU BYTCNT+$1
RTNADR   EQU LENGTH+$1

DESTX    EQU $90		; 2nd chunk of 24 bytes on zero page
DESTY    EQU $92
ASV1     EQU DESTY+$2		
YSV1     EQU ASV1+$1
XSV1     EQU YSV1+$1
BITSET   EQU XSV1+$1
RANGE    EQU BITSET+$1
TMPLT1   EQU RANGE+$1
TMPLT2   EQU TMPLT1+$1
NBYTS    EQU TMPLT2+$1
DELTAX   EQU NBYTS+$1
DELTAY   EQU DELTAX+$2
I        EQU DELTAY+$2
XINC     EQU I+$2
YINC     EQU XINC+$2
ERROR    EQU YINC+$2
RTN      EQU ERROR+$2

;  A bunch of data tables.   These are near the beginning
;  of the file so as to avoid splitting the table across
;  the linker hole at $2000 to $5999
;
XCOORD   FCB $01,$02,$04,$08,$10,$20,$40
		 FCB $01,$02,$04,$08,$10,$20,$40
		 FCB $01,$02,$04,$08,$10,$20,$40
		 FCB $01,$02,$04,$08,$10,$20,$40
		 FCB $01,$02,$04,$08,$10,$20,$40
		 FCB $01,$02,$04,$08,$10,$20,$40
		 FCB $01,$02,$04,$08,$10,$20,$40
		 FCB $01,$02,$04,$08,$10,$20,$40
		 FCB $01,$02,$04,$08,$10,$20,$40
		 FCB $01,$02,$04,$08,$10,$20,$40
		 FCB $01,$02,$04,$08,$10,$20,$40
		 FCB $01,$02,$04,$08,$10,$20,$40
		 FCB $01,$02,$04,$08,$10,$20,$40
		 FCB $01,$02,$04,$08,$10,$20,$40
		 FCB $01,$02,$04,$08,$10,$20,$40
		 FCB $01,$02,$04,$08,$10,$20,$40
		 FCB $01,$02,$04,$08,$10,$20,$40
		 FCB $01,$02,$04,$08,$10,$20,$40
		 FCB $01,$02,$04,$08,$10,$20,$40
		 FCB $01,$02,$04,$08,$10,$20,$40
		 FCB $01,$02,$04,$08,$10,$20,$40
		 FCB $01,$02,$04,$08,$10,$20,$40
		 FCB $01,$02,$04,$08,$10,$20,$40
		 FCB $01,$02,$04,$08,$10,$20,$40
		 FCB $01,$02,$04,$08,$10,$20,$40
		 FCB $01,$02,$04,$08,$10,$20,$40
		 FCB $01,$02,$04,$08,$10,$20,$40
		 FCB $01,$02,$04,$08,$10,$20,$40
		 FCB $01,$02,$04,$08,$10,$20,$40
		 FCB $01,$02,$04,$08,$10,$20,$40
		 FCB $01,$02,$04,$08,$10,$20,$40
		 FCB $01,$02,$04,$08,$10,$20,$40
		 FCB $01,$02,$04,$08,$10,$20,$40
		 FCB $01,$02,$04,$08,$10,$20,$40
		 FCB $01,$02,$04,$08,$10,$20,$40
		 FCB $01,$02,$04,$08

;
XCORD2   FCB $10,$20,$40
         FCB $01,$02,$04,$08,$10,$20,$40
         FCB $01,$02,$04,$08,$10,$20,$40
         FCB $01,$02,$04,$08,$10,$20,$40
         FCB $01,$02,$04,$08,$10,$20,$40
;
;
;  
XDIV7    FCB $00,$00,$00,$00,$00,$00,$00
         FCB $01,$01,$01,$01,$01,$01,$01
         FCB $02,$02,$02,$02,$02,$02,$02
         FCB $03,$03,$03,$03,$03,$03,$03
         FCB $04,$04,$04,$04,$04,$04,$04
         FCB $05,$05,$05,$05,$05,$05,$05
         FCB $06,$06,$06,$06,$06,$06,$06
         FCB $07,$07,$07,$07,$07,$07,$07
         FCB $08,$08,$08,$08,$08,$08,$08
         FCB $09,$09,$09,$09,$09,$09,$09
         FCB $0A,$0A,$0A,$0A,$0A,$0A,$0A
         FCB $0B,$0B,$0B,$0B,$0B,$0B,$0B
         FCB $0C,$0C,$0C,$0C,$0C,$0C,$0C
         FCB $0D,$0D,$0D,$0D,$0D,$0D,$0D
         FCB $0E,$0E,$0E,$0E,$0E,$0E,$0E
         FCB $0F,$0F,$0F,$0F,$0F,$0F,$0F
;
         FCB $10,$10,$10,$10,$10,$10,$10
         FCB $11,$11,$11,$11,$11,$11,$11
         FCB $12,$12,$12,$12,$12,$12,$12
         FCB $13,$13,$13,$13,$13,$13,$13
         FCB $14,$14,$14,$14,$14,$14,$14
         FCB $15,$15,$15,$15,$15,$15,$15
         FCB $16,$16,$16,$16,$16,$16,$16
         FCB $17,$17,$17,$17,$17,$17,$17
         FCB $18,$18,$18,$18,$18,$18,$18
         FCB $19,$19,$19,$19,$19,$19,$19
         FCB $1A,$1A,$1A,$1A,$1A,$1A,$1A
         FCB $1B,$1B,$1B,$1B,$1B,$1B,$1B
         FCB $1C,$1C,$1C,$1C,$1C,$1C,$1C
         FCB $1D,$1D,$1D,$1D,$1D,$1D,$1D
         FCB $1E,$1E,$1E,$1E,$1E,$1E,$1E
         FCB $1F,$1F,$1F,$1F,$1F,$1F,$1F
;
         FCB $20,$20,$20,$20,$20,$20,$20
         FCB $21,$21,$21,$21,$21,$21,$21
         FCB $22,$22,$22,$22,$22,$22,$22
         FCB $23,$23,$23,$23,$23,$23,$23
         FCB $24,$24,$24,$24,$24,$24,$24
;
XDV72    FCB $24,$24,$24
         FCB $25,$25,$25,$25,$25,$25,$25
         FCB $26,$26,$26,$26,$26,$26,$26
         FCB $27,$27,$27,$27,$27,$27,$27
         FCB $28,$28,$28,$28,$28,$28,$28
         FCB $29,$29,$29,$29,$29,$29,$29
;
;
BITCNV   FCB $00,$01,$02,$00,$03
         FCB $00,$00,$00,$04,$00
         FCB $00,$00,$00,$00,$00
         FCB $00,$05,$00,$00,$00
         FCB $00,$00,$00,$00,$00
         FCB $00,$00,$00,$00,$00
         FCB $00,$00,$06,$00,$00
         FCB $00,$00,$00,$00,$00
         FCB $00,$00,$00,$00,$00
         FCB $00,$00,$00,$00,$00
         FCB $00,$00,$00,$00,$00
         FCB $00,$00,$00,$00,$00
         FCB $00,$00,$00,$07,$00
  
YLOBYT  
         FCB $D0,$D0,$D0,$D0,$D0,$D0,$D0,$D0
         FCB $50,$50,$50,$50,$50,$50,$50,$50
         FCB $D0,$D0,$D0,$D0,$D0,$D0,$D0,$D0
         FCB $50,$50,$50,$50,$50,$50,$50,$50
         FCB $D0,$D0,$D0,$D0,$D0,$D0,$D0,$D0
         FCB $50,$50,$50,$50,$50,$50,$50,$50
         FCB $D0,$D0,$D0,$D0,$D0,$D0,$D0,$D0
         FCB $50,$50,$50,$50,$50,$50,$50,$50
         FCB $A8,$A8,$A8,$A8,$A8,$A8,$A8,$A8
         FCB $28,$28,$28,$28,$28,$28,$28,$28
		 FCB $A8,$A8,$A8,$A8,$A8,$A8,$A8,$A8
         FCB $28,$28,$28,$28,$28,$28,$28,$28
		 FCB $A8,$A8,$A8,$A8,$A8,$A8,$A8,$A8
         FCB $28,$28,$28,$28,$28,$28,$28,$28
		 FCB $A8,$A8,$A8,$A8,$A8,$A8,$A8,$A8
         FCB $28,$28,$28,$28,$28,$28,$28,$28
         FCB $80,$80,$80,$80,$80,$80,$80,$80
         FCB $00,$00,$00,$00,$00,$00,$00,$00
         FCB $80,$80,$80,$80,$80,$80,$80,$80
         FCB $00,$00,$00,$00,$00,$00,$00,$00
         FCB $80,$80,$80,$80,$80,$80,$80,$80
         FCB $00,$00,$00,$00,$00,$00,$00,$00
         FCB $80,$80,$80,$80,$80,$80,$80,$80
         FCB $00,$00,$00,$00,$00,$00,$00,$00
;
YHIBYT   FCB $3F,$3B,$37,$33,$2F,$2B,$27,$23
         FCB $3F,$3B,$37,$33,$2F,$2B,$27,$23
         FCB $3E,$3A,$36,$32,$2E,$2A,$26,$22
         FCB $3E,$3A,$36,$32,$2E,$2A,$26,$22
         FCB $3D,$39,$35,$31,$2D,$29,$25,$21
         FCB $3D,$39,$35,$31,$2D,$29,$25,$21
         FCB $3C,$38,$34,$30,$2C,$28,$24,$20
         FCB $3C,$38,$34,$30,$2C,$28,$24,$20
         FCB $3F,$3B,$37,$33,$2F,$2B,$27,$23
         FCB $3F,$3B,$37,$33,$2F,$2B,$27,$23
         FCB $3E,$3A,$36,$32,$2E,$2A,$26,$22
         FCB $3E,$3A,$36,$32,$2E,$2A,$26,$22
         FCB $3D,$39,$35,$31,$2D,$29,$25,$21
         FCB $3D,$39,$35,$31,$2D,$29,$25,$21
         FCB $3C,$38,$34,$30,$2C,$28,$24,$20
         FCB $3C,$38,$34,$30,$2C,$28,$24,$20
         FCB $3F,$3B,$37,$33,$2F,$2B,$27,$23
         FCB $3F,$3B,$37,$33,$2F,$2B,$27,$23
         FCB $3E,$3A,$36,$32,$2E,$2A,$26,$22
         FCB $3E,$3A,$36,$32,$2E,$2A,$26,$22
         FCB $3D,$39,$35,$31,$2D,$29,$25,$21
         FCB $3D,$39,$35,$31,$2D,$29,$25,$21
         FCB $3C,$38,$34,$30,$2C,$28,$24,$20
         FCB $3C,$38,$34,$30,$2C,$28,$24,$20

;  MODULO 7 TABLE
XMOD7
		 FCB $00,$01,$02,$03,$04,$05,$06
         FCB $00,$01,$02,$03,$04,$05,$06
         FCB $00,$01,$02,$03,$04,$05,$06
         FCB $00,$01,$02,$03,$04,$05,$06
         FCB $00,$01,$02,$03,$04,$05,$06
         FCB $00,$01,$02,$03,$04,$05,$06
         FCB $00,$01,$02,$03,$04,$05,$06
         FCB $00,$01,$02,$03,$04,$05,$06
         FCB $00,$01,$02,$03,$04,$05,$06
         FCB $00,$01,$02,$03,$04,$05,$06
         FCB $00,$01,$02,$03,$04,$05,$06
         FCB $00,$01,$02,$03,$04,$05,$06
         FCB $00,$01,$02,$03,$04,$05,$06
         FCB $00,$01,$02,$03,$04,$05,$06
         FCB $00,$01,$02,$03,$04,$05,$06
         FCB $00,$01,$02,$03,$04,$05,$06
         FCB $00,$01,$02,$03,$04,$05,$06
         FCB $00,$01,$02,$03,$04,$05,$06
         FCB $00,$01,$02,$03,$04,$05,$06
         FCB $00,$01,$02,$03,$04,$05,$06
         FCB $00,$01,$02,$03,$04,$05,$06
         FCB $00,$01,$02,$03,$04,$05,$06
         FCB $00,$01,$02,$03,$04,$05,$06
         FCB $00,$01,$02,$03,$04,$05,$06
         FCB $00,$01,$02,$03,$04,$05,$06
         FCB $00,$01,$02,$03,$04,$05,$06
         FCB $00,$01,$02,$03,$04,$05,$06
         FCB $00,$01,$02,$03,$04,$05,$06
         FCB $00,$01,$02,$03,$04,$05,$06
         FCB $00,$01,$02,$03,$04,$05,$06
         FCB $00,$01,$02,$03,$04,$05,$06
         FCB $00,$01,$02,$03,$04,$05,$06
         FCB $00,$01,$02,$03,$04,$05,$06
         FCB $00,$01,$02,$03,$04,$05,$06
         FCB $00,$01,$02,$03,$04,$05,$06
         FCB $00,$01,$02,$03,$04,$05,$06
         FCB $00,$01,$02,$03,$04,$05,$06
		 
; This is the ascii character generator bitmap
; This is generalized image table, with objects
; 1 byte wide, 7 bytes tall, 96 objects
; 
;
CHRTBL#  
		 FCB $60,$01,$07					; $60 OBJECTS, 1 WIDE, 7 TALL
         FCB $00,$00,$00,$00,$00,$00,$00    ; " "
         FCB $04,$04,$04,$04,$04,$00,$04    ; "!"
         FCB $0A,$0A,$0A,$00,$00,$00,$00    ; """
         FCB $0A,$0A,$1F,$0A,$1F,$0A,$0A    ; "#"
         FCB $04,$1E,$05,$0E,$14,$0F,$04    ; "$"
         FCB $00,$13,$0B,$04,$1A,$19,$00    ; "%"
         FCB $02,$05,$05,$02,$15,$0F,$16    ; "&"
         FCB $04,$04,$04,$00,$00,$00,$00    ; "'"
         FCB $04,$02,$01,$01,$01,$02,$04    ; "("
         FCB $04,$08,$10,$10,$10,$08,$04    ; ")"
         FCB $04,$15,$0E,$04,$0E,$15,$04    ; "*"
         FCB $00,$04,$04,$1F,$04,$04,$00    ; "+"
         FCB $00,$00,$00,$00,$06,$04,$02    ; ","
         FCB $00,$00,$00,$1F,$00,$00,$00    ; "-" 
         FCB $00,$00,$00,$00,$00,$06,$06    ; "."
         FCB $10,$10,$08,$04,$02,$01,$01    ; "/"
         FCB $04,$0A,$11,$11,$0A,$04,$00    ; "0"
         FCB $04,$06,$04,$04,$04,$0E,$00    ; "1"
         FCB $0E,$11,$10,$0C,$06,$1F,$00    ; "2"
         FCB $0E,$11,$10,$0C,$11,$0E,$00    ; "3"
         FCB $01,$09,$09,$1F,$08,$08,$00    ; "4"
         FCB $1F,$01,$0F,$10,$10,$0F,$00    ; "5"
         FCB $0E,$01,$01,$0F,$11,$0E,$00    ; "6"
         FCB $1F,$10,$08,$04,$02,$01,$00    ; "7"
         FCB $0E,$11,$0E,$11,$11,$0E,$00    ; "8"
         FCB $1E,$11,$1E,$10,$10,$0E,$00    ; "9"
         FCB $00,$06,$06,$00,$06,$06,$00    ; ":"
         FCB $00,$06,$06,$00,$06,$04,$02    ; ";"
         FCB $08,$04,$02,$01,$02,$04,$08    ; "<"
         FCB $00,$00,$1F,$00,$1F,$00,$00    ; "="
         FCB $02,$04,$08,$10,$08,$04,$02    ; ">" 
         FCB $0E,$11,$10,$0C,$04,$00,$04    ; "?"
         FCB $0E,$11,$1D,$0D,$05,$01,$1E    ; "@"
         FCB $04,$0A,$11,$1F,$11,$11,$00    ; "A"
         FCB $0F,$11,$0F,$11,$11,$0F,$00    ; "B
         FCB $0E,$11,$01,$01,$11,$0E,$00    ; "C"
         FCB $0F,$11,$11,$11,$11,$0F,$00    ; "D"
         FCB $1F,$01,$07,$01,$01,$1F,$00    ; "E"
         FCB $1F,$01,$07,$01,$01,$01,$00    ; "F"
         FCB $0F,$11,$01,$1D,$11,$1E,$00    ; "G"
         FCB $11,$11,$1F,$1F,$11,$11,$00    ; "H"
         FCB $1F,$04,$04,$04,$04,$1F,$00    ; "I" 
         FCB $10,$10,$10,$10,$11,$0E,$00    ; "J" 
         FCB $11,$09,$07,$05,$09,$11,$00    ; "K"
         FCB $01,$01,$01,$01,$01,$1F,$00    ; "L"
         FCB $11,$1B,$15,$11,$11,$11,$00    ; "M
         FCB $11,$13,$15,$19,$11,$11,$00    ; "N"
         FCB $0E,$11,$11,$11,$11,$0E,$00    ; "O"
         FCB $0F,$11,$11,$0F,$01,$01,$00    ; "P"
         FCB $0E,$11,$11,$15,$09,$16,$00    ; "Q"
         FCB $0F,$11,$11,$0F,$09,$11,$00    ; "R"
         FCB $1F,$01,$1F,$10,$10,$1F,$00    ; "S"
         FCB $1F,$04,$04,$04,$04,$04,$00    ; "T" 
         FCB $11,$11,$11,$11,$11,$0E,$00    ; "U" 
         FCB $11,$11,$11,$11,$1A,$04,$00    ; "V"
         FCB $11,$11,$11,$15,$1B,$11,$00    ; "W" 
         FCB $11,$0A,$04,$0A,$11,$11,$00    ; "X"
         FCB $11,$11,$0A,$04,$04,$04,$00    ; "Y"
         FCB $1F,$08,$04,$02,$01,$1F,$00    ; "Z"
         FCB $07,$01,$01,$01,$01,$01,$07    ; "["
         FCB $01,$01,$02,$04,$08,$10,$10    ; "\" 
         FCB $1C,$10,$10,$10,$10,$10,$1C    ; "]" 
         FCB $04,$0E,$15,$04,$04,$04,$04    ; "^" 
         FCB $00,$00,$00,$00,$00,$00,$1F    ; "_" 
         FCB $01,$02,$04,$00,$00,$00,$00    ; "`"
         FCB $00,$0E,$08,$0E,$09,$1E,$00    ; "a"
         FCB $02,$02,$02,$0E,$12,$0F,$00    ; "b" 
         FCB $00,$00,$1E,$01,$01,$1E,$00    ; "c"
         FCB $08,$08,$08,$0E,$09,$1E,$00    ; "d"
         FCB $00,$0E,$11,$0F,$01,$0E,$00    ; "e"
         FCB $04,$12,$02,$0F,$02,$02,$00    ; "f"
         FCB $00,$0E,$11,$11,$1E,$10,$0E    ; "g"
         FCB $01,$01,$01,$0F,$11,$11,$00    ; "h" 
         FCB $04,$00,$04,$04,$04,$0E,$00    ; "i"
         FCB $08,$00,$08,$08,$08,$0A,$04    ; "j"
         FCB $00,$09,$05,$03,$05,$09,$00    ; "k"
         FCB $06,$04,$04,$04,$04,$0E,$00    ; "l" 
         FCB $00,$0A,$15,$15,$15,$15,$00    ; "m"
         FCB $00,$0D,$13,$11,$11,$11,$00    ; "n"
         FCB $00,$0C,$12,$12,$12,$0C,$00    ; "o"
         FCB $00,$0F,$11,$11,$0F,$01,$01    ; "p"
         FCB $00,$0E,$09,$09,$0E,$08,$18    ; "q" 
         FCB $00,$0A,$16,$02,$02,$02,$00    ; "r"
         FCB $00,$1E,$01,$0E,$10,$0E,$00    ; "s"
         FCB $04,$1F,$04,$04,$04,$08,$00    ; "t"  
         FCB $00,$12,$12,$12,$12,$1C,$00    ; "u" 
         FCB $00,$11,$11,$0A,$0A,$04,$00    ; "v"
         FCB $00,$11,$11,$11,$15,$0A,$00    ; "w" 
         FCB $00,$11,$0A,$04,$0A,$11,$00    ; "x"
         FCB $00,$11,$11,$11,$1E,$10,$1E    ; "y"
         FCB $00,$1F,$08,$04,$02,$1F,$00    ; "z" 
         FCB $0C,$02,$02,$01,$02,$02,$0C    ; "{"
         FCB $04,$04,$04,$00,$04,$04,$04    ; "|"
         FCB $06,$08,$08,$10,$08,$08,$06    ; "}" 
         FCB $00,$00,$10,$0A,$05,$00,$00    ; "~"
         FCB $00,$00,$00,$0E,$0E,$0E,$00    ; "???"
;
;

#endasm 

/* External variables */
unsigned char *pyaxis;
unsigned int *pxaxis;
unsigned char **ppbase;
unsigned char *pdisp;
unsigned char *pbitnum;
unsigned int *pdestx;
unsigned int *pdesty;

/*****************************************/
/* GRAFINIT:  Initialize pointers to zero page */
/*****************************************/
GRAFINIT()
{
	pyaxis = 0xE0;
	pxaxis = 0xE1;
	ppbase = 0xE3;
	pdisp = 0xE5;
	pbitnum = 0xE6;
	pdestx = 0X90;
	pdesty = 0x92;
	
}
	

/*****************************************/
/* HGR1ON:  C Language Call - Turn on HGR1*/
/*****************************************/
HGR1ON()
{
	#asm
	JSR HRGON	
	#endasm
}

/*****************************************/
/* HGR1CLR:  C Language Call - Clear HGR1 */
/*****************************************/
HGR1CLR()
{
	printf("HGR1CLR\n");
	#asm
	JSR CLRPG1	
	#endasm
}

/*****************************************/
/* HGR1LINE:  C Language Call - PLOT X,Y */
/*****************************************/
HGR1LINE(x1,y1,x2,y2)
int x1,y1,x2,y2;
{
	if(x1<0 || x1>279 || y1<0 || y1>191)
		return;
	if(x2<0 || x2>279 || y2<0 || y2>191)
		return;
/*
	printf("px1-%x py1-%x px2-%x py2-%x\n", pxaxis,pyaxis, pdestx, pdesty);
	printf("x1-%x y1-%x x2-%x y2-%d\n", *pxaxis,(unsigned int)*pyaxis, *pdestx, *pdesty);
	getch();
*/	
	*pxaxis = (unsigned int )x1;
	*pyaxis = (unsigned char)y1;
	*pdestx = (unsigned int )x2;
	*pdesty = (unsigned int )y2;

	#asm
	JSR DRAWLN
	#endasm
}

/*****************************************/
/* HGR1PLOT:  C Language Call - PLOT X,Y */
/*****************************************/
HGR1PLOT(x, y)
int x,y;
{
	if(x<0 || x>279 || y<0 || y>191)
		return;
	
	*pxaxis = (unsigned int )x;
	*pyaxis = (unsigned char)y;

	#asm
	JSR PLOT
	#endasm
}


/*****************************************/
/* HGR1BMAPDRW:  C Language Call - Draw a bitmap */
/* pbmptbl - pointer to bitmap table
/* ibmp - index to the bitmap to draw
/* x,y - location on screen.   x = 0-39, y = 0-191
/*****************************************/
HGR1BMPDRW(pbmptbl, ibmp, x,y)
unsigned char *pbmptbl;
unsigned int ibmp, x,y;
{
	unsigned char iline, icol, width, height, nbmps, x0;
	unsigned int bytes;		/* bytes per image */


	/* find the correct image in the bitmap table */
	nbmps = *(pbmptbl++);
	width = *(pbmptbl++);
	height = *(pbmptbl++);
	bytes = width * height;
	pbmptbl += ibmp*bytes;  /* got the address of the image */
	
	iline = height;
	icol = width;
	x0 = x;
	
	/* go through columns and lines */
	loop1:
		
		/* get the base address & disp on the screen */
		*pxaxis = (unsigned int )x*7;
		*pyaxis = (unsigned char)y;

		/* set the xy and call base address calculation */
		*pxaxis = (unsigned int )x*7;
		*pyaxis = (unsigned char)y;

		printf("BASCAL px-%x py-%x x-%x y-%x\n",pxaxis,pyaxis, *pxaxis,(unsigned int)*pyaxis);
		getch();

		#asm
		JSR BASCAL
		#endasm
		printf("       base-%x disp-%x bitnum-%x\n",(unsigned int)*ppbase, (unsigned int) *pdisp, (unsigned int)*pbitnum);

		**(ppbase + *pdisp) = *pbmptbl;   /* write the byte */
		
		pbmptbl++;  /* go to the next byte in the table */
	
	icol--;  x++;
	if (icol > 0 && x<40)
		goto loop1;
	iline--; y++; x= x0;
	if (iline >0 && y<192)
		goto loop1;
}


/*****************************************/
/* All assembly langauge routines here */
/*****************************************/

#asm
;
;
; HRGON- TURN HIRES ON
;
HRGON    BIT $C050     ; selecbrun t graphics
         BIT $C057     ; select hires
		 BIT $C054     ; select page #1
		 BIT $C053	   ; ENABLE MIXED MODE
         ;BIT $C052    ; enable full screen
		 
         RTS 

;
;
;
; CLRPG1 - CLEARS PAGE ONE OF
;          HIRES GRAPHICS.
;
CLRPG1   PHA 
         TYA 
         PHA 
;
         LDA #$00
         STA DATA
         LDA #$20
         STA DATA+$1
;
         LDY #$00
         LDA #$00
;
CLOOP    STA (DATA),Y
         INC DATA
         BNE CLOOP
         INC DATA+$1
         LDA DATA+$1
         CMP #$40
         BEQ CXIT
         LDA #$00
         JMP CLOOP
;
CXIT     PLA 
         TAY 
         PLA 
         RTS 




;
;
; PLOT - PLOTS AN INDIVIDUAL
;        POINT.
;
PLOT     PHA 
         TYA 
         PHA 
;
         JSR BASCAL
;
         LDY DISP
         LDA BITNUM
         ORA (BASE),Y
         STA (BASE),Y
         PLA 
         TAY 
         PLA
		 RTS 

;
;
; ERASE - ERASES POINT AT
;         (XAXIS,YAXIS)
;
ERASE   
         PHA 
         TYA 
         PHA 
;
         JSR BASCAL
;
         LDY DISP
         LDA BITNUM
         EOR #$FF
         AND (BASE),Y
         STA (BASE),Y
;
         PLA 
         TAY 
         PLA 
         RTS 
;
;
; DRAWLN - DRAWS A LINE FROM
; (XAXIS,YAXIS) TO (DESTX,DESTY)
;
; AFTER RETURN, ALL AXIS ARE
; RESTORED TO ORIGINAL VALUE.
;
DRAWLN  
         JSR SAVREG
         JSR SAVAXS
         LDA #$00
         STA COLOR
         JMP DRWLNE
;
;
; ERSLN - ERASES A LINE INSTEAD
; OF DRAWING IT.
;
ERSLN   
         JSR SAVREG
         JSR SAVAXS
         LDA #$FF
         STA COLOR
;
;
DRWLNE  
;
; COMPUTE DELTAX
;
         SEC 
         LDA DESTX
         SBC XAXIS
         STA DELTAX
         LDA DESTX+$1
         SBC XAXIS+$1
         STA DELTAX+$1
;
; COMPUTE DELTAY
;
         SEC 
         LDA DESTY
         SBC YAXIS
         STA DELTAY
         LDA #$00
         SBC #$00
         STA DELTAY+$1
;
;
         LDA DELTAX+$1
         BPL DRWLN1
;
         LDA #$FF
         STA XINC
         STA XINC+$1
         SEC 
         LDA #$00
         SBC DELTAX
         STA DELTAX
         LDA #$00
         SBC DELTAX+$1
         STA DELTAX+$1
         JMP DRWLN2
;
;
DRWLN1  
         LDA #$01
         STA XINC
         LDA #$00
         STA XINC+$1
;
;
DRWLN2  
         LDA DELTAY+$1
         BPL DRWLN3
         LDA #$FF
         STA YINC
         STA YINC+$1
         SEC 
         LDA #$00
         SBC DELTAY
         STA DELTAY
         LDA #$00
         SBC DELTAY+$1
         STA DELTAY+$1
         JMP DRWLN4
;
;
DRWLN3  
         LDA #$01
         STA YINC
         LDA #$00
         STA YINC+$1
;
;
DRWLN4  
         LDA DELTAX
         CMP DELTAY
         LDA DELTAX+$1
         SBC DELTAY+$1
         BCS DRWLN5
;
         JSR DOFORY
         JMP DRWLN6
;
;
DRWLN5  
         JSR DOFORX
;
;
DRWLN6  
         JSR RSTAXS
         JSR RSTREG
         RTS 
;
;
;
DOFORX  
         LDA DELTAX
         BNE DFRX1
         LDA DELTAX+$1
         BEQ DFRX5
;
DFRX1   
         LDA DELTAX+$1
         STA I+$1
         LSR 
         STA ERROR+$1
         LDA DELTAX
         STA I
         ROR 
         STA ERROR
;
DFRX2   
         CLC 
         LDA ERROR
         ADC DELTAY
         STA ERROR
         LDA ERROR+$1
         ADC DELTAY+$1
         STA ERROR+$1
;
         LDA ERROR
         CMP DELTAX
         LDA ERROR+$1
         SBC DELTAX+$1
         BCC DFRX3
;
         LDA ERROR
         SBC DELTAX
         STA ERROR
         LDA ERROR+$1
         SBC DELTAX+$1
         STA ERROR+$1
         CLC 
         LDA YAXIS
         ADC YINC
         STA YAXIS
;
DFRX3   
         CLC 
         LDA XAXIS
         ADC XINC
         STA XAXIS
         LDA XAXIS+$1
         ADC XINC+$1
         STA XAXIS+$1
;
         BIT COLOR
         BPL DFRX6
;
; ERASE A DOT HERE
;
         JSR ERASE
         JMP DFRX7
;
; PLOT A POINT HERE.
;
DFRX6   
         JSR PLOT
;
;
DFRX7   
         LDA I
         BNE DFRX4
         DEC I+$1
DFRX4   
         DEC I
         LDA I
         ORA I+$1
         BNE DFRX2
DFRX5   
         RTS 
;
;
;
DOFORY  
         LDA DELTAY+$1
         STA I+$1
         LSR 
         STA ERROR+$1
         LDA DELTAY
         STA I
         ROR 
         STA ERROR
;
DFRY1   
         CLC 
         LDA ERROR
         ADC DELTAX
         STA ERROR
         LDA ERROR+$1
         ADC DELTAX+$1
         STA ERROR+$1
;
         LDA ERROR
         CMP DELTAY
         LDA ERROR+$1
         SBC DELTAY+$1
         BCC DFRY2
;
         LDA ERROR
         SBC DELTAY
         STA ERROR
         LDA ERROR+$1
         SBC DELTAY+$1
         STA ERROR+$1
;
         CLC 
         LDA XAXIS
         ADC XINC
         STA XAXIS
         LDA XAXIS+$1
         ADC XINC+$1
         STA XAXIS+$1
;
;
DFRY2   
         CLC 
         LDA YAXIS
         ADC YINC
         STA YAXIS
;
         JSR PLOT
;
         LDA I
         BNE DFRY3
         DEC I+$1
DFRY3    DEC I
;
         LDA I
         ORA I+$1
         BNE DFRY1
;
         RTS 
;
;
ASAVE    FCB $00
YSAVE    FCB $00
XSAVE    FCB $00
XAXSV    FCB $00
XAXSVH   FCB $00
YAXSV    FCB $00
;
		 
		 ;
; BASCAL- HIRES BASE CALCULATION
; ROUTINE.
;
; XAXIS-CONTIANS X-COORDINATE OF
;       POINT DESIRED.
; YAXIS-CONTIANS Y-COORDINATE OF
;       POINT DESIRED.
;
; BASE -TWO BYTE BASE ADDRESS IS
;       RETURNED HERE.
; DISP -ONE BYTE DISPLACEMENT IS
;       RETURNED HERE
;
; BITNUM - CONTAINS A "1" IN THE
;          BIT POSITION CORRES-
;          PONDING WITH THE BIT
;          TO BE SET.  ALL OTHER
;          BIT POSITIONS CONTAIN
;          "0".
;
;
;   ** CALCULATE BASE ADDRESS **
;
BASCAL  
;
         STA ASV1
         STY YSV1
         STX XSV1
;
;
; ** CALCULATE DISPLACEMENT **
;
         LDX YAXIS
         LDA YLOBYT,X
         STA BASE
         LDA YHIBYT,X
         STA BASE+$1
;
         LDX XAXIS
         LDA XAXIS+$1
         BNE BSCL2
;
; ** HERE X-COORDINATE <256 **
;
; DETERMINE BITNUM
;
         LDA XCOORD,X
         STA BITNUM
;
; "CALCULATE" XAXIS / 7
;
         LDA XDIV7,X
         STA DISP
;
         LDA ASV1
         LDX XSV1
         LDY YSV1
         RTS 
;
;
; ** HERE X-C00RDINATE >= 256 **
;
; DETERMINE BITNUM.
;
BSCL2    LDA XCORD2,X
         STA BITNUM
;
; "CALCULATE" XAXIS / 7
;
         LDA XDV72,X
         STA DISP
;
         LDA ASV1
         LDY YSV1
         LDX XSV1
         RTS 
;
;
SAVREG  
         STA ASAVE
         STX XSAVE
         STY YSAVE
         RTS 
;
;
RSTREG  
         LDA ASAVE
         LDX XSAVE
         LDY YSAVE
         RTS 
		 
		 ;
;
;
SAVAXS  
         PHA 
         LDA YAXIS
         STA YAXSV
         LDA XAXIS
         STA XAXSV
         LDA XAXIS+$1
         STA XAXSV+$1
         PLA 
         RTS 
;
RSTAXS  
         PHA 
         LDA YAXSV
         STA YAXIS
         LDA XAXSV
         STA XAXIS
         LDA XAXSV+$1
         STA XAXIS+$1
         PLA 
         RTS 

#endasm 
/*  ALL A BIT STILLBORN
;
;
; PRINT CHARACTERS TO THE SCREEN.  
; ADDRESS OF TEXT IS POINTED TO BY DATA
; PRINTING TO START AT XAXIS,YAXIS, ROUNDED DOWN TO EVEN COLUMN.
;
HGRPRINT
         STA SAVA
         STY SAVY
         STX SAVX
						
HPRINT1   				;LOOP THROUGH TEXT
         LDY #$00
         JSR HPRINT2
         LDA (DATA),Y	; LOAD THE CHARACTER
         BNE HPRINT1	; IF ZERO, WE'RE DONE
         JMP HPREXIT
;
; OKAY - WE'VE GOT THE CHARACTER.  NOW PRINT IT.

HPRINT2
         AND #$7F		; CONVERT TO STRAIGHT ASCII
         SEC 			; FORM A DISPLACEMENT INTO CHRTBL.
         SBC #$20

;
; MULTIPLY TIMES 7, SINCE EACH CHARACTER IS 7 PIXELS WIDE.
;
         STY PNTR
         STY PNTR+$1
         STA PNTR
         TAX 
         ASL PNTR
         ROL PNTR+$1
         LDA PNTR+$1
         PHA 
         LDA PNTR
         PHA 
         ASL PNTR
         ROL PNTR+$1
         CLC 
         PLA 
         ADC PNTR
         STA PNTR
         PLA 
         ADC PNTR+$1
         STA PNTR+$1
         CLC 
         TXA 
         ADC PNTR
         STA PNTR
         BCC HPRINT3
;
         INC PNTR+$1
;
; CONVERT DISPLACEMENT TO ADDRESS.
;
HPRINT3
         CLC 
         LDA #<CHRTBL   ;should be LSB
         ADC PNTR
         STA PNTR
         LDA #>CHRTBL   ;should be MSB
         ADC PNTR+$1
         STA PNTR+$1	; NOW PNTR HAS THE ADDRESS OF THE CHARACTER BITMAP
;
; NOW COPY THE BYTES		
		 
		 LDX #$07		; NEED TO LOOP THROUGH 7 LINES 
		 STX CLINES
HPRINT4
		 LDA (PNTR),Y	; LOAD THE FIRST BYTE OF CHARACTER FROM CHRTBL
		 
		 JSR BASCAL		; NOW CALCULATE THE BASE ADDRESS - BASE,DISP, IGNORE BITNUM
         LDY DISP
         STA (BASE),Y	; WRITE THE BYTE TO SCREEN
		 
		 INX YAXIS		; GO TO NEXT
		 DEC CLINES		; HAVE WE FINISHED 7 LINES?
		 BNE HPRRINT4	; IF SO, DONE

		
HPREXIT
		RTS

CLINES	FCB #$00


		
;
; OUTPUT CHARACTERS TO THE
; SCREEN
;
; EXAMPLE
;
;   JSR SYMBOL
;   ASC "HELLO THERE"
;   HEX 00
;
; PRINTS "HELLO THERE" AT XAXIS
; YAXIS.
;
SYMBOL  
         STA SAVA
         STY SAVY
         STX SAVX
;
         PLA 
         STA RTN
         PLA 
         STA RTN+$1
;
SLOOP   
         LDY #$00
         JSR INCR
         LDA (RTN),Y
         BNE SLOOP1
         JMP SYMXIT
SLOOP1  
;
; CONVERT TO STRAIGHT ASCII
;
         AND #$7F
;
; FORM A DISPLACEMENT INTO CHRTBL.
;
         SEC 
         SBC #$20
;
; MULTIPLY TIMES 7
;
         STY PNTR
         STY PNTR+$1
         STA PNTR
         TAX 
         ASL PNTR
         ROL PNTR+$1
         LDA PNTR+$1
         PHA 
         LDA PNTR
         PHA 
         ASL PNTR
         ROL PNTR+$1
         CLC 
         PLA 
         ADC PNTR
         STA PNTR
         PLA 
         ADC PNTR+$1
         STA PNTR+$1
         CLC 
         TXA 
         ADC PNTR
         STA PNTR
         BCC SYMBL1
;
         INC PNTR+$1
SYMBL1  
;
; CONVERT DISPLACEMENT TO ADDRESS.
;
         CLC 
         LDA #CHRTBL
         ADC PNTR
         STA PNTR
         LDA #CHRTBL+1  ; MODIFIED FROM /CHRTBL
         ADC PNTR+$1
         STA PNTR+$1
;
; FIX UP TYPO IN CHRTBL
;
         LDX #$00
SYMBL4  
         LDY #$00
         LDA (PNTR),Y
         JSR INCP
         LDY #$07
;
SYMBL5  
         LSR 
         ROL CHARS,X
         DEY 
         BPL SYMBL5
;
         INX 
         CPX #$07
         BCC SYMBL4
;
         LDA #$05
         STA WIDTH
         LDA #$07
         STA LENGTH
         LDA RTN
         PHA 
         LDA RTN+$1
         PHA 
         JSR ORPIX
;         ADR CHAR
         PLA 
         STA RTN+$1
         PLA 
         STA RTN
;
; MOVE OVER TO NEXT PRINT POSITION.
;
         CLC 
         LDA XAXIS
         ADC #$06
         STA XAXIS
         BCC SYMBL2
;
         INC XAXIS+$1
SYMBL2  
;
; PROVIDE "WRAP-AROUND" IF NECESSARY.
;
         LDA XAXIS
         CMP #$11
         LDA XAXIS+$1
         SBC #$01
         BCS SLOOP3
         JMP SLOOP
SLOOP3  
;
; TO MANY COLUMNS HERE.
;
         LDA #$00
         STA XAXIS
         STA XAXIS+$1
;
         LDA YAXIS
         CMP #$08
;
; IF AT BOTTOM, TOUGH LUCK!
;
         BCS SLOOP2
         JMP SLOOP
SLOOP2  
;
; IF NOT A BOTTOM, DECREMENT YAXIS.
;
         SEC 
         LDA YAXIS
         SBC #$08
         STA YAXIS
         JMP SLOOP
;
;
SYMXIT  
         JSR INCR
         LDA SAVA
         LDY SAVY
         LDX SAVX
         JMP (RTN)
*/ 
#asm
;
SAVA     FCB $00
SAVY     FCB $00
SAVX     FCB $00
;
CHAR     FCB $05,$07
CHARS    FCB $00,$00,$00,$00,$00,$00,$00,$00




#endasm



