#include "pathhelpers.h"
#include <QDir>
#include <QFileInfo>
#include "FileSystemTree.h"

namespace Helpers {
    QString generateTargetPath(const QString &backupDisk, const QString &source) {
        QString result = source;

        if (source != backupDisk) {
            result = backupDisk + source;
        }

        return result;
    }

    bool areAllSubdirsAdded(BackupTree *tree, const QString &parentPath) {
        QDir dir(parentPath);
        Q_ASSERT(dir.exists());
        Q_ASSERT(tree != nullptr);

        bool anyFault = false;

        auto infoList = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
        for (auto &info: infoList) {
            QString dirPath = info.absolutePath();
            if (!tree->isInTheTree(dirPath)) {
                anyFault = true;
                break;
            }
        }

        return !anyFault;
    }

    bool addAllSubdirsButOne(BackupTree *tree, const QString &parentPath, const QString &oddPath) {
        QDir dir(parentPath);
        Q_ASSERT(dir.exists());
        Q_ASSERT(tree != nullptr);

        bool anyFault = false;

        auto infoList = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
        for (auto &info: infoList) {
        }
    }
}
