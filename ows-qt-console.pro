#-------------------------------------------------
#
# Project created by QtCreator 2012-04-20T22:00:17
#
#-------------------------------------------------

QT       += core gui

TARGET = ows-gui
TEMPLATE = app

unix:LIBS += -lthrift \
	-L/opt/local/lib \
	-L/opt/local/lib/mysql \
	-L/opt/local/lib/mysql5/mysql \
	-L/usr/lib \
	-L/usr/lib/mysql \
	-L/usr/local/lib \
	-L/usr/share/lib \
	/opt/local/lib/libboost_regex.a \
	/opt/local/lib/libboost_thread-mt.a \
	/opt/local/lib/libboost_filesystem.a

linux:LIBS += -lthrift \
	-L/lib \
	-L/opt/local/lib \
	-L/opt/local/lib/mysql \
	-L/opt/local/lib/mysql5/mysql \
	-L/usr/lib \
	-L/usr/lib/mysql \
	-L/usr/local/lib \
	-L/usr/local/lib/mysql \
	-L/usr/local/lib/mysql5/mysql \
	-L/usr/share/lib \
	-L/usr/share/lib/mysql \
	-L/usr/share/lib/mysql5/mysql

INCLUDEPATH += 	/opt/local/include \
	/opt/local/include/mysql \
	/opt/local/include/mysql5 \
	/opt/local/include/mysql5/mysql \
	/opt/local/include/thrift \
	../../open-workload-scheduler/src

SOURCES += main.cpp\
	main_window.cpp \
	domains_manager.cpp \
	../../open-workload-scheduler/src/gen-cpp/ows_rpc.cpp \
	../../open-workload-scheduler/src/gen-cpp/model_types.cpp \
	../../open-workload-scheduler/src/gen-cpp/model_constants.cpp \
	../../open-workload-scheduler/src/rpc_client.cpp \
#	../../open-workload-scheduler/src/config.cpp \
#	../../open-workload-scheduler/src/router.cpp
	connect.cpp

HEADERS  += main_window.h \
	domains_manager.h \
	../../open-workload-scheduler/src/gen-cpp/ows_rpc.h \
	../../open-workload-scheduler/src/gen-cpp/model_types.h \
	../../open-workload-scheduler/src/gen-cpp/model_constants.h \
	../../open-workload-scheduler/src/rpc_client.h \
#	../../open-workload-scheduler/src/config.h \
#	../../open-workload-scheduler/src/router.h
	connect.h

FORMS    += main_window.ui \
	domains_manager.ui \
	connect.ui
