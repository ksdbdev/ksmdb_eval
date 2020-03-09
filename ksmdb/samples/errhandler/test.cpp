#include "student.h"
#include <stdio.h>
#if defined(WIN32)
#include <conio.h>
#endif

/////////////////////////////////////////////////////////////////////////////////
//
// ksmdb错误处理：
//
//    用户自定义错误处理函数，通过SetErrorHandle方法注册到ksmdb内核。
//    ksmdb内核发生错误时，如果没有注册错误处理函数，会把错误信息打印到标准输出；
//    如果注册了错误处理函数，会调用用户自定义错误处理函数。
//
bool myerrhandle(int errcode,char *errmsg)
{
	static bool wait = true;
	printf("ksmdb  runtime error: errcode=%d,errmsg=%s\n",errcode,errmsg);
	if (wait == true)
	{
		printf("press any key to continue...\n");
		getchar();
		wait = false;
	}
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

	for (i=0; i<3000; i++)
	{
		grade.newrecord();
		grade.set_math(i);
		grade.set_Chinese(i);
		grade.set_english(i);
		sprintf(name,"%d",i % 10);
		sprintf(room,"%d",i % 10);

		//will trigger error and call user defined errorhandler.
		grade.append(i,name,room);
	}
	studentdb.CommitTransaction();

	studentdb.GetMemoryInfo(size,inused);
	printf("database size=%d,inused=%d\n",size,inused);

	studentdb.GetMemoryInfo(size,inused);
	printf("size=%d,inused=%d\n",size,inused);
	studentdb.Close();
	printf("database is closed.\n");
	printf("press any key to quit...\n");

	getc(stdin);
	return 0;
}
