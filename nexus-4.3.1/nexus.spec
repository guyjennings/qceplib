# nexus.spec.  Generated from nexus_spec.in by configure.
# $Id: nexus_spec.in 1889 2013-03-07 12:35:34Z Freddie Akeroyd $
# Template for NeXus RPM SPEC file
# Copyright (C) 2004 Freddie Akeroyd <freddie.akeroyd@stfc.ac.uk>
#
Summary: Libraries and utilities for using NeXus format data files
Name: nexus
Version: 4.3.1
# Release is the number of times this version of the software was 
# built into an RPM file; it should be incremented each RPM build and
# then reset to 1 when a new version of the software is released
%if "" == ""
%else
%define nexusrelease .
%endif
Release: 1%{?nexusrelease}%{?dist}
License: LGPL
# Group: there is more than one choice for this - maybe we need to split
# nexus into separate packages (libraries + apps)
Group: Development/Libraries
#Group: Development/Tools
Source: http://download.nexusformat.org/kits/nexus-4.3.1.tar.gz
URL: http://www.nexusformat.org/
Distribution: Unknown
#Icon: nexus.xpm
Vendor: NeXus International Advisory Committee (NIAC)
Packager: NeXus Developers <nexus-developers@nexusformat.org>
# Prefix allows our package to be relocatable i.e. installable in 
# other than just the /usr/local directory
#Prefix: /usr
# BuildRoot is the root for software installation
# this value will not usually be used, but something must
# be specified here to allow   rpm --buildroot   to be used later
# (it will get used for a   rpmbuild --recompile  of the the src.rpm)
%if 0%{?rhel} == 5
%define is_rhel5 1
%endif
%if 0%{?el5}
%define is_rhel5 1
%endif
%if "0%{?dist}" == "0.el5"
%define is_rhel5 1
%endif

%if 0%{?rhel} == 6
%define is_rhel6 1
%endif
%if 0%{?el6}
%define is_rhel6 1
%endif
%if "0%{?dist}" == "0.el6"
%define is_rhel6 1
%endif

BuildRoot: %{_tmppath}/nexus-4.3.1
BuildRequires: python numpy
BuildRequires: hdf5-devel hdf-devel 
BuildRequires: libxml2-devel
#BuildRequires: java-1.6.0-openjdk-devel
BuildRequires: readline-devel
# mxml is not in rhel or epel as yet
# ant on rhel5 is too old to build NXvalidate
%if 0%{?fedora}
BuildRequires: mxml-devel
BuildRequires: ant
%endif
%if 0%{?is_rhel5}
BuildRequires: python-ctypes
%endif
%if 0%{?is_rhel6}
BuildRequires: ant ant-nodeps
%endif

%description
NeXus is an international standard for exchanging data files
among Neutron, Muon and X-ray science facilities. The underlying
data is stored using the HDF format from NCSA. This package provides
access routines, documentation, examples and a basic NeXus file browser.

%package devel
Summary: Libraries and utilities for using NeXus format data files
Group: Development/Libraries

%description devel
NeXus is an international standard for exchanging data files
among Neutron, Muon and X-ray science facilities. The underlying
data is stored using the HDF format from NCSA. This package provides

%package tools
Summary: Libraries and utilities for using NeXus format data files
Group: Development/Libraries

%description tools
NeXus is an international standard for exchanging data files
among Neutron, Muon and X-ray science facilities. The underlying
data is stored using the HDF format from NCSA. This package provides

%package doc
Summary: Libraries and utilities for using NeXus format data files
Group: Development/Libraries

%description doc
NeXus is an international standard for exchanging data files
among Neutron, Muon and X-ray science facilities. The underlying
data is stored using the HDF format from NCSA. This package provides

%package python
Summary: Libraries and utilities for using NeXus format data files
Group: Development/Libraries

%description python
NeXus is an international standard for exchanging data files
among Neutron, Muon and X-ray science facilities. The underlying
data is stored using the HDF format from NCSA. This package provides

%package java
Summary: Libraries and utilities for using NeXus format data files
Group: Development/Libraries

%description java
NeXus is an international standard for exchanging data files
among Neutron, Muon and X-ray science facilities. The underlying
data is stored using the HDF format from NCSA. This package provides

