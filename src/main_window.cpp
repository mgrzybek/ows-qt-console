/**
 * Project: ows-qt-console
 * File name: main_window.cpp
 * Description: this source file describes the program's main window
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

#include "main_window.h"
#include "ui_main_window.h"

// TODO: think of using a function instead of a macro to be able to return the result of the RPC command
#define RPC_EXEC(command) \
	try { \
		command; \
	} catch ( const apache::thrift::transport::TTransportException& e ) { \
		QErrorMessage* error_msg; \
	\
		qCritical() << "Connection failed : " << e.what(); \
	\
		error_msg = new QErrorMessage(); \
		error_msg->showMessage(e.what()); \
		error_msg->exec(); \
		delete error_msg; \
	\
		on_actionDisconnect_triggered(); \
	} catch ( const apache::thrift::TException& e ) { \
		QErrorMessage* error_msg; \
	\
		qCritical() << "Cannot get the result from the RPC call : " << e.what(); \
	\
		error_msg = new QErrorMessage(); \
		error_msg->showMessage(e.what()); \
		error_msg->exec(); \
		delete error_msg; \
	\
	} catch ( const std::exception& e ) { \
		QErrorMessage* error_msg; \
	\
		qCritical() << "Cannot get the result from the RPC call : " << e.what(); \
		error_msg = new QErrorMessage(); \
		error_msg->showMessage(e.what()); \
		error_msg->exec(); \
		delete error_msg; \
	}

Main_Window::Main_Window(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::Main_Window)
{
	QStringList	headers;

	load_settings();
	current_planning_name.clear();

	headers << "Domain Name" << "Hostname" << "Port" << "Username" << "Password";
	servers_model.setHorizontalHeaderLabels(headers);

	ui->setupUi(this);

	ui->centralWidget->setVisible(false);
	ui->actionDisconnect->setDisabled(true);

	ui->current_jobs_view->setModel(&current_jobs_model);
	ui->template_jobs_view->setModel(&template_jobs_model);
//	ui->nodes_list->setModel(&nodes_model);
	ui->auto_refresh_current_check->setChecked(true);
	ui->auto_refresh_template_check->setChecked(true);
}

Main_Window::~Main_Window()
{
	delete ui;

	if ( rpc_client != NULL ) {
		delete rpc_client;
		rpc_client = NULL;
	}
}

void Main_Window::on_actionManage_triggered()
{
	dm_dialog = new Domains_Manager(&servers_model);

	if ( dm_dialog->exec() == QDialog::Accepted) {
		qDebug() << "dm_dialog -> Accepted";
		save_settings();
	} else {
		qDebug() << "dm_dialog -> Rejected";
		load_settings();
	}

	delete dm_dialog;
}

void Main_Window::on_actionConnect_triggered()
{
	int	selected_row;
	int	port;
	QString	domain_name;
	QString	username;
	QString	hostname;
	QString	password;

	connect_dialog = new Connect(&selected_row, &servers_model);

	if ( connect_dialog->exec() == QDialog::Accepted ) {
		qDebug() << "connect_dialog -> Accepted";

		domain_name = servers_model.item(selected_row, 0)->text();
		hostname = servers_model.item(selected_row, 1)->text();
		port = servers_model.item(selected_row, 2)->text().toInt();
		username = servers_model.item(selected_row, 3)->text();
		password = servers_model.item(selected_row, 4)->text();

		local_node.domain_name = domain_name.toStdString();
		local_node.name = "ows_gui";

		remote_node.domain_name = domain_name.toStdString();
		remote_node.name = hostname.toStdString();

		if ( rpc_client == NULL )
			rpc_client = new Rpc_Client();

		if ( rpc_client->open(hostname.toStdString().c_str(), port) == true ) {
			rpc_client->get_handler()->get_current_planning_name(current_planning_name, local_node.domain_name, local_node, remote_node);

			if ( populate_domain_models() == true ) {
				ui->actionConnect->setEnabled(false);
				ui->actionDisconnect->setEnabled(true);
				ui->centralWidget->setVisible(true);
			}
		} else {
			QErrorMessage* error_msg = new QErrorMessage();
			error_msg->showMessage("Cannot connect to the selected server");
			error_msg->exec();
			delete error_msg;
		}
	}

	delete connect_dialog;
}

void Main_Window::on_actionDisconnect_triggered() {
	rpc_client->close();
	delete rpc_client;

	ui->centralWidget->setVisible(false);
	ui->actionConnect->setEnabled(true);
	ui->actionDisconnect->setEnabled(false);

	prepare_models();
}

void Main_Window::load_settings()
{
	QSettings	settings;
	int		size;
	QList<QStandardItem*>	row;

	servers_model.clear();

	settings.beginGroup("domains_manager");
	size = settings.beginReadArray("servers");

	row.clear();

	for ( int i = 0 ; i < size ; i++ ) {
		settings.setArrayIndex(i);

		row << new QStandardItem(settings.value("domain_name").toString());
		qDebug() << "domain_name :" << settings.value("domain_name").toString();

		row << new QStandardItem(settings.value("hostname").toString());
		qDebug() << "hostname : " << settings.value("hostname").toString();

		row << new QStandardItem(settings.value("port").toString());
		qDebug() << "port : " << settings.value("port").toString();

		row << new QStandardItem(settings.value("username").toString());
		qDebug() << "username : " << settings.value("username").toString();

		row << new QStandardItem(settings.value("password").toString());
		qDebug() << "password : " << settings.value("password").toString();

		servers_model.insertRow(i, row);
		row.clear();
	}

	settings.endArray();
	settings.endGroup();
}

void Main_Window::save_settings()
{
	QSettings settings;

	settings.beginGroup("domains_manager");
	settings.beginWriteArray("servers");

	for ( int row = 0 ; row < servers_model.rowCount() ; row++ ) {
		settings.setArrayIndex(row);

		settings.setValue("domain_name", servers_model.item(row, 0)->text());
		qDebug() << "domain_name : " << servers_model.item(row, 0)->text();

		settings.setValue("hostname", servers_model.item(row, 1)->text());
		qDebug() << "hostname : " << servers_model.item(row, 1)->text();

		settings.setValue("port", servers_model.item(row, 2)->text());
		qDebug() << "port : " << servers_model.item(row, 2)->text();

		settings.setValue("username", servers_model.item(row, 3)->text());
		qDebug() << "username : " << servers_model.item(row, 3)->text();

		settings.setValue("password", servers_model.item(row, 4)->text());
		qDebug() << "password : " << servers_model.item(row, 4)->text();
	}

	settings.endArray();
	settings.endGroup();
}

bool Main_Window::populate_domain_models() {
	rpc::v_nodes	result_template_nodes; // TODO: think of putting it into the main_window attributes
	rpc::v_nodes	result_running_nodes;

	if ( current_planning_name.size() == 0 ) {
		qCritical() << "The current planning name is empty";
		return false;
	}

	RPC_EXEC(rpc_client->get_handler()->get_current_planning_name(current_planning_name, local_node.domain_name, local_node, remote_node));
	RPC_EXEC(rpc_client->get_handler()->get_nodes(result_template_nodes, local_node.domain_name, local_node, remote_node))
	RPC_EXEC(rpc_client->get_handler()->get_nodes(result_running_nodes, current_planning_name, local_node, remote_node))

	prepare_models();

	qDebug() << "Number of nodes (template): " << result_template_nodes.size();
	qDebug() << "Number of nodes (running): " << result_running_nodes.size();

	for ( ulong i = 0 ; i < result_template_nodes.size() ; i ++ ) {
		insert_nodes_model(result_template_nodes.at(i));

		if ( result_running_nodes.size() > 0 )
			populate_jobs_models(&result_template_nodes.at(i).jobs, &result_running_nodes.at(i).jobs);
		else
			populate_jobs_models(&result_template_nodes.at(i).jobs, NULL);
	}

	return true;
}

void Main_Window::insert_nodes_model(const rpc::t_node& n) {
	QList<QStandardItem*>	node_row;

	node_row << new QStandardItem(n.name.c_str());
	nodes_model.appendRow(node_row);

	node_row.clear();
}

bool Main_Window::populate_jobs_models(const rpc::v_jobs* template_jobs, const rpc::v_jobs* current_jobs) {
	QList<QStandardItem*>	job_row;
	ulong	max_index = 0;

	if ( current_jobs == NULL )
		max_index = template_jobs->size();
	else {
		if ( template_jobs->size() > current_jobs->size() )
			max_index = template_jobs->size();
		else
			max_index = current_jobs->size();
	}

	for ( ulong i = 0 ; i < max_index ; i++ ) {

		if ( i < template_jobs->size() ) {
			const rpc::t_job&	j = template_jobs->at(i);

			job_row << new QStandardItem(j.node_name.c_str());
			job_row << new QStandardItem(j.name.c_str());
			job_row << new QStandardItem(j.cmd_line.c_str());
			job_row << new QStandardItem(build_string_from_job_state(j.state).c_str());

			if ( j.state == rpc::e_job_state::WAITING) {
				job_row << new QStandardItem("-");
				job_row << new QStandardItem("-");
			} else {
				// TODO: change the way the dates are printed
				job_row << new QStandardItem(QDateTime::fromTime_t(j.start_time).toString());
				job_row << new QStandardItem(QDateTime::fromTime_t(j.stop_time).toString());
			}

			job_row << new QStandardItem(QString::number(j.weight));

			template_jobs_model.appendRow(job_row);
			job_row.clear();
		}

		if ( current_jobs != NULL && i < current_jobs->size() ) {
			const rpc::t_job&	j = current_jobs->at(i);

			job_row << new QStandardItem(j.node_name.c_str());
			job_row << new QStandardItem(j.name.c_str());
			job_row << new QStandardItem(j.cmd_line.c_str());
			job_row << new QStandardItem(build_string_from_job_state(j.state).c_str());

			if ( j.state == rpc::e_job_state::WAITING) {
				job_row << new QStandardItem("-");
				job_row << new QStandardItem("-");
			} else {
				// TODO: change the way the dates are printed
				job_row << new QStandardItem(QDateTime::fromTime_t(j.start_time).toString());
				job_row << new QStandardItem(QDateTime::fromTime_t(j.stop_time).toString());
			}

			job_row << new QStandardItem(QString::number(j.weight));

			current_jobs_model.appendRow(job_row);
			job_row.clear();
		}
	}

	return true;
}

void Main_Window::prepare_models() {
	ui->current_planning_label->setText(current_planning_name.c_str());
	prepare_jobs_model();
	prepare_nodes_model();
}

void Main_Window::prepare_jobs_model() {
	QStringList	headers;

	headers << "Node Name" << "Job Name" << "Command Line" << "State" << "Start Time" << "Stop Time" << "Weight";

	current_jobs_model.clear();
	template_jobs_model.clear();

	current_jobs_model.setHorizontalHeaderLabels(headers);
	template_jobs_model.setHorizontalHeaderLabels(headers);

	headers.clear();
}

void Main_Window::prepare_nodes_model() {
	QStringList	headers;

	headers << "Nodes";
	nodes_model.clear();
	nodes_model.setHorizontalHeaderLabels(headers);
	headers.clear();
}

void Main_Window::on_nodes_tree_doubleClicked(const QModelIndex& index)
{
	/*
	 * Have we clicked on a node or a job?
	 * - its parent is valid -> this is a job
	 */
	if ( index.parent().isValid() == false ) {
		rpc::t_node	template_result_node;
		rpc::t_node	current_result_node;
		rpc::t_node	node_to_get;

		// Clean the main window
		prepare_jobs_model();

		// Get the node's jobs only
		node_to_get.name = index.data().toString().toStdString().c_str();

		RPC_EXEC(rpc_client->get_handler()->get_node(template_result_node, local_node.domain_name, local_node, remote_node, node_to_get))
		RPC_EXEC(rpc_client->get_handler()->get_node(current_result_node, current_planning_name, local_node, remote_node, node_to_get))

		// TODO: fix it
		qDebug() << "node name: " << node_to_get.name.c_str();
		populate_jobs_models(&template_result_node.jobs, &current_result_node.jobs);

	} else {
/*
		rpc::t_job	job;

		job.node_name = jobs_model.item(index.row(), 0)->text().toStdString().c_str();
		job.name = jobs_model.item(index.row(), 1)->text().toStdString().c_str();

		RPC_EXEC(rpc_client->get_handler()->get_job(job, local_node.domain_name, local_node, remote_node, job))

		Edit_Job_Dialog*	edit_job = new Edit_Job_Dialog(&jobs_model, &nodes_tree, &nodes_model, &job, local_node.domain_name.c_str());

		if ( edit_job->exec() == QDialog::Rejected ) {
			delete edit_job;
			return;
		}

		delete edit_job;

		RPC_EXEC(rpc_client->get_handler()->update_job(local_node.domain_name, local_node, job))

		if ( ui->auto_refresh_check->isChecked() == true )
			populate_domain_model();
*/
	}
}

