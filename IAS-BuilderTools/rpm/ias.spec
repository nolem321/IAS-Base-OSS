Summary: IAS Invenire Aude System
Name: ias
Version: 1.0.1
Release: 2
License: ASL 2.0
Group: Applications/Communications
Source: https://github.com/InvenireAude/IAS-Base-OSS/archive/master.tar.gz
BuildRoot: /var/tmp/%{name}-buildroot

%description
IAS Softwares
%prep
%setup -q -n IAS-Base-OSS-master
IAS-BuilderTools/bin/build_all.sh -p Linux-64bitO3 clean

%build

IAS-BuilderTools/bin/build_all.sh -p Linux-64bitO3
IAS-BuilderTools/bin/build_all.sh -p Linux-64bitO3 -j dm all

%install

rm -rf $RPM_BUILD_ROOT
IAS-BuilderTools/bin/build_all.sh -p Linux-64bitO3 -j -d $RPM_BUILD_ROOT/usr/ias install
tree $RPM_BUILD_ROOT

mkdir -p $RPM_BUILD_ROOT/usr/bin
cd $RPM_BUILD_ROOT/usr/bin
ln -s ../ias/bin/* .
pwd
ls -l

mkdir -p $RPM_BUILD_ROOT/usr/lib64
cd $RPM_BUILD_ROOT/usr/lib64
ln -s ../ias/lib/* .

pwd
ls -l

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root)
%dir /usr/ias

/usr/ias/lib/dsmod_postgresql.so
/usr/ias/lib/dsmod_sqlite.so
/usr/ias/lib/qsfmt_SOAP.so
/usr/ias/lib/qsfmt_SOAP12.so
/usr/ias/lib/qsmod_fcgi.so
/usr/ias/lib/qsmod_sm.so
/usr/ias/lib/libIASQSystemMod-FCGI.so
/usr/ias/lib/libIASQSystemMod-LDAP.so
/usr/ias/lib/libIASQSystemFmt-SOAP.so
/usr/ias/lib/libIASCommonLib.so
/usr/ias/lib/libIASServiceManagerLib.so
/usr/ias/lib/libIASQSystemMod-ServiceManager.so
/usr/ias/lib/libIASLangLib.so
/usr/ias/lib/libIASDataModelLib.so
/usr/ias/lib/libIASQSystemMod-SQLite.so
/usr/ias/lib/libIASQSystemMod-PostgreSQL.so
/usr/ias/lib/libIASQSystemLib.so
/usr/ias/bin/ias_qs_status
/usr/ias/bin/sm_restart_service
/usr/ias/bin/sm_stop_service
/usr/ias/bin/ias_qs_distributor
/usr/ias/bin/sm_dsp_service
/usr/ias/bin/sm_mon_service
/usr/ias/bin/ias_qs_create
/usr/ias/bin/sm_start_service
/usr/ias/bin/sm_run_service_cmd
/usr/ias/bin/ias_dm_codegen
/usr/ias/bin/ias_qs_change
/usr/ias/bin/ias_qs_processor
/usr/ias/bin/ias_qs_cleaner

/usr/lib64/libIASCommonLib.so
/usr/lib64/libIASServiceManagerLib.so
/usr/lib64/libIASLangLib.so
/usr/lib64/libIASDataModelLib.so
/usr/lib64/libIASQSystemLib.so
/usr/lib64/libIASQSystemFmt-SOAP.so
/usr/lib64/libIASQSystemMod-FCGI.so
/usr/lib64/libIASQSystemMod-LDAP.so
/usr/lib64/libIASQSystemMod-PostgreSQL.so
/usr/lib64/libIASQSystemMod-SQLite.so
/usr/lib64/libIASQSystemMod-ServiceManager.so

/usr/lib64/dsmod_postgresql.so
/usr/lib64/dsmod_sqlite.so
/usr/lib64/qsfmt_SOAP.so
/usr/lib64/qsfmt_SOAP12.so
/usr/lib64/qsmod_fcgi.so
/usr/lib64/qsmod_sm.so
/usr/bin/ias_qs_status
/usr/bin/sm_restart_service
/usr/bin/sm_stop_service
/usr/bin/ias_qs_distributor
/usr/bin/sm_dsp_service
/usr/bin/sm_mon_service
/usr/bin/ias_qs_create
/usr/bin/sm_start_service
/usr/bin/sm_run_service_cmd
/usr/bin/ias_dm_codegen
/usr/bin/ias_qs_change
/usr/bin/ias_qs_processor
/usr/bin/ias_qs_cleaner



%changelog
* Tue Dec 04 2018 Admin (admin@invenireaude.com)
- auto rebuild in the new build environment (release 1)





