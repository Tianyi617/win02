#ifndef IMAGEEDITCOMMAND_H
#define IMAGEEDITCOMMAND_H

#include <QUndoCommand>
#include <QImage>
#include <QString>

class ImageStyleEditor;

/**
 * @brief 用來記錄圖片編輯前後的狀態，以便支援Undo/Redo的命令類別
 */
class ImageEditCommand : public QUndoCommand
{
public:
    /**
     * @param editor   指向主要的 ImageStyleEditor，用來呼叫其 loadImageToScene() 等函式
     * @param oldState 編輯前的 QImage 狀態
     * @param newState 編輯後的 QImage 狀態
     * @param desc     此次命令的描述文字（會顯示在 Undo/Redo 堆疊）
     */
    ImageEditCommand(ImageStyleEditor *editor,
                     const QImage &oldState,
                     const QImage &newState,
                     const QString &desc);

    // QUndoCommand 介面
    void undo() override;
    void redo() override;

private:
    ImageStyleEditor *m_editor; ///< 主要編輯器的指標
    QImage m_oldState;          ///< 編輯前的影像快照
    QImage m_newState;          ///< 編輯後的影像快照

};

#endif // IMAGEEDITCOMMAND_H