%prep
%setup -q -n nexus-4.3.1

%build
# RPM_INSTALL_PREFIX - where to install software
# do --prefix last in case also present in passed config options
if ! test -z "$RPM_INSTALL_PREFIX"; then
    ./configure %{?nexus_config_options} --prefix="$RPM_INSTALL_PREFIX"
else
    ./configure %{?nexus_config_options} --prefix=%{_prefix} --libdir=%{_libdir}
fi
make

%install
# RPM_BUILD_ROOT is where to install software to
if test "$RPM_BUILD_ROOT" != "/"; then rm -fr "$RPM_BUILD_ROOT"; fi
make DESTDIR="$RPM_BUILD_ROOT" install
find "$RPM_BUILD_ROOT" -name '*.la' -exec rm -f {} \;

%files
%defattr(-,root,root)
%doc README NEWS ChangeLog AUTHORS COPYING INSTALL
# %docdir /usr/local/doc
%{_libdir}/libNeXus*.so*
%{_libdir}/libnxconvert*.so*
#%ifarch x86_64
#/usr/lib/*.so*
#%endif

%files devel
%defattr(-,root,root)
%{_libdir}/libNeXus*.a
%{_libdir}/libnxconvert*.a
%{_libdir}/pkgconfig
%{_includedir}/*

%files tools
%defattr(-,root,root)
%{_bindir}/*
%{_datadir}/man

%files doc
%defattr(-,root,root)
%{_datadir}/nexus

%files python
%defattr(-,root,root)
/usr/lib/python*/site-packages/nxs

%files java
%defattr(-,root,root)
%{_datadir}/java
%{_libdir}/libjnexus.so*
%{_libdir}/libjnexus.a

%clean
if test "$RPM_BUILD_ROOT" != "/"; then rm -fr "$RPM_BUILD_ROOT"; fi

%post
if test `whoami` = root; then ldconfig; fi

%post tools
if [ "$RPM_INSTALL_PREFIX" != "" ]; then
    INSTALL_PREFIX=$RPM_INSTALL_PREFIX
else
    INSTALL_PREFIX=%{_prefix}
fi

( cd $INSTALL_PREFIX/bin; for i in nxbuild; do \
  sed -i -e "s|^prefix=.*|prefix=$INSTALL_PREFIX|" $i; done )

%postun
if test `whoami` = root; then ldconfig; fi
#
# %changelog date format as per  `date +"%a %d %b %Y"`
# first line should be   date  user  email
%changelog
* Sat Oct 22 2011 Freddie Akeroyd <freddie.akeroyd@stfc.ac.uk> - 4.3.0
- Split into subpackages
* Thu May 24 2007 Freddie Akeroyd <F.A.Akeroyd@rl.ac.uk> - 4.0.0
- Tag and build 4.0.0
* Wed May 16 2007 Freddie Akeroyd <F.A.Akeroyd@rl.ac.uk> - 4.0rc3
- Tag and build 4.0rc3
* Fri Mar 30 2007 Freddie Akeroyd <F.A.Akeroyd@rl.ac.uk> - 4.0rc2
- Tag and build 4.0rc2
* Thu Mar 15 2007 Freddie Akeroyd <F.A.Akeroyd@rl.ac.uk> - 4.0rc1
- Tag and build 4.0rc1
* Wed Jul 27 2005 Freddie Akeroyd <F.A.Akeroyd@rl.ac.uk>
- Change Copyright: to License: and add PACKAGE_RELEASE
* Mon Jun  6 2005 Freddie Akeroyd <F.A.Akeroyd@rl.ac.uk>
- Add extra documentation and example files to distribution
* Wed May 12 2004 Jens Krueger <jens.krueger@frm2.tum.de>
- Change the License entry to LGPL
- remove /usr/local/nexus /usr/local/doc from the file list
* Wed Mar 24 2004 Freddie Akeroyd <F.A.Akeroyd@rl.ac.uk>
- Fix up prefix in nxbuild after an install so the RPM is now relocatable
* Sun Feb 22 2004 Freddie Akeroyd <F.A.Akeroyd@rl.ac.uk>
- Initial RPM kit version
