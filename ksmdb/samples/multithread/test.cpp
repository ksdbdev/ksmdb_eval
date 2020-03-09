#include "student.h"
#include "tools.h"
#include <stdio.h>
#if defined(WIN32)
#include <conio.h>
#endif


bool myerrhandle(int errcode,char *errmsg)
{
	printf("my errhandle:errcode=%d,errmsg=%s\n",errcode,errmsg);
	return true;
}



#ifdef WIN32
unsigned int _stdcall
#else
void *
#endif
wthread(void *arg)
{

	printf("readwrite thread  start.\n");

	int errcode;
	char errmsg[300];

	char name[20]={0};
	char room[20]={0};

	DB_student studentdb;

	if (studentdb.Open(".","studentdb",READWRITE,5000,false,1) == false)
	{
		studentdb.GetLastError(&errcode,errmsg);
		printf("errcode=%d,errmsg=%s\n",errcode,errmsg);
		return 0;
	}

	studentdb.UnLockDb();
	studentdb.SetErrorHandle(myerrhandle);

	TB_grade grade(studentdb.GetDBHandle());

	studentdb.BeginTransaction();

	for (int i=0; i<1000; i++)
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

	studentdb.Close();

	return 0;

}



#ifdef WIN32
unsigned int _stdcall
#else
void *
#endif
rthread(void *arg)
{

	printf("readolny thread  start.\n");

	//wait for data insert.
	printf("press any key to read data...\n");
    getchar();

	Sleep(1000);

	int errcode;
	char errmsg[300];

	DB_student studentdb;

	if (studentdb.Open(".","studentdb",READONLY,5000,false,1) == false)
	{
		studentdb.GetLastError(&errcode,errmsg);
		printf("errcode=%d,errmsg=%s\n",errcode,errmsg);
		return 0;
	}

	studentdb.UnLockDb();
	studentdb.SetErrorHandle(myerrhandle);

	TB_grade grade(studentdb.GetDBHandle());

	int i = 1;
	while (i<1000)
	{

		studentdb.BeginTransaction();
		if (!grade.find_by_pkey(i))
		{
			studentdb.CommitTransaction();
			continue;;
		}
		printf("FindById:  id=%d,name=%s,classroom=%s,math=%4.1f,chinese=%4.1f,english=%4.1f\n",
			grade.get_id(),grade.get_name(),grade.get_classroom(),
			grade.get_math(),grade.get_Chinese(),grade.get_english());

		studentdb.CommitTransaction();

		i++;

	}

	studentdb.Close();

	return 0;

}



int main(int argc,char **argv)
{
	DB_student studentdb;
	long size,inused;
	int errcode;

	char errmsg[300];



	if (studentdb.Create(".","studentdb",200000000) == false)
	{
		studentdb.GetLastError(&errcode,errmsg);
		printf("errcode=%d,errmsg=%s\n",errcode,errmsg);
		return 0;
	}
	studentdb.UnLockDb();
	studentdb.SetErrorHandle(myerrhandle);

	printf("database is created.\n");

	THREAD_HANDLE t_handle_w;
	create_thread(&t_handle_w, wthread, NULL);

	THREAD_HANDLE t_handle_r;
	create_thread(&t_handle_r, rthread, NULL);

    join_thread(t_handle_w);
	join_thread(t_handle_r);


	studentdb.GetMemoryInfo(size,inused);
	printf("size=%d,inused=%d\n",size,inused);
	studentdb.Close();
	printf("database is closed.\n");
	printf("press any key to quit...\n");

	getc(stdin);
	return 0;
}
