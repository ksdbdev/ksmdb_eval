# 金仕达内存数据库体验版。

## 产品信息
KSMDB是嵌入式内存数据库，可以为企业级服务器端应用系统和嵌入式系统提供高性能数据存取服务。
KSMDB提供符合标准ACID规范的事务特性，由于数据存取访问路径足够短，KSMDB在高并发事务访问场景仍然具有极速性能表现。

KSMDB对外表现为一个静态链接库。为了支持KSMDB静态链接库的开发与使用，该发布包同时包括工具集，文档，以及示例工程代码：
- 静态库及工具文件包括：libksmdb.a, libksmdb.so, libksmdbcli.a, ksmdbmanage, kstbcmp，分别在ksmdb/lib，ksmdb/bin以及ksmdb/tool目录下。具体用法参见用户手册。
- 示例工程及代码在ksmdb/samples目录下，包括基本接口的使用，性能，多线程，错误处理，导入导出(备份及恢复)。

当前版本： V2.3

## 支持的运行环境
- Windows XP以上版本
- Linux
- 中标麒麟Linux(鲲鹏ARM64)
- AIX
- HP-UX

该体验版仅包含X86平台上Windows和通用Linux发布包，若需要AIX,HP-UX或其他平台的版本，请联系我们的技术支持。

## 技术社区和问题反馈
- 技术支持QQ群：1048263371
- 产品发布渠道：https://github.com/ksdbdev/ksmdb_eval
- 技术支持邮箱：hongbin.zhu@kingstarfintech.com
- 公司地址：上海市浦东新区亮景路210号
