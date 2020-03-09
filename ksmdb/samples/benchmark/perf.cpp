#include "perf.h"
DB_perf::DB_perf()
{
	m_inited = false;
	m_database = NULL;
}

bool DB_perf::Create(char *path,char *name,long size)
{
	if(m_inited)
	{
		return true;
	}
	m_inited=true;
	if (KsCreateDb(&m_database,path,name,"20200227-12:32:18:000",size) == true)
	{
		KsAddTable(m_database,"grade");
		KsAddField(m_database,0,"id",KSTYPE_INT4,4,-1);
		KsAddField(m_database,0,"value",KSTYPE_INT4,4,-1);
		KsAddIndex(m_database,0,"pkey",UNIQUE_INDEX);
		KsAddIndexField(m_database,0,0,0);
		KsSaveDbInfo(m_database);
	}
	else
	{
		m_inited=false;
		return false;
	}
	KsLoadDb(m_database);
	return true;
};

bool DB_perf::Open(char *path,char *name,int mode,int port,bool isolate,int reuse_shmmap, int shmrcset_mode)
{
	if(m_inited)
	{
		return true;
	}
	m_inited=true;
	if (KsOpenDb(&m_database,path,name,"20200227-12:32:18:000",mode,port,isolate, reuse_shmmap, shmrcset_mode) == true)
	{
		KsLoadDbInfo(m_database);
	}
	else
	{
		m_inited=false;
		return false;
	}
	KsLoadDb(m_database);
	return true;
};

void DB_perf::UnLockDb()
{
	KsUnLockDb(m_database);
}

void DB_perf::SetErrorHandle(KsErrorHandle handle)
{
	KsSetErrorHandle(m_database,handle);
}

int DB_perf::GetCols(KsRecordHandle handle)
{
	return KsGetCols(m_database,handle);
}

char *DB_perf::GetColName(KsRecordHandle handle,int col)
{
	return KsGetColName(m_database,handle,col);
}

int DB_perf::GetColType(KsRecordHandle handle,int col)
{
	return KsGetColType(m_database,handle,col);
}

int DB_perf::GetColSize(KsRecordHandle handle,int col)
{
	return KsGetColSize(m_database,handle,col);
}

int DB_perf::GetColDecimal(KsRecordHandle handle,int col)
{
	return KsGetColDecimal(m_database,handle,col);
}

char *DB_perf::GetColData(KsRecordHandle handle,int col)
{
	return KsGetColData(m_database,handle,col);
}

void DB_perf::GetMemoryInfo(long &size,long &inused)
{
	KsMemoryInfo(m_database,&size,&inused);
}

void DB_perf::Reset()
{
	KsResetDb(m_database);
}

bool DB_perf::Backup(char *filename)
{
	return KsWriteDbFile(m_database,filename);
}

bool DB_perf::Load(char *filename)
{
	return KsReadDbFile(m_database,filename);
}

void DB_perf::BeginTransaction()
{
	KsBeginTransaction(m_database);
}

void DB_perf::RollbackTransaction()
{
	KsRollbackTransaction(m_database);
}

void DB_perf::CommitTransaction()
{
	KsCommitTransaction(m_database);
}

void DB_perf::GetLastError(int *errcode,char *errmsg)
{
	KsGetError(m_database,*errcode,errmsg);
}

bool DB_perf::LoadLicense(char *licensefilename,char *errmsg)
{
	 return KsDbLoadLicense(licensefilename,errmsg);
}

void DB_perf::GetLicenseInfo(int &controlexpitedate,int &expitedate,int &controltransactioncount,long &transactioncount,int &delay)
{
	KsDbGetLicenseInfo(&controlexpitedate,&expitedate,&controltransactioncount,&transactioncount,&delay);
}

void DB_perf::Close()
{
	KsDeleteDb(m_database);
	m_inited=false;
}

char* DB_perf::LibVersion()
{
	return KsGetLibVersion();
}

char* DB_perf::DbVersion()
{
	return KsGetDbVersion(m_database);
}

KsDbHandle DB_perf::GetDBHandle()
{
	return m_database;
}

