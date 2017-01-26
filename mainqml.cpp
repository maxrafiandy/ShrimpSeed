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

#include "mainqml.h"
#include <QDebug>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

extern QObject *qml_root;
extern QImage q_img;

QString selectedFileName;

MainQml::MainQml()
{

}

MainQml::~MainQml()
{

}

void MainQml::bt_browse_clicked()
{
    qDebug() << "button browse clicked";
}

void MainQml::threshold_change(qint8 value)
{
    threshold = value;
    update_status();
}

void MainQml::scale_change(qint8 value)
{
    scale = value;
    update_status();
}

void MainQml::update_filename(QString value)
{
    filename = value.toLatin1().data();
    update_status();
}

void MainQml::file_selected(QString value)
{
    filename = value.toLatin1().data() + 6;
    update_status();
}

void MainQml::update_status()
{
    char msg[100];

    if(QFileInfo(filename).exists())
    {
/*
#ifndef __ANDROID__
        FILE *file;
        char csvfile[30];
        sprintf (csvfile, "%s.csv ", filename.toLatin1().data());
        file = fopen(csvfile,"a+");
#endif
*/
        cv::Mat img = cv::imread(filename.toLatin1().data(), 0);
        cv::Size size(320,240);
        cv::resize(img,img,size);

        shrimp = 0;

        cv::Mat bw = threshold < 128 ? (img < threshold) : (img > threshold);
        cv::Mat labelImage(img.size(), CV_32S), centeroid, stats;

        int nLabels = cv::connectedComponentsWithStats(bw, labelImage, stats, centeroid, 4, CV_32S);

        for (int n=1; n<nLabels; n++)
        {
            int shrimp_size = stats.at<int>(n,cv::CC_STAT_WIDTH) * stats.at<int>(n,cv::CC_STAT_HEIGHT);
            if (shrimp_size >= scale)
            {
                int width = stats.at<int>(n,cv::CC_STAT_WIDTH);
                int height = stats.at<int>(n,cv::CC_STAT_HEIGHT);
                int left = stats.at<int>(n,cv::CC_STAT_LEFT);
                int top = stats.at<int>(n,cv::CC_STAT_TOP);
                rectangle(img, cv::Rect(cv::Point(left,top), cv::Size(width,height)), cv::Scalar(255, 255, 11));
                shrimp++;
            }
        }

/*#ifndef __ANDROID__
        fprintf(file,"%d; %ld; %d;\n", threshold, scale, shrimp);
        fclose(file);
#endif*/
        cv::Mat temp;
        cvtColor(img, temp, CV_GRAY2RGB);
        QImage dest((const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
        dest.bits();
        q_img = dest;

        QMetaObject::invokeMethod(qml_root,"reset_image");
        QMetaObject::invokeMethod(qml_root,"reload_image");

        sprintf (msg, "Shrimp = %dseed(s); ", shrimp);
    }
    else
    {
        sprintf (msg, "Something error!\n%s not found.", filename.toLatin1().data());
    }

    QVariant src = msg;
    QMetaObject::invokeMethod(qml_root,"properties_change",Q_ARG(QVariant, src));
 }
