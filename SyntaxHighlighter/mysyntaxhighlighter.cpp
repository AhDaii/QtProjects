#include "mysyntaxhighlighter.h"
#include <QTextCharFormat>
#include <QRegularExpression>
#include <QFont>

MySyntaxHighlighter::MySyntaxHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent) {}

void MySyntaxHighlighter::highlightBlock(const QString &text)
{
    QTextCharFormat fmt;
    fmt.setFont(QFont("STFangsong"));
    fmt.setFontWeight(QFont::Bold);
    fmt.setForeground(Qt::green);
    fmt.setFontPointSize(16);

    static QRegularExpression exp("\\bchar\\b");
    int idx = text.indexOf(exp);
    while (idx > 0) {
        int len = exp.match(text).capturedLength();
        setFormat(idx, len, fmt);
        idx = text.indexOf(exp, idx + len);
    }
}
