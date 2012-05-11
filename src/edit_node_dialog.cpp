/**
 * Project:
 * File name:
 * Description:
 *
 * @author Mathieu Grzybek on 20??-??-??
 * @copyright 20?? Mathieu Grzybek. All rights reserved.
 * @version $Id: code-gpl-license.txt,v 1.2 2004/05/04 13:19:30 garry Exp $
 *
 * @see The GNU Public License (GPL) version 3 or higher
 *
 *
 * ? is free software; you can redistribute it and/or modify
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

#include "edit_node_dialog.h"
#include "ui_edit_node_dialog.h"

Edit_Node_Dialog::Edit_Node_Dialog(rpc::t_node* n, const char* domain_name, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::Edit_Node_Dialog)
{
	QStringList	headers;

	node = n;

	headers << "Name" << "Initial Value";
	resources_model.setHorizontalHeaderLabels(headers);

	ui->setupUi(this);
	ui->domain_line->setText(domain_name);
	ui->control_buttons->setDisabled(true);
	ui->resources_table->setModel(&resources_model);
}

Edit_Node_Dialog::~Edit_Node_Dialog()
{
	delete ui;
}

void Edit_Node_Dialog::changeEvent(QEvent *e)
{
	QDialog::changeEvent(e);
	switch (e->type()) {
		case QEvent::LanguageChange:
			ui->retranslateUi(this);
			break;
		default:
			break;
	}
}

void Edit_Node_Dialog::add_blank_resource() {
	QStandardItem new_item;

	new_item.appendRow(new QStandardItem(""));
	new_item.appendRow(new QStandardItem(""));
	new_item.appendRow(new QStandardItem(""));

	resources_model.appendRow(&new_item);
}

void Edit_Node_Dialog::on_add_resource_button_clicked()
{
	add_blank_resource();
}

void Edit_Node_Dialog::on_delete_resource_button_clicked()
{
	QModelIndexList selected_items = ui->resources_table->selectionModel()->selectedIndexes();

	Q_FOREACH(QModelIndex index, selected_items) {
		resources_model.removeRow(index.row());
	}
}

void Edit_Node_Dialog::on_name_line_textChanged(const QString &arg1)
{
	if ( ui->name_line->text().isEmpty() == true )
		ui->control_buttons->setDisabled(true);
	else
		ui->control_buttons->setEnabled(true);
}

void Edit_Node_Dialog::on_control_buttons_accepted()
{
	node->name = ui->name_line->text().toStdString();
	node->domain_name = ui->domain_line->text().toStdString();
	node->weight = ui->weight_box->value();

	if ( resources_model.rowCount() > 0 ) {
		rpc::t_resource* r = NULL;

		for ( int row = 0 ; row < resources_model.rowCount() ; row++ ) {
			r = new rpc::t_resource();

			r->name = resources_model.item(row, 0)->text().toStdString();
			r->initial_value = resources_model.item(row, 1)->text().toInt();
			r->current_value = resources_model.item(row, 1)->text().toInt();

			node->resources.push_back(*r);
			delete r;
		}
	}
}
