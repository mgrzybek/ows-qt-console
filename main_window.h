/**
 * Project: OWS GUI
 * File name: main_window.h
 * Description: this header describes the program's main window
 *
 * @author Mathieu Grzybek on 2012-04-30
 * @copyright 2012 Mathieu Grzybek. All rights reserved.
 * @version $Id: code-gpl-license.txt,v 1.2 2004/05/04 13:19:30 garry Exp $
 *
 * @see The GNU Public License (GPL) version 3 or higher
 *
 *
 * OWS GUI is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <iostream>
#include <QMainWindow>
#include <QSettings>
#include <QErrorMessage>

#include "connect.h"
#include "domains_manager.h"
#include "ui_domains_manager.h"

#include "rpc_client.h"

namespace Ui {
	class Main_Window;
}

class Connect;

class Main_Window : public QMainWindow
{
	Q_OBJECT

public:
	explicit Main_Window(QWidget *parent = 0);
	~Main_Window();

	QStandardItemModel	servers_model;
	QStandardItemModel	jobs_model;

	bool	rpc_connect(const QString& hostname, const int& port, const QString& username, const QString& password);

private slots:
	void	on_actionManage_triggered();

	void	on_actionConnect_triggered();
	void	on_actionDisconnect_triggered();

private:
	/*
	 * Windows
	 */
	Ui::Main_Window*	ui;
	Domains_Manager*	dm_dialog;
	Connect*		connect_dialog;

	/*
	 * Settings objects
	 *
	 * QSettings::QSettings ( Scope scope, const QString & organization, const QString & application = QString(), QObject * parent = 0 )
	 */
	QSettings	settings;
	char*		config_file;

	/*
	 * RPC objects
	 */
	Rpc_Client*	rpc_client;
	rpc::t_node	local_node;
	rpc::t_node	remote_node;

	void	load_settings();
	void	save_settings();

	/*
	 * RPC methods
	 */
	bool	populate_domain_model();
};

#endif // MAIN_WINDOW_H
