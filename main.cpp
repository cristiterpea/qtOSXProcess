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
        qDebug() << "Wait for Start failed. Error: " << launchProc.error();
        return false;
    }
    qDebug() << "Started.";

    if (!launchProc.waitForFinished()) {
        qDebug() << "Wait for Finish failed. Error: " << launchProc.error();
        return false;
    }
    qDebug() << "Finished.";

    QByteArray procOutput = launchProc.readAllStandardError();

    qDebug() << "State: " << launchProc.state();
    qDebug() << "Error: " << launchProc.error();
    qDebug() << "Output: " << procOutput;

    return 0;
}
