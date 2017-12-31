/*****************************************/
/* This file includes bunch of asm lang  */
/* graphics routines, and associated     */
/* c language interface headers			 */
/*****************************************/

#include "TYPES.H"

#asm
; Graphics utilities base
GUTIL	EQU $8000		

; Parameters

ARG		EQU GUTIL+5 ; arg - used for misc functions, e.g. SetColor and SetPage
X0L		EQU GUTIL+6	; x0l - low part of the X0 coordinate (0-279)
X0H		EQU GUTIL+7 ; x0h -   high part of X0
Y0		EQU GUTIL+8 ; y0  - Y0 coordinate (0-191)
X1L		EQU GUTIL+9 ; x1l - low part of X1 (0-279)
X1H		EQU GUTIL+10 ; x1h -   high part of X1
Y1		EQU GUTIL+11 ; y1  - Y1 coordinate (0-191)
RAD 	EQU GUTIL+12 ; rad - circle radius (0-255)

RASTTOP	EQU GUTIL+52 ; topmost line to rasterize (0-191)  
RASTBOT EQU GUTIL+53 ; bottom-most line to rasterize (0-191), inclusive
RASTX1L EQU GUTIL+54 ; address of rastx1l table
RASTX1H EQU GUTIL+56 ; (2 bytes) address of rastx1h table
RASTX2L EQU GUTIL+58 ; (2 bytes) address of rastx2l table
RASTX2H EQU GUTIL+60 ; (2 bytes) address of rastx2h table

; Routine Addresses

;Init - call this when the library is first loaded.  It must be
;       called before any other functions are used.  It initializes the
;       color to zero and the page to $20.
;SetColor - set the color used for drawing (0-7) to the value in "arg".
;           The numbering is the same as the Applesoft hi-res colors.
;SetPage - set the hi-res page used for drawing to the value in "arg",
;           which must be $20 or $40.  Does not change the page that is displayed.
;           (Because a bad value can cause memory corruption, this value *is*
;           checked, and bad values rejected.)
;Clear - erase the current hi-res page to the current color.
;DrawPoint - plot a single point at x0,y0.
;DrawLine - draw a line from x0,y0 to x1,y1 (inclusive).
;DrawRect - draw a rectangle with corners at x0,y0 and x1,y1 (inclusive).
;           x0,y0 is the top-left, x1,y1 is the bottom-right.  The left and
;           right edges will be drawn two bits wide to ensure that the edges
;           are visible (drawn at x0+1, x1-1).
;FillRect - draw a filled rectangle with corners at x0,y0 and x1,y1
;          (inclusive).
;DrawCircle - draw a circle with center at x0,y0 and radius=rad.
;FillCircle - draw a filled circle with center at x0,y0 and radius=rad.
;SetLineMode - set the DrawLine mode to the value in "arg", which can
;           be 0 (normal) or 1 (xdraw).
;FillRaster - draw an arbitrary shape from the rasterization tables.
;             For each line from top to bottom, the left and right edges will
;             be read from rastx1/rastx2 and a raster drawn in the current color.

INIT		EQU GUTIL+0
SETCOLOR	EQU	GUTIL+16
SETPAGE		EQU GUTIL+19
CLEAR		EQU	GUTIL+22
DRAWPOINT	EQU	GUTIL+25
DRAWLINE	EQU	GUTIL+28
DRAWRECT	EQU	GUTIL+31
FILLRECT	EQU	GUTIL+34
DRAWCIRCLE	EQU	GUTIL+37
FILLCIRCLE	EQU	GUTIL+40
SETLINEMODE	EQU	GUTIL+43
FILLRASTER	EQU GUTIL+49

TXTCLR 	EQU $c050	;enable graphics
TXTSET 	EQU $c051	;text-only
MIXCLR 	EQU $c052	;disable mixed mode
MIXSET 	EQU $c053	;enable mixed mode (4 lines of text)
LOWSCR 	EQU $c054	;display page 1
HISCR 	EQU $c055	;display page 2
LORES 	EQU $c056	;show lo-res screen
HIRES 	EQU $c057	;show hi-res screen

#endasm 

/* External variables - matching parameters*/

unsigned char *pGUTIL;
unsigned char *pARG;
unsigned char *pX0L;
unsigned char *pX0H;
unsigned char *pY0;
unsigned char *pX1L;
unsigned char *pX1H;
unsigned char *pY1;
unsigned char *pRAD;