TB_grade::TB_grade(KsDbHandle database)
{
	m_database = database;
	KsCreateCondition(1,&m_condition);
	KsCreateRecord(&m_record);
}

TB_grade::TB_grade(TB_grade &V)
{
	KsCreateCondition(1,&m_condition);
	KsCreateRecord(&m_record);
	KsDupCondition(V.m_condition,m_condition);
	KsDupRecord(V.m_record,m_record);
}

TB_grade::~TB_grade()
{
	KsCloseCondition(m_condition);
	KsCloseRecord(m_database,m_record);
}

bool TB_grade::newrecord()
{
	return KsNewRecord(m_database,0,m_record);
}

bool TB_grade::append(int id)
{
	KsSetField(m_database,m_record,0,(char *)&id);
	return KsPutRecord(m_database,m_record);
}

bool TB_grade::erase()
{
	KsDeleteRecord(m_database,m_record);
	return true;
}

bool TB_grade::first()
{
	if(!KsFirstRecord(m_database,m_condition))
	{
		return false;
	}
	KsGetRecord(m_database,m_condition,m_record);
	return true;
}

bool TB_grade::prev()
{
	if(!KsPrevRecord(m_database,m_condition))
	{
		return false;
	}
	KsGetRecord(m_database,m_condition,m_record);
	return true;
}

bool TB_grade::next()
{
	if(!KsNextRecord(m_database,m_condition))
	{
		return false;
	}
	KsGetRecord(m_database,m_condition,m_record);
	return true;
}

bool TB_grade::end()
{
	if(!KsLastRecord(m_database,m_condition))
	{
		return false;
	}
	KsGetRecord(m_database,m_condition,m_record);
	return true;
}

bool TB_grade::gotorow(int rowid)
{
	if(!KsGotoRecord(m_database,0,rowid,m_condition))
	{
		return false;
	}
	KsGetRecord(m_database,m_condition,m_record);
	return true;
}

int  TB_grade::recordrowid()
{
	return KsGetRecordId(m_database,m_record);
}

bool TB_grade::dump(char *filename)
{
	return KsDumpTable(m_database,0,filename);
}

bool TB_grade::SaveTXT(char *filename)
{
	return KsWriteTableTxt(m_database,0,filename);
}

bool TB_grade::LoadTXT(char *filename)
{
	return KsReadTableTxt(m_database,0,m_record,filename);
}

bool TB_grade::SaveBinary(char *filename)
{
	return KsWriteTableBinary(m_database,0,filename);
}

bool TB_grade::LoadBinary(char *filename)
{
	return KsReadTableBinary(m_database,0,m_record,filename);
}

bool TB_grade::backup(char *filename)
{
	return KsWriteDbTable(m_database,0,filename);
}

bool TB_grade::load(char *filename)
{
	return KsReadDbTable(m_database,0,filename);
}

int  TB_grade::get_id()
{
	int fieldtype;
	int r;

	memcpy(&r,KsGetField(m_database,m_record,0,fieldtype),sizeof(int));
	return r;
}

bool TB_grade::set_value(int value)
{
	return KsSetField(m_database,m_record,1,(char *)&value);
}

int  TB_grade::get_value()
{
	int fieldtype;
	int r;

	memcpy(&r,KsGetField(m_database,m_record,1,fieldtype),sizeof(int));
	return r;
}

bool TB_grade::find_by_pkey(int id,int op)
{
	KsSetConditionIndex(m_condition,0);
	KsAddConditionIndexItem(m_condition,KSTYPE_INT4,4,(char *)&id);
	if (!KsFindRecord(m_database,0,m_condition,op))
	{
		return false;
	}
	KsGetRecord(m_database,m_condition,m_record);
	return true;
}

bool TB_grade::lists()
{
	KsSetConditionIndex(m_condition,-1);
	if (!KsListRecord(m_database,0,m_condition))
	{
		return false;
	}
	KsGetRecord(m_database,m_condition,m_record);
	return true;
}

bool TB_grade::list_by_pkey()
{
	KsSetConditionIndex(m_condition,0);
	if (!KsListRecord(m_database,0,m_condition))
	{
		return false;
	}
	KsGetRecord(m_database,m_condition,m_record);
	return true;
}

