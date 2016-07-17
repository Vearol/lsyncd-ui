#ifndef PATHHELPERS_H
#define PATHHELPERS_H

#include <QString>

class BackupTree;

namespace Helpers {
    QString generateTargetPath(const QString &backupDisk, const QString &source);
    bool areAllSubdirsAdded(BackupTree *tree, const QString &parentPath);
}

#endif // PATHHELPERS_H
