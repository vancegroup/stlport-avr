Summary: Complete C++ standard library
Name: STLport
Version: 4.5
Release: 1
Copyright: free (see license)
Url: http://www.stlport.org/
Packager: Levente Farkas <lfarkas@mindmaker.hu>
Group: System Environment/Languages
Source0: http://www.stlport.org/archive/STLport-4.5.1.tar.gz

Buildroot: /tmp/%{name}-%{version}-%{release}/root

%description
STLport is a multiplatform STL implementation based on SGI STL.
This package contains the runtime library for STLport.

%package -n STLport-devel
Summary: Complete C++ standard library header files and libraries
Group: Development/Libraries
Requires: STLport = %{version}

%description -n STLport-devel
STLport is a multiplatform STL implementation based on SGI STL. Complete   
C++ standard library, including <complex> and SGI STL iostreams. If you
would like to use your code with STLport add
"-nostdinc++ -I/usr/include/stlport" when compile and -lstlport_gcc when
link (eg: gcc -nostdinc++ -I/usr/include/stlport x.cc -lstlport_gcc).

%define MAKEFILE gcc-linux.mak

%prep
%setup
%patch0 -p1
%patch1 -p1
%patch2 -p1

%build
cd src
make -f %{MAKEFILE} INSTALLDIR=/tmp/%{name}-%{version}-%{release}/root/usr clean all

%install
rm -rf $RPM_BUILD_ROOT
cd src
make -f %{MAKEFILE} INSTALLDIR=/tmp/%{name}-%{version}-%{release}/root/usr install
cd $RPM_BUILD_ROOT/usr/include/stlport
ln -s . ext

%clean
rm -rf $RPM_BUILD_ROOT

%post -p /sbin/ldconfig
%postun -p /sbin/ldconfig

%post -n STLport-devel
/sbin/ldconfig

%postun -n STLport-devel
/sbin/ldconfig

%files
%defattr(-,root,root)
/usr/lib/libstlport_gcc.so
/usr/lib/libstlport_gcc.so.4.5

%files -n STLport-devel
%defattr(-,root,root)
%doc INSTALL README doc
/usr/lib/libstlport_gcc*.a
/usr/lib/libstlport_gcc_stldebug.so*
/usr/include/*

%changelog
* Tue Oct  2 2001 Levente Farkas <lfarkas@mindmaker.hu>
- upgrade to 4.5

* Thu Oct 26 2000 Levente Farkas <lfarkas@mindmaker.hu>
- upgrade to 4.1-b3

* Thu Jul 17 2000 Levente Farkas <lfarkas@mindmaker.hu>
- initial release use STLport-4.0
