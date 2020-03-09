#!/bin/sh

###########################################################################################
# clripc.sh

# 功能：
# 内存数据库系统资源清理工具脚本，用于清理进程异常崩溃后内存数据库遗留的系统资源，
# 这些遗留资源包括文件、System V共享内存、System V信号量。

# 用法：
# 把脚本拷贝到内存数据库所在目录，确认脚本执行权限，执行脚本：
# ./clripc.sh dbpath dbname
# 例：
# ./clripc.sh /rk_a_mdb riskmdb

# 备注：
# 1）单进程使用内存数据库（嵌入式模式）场合可用本工具。
# 2）使用ksmdbmanage多业务进程非隔离模式场合，可用本工具。
# 3）使用ksmdbmanage多业务进程隔离模式场合，本工具当前版本没有清理隔离模式特有的资源，
#    这类资源的例子：000059C9_5A97950E_00000001.a0.sem


let ftokkey=0
resfilenames=(0)
function ftok(){

    pathname=$1;
    proj_id=$2;
	
    if [ "${pathname:0:1}" != "/" ] ; then

        pathname=${PWD}/${pathname}

    fi
    if ! test -f ${pathname} ; then

        echo "No File Found![${pathname}]"
        exit 4
    fi

    str_st_ino=`stat --format='%i' "${pathname}" 2>/dev/null`;
    str_st_dev=`stat --format='%d' "${pathname}" 2>/dev/null`;

    if [ "x${str_st_ino}" = "x" -o "x${str_st_dev}" = "x" ] ; then
        return 1;
    fi
	
    let st_ino=${str_st_ino}

    let st_dev=${str_st_dev}

    let key1=${st_ino}\&16#FFFF

    let key2=${st_dev}\&16#FF

    let key2=${key2}\<\<16

    let key3=${proj_id}\&16#FF

    let key3=${key3}\<\<24

    let ftokkey=${key1}\|${key2}

    let ftokkey=${ftokkey}\|${key3}

}
function echohelp(){

    echo "ksmdb ipc resource clean up tool."
    echo "Usage:clripc dbpath dbname"
    exit 5

}

function clrres(){

    reskey=$1
	ipctype=$2
    for filename in ${resfilenames[@]}
    do
        projid=0
	    while(($projid<10))
	    do
            let ftokkey=0
			#ftok函数取得文件对应的key，存入${ftokkey}
	        ftok "${filename}" "${projid}"
            filekey=`printf "0x%08x" ${ftokkey}`
            #DEBUG INFO:
			#printf "file: %s  proid: %d, genarator key: %s\n" ${filename} ${projid} ${filekey}
            if [ $reskey = $filekey ] 
            then
			    if [ $ipctype = "M" ]
				then
				    #shm resource clean up
                    echo "clear shm: ipcrm -M ${reskey}"
					ipcrm -M $reskey
				else
				    #sema resource clean up
                    echo "clear sema: ipcrm -S ${reskey}"
					ipcrm -S $reskey
				fi
	            return 0
	        fi
			
            let projid=projid+1
	    done
    done
	printf "##  ipc resource key: %s is not ksmdb resource.\n" $reskey
	
}

####################################################
#
#    shell start up
if [ $# -ne 2 ] ; then
    echohelp
fi

printf "ksmdb ipc resource clean up startup:\n"

#根据参数给定的内存数据库名，生成资源文件数组
dbpath=$1
dbname=$2
dbfilename=${dbpath}"//"${dbname}

printf "target ksmdb is: dbpath=%s dbname=%s\n" $dbpath $dbname

#内存数据库文件锁对应的文件
dbfilelockres=${dbfilename}
if test -f ${dbfilelockres} ; then
    resfilenames[0]=${dbfilelockres}
fi

#事务相关自旋锁对应的文件
spinfilename=${dbfilename}".lk"
if test -f ${spinfilename} ; then
    resfilenames[1]=${spinfilename}
fi

#自旋锁相关的信号量对应的文件
sema_r_1=${dbfilename}".1.r.s0.sem"
if test -f ${sema_r_1} ; then
    resfilenames[2]=${sema_r_1}
fi

sema_w_1=${dbfilename}".1.w.s0.sem"
if test -f ${sema_w_1} ; then
    resfilenames[3]=${sema_w_1}
fi

sema_r_2=${dbfilename}".2.r.s0.sem"
if test -f ${sema_r_2} ; then
    resfilenames[4]=${sema_r_2}
fi

sema_w_2=${dbfilename}".2.w.s0.sem"
if test -f ${sema_w_2} ; then
    resfilenames[5]=${sema_w_2}
fi

#事务信息存储shm对应的文件
sessionctfilename=${dbfilename}"_session_shmname"
if test -f ${sessionctfilename} ; then
    resfilenames[6]=${sessionctfilename}
fi

#内存数据库数据对应的资源文件
i=7
for datafile in $(ls ${dbpath}/${dbname}*.data)
do
    resfilenames[$i]=${datafile}
    let i=i+1
done

echo "ksmdb files:--------------------------"
for rsfile in ${resfilenames[*]}
do
    echo "$rsfile"
done

OLDIFS=$IFS
IFS=$'\n'

for i in $(ipcs -m | grep 0x | awk '{print $1}')
do
    printf "\n\n###########################################\n" $i
    printf "system shm ipc resource key: %s\n" $i
    clrres "${i}" "M"
done

for i in $(ipcs -s | grep 0x | awk '{print $1}')
do
    printf "\n\n###########################################\n" $i
    printf "system sema ipc resource key: %s\n" $i
    clrres "${i}" "S"
done

IFS=$OLDIFS

printf "clear ksmdb files:-------------------------------\n"
for rsfile in ${resfilenames[*]}
do
    echo "clear ksmdb files: rm -f ${rsfile}"
    rm -f $rsfile
done



