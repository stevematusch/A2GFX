********************************
*                              *
* Bunch of bogus graphics      *
* By Steve Matusch             *
*							   *
* Developed with Merlin-32     *
*                              *
********************************

* Arguments
*in_arg   ds    1          ;generic argument
*in_x0l   ds    1          ;X coordinate 0, low part
*in_x0h   ds    1          ;X coordinate 0, high part
*in_y0    ds    1          ;Y coordinate 0
*in_x1l   ds    1
*in_x1h   ds    1
*in_y1    ds    1
*in_rad   ds    1          ;radius for circles

*Routines
*   SetColor
*   SetPage
*   Clear
*   DrawPoint
*   DrawLine
*   DrawRect
*   FillRect
*   DrawCircle
*   FillCircle
*   SetLineMode
*   FillRaster



********************************
*
* Do nothing right now
*
********************************
TXTCLR 	EQU		$c050	;enable graphics
TXTSET 	EQU 	$c051	;text-only
MIXCLR	EQU		$c052	;disable mixed mode
MIXSET	EQU		$c053	;enable mixed mode (4 lines of text)
LOWSCR	EQU		$c054	;display page 1
HISCR	EQU		$c055	;display page 2
LORES	EQU		$c056	;show lo-res screen
HIRES	EQU		$c057	;show hi-res screen


Main
         jsr	Init	;Init graphics
		 
		 lda	#$00	;Draw screen 0
		 sta	in_arg
		 jsr	SetPage
		 
		 bit	TXTCLR	; Set Display screen 0
		 bit	MIXSET
		 bit	HIRES
		 bit	LOWSCR
		 
		 jsr	Clear	; Clear Screen
		 
		 lda	#$3		; Set White
		 sta	in_arg
		 jsr	SetColor
		 
		 lda	#0		; Draw a white line
		 sta	in_x0l
		 sta	in_x0h
		 sta	in_y0
		 sta	in_x1h
		 lda	#80
		 sta	in_x1l
		 sta	in_y1
		 jsr	DrawLine
		 
		 lda	#5		; Set Red
		 sta	in_arg

		 ldx	#0		; Draw a red circle
		 lda	#100	
		 ldy	#25
		 stx	in_x0h
		 sta	in_x0l
		 sta	in_y0
		 sty	in_rad
		 jsr	DrawCircle
		 
		 rts


