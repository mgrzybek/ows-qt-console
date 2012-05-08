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

#include "connect.h"
#include "ui_connect.h"

Connect::Connect(int* row, QStandardItemModel* model, QWidget* parent) :
	QDialog(parent),
	ui(new Ui::Connect)
{
	selected_row = row;
	servers_model = model;

	ui->setupUi(this);

	ui->Servers_List->setModel(model);
	ui->Servers_List->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui->Servers_List->setSelectionBehavior(QAbstractItemView::SelectItems);
}

Connect::~Connect()
{
	delete ui;
}

void Connect::changeEvent(QEvent *e)
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

void Connect::on_Servers_List_clicked(const QModelIndex &index)
{
	*selected_row = index.row();
}
