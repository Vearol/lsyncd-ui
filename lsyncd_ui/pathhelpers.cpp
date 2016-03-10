#include "pathhelpers.h"

namespace Helpers {
    QString generateTargetPath(const QString &backupDisk, const QString &source) {
        QString result = source;

        if (source != backupDisk) {
            result = backupDisk + source;
        }

        return result;
    }
}
