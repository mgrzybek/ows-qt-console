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

#include <QDialog>

#include "rpc_client.h"

namespace Ui {
	class Edit_Job_Dialog;
}

class Edit_Job_Dialog : public QDialog
{
	Q_OBJECT

public:
	explicit Edit_Job_Dialog(rpc::t_job* j, const char* domain_name, QWidget* parent = 0);
	~Edit_Job_Dialog();

protected:
	void changeEvent(QEvent* e);

private:
	Ui::Edit_Job_Dialog*	ui;

	rpc::t_job*	job;
};

#endif // EDIT_JOB_DIALOG_H
