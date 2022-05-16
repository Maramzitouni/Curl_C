#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>

//gcc main.c -o main $(mysql_config --libs) -L/usr/local/opt/openssl/lib


typedef struct Data1{
    char datas[50];
    char name[255];
    char adress[50];
    char adressInput[50];
    char products[50];
    char product[50];
    char productInput[50];
    char phone[50];
    char phoneInput[50];
    char stock[50];
    char stockInput[50];
} Data1;



typedef struct _db_con
{
    char *server;
    char *username;
    char *password;
    char *database;
    MYSQL *conn;

}db_con;

//fonction ecriture fichier
int writeYaml1(Data1* data1){
    FILE* f = fopen("test.yaml", "a");
    if(f == NULL){
        return 1;
    }
    strcat(data1->name, ": ");
    fprintf(f,"%s%s\n%s%s\n%s\n%s%s\n%s%s\n%s%s\n",data1->name,data1->datas,data1->adress,data1->adressInput,data1->products,
            data1->product,data1->productInput,data1->stock,data1->stockInput,data1->phone,data1->phoneInput);

    return 0;
}

// fonction init bd
int initialisation_bd(db_con *db_cn){
    db_cn->server= "localhost";
    db_cn->username = "root";
    db_cn->password = "";
    db_cn->database = "projetC";
    db_cn->conn = mysql_init(NULL);
    if (mysql_real_connect(db_cn->conn, db_cn->server, db_cn->username, db_cn->password, db_cn->database, 0, NULL, 0) == NULL) {
        printf("Unable to connect with MySQL server\n");
        mysql_close(db_cn->conn);
        return 0;
    }

    return 1;

}

void fonction (db_con db,int*i);
// main

int main(int argc, char const *argv[]) {
    FILE* f = fopen("test.yaml", "a");
    fprintf(f,"%s\n","---");
    db_con db;
    int i =2;
    int j=3;
    initialisation_bd(&db);
    fonction (db,&i);
    fonction (db,&j);







    return EXIT_SUCCESS;
}


void fonction (db_con db,int* i){
    int j=2;
    MYSQL_ROW record;
    char buf5[1024] = {};
    Data1* data1 = malloc(sizeof(Data1));
    char query_string5[] = {"SELECT id,name,email FROM USERS where id = ('%d')"};
    sprintf(buf5, query_string5,*i);
            if (mysql_query(db.conn, buf5)) {
        printf("Unable to select table\n");
        mysql_close(db.conn);
        //break; dialog box show
    }

    MYSQL_RES *rs = mysql_store_result(db.conn);

    if (rs == NULL) {
        printf("Unable to compile SQL statement\n");
        mysql_close(db.conn);
        //break;
    }

    while (record = mysql_fetch_row(rs)) {
        strcpy(data1->name,"name");
        strcpy(data1->datas, record[1]);
        strcpy(data1->adress,"adresse: ");
        strcpy(data1->adressInput, record[1]);
        strcpy(data1->products,"products:");
        strcpy(data1->product," product: ");
        strcpy(data1->productInput, record[1]);
        strcpy(data1->stock," stock: ");
        strcpy(data1->stockInput, record[1]);
        strcpy(data1->phone,"phone: ");
        strcpy(data1->phoneInput,record[1]);
    }


    writeYaml1(data1);
    free(data1);

}
