#include <QCoreApplication>
#include <QProcess>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QString program = "launchctl";
    QStringList arguments;
    arguments << "load" << "/System/Library/LaunchDaemons/com.apple.FontWorker.plist";

    QProcess launchProc;
    launchProc.start(program, arguments);

    if (!launchProc.waitForStarted()) {
        qCritical() << "Wait for Start failed. Error:" << launchProc.error();
        return false;
    }
    qInfo() << "Started.";

    if (!launchProc.waitForFinished()) {
        qCritical() << "Wait for Finish failed. Error:" << launchProc.error();
        return false;
    }
    qInfo() << "Finished.";

    qDebug() << "Output stdout:" << launchProc.readAllStandardOutput();
    qDebug() << "Output stderr:" << launchProc.readAllStandardError();

    return 0;
}
