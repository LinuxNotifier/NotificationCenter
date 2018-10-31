#ifndef CONVERTER_H
#define CONVERTER_H

#include <QDir>
#include <QLabel>
#include <QPixmap>
#include <QImage>
#include <QBitmap>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <unistd.h>
#include <QDebug>

using namespace std;
using namespace cv;

void qimage_to_mat(const QImage& image, cv::OutputArray out)
{
    switch(image.format()) {
        case QImage::Format_Invalid:
        {
            Mat empty;
            empty.copyTo(out);
            break;
        }
        case QImage::Format_RGB32:
        {
            Mat view(image.height(),image.width(),CV_8UC4,(void *)image.constBits(),image.bytesPerLine());
            view.copyTo(out);
            break;
        }
        case QImage::Format_RGB888:
        {
            Mat view(image.height(),image.width(),CV_8UC3,(void *)image.constBits(),image.bytesPerLine());
            cvtColor(view, out, COLOR_RGB2BGR);
            break;
        }
        default:
        {
            QImage conv = image.convertToFormat(QImage::Format_ARGB32);
            Mat view(conv.height(),conv.width(),CV_8UC4,(void *)conv.constBits(),conv.bytesPerLine());
            view.copyTo(out);
            break;
        }
    }
}

void mat_to_qimage(cv::InputArray image, QImage& out)
{
    switch(image.type())
    {
        case CV_8UC4:
        {
            Mat view(image.getMat());
            QImage view2(view.data, view.cols, view.rows, view.step[0], QImage::Format_ARGB32);
            out = view2.copy();
            break;
        }
        case CV_8UC3:
        {
            Mat mat;
            cvtColor(image, mat, COLOR_BGR2BGRA); //COLOR_BGR2RGB doesn't behave so use RGBA
            QImage view(mat.data, mat.cols, mat.rows, mat.step[0], QImage::Format_ARGB32);
            out = view.copy();
            break;
        }
        case CV_8UC1:
        {
            Mat mat;
            cvtColor(image, mat, COLOR_GRAY2BGRA);
            QImage view(mat.data, mat.cols, mat.rows, mat.step[0], QImage::Format_ARGB32);
            out = view.copy();
            break;
        }
        default:
        {
            throw invalid_argument("Image format not supported");
            break;
        }
    }
}

void convert(QPixmap &pixmap, int i)
{
    qDebug() << "converting with kernel " << i;
    Mat srcMat, dstMat;
    QImage image = pixmap.toImage();
    qimage_to_mat(image, srcMat);
//    imshow("Yanhe", srcMat);
//    mat_to_qimage(img2, y2);
    // QPixmap::converFromImage and QPixmap::toImage
    blur(srcMat, dstMat, Size(i, i), Point(-1, -1));
    mat_to_qimage(dstMat, image);
//    pixmap = pixmap.fromImage(image);
    pixmap.convertFromImage(image);
}

#endif // CONVERTER_H
