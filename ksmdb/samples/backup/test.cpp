#include "student.h"
#include <stdio.h>
#if defined(WIN32)
#include <conio.h>
#endif
bool myerrhandle(int errcode,char *errmsg)
{
	printf("my errhandle:errcode=%d,errmsg=%s\n",errcode,errmsg);
	return true;
}

int main(int argc,char **argv)
{
	DB_student studentdb;
	long size,inused;
	int errcode;
	int i;
	char errmsg[300];
	char name[20];
	char room[20];

	if (studentdb.Create(".","qzh",1000000) == false)
	{
		studentdb.GetLastError(&errcode,errmsg);
		printf("errcode=%d,errmsg=%s\n",errcode,errmsg);
		return 0;
	}
	studentdb.UnLockDb();

	studentdb.SetErrorHandle(myerrhandle);

	printf("database is created.\n");

	TB_grade grade(studentdb.GetDBHandle());

	studentdb.BeginTransaction();

	for (i=0; i<100; i++)
	{
		grade.newrecord();
		grade.set_math(i);
		grade.set_Chinese(i);
		grade.set_english(i);
		sprintf(name,"%d",i % 10);
		sprintf(room,"%d",i % 10);
		grade.append(i,name,room);
	}
	studentdb.CommitTransaction();
	printf("insert data into table succeed.\n");

	studentdb.GetMemoryInfo(size,inused);
	printf("database size=%d,inused=%d\n",size,inused);
	studentdb.BeginTransaction();
	grade.backup("grade.tb");
	printf("table backup succeed.\n");
	printf("press any key to continue...\n");
	getc(stdin);
	studentdb.Reset();
	grade.load("grade.tb");
	printf("table load succeed.\n");

	studentdb.CommitTransaction();

	studentdb.BeginTransaction();
	if (grade.find_by_nameindex("12",LARGE_EQ))
	{
		grade.end();
		do 
		{
			printf("FindById:  id=%d,name=%s,classroom=%s,math=%4.1f,chinese=%4.1f,english=%4.1f\n",
				grade.get_id(),grade.get_name(),grade.get_classroom(),
				grade.get_math(),grade.get_Chinese(),grade.get_english());
		}while(grade.prev());
	}
	else
	{
		printf("not found\n");
	}
	studentdb.CommitTransaction();

	studentdb.GetMemoryInfo(size,inused);
	printf("size=%d,inused=%d\n",size,inused);
	studentdb.Close();
	printf("database is closed.\n");
	printf("press any key to quit...\n");

	getc(stdin);
	return 0;
}