void Main_Window::on_add_template_node_button_clicked()
{
	rpc::t_node	node;
	Edit_Node_Dialog*	add_node = new Edit_Node_Dialog(&node, local_node.domain_name.c_str());

	if ( add_node->exec() == QDialog::Rejected ) {
		delete add_node;
		return;
	}

	RPC_EXEC(rpc_client->get_handler()->add_node(local_node.domain_name, local_node, remote_node, node))

	if ( ui->auto_refresh_template_check->isChecked() == true )
		populate_domain_models();

	delete add_node;
}

void Main_Window::on_add_template_job_button_clicked()
{
	rpc::t_job	job;
	Edit_Job_Dialog*	add_job = new Edit_Job_Dialog(&template_jobs_model, &nodes_model, &job, local_node.domain_name.c_str());

	if ( add_job->exec() == QDialog::Rejected ) {
		delete add_job;
		return;
	}

	RPC_EXEC(rpc_client->get_handler()->add_job(local_node.domain_name, local_node, job))

	if ( ui->auto_refresh_template_check->isChecked() == true )
		populate_domain_models();

	delete add_job;
}

void Main_Window::on_add_current_job_button_clicked()
{
	rpc::t_job	job;
	Edit_Job_Dialog*	add_job = new Edit_Job_Dialog(&current_jobs_model, &nodes_model, &job, current_planning_name.c_str());

	if ( add_job->exec() == QDialog::Rejected ) {
		delete add_job;
		return;
	}

	RPC_EXEC(rpc_client->get_handler()->add_job(current_planning_name, local_node, job))

	if ( ui->auto_refresh_current_check->isChecked() == true )
		populate_domain_models();

	delete add_job;
}

void Main_Window::on_get_current_nodes_button_clicked()
{
	populate_domain_models();
}

void Main_Window::on_get_template_nodes_button_clicked()
{
	populate_domain_models();
}
