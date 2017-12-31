del *.bin
c65 GFX.C
c65 GUTIL.C
echo LN65 +B +H 2000,6004 GFX.R GUTIL.R -ld -lg3 -ls -lm -ld -lg3 -ls -lm
LN65 +B +H 4000,6004 GFX.R GUTIL.R -ld -lg3
MAKEPRG2 GFX GFX.BIN
del *.r
rename GFX.prg G#060800.BIN
