%define MAKEFILE gcc-linux.mak

Summary: Complete C++ standard library
Name: STLport
Version: 4.5
Release: 1
Source: http://www.stlport.org/archive/%{name}-%{version}.%{release}.tar.gz
URL: http://www.stlport.org/
License: free to use, see /usr/share/doc/%{name}-%{version}/license.html
Icon: stlport_powered_white.xpm
Group: System Environment/Languages
BuildRoot: %{_tmppath}/%{name}-%{version}-%(id -u -n)

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
"-nostdinc++ -I/usr/include/stlport" when compiling and -lstlport_gcc when
linking (eg: gcc -nostdinc++ -I/usr/include/stlport x.cc -lstlport_gcc).

%prep
%setup

%build
cd src
make -f %{MAKEFILE} INSTALLDIR=$RPM_BUILD_ROOT/usr clean all

%install
rm -rf $RPM_BUILD_ROOT
cd src
make -f %{MAKEFILE} INSTALLDIR=$RPM_BUILD_ROOT/usr install
cd $RPM_BUILD_ROOT/usr/include/stlport
ln -s . ext

# fix links so they don't point to BuildRoot
ln -sf libstlport_gcc_stldebug.so.%{version} $RPM_BUILD_ROOT/usr/lib/libstlport_gcc_stldebug.so
ln -sf libstlport_gcc.so.%{version} $RPM_BUILD_ROOT/usr/lib/libstlport_gcc.so

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
%doc doc/license.html
/usr/lib/libstlport_gcc.so
/usr/lib/libstlport_gcc.so.%{version}

%files -n STLport-devel
%defattr(-,root,root)
%doc INSTALL README doc etc test
/usr/lib/libstlport_gcc*.a
/usr/lib/libstlport_gcc_stldebug.so*
/usr/include/*

%changelog
* Thu Nov 15 2001 <stlport@lanceerplaats.nl>
- rebuild for RedHat 7.2, spec file fixes.

* Tue Oct  2 2001 Levente Farkas <lfarkas@mindmaker.hu>
- upgrade to 4.5

* Thu Oct 26 2000 Levente Farkas <lfarkas@mindmaker.hu>
- upgrade to 4.1-b3

* Thu Jul 17 2000 Levente Farkas <lfarkas@mindmaker.hu>
- initial release use STLport-4.0
