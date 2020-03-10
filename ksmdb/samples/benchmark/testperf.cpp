#include "perf.h"
#include <stdio.h>
#include <time.h>
#include <stdarg.h>
#if !defined(WIN32)
#include <sys/time.h>
#endif
#if defined(WIN32)
	#include <windows.h>
	#include <direct.h>
	#include <process.h>
	#include <stdlib.h>
	#include <io.h>
	#include <fcntl.h>
	#include <sys/stat.h>
#else
	#include <sys/types.h>
	#include <stdio.h>
	#include <fcntl.h>
	#include <signal.h>
	#include <errno.h>
	#include <sys/ioctl.h>  
	#include <signal.h>
	#define O_BINARY 0
	#include <sys/stat.h>
#ifdef SOLARIS
	#include <sys/termios.h>
#endif
#endif

typedef struct
{
    long sec;
	long nsec;
}XTIME;

void xtime_get(XTIME &xtp)
{
#ifdef WIN32
        FILETIME ft;
        GetSystemTimeAsFileTime(&ft);
        const __int64 TIMESPEC_TO_FILETIME_OFFSET =
            ((__int64)27111902UL << 32) +
            (__int64)3577643008UL;
        xtp.sec = (int)((*(__int64*)&ft - TIMESPEC_TO_FILETIME_OFFSET) /
            10000000);
        xtp.nsec = (int)((*(__int64*)&ft - TIMESPEC_TO_FILETIME_OFFSET -
                              ((__int64)xtp.sec * (__int64)10000000)) * 100);
		return;
#else
	#if defined(LINUX)
        struct timeval tv;
        gettimeofday(&tv, 0);
        xtp.sec = tv.tv_sec;
        xtp.nsec = tv.tv_usec * 1000;
	#else
		timespec ts;
		clock_gettime(CLOCK_REALTIME, &ts);
		xtp.sec = ts.tv_sec;
		xtp.nsec = ts.tv_nsec;
		return;
	#endif
#endif
}

//返回结果是us为单位的整数时间差
long  xtimemute(XTIME &b,XTIME &e)
{
	return (e.sec - b.sec)*1000*1000+(e.nsec - b.nsec)/1000;
}


bool myerrhandle(int errcode,char *errmsg)
{
	printf("my errhandle:errcode=%d,errmsg=%s\n",errcode,errmsg);
	return true;
}
#include <vector>
using namespace std;
int main(int argc,char **argv)
{
    DB_perf perf;
	long i,k,count,c;
	long size,inused;
    long dbsize = 1000*1024*1024;
	char errmsg[300];
	XTIME s,e;

    perf.Create(".","qzh",dbsize);
	TB_grade grade(perf.GetDBHandle());

	if (argv[1][0] == 'Q')
	{
		perf.Open(".","qzh",READONLY,3519,false,0);
	}else if (argv[1][0] == 'S')
	{
        perf.Open(".","qzh",READWRITE,3519,false,0,1);
	}
	else
	{
		perf.Open(".","qzh",READWRITE,3519,false,0);
	}
	perf.SetErrorHandle(myerrhandle);
	perf.UnLockDb();
	perf.LoadLicense("perf.lic",errmsg);

	count=1000000;

	if ((argv[1][0] == 'I') || (argv[1][0] == 'A') || (argv[1][0] == 'S'))
	{
		xtime_get(s);
		for (i=0; i<count; i++)
		{
			perf.BeginTransaction();
			grade.newrecord();
			grade.set_value(i);
			grade.append(i);
			perf.CommitTransaction();
		}
		xtime_get(e);
		c=xtimemute(s,e);
        double c_double= (double) c;
		printf("insert %d rows,spend %d ms,one row cost=%.2lf us\n",count,c/1000,c_double/count);
	}
	if ((argv[1][0] == 'Q') || (argv[1][0] == 'A') || (argv[1][0] == 'S'))
	{
		k=0;
		xtime_get(s);
		for (i=0; i<count; i++)
		{
			perf.BeginTransaction();
			if (grade.find_by_pkey(i))
			{
				k++;
			}
			perf.CommitTransaction();
		}
		xtime_get(e);
		c=xtimemute(s,e);
		double c_double= (double) c;
		printf("find %d times,spend %d ms,one row cost=%.2lf us\n",count,c/1000,c_double/count);


	}
	if ((argv[1][0] == 'U') || (argv[1][0] == 'A') || (argv[1][0] == 'S'))
	{
		k=0;
		xtime_get(s);
		for (i=0; i<count; i++)
		{
			perf.BeginTransaction();
			if (grade.find_by_pkey(i))
			{
				grade.set_value(i+i);
				k++;
			}
			perf.CommitTransaction();
		}
		xtime_get(e);
		c=xtimemute(s,e);
		double c_double= (double) c;
		printf("update %d rows,spend %d ms,one row cost=%.2lf us\n",count,c/1000,c_double/count);
	}
	perf.GetMemoryInfo(size,inused);
	printf("size=%d,inused=%d\n",size,inused);
	perf.Close();
	return 0;
}
