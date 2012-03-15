# Add more folders to ship with the application, here
folder_qml.source = qml
folder_qml.target = .
DEPLOYMENTFOLDERS = folder_qml

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

# Smart Installer package's UID
# This UID is from the protected range and therefore the package will
# fail to install if self-signed. By default qmake uses the unprotected
# range value if unprotected UID is defined for the application and
# 0x2002CCCF value if protected UID is given to the application
#symbian:DEPLOYMENT.installer_header = 0x2002CCCF

maemo5 {
    target.path = /opt/foldergallery/bin
    INSTALLS += target
}

contains(MEEGO_EDITION,harmattan) {
    DEFINES += Q_WS_HARMATTAN # definition for harmattan
    target.path = /opt/foldergallery/bin
    INSTALLS += target
    # enable booster
    QMAKE_CXXFLAGS += -fPIC -fvisibility=hidden -fvisibility-inlines-hidden
    QMAKE_LFLAGS += -pie -rdynamic
}

# enable booster
CONFIG += qdeclarative-boostable

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

# Please do not modify the following two lines. Required for deployment.
include(qmlapplicationviewer/qmlapplicationviewer.pri)
qtcAddDeployment()

QT += sql
HEADERS += \
    DeclarativeList.h \
    mediafiles/MediaThumbnailGenerator.h \
    mediafiles/MediaThumbnailDb.h \
    mediafiles/MediaFile.h \
    mediafiles/MediaDir.h \
    java/MidletFile.h \
    java/MidletDb.h \
    java/MidletRecord.h \
    java/Phoneme.h

SOURCES += main.cpp \
    mediafiles/MediaThumbnailGenerator.cpp \
    mediafiles/MediaThumbnailDb.cpp \
    mediafiles/MediaFile.cpp \
    mediafiles/MediaDir.cpp \
    java/MidletFile.cpp \
    java/MidletDb.cpp \
    java/MidletRecord.cpp \
    java/Phoneme.cpp

OTHER_FILES += \
    qtc_packaging/debian_harmattan/* \
    qtc_packaging/debian_fremantle/*
