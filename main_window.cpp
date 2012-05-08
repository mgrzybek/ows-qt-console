/**
 * Project: OWS GUI
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

#include "main_window.h"
#include "ui_main_window.h"

Main_Window::Main_Window(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::Main_Window)
{
	load_settings();

	ui->setupUi(this);
	ui->centralWidget->setVisible(false);
}

Main_Window::~Main_Window()
{
	delete ui;
}

bool Main_Window::rpc_connect(const QString& hostname, const int& port, const QString& username, const QString& password) {
	if ( rpc_client == NULL )
		rpc_client = new Rpc_Client();
	else
		rpc_client->close();

	if ( rpc_client->open(hostname.toStdString().c_str(), port) == false ) {
		qDebug() << "Connection failed";
		rpc_client->close();
		delete rpc_client;
		return false;
	}

	rpc_client->close();
	delete rpc_client;
	return true;
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

		rpc_client = new Rpc_Client();

		if ( rpc_client->open(hostname.toStdString().c_str(), port) == true ) {
			if ( populate_domain_model() == true ) {
				ui->actionConnect->setDisabled(true);
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
}

void Main_Window::load_settings()
{
	QSettings	settings;
	QStringList	headers;
	int		size;
	QList<QStandardItem*>	row;

	headers << "Domain Name" << "Hostname" << "Port" << "Username" << "Password";

	servers_model.clear();
	servers_model.setHorizontalHeaderLabels(headers);

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

bool Main_Window::populate_domain_model() {
	rpc::v_nodes	result_nodes; // TODO: thing of putting it into the main_window attributes
	QErrorMessage*	error_msg;

	QStringList	headers;
	QList<QStandardItem*>	row;

	try {
		rpc_client->get_handler()->get_nodes(result_nodes, local_node.domain_name, local_node, remote_node);
	} catch ( rpc::ex_routing r) {
		qCritical() << "Cannot send the RPC call to the right server : " << r.msg.c_str();

		error_msg = new QErrorMessage();
		error_msg->showMessage(r.msg.c_str());
		error_msg->exec();
		delete error_msg;

		return false;
	} catch ( rpc::ex_node n ) {
		qCritical() << "Cannot get the resul from the RPC call : " << n.msg.c_str();

		error_msg = new QErrorMessage();
		error_msg->showMessage(n.msg.c_str());
		error_msg->exec();
		delete error_msg;

		return false;
	} catch ( rpc::ex_processing p ) {
		qCritical() << "Cannot get the resul from the RPC call : " << p.msg.c_str();

		error_msg = new QErrorMessage();
		error_msg->showMessage(p.msg.c_str());
		error_msg->exec();
		delete error_msg;

		return false;
	}

	headers << "Node Name" << "Job Name" << "Command Line" << "State" << "Start Time" << "Stop Time" << "Weight";

	jobs_model.clear();
	jobs_model.setHorizontalHeaderLabels(headers);
	row.clear();

	Q_FOREACH(rpc::t_node n, result_nodes) {
		Q_FOREACH(rpc::t_job j, n.jobs) {
			row << new QStandardItem(j.node_name.c_str());
			row << new QStandardItem(j.name.c_str());
			row << new QStandardItem(j.cmd_line.c_str());
			row << new QStandardItem(j.state);
			row << new QStandardItem(j.start_time);
			row << new QStandardItem(j.stop_time);

			jobs_model.appendRow(row);
			row.clear();
		}
	}

	ui->jobs_view->setModel(&jobs_model);

	return true;
}
