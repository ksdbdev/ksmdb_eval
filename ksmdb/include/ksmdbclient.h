/*********************************************************************************
  *Copyright(C),2008 - 2020  Kingstar
  *FileName:  ksmdbclient.h
  *Author:  钱正华
  *Version: KSMDB V2.3
  *Description:  
     内存库客户端API接口。


  *History: 
     1.Date: 2008.1
       Author: 钱正华
       Modification: 创建文件
	   
**********************************************************************************/ 

#ifndef __KSMDBCLI_H
#define __KSMDBCLI_H
#include "cachet.h"

typedef void* KSMDBCLIHANDLE;

#ifdef __cplusplus
extern "C" {
#endif

KSMDBCLIHANDLE KsCreate();
void KsFree(KSMDBCLIHANDLE handle);
bool KsConnect(KSMDBCLIHANDLE handle,char *ip,int port);
void KsClose(KSMDBCLIHANDLE handle);
bool KsQueryDb(KSMDBCLIHANDLE handle);
bool KsQueryDbTransInfo(KSMDBCLIHANDLE handle);
bool KsGetDbName(KSMDBCLIHANDLE handle,char *name,int size);
bool KsGetCodeVersion(KSMDBCLIHANDLE handle,char *version,int size);
bool KsGetDbVersion(KSMDBCLIHANDLE handle,char *version,int size);
KSINT8 KsGetDbSize(KSMDBCLIHANDLE handle);
KSINT8 KsGetFreeSize(KSMDBCLIHANDLE handle);
int  KsGetTableCount(KSMDBCLIHANDLE handle);
bool KsGetTbName(KSMDBCLIHANDLE handle,int tableid,char *name, int size);
int  KsGetTbColCount(KSMDBCLIHANDLE handle,int tableid);
KSINT8 KsGetTbSize(KSMDBCLIHANDLE handle,int tableid);
int  KsGetTbInxCount(KSMDBCLIHANDLE handle,int tableid);
bool KsGetTbColName(KSMDBCLIHANDLE handle,int tableid,int colid,char *name,int size);
int  KsGetTbColType(KSMDBCLIHANDLE handle,int tableid,int colid);
int  KsGetTbColLength(KSMDBCLIHANDLE handle,int tableid,int colid);
int  KsGetTbColDeciaml(KSMDBCLIHANDLE handle,int tableid,int colid);
int  KsGetTbIdxColCount(KSMDBCLIHANDLE handle,int tableid,int indexid);
int  KsGetTbIdxType(KSMDBCLIHANDLE handle,int tableid,int indexid);
int  KsGetTbIdxColId(KSMDBCLIHANDLE handle,int tableid,int indexid,int indexcolid);
int  KsQueryTb(KSMDBCLIHANDLE handle,int tableid);
int  KsGetRecord(KSMDBCLIHANDLE handle);
int  KsGetRecordId(KSMDBCLIHANDLE handle);
bool KsGetRecordCol(KSMDBCLIHANDLE handle,int colid,char *value,int size);
bool KsInitRecord(KSMDBCLIHANDLE handle,int tableid,int colcount,int recordid);
bool KsSetRecordCol(KSMDBCLIHANDLE handle,int colid,char *value);
int  KsAddRecord(KSMDBCLIHANDLE handle,int *errcode,char *errmsg);
bool KsUpdateRecord(KSMDBCLIHANDLE handle,int *errcode,char *errmsg);
bool KsDeleteRecord(KSMDBCLIHANDLE handle,int tableid,int recordid,int *errcode,char *errmsg);
bool KsBackupDatabase(KSMDBCLIHANDLE handle,char *filename,int *errcode,char *errmsg);
bool KsRestoreDatabase(KSMDBCLIHANDLE handle,char *filename,int *errcode,char *errmsg);
bool KsBackupTable(KSMDBCLIHANDLE handle,int tableid,char *filename,int *errcode,char *errmsg);
bool KsRestoreTable(KSMDBCLIHANDLE handle,int tableid,char *filename,int *errcode,char *errmsg);
bool KsResetDatabase(KSMDBCLIHANDLE handle,int *errcode,char *errmsg);

//zhb, 2017.11.21, kdmdb2.3
bool KsCliClearWildTrans(KSMDBCLIHANDLE handle, unsigned long stype, unsigned long pid, unsigned long tid, int *errcode,char *errmsg);
bool KsCliClearDBWildTrans(KSMDBCLIHANDLE handle, int *errcode,char *errmsg);

#ifdef __cplusplus
}
#endif

#endif
