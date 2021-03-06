dnl configure.ac
dnl
dnl Autoconf configuration
dnl
dnl Use autoconf to process this into a configure script
dnl
dnl   (C) Copyright 2014-2017 Fred Gleason <fredg@paravelsystems.com>
dnl
dnl   This program is free software; you can redistribute it and/or modify
dnl   it under the terms of the GNU General Public License version 2 as
dnl   published by the Free Software Foundation.
dnl
dnl   This program is distributed in the hope that it will be useful,
dnl   but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
dnl   GNU General Public License for more details.
dnl
dnl   You should have received a copy of the GNU General Public
dnl   License along with this program; if not, write to the Free Software
dnl   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
dnl

AC_INIT(drouter,m4_esyscmd(cat PACKAGE_VERSION))
AM_INIT_AUTOMAKE
AC_SUBST(RPM_RELEASE,1)
m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([yes])])

#
# Basic Compiler Checks
#
AC_PROG_CXX
AC_LANG(C++)

# to avoid rpath usage :
# http://wiki.debian.net/index.cgi?RpathIssue
case ${host} in
  *-pc-linux-gnu)
    AC_MSG_RESULT([Fixing libtool for -rpath problems.])
    sed < libtool > libtool-2 \
    's/^hardcode_libdir_flag_spec.*$/hardcode_libdir_flag_spec=" -D__LIBTOOL_IS_A_FOOL__ "/'
    mv libtool-2 libtool
    chmod 755 libtool
  ;;
esac

#
# Option Switches
#
AC_ARG_ENABLE(docbook,[  --disable-docbook       disable building of DocBook documentation],[DOCBOOK_DISABLED=yes],[])

#
# Check for Qt (Mandatory)
#
PKG_CHECK_MODULES(QT4CLI,QtCore QtNetwork QtSql,[],[AC_MSG_ERROR([*** Qt4 CLI components not found ***])])
PKG_CHECK_MODULES(QT4GUI,QtCore QtGui QtNetwork QtSql,[],[AC_MSG_ERROR([*** Qt4 GUI components not found ***])])
AC_CHECK_PROG(MOC_NAME,moc-qt4,[moc-qt4],[moc])
AC_SUBST(MOC,$MOC_NAME)

#
# Check for Switchyard (Mandatory)
#
PKG_CHECK_MODULES(SWITCHYARD,switchyard,[],[AC_MSG_ERROR([*** Switchyard not found ***])])

#
# Check for SystemD (Optional)
#
PKG_CHECK_MODULES(LIBSYSTEMD,libsystemd,[LIBSYSTEMD_FOUND=yes],[LIBSYSTEMD_FAILED=yes])
if test $LIBSYSTEMD_FOUND ; then
  AC_DEFINE(LIBSYSTEMD)
fi

#
# Check for DocBook Toolchain
#
if test -z $DOCBOOK_DISABLED ; then
  USING_DOCBOOK=yes
fi
AM_CONDITIONAL([DOCBOOK_AM], [test "$USING_DOCBOOK" = yes])

#
# Determine the target architecture
#
AR_GCC_TARGET()
AC_SUBST(VENDOR,$ar_gcc_distro)
AC_SUBST(ARCH,$ar_gcc_arch)

#
# Determine Distro
#
AR_GET_DISTRO()
AC_SUBST(DISTRO,$ar_gcc_distro)

#
# Configure RPM Build
#
AC_CHECK_PROG(RPMBUILD_FOUND,rpmbuild,[yes],[])
if test -z $RPMBUILD_FOUND ; then
  AC_SUBST(RPMBUILD,rpm)
else
  AC_SUBST(RPMBUILD,rpmbuild)
fi
if test -d /usr/src/redhat ; then
  AC_SUBST(RPM_ROOT,/usr/src/redhat)
  AC_SUBST(VENDOR,redhat)
else
  AC_SUBST(RPM_ROOT,/usr/src/packages)
  AC_SUBST(VENDOR,suse)
fi 

AC_CONFIG_FILES([ \
    docs/Makefile \
    icons/Makefile \
    src/Makefile \
    src/buttonpanel/Makefile \
    src/common/Makefile \
    src/dmap/Makefile \
    src/drouterd/Makefile \
    src/outputpanel/Makefile \
    src/shotpanel/Makefile \
    src/tests/Makefile \
    src/xpointpanel/Makefile \
    src/xypanel/Makefile \
    systemd/Makefile \
    systemd/drouter.service \
    drouter.spec \
    Makefile ])
AC_OUTPUT()

#
# Link Common Elements
#
./link_common.sh buttonpanel
./link_common.sh dmap
./link_common.sh drouterd
./link_common.sh outputpanel
./link_common.sh shotpanel
./link_common.sh tests
./link_common.sh xpointpanel
./link_common.sh xypanel

AC_MSG_NOTICE()
AC_MSG_NOTICE(Now enter 'make' to build the software.)
AC_MSG_NOTICE()
