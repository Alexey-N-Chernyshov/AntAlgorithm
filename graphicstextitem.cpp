#include <QTextCursor>
#include <QTextBlockFormat>
#include <QKeyEvent>
#include "graphicstextitem.h"
#include "graphscene.h"

GraphicsTextItem::GraphicsTextItem(QString str, QGraphicsItem *parent) :
    QGraphicsTextItem(parent)
{
    setTextInteractionFlags(Qt::TextEditorInteraction);
    setTabChangesFocus(true);
    setTextWidth(40);
    setPlainText(str);

    //centered text
    QTextCursor  cursor = textCursor();
    QTextBlockFormat bfmt = cursor.blockFormat();
    bfmt.setAlignment(Qt::AlignCenter);
    cursor.setBlockFormat(bfmt);
    setTextCursor(cursor);
}

void GraphicsTextItem::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return)
    {
        clearFocus();
        return;
    }

    if (!event->text().isEmpty() && (event->text().at(0).isPrint()))
        if (!event->text().at(0).isDigit() || (toPlainText().length() >= 4))
            return;
    QGraphicsTextItem::keyPressEvent(event);
    qobject_cast<GraphScene *>(scene())->nodesChanged();
}
