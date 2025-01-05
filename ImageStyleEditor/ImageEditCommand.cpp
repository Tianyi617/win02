    #include "ImageEditCommand.h"
    #include "ImageStyleEditor.h"

    ImageEditCommand::ImageEditCommand(ImageStyleEditor *editor,
                                       const QImage &oldState,
                                       const QImage &newState,
                                       const QString &desc)
        : m_editor(editor),
        m_oldState(oldState),
        m_newState(newState)
    {
        // 設定此命令在 Undo Stack 上顯示的文字
        setText(desc);
    }

    void ImageEditCommand::undo()
    {
        if (m_editor) {
            // 還原到舊的 QImage 狀態
            m_editor->loadImageToScene(m_oldState);
        }

    }

    void ImageEditCommand::redo()
    {
        if (m_editor) {
            // 套用新的 QImage 狀態
            m_editor->loadImageToScene(m_newState);
        }
    }
