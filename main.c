#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <conio.h>
#include "fonksiyonlar.h"

int main()
{
    char secim[6][1] = {
                        {'*'},
                        {' '},
                        {' '},
                        {' '},
                        {' '},
                       };

    int menu_Konum = 1;
    int last_Konum = 0;

    char tus,tus2 = 'b';

    while(1)
    {
        bool menu_donusu;
        int secim_konum = 0;
        secim[menu_Konum][1] = '*';
        secim[last_Konum][1] = ' ';
        last_Konum = menu_Konum;

        if(last_Konum == 1 || last_Konum == 4)
        {
            secim[last_Konum][1] = '*';
        }

        printf("                 ``*...*``\n"
               "                   `***`\n"
               "                 ``*.|.*``\n"
               "                     |\n"
               "              _______n______\n"
               "             |              |\n"
               "             |      BAY     |\n"
               "             |    CESURLA   |\n"
               "             |     BOMBA    |\n"
               "             |   IMHA OYUNU |\n"
               "             |   Version 1  |\n"
               "             |______________|\n\n\n"

               );

        printf(" ----------MENU------------\n");
        printf(" Oyna     ---> %c\n",secim[1][1]);
        printf(" Hakkimda ---> %c\n",secim[2][1]);
        printf(" Oynanis  ---> %c\n",secim[3][1]);
        printf(" Exit     ---> %c\n",secim[4][1]);

        tus = getch();

        if((tus == 'w' || tus == 72) &&  menu_Konum > 1 )
        {
            menu_Konum -= 1;

        }else if((tus == 's' || tus == 80) && menu_Konum < 4)
        {
            menu_Konum += 1;

        }else if(tus == 13)   //Enter karakterinin ASCII kodu 13
        {
            secim_konum = menu_Konum;
            last_Konum = 1 + secim_konum;
        }else if(tus == 27)   //Esc karakterinin ASCII kodu 27
        {
            return 0;
        }else
        {
            last_Konum = 1 + secim_konum;
        }


        switch(secim_konum)
        {
            case 0:
                break;
            case 1:
                system("CLS");
                menu_donusu = oyna();

                if(!menu_donusu)
                {
                    while(tus2 != 27 && tus2 != 13)
                    {
                        tus2 = getch();
                    }
                    tus2 = 'b';
                }
                    break;

            case 2:
                system("CLS");
                hakkimda();
                while(tus2 != 27)
                {
                    bekle(10);
                    tus2 = getch();
                }
                tus2 = 'b';
                break;
            case 3:
                system("CLS");
                oynanis();
                while(tus2 != 27)
                {
                    bekle(10);
                    tus2 = getch();
                }
                tus2 = 'b';
                break;
            case 4:
                return 0;
        }

        system("CLS");

    }

    return 0;
}
