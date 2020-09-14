#include "ProgressDialog.h"
#include "stdafx.h"
#include <QtWidgets/QApplication>

#include <QtConcurrent/QtConcurrent>
#include <functional>

using namespace std;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    QVector<int> vec;
    const int size = 200;

    for (int i = 0; i < size; ++i)
    {
        vec.push_back(i);
    }

    function<void(const int&)> fnc = [](const int& val)
    {
        const int max = 100000;

        for (int i = 0; i < max; ++i)
        {
            i* i;
        }

        qDebug() << QString("QVector<int> val: %1 in Thread: ").arg(val) << QThread::currentThreadId();
    };

    QFutureWatcher<void> futureWatcher;
    QProgressDialog dlg;

    dlg.setLabelText(QString("Progressing using %1 thread(s)...").arg(QThread::idealThreadCount()));
    QObject::connect(&futureWatcher, &QFutureWatcher<void>::progressRangeChanged
        , &dlg, &QProgressDialog::setRange);
    QObject::connect(&futureWatcher, &QFutureWatcher<void>::progressValueChanged
        , &dlg, &QProgressDialog::setValue);
    QObject::connect(&dlg, &QProgressDialog::canceled, &futureWatcher, &QFutureWatcher<void>::cancel);
    QObject::connect(&futureWatcher, &QFutureWatcher<void>::canceled, &dlg, &QProgressDialog::reset);
    futureWatcher.setFuture(QtConcurrent::map(vec, fnc));
    
    dlg.exec();
    futureWatcher.waitForFinished();

    return a.exec();
}
