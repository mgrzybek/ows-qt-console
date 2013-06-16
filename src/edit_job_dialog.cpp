/**
 * Project: ows-qt-console
 * File name: edit_job_dialog.cpp
 * Description: this class describes the job editing dialog window
 *
 * @author Mathieu Grzybek on 2012-06-19
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

#include "src/edit_job_dialog.h"
#include "ui_edit_job_dialog.h"

Edit_Job_Dialog::Edit_Job_Dialog(QStandardItemModel* jobs, QStandardItemModel* nodes, rpc::t_job* j, const char* domain_name, QWidget* parent) :
	QDialog(parent),
	ui(new Ui::Edit_Job_Dialog)
{
	job = j;
	jobs_model = jobs;
	nodes_model = nodes;

	ui->setupUi(this);

	ui->Available_Jobs_Tree->setModel(jobs);
	ui->Node_List->setModel(nodes_model);
	ui->Domain_Edit->setText(domain_name);
	ui->Domain_Edit->setEnabled(false);
	ui->Control_Buttons->setDisabled(true);

	edit_mode = false;
	fill_in_job_data();
}

Edit_Job_Dialog::~Edit_Job_Dialog()
{
	job = NULL;
	delete ui;
}

void Edit_Job_Dialog::changeEvent(QEvent *e)
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

void Edit_Job_Dialog::on_Name_Edit_textChanged(const QString &arg1)
{
	activate_control_buttons();
}

void Edit_Job_Dialog::on_Cmd_Line_Edit_textChanged(const QString &arg1)
{
	activate_control_buttons();
}

void Edit_Job_Dialog::activate_control_buttons()
{
	// TODO: add check or cross icons next to the boxes
	if ( ui->Name_Edit->text().isEmpty() == true or
		ui->Cmd_Line_Edit->text().isEmpty() == true or
		ui->Domain_Edit->text().isEmpty() == true or
		job->node_name.empty() == true )
		ui->Control_Buttons->setDisabled(true);
	else
		ui->Control_Buttons->setEnabled(true);

	if ( jobs_model->findItems(ui->Name_Edit->text(), Qt::MatchExactly, 1).size() > 0 and edit_mode == true ) {
		ui->Control_Buttons->setDisabled(true);
		qDebug() << "Job not found";
	}
}


void Edit_Job_Dialog::on_Node_List_clicked(const QModelIndex &index)
{
	job->node_name = nodes_model->item(index.row(), 0)->text().toStdString();
}

void Edit_Job_Dialog::on_Time_Window_Radio_clicked()
{
	ui->Before_Check->setEnabled(true);
	ui->After_Check->setEnabled(true);

	ui->Before_Line->setEnabled(true);
	ui->After_Line->setEnabled(true);

	ui->At_Line->setDisabled(true);
}

void Edit_Job_Dialog::on_At_Radio_clicked()
{
	ui->Before_Check->setDisabled(true);
	ui->After_Check->setDisabled(true);

	ui->Before_Line->setDisabled(true);
	ui->After_Line->setDisabled(true);

	ui->At_Line->setEnabled(true);
}

void Edit_Job_Dialog::on_None_Radio_clicked()
{
	ui->Before_Check->setDisabled(true);
	ui->After_Check->setDisabled(true);

	ui->Before_Line->setDisabled(true);
	ui->After_Line->setDisabled(true);

	ui->At_Line->setDisabled(true);
}

void Edit_Job_Dialog::on_Control_Buttons_accepted()
{
	job->name = ui->Name_Edit->text().toStdString().c_str();
	job->cmd_line = ui->Cmd_Line_Edit->text().toStdString().c_str();
	job->domain = ui->Domain_Edit->text().toStdString().c_str();

//	job->nxt
//	job->prv
//	job->recovery_type

	/*
	 * Some properties cannot be changed:
	 * - return_code
	 * - start_time
	 * - state
	 * - stop_time
	*/

	/*
	 * Time Constraints
	 */
	if ( ui->At_Radio->isChecked() == true ) {
		rpc::t_time_constraint	tc;

		tc.job_name = job->name;
		tc.type = rpc::e_time_constraint_type::AT;
		tc.value = ui->At_Line->text().toUInt();

		job->time_constraints.push_back(tc);
	} else if ( ui->Time_Window_Radio->isChecked() == true ) {
		if ( ui->Before_Check->isChecked() == true ) {
			rpc::t_time_constraint before_tc;

			before_tc.job_name = job->name;
			before_tc.type = rpc::e_time_constraint_type::BEFORE;
			before_tc.value = ui->Before_Line->text().toInt();

			job->time_constraints.push_back(before_tc);
		}

		if ( ui->After_Check->isChecked() == true ) {
			rpc::t_time_constraint after_tc;

			after_tc.job_name = job->name;
			after_tc.type = rpc::e_time_constraint_type::AFTER;
			after_tc.value = ui->After_Line->text().toInt();

			job->time_constraints.push_back(after_tc);
		}
	}

	job->weight = ui->Weight_Spin->value();
}

void Edit_Job_Dialog::fill_in_job_data()
{
	if ( job->cmd_line.empty() == false )
		ui->Cmd_Line_Edit->setText(job->cmd_line.c_str());

	if ( job->name.empty() == false ) {
		ui->Name_Edit->setText(job->name.c_str());
		edit_mode = true;
	}

	// TODO: do it
	if ( job->node_name.empty() == false ) {
		for ( int row = 0 ; row < jobs_model->rowCount() ; row++ ) {
			if ( jobs_model->item(row, 0)->data().toString().toStdString() == job->node_name ) {
				QItemSelectionModel	select_model(jobs_model);
				select_model.select(jobs_model->index(row, 0), QItemSelectionModel::Toggle);
				ui->Node_List->setSelectionModel(&select_model);
				break;
			}
		}
	}

//	if ( job->nxt
//	if ( job->prv
//	if ( job->recovery_type

	/*
	 * Theses properties are not shown:
	 * - return_code
	 * - start_time
	 * - stop_time
	 * - state
	 */

	if ( job->time_constraints.empty() == true )
		ui->None_Radio->setChecked(true);
	else
		Q_FOREACH( rpc::t_time_constraint tc, job->time_constraints ) {
			if ( tc.type == rpc::e_time_constraint_type::AT ) {
				ui->At_Radio->setChecked(true);
				ui->At_Line->setText(QDateTime::fromTime_t(tc.value).toString());
				break;
			} else if ( tc.type == rpc::e_time_constraint_type::BEFORE ) {
				ui->Time_Window_Radio->setChecked(true);
				ui->Before_Line->setText(QDateTime::fromTime_t(tc.value).toString());
			} else {
				ui->Time_Window_Radio->setChecked(true);
				ui->After_Line->setText(QDateTime::fromTime_t(tc.value).toString());
			}
		}

	if ( job->weight > 0 )
		ui->Weight_Spin->setValue(job->weight);
}
