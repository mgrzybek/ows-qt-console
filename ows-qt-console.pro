# Project: ows-qt-console
# File name: ows-qt-console.pro
# Description: describes the project and how to build it
#
# @author Mathieu Grzybek on 20??-??-??
# @copyright 20?? Mathieu Grzybek. All rights reserved.
# @version $Id: code-gpl-license.txt,v 1.2 2004/05/04 13:19:30 garry Exp $
#
# @see The GNU Public License (GPL) version 3 or higher
#
#
# ? is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
# or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
# for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
#

QT		+= core widgets

TARGET		= ows-qt-console
TEMPLATE	= app

unix:LIBS += -lthrift \
	-L/opt/local/lib \
#	-L/opt/local/lib/mysql5/mysql \
	-L/usr/lib \
	-L/usr/local/lib \
	/opt/local/lib/libboost_regex-mt.a \
	/opt/local/lib/libboost_thread-mt.a \
	/opt/local/lib/libboost_filesystem-mt.a

linux:LIBS	+= -lthrift \
	-L/lib \
	-L/opt/local/lib \
#	-L/opt/local/lib/mysql \
#	-L/opt/local/lib/mysql5/mysql \
	-L/usr/lib \
#	-L/usr/lib/mysql \
	-L/usr/local/lib \
#	-L/usr/local/lib/mysql \
#	-L/usr/local/lib/mysql5/mysql \
	-L/usr/share/lib \
#	-L/usr/share/lib/mysql \
#	-L/usr/share/lib/mysql5/mysql

INCLUDEPATH	+= 	/opt/local/include \
#	/opt/local/include/mysql \
#	/opt/local/include/mysql5 \
#	/opt/local/include/mysql5/mysql \
	/opt/local/include/thrift \
	../open-workload-scheduler/include \
	../open-workload-scheduler/src/gen-cpp

SOURCES	+= src/main.cpp\
	src/main_window.cpp \
	src/connect.cpp \
	src/domains_manager.cpp \
	src/edit_node_dialog.cpp \
	src/edit_job_dialog.cpp \
	../open-workload-scheduler/src/gen-cpp/ows_rpc.cpp \
	../open-workload-scheduler/src/gen-cpp/model_types.cpp \
	../open-workload-scheduler/src/gen-cpp/model_constants.cpp \
	../open-workload-scheduler/src/rpc_client.cpp \
	../open-workload-scheduler/src/convertions.cpp

HEADERS	+= src/main_window.h \
	src/connect.h \
	src/domains_manager.h \
	src/edit_node_dialog.h \
	src/edit_job_dialog.h \
	../open-workload-scheduler/src/gen-cpp/ows_rpc.h \
	../open-workload-scheduler/src/gen-cpp/model_types.h \
	../open-workload-scheduler/src/gen-cpp/model_constants.h \
	../open-workload-scheduler/include/rpc_client.h \
	../open-workload-scheduler/include/convertions.h

FORMS	+= ui/main_window.ui \
	ui/domains_manager.ui \
	ui/connect.ui \
	ui/edit_node_dialog.ui \
	ui/edit_job_dialog.ui
