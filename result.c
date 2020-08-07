#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<my_global.h>
#include<mysql.h>
#include<math.h>

long int p,q,n,t,flag,e[100],d[100],temp[100],j,i;
char en[100];
char m[100];
char msg[100];
int prime(long int);
void ce();
long int cd(long int);
void encrypt();
void decrypt();


void finish_with_error(MYSQL*con)
{
	fprintf(stderr, "%s\n" , mysql_error(con));
	mysql_close(con);
	exit(1);
}
int main(int argc , char * argv[])
{
	MYSQL * con = mysql_init(NULL);
	if(con==NULL)
	{
		fprintf(stderr , "mysql_init() failed\n");
		exit(1);
	}
	 if (mysql_real_connect(con, "localhost", "ccnteam", "Ccn123!@#","pollbooth", 0, NULL, 0) == NULL)
                {
                        finish_with_error(con);
                }
	 if (mysql_query(con, "Select * FROM Voting"))
  {
      finish_with_error(con);
  }
	 MYSQL_RES *result = mysql_store_result(con);
	 if (result == NULL)
  {
	  printf("error\n");
      finish_with_error(con);
  }

  int num_fields = mysql_num_fields(result);

  MYSQL_ROW row;
  while ((row = mysql_fetch_row(result)))
  {
	p=23,q=17;	
	  strcpy(en,row[2]);
	    n=p*q;
        t=(p-1)*(q-1);
	     ce();
encrypt();
	  decrypt();

	  printf("%s", m ? m : "NULL");
  }


  mysql_free_result(result);
  mysql_close(con);

  exit(0);
}
void encrypt()
{
  long int pt, ct, key = e[0], k, len;
  i = 0;
  len = strlen(en);
  while(i != len)
  {
    pt = m[i];
    pt = pt - 96;
    k = 1;
    for(j = 0; j < key; j++)
    {
     k = k * pt;
     k = k % n;
    }
   temp[i] = k;
   ct = k + 96;
   i++;
  }
}
void decrypt()
{
  long int pt, ct, key = d[0], k;
  i = 0;
  while(en[i] != -1)
  {
    ct = temp[i];
    k = 1;
    for(j = 0; j < key; j++)
    {
      k = k * ct;
      k = k % n;
    }
   pt = k + 96;
   m[i] = pt;
   i++;
  }
  m[i] = -1;
}
void ce()
{
        int k;
        k=0;
        for (i=2;i<t;i++)
        {
                if(t%i==0)
                continue;
                flag=prime(i);
                if(flag==1&&i!=p&&i!=q)
                {
                        e[k]=i;
                        flag=cd(e[k]);
                        if(flag>0)
                        {
                                d[k]=flag;
                                k++;
                        }
                        if(k==99)
                                break;
                }
        }
}
long int cd(long int x)
{
        long int k=1;
        while(1)
        {
                k=k+t;
                if(k%x==0)
                        return(k/x);
        }
}
int prime(long int pr) {
int i;
j=sqrt(pr);
for (i=2;i<=j;i++)
{
        if(pr%i==0)
        return 0;
}
        return 1;
}



