/**
 * Project: ows-qt-console
 * File name: edit_job_dialog.h
 * Description: this header describes the job editing dialog window
 *
 * @author Mathieu Grzybek on 2012-06-19
 * @copyright 20?? Mathieu Grzybek. All rights reserved.
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

#ifndef EDIT_JOB_DIALOG_H
#define EDIT_JOB_DIALOG_H

#include <QTreeWidgetItem>
#include <QStandardItemModel>
#include <QDateTime>
#include <QDialog>
#include <QDebug>

#include "rpc_client.h"

namespace Ui {
	class Edit_Job_Dialog;
}

class Edit_Job_Dialog : public QDialog
{
	Q_OBJECT

public:
	explicit Edit_Job_Dialog(QStandardItemModel* jobs, QStandardItemModel* nodes, rpc::t_job* j, const char* domain_name, QWidget* parent = 0);
	~Edit_Job_Dialog();

protected:
	void changeEvent(QEvent* e);

private slots:
	void on_Name_Edit_textChanged(const QString &arg1);
	void on_Cmd_Line_Edit_textChanged(const QString &arg1);
	void on_Node_List_clicked(const QModelIndex &index);

	void on_Time_Window_Radio_clicked();
	void on_At_Radio_clicked();
	void on_None_Radio_clicked();

	void on_Control_Buttons_accepted();

private:
	Ui::Edit_Job_Dialog*	ui;
	bool			edit_mode;

	rpc::t_job*	job;

	QStandardItemModel*	jobs_model;
	QStandardItemModel*	nodes_model;

	void activate_control_buttons();
	void fill_in_job_data();
};

#endif // EDIT_JOB_DIALOG_H
