#include "camerahandler.h"
#include <QMediaMetaData>
#include <QStandardPaths>
#include <QDir>
#include <QDateTime>

CameraHandler::CameraHandler(QObject *parent)
    : QObject(parent)
    , m_camera(nullptr)
    , m_captureSession(nullptr)
    , m_recorder(nullptr)
    , m_isRecording(false)
{
}

CameraHandler::~CameraHandler()
{
    stopCamera();
}

void CameraHandler::startCamera()
{
    if (!m_camera) {
        m_camera = new QCamera(QCameraDevice::FrontFace, this);
        m_captureSession = new QMediaCaptureSession(this);
        m_recorder = new QMediaRecorder(this);

        m_captureSession->setCamera(m_camera);
        m_captureSession->setRecorder(m_recorder);

        connect(m_recorder, &QMediaRecorder::recorderStateChanged,
                this, [this](QMediaRecorder::RecorderState state) {
            if (state == QMediaRecorder::RecordingState) {
                m_isRecording = true;
                emit recordingStarted();
            } else if (state == QMediaRecorder::StoppedState && m_isRecording) {
                m_isRecording = false;
                emit recordingStopped(m_recorder->actualLocation().toLocalFile());
            }
        });

        connect(m_camera, &QCamera::errorOccurred, this, [this]() {
            emit cameraError(m_camera->errorString());
        });
    }

    m_camera->start();
}

void CameraHandler::stopCamera()
{
    if (m_camera) {
        m_camera->stop();
        delete m_camera;
        m_camera = nullptr;
    }
}

void CameraHandler::startRecording()
{
    if (m_recorder && m_recorder->recorderState() == QMediaRecorder::StoppedState) {
        QString videosPath = QStandardPaths::writableLocation(QStandardPaths::MoviesLocation);
        QDir().mkpath(videosPath);

        QString fileName = QString("story_%1.mp4")
            .arg(QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss"));
        QString filePath = videosPath + "/" + fileName;

        m_recorder->setOutputLocation(QUrl::fromLocalFile(filePath));
        m_recorder->setMediaFormat(QMediaFormat().mimeType());
        m_recorder->record();
    }
}

void CameraHandler::stopRecording()
{
    if (m_recorder && m_recorder->recorderState() == QMediaRecorder::RecordingState) {
        m_recorder->stop();
    }
}

void CameraHandler::switchCamera()
{
    if (m_camera) {
        QCameraDevice::Position currentPos = m_camera->cameraDevice().position();
        QCameraDevice::Position newPos = (currentPos == QCameraDevice::FrontFace) 
            ? QCameraDevice::BackFace 
            : QCameraDevice::FrontFace;
        
        m_camera->stop();
        m_camera->setCameraDevice(
            QMediaDevices::videoInputs().first([newPos](const QCameraDevice &device) {
                return device.position() == newPos;
            })
        );
        m_camera->start();
    }
}

void CameraHandler::setVideoOutput(QVideoWidget *output)
{
    if (m_captureSession) {
        m_captureSession->setVideoOutput(output);
    }
}
