/**
 * Project: ows-qt-console
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
 * ows-qt-console is free software; you can redistribute it and/or modify
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

#include <QMainWindow>
#include <QSettings>
#include <QErrorMessage>
#include <QTreeWidgetItem>
#include <QDateTime>

#include "convertions.h"
#include "connect.h"
#include "domains_manager.h"
#include "edit_node_dialog.h"
#include "edit_job_dialog.h"

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
	QStandardItemModel	template_jobs_model;
	QStandardItemModel	current_jobs_model;
	QStandardItemModel	nodes_model;

//	bool	rpc_connect(const QString& hostname, const int& port, const QString& username, const QString& password);

private slots:
	void	on_actionManage_triggered();

	void	on_actionConnect_triggered();
	void	on_actionDisconnect_triggered();

	void	on_nodes_tree_doubleClicked(const QModelIndex &index);

	void	on_add_template_job_button_clicked();

	void	on_add_current_job_button_clicked();

	void	on_add_template_node_button_clicked();

	void	on_get_current_nodes_button_clicked();

	void	on_get_template_nodes_button_clicked();

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
	Rpc_Client*				rpc_client;
	rpc::t_node				local_node;
	rpc::t_node				remote_node;
	rpc::t_routing_data    	routing;
	std::string				current_planning_name;

	void	load_settings();
	void	save_settings();

	/*
	 * RPC methods
	 */
	bool	populate_domain_models();
	void	insert_nodes_model(const rpc::t_node& n);
	bool	populate_jobs_models(const rpc::v_jobs* template_jobs, const rpc::v_jobs* current_jobs);

	/*
	 * Models
	 */
	void	prepare_models();
	void	prepare_jobs_model();
	void	prepare_nodes_model();
};

#endif // MAIN_WINDOW_H
