/**
 * Project: ows-qt-console
 * File name: connect.h
 * Description: describes the connection dialog window
 *
 * @author Mathieu Grzybek on 2012-05-08
 * @copyright 2012 Mathieu Grzybek. All rights reserved.
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

#ifndef CONNECT_H
#define CONNECT_H

#include <QDebug>
#include <QDialog>
#include <QStandardItemModel>

#include "Main_Window.h"

namespace Ui {
	class Connect;
}

class Main_Window;

class Connect : public QDialog
{
	Q_OBJECT

public:
	explicit Connect(int* row, QStandardItemModel* model, QWidget *parent = 0);
	~Connect();

protected:
	void changeEvent(QEvent *e);

private slots:
	void on_Servers_List_clicked(const QModelIndex &index);

private:
	Ui::Connect *ui;
	QModelIndex* clicked_item;
	QStandardItemModel* servers_model;
	int* selected_row;
};

#endif // CONNECT_H
