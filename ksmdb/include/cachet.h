/*********************************************************************************
  *Copyright(C),2008 - 2020  Kingstar
  *FileName:  cachet.h
  *Author:  钱正华
  *Version: KSMDB V2.3
  *Description:  
     内存库内核预定义类型。


  *History: 
     1.Date: 2008.1
       Author: 钱正华
       Modification: 创建文件
	   
**********************************************************************************/ 
#ifndef _CACHE_T_H
#define _CACHE_T_H

#define KSTYPE_INT2		1
#define KSTYPE_INT4		2
#define KSTYPE_CHAR		3
#define KSTYPE_UINT2	4
#define KSTYPE_UINT4	5
#define KSTYPE_UCHAR	6
#define KSTYPE_STRING	7 
#define KSTYPE_DOUBLE   8
#define KSTYPE_INT8		9

#define UNIQUE_INDEX	1
#define NONUNIQUE_INDEX 2

typedef short	KSINT2;
typedef int		KSINT4;
typedef char    KSCHAR;
typedef unsigned short	KSUINT2;
typedef unsigned int	KSUINT4;
typedef unsigned char   KSUCHAR;
typedef char*   KSSTRING;

#if defined(PLATFORM24)
	typedef long KSINT8
#else
	#if defined(WIN32)
		typedef __int64 KSINT8;
	#else
		typedef long long KSINT8;
	#endif
#endif

typedef void *KsDbHandle;
typedef void *KsRecordHandle;
typedef void *KsConditionHandle;

#define KS_DBERR_TRANSACTION_NOT_FINISH		-1001
#define KS_DBERR_TRANSACTION_NOT_OPEN		-1002
#define KS_DBERR_NO_MEMORY					-1003
#define KS_DBERR_NOT_ALLOW_MODIFY			-1004
#define KS_DBERR_DEADLOCK					-1005
#define KS_DBERR_SINGLE						-1006
#define KS_DBERR_COMP_NOT_SUPPORT			-1007
#define KS_DBERR_IO							-1008
#define KS_DBERR_UNIQUE_TREE				-1009
#define KS_DBERR_VERSION					-1010
#define KS_DBERR_AUTHORIZATION_EXPIRED		-1011

#define LESS			1
#define LESS_EQ			2
#define EQ				3
#define LARGE_EQ		4
#define LARGE			5

#define READONLY		1
#define READWRITE		2

typedef bool (* KsErrorHandle)(int errcode,char *errmsg);

#endif
