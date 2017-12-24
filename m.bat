del *.bin
c65 HW.C
c65 GRAF.C
LN65 +B +H 2000,4004 HW.R GRAF.R -ld -lg3 -ls -lm -ld -lg3 -ls -lm
MAKEPRG2 hw hw.bin
del *.r
del hw
rename hw.prg hw.bin
