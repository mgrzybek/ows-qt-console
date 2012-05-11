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

#ifndef EDIT_NODE_DIALOG_H
#define EDIT_NODE_DIALOG_H

#include <QDialog>
#include <QStandardItemModel>
#include <QDebug>

#include "rpc_client.h"

namespace Ui {
	class Edit_Node_Dialog;
}

class Edit_Node_Dialog : public QDialog
{
	Q_OBJECT

public:
	explicit Edit_Node_Dialog(rpc::t_node* n, const char* domain_name, QWidget* parent = 0);
	~Edit_Node_Dialog();

protected:
	void changeEvent(QEvent *e);

private slots:
	void on_add_resource_button_clicked();
	void on_delete_resource_button_clicked();

	void on_name_line_textChanged(const QString &arg1);

	void on_control_buttons_accepted();

private:
	Ui::Edit_Node_Dialog*	ui;
	QStandardItemModel	resources_model;

	rpc::t_node*	node;

	void	add_blank_resource();
};

#endif // EDIT_NODE_DIALOG_H
