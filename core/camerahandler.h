#ifndef CAMERAHANDLER_H
#define CAMERAHANDLER_H

#include <QObject>
#include <QCamera>
#include <QMediaCaptureSession>
#include <QMediaRecorder>
#include <QVideoWidget>
#include <QUrl>

class CameraHandler : public QObject
{
    Q_OBJECT

public:
    explicit CameraHandler(QObject *parent = nullptr);
    ~CameraHandler();

    Q_INVOKABLE void startCamera();
    Q_INVOKABLE void stopCamera();
    Q_INVOKABLE void startRecording();
    Q_INVOKABLE void stopRecording();
    Q_INVOKABLE void switchCamera();

    void setVideoOutput(QVideoWidget *output);

signals:
    void recordingStarted();
    void recordingStopped(const QString &filePath);
    void cameraError(const QString &errorMessage);

private:
    QCamera *m_camera;
    QMediaCaptureSession *m_captureSession;
    QMediaRecorder *m_recorder;
    bool m_isRecording;
};

#endif // CAMERAHANDLER_H
