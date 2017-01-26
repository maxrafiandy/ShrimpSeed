/* * *
 * Copyright (C) 2017  Max Rafiandy
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * * */

#ifndef MAINQML_H
#define MAINQML_H

#include <QObject>
#include <QFileDialog>
#include <QFileInfo>

#ifdef __ANDROID__
#include <QtAndroidExtras>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/imgcodecs/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#else
#include "opencv2/imgproc.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#endif

class MainQml: public QObject
{
    Q_OBJECT
public:
    MainQml();
    virtual ~MainQml();
    Q_INVOKABLE void bt_browse_clicked();
    Q_INVOKABLE void threshold_change(qint8 value);
    Q_INVOKABLE void scale_change(qint8 value);
    Q_INVOKABLE void update_filename(QString value);
    Q_INVOKABLE void file_selected(QString value);
private:
    qint8 scale=1, threshold=1, shrimp=0;
    void update_status();
    cv::Mat img;
    int threshval = 0;
    int obj_min_size = 0;
    int index = 0;
    QString filename;
};
#endif // MAINQML_H
