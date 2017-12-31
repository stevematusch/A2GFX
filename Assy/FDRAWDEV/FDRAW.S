********************************
*                              *
* Fast Apple II Graphics       *
* By Andy McFadden             *
* Version 0.3, Aug 2015        *
*                              *
* Main source file             *
*                              *
* Developed with Merlin-16     *
*                              *
* Butchered by Steve Matusch   *
* Using Merlin-32              *
********************************


* Set to 1 to build FDRAW.FAST, set to zero to
* build FDRAW.SMALL.
USE_FAST equ   1

* Set to 1 to turn on beeps/clicks for debugging.
NOISE_ON equ   0


         lst   off
         org   $0800	;Usual Spot

*
* Macros.
*
spkr     equ   $c030
bell     equ   $ff3a

* If enabled, click the speaker (changes flags only).
CLICK    mac
         do    NOISE_ON
         bit   spkr
         fin
         <<<
* If enabled, beep the speaker (scrambles regs).
BEEP     mac
         do    NOISE_ON
         jsr   bell
         fin
         <<<
* If enabled, insert a BRK.
BREAK    mac
         do    NOISE_ON
         brk   $99
         fin
         <<<


* include the FDRAW functions
         put   FDRAW

* include the circle functions
         put   FDRAW.CIRCLE

         lst   on
CODE_END equ   *          ;end of code section
         lst   off

* include the data tables
         put   FDRAW.TABLES

         lst   on
DAT_END  equ   *          ;end of data / BSS
         lst   off

* Save the appropriate object file.
         do    USE_FAST
         sav   FDRAW.FAST
         else
         sav   FDRAW.SMALL
         fin
