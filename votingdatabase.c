#include<stdio.h>
// #include<my_global.h>
#include<mysql.h>
#include<stdlib.h>
void error(MYSQL *con)
{
	fprintf(stderr, "%s\n" , mysql_error(con));
	mysql_close(con);
	exit(1);
}
int main(int argc, char ** argv)
{
	MYSQL * con = mysql_init(NULL);
	if(con==NULL)
	{
		fprintf(stderr, "%s\n" , mysql_error(con));
		exit(1);
	}
	if(mysql_real_connect(con,"localhost","ccnpro","Ccn!@#123",NULL,0,NULL,0) ==NULL)
	{
		error(con);
	}
	if(mysql_query(con, "CREATE DATABASE pollbooth"))
	{
		error(con);
	}
	mysql_close(con);
	exit(0);
}
