#include "FileSystemTree.h"
#include <QDir>
#include <algorithm>

void deleteNode(BackupTreeNode *nodeToDelete);

void deleteTree(BackupTreeNode *nodeToDelete) {
    if (nodeToDelete == nullptr) { return; }

    BackupTreeNode *sibling = nodeToDelete->m_Sibling;
    BackupTreeNode *child = nodeToDelete->m_Child;

    while (sibling != nullptr) {
        BackupTreeNode *siblingToDelete = sibling;
        sibling = sibling->m_Sibling;
        deleteNode(siblingToDelete);
    }

    deleteTree(child);

    delete nodeToDelete;
}

void deleteNode(BackupTreeNode *nodeToDelete) {
    if (nodeToDelete == nullptr) { return; }

    deleteTree(nodeToDelete->m_Child);
    delete nodeToDelete;
}

BackupTree::BackupTree() {
    m_Root = new BackupTreeNode("");
}

BackupTree::~BackupTree() {
    deleteTree(m_Root);
}

void BackupTree::addBackupPath(const QString &path) {
    QStringList parts = path.split(QDir::separator(), QString::SkipEmptyParts);

    BackupTreeNode *node = m_Root->m_Child;
    BackupTreeNode *parent = m_Root;

    int i = 0;
    int length = parts.length();

    for (; i < length; ++i) {
        auto &part = parts.at(i);

        BackupTreeNode *curr = node;
        BackupTreeNode *lastSibling = nullptr;

        while ((curr != nullptr) && (curr->m_Value != part)) {
            lastSibling = curr;
            curr = curr->m_Sibling;
        }

        if (curr != nullptr) {
            parent = curr;
            node = curr->m_Child;
            continue;
        } else {
            BackupTreeNode *nodeToAdd = new BackupTreeNode(part);

            if (lastSibling != nullptr) {
                lastSibling->m_Sibling = nodeToAdd;
            } else {
                parent->m_Child = nodeToAdd;
            }

            parent = nodeToAdd;
            node = nullptr; //nodeToAdd->m_Child;
        }
    }

    if (node != nullptr) {
        // case when we add /A/B after adding /A/B/C
        parent->m_Child = nullptr;
        deleteTree(node);
    }
}

void BackupTree::removeBackupPath(const QString &path) {
    QStringList parts = path.split(QDir::separator(), QString::SkipEmptyParts);

    BackupTreeNode *node = m_Root->m_Child;
    BackupTreeNode *parent = m_Root;

    doDeleteNode(node, parent, parts, 0);
}

bool BackupTree::isFullBackup(const QString &path) const {
    bool processedAll = false;
    std::vector<BackupTreeNode*> descentPath;
    auto *node = findNode(path, descentPath, processedAll);

    bool isFull = false;
    if (node != nullptr) {
        if (node->m_Child == nullptr) {
            isFull = true;
        } else if (processedAll) {
            isFull = false;
        }
    }

    return isFull;
}

bool BackupTree::isPartialBackup(const QString &path) const {
    bool processedAll = false;
    std::vector<BackupTreeNode*> descentPath;
    auto *node = findNode(path, descentPath, processedAll);
    return (node != nullptr) && (processedAll && (node->m_Child != nullptr));
}

bool BackupTree::isInTheTree(const QString &path) const {
    bool processedAll = false;
    std::vector<BackupTreeNode*> descentPath;
    auto *node = findNode(path, descentPath, processedAll);
    bool result = (node != nullptr) && (node->m_Child == nullptr) && processedAll;
    return result;
}

BackupTreeNode *BackupTree::findNode(const QString &path, std::vector<BackupTreeNode *> &descentPath, bool &processedAll) const {
    QStringList parts = path.split(QDir::separator(), QString::SkipEmptyParts);

    BackupTreeNode *node = m_Root->m_Child;
    BackupTreeNode *parent = m_Root;

    int i = 0;
    int length = parts.length();

    for (; i < length; ++i) {
        auto &part = parts.at(i);

        BackupTreeNode *curr = node;
        BackupTreeNode *lastSibling = nullptr;

        descentPath.push_back(parent);

        while ((curr != nullptr) && (curr->m_Value != part)) {
            lastSibling = curr;
            curr = curr->m_Sibling;
        }

        if (curr != nullptr) {
            parent = curr;
            node = curr->m_Child;
            continue;
        } else {
            break;
        }
    }

    BackupTreeNode *result = nullptr;

    processedAll = (i == length);

    if ((i <= length) && (parent != m_Root)) {
        result = parent;
    }

    return result;
}

void BackupTree::doDeleteNode(BackupTreeNode *nodeToLookIn, BackupTreeNode *parent,
                                         const QStringList &path, int currIndex) {
    Q_ASSERT(currIndex < path.length());

    BackupTreeNode *curr = nodeToLookIn;
    BackupTreeNode *lastSibling = nullptr;

    const QString &value = path.at(currIndex);

    while ((curr != nullptr) && (curr->m_Value != value)) {
        lastSibling = curr;
        curr = curr->m_Sibling;
    }

    if (currIndex < path.length() - 1) {
        doDeleteNode(curr->m_Child, curr, path, currIndex + 1);

        if (curr->m_Child == nullptr) {
            freeNode(curr, lastSibling, parent);
        }
    } else {
        freeNode(curr, lastSibling, parent);
    }
}

void BackupTree::freeNode(BackupTreeNode *nodeToDelete, BackupTreeNode *prevSibling, BackupTreeNode *parent) {
    BackupTreeNode *nextSibling = nodeToDelete->m_Sibling;

    deleteNode(nodeToDelete);

    if (prevSibling != nullptr) {
        prevSibling->m_Sibling = nextSibling;
    } else {
        parent->m_Child = nextSibling;
    }
}
