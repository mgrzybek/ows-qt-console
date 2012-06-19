/**
 * Project: ows-qt-console
 * File name: domains_manager.cpp
 * Description: this class describes the connections management dialog window
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

#include "domains_manager.h"
#include "ui_domains_manager.h"

Domains_Manager::Domains_Manager(QStandardItemModel* model, QDialog* parent) :
	QDialog(parent),
	ui(new Ui::Domains_Manager)
{
	servers_model = model;
	ui->setupUi(this);
	ui->Saved_Servers_List->setModel(model);
	ui->Saved_Servers_List->show();
}

Domains_Manager::~Domains_Manager()
{
	delete ui;
	servers_model = NULL;
}

void Domains_Manager::add_blank_server() {
	QStandardItem new_item;

	new_item.appendRow(new QStandardItem(""));
	new_item.appendRow(new QStandardItem(""));
	new_item.appendRow(new QStandardItem(""));
	new_item.appendRow(new QStandardItem(""));

	servers_model->appendRow(&new_item);
}

void Domains_Manager::on_New_Server_Button_clicked()
{
	add_blank_server();
}

void Domains_Manager::on_Delete_Server_Button_clicked()
{
	QModelIndexList selected_items = ui->Saved_Servers_List->selectionModel()->selectedIndexes();

	Q_FOREACH(QModelIndex index, selected_items) {
		servers_model->removeRow(index.row());
	}
}
