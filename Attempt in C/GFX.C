#include stdio.h

#include "GFX.H"
/*#include "GUTIL.H"*/
int getch();

main()
{
	int c,i,j;
	
	pt("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nSteve's Test Program");

	pt("Initializing graphics");
	G_Init();

	G_DispScrnSet(1, 0);
	
	pt("Setting draw screen 1");
	G_DrawScrnSet(1);

	pt("Setting color");
	G_SetColor(0);

	pt("Clear Screen");
	G_ScrnClear();
	
	pt("Setting color");
	G_SetColor(3);
/*	
	pt("Drawing Point");
	G_DrawPoint(14,14);
*/
	pt("Drawing Lines");
	
	G_DrawLine(0,90,180,95);
	G_DrawLine(90,0,90,90);
	G_DrawLine(0,0,180,180);
	G_DrawLine(180,180,0,0);
	
	
	
	
	/*
	for (i = 0; i< 180; i+=7)
	{
		G_DrawLine(0,i,180,180-i);
	}

	pt("Clear Screen");
	G_ScrnClear();
	
	pt("Drawing Lines");
	
	for (i = 0; i< 180; i+=10)
	{
		G_DrawLine(i,0,180-i,180);
	}
	*/
	
	pt("And we're done!");

	exit(0);
 
}

pt(psz)

char *psz;
{
	int c;
	
	printf(psz);
	printf(": hit a key");
	c = getch();
	printf("\n");

}
