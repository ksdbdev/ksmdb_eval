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

	if (argc == 1)
	{
		printf("students [C][O]\n");
		return 0;
	}
	if (argv[1][0] =='C')
	{
		if (studentdb.Create(".","qzh",1000000) == false)
		{
			studentdb.GetLastError(&errcode,errmsg);
			printf("errcode=%d,errmsg=%s\n",errcode,errmsg);
			return 0;
		}
		studentdb.UnLockDb();
	}
	else if (argv[1][0] == 'O')
	{
		if (studentdb.Open(".","qzh",READWRITE,3519,false,0) == false)
		{
			studentdb.GetLastError(&errcode,errmsg);
			printf("errcode=%d,errmsg=%s\n",errcode,errmsg);
			return 0;
		}
		studentdb.UnLockDb();
	}
	else
	{
		printf("students [C][O]\n");
		return 0;
	}
	studentdb.SetErrorHandle(myerrhandle);
	studentdb.LoadLicense("common.lic",errmsg);

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

	while (1)
	{
		if (grade.lists())
		{
			if (grade.end())
			{
				studentdb.BeginTransaction();
				grade.erase();
				studentdb.CommitTransaction();
			}
			studentdb.BeginTransaction();
			if (grade.find_by_nameclassroom("0","8",LARGE))
			{
				grade.end();
				while (1)
				{
					printf("%d\n",grade.get_id());
					if (grade.prev() == false)
						break;
				}
			}
			studentdb.CommitTransaction();
		}
		else
		{
			break;
		}
	}
	
	studentdb.GetMemoryInfo(size,inused);
	printf("size=%d,inused=%d\n",size,inused);
	getc(stdin);
	studentdb.BeginTransaction();
	grade.backup("grade.tb");
	studentdb.Reset();
	grade.load("grade.tb");
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

	grade.dump();
	printf("dbversion=%s\n",studentdb.DbVersion());
	printf("libversion=%s\n",studentdb.LibVersion());
	studentdb.GetMemoryInfo(size,inused);
	printf("size=%d,inused=%d\n",size,inused);
	getc(stdin);
	studentdb.Close();
	printf("closed\n");
	getc(stdin);
	return 0;
}
