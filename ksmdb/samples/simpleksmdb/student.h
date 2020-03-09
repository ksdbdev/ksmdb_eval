#ifndef __student_HH
#define __student_HH
#include "cache.h"
#include <string.h>
class DB_student
{
private:
	bool m_inited;
	KsDbHandle m_database;
public:
	DB_student();
	virtual ~DB_student(){};
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
	bool append(int id,char* name,char* classroom);
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
	char* get_name();
	char* get_classroom();
	bool set_math(double value);
	double get_math();
	bool set_Chinese(double value);
	double get_Chinese();
	bool set_english(double value);
	double get_english();
	bool find_by_pkey(int id,int op=EQ);
	bool find_by_nameindex(char* name,int op=EQ);
	bool find_by_classroom(char* classroom,int op=EQ);
	bool find_by_nameclassroom(char* name,char* classroom,int op=EQ);
	bool lists();
	bool list_by_pkey();
	bool list_by_nameindex();
	bool list_by_classroom();
	bool list_by_nameclassroom();
};

#endif
