#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 
#include <string>

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int main(int argc, char* argv[]) {
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   const char *sql;

   /* Open database */
   rc = sqlite3_open("graph.db", &db);
   
   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   } else {
      fprintf(stderr, "Opened database successfully\n");
   }

   /* Create SQL statement */
   for (int i = 0; i < 10; ++i)
   {
      printf("%d\n", i);
      sql = "INSERT INTO node (name, frecuency) "  \
            "VALUES ('random', 1); " ;
      /* Execute SQL statement */
      rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
      
      /*if( rc != SQLITE_OK ){
         fprintf(stderr, "SQL error: %s\n", zErrMsg);
         sqlite3_free(zErrMsg);
      } else {
         fprintf(stdout, "Reccallbackord created successfully\n");
      }*/
   }



   sqlite3_close(db);
   return 0;
}