/*********************************************************************************
  *Copyright(C),2008 - 2020  Kingstar
  *FileName:  cache.h
  *Author:  Ǯ����
  *Version: KSMDB V2.3
  *Description:
	 �ڴ���ں˽ӿڡ�


  *History:
	 1.Date: 2008.1
	   Author: Ǯ����
	   Modification: �����ļ�

	 2.Date: 2019.12
	   Author: ����
	   Modification: ʵ�ֶ��̹߳������ӳ��ռ�Ľӿ�

**********************************************************************************/

#ifndef _CACHE_H
#define _CACHE_H

#include <stdio.h>
#include "cachet.h"
#ifdef __cplusplus
extern "C" {
#endif

	bool KsCreateDb(KsDbHandle *database,char *path,char *name,char *version, size_t size, int dbsesion_mode=0);
	bool KsOpenDb(KsDbHandle *database,char *path,char *name,char *version,int mode,int port,bool isolate, 
		int reuse_shmmap,int shmrcset_mode=0, int dbsesion_mode=0);
	void KsDeleteDb(KsDbHandle database);
	void KsSaveDbInfo(KsDbHandle database);
	void KsLoadDbInfo(KsDbHandle database);
	void KsLoadDb(KsDbHandle database);
	void KsResetDb(KsDbHandle database);
	void KsCreateRecord(KsRecordHandle *recordrow);
	void KsCloseRecord(KsDbHandle database,KsRecordHandle recordrow);
	void KsCreateCondition(int fieldcount,KsConditionHandle *condition);
	void KsCloseCondition(KsConditionHandle condition);
	void KsSetConditionIndex(KsConditionHandle condition,int index);
	void KsAddConditionIndexItem(KsConditionHandle condition,int type,int len,char *p);
	void KsAddTable(KsDbHandle database, char *name);
	void KsAddField(KsDbHandle database, int tableid, char *name, int type, int length,int decimal);
	void KsAddIndex(KsDbHandle database, int tableid, char *name, int indextype);
	void KsAddIndexField(KsDbHandle database,int tableid,int indexid,int fieldid);
	bool KsNewRecord(KsDbHandle database,int tableid,KsRecordHandle recordrow);
	bool KsPutRecord(KsDbHandle database,KsRecordHandle record);
	void KsDeleteRecord(KsDbHandle database,KsRecordHandle record);
	int  KsGetRecordId(KsDbHandle database,KsRecordHandle record);
	bool KsGotoRecord(KsDbHandle database,int tableid,int rowid,KsConditionHandle condition);
	bool KsListRecord(KsDbHandle database,int tableid,KsConditionHandle condition);
	bool KsFindRecord(KsDbHandle database,int tableid,KsConditionHandle condition,int op);
	bool KsGetRecord(KsDbHandle database,KsConditionHandle condition,KsRecordHandle recordrow);
	bool KsSetField(KsDbHandle database,KsRecordHandle record,int fieldid,char *data);
	char *KsGetField(KsDbHandle database,KsRecordHandle record,int fieldid,int &fieldtype);
	bool KsNextRecord(KsDbHandle database,KsConditionHandle condition);
	bool KsPrevRecord(KsDbHandle database,KsConditionHandle condition);
	bool KsFirstRecord(KsDbHandle database,KsConditionHandle condition);
	bool KsLastRecord(KsDbHandle database,KsConditionHandle condition);
	void KsGetError(KsDbHandle database,int &errcode,char *errmsg);
	void KsSetErrorHandle(KsDbHandle database,KsErrorHandle handle);
	bool KsDumpTable(KsDbHandle database,int tableid,char *filename);
	int  KsGetCols(KsDbHandle database,KsRecordHandle record);
	char *KsGetColName(KsDbHandle database,KsRecordHandle record,int col);
	int  KsGetColType(KsDbHandle database,KsRecordHandle record,int col);
	int  KsGetColSize(KsDbHandle database,KsRecordHandle record,int col);
	int  KsGetColDecimal(KsDbHandle database,KsRecordHandle record,int col);
	char *KsGetColData(KsDbHandle database,KsRecordHandle record,int col);
	void KsMemoryInfo(KsDbHandle database, size_t *size, size_t *used);
	bool KsWriteDbDir(KsDbHandle database,char * path);
	bool KsReadDbDir(KsDbHandle database,char * path);
	bool KsWriteDbTable(KsDbHandle database,int tableid,char * tablefile);
	bool KsReadDbTable(KsDbHandle database,int tableid,char * tablefile);
	bool KsWriteDbFile(KsDbHandle database,char * filename);
	bool KsReadDbFile(KsDbHandle database,char * filename);
	void KsBeginTransaction(KsDbHandle database);
	void KsRollbackTransaction(KsDbHandle database);
	void KsCommitTransaction(KsDbHandle database);
	bool KsLockDb(KsDbHandle database,int mode);
	void KsUnLockDb(KsDbHandle database);
	char *KsGetLibVersion();
	char *KsGetDbVersion(KsDbHandle database);
	void KsTableSize(KsDbHandle database,int tableid,long &count,long &size);
	void KsDupRecord(KsRecordHandle srecordrow,KsRecordHandle drecordrow);
	void KsDupCondition(KsConditionHandle scondition,KsConditionHandle dcondition);
    bool KsWriteTableCsv(KsDbHandle database, int tableid, char *filename);
    bool KsReadTableCsv(KsDbHandle database, int tableid, KsRecordHandle recordrow, char *filename);
	bool KsWriteTableTxt(KsDbHandle database,int tableid,char *filename);
	bool KsReadTableTxt(KsDbHandle database,int tableid,KsRecordHandle recordrow,char *filename);
	bool KsWriteTableBinary(KsDbHandle database,int tableid,char *filename);
	bool KsReadTableBinary(KsDbHandle database,int tableid,KsRecordHandle recordrow,char *filename);
	bool KsClearWildTrans(KsDbHandle database, int stype, unsigned long pid, unsigned long tid);
	bool KsClearDBWildTrans(KsDbHandle database);

#ifdef __cplusplus
}
#endif

#endif
