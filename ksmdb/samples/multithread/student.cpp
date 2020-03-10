#include "student.h"
DB_student::DB_student()
{
	m_inited = false;
	m_database = NULL;
}

bool DB_student::Create(char *path,char *name,long size)
{
	if(m_inited)
	{
		return true;
	}
	m_inited=true;
	if (KsCreateDb(&m_database,path,name,"20200227-09:27:04:000",size) == true)
	{
		KsAddTable(m_database,"grade");
		KsAddField(m_database,0,"id",KSTYPE_INT4,4,-1);
		KsAddField(m_database,0,"name",KSTYPE_STRING,51,-1);
		KsAddField(m_database,0,"classroom",KSTYPE_STRING,11,-1);
		KsAddField(m_database,0,"math",KSTYPE_DOUBLE,8,0);
		KsAddField(m_database,0,"Chinese",KSTYPE_DOUBLE,8,0);
		KsAddField(m_database,0,"english",KSTYPE_DOUBLE,8,0);
		KsAddIndex(m_database,0,"pkey",UNIQUE_INDEX);
		KsAddIndexField(m_database,0,0,0);
		KsAddIndex(m_database,0,"nameindex",NONUNIQUE_INDEX);
		KsAddIndexField(m_database,0,1,1);
		KsAddIndex(m_database,0,"classroom",NONUNIQUE_INDEX);
		KsAddIndexField(m_database,0,2,2);
		KsAddIndex(m_database,0,"nameclassroom",NONUNIQUE_INDEX);
		KsAddIndexField(m_database,0,3,1);
		KsAddIndexField(m_database,0,3,2);
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

bool DB_student::Open(char *path,char *name,int mode,int port,bool isolate,int reuse_shmmap, int shmrcset_mode)
{
	if(m_inited)
	{
		return true;
	}
	m_inited=true;
	if (KsOpenDb(&m_database,path,name,"20200227-09:27:04:000",mode,port,isolate, reuse_shmmap, shmrcset_mode) == true)
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

void DB_student::UnLockDb()
{
	KsUnLockDb(m_database);
}

void DB_student::SetErrorHandle(KsErrorHandle handle)
{
	KsSetErrorHandle(m_database,handle);
}

int DB_student::GetCols(KsRecordHandle handle)
{
	return KsGetCols(m_database,handle);
}

char *DB_student::GetColName(KsRecordHandle handle,int col)
{
	return KsGetColName(m_database,handle,col);
}

int DB_student::GetColType(KsRecordHandle handle,int col)
{
	return KsGetColType(m_database,handle,col);
}

int DB_student::GetColSize(KsRecordHandle handle,int col)
{
	return KsGetColSize(m_database,handle,col);
}

int DB_student::GetColDecimal(KsRecordHandle handle,int col)
{
	return KsGetColDecimal(m_database,handle,col);
}

char *DB_student::GetColData(KsRecordHandle handle,int col)
{
	return KsGetColData(m_database,handle,col);
}

void DB_student::GetMemoryInfo(long &size,long &inused)
{
	KsMemoryInfo(m_database,&size,&inused);
}

void DB_student::Reset()
{
	KsResetDb(m_database);
}

bool DB_student::Backup(char *filename)
{
	return KsWriteDbFile(m_database,filename);
}

bool DB_student::Load(char *filename)
{
	return KsReadDbFile(m_database,filename);
}

void DB_student::BeginTransaction()
{
	KsBeginTransaction(m_database);
}

void DB_student::RollbackTransaction()
{
	KsRollbackTransaction(m_database);
}

void DB_student::CommitTransaction()
{
	KsCommitTransaction(m_database);
}

void DB_student::GetLastError(int *errcode,char *errmsg)
{
	KsGetError(m_database,*errcode,errmsg);
}

bool DB_student::LoadLicense(char *licensefilename,char *errmsg)
{
	return KsDbLoadLicense(licensefilename,errmsg);
}

void DB_student::GetLicenseInfo(int &controlexpitedate,int &expitedate,int &controltransactioncount,long &transactioncount,int &delay)
{
	KsDbGetLicenseInfo(&controlexpitedate,&expitedate,&controltransactioncount,&transactioncount,&delay);
}

void DB_student::Close()
{
	KsDeleteDb(m_database);
	m_inited=false;
}

char* DB_student::LibVersion()
{
	return KsGetLibVersion();
}

char* DB_student::DbVersion()
{
	return KsGetDbVersion(m_database);
}

KsDbHandle DB_student::GetDBHandle()
{
	return m_database;
}

TB_grade::TB_grade(KsDbHandle database)
{
	m_database = database;
	KsCreateCondition(2,&m_condition);
	KsCreateRecord(&m_record);
}

TB_grade::TB_grade(TB_grade &V)
{
	KsCreateCondition(2,&m_condition);
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

bool TB_grade::append(int id,char* name,char* classroom)
{
	KsSetField(m_database,m_record,0,(char *)&id);
	KsSetField(m_database,m_record,1,(char *)name);
	KsSetField(m_database,m_record,2,(char *)classroom);
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

char* TB_grade::get_name()
{
	int fieldtype;

	return (char *)KsGetField(m_database,m_record,1,fieldtype);
}

char* TB_grade::get_classroom()
{
	int fieldtype;

	return (char *)KsGetField(m_database,m_record,2,fieldtype);
}

bool TB_grade::set_math(double value)
{
	return KsSetField(m_database,m_record,3,(char *)&value);
}

double TB_grade::get_math()
{
	int fieldtype;
	double r;

	memcpy(&r,KsGetField(m_database,m_record,3,fieldtype),sizeof(double));
	return r;
}

bool TB_grade::set_Chinese(double value)
{
	return KsSetField(m_database,m_record,4,(char *)&value);
}

double TB_grade::get_Chinese()
{
	int fieldtype;
	double r;

	memcpy(&r,KsGetField(m_database,m_record,4,fieldtype),sizeof(double));
	return r;
}

bool TB_grade::set_english(double value)
{
	return KsSetField(m_database,m_record,5,(char *)&value);
}

double TB_grade::get_english()
{
	int fieldtype;
	double r;

	memcpy(&r,KsGetField(m_database,m_record,5,fieldtype),sizeof(double));
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

bool TB_grade::find_by_nameindex(char* name,int op)
{
	KsSetConditionIndex(m_condition,1);
	KsAddConditionIndexItem(m_condition,KSTYPE_STRING,51,(char *)name);
	if (!KsFindRecord(m_database,0,m_condition,op))
	{
		return false;
	}
	KsGetRecord(m_database,m_condition,m_record);
	return true;
}

bool TB_grade::find_by_classroom(char* classroom,int op)
{
	KsSetConditionIndex(m_condition,2);
	KsAddConditionIndexItem(m_condition,KSTYPE_STRING,11,(char *)classroom);
	if (!KsFindRecord(m_database,0,m_condition,op))
	{
		return false;
	}
	KsGetRecord(m_database,m_condition,m_record);
	return true;
}

bool TB_grade::find_by_nameclassroom(char* name,char* classroom,int op)
{
	KsSetConditionIndex(m_condition,3);
	KsAddConditionIndexItem(m_condition,KSTYPE_STRING,51,(char *)name);
	KsAddConditionIndexItem(m_condition,KSTYPE_STRING,11,(char *)classroom);
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

bool TB_grade::list_by_nameindex()
{
	KsSetConditionIndex(m_condition,1);
	if (!KsListRecord(m_database,0,m_condition))
	{
		return false;
	}
	KsGetRecord(m_database,m_condition,m_record);
	return true;
}

bool TB_grade::list_by_classroom()
{
	KsSetConditionIndex(m_condition,2);
	if (!KsListRecord(m_database,0,m_condition))
	{
		return false;
	}
	KsGetRecord(m_database,m_condition,m_record);
	return true;
}

bool TB_grade::list_by_nameclassroom()
{
	KsSetConditionIndex(m_condition,3);
	if (!KsListRecord(m_database,0,m_condition))
	{
		return false;
	}
	KsGetRecord(m_database,m_condition,m_record);
	return true;
}

