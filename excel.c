#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "xlsxwriter.h"
//gcc main.c -o main -lxlsxwriter

// recuperer les données du fichier yaml et les mettre dans le fichier excel
void fonction(lxw_workbook  *workbook, lxw_worksheet *worksheet,FILE * pf);


int main()
{

    lxw_workbook  *workbook  = workbook_new("myexcel9.xlsx");

    lxw_worksheet *worksheet = workbook_add_worksheet(workbook, NULL);


    FILE * pf = fopen ("test.yaml", "rb");

    fonction(workbook,worksheet, pf);

    fclose(pf);

    return workbook_close(workbook);

}

void fonction(lxw_workbook  *workbook, lxw_worksheet *worksheet,FILE * pf){
    int row = 0;
    int col = 0;

    char line[500] = {0};
    char name1[30] = {0};
    char adress1[300] = {0};

    while ( fgets ( line, sizeof ( line) , pf)) {

        if ( ( sscanf ( line,"%29[^:]: %299[^\n]%*c"
                , name1
                , adress1
        )) == 2) {

            if (col<=4) {
                worksheet_write_string(worksheet, row+1, col, adress1, NULL);
                worksheet_write_string(worksheet, row, col, name1, NULL);
            }
            if (col>4 && col<=9){
                worksheet_write_string(worksheet, 2,col-5, adress1, NULL);
            }
            if (col>9){
                worksheet_write_string(worksheet, 3,col-10, adress1, NULL);
            }
            printf ( "%s\n", name1);
            printf ( "%s\n", adress1);
            col++;

        }
    }


}
