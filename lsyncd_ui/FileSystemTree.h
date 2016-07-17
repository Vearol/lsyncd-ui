#ifndef FILESYSTEMTREE_H
#define FILESYSTEMTREE_H

#include <QString>
#include <vector>

class BackupTreeNode {
public:
    BackupTreeNode(const QString &value):
        m_Value(value),
        m_Child(nullptr),
        m_Sibling(nullptr)
    { }

public:
    QString m_Value;
    BackupTreeNode *m_Child;
    BackupTreeNode *m_Sibling;
};

class BackupTree
{
public:
    BackupTree();
    ~BackupTree();

public:
    void addBackupPath(const QString &path);
    void removeBackupPath(const QString &path);
    bool isFullBackup(const QString &path) const;
    bool isPartialBackup(const QString &path) const;
    bool isInTheTree(const QString &path) const;

private:
    BackupTreeNode *findNode(const QString &path, bool &processedAll) const;
    void doDeleteNode(BackupTreeNode *nodeToLookIn, BackupTreeNode *parent,
                                 const QStringList &path, int currIndex);
    void freeNode(BackupTreeNode *nodeToDelete, BackupTreeNode *prevSibling, BackupTreeNode *parent);

private:
    BackupTreeNode *m_Root;
};

#endif // FILESYSTEMTREE_H