/*****************************************/
/* GRAFINIT:  Initialize pointers to zero page */
/*****************************************/
G_Init()
{
	/* set parameter addresses */
	pGUTIL = 0x8000;
	pARG = pGUTIL + 5;
	pX0L = pGUTIL + 6;
	pX0H = pGUTIL + 7;
	pY0 = pGUTIL + 8;
	pX1L = pGUTIL + 9;
	pX1H = pGUTIL + 10;
	pY1 = pGUTIL + 11;
	pRAD = pGUTIL + 12;

	#asm
	JSR INIT	
	#endasm
}

/************************************************************/
/* G_SetColor(c):  Set drawing color 						*/
/************************************************************/
G_SetColor(c)
int c;
{
	*pARG = (char)c;
	#asm
	JSR SETCOLOR
	#endasm
}

/************************************************************/
/* G_ScrnClear():  Clear active drawing screen				*/
/************************************************************/

G_ScrnClear()
{
	#asm
	JSR CLEAR	
	#endasm
}

/************************************************************/
/* G_DrawScrnSet(fScrn):  Set screen number and mode */
/************************************************************/
G_DrawScrnSet(fScrn)

int fScrn;	/*0 = HGR1, 1 = HGR2 */
{
	/* Select graphics screen to draw on*/
	
	if(fScrn)	/* check which screen we want */
	{
		pt("Set Draw HiScr");
		#asm
		LDA #$40	/* Screen 2 */
		STA ARG
		#endasm
	}
	else
	{
		pt("Set Draw LoScr");
		#asm  		/* Screen 1 */
		LDA #$20
		STA ARG
		#endasm
	}
	#asm
	JSR SETPAGE		;Call Set page routine
	#endasm
}
	

/************************************************************/
/* G_DispScrnSet(fScrn,fGMode):  Set screen number and mode */
/************************************************************/
G_DispScrnSet(fScrn,fMixed)

int fScrn;	/*0 = HGR1, 1 = HGR2 */
int fMixed; /*0 = Graphics only, 1 = Mixed */
{
	#asm
	BIT TXTCLR
	BIT HIRES
	#endasm

	/* Select graphics screen to display */
	
	if(fScrn)	/* check which screen we want */
	{
		pt("Set Disp HiScr");
		#asm
		BIT	HISCR	;Set #2 Page
		#endasm
	}
	else
	{
		pt("Set Draw LoScr");
		#asm
		BIT LOWSCR	; Set #1 Page
		#endasm
	}
	
	/* Select text/gr or pure graphics mode */
	if(fMixed)
	{
		pt("Set Mixed");
		#asm
		BIT	MIXSET	;Set mixed text/graphics
		#endasm
	}
	else
	{
		pt("Set Pure graphics");
		#asm
		BIT MIXCLR	;Set pure graphics
		#endasm
	}
	
}

/************************************************************/
/* G_DrawLine(x0,y0,x1,x1):  Draw line, x0,y0 to x1,y1 		*/
/************************************************************/
G_DrawLine(x0,y0,x1,y1)

int x0,y0,x1,y1;
{
	/* set memory parameters */
	*pX0L = (char)x0;
	*pX0H = (char)0;
	*pY0 = (char)y0;
	*pX1L = (char)x1;
	*pX1H = (char)0;
	*pY1 = (char)y1;
	
	/* do the call */
	#asm
	JSR DRAWLINE
	#endasm
}
	
/************************************************************/
/* G_DrawPoint(x0,y0):  Draw point, x0,y0 			 		*/
/************************************************************/
G_DrawPoint(x0,y0)

int x0,y0;
{
	/* set memory parameters */
	*pX0L = (char)x0;
	*pX0H = (char)0;
	*pY0 = (char)y0;
	
	/* do the call */
	#asm
	JSR DRAWPOINT
	#endasm
}

/************************************************************/
/* G_DrawLine(x0,y0,x1,x1):  Draw line, x0,y0 to x1,y1 		*/
/************************************************************/
G_FillRect(x0,y0,x1,y1)

int x0,y0,x1,y1;
{
	/* set memory parameters */
	*pX0L = (char)x0;
	*pX0H = (char)0;
	*pY0 = (char)y0;
	*pX1L = (char)x1;
	*pX1H = (char)0;
	*pY1 = (char)y1;
	
	/* do the call */
	#asm
	JSR FILLRECT
	#endasm
}

	