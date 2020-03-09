#ifndef __perf_HH
#define __perf_HH
#include "cache.h"
#include <string.h>
class DB_perf
{
private:
	bool m_inited;
	KsDbHandle m_database;
public:
	DB_perf();
	virtual ~DB_perf(){};
	bool Create(char *path,char *name,long size);
	bool Open(char *path,char *name,int mode,int port,bool isolate, int reuse_shmmap, int shmrcset_mode=0);
	void UnLockDb();
	void SetErrorHandle(KsErrorHandle handle);
	int  GetCols(KsRecordHandle handle);
	char *GetColName(KsRecordHandle handle,int col);
	int  GetColType(KsRecordHandle handle,int col);
	int  GetColSize(KsRecordHandle handle,int col);
	int  GetColDecimal(KsRecordHandle handle,int col);
	char *GetColData(KsRecordHandle handle,int col);
	void GetMemoryInfo(long &size,long &inused);
	void Reset();
	bool Backup(char *filename);
	bool Load(char *filename);
	void BeginTransaction();
	void RollbackTransaction();
	void CommitTransaction();
	void GetLastError(int *errcode,char *errmsg);
	bool LoadLicense(char *licensefilename,char *errmsg);
	void GetLicenseInfo(int &controlexpitedate,int &expitedate,int &controltransactioncount,long &transactioncount,int &delay);
	void Close();
	char *LibVersion();
	char *DbVersion();
	KsDbHandle GetDBHandle();
};

class TB_grade
{
private:
	KsDbHandle m_database;
public:
	KsRecordHandle m_record;
	KsConditionHandle m_condition;
public:
	TB_grade(KsDbHandle database);
	TB_grade(TB_grade &V);
	virtual ~TB_grade();
	bool newrecord();
	bool append(int id);
	bool erase();
	bool first();
	bool prev();
	bool next();
	bool end();
	bool gotorow(int rowid);
	int  recordrowid();
	bool dump(char *filename="grade");
	bool SaveTXT(char *filename="grade.txt");
	bool LoadTXT(char *filename="grade.txt");
	bool SaveBinary(char *filename="grade.txt");
	bool LoadBinary(char *filename="grade.txt");
	bool backup(char *filename="grade");
	bool load(char *filename="grade");
	int  get_id();
	bool set_value(int value);
	int  get_value();
	bool find_by_pkey(int id,int op=EQ);
	bool lists();
	bool list_by_pkey();
};

#endif
