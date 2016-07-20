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
    void doAddBackupPath(const QString &path);
    void doRemoveBackupPath(const QString &path);
    BackupTreeNode *findNode(const QString &path, std::vector<BackupTreeNode*> &descentPath,
                             bool &processedAll) const;
    void doDeleteNode(BackupTreeNode *nodeToLookIn, BackupTreeNode *parent,
                                 const QStringList &path, int currIndex);
    void freeNode(BackupTreeNode *nodeToDelete, BackupTreeNode *prevSibling, BackupTreeNode *parent);

private:
    BackupTreeNode *m_Root;
    bool m_RootIsAdded;
};

#endif // FILESYSTEMTREE_H
